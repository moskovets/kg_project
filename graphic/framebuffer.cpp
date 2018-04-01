#include "framebuffer.h"

FrameBuffer::FrameBuffer(uint32_t h, uint32_t w, const Color &c)
    : m_currBuff(0)
{
    for (uint8_t i = 0; i < m_buffCount; i++) {
        m_buff[i] = new ZBuffer(h, w, c);
    }
}

FrameBuffer::~FrameBuffer()
{
    for (uint8_t i = 0; i < m_buffCount; i++) {
        delete m_buff[i];
    }
}

void FrameBuffer::swap()
{
    m_buff[m_currBuff]->clear();
    m_currBuff = (m_currBuff + 1) % m_buffCount;
}

ZBuffer *FrameBuffer::getBuffer()
{
    return m_buff[m_currBuff];
}
