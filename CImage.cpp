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

void CImage::algo(tScene &scene, tPaintParam &param, BaseFunction *func, tParamFractal &paramFract)
{
/*    std::ofstream out;
    out.open("sphere.obj");
    {
        Mesh* mesh = new Mesh();
        mesh->addSphere(20, 20, 3);
        mesh->operator <<(out);
    }
    out.close();
    std::cout << "ok" << std::endl;
//    return;

*/

    qDebug() << image.height() << image.width();

    SetDrawer setDrawer(image.height(), image.width(), 20, 20, 0.5);
    setDrawer.setPixel(Vector4(0, 0, 1), Color(0, 255));
    setDrawer.setPixel(Vector4(2, 3, 20), Color(0, 255));
    setDrawer.setPixel(Vector4(1, 1, 15), Color(0, 255));
    setDrawer.setPixel(Vector4(-2, -3, 15), Color(0, 255));
    setDrawer.setPixel(Vector4(5, -10, 15), Color(0, 255));
    setDrawer.setPixel(Vector4(-2, 3, 15), Color(255));
    setDrawer.setPixel(Vector4(-2, 8, 15), Color(255, 255));

    image = setDrawer.getImage().scaled(image.width(), image.height());
    printOnScene(scene);
    //вывести сферу, перенести ее по z только (модель) на 4 единицы
    //Сферу лучше с большим кол-вом разбиений создавать - 50 - 150
    //Радиус 1

return;

    {
        std::shared_ptr<FrameBuffer> frame(new FrameBuffer(image.height(), image.width()));

        Drawer3D drawer(frame, DME_FLAT);
        Render render(frame);
        {
            Mesh* mesh = new Mesh();

            mesh->addSphere(20, 20, 3);
            Model model(mesh, Color(0, 255), Vector4(0, 0, 8));
            drawer.drawModel(model);

        }
        {
            Mesh* mesh = new Mesh();
            Vector4 vertex[3] = { Vector4(0, 0, 1),
                                  Vector4(0.1, 0, 1),
                                  Vector4(0, 1, 1)
                                };
            Vector4 normal[3] = { Vector4(0, 0, -1),
                                  Vector4(0, 0, -1),
                                  Vector4(0, 0, -1)
                                };
            Triangle triangle(vertex, normal);
            mesh->addTriangle(triangle);
            Model model(mesh, Color(255), Vector4(0, 0, 0));
            drawer.drawModel(model);

        }
        /* {
        Mesh* mesh = new Mesh();
        Vector4 vertex[3] = { Vector4(-0.05, -0.2, 3),
                              Vector4(0.05, -0.2, 3),
                              Vector4(0, 0.15, 1)
                            };
        Vector4 normal[3] = { Vector4(0, 0, -1),
                              Vector4(0, 0, -1),
                              Vector4(0, 0, -1)
                            };
        Triangle triangle(vertex, normal);
        mesh->addTriangle(triangle);
        Model model(mesh, Color(255), Vector4(0, 0, 5));
        //    Model model(mesh, Color(0, 255), Vector4(0.2, 0.2, 0));
        //    Model model(mesh, Color(0, 255));
        drawer.drawModel(model);
    }*/
        drawer.swap();
        image = render.getImage().scaled(image.width(), image.height());
        printOnScene(scene);
    }
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
    BaseFunction *f = func; //new Function1(Quaternion(-0.65, -0.5)); //, 0.2, 0.3, 0.4));


   const double r = 3;

//    BaseFunction *f = new Function2(Quaternion(0.19, -0.5, 0, 0.1)); //, 0.2, 0.3, 0.4));
    //BaseFunction *f = new Function1(Quaternion(-0.65, -0.5)); //, 0.2, 0.3, 0.4));
   // JuliaSet set(f, r, 15);

   JuliaSet set(f, paramFract.r, paramFract.maxIter);

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
    /*
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

*/

    double xmin = paramFract.xmin; //-2;
    double xmax = paramFract.xmax; //2;

    double ymin = paramFract.ymin; //-1;
    double ymax = paramFract.ymax; //1;

    double w = 0;
    double z;

    double zmin = paramFract.zmin; //-2;
    double zmax = paramFract.zmax; //2;

    double height = image.height();
    double width = image.width();

    double dx = (xmax - xmin) / image.width();
    double dy = (ymax - ymin) / image.height();

    for (double x = xmin; x < width; x += dx) {
        for (double y = ymin; y < height; y += dy) {
            Quaternion startQ(x, y, zmin, w);
            Quaternion res;
            if (algoSet.findMinSolutionByC(startQ, zmax, res)) {
                z = res.c();

                double xDrawer = round((x/width + 1) * (width / 2.0));
                double yDrawer = round((y/height + 1) * (height / 2.0));
                double zDrawer = z;

                Vector4 pos(xDrawer, yDrawer, zDrawer, z);
                setDrawer.setPixel(pos, Color(param.color.red(), param.color.green(), param.color.blue(), param.color.alpha()));
            }
        }
    }


/*    {
        double x = xmin;
        double dx = (xmax - xmin) / image.width();
        double dy = (ymax - ymin) / image.height();

        for (int xScreen = 0; xScreen < image.width(); xScreen++) {
            double y = ymin;
            for (int yScreen = 0; yScreen < image.height(); yScreen++) {
                Quaternion startQ(x, y, zmin, w);
                Quaternion res;

                if (algoSet.findMinSolutionByC(startQ, zmax, res)) {
                    z = res.c();
                    addPixel(tPoint(xScreen, yScreen, (z - zmin) / (zmax - zmin)), param.color);

                    double xDrawer = round((x/width + 1) * (height / 2.0));;
                    double yDrawer = round((y/width + 1) * (height / 2.0));
                    double zDrawer = z;

                    Vector4 pos(xDrawer, yDrawer, zDrawer, z);
                    setDrawer.setPixel(pos, Color(param.color.red(), param.color.green(), param.color.blue(), param.color.alpha()));
                }
                y += dy;
            }
            x += dx;
        }
    }*/
    image = setDrawer.getImage().scaled(image.width(), image.height());
    printOnScene(scene);
}

