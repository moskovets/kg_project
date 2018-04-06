#include "camera.h"

Color Camera::lightColor() const
{
    return m_lightColor;
}

void Camera::setLightColor(const Color &lightColor)
{
    m_lightColor = lightColor;
}

Vector4 Camera::lightVector() const
{
    return m_lightVector;
}

void Camera::setLightVector(const Vector4 &lightVector)
{
    m_lightVector = lightVector;
}
