#include "quaternion.h"
#include <math.h>

const double Quaternion::m_eps = 0.001;

double Quaternion::a() const
{
    return m_a;
}

void Quaternion::setA(double a)
{
    m_a = a;
}

double Quaternion::b() const
{
    return m_b;
}

void Quaternion::setB(double b)
{
    m_b = b;
}

double Quaternion::c() const
{
    return m_c;
}

void Quaternion::setC(double c)
{
    m_c = c;
}

double Quaternion::d() const
{
    return m_d;
}

void Quaternion::setD(double d)
{
    m_d = d;
}

Quaternion::Quaternion(double a, double b, double c, double d)
    : m_a(a), m_b(b), m_c(c), m_d(d)
{

}

double Quaternion::length() const
{
    return sqrt(m_a * m_a + m_b * m_b + m_c * m_c + m_d * m_d);
}

Quaternion Quaternion::operator *(const Quaternion &q) const
{
    return Quaternion(m_a * q.m_a - m_b * q.m_b - m_c * q.m_c - m_d * q.m_d,
                      m_a * q.m_b + m_b * q.m_a + m_c * q.m_d - m_d * q.m_c,
                      m_a * q.m_c + m_c * q.m_a + m_d * q.m_b - m_b * q.m_d,
                      m_a * q.m_d + m_d * q.m_a + m_b * q.m_c - m_c * q.m_b);
}

Quaternion Quaternion::operator +(const Quaternion &q) const
{
    return Quaternion(m_a + q.m_a,
                      m_b + q.m_b,
                      m_c + q.m_c,
                      m_d + q.m_d);
}

Quaternion Quaternion::operator -(const Quaternion &q) const
{
    return Quaternion(m_a - q.m_a,
                      m_b - q.m_b,
                      m_c - q.m_c,
                      m_d - q.m_d);
}

Quaternion Quaternion::operator *(double value) const
{
    return Quaternion(m_a * value,
                      m_b * value,
                      m_c * value,
                      m_d * value);
}

Quaternion Quaternion::operator /(double value) const
{
    return Quaternion(m_a / value,
                      m_b / value,
                      m_c / value,
                      m_d / value);
}

bool Quaternion::operator ==(const Quaternion &q) const
{
    return m_a == q.m_a && m_b == q.m_b && m_c == q.m_c && m_d == q.m_d;
}

bool Quaternion::operator !=(const Quaternion &q) const
{
    return !this->operator ==(q);
}

Quaternion Quaternion::squaring() const
{
    return Quaternion(m_a * m_a - m_b * m_b - m_c * m_c - m_d * m_d,
                      2 * m_a * m_b,
                      2 * m_a * m_c,
                      2 * m_a * m_d);
}

Quaternion Quaternion::normalization() const
{
    return this->operator /(this->length());
}

bool Quaternion::isZero() const
{
    return this->length() < m_eps;
}

Quaternion Quaternion::inverse() const
{
    double len = this->length();
    return this->conjugation() / (len * len);
}

Quaternion Quaternion::conjugation() const
{
    return Quaternion(m_a, -m_b, -m_c, -m_d);
}
