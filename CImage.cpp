#include <QPen>
#include "CImage.h"
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <math.h>
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

    QColor fonColor = image.pixelColor(QPoint(p.x, image.height() - p.y));
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

void CImage::algo(tScene &scene, tPaintParam &param)
{
    qDebug() << image.height() << image.width();

    //вывести сферу, перенести ее по z только (модель) на 4 единицы
    //Сферу лучше с большим кол-вом разбиений создавать - 50 - 150
    //Радиус 1


    std::shared_ptr<FrameBuffer> frame(new FrameBuffer(image.height(), image.width()));

    Drawer3D drawer(frame);
    Render render(frame);

    Mesh* mesh = new Mesh();
    Vector4 vertex[3] = { Vector4(-0.1, -0, 4),
                          Vector4(0.2, 0, 4),
                          Vector4(0, 0.2, 4)
                        };
    Vector4 normal[3] = { Vector4(1/sqrt(3), 1/sqrt(3), 1/sqrt(3)),
                          Vector4(1/sqrt(3), 1/sqrt(3), 1/sqrt(3)),
                          Vector4(1/sqrt(3), 1/sqrt(3), 1/sqrt(3))
                        };
    Triangle triangle(vertex, normal);
    mesh->addTriangle(triangle);
    mesh->addSphere(50, 50, 1);
    Model model(mesh, Color(0, 255), Vector4(0, 0, 4));
//    Model model(mesh, Color(0, 255), Vector4(0.2, 0.2, 0));
//    Model model(mesh, Color(0, 255));
    drawer.drawModel(model);
    drawer.swap();
    image = render.getImage().scaled(image.width(), image.height());
    printOnScene(scene);
    return;
/*    Dimension4 d4;
    QColor c;
    for(double i = 0; i < 400; i++) {
        if(i == 150) {
            int j = 5;
        }
        c = d4.getColorByLen(i + 380);
        for(int j = 0; j < 30; j++) {
            addPixel(tPoint(i/2, j + 100), c);
//            if(i > 200)
//                addPixel(tPoint(i - 200, j + 50), c);
//            else
//                addPixel(tPoint(i, j + 100), c);
        }
    }
    printOnScene(scene);
    return;
*/
    const double r = 3;

//    BaseFunction *f = new Function2(Quaternion(0.19, -0.5, 0, 0.1)); //, 0.2, 0.3, 0.4));
    BaseFunction *f = new Function1(Quaternion(-0.65, -0.5)); //, 0.2, 0.3, 0.4));
    JuliaSet set(f, r, 15);

    JuliaSetAlgo algoSet(&set);

/*
    double x = 0.15;
    double y = 0;

    double wmin = -r;
    double wmax = r;
    double dw = (wmax - wmin) / image.width();

    double w = wmin;
    double z;
    double zStart = -r;
    for (int wScreen = 0; wScreen < image.width(); wScreen++) {
        Quaternion startQ(x, y, zStart, w);
        Quaternion res;
        if (algoSet.findMinSolutionByC(startQ, r, res)) {
            z = res.c();
            addPixel(tPoint(wScreen, z * image.height() / 2 / r + image.height() / 2), param.color);
        }
        else {
            z = res.c();
            addPixel(tPoint(wScreen, z * image.height() / 2 / r + image.height() / 2), Qt::red);
        }
        qDebug() << w << "\t" << z;

        w += dw;
    }

*/
    double xmin = -2;
    double xmax = 2;

    double ymin = -1;
    double ymax = 1;

    double dx = (xmax - xmin) / image.width();
    double dy = (ymax - ymin) / image.height();

    double w = 0;
    double z;

    double zmin = -2;
    double zmax = 2;

    double x = xmin;
    for (int xScreen = 0; xScreen < image.width(); xScreen++) {
        double y = ymin;
        for (int yScreen = 0; yScreen < image.height(); yScreen++) {
            Quaternion startQ(x, y, zmin, w);
            Quaternion res;

            if (algoSet.findMinSolutionByC(startQ, zmax, res)) {
                z = res.c();
                addPixel(tPoint(xScreen, yScreen, (z - zmin) / (zmax - zmin)), param.color);
            }
            y += dy;
        }
        x += dx;
    }
    printOnScene(scene);
}

