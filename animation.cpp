#include "animation.h"

Animation::Animation():m_currentFrame(0),m_isPlaying(true),m_speed(0) {}

void Animation::Tick(float time) {
    if(!m_isPlaying) return;

    m_currentFrame += m_speed * time;
    if(m_currentFrame > m_frames.size()) m_currentFrame -= m_frames.size();
    m_sprite.setTextureRect(m_frames[(int)m_currentFrame]);

    if(m_flip) m_sprite.setTextureRect(m_frames_flip[(int)m_currentFrame]);
}

void Animation::IsFlip(bool l_flip) { m_flip = l_flip; }
void Animation::IsFlip() { m_flip = !m_flip; }

void Animation::SetCurrentFrame(float l_frame) { m_currentFrame = l_frame; }
