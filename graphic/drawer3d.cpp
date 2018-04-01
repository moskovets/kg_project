#include "drawer3d.h"


Vector4 Drawer3D::lightVector() const
{
    return m_lightVector;
}

void Drawer3D::setLightVector(const Vector4 &lightVector)
{
    m_lightVector = lightVector.norm3();
}

DrawerModeEnum Drawer3D::mode() const
{
    return m_mode;
}
