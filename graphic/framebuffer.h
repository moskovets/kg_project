#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "zbuffer.h"

class FrameBuffer
{
    static const uint8_t m_buffCount = 2;
    ZBuffer *m_buff[m_buffCount];
    uint8_t m_currBuff;

public:
    FrameBuffer(uint32_t h, uint32_t w, const Color &c = Color());

    ~FrameBuffer();

    void swap();

    ZBuffer *getBuffer();
};

#endif // FRAMEBUFFER_H
