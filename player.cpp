#include "player.h"

Player::Player() {}
Player::Player(AnimationManager &l_anim,Object &l_player,std::vector<Object> &l_ground,std::vector<Object> &l_ladder)
{
    newGame = false;
    onLadder = false;
    m_anim = l_anim;
    player = l_player;
    ground = l_ground;
    ladder = l_ladder;
    isLookDown = isLookUp = false;
    groundNum = 0;
    isMainMenu = false;

    m_life = PLAYER_LIFE;
    m_score = 0;

    Reset();
}

void Player::KeyCheck() {
    ////////////////////////////Check pressed key/////////////////////////////
    if (key["Left"]) {
        m_anim.Flip(true);
        isFlip = true;
        m_state = STATE::walk;
    }
    if(key["Right"]) {
       m_anim.Flip(false);
       isFlip = false;
       m_state = STATE::walk;
    }
    if(key["Down"]) {
        isLookDown = true;
        if(onLadder)
        m_state = STATE::climb;
    }
    if(key["Up"]) {
        isLookUp = true;
        if(onLadder)
        m_state = STATE::climb;
    }
    if (key["C"]) {
        m_state = STATE::duck;
    }
    if (key["X"]) {
        m_state = STATE::jump;
    }
    if(key["Z"]) {
        isShoot = true;
    }
    ///////////////////////////Check release key///////////////////////////
    if(!(key["Left"] || key["Right"]))
        if(m_state == STATE::walk && onGround) m_state = STATE::stay;
    if(!key["Down"])
        isLookDown = false;
    if(!key["Up"])
        isLookUp = false;
    if(!key["X"])
        if(m_state == STATE::jump && onGround) m_state = STATE::stay;
    if(!key["Z"])
        isShoot = false;
    if (!key["C"])
        if(m_state == STATE::duck) m_state = STATE::stay;
    if (!isLife) m_state = STATE::death;
}

void Player::HandleInput() {
    b2Vec2 vel = playerBody->GetLinearVelocity();
    if(key["Right"] && m_state != STATE::duck) {
        if (vel.x < 2)
        playerBody->ApplyForceToCenter(b2Vec2(15.0f, 0.0f),1);
    }
    if (key["Left"] && m_state != STATE::duck) {
        if (vel.x > -2)
        playerBody->ApplyForceToCenter(b2Vec2(-15.0f, 0.0f),1);
    }
    if(key["Up"] && m_state == STATE::climb && onLadder) {
        if (vel.x < 2)
        playerBody->ApplyForceToCenter(b2Vec2(0.0f, -50.0f),1);
    }
    if(key["Down"] && m_state == STATE::climb && onLadder) {
        if (vel.x < 2)
        playerBody->ApplyForceToCenter(b2Vec2(0.0f, 50.0f),1);
    }
    if((!key["Up"] || !key["Down"]) && m_state == STATE::climb && onLadder)
        playerBody->SetLinearVelocity(b2Vec2(0,0));
    if (key["X"] ) {
        if(onGround && !onLadder)
        playerBody->ApplyForceToCenter(b2Vec2(0.0f, -62.0f),1);
    }
}

void Player::Update(float &time) {
    for(int i = 0;i < ladder.size();i++) {
        if(GetRect().intersects(ladder[i].rect))
            onLadder = true;
        else onLadder = false;
    }
    if(Collision() != COLLISION_BREAK)
    groundNum = Collision(); // Check onGround variable and collision with blocks
    KeyCheck(); // Set State
    SetAnim(); // Set animation
    m_anim.Tick(time); // Update animation
    HandleInput(); // Give speed for player
    b2Vec2 pos = playerBody->GetPosition();
    x = pos.x * SCALE; // Set x coordinate
    y = pos.y * SCALE; // Set y coordinate

    key["Right"] = key["Left"] = key["X"] = key["Z"] = key["C"] = key["Up"] = key["Down"] = false; // Release all keys
}

void Player::SetAnim() {
    switch (m_state) {
    case STATE::stay:
        if (onGround || !onLadder) {
        if(!isShoot) {
            if(!isLookDown && !isLookUp)
                m_anim.Set("stay");
            else if (isLookUp)
                m_anim.Set("lookUp");
            else if(isLookDown)
                m_anim.Set("lookDown");
        }
        else
            if(!isLookDown && !isLookUp)
            m_anim.Set("shoot");
            else if (isLookUp)
                m_anim.Set("shootUp");
            else if(isLookDown)
                m_anim.Set("shootDown");
        }
        break;
    case STATE::walk:
        if (onGround) {
        if(!isShoot)  {
            if(!isLookDown && !isLookUp)
                m_anim.Set("walk");
            else if (isLookUp)
                m_anim.Set("lookUpAndWalk");
            else if(isLookDown)
                m_anim.Set("lookDownAndWalk");
        }
        else {
            if(!isLookDown && !isLookUp)
                 m_anim.Set("walkAndShoot");
            else if (isLookUp)
                m_anim.Set("lookUpShootAndWalk");
            else if(isLookDown)
                m_anim.Set("lookDownShootAndWalk");
        }
        }
        break;
    case STATE::jump:
        if(onGround && !isShoot) m_anim.Set("jump");
        if(isShoot) m_anim.Set("jumpAndShoot");
        break;
    case STATE::duck:
        if (onGround) {
        if(!isShoot) m_anim.Set("duck");
        else m_anim.Set("duckAndShoot");
        }
        break;
    case STATE::death:
        m_anim.Set("die1");
        break;
    case STATE::climb:
        if (isLookUp)
            m_anim.Set("lookUpAndWalk");
        else if(isLookDown)
            m_anim.Set("lookDownAndWalk");
        break;
    }
}

