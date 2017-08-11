#ifndef ANIMATION_H
#define ANIMATION_H

#include "constants.h"

using namespace sf;

struct Animation
{
    Animation(); // Initialize animation
    void SetCurrentFrame(float l_frame);

    void IsFlip(bool l_flip); // Check
    void IsFlip();            // flip
    void Tick(float time); // Update animation
    std::vector<IntRect> m_frames,m_frames_flip; // Frames vectors
    float m_currentFrame,m_speed;
    bool m_isPlaying,m_flip;
    Sprite m_sprite;
};

#endif // ANIMATION_H
