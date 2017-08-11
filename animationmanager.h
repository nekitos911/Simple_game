#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "animation.h"
#include "constants.h"

class AnimationManager
{
public:
    AnimationManager();
    ~AnimationManager();

    // Create simple animation
    void Create(std::string l_name,Image &image,int x,int y,int w,int h,size_t count,float speed,int step = 0);
    void Set(std::string l_name); // Set animation
    void LoadFromXML(std::string fileName,Image &img); // Load animations from Xml

    float getW(); // Get
    float getH(); // size

    void Tick(float time); // Update animations

    void Flip(bool l_flip); // Check
    void Flip();            // flip

    std::string GetName(); // Get name of current animation
    void SetName(std::string l_name); // Set curren animation's name
    void Draw(RenderWindow &window,int x = 0,int y = 0); // Draw animations
private:
    std::string m_currentAnim;
    std::map<std::string,Animation> m_animList;
    std::vector<std::string> animName;
    std::string name;
    Texture texture;
};

#endif // ANIMATIONMANAGER_H
