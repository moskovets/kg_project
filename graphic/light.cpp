#include "light.h"

Color Light::lightColor() const
{
    return m_lightColor;
}

void Light::setLightColor(const Color &lightColor)
{
    m_lightColor = lightColor;
}
/*
 * https://stackoverflow.com/questions/726549/algorithm-for-additive-color-mixing-for-rgb-values
 * */

Color Light::calculateColor(const Color &modelColor, double inten) const
{
   Color col = m_lightColor;
    col.setR(col.r() * inten);
        col.setG(col.g() * inten);
        col.setB(col.b() * inten);
    return col;
    //2 накладывается на 1

    //Color col;
    double a1 = (double) modelColor.alpha() / 255;
    double r1 = (double) modelColor.r() / 255;
    double g1 = (double) modelColor.g() / 255;
    double b1 = (double) modelColor.b() / 255;

    double a2 = inten; //(double) (m_lightColor.alpha() / 255) * inten;
    double r2 = (double) m_lightColor.r() / 255;
    double g2 = (double) m_lightColor.g() / 255;
    double b2 = (double) m_lightColor.b() / 255;

    double colA = 1 - (1 - a2) * (1 - a1);
    if (colA < 0.0001)
        return col; //полностью прозрачен

    col.setR((r2 * a2 / colA + r1 * a1 * (1 - a2) / colA) * 255);
    col.setG((g2 * a2 / colA + g1 * a1 * (1 - a2) / colA) * 255);
    col.setB((b2 * a2 / colA + b1 * a1 * (1 - a2) / colA) * 255);
    col.setR(col.r());
    col.setG(col.g());
    col.setB(col.b());
//    col.setR(col.r() * inten);
//    col.setG(col.g() * inten);
//    col.setB(col.b() * inten);
//    col.setAlpha(255);
    return col;

}

Light::Light(const Vector4 &vector, const Color &color) :
    m_lightVector(vector), m_lightColor(color)
{}

void Light::rotate(double xAngle, double yAngle, double zAngle)
{
    m_lightVector = Matrix4::rotateVector(m_lightVector, xAngle, yAngle, zAngle);
}

Vector4 Light::lightVector() const
{
    return m_lightVector;
}

void Light::setLightVector(const Vector4 &lightVector)
{
    m_lightVector = lightVector;
}