void Player::Draw(RenderWindow &window) {
    m_anim.Draw(window,x,y);
}


int Player::Collision() {
    b2Filter filter;
    int k = 0;
    for(size_t i = 0;i < b_ground.size() - BLOCKS_COUNT;i ++) {
            if (y + h / 4 > ground[i].rect.top || (onLadder && key["Down"] && ladder[k].rect.top > y - h )) {
                filter.categoryBits = ~WALL_CATEGORY;
                filter.maskBits = ~WALL_MASK;
             }
            else {
                 if(k != ladder.size() - 1) k++;
                filter.categoryBits = WALL_CATEGORY;
                filter.maskBits = WALL_MASK;
            }
        b_ground[i]->GetFixtureList()->SetFilterData(filter);
    }
    onGround = false;
    b2Vec2 pos = playerBody->GetPosition();
    pos.y += 22 / SCALE;
    int i = COLLISION_BREAK;
    for (unsigned j = 0;j < ground.size();j++) {
        if(((int)y + 19 == (int)ground[j].rect.top || (int)y + 20 == (int)ground[j].rect.top)  &&
                (x  > ground[j].rect.left && x < 2 * ground[j].rect.width + ground[j].rect.left)) {
            i = j;
            if(i != COLLISION_BREAK)
            break;
            else continue;
        }
    }
    if (i == COLLISION_BREAK) return COLLISION_BREAK;
    if(pos.y > ground[i].rect.top / SCALE)  {
        onGround = true;
        return i;
    }
}

float Player::GetH() {
    h = m_anim.getH();
    return h;
}
float Player::GetW() {
    w =  m_anim.getW();
    return w;
}
float Player::GetCoordX() { return x; }
float Player::GetCoordY() { return y; }

void Player::SetPlayerBody(b2Body * l_body) {
    playerBody = l_body;
}
void Player::SetGroundBody(std::vector<b2Body*> l_body) {
    b_ground = l_body;
}

bool Player::IsShoot() {
    float time = clock.getElapsedTime().asSeconds();
    if(time > 0.3) {
        clock.restart();
        return true;
    }
    else return false;
}

bool Player::GetFlip() { return isFlip; }
bool Player::GetIsShoot() { return isShoot;}
std::string Player::GetState() {return m_anim.GetName();}

int Player::GetLife() { return m_life; }
int Player::GetScore() { return m_score; }

void Player::Die(RenderWindow &window,View &view) {
        isMainMenu = false;
    m_life--;
    if(!m_life)
        GameOver(window,view);
    else Reset();
}

void Player::GameOver(RenderWindow &window,View &view){
    gamewindow = new GameWindow(window,view);
    m_life = PLAYER_LIFE;
    m_score = NULL;
    gameOverMenu = new GameOverMenu("gameOver",window,3);
    while(gameOverMenu->GetState()) {
        gameOverMenu->Update(window);
        gameOverMenu->Draw(window);
    }
    if(gameOverMenu->GetString() == "newGame") { newGame = true; isMainMenu = false; isPlaying = true;}
    else if(gameOverMenu->GetString() == "exit") isPlaying = false;
    else if(gameOverMenu->GetString() == "mainMenu") { isMainMenu = true; }
    delete gameOverMenu;
}
void Player::Reset() {
    m_anim.Set("stay");
    onGround = false;
    isShoot = false;
    m_state = STATE::stay;
    isFlip = false;
    isLife = true;
    isPlaying = true;
    newGame = false;
    x = player.rect.left;
    y = player.rect.top;
}

FloatRect Player::GetRect() {
    if(GetState() == "duck" || GetState() == "duckAndShoot")
    return FloatRect(x,y,GetW() / 2,GetH());
    else return FloatRect(x,y - GetH() / 2,GetW() / 2,GetH());
}

bool Player::IsLife() { return isLife; }
void Player::IsLife(bool l_life) { isLife = l_life; }

AnimationManager &Player::GetAnim() { return m_anim; }
void Player::IncreaseScore(int l_score) { m_score += l_score; }

std::string Player::GetLook() {
    if(isLookUp) return "lookUp";
    else if (isLookDown) return "lookDown";
    return "NONE";
}

int Player::GetGroundNum() { return groundNum; }
void Player::SetCoordY(float Y) {
    y += Y;
}

bool Player::IsNewGame() { return newGame; }
bool Player::IsPlaying() { return isPlaying;}
bool Player::IsMainMenu() {return isMainMenu;}
bool Player::IsOnLadder() { return onLadder;}
bool Player::IsOnGround() { return onGround;}
