#ifndef CIMAGE_H
#define CIMAGE_H

#include "my_scene.h"
#include "errors.h"
#include "point.h"
#include <vector>
#include "ringbuffer.h"
#include "graphic/setdrawer.h"
#include <memory>
using namespace std;

#include "juliafunctions.h"

#define BUFSIZE 10000

struct tParamFractal {
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    double zmin;
    double zmax;
    double r;
    int maxIter;

    double xAngle;
    double yAngle;
    double zAngle;

    Vector4 lightVector;
    Color   lightColor;
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
        void algoThread2(tScene &scene, tPaintParam &param, BaseFunction* func, tParamFractal &paramFract);

        static std::queue<Vector4> m_queue;
};

void m_oneMathFunc2(int heightINT, int widthINT, double** depth, BaseFunction *func, tParamFractal &paramFract, int thredNum, double** color);
void m_oneDrawerFunc2(std::shared_ptr<FrameBuffer> &fbuf, int heightINT, int widthINT, double** depth, tParamFractal &paramFract, int thredNum, double** color);
void m_oneThreadFunc(RingBuffer<Vector4, BUFSIZE> &buff, BaseFunction *func, tParamFractal &paramFract, int thredNum, double height, double width);
void m_oneDrawerFunc(RingBuffer<Vector4, BUFSIZE> &buff,  SetDrawer &setDrawer, int thredNum);



#endif // CIMAGE_H
