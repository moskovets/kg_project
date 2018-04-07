#ifndef SETDRAWER_H
#define SETDRAWER_H

#include "drawer3d.h"
#include "render.h"
#include "../model/mesh.h"
#include "camera.h"

class SetDrawer
{
    Mesh        *m_mesh;
    Drawer3D    *m_drawer;
    Render      *m_render;
    Model        m_model;
public:
    SetDrawer(uint32_t h, uint32_t w, unsigned xnum = 10, unsigned ynum = 10, double radius = 1,
              const Camera &camera = Camera(Vector4(1/sqrt(3), 1/sqrt(3), 1/sqrt(3)), Color()));

    ~SetDrawer();

    void rotateCamera(double xAngle = 0, double yAngle = 0, double zAngle = 0);

    void setPixel(const Vector4 &position, const Color &color = Color(0,255));

    QImage getImage();
};

#endif // SETDRAWER_H
