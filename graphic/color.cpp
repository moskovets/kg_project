#include "color.h"


uchar Color::g() const
{
    return m_g;
}

void Color::setG(const uchar &g)
{
    m_g = g;
}

uchar Color::b() const
{
    return m_b;
}

void Color::setB(const uchar &b)
{
    m_b = b;
}

uchar Color::alpha() const
{
    return m_alpha;
}

void Color::setAlpha(const uchar &alpha)
{
    m_alpha = alpha;
}

Color::Color(uchar r, uchar g, uchar b, uchar alpha) :
    m_r(r), m_g(g), m_b(b), m_alpha(alpha)
{}

Color Color::operator +(const Color &c) const
{
    Color res;
    double inten = ((double) c.alpha()) / 255;
    res.setR(c.r() * inten + m_r * (1 - inten));
    res.setG(c.g() * inten + m_g * (1 - inten));
    res.setB(c.b() * inten + m_b * (1 - inten));

    return res;
}

uchar Color::r() const
{
    return m_r;
}

void Color::setR(const uchar &r)
{
    m_r = r;
}
