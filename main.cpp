#include "ui/mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDebug>

#include "juliafunctions.h"
#include "math/juliaset.h"
#include <iostream>
int main(int argc, char *argv[])
{

    Quaternion q1(0.3, -0.1, 0.2, 0.3);
    Quaternion q2 = q1 * q1;
    Quaternion q3 = q1.squaring();
    qDebug() << (int)( q2 == q3 );
    //return 0;
  /*  Function1 *f = new Function1(Quaternion(1.5));

    JuliaSet set(f, 2);

    Quaternion q1(0, -1, 2, 3);
    Quaternion q2(0, -0.1, 0.2, 0.3);
    qDebug() << (int)set.isInSet(q1);
    qDebug() << (int)set.isInSet(q2);

    return 0;
*/


    //подключаем русский язык
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8")); //изменения
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
