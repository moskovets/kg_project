#ifndef COORDINATES_H
#define COORDINATES_H


class Coordinates
{
    double m_x;
    double m_y;
    double m_z;
    double m_w;

public:
    Coordinates(double x, double y, double z = 0, double w = 1) :
        m_x(x), m_y(y), m_z(z), m_w(w)
    {}

    double x() const;
    void setX(double x);
    double y() const;
    void setY(double y);
    double z() const;
    void setZ(double z);
    double w() const;
    void setW(double w);
};

#endif // COORDINATES_H
