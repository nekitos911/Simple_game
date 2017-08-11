#include "game.h"

Game::Game()
{
    loadingX = loadingY = 0;
    tempX = tempY = 0;
    // Create window
    window.create(VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Fang",Style::Fullscreen);
    window.setFramerateLimit(60);
    icon.loadFromFile("Media/icon.png");
    window.setIcon(32, 32, icon.getPixelsPtr());
    view.reset(FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT));
    view.setCenter(VIEW_WIDTH / 2 ,VIEW_HEIGHT / 2);
    window.setView(view);

    // Create world
    gravity.Set(0.f,9.8f);
    world = new b2World(gravity);

    // Create Images
    level.LoadFromFile("Media/Level1.tmx");
    playerImage.loadFromFile("Media/Images/fang.png");
    bulletImage.loadFromFile("Media/Images/bullet.png");
    statusImage.loadFromFile("Media/icon.png");
    enemyImage.loadFromFile("Media/Images/enemy2.png");
    enemyImage.createMaskFromColor(Color::White);

    // Create Objects
    playerObject = level.GetObject("player");
    groundObjects = level.GetObjects("solid");
    blockObjects = level.GetObjects("block");
    waterObjects = level.GetObjects("water");
    enemyObjects = level.GetObjects("enemy");

    loading = new Loading(VIEW_WIDTH,VIEW_HEIGHT,L"Загрузка объектов.","");
    loading->Draw(window);
    delete loading;

    // Create Animations
    playerAnim.LoadFromXML("Media/playerAnim.xml",playerImage);
    enemyAnim.LoadFromXML("Media/enemy2Anim.xml",enemyImage);
    bulletAnim.Create("explode",bulletImage,58,6,13,13,1,0);
    bulletAnim.Create("move",bulletImage,8,10,6,6,1,0);


    loading = new Loading(VIEW_WIDTH,VIEW_HEIGHT, L"Загрузка анимаций..","");
    loading->Draw(window);
    delete loading;


    player = new Player(playerAnim,playerObject,groundObjects);
    statusbar = new StatusBar(statusImage,level.GetMapW());

    // Create ground
    for (unsigned i = 0;i < groundObjects.size();i ++) {
        wallName = "solid";
    SetWall(wallName,groundObjects[i].rect.left,groundObjects[i].rect.top,
              groundObjects[i].rect.width,0);
    }
    // Create level walls
    for (unsigned i = 0;i < blockObjects.size();i ++) {
        wallName = "block";
    SetWall(wallName,blockObjects[i].rect.left,blockObjects[i].rect.top,
              blockObjects[i].rect.width,blockObjects[i].rect.height);
    }

    loading = new Loading(VIEW_WIDTH,VIEW_HEIGHT,L"Запуск мира...","");
    loading->Draw(window);
    delete loading;

    GameReset();

}

void Game::SetWall(std::string name,int x,int y,int w,int h) {
    b2PolygonShape gr;
    b2BodyDef bdef;
    bdef.type = b2_staticBody;
    b2Body *body;

    gr.SetAsBox(w / ( SCALE),h / ( SCALE));
    bdef.position.Set((x + w) / SCALE ,(y + h) / SCALE);
    body = world->CreateBody(&bdef);
    body->CreateFixture(&gr,1.0f);
    b2Filter filter;
    filter.categoryBits = WALL_CATEGORY;
    filter.maskBits = WALL_MASK;
    body->GetFixtureList()->SetFilterData(filter);
    b_ground.push_back(body);
}

void Game::SetPlayer(int x,int y,int w,int h) {
    b2BodyDef bdef;
    bdef.type = b2_dynamicBody;

    bdef.position.Set(x ,y );

    bdef.fixedRotation = true;

    b2PolygonShape shape;
    shape.SetAsBox(w / (100 * SCALE),h / (2 * SCALE));

    playerBody = world->CreateBody(&bdef);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 9.0f; fixtureDef.friction = 15.0f;
    playerBody->CreateFixture(&fixtureDef);
    b2Filter filter;
    filter.categoryBits = PLAYER_CATEGORY;
    filter.maskBits = PLAYER_MASK;
    playerBody->GetFixtureList()->SetFilterData(filter);
}

