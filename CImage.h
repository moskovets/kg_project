#ifndef CIMAGE_H
#define CIMAGE_H

#include "my_scene.h"
#include "errors.h"
#include "point.h"
#include <vector>
using namespace std;

#include "juliafunctions.h"


struct tParamFractal {
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double zmin;
    double zmax;
    double r;
    int maxIter;
};

struct tPaintParam {
    int sizePixel;
    QColor color;
    QColor fon;
};


typedef unsigned long long int tick_t;

struct tAnaliz {
    tick_t time;
    int max_step;
};
#include <stack>
#include <queue>
#include "math/vector4.h"

class CImage {
    private:
        QImage image;
        QColor fon;
        int scale;
        void printOnScene(tScene &scene);
        void addPixel(const tPoint &p,
                      const QColor &color);

        void m_oneThread(BaseFunction* func, tParamFractal &paramFract, int thredNum);

public:
        CImage(); //todo
        CImage(int w, int h, int sizepixel); //todo
        CImage(tScene &scene, int sizepixel, const QColor &color);
        CImage(tScene &scene, tPaintParam &param);
        void changeFon(tScene &scene, const QColor &color);
        void changeScale(tScene &scene, int sizepixel);

        void algo(tScene &scene, tPaintParam &param, BaseFunction* func, tParamFractal &paramFract);
        void algoThread(tScene &scene, tPaintParam &param, BaseFunction* func, tParamFractal &paramFract);

        static std::queue<Vector4> m_queue;
};

#endif // CIMAGE_H
