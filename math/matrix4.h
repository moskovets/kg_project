#ifndef MATRIX4_H
#define MATRIX4_H

#include "vector4.h"

#include <math.h>

class Matrix4
{
    double m_matr[4][4];
public:
    Matrix4(double matr[][4]);
    Matrix4();

    Matrix4 operator *(const Matrix4& m) const;

    friend Vector4 operator *(const Vector4 &v, const Matrix4 &m);

    static Matrix4 createDiagMatrix(double d = 1);

    static Matrix4 createMoveMatrix(double dx = 0, double dy = 0, double dz = 0);

    static Matrix4 createMoveMatrix(const Vector4 &vector);

    static Matrix4 createRotateMatrix(double xAngle = 0, double yAngle = 0, double zAngle = 0);

    static Vector4 rotateVector(const Vector4 &v, double xAngle = 0, double yAngle = 0, double zAngle = 0);


    static Matrix4 createPerspectiveMatrix(double nearPlain = 0.1, double farPlain = 1000, double aspect = 1, double fovyRad = M_PI_2);


};


#endif // MATRIX4_H
