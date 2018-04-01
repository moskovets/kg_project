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

Vector4 Triangle::getAverageNormal() const
{
    Vector4 res = m_normal[0] + m_normal[1] + m_normal[2];
    res.normalize3();
    return res;
}

Triangle Triangle::sortX() const
{
    Vector4 vertex[3];
    Vector4 normal[3];
    if(m_vertex[0].x() <= m_vertex[1].x() && m_vertex[0].x() <= m_vertex[2].x()) {
        vertex[0] = m_vertex[0];
        normal[0] = m_normal[0];
        if(m_vertex[1].x() >= m_vertex[2].x()) {
            vertex[2] = m_vertex[1];
            normal[2] = m_normal[1];
            vertex[1] = m_vertex[2];
            normal[1] = m_normal[2];
        } else {
            vertex[2] = m_vertex[2];
            normal[2] = m_normal[2];
            vertex[1] = m_vertex[1];
            normal[1] = m_normal[1];
        }
    } else if(m_vertex[1].x() <= m_vertex[0].x() && m_vertex[1].x() <= m_vertex[2].x()) {
        vertex[0] = m_vertex[1];
        normal[0] = m_normal[1];
        if( m_vertex[0].x() >= m_vertex[2].x()) {
            vertex[2] = m_vertex[0];
            normal[2] = m_normal[0];
            vertex[1] = m_vertex[2];
            normal[1] = m_normal[2];
        } else {
            vertex[2] = m_vertex[2];
            normal[2] = m_normal[2];
            vertex[1] = m_vertex[0];
            normal[1] = m_normal[0];
        }
    } else if(m_vertex[2].x() <= m_vertex[1].x() && m_vertex[2].x() <= m_vertex[0].x()) {
        vertex[0] = m_vertex[2];
        normal[0] = m_normal[2];
        if(m_vertex[1].x() >= m_vertex[0].x()) {
            vertex[2] = m_vertex[1];
            normal[2] = m_normal[1];
            vertex[1] = m_vertex[0];
            normal[1] = m_normal[0];
        } else {
            vertex[2] = m_vertex[0];
            normal[2] = m_normal[0];
            vertex[1] = m_vertex[1];
            normal[1] = m_normal[1];
        }
    }
    return Triangle(vertex, normal);
}

void Triangle::multVertex(const Matrix4 &matr)
{
    for(int i = 0; i < 3; i++) {
        m_vertex[i] = m_vertex[i] * matr;
    }
}

void Triangle::multNormal(const Matrix4 &matr)
{
    for(int i = 0; i < 3; i++) {
        m_normal[i] = m_normal[i] * matr;
        m_normal[i].normalize3();
    }
}

void Triangle::mult(const Matrix4 &matr)
{
    multNormal(matr);
    multVertex(matr);
}

Vector4 Triangle::getVertex(unsigned index) const
{
    return m_vertex[index > 2 ? 2 : index];
}

Vector4 Triangle::getNormal(unsigned index) const
{
    return m_normal[index > 2 ? 2 : index];
}
