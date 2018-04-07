#include "camera.h"

Color Camera::lightColor() const
{
    return m_lightColor;
}

void Camera::setLightColor(const Color &lightColor)
{
    m_lightColor = lightColor;
}

Camera::Camera(const Vector4 &vector, const Color &color) :
    m_lightVector(vector), m_lightColor(color)
{}

void Camera::rotate(double xAngle, double yAngle, double zAngle)
{
    m_lightVector = Matrix4::rotateVector(m_lightVector, xAngle, yAngle, zAngle);
}

Vector4 Camera::lightVector() const
{
    return m_lightVector;
}

void Camera::setLightVector(const Vector4 &lightVector)
{
    m_lightVector = lightVector;
}
