#include "player.h"

Player::Player() {}
Player::Player(AnimationManager &l_anim,Object &l_player,std::vector<Object> &l_ground)
{
    m_anim = l_anim;
    player = l_player;
    ground = l_ground;

    m_life = 3;
    m_score = 0;

    Reset();
}

void Player::KeyCheck() {
    ////////////////////////////Check pressed key/////////////////////////////
    if (key["L"]) {
        m_anim.Flip(true);
        isFlip = true;
        m_state = STATE::walk;
    }
    if(key["R"]) {
       m_anim.Flip(false);
       isFlip = false;
       m_state = STATE::walk;
    }
    if (key["D"]) {
        m_state = STATE::duck;
    }
    if (key["X"]) {
        m_state = STATE::jump;
    }
    if(key["Z"]) {
        isShoot = true;
    }
    ///////////////////////////Check release key///////////////////////////
    if(!(key["L"] || key["R"]))
        if(m_state == STATE::walk && onGround) m_state = STATE::stay;
    if(!key["X"])
        if(m_state == STATE::jump && onGround) m_state = STATE::stay;
    if(!key["Z"])
        isShoot = false;
    if (!key["D"])
        if(m_state == STATE::duck) m_state = STATE::stay;
    if (!isLife) m_state = STATE::death;
}

void Player::HandleInput() {
    b2Vec2 vel = playerBody->GetLinearVelocity();
    if(key["R"] && m_state != STATE::duck) {
        if (vel.x < 2)
        playerBody->ApplyForceToCenter(b2Vec2(15.0f, 0.0f),1);
    }
    if (key["L"] && m_state != STATE::duck) {
        if (vel.x > -2)
        playerBody->ApplyForceToCenter(b2Vec2(-15.0f, 0.0f),1);
    }
    if (key["X"] ) {
        if(onGround)
        playerBody->ApplyForceToCenter(b2Vec2(0.0f, -62.0f),1);
    }
}

void Player::Update(float &time) {
    Collision(); // Check onGround variable and collision with blocks
    KeyCheck(); // Set State
    SetAnim(); // Set animation
    m_anim.Tick(time); // Update animation
    HandleInput(); // Give speed for player
    b2Vec2 pos = playerBody->GetPosition();
    x = pos.x * SCALE; // Set x coordinate
    y = pos.y * SCALE; // Set y coordinate

    key["R"] = key["L"] = key["X"] = key["Z"] = key["D"] = false; // Release all keys
}

void Player::SetAnim() {
    switch (m_state) {
    case STATE::stay:
        if (onGround) {
        if(!isShoot) m_anim.Set("stay");
        else m_anim.Set("shoot");
        }
        break;
    case STATE::walk:
        if (onGround) {
        if(!isShoot)  m_anim.Set("walk");
        else m_anim.Set("walkAndShoot");
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
    }
}

void Player::Draw(RenderWindow &window) {
    m_anim.Draw(window,x,y);
}


void Player::Collision() {
    b2Filter filter;
    for(size_t i = 0;i < b_ground.size() - BLOCKS_COUNT;i ++) {
            if (y + h / 4 > ground[i].rect.top) {
                filter.categoryBits = ~WALL_CATEGORY;
                filter.maskBits = ~WALL_MASK;
             }
            else {
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
        if((y + 19 == ground[j].rect.top || y + 20 == ground[j].rect.top)  &&
                (x  > ground[j].rect.left && x < 2 * ground[j].rect.width + ground[j].rect.left)) {
            i = j;
            if(i != COLLISION_BREAK)
            break;
            else continue;
        }
    }
    if (i == COLLISION_BREAK) return;
    if(pos.y > ground[i].rect.top / SCALE) onGround = true;
}

float Player::GetH() {
    h = m_anim.getH();
    return h;
}
float Player::GetW() {
    w =  m_anim.getW();
    return w;
}
int Player::GetCoordX() { return x; }
int Player::GetCoordY() { return y; }

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

void Player::Die(RenderWindow &window) {
    m_life--;
    if(!m_life)
        GameOver(window);
    else Reset();
}

void Player::GameOver(RenderWindow &window){
    window.close();
}
void Player::Reset() {
    m_anim.Set("stay");
    onGround = false;
    isShoot = false;
    m_state = STATE::stay;
    isFlip = false;
    x = player.rect.left;
    y = player.rect.top;
}

IntRect Player::GetRect() {
    if (m_anim.GetName() == "duck"  || m_anim.GetName() == "duckAndShoot")
    return IntRect(x,y,w / 2,h);
    else return IntRect(x,y - h / 2,w / 2,h);
}

bool Player::IsLife() { return isLife; }
void Player::IsLife(bool l_life) { isLife = l_life; }

AnimationManager &Player::GetAnim() { return m_anim; }
void Player::IncreaseScore(int l_score) { m_score += l_score; }
