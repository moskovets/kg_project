#include "drawer3d.h"


Vector4 Drawer3D::lightVector() const
{
    return m_lightVector;
}

void Drawer3D::setLightVector(const Vector4 &lightVector)
{
    m_lightVector = lightVector.norm3();
}

Matrix4 Drawer3D::projectingMatr() const
{
    return m_projectingMatr;
}

void Drawer3D::setProjectingMatr(const Matrix4 &projectingMatr)
{
    m_projectingMatr = projectingMatr;
}

DrawerModeEnum Drawer3D::mode() const
{
    return m_mode;
}
