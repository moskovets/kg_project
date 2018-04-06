#include "matrix4.h"
#include "quaternion.h"

Matrix4::Matrix4(double matr[][4])
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_matr[i][j] = matr[i][j];
}

Matrix4::Matrix4()
{
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            m_matr[i][j] = 0;
}

Matrix4 Matrix4::operator *(const Matrix4 &m) const
{
    Matrix4 res;
    double tmp;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            tmp = 0;
            for(int k = 0; k < 4; k++) {
                tmp += m_matr[i][k] * m.m_matr[k][j];
            }
            res.m_matr[i][j] = tmp;
        }
    }
    return res;
}

Vector4 operator *(const Vector4 &v, const Matrix4 &m)
{
    Vector4 res;
    double tmp;
    for(int i = 0; i < 4; i++) {
        tmp = 0;
        for(int j = 0; j < 4; j++) {
            tmp += v.get(j) * m.m_matr[j][i];
        }
        res.set(i, tmp);
    }
    return res;
}

Matrix4 Matrix4::createDiagMatrix(double d)
{
    double matr[4][4] = {
        { d, 0, 0, 0 },
        { 0, d, 0, 0 },
        { 0, 0, d, 0 },
        { 0, 0, 0, d }
    };
    return Matrix4(matr);
}

Matrix4 Matrix4::createMoveMatrix(double dx, double dy, double dz)
{
    double matr[4][4] = {
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { dx, dy, dz, 1 }
    };
    return Matrix4(matr);
}

Matrix4 Matrix4::createMoveMatrix(const Vector4 &vector)
{
    return createMoveMatrix(vector.x(), vector.y(), vector.z());
}

Matrix4 Matrix4::createRotateMatrix(double xAngle, double yAngle, double zAngle)
{
    Quaternion qx = Quaternion::createRotateQ(Vector4(1, 0, 0), xAngle);
    Quaternion qy = Quaternion::createRotateQ(Vector4(0, 1, 0), yAngle);
    Quaternion qz = Quaternion::createRotateQ(Vector4(0, 0, 1), zAngle);
    Quaternion q = (qz * qy) * qx;

    double matr[4][4] = {
        { 1 - 2*q.c()*q.c() - 2*q.d()*q.d(), 2*q.b()*q.c() - 2*q.d()*q.a(),     2*q.b()*q.d() + 2*q.c()*q.a(), 0 },
        { 2*q.b()*q.c() + 2*q.d()*q.a(),     1 - 2*q.b()*q.b() - 2*q.d()*q.d(), 2*q.c()*q.d() - 2*q.b()*q.a(), 0 },
        { 2*q.b()*q.d() - 2*q.c()*q.a(),     2*q.c()*q.d() + 2*q.b()*q.a(),     1 - 2*q.b()*q.b() - 2*q.c()*q.c(),  1},
        { 0, 0, 0, 1 }
    };
    return Matrix4(matr);
}

Vector4 Matrix4::rotateVector(const Vector4 &v, double xAngle, double yAngle, double zAngle)
{
    Quaternion qx = Quaternion::createRotateQ(Vector4(1, 0, 0), xAngle);
    Quaternion qy = Quaternion::createRotateQ(Vector4(0, 1, 0), yAngle);
    Quaternion qz = Quaternion::createRotateQ(Vector4(0, 0, 1), zAngle);
    Quaternion q = (qz * qy) * qx;
    Quaternion u = Quaternion(0, v.x(), v.y(), v.z());
    Quaternion res = (q * u) * q.inverse();
    return Vector4(res.b(), res.c(), res.d());
}

Matrix4 Matrix4::createPerspectiveMatrix(double nearPlain, double farPlain, double aspect, double fovyRad)
{
    double ctg = 1 / tan(fovyRad / 2);
    double matr[4][4] = {
        { ctg/aspect, 0, 0, 0 },
        { 0, ctg, 0, 0 },
        { 0, 0, (farPlain + nearPlain) / (farPlain - nearPlain),  1},
        { 0, 0, (-2 * farPlain * nearPlain) / (farPlain - nearPlain), 0 }
    };
    return Matrix4(matr);
}
