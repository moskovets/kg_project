#include "triangle.h"

Triangle::Triangle(Vector4 vertex[], Vector4 normal[])
{
    for(int i = 0; i < 3; i++) {
        m_vertex[i] = vertex[i];
        m_normal[i] = normal[i];
    }
}

Triangle::Triangle()
{}

void Triangle::setVertex(unsigned index, const Vector4 &vertex)
{
    if (index < 3)
        m_vertex[index] = vertex;
}

void Triangle::setNormal(unsigned index, const Vector4 &normal)
{
    if (index < 3)
        m_normal[index] = normal;
}

void Triangle::set(unsigned index, const Vector4 &vertex, const Vector4 &normal)
{
    if (index < 3) {
        m_normal[index] = normal;
        m_vertex[index] = vertex;
    }
}

Vector4 Triangle::getVertex(unsigned index) const
{
    return m_vertex[index > 2 ? 2 : index];
}

Vector4 Triangle::getNormal(unsigned index) const
{
    return m_normal[index > 2 ? 2 : index];
}