void Game::SetEnemy(int x, int y, int w, int h) {
    b2BodyDef bdef;
    bdef.type = b2_kinematicBody;

    bdef.position.Set(x,y);

    b2PolygonShape shape;
    shape.SetAsBox(w / (2 * SCALE),h / (2 * SCALE));

    b2Body *body = world->CreateBody(&bdef);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 3.0f; fixtureDef.friction = 6.0f;
    b2Filter filter;
    filter.categoryBits = ENEMY_CATEGORY;
    filter.maskBits = ~ENEMY_MASK;
    body->CreateFixture(&fixtureDef);
    body->GetFixtureList()->SetFilterData(filter);
    enemybody.push_back(body);
}

void Game::SetView(int x,int y) {
    tempX = x; tempY = y;
    // if player at the beginning of level
    if (x <= VIEW_WIDTH / 2 - OFFSET_X) tempX = VIEW_WIDTH / 2 - OFFSET_X;
    // if player at the end of level
    if (x > level.GetMapW() - VIEW_WIDTH / 2 - OFFSET_X) tempX = level.GetMapW() - VIEW_WIDTH / 2 - OFFSET_X;
    tempY = level.GetMapH() / 2;

    view.setCenter(tempX + OFFSET_X,tempY);
}

void Game::GameLoop() {
    while (window.isOpen()) {
        Events();
        HandleInput(); // Set key for player
        Update(); // Update world
        SetView(player->GetCoordX(),player->GetCoordY());
        Draw(); // Draw world
        EntitiesDie(); // delete bullets and enemy
        if (!player->IsLife()) PlayerBulletRect();
    }
}

void Game::Events() {
    Event event;
    while(window.pollEvent(event)) {
        if(event.type == Event::Closed)
            window.close();
    }
}

void  Game::HandleInput() {
    if (Keyboard::isKeyPressed(Keyboard::Left)) {player->key["L"] = true;}
    if (Keyboard::isKeyPressed(Keyboard::Right)) {player->key["R"] = true;}
    if (Keyboard::isKeyPressed(Keyboard::Down)) {player->key["D"] = true;}
    if (Keyboard::isKeyPressed(Keyboard::X)) {player->key["X"] = true;}
    if (Keyboard::isKeyPressed(Keyboard::Z)) {
        player->key["Z"] = true;
        if (player->IsShoot() && player->GetIsShoot()) {
            if (player->GetState() != "duck" && player->GetState() != "duckAndShoot") {
            if (!player->GetFlip())
            entities.push_back(new Bullet("bullet",bulletAnim,level,player->GetRect().left + player->GetW() / 1.5,
                                                       player->GetCoordY() - player->GetH() / 4,player->GetFlip()));
            else  entities.push_back(new Bullet("bullet",bulletAnim,level,player->GetRect().left - player->GetW() / 1.5,
                                             player->GetCoordY() - player->GetH() / 4,player->GetFlip()));
            }
            else {
                if (!player->GetFlip())
                entities.push_back(new Bullet("bullet",bulletAnim,level,player->GetRect().left + player->GetW() / 1.5,
                                                           player->GetCoordY() + player->GetH() / 1.5,player->GetFlip()));
                else  entities.push_back(new Bullet("bullet",bulletAnim,level,player->GetRect().left - player->GetW() / 1.5,
                                                 player->GetCoordY() + player->GetH() / 1.5,player->GetFlip()));
            }
        }
    }
}

void Game::EnemyDie() {
    auto itr = enemybody.begin();
    for (auto it = entities.begin();it != entities.end(); it ++,itr++) {
            Entity *a = *it;
            for (auto it2 = entities.begin(); it2 != entities.end(); it2 ++) {
                if(a->GetName() == "enemy") {
                    Entity *b = *it2;
                    if(b->GetName() == "bullet") {
                        if(a->GetBodyRect().intersects(b->GetRect())) {
                            player->IncreaseScore(10);
                            world->DestroyBody(*itr);
                            itr = enemybody.erase(itr);
                            a->Die();
                            b->Die();
                        }
                    }
                }
            }
    }
}

void Game::PlayerDie() {
    // If player fell in the water
    for (unsigned i = 0;i < waterObjects.size();i ++) {
        if (player->GetRect().intersects(waterObjects[i].rect)) {
            world->DestroyBody(playerBody);
            player->Die(window);
            for(auto it = entities.begin();it != entities.end();) {
                if (!entities.empty()) {
                    it = entities.erase(it);
                    delete (*it);
                }
                if (!enemybody.empty()) {
                    auto itr = enemybody.begin();
                    world->DestroyBody(*itr);
                    *itr = nullptr;
                    enemybody.clear();
                }
            }
            GameReset();
            return;
        }
    }
    // If bullet hit the player
    for(auto it = entities.begin();it != entities.end();it ++) {
        Entity *b = *it;
        if (b->GetName() == "enemyBullet" && b->GetRect().intersects(player->GetRect())) {
        player->IsLife(false);
        return;
        }
    }
}

