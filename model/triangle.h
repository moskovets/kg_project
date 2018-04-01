#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../math/matrix4.h"

class Triangle
{
    Vector4 m_vertex[3];
    Vector4 m_normal[3];

public:
    Triangle(Vector4 vertex[], Vector4 normal[]);
    Triangle();

    void setVertex(unsigned index, const Vector4 &vertex);
    void setNormal(unsigned index, const Vector4 &normal);
    void set(unsigned index, const Vector4 &vertex, const Vector4 &normal);
    Vector4 getAverageNormal() const
    {
        Vector4 res = m_normal[0] + m_normal[1] + m_normal[2];
        res.normalize3();
        return res;
    }
    Triangle sortX() const
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

    void multVertex(const Matrix4 &matr)
    {
        for(int i = 0; i < 3; i++) {
            m_vertex[i] = m_vertex[i] * matr;
        }
    }
    void multNormal(const Matrix4 &matr)
    {
        for(int i = 0; i < 3; i++) {
            m_normal[i] = m_normal[i] * matr;
            m_normal[i].normalize3();
        }
    }
    void mult(const Matrix4 &matr)
    {
        multNormal(matr);
        multVertex(matr);
    }

    Vector4 getVertex(unsigned index) const;

    Vector4 getNormal(unsigned index) const;
};

#endif // TRIANGLE_H
