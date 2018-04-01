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
    m_currBuff = (m_currBuff + 1) % m_buffCount;
    m_buff[m_currBuff]->clear();
}

ZBuffer *FrameBuffer::getPreviousBuffer()
{
    if(m_currBuff > 0)
        return m_buff[m_currBuff - 1];
    else
        return m_buff[m_buffCount - 1];
}

ZBuffer *FrameBuffer::getBuffer()
{
    return m_buff[m_currBuff];
}
