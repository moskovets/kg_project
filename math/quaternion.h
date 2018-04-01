#ifndef QUATERNION_H
#define QUATERNION_H


class Quaternion
{
private:
    static const double m_eps;

    double m_a;
    double m_b;
    double m_c;
    double m_d;

public:
    //q = a + bi + cj + dk
    Quaternion(double a = 0, double b = 0, double c = 0, double d = 0);

    double length() const;

    //q 1 ⋅ q 2 = ( r 1 r 2 − a 1 a 2 − b 1 b 2 − c 1 c 2 ) + ( r 1 a 2 + a 1 r 2 + b 1 c 2 − c 1 b 2 ) ⋅ i +
    //( r 1 b 2 + b 1 r 2 + c 1 a 2 − a 1 c 2 ) ⋅ j + ( r 1 c 2 + c 1 r 2 + a 1 b 2 − b 1 a 2 ) ⋅ k

    Quaternion operator *(const Quaternion& q) const;

    //q 1 + q 2 = ( r 1 + r 2 ) + ( a 1 + a 2 ) ⋅ i + ( b 1 + b 2 ) ⋅ j + ( c 1 + c 2 ) ⋅ k
    Quaternion operator +(const Quaternion& q) const;

    //q 1 − q 2 = ( r 1 − r 2 ) + ( a 1 − a 2 ) ⋅ i + ( b 1 − b 2 ) ⋅ j + ( c 1 − c 2 ) ⋅ k
    Quaternion operator -(const Quaternion& q) const;

    Quaternion operator *(double value) const;

    Quaternion operator /(double value) const;

    bool operator ==(const Quaternion &q) const;

    bool operator !=(const Quaternion &q) const;

    //q 2 = ( r 2 − a 2 − b 2 − c 2 ) + 2 ra ⋅ i + 2 rb ⋅ j + 2 rc ⋅ k
    Quaternion squaring() const;

    Quaternion normalization() const;

    bool isZero() const;

    Quaternion inverse() const;

    Quaternion conjugation() const;
    double a() const;
    double b() const;
    double c() const;
    double d() const;

    void setA(double a);
    void setB(double b);
    void setC(double c);
    void setD(double d);
};


#endif // QUATERNION_H
