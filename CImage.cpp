#include <QPen>
#include "CImage.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <math.h>
#include "graphic/dimension4.h"
#define EPS 0.1
#define SIGN(x) ((int) (x > 0) - (x < 0))

tick_t tick(void)
{
    tick_t d;
    __asm__ __volatile__
    (
        "rdtsc"
        : "=A" (d)
    );
    return d;
}

void CImage::printOnScene(tScene &scene)
{
    QImage image_tmp = image.scaled(QSize(image.width() * scale,
                       image.height() * scale));
    QPixmap pixmap;
    pixmap.convertFromImage(image_tmp);
    scene.scene->clear();
    scene.scene->addPixmap(pixmap);
}

void CImage::addPixel(const tPoint &p, const QColor &color)
{
    double i = p.intensity;

    QColor fonColor = image.pixelColor(QPoint(p.x, image.height() - p.y - 1));
    QColor res;
    res.setGreen(color.green() * i + fonColor.green() * (1 - i));
    res.setRed(color.red() * i + fonColor.red() * (1 - i));
    res.setBlue(color.blue() * i + fonColor.blue() * (1 - i));

    image.setPixelColor(QPoint(p.x, image.height() - p.y - 1), res);

}



CImage::CImage() {}

CImage::CImage(tScene &scene, int sizepixel, const QColor &color)
{
    sizepixel = 1; //SCALESIZEPIXEL
    image = QImage((int)scene.scene->width() / sizepixel, (int)scene.scene->height() / sizepixel, QImage::Format_ARGB32);
    image.fill(color);
    fon = color;
    scale = sizepixel;
    printOnScene(scene);
}
CImage::CImage(tScene &scene, tPaintParam &param)
{
    param.sizePixel = 1;
    fon = param.fon;
    scale = param.sizePixel;
    image = QImage((int)scene.scene->width() / scale, (int)scene.scene->height() / scale, QImage::Format_ARGB32);
    image.fill(fon);
    printOnScene(scene);
}

void CImage::changeFon(tScene &scene, const QColor &color)
{
    image.fill(color);
    fon = color;
    printOnScene(scene);
}

void CImage::changeScale(tScene &scene, int sizepixel)
{
    image = QImage((int)scene.scene->width() / sizepixel, (int)scene.scene->height() / sizepixel, QImage::Format_RGB888);
    image.fill(fon);
    scale = sizepixel;
    printOnScene(scene);
}

#include "math/juliasetalgo.h"
#include "math/quaternion.h"
#include "juliafunctions.h"

#include "graphic/drawer3d.h"
#include "graphic/render.h"
#include "graphic/setdrawer.h"
#include <fstream>
#include <QTime>

void CImage::algo(tScene &scene, tPaintParam &param, BaseFunction *func, tParamFractal &paramFract)
{
    JuliaSet set(func, paramFract.r, paramFract.maxIter);
    JuliaSetAlgo algoSet(&set);

    double xmin = paramFract.xmin; //-2;
    double xmax = paramFract.xmax; //2;

    double ymin = paramFract.ymin; //-1;
    double ymax = paramFract.ymax; //1;

    double zmin = paramFract.zmin; //-2;
    double zmax = paramFract.zmax; //2;

    double height = image.height() / 2;
    int heightINT = image.height() / 2;

    double width = image.width() / 2;
    int widthINT = image.width() / 2;


    std::shared_ptr<FrameBuffer> fbuf(new FrameBuffer(heightINT, widthINT));

    Quaternion res;
    double depth[heightINT + 2][widthINT + 2];

    for (int y = 0; y < heightINT + 2; ++y)
    {
        //double curY = (((2 * double(y) / (height + 2) - 1.0) + 1) * (ymax - ymin) / 2) + ymin;
        double curY = ((double(y) / (height + 2)) * (ymax - ymin)) + ymin;
        for (int x = 0; x < widthINT + 2; ++x)
        {
            //double curX = (((2 * double(x) / (width + 2) - 1.0) + 1) * (xmax - xmin) / 2) + xmin;
            double curX = ((double(x) / (width + 2)) * (xmax - xmin)) + xmin;
            Quaternion startQ(curX, curY, zmin, 0);
            if (algoSet.findMinSolutionByC(startQ, zmax, res))
                depth[y][x] = res.c() - zmin;
            else
                depth[y][x] = 1e10; // TODO big
        }
    }

    Vector4 light(1/sqrt(3), 1/sqrt(3), 1/sqrt(3));
    //light = -light;

    for (int y = 1; y < heightINT + 1; ++y)
    {
        for (int x = 1; x < widthINT + 1; ++x)
        {
            if (depth[y][x] >= 1e10 - 5)
                continue;
            Vector4 norm(
                            (depth[y][x + 1] - depth[y][x - 1]) * width / (xmax - xmin),
                            (depth[y + 1][x] - depth[y - 1][x]) * height / (ymax - ymin),
                            2
                        );
            norm.normalize3();

            double I = light * norm;
            //if (I < 0)
            //    continue;
            if (I < 0.2)
                I = 0.2;
            Color c(255 * I);
            fbuf->getBuffer()->addPixel(x, heightINT - y - 1, depth[y][x], c);
        }
    }

    Render render(fbuf);
    fbuf->swap();
    image = render.getImage().scaled(image.width(), image.height());
    printOnScene(scene);
}

#define THREAD_MATH_NUMBER   3
#define THREAD_DRAWER_NUMBER 1
#include <thread>
#include <chrono>
#include "ringbuffer.h"
#define BUFSIZE 10000

