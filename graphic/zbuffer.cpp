#include "zbuffer.h"
#include <float.h>

const double ZBuffer::m_initDeep = DBL_MAX;

uint32_t ZBuffer::width() const
{
    return m_width;
}

Color ZBuffer::initColor() const
{
    return m_initColor;
}

void ZBuffer::setInitColor(const Color &initColor)
{
    m_initColor = initColor;
}

ZBuffer::ZBuffer(uint32_t h, uint32_t w, const Color &c) :
    m_height(h), m_width(w), m_initColor(c)
{
    m_dataBuff = new Color[h * w];
    m_buff = new Color*[h];
    m_dataDeep = new double[h * w];
    m_deep = new double*[h];
    for (uint32_t i = 0; i < h; i++) {
        m_buff[i] = &m_dataBuff[i * w];
        m_deep[i] = &m_dataDeep[i * w];
        for(uint32_t j = 0; j < w; j++) {
            m_buff[i][j] = m_initColor;
            m_deep[i][j] = m_initDeep;
        }
    }
}

ZBuffer::~ZBuffer()
{
    delete[] m_dataBuff;
    delete[] m_dataDeep;
    delete[] m_buff;
    delete[] m_deep;

    m_dataBuff = nullptr;
    m_dataDeep = nullptr;
    m_deep = nullptr;
    m_buff = nullptr;
}

void ZBuffer::addPixel(uint32_t x, uint32_t y, double deep, const Color &c)
{
    if (x < m_width && y < m_height) {
        if (deep < m_deep[y][x] && deep > 0) { // TODO deep > 0
            m_buff[y][x] = c;
            m_deep[y][x] = deep;
        }
    }
}

void ZBuffer::clear(const Color &c)
{
    m_initColor = c;
    clear();
}

void ZBuffer::clear()
{
    for (uint32_t i = 0; i < m_height; i++) {
        for(uint32_t j = 0; j < m_width; j++) {
            m_buff[i][j] = m_initColor;
            m_deep[i][j] = m_initDeep;
        }
    }
}

Color ZBuffer::getPixel(uint32_t x, uint32_t y) const
{
    if (x < m_width && y < m_height)
        return m_buff[y][x];
    return m_initColor;
}

double ZBuffer::getDeep(uint32_t x, uint32_t y) const
{
    if (x < m_width && y < m_height)
        return m_deep[y][x];
    return m_initDeep;
}

uint32_t ZBuffer::height() const
{
    return m_height;
}