void Game::GameReset() {
    playerDeathAnimTimer = 0;
    for (unsigned i = 0;i < enemyObjects.size();i ++) {
        SetEnemy(enemyObjects[i].rect.left / SCALE,enemyObjects[i].rect.top / SCALE,
                 enemyAnim.getW(),enemyAnim.getH());
    }
    int i = 0;
    for (auto it = enemybody.begin();it != enemybody.end();it ++,i++) {
        entities.push_back(new Enemy("enemy",enemyAnim,level,enemyObjects[i].rect.left,enemyObjects[i].rect.top,0,it));
    }
        SetPlayer(playerObject.rect.left / SCALE,playerObject.rect.top / SCALE,
              player->GetW(),player->GetH() - 10);
    player->SetPlayerBody(playerBody);
    player->SetGroundBody(b_ground);
    timer = 0;
    if (tempX == VIEW_WIDTH / 2 - OFFSET_X || tempX == 0)
        loading = new Loading(VIEW_WIDTH / 2 - OFFSET_X,VIEW_HEIGHT,L"Level 1","");
    else
    loading = new Loading(tempX,VIEW_HEIGHT,L"Level 1","");
    loading->GetImage(statusImage,"x " + std::to_string(player->GetLife()),1);
    while (timer < 500) {
        timer += clock.getElapsedTime().asSeconds();
        loading->Draw(window);
    }
    delete loading;
    player->GetAnim().Flip(false);
    player->IsLife(true);
    timer = 0;
}

void Game::EntitiesDie() {
    for (auto it = entities.begin();it != entities.end();) {
        Entity *b = *it;
        if(b->GetName() == "bullet" || b->GetName() == "enemyBullet") {
            if (player->GetRect().left < VIEW_WIDTH / 2 - OFFSET_X / 5) {
            if (b->GetRect().left > VIEW_WIDTH + OFFSET_X)
                b->Die();
        }
            else
                if (b->GetRect().left >player->GetCoordX() + VIEW_WIDTH / 2 + OFFSET_X)
                    b->Die();
        }
        bool life = b->IsLife();
        if (!life)	{
            it  = entities.erase(it);
            delete b;
        }
        else it++;
    }
}

void Game::Update() {
    world->Step(1.0f/60.0f,8,3);
    float time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time /= 600;
    if (time > 40) time = 40;
    PlayerDie(); // Check for player lose
    player->Update(time); // Update player
    EnemyDie(); // Check for enemy die
    statusbar->Update(std::to_string(player->GetLife()),std::to_string(player->GetScore())); // Update score and life
    // Update bullets and enemies
    for(auto it = entities.begin();it != entities.end();it++) {
        Entity *b = *it;
        b->Update(time);
        b->SetPlayerCoords(player->GetCoordX(),playerBody->GetPosition().y);
        // Allow to shoot for enemy
        if (b->IsShoot() && b->GetName() == "enemy") {
            timer += time;
            if (timer > 1200) {
                timer = 0;
                entities.push_back(new Bullet("enemyBullet",bulletAnim,level,b->GetRect().left - enemyAnim.getW() / 1.5,
                                                           b->GetRect().top - enemyAnim.getH() / 4,1));
            }
        }
    }
}

void Game::Draw() {
    window.setView(view);
    window.clear();
    level.Draw(window); // Draw map
    player->Draw(window); // Draw player
    statusbar->Draw(window,player->GetCoordX()); // Draw statusbar
    // Draw bullets and enemies
    for (auto it = entities.begin(); it != entities.end();it ++)
        (*it)->Draw(window);
    window.display();
}

void Game::PlayerBulletRect() {
    while (playerDeathAnimTimer < 30) {
        playerDeathAnimTimer += clock.getElapsedTime().asSeconds();
        player->GetAnim().Tick(10);
        Draw();
        if (playerDeathAnimTimer > 15)
        player->GetAnim().Set("die");
    }
    world->DestroyBody(playerBody);
    player->Die(window);
    for (auto it1 = entities.begin();it1 != entities.end();) {
        if (!entities.empty()) {
            it1 = entities.erase(it1);
            delete (*it1);
        }
        if (!enemybody.empty()) {
            auto itr = enemybody.begin();
            world->DestroyBody(*itr);
            *itr = nullptr;
            enemybody.clear();
        }
    }
GameReset();
}
