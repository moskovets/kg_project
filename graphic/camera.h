#ifndef CAMERA_H
#define CAMERA_H

#include "math/vector4.h"
#include "color.h"
#include "math/matrix4.h"


class Camera
{
    Vector4 m_lightVector;

    Color m_lightColor;

public:
    Camera(const Vector4 &vector = Vector4(1/sqrt(3), 1/sqrt(3), 1/sqrt(3)),  const Color &color = Color());

    void rotate(double xAngle = 0, double yAngle = 0, double zAngle = 0);

    Vector4 lightVector() const;
    void setLightVector(const Vector4 &lightVector);
    Color lightColor() const;
    void setLightColor(const Color &lightColor);
};

#endif // CAMERA_H
