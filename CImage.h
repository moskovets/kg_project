#ifndef CIMAGE_H
#define CIMAGE_H

#include "my_scene.h"
#include "errors.h"
#include "point.h"
#include <vector>
using namespace std;

struct tLine {
    vector <tPoint> line;
    int sizePixel;
    QColor color;
};

enum ALGORITHM {
    STANDART = 1,
    BRESENHAM, // алгоритм Брезенхема
    MID_POINT, // алгоритм средней точки
    CANON_EQ,  // алгоритм построения по каноническому уравнению
    PARAM_EQ,  // алгоритм построения по параметрическому уравнению

    CHANGE_FON,
    CHANGE_SCALE,
    CLEAR_SCENE
};

struct tParamFractal {
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double zmin;
    double zmax;
    double r;
    double maxIter;
};

struct tPaintParam {
    int sizePixel;
    QColor color;
    QColor fon;
};

struct tDataEllipse {
    QPoint center;
    int rx;
    int ry;
    tPaintParam param;
};

struct tDataCircle {
    QPoint center;
    int radius;
    tPaintParam param;
};

typedef unsigned long long int tick_t;

struct tAnaliz {
    tick_t time;
    int max_step;
};

class CImage {
    private:
        QImage image;
        QColor fon;
        int scale;
        void printOnScene(tScene &scene);
        void addPixel(const tPoint &p,
                      const QColor &color);
    public:
        CImage(); //todo
        CImage(int w, int h, int sizepixel); //todo
        CImage(tScene &scene, int sizepixel, const QColor &color);
        CImage(tScene &scene, tPaintParam &param);
        void changeFon(tScene &scene, const QColor &color);
        void changeScale(tScene &scene, int sizepixel);

        void algo(tScene &scene, tPaintParam &param);

};

#include <math.h>
class Dimension4
{
    const double gamma = 0.8;
    const double maxInten = 255;

    double left;
    double right;
    double step;
public:
    Dimension4() {}
    Dimension4(double left, double right, double step)
    {

    }

/*
 * http://qaru.site/questions/59561/convert-light-frequency-to-rgb
 *
 * */
    QColor getColorByLen(double len)
    {
        double factor;
        double r,g,b;

        if((len >= 380) && (len<440)){
            r = -(len - 440) / (440 - 380);
            g = 0.0;
            b = 1.0;
        }else if((len >= 440) && (len<490)){
            r = 0.0;
            g = (len - 440) / (490 - 440);
            b = 1.0;
        }else if((len >= 490) && (len<510)){
            r = 0.0;
            g = 1.0;
            b = -(len - 510) / (510 - 490);
        }else if((len >= 510) && (len<580)){
            r = (len - 510) / (580 - 510);
            g = 1.0;
            b = 0.0;
        }else if((len >= 580) && (len<645)){
            r = 1.0;
            g = -(len - 645) / (645 - 580);
            b = 0.0;
        }else if((len >= 645) && (len<781)){
            r = 1.0;
            g = 0.0;
            b = 0.0;
        }else{
            r = 0.0;
            g = 0.0;
            b = 0.0;
        };

        // Let the intensity fall off near the vision limits

        if((len >= 380) && (len<420)){
            factor = 0.3 + 0.7*(len - 380) / (420 - 380);
        }else if((len >= 420) && (len<701)){
            factor = 1.0;
        }else if((len >= 701) && (len<781)){
            factor = 0.3 + 0.7*(780 - len) / (780 - 700);
        }else{
            factor = 0.0;
        };



        // Don't want 0^x = 1 for x <> 0
        r = r<=0.0 ? 0 : round(maxInten * pow(r * factor, gamma));
        g = g<=0.0 ? 0 : round(maxInten * pow(g * factor, gamma));
        b = b<=0.0 ? 0 : round(maxInten * pow(b * factor, gamma));

        return QColor(r, g, b);






//return;
        double x = 0.398 * exp(
                    -1250 * pow(log((len + 570.1) / 1014), 2))
                + 1.132 * exp(
                    -234 * pow(log((1338 - len) / 743.5), 2));
        double y = 1.011 * exp(
                    -0.5 * pow((len - 556.1) / 46.14, 2));
        double z = 2.060 * exp(
                    -32 * pow(log((len - 265.8) / 180.4), 2));


        //XYZ->RGB
        //double r = x *  3.2406 + y * -1.5372 + z * -0.4986;
        //double g = x * -0.9689 + y *  1.8758 + z *  0.0415;
        //double b = x * 0.0557 + y * -0.2040 + z * 1.0570;
/*
        double r =  3.2406255 * x + -1.537208  * y + -0.4986286 * z;
        double g = -0.9689307 * x +  1.8757561 * y +  0.0415175 * z;
        double b =  0.0557101 * x + -0.2040211 * y +  1.0569959 * z;

        if (r > 0.0031308)
            r = 1.055 * pow(r, 1 / 2.4) - 0.055;
        else
            r = 12.92 * r;

        if (g > 0.0031308)
            g = 1.055 * pow(g, 1 / 2.4) - 0.055;
        else
            g = 12.92 * g;

        if (b > 0.0031308)
            b = 1.055 * pow(b, 1 / 2.4) - 0.055;
        else
            b = 12.92 * b;
        r *= 255;
        g *= 255;
        b *= 255;
*/
/*        x /= 100;
        y /= 100;
        z /= 100;
        double r = x * 3.2404542 + y * -1.5371385 + z * -0.4985314;
        double g = x * -0.9692660 + y * 1.8760108 + z * 0.0415560;
        double b = x * 0.0556434 + y * -0.2040259 + z * 1.0572252;

        r = ((r > 0.0031308) ? (1.055*pow(r, 1 / 2.4) - 0.055) : (12.92*r)) * 255.0;
        g = ((g > 0.0031308) ? (1.055*pow(g, 1 / 2.4) - 0.055) : (12.92*g)) * 255.0;
        b = ((b > 0.0031308) ? (1.055*pow(b, 1 / 2.4) - 0.055) : (12.92*b)) * 255.0;

        r = (r < 0) ? 0 : r;
        g = (g < 0) ? 0 : g;
        b = (b < 0) ? 0 : b;

        r *= 8;
        g *= 8;
        b *= 8;


        r = (r > 255) ? 255 : r;
        g = (g > 255) ? 255 : g;
        b = (b > 255) ? 255 : b;

        return QColor(r, g, b);*/
    }

};


#endif // CIMAGE_H