//deprecated
void CImage::m_oneThread(BaseFunction *func, tParamFractal &paramFract, int thredNum)
{
    BaseFunction *f = func; //new Function1(Quaternion(-0.65, -0.5)); //, 0.2, 0.3, 0.4));
    JuliaSet set(f, paramFract.r, paramFract.maxIter);
    JuliaSetAlgo algoSet(&set);

    double xmin = paramFract.xmin; //-2;
    double xmax = paramFract.xmax; //2;

    double ymin = paramFract.ymin; //-1;
    double ymax = paramFract.ymax; //1;

    double w = 0;
    double z;

    double zmin = paramFract.zmin; //-2;
    double zmax = paramFract.zmax; //2;

    double height = image.height() / 4;
    double width = image.width() / 4;

    double dx = (xmax - xmin) / width;
    double dy = (ymax - ymin) / height;

    int currPoint = 0;
    for (double x = xmin; x < xmax; x += dx) {
        for (double y = ymin; y < ymax; y += dy) {
            if (currPoint % THREAD_MATH_NUMBER == thredNum) {
                Quaternion startQ(x, y, zmin, w);
                Quaternion res;
                if (algoSet.findMinSolutionByC(startQ, zmax, res)) {
                    z = res.c();

                    double xDrawer = 2 * (x - xmin) / (xmax - xmin) - 1;
                    double yDrawer = 2 * (y - ymin) / (ymax - ymin) - 1;
                    double zDrawer = z - zmin + 0.2;

                    Vector4 pos(xDrawer, yDrawer, zDrawer);
                    //queue.push(pos);
                }
            }
            currPoint++;
        }
    }
}


void m_oneThreadFunc(RingBuffer<Vector4, BUFSIZE> &buff, BaseFunction *func, tParamFractal &paramFract, int thredNum, double height, double width)
{
    QTime timeStart = QTime::currentTime();

    BaseFunction *f = func->clone(); //new Function1(Quaternion(-0.65, -0.5)); //, 0.2, 0.3, 0.4));
    JuliaSet set(f, paramFract.r, paramFract.maxIter);
    JuliaSetAlgo algoSet(&set);

    double xmin = paramFract.xmin; //-2;
    double xmax = paramFract.xmax; //2;

    double ymin = paramFract.ymin; //-1;
    double ymax = paramFract.ymax; //1;

    double w = 0;
    double z;

    double zmin = paramFract.zmin; //-2;
    double zmax = paramFract.zmax; //2;

    height /= 4;
    width  /= 4;
    double dx = (xmax - xmin) / width;
    double dy = (ymax - ymin) / height;

    int currPoint = 0;
    for (double x = xmin; x < xmax; x += dx) {
        if (currPoint % THREAD_MATH_NUMBER == thredNum) {
            for (double y = ymin; y < ymax; y += dy) {
                Quaternion startQ(x, y, zmin, w);
                Quaternion res;
                if (algoSet.findMinSolutionByC(startQ, zmax, res)) {
                    z = res.c();

                    double xDrawer = 2 * (x - xmin) / (xmax - xmin) - 1;
                    double yDrawer = 2 * (y - ymin) / (ymax - ymin) - 1;
                    double zDrawer = z - zmin + 0.2;

                    //Vector4 pos(xDrawer, yDrawer, zDrawer);
                    while (buff.isFull()) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(40));
                        std::cout << "thread " << thredNum << "sleep\n";
                    }
                    buff.push(Vector4(xDrawer, yDrawer, zDrawer));
                }
            }
        }
        currPoint++;
    }

    QTime timeEnd = QTime::currentTime();

    std::cout << "поток математики " << thredNum << " " << timeStart.msecsTo(timeEnd) << std::endl;

}
/* без потоков
 * общее время 10266
время до рендеринга 10256

c потоками
общее время 8045
время до рендеринга 8034

*/

void m_oneDrawerFunc(RingBuffer<Vector4, BUFSIZE> &buff,  SetDrawer &setDrawer, int thredNum)
{
    int flag = 0;
    int popCount = 0;
    while(flag < 10) {
        if (buff.isEmpty()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            flag++;
        } else {
            flag = 0;
            Vector4 pos;
            buff.pop(pos);
            //popCount++;
            //if(popCount % 100 == 0)
            //    std::cout << "drawing " << popCount << " points\n";
            setDrawer.setPixel(pos, Color(255));
        }
    }
}

void CImage::algoThread(tScene &scene, tPaintParam &param, BaseFunction *func, tParamFractal &paramFract)
{
    RingBuffer<Vector4, BUFSIZE> buffer;

    double height = image.height() / 4;
    double width = image.width() / 4;

    SetDrawer setDrawer(height, width, 20, 20, 0.01);

    QTime timeStart = QTime::currentTime();


    std::thread threadDrawer[THREAD_DRAWER_NUMBER];
    for(int i = 0; i < THREAD_DRAWER_NUMBER; i++) {
        threadDrawer[i] = std::thread(&m_oneDrawerFunc, std::ref(buffer), std::ref(setDrawer), i);
    }

    std::thread threadMath[THREAD_MATH_NUMBER];
    for(int i = 0; i < THREAD_MATH_NUMBER; i++) {
        threadMath[i] = std::thread(&m_oneThreadFunc, std::ref(buffer), func, std::ref(paramFract), i, image.height(), image.width());
    }

    for(int i = 0; i < THREAD_MATH_NUMBER; i++) {
        threadMath[i].join();
    }

    for(int i = 0; i < THREAD_DRAWER_NUMBER; i++) {
        threadDrawer[i].join();
    }

    //TODO threads call
    QTime timePreRender = QTime::currentTime();

    image = setDrawer.getImage().scaled(image.width(), image.height());
    QTime timeEnd = QTime::currentTime();

    std::cout << "общее время " << timeStart.msecsTo(timeEnd) << std::endl;
    std::cout << "время до рендеринга " << timeStart.msecsTo(timePreRender) << std::endl;

    printOnScene(scene);
}

