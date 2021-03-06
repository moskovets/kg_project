#ifndef DRAWER3D_H
#define DRAWER3D_H

#include "framebuffer.h"
#include "../model/triangle.h"
#include "../model/model.h"
#include "../math/matrix4.h"
#include "light.h"

#include <memory>

#define EPS_COORD 0.5

inline Vector4 interpolate(const Vector4 &v1, const Vector4 &v2, double aspect);
inline double interpolate(double x1, double y1, double x2, double y2, double x);

enum DrawerModeEnum {
    DME_FLAT,
    DME_GURO
};

class Drawer3D
{
    std::shared_ptr <FrameBuffer> m_frame;

    DrawerModeEnum m_mode;

    Light  m_light;

    Matrix4 m_projectingMatr;

private:
    double m_intensity(const Vector4 &normal) const;

    void m_drawFlatTriangle(const Triangle &triangle, const Color &color = Color());

    void m_drawGuroTriangle(const Triangle &triangle, const Color &color = Color());

    void m_drawVerticalTriangle(const Triangle &triangle, const Color &color = Color());

    void m_drawTriangle(const Triangle &triangle, const Color &color = Color());

public:
    Drawer3D(std::shared_ptr <FrameBuffer> &frame, DrawerModeEnum mode = DME_FLAT,
             const Light &light = Light(Vector4(1/sqrt(3), 1/sqrt(3), 1/sqrt(3)), Color(255, 255, 255)));

    void swap();

    void setMode(DrawerModeEnum mode);

    void rotateLight(double xAngle = 0, double yAngle = 0, double zAngle = 0);

    void drawModel(const Model &model);

    DrawerModeEnum mode() const;
    Vector4 lightVector() const;
    void setLightVector(const Vector4 &lightVector);
    Matrix4 projectingMatr() const;
    void setProjectingMatr(const Matrix4 &projectingMatr);
};

#endif // DRAWER3D_H
