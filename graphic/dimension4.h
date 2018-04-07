#ifndef DIMENSION4_H
#define DIMENSION4_H

#include <math.h>
#include <QColor>
#include "color.h"

class Dimension4
{
    const double m_gamma = 0.8;
    const double m_maxInten = 255;

    const double m_lenStart = 380;
    const double m_lenEnd   = 780;

private:
    Color m_getColorByLen(double len);
    /*
 * http://qaru.site/questions/59561/convert-light-frequency-to-rgb
 *
 * */
    QColor m_getQColorByLen(double len);


public:
    Dimension4();

    //x из интервала [0, 1]
    QColor getQColorForNormCoord(double x);

    //x из интервала [0, 1]
    Color getColorForNormCoord(double x);

};


#endif // DIMENSION4_H
