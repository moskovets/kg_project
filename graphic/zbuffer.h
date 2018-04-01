#ifndef ZBUFFER_H
#define ZBUFFER_H

#include "color.h"
#include <inttypes.h>

class ZBuffer
{
    static const double m_initDeep;
    uint32_t m_height;
    uint32_t m_width;
    Color*   m_dataBuff;
    Color**  m_buff;
    double*  m_dataDeep;
    double** m_deep;
    Color    m_initColor;
public:

    ZBuffer(uint32_t h, uint32_t w, const Color &c);

    ~ZBuffer();

    void addPixel(uint32_t x, uint32_t y, double deep, const Color &c = Color());

    void clear(const Color &c);

    void clear();

    Color getPixel(uint32_t x, uint32_t y) const;

    double getDeep(uint32_t x, uint32_t y) const;

    uint32_t height() const;
    uint32_t width() const;
    Color initColor() const;
    void setInitColor(const Color &initColor);
};

#endif // ZBUFFER_H
