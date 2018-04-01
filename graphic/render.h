#ifndef RENDER_H
#define RENDER_H

#include <QImage>
#include <memory>

#include "framebuffer.h"

class Render
{
    std::shared_ptr <FrameBuffer> m_frame;
public:
    Render(std::shared_ptr <FrameBuffer> &frame) : m_frame(frame)
    {}
    QImage getImage()
    {
        uint32_t w = m_frame->getPreviousBuffer()->width();
        uint32_t h = m_frame->getPreviousBuffer()->height();
        QImage image = QImage(w, h, QImage::Format_ARGB32);

        for (uint32_t x = 0; x < w; x++) {
            for (uint32_t y = 0; y < h; y++) {
                Color c = m_frame->getPreviousBuffer()->getPixel(x, y);
                QColor color(c.r(), c.g(), c.b());
                image.setPixelColor(QPoint(x, h - y - 1), color);
            }
        }

        return image;
    }
};

#endif // RENDER_H
