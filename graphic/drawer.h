#ifndef DRAWER_H
#define DRAWER_H

#include "framebuffer.h"
#include "../math/coordinates.h"

#include <memory>

class Drawer
{
    std::shared_ptr <FrameBuffer> m_frame;

private:
    void m_drawSphere(const Coordinates &coord, double r, Color c = Color(255))
    {

    }


public:
    Drawer(std::shared_ptr <FrameBuffer> &frame) : m_frame(frame)
    {}

    void swap()
    {
        m_frame->swap();
    }

    void drawSphere(const Coordinates &coord, double r, Color c = Color(255))
    {
        m_drawSphere(coord, r, c);
    }
};

#endif // DRAWER_H
