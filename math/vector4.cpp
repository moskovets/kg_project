#include "vector4.h"


Vector4::Vector4(double arr[])
{
    for(int i = 0; i < 4; i++) {
        m_arr[i] = arr[i];
    }
}

Vector4::Vector4(double x, double y, double z, double w)
{
    m_arr[0] = x;
    m_arr[1] = y;
    m_arr[2] = z;
    m_arr[3] = w;
}

double Vector4::operator *(const Vector4 &v) const
{
    double res = 0;
    for(int i = 0; i < 3; i++) {
        res += m_arr[i] * v.m_arr[i];
    }
    return res;
}

Vector4 Vector4::operator +(const Vector4 &v) const
{
    double res_arr[4];
    for(int i = 0; i < 3; i++) {
        res_arr[i] = m_arr[i] + v.m_arr[i];
    }
    return Vector4(res_arr);
}
void Vector4::normalize3()
{
    double len = length3();
    if  (len < EPS_VECTOR)
        return;
    len = 1 / len;
    for(int i = 0; i < 3; i++) {
        m_arr[i] *= len / m_arr[3];
    }
    m_arr[3] = 1;
}

Vector4 Vector4::norm3() const
{
    Vector4 res = *this;
    res.normalize3();
    return res;
}

double Vector4::length3() const
{
    return sqrt(length_sqr3());
}

double Vector4::length_sqr3() const
{
    assert(m_arr[3] == 0);
    double res = 0;
    for(int i = 0; i < 3; i++) {
        res += m_arr[i] * m_arr[i];
    }
    return res / (m_arr[3] * m_arr[3]);
}

void Vector4::set(unsigned index, double value)
{
    m_arr[index < 4 ? index : 3] = value;
}

void Vector4::set(double arr[])
{
    for(int i = 0; i < 4; i++) {
        m_arr[i] = arr[i];
    }
}

double Vector4::get(unsigned index) const
{
    return m_arr[index < 4 ? index : 3];
}

double Vector4::x() const
{
    return m_arr[0];
}

double Vector4::y() const
{
    return m_arr[1];
}

double Vector4::z() const
{
    return m_arr[2];
}

double Vector4::w() const
{
    return m_arr[3];
}

void Vector4::setX(double x)
{
    m_arr[0] = x;
}

void Vector4::setY(double y)
{
    m_arr[1] = y;
}

void Vector4::setZ(double z)
{
    m_arr[2] = z;
}

void Vector4::setW(double w)
{
    m_arr[3] = w;
}
