#include "animationmanager.h"

using namespace tinyxml2;

AnimationManager::AnimationManager() {}
AnimationManager::~AnimationManager() { m_animList.clear(); }

void AnimationManager::Create(std::string l_name, Image &image, float x, float y, float w, float h, size_t count, float speed, int step) {
    Animation anim;
    anim.m_flip = false;
    anim.m_speed = speed;
    texture.loadFromImage(image);
    anim.m_sprite.setTexture(texture);
    anim.m_sprite.setOrigin(w / 2,h / 2);
    animName.push_back(l_name);
    for (size_t i = 0; i < count; i ++) {
        anim.m_frames.push_back(IntRect(x + i * step,y,w,h));
        anim.m_frames_flip.push_back(IntRect(x + i * step + w,y,-w,h));
    }
    m_animList[l_name] = anim;
    m_currentAnim = l_name;

}

void AnimationManager::Set(std::string l_name) {
    SetName(l_name);
    if (m_currentAnim == "duck" || m_currentAnim == "duckAndShoot" || m_currentAnim == "die" )
        m_animList[m_currentAnim].m_sprite.setOrigin
                (m_animList[m_currentAnim].m_frames[0].width / 2,0);
    else m_animList[m_currentAnim].m_sprite.setOrigin
            (m_animList[m_currentAnim].m_frames[0].width / 2,m_animList[m_currentAnim].m_frames[0].height / 2);
    if (m_currentAnim != l_name) {
    m_currentAnim = l_name;
    m_animList[l_name].SetCurrentFrame(0);
    }
}

void AnimationManager::Tick(float time) {

    m_animList[m_currentAnim].Tick(time);
}
void AnimationManager::Flip(bool l_flip) {
    for (unsigned i = 0;i < animName.size();i ++)
    m_animList[animName[i]].IsFlip(l_flip);
}
void AnimationManager::Flip() {
    for (unsigned i = 0;i < animName.size();i ++)
        m_animList[animName[i]].IsFlip();
}

void AnimationManager::Draw(RenderWindow &window, float x, float y) {
    m_animList[m_currentAnim].m_sprite.setPosition(x,y);
    window.draw(m_animList[m_currentAnim].m_sprite);
}

float AnimationManager::getW() {
    return m_animList[m_currentAnim].m_frames[0].width;
}
float AnimationManager::getH() {
    return m_animList[m_currentAnim].m_frames[0].height;
}

void AnimationManager::LoadFromXML(std::string fileName,Image &img)
{
    XMLDocument animFile(fileName.c_str());

    animFile.LoadFile(fileName.c_str());

    XMLElement *head;
    head = animFile.FirstChildElement("sprites");

    XMLElement *animElement;
    animElement = head->FirstChildElement("animation");
    while(animElement)
    {
        Animation anim;
        m_currentAnim = animElement->Attribute("title");
        int delay = atoi(animElement->Attribute("delay"));
        texture.loadFromImage(img);
        anim.m_speed = 1.0f / delay; anim.m_sprite.setTexture(texture);
        animName.push_back(m_currentAnim);

        XMLElement *cut;
        cut = animElement->FirstChildElement("cut");
        while (cut)
        {
            float x = atoi(cut->Attribute("x"));
            float y = atoi(cut->Attribute("y"));
            float w = atoi(cut->Attribute("w"));
            float h = atoi(cut->Attribute("h"));

            anim.m_frames.push_back( IntRect(x,y,w,h) );
            anim.m_frames_flip.push_back( IntRect(x + w,y,-w,h)  );
            cut = cut->NextSiblingElement("cut");
        }

        anim.m_sprite.setOrigin(anim.m_frames[0].width / 2,anim.m_frames[0].height / 2);

        m_animList[m_currentAnim] = anim;
        animElement = animElement->NextSiblingElement("animation");
    }
}

std::string AnimationManager::GetName() { return name; }
void AnimationManager::SetName(std::string l_name) {
    name = l_name;
}
