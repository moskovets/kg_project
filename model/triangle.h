#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../math/matrix4.h"
#include <iostream>

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
    Vector4 getAverageNormal() const;
    Triangle sortX() const;

    void multVertex(const Matrix4 &matr);
    void multNormal(const Matrix4 &matr);
    void mult(const Matrix4 &matr);

    Vector4 getVertex(unsigned index) const;

    Vector4 getNormal(unsigned index) const;

    void toScreenCoord(double w, double h);

};

#endif // TRIANGLE_H
