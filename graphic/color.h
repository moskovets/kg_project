#ifndef COLOR_H
#define COLOR_H

typedef unsigned char uchar;

class Color
{
    uchar m_r, m_g, m_b;
    uchar m_alpha;
public:
    Color(uchar r = 0, uchar g = 0, uchar b = 0, uchar alpha = 255);

    Color operator +(const Color& c) const;

    uchar r() const;
    uchar g() const;
    uchar b() const;
    uchar alpha() const;

    void setR(const uchar &r);
    void setG(const uchar &g);
    void setB(const uchar &b);
    void setAlpha(const uchar &alpha);
};

#endif // COLOR_H
