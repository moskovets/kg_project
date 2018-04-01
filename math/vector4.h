#ifndef VECTOR4_H
#define VECTOR4_H

#include <math.h>
#include <assert.h>

#define EPS_VECTOR 0.001

class Vector4
{
    double m_arr[4];
public:
    Vector4(double arr[]);

    Vector4(double x = 0, double y = 0, double z = 0, double w = 1);

    Vector4 operator -() const
    {
        return Vector4(-m_arr[0], -m_arr[1], -m_arr[2], -m_arr[3]);
    }

    double operator *(const Vector4 &v) const;

    Vector4 operator +(const Vector4 &v) const;

    void normalize3();

    Vector4 norm3() const;

    double length3() const;

    double length_sqr3() const;

    void set(unsigned index, double value);
    void set(double arr[]);
    double get(unsigned index) const;

    double x() const;
    double y() const;
    double z() const;
    double w() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setW(double w);


};

#endif // VECTOR4_H
