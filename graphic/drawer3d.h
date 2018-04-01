#ifndef DRAWER3D_H
#define DRAWER3D_H

#include "framebuffer.h"
#include "../model/triangle.h"

#include <memory>

enum DrawerModeEnum {
    DME_FLAT,
    DME_GURO
};

class Drawer3D
{
    std::shared_ptr <FrameBuffer> m_frame;

    DrawerModeEnum m_mode;

    Vector4 m_lightVector;

private:
    void m_drawFlatTriangle(const Triangle &triangle)
    {

    }

    void m_drawGuroTriangle(const Triangle &triangle)
    {

    }

    void m_drawTriangle(const Triangle &triangle)
    {
        switch(m_mode) {
        case DME_FLAT:
            m_drawFlatTriangle(triangle);
            break;
        case DME_GURO:
            m_drawGuroTriangle(triangle);
            break;
        }
    }

public:
    Drawer3D(std::shared_ptr <FrameBuffer> &frame, DrawerModeEnum mode = DME_FLAT, Vector4 lightVector = Vector4(1/sqrt(2), 1/sqrt(2), 0)) :
        m_frame(frame), m_mode(mode), m_lightVector(lightVector)
    {}

    void swap()
    {
        m_frame->swap();
    }

    void setMode(DrawerModeEnum mode)
    {
        m_mode = mode;
    }


    DrawerModeEnum mode() const;
    Vector4 lightVector() const;
    void setLightVector(const Vector4 &lightVector);
};

#endif // DRAWER3D_H
