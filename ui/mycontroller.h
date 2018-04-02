#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include "my_scene.h"
#include "CImage.h"


#include <QWidget>
#include <QtGui>
#include <QErrorMessage>
#include <QString>
#include <QStringList>
#include <QLineEdit>
#include <QGraphicsScene>

#include <string>
#include <stdio.h>
#include <vector>

#include "math/basefunction.h"
using namespace std;
enum Text_Error { EMPTY, E_SYMBOL, NO_ER };


namespace Ui {
class MyController;
}

class MyController : public QWidget
{
    Q_OBJECT

public:
    explicit MyController(QWidget *parent = 0);
    ~MyController();
    void GetScene(tScene *scene);
signals:
    void SceneChange(QGraphicsScene *scene);
private slots:


    void on_foncolorButton_clicked();

    void on_visorcolorButton_clicked();

    void on_clearButton_clicked();

    void on_drawButton_clicked();

private:
    QString GetColor(QColor &color);
    double *GetData(vector <QLineEdit*> &vec);
    BaseFunction* getFunction(const Quaternion &c);

    tScene scene;
    tPaintParam  data;
    CImage image;
    Ui::MyController *ui;
    QWidget *par;
    QColor colorLine;
    QRegExpValidator *ValidatorDouble;
    QIntValidator *Validator;

};

double Analiz_Text(QString str);
#endif // MYCONTROLLER_H
