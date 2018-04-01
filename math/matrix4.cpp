#include "matrix4.h"

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
            tmp += v.get(j) * m.m_matr[i][j];
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
Matrix4 Matrix4::createPerspectiveMatrix(double nearPlain, double farPlain, double aspect, double fovyRad)
{
    double ctg = 1 / tan(fovyRad / 2);
    double matr[4][4] = {
        { ctg/aspect, 0, 0, 0 },
        { 0, ctg, 0, 0 },
        { 0, 0, (farPlain + nearPlain) / (farPlain - nearPlain), 1 },
        { 0, 0, 0, (-2 * farPlain * nearPlain) / (farPlain - nearPlain) }
    };
    return Matrix4(matr);
}
