#ifndef LIGHT_H
#define LIGHT_H

#include "math/vector4.h"
#include "color.h"
#include "math/matrix4.h"


class Light
{
    Vector4 m_lightVector;

    Color m_lightColor;

public:
    Light(const Vector4 &vector = Vector4(1/sqrt(3), 1/sqrt(3), 1/sqrt(3)),  const Color &color = Color(255, 255, 255));

    void rotate(double xAngle = 0, double yAngle = 0, double zAngle = 0);

    Vector4 lightVector() const;
    void setLightVector(const Vector4 &lightVector);
    Color lightColor() const;
    void setLightColor(const Color &lightColor);

    Color calculateColor(const Color &modelColor, double inten) const;
};

#endif // LIGHT_H
