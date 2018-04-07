#include "mycontroller.h"
#include "ui_mycontroller.h"
#include <QRegExpValidator>
#include <QIntValidator>
#include <QFileDialog>
#include <iostream>
#include <string.h>
#include <QColorDialog>
#include <QDebug>

#include "juliafunctions.h"

#define MIN_PAR    10
#define LEN        300
#define MAX_PIXEL  100
#define MAX_RADIUS 100

Text_Error LineEditError;

MyController::MyController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyController)
{
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    par = parent;
    ui->setupUi(this);
    ValidatorDouble = new QRegExpValidator(QRegExp("^[+-]?[0-9]{0,5}(\\.|,|$)[0-9]{0,4}$"));
    Validator = new QIntValidator(0, 1000);
    ui->aEdit->setValidator(ValidatorDouble);
    ui->bEdit->setValidator(ValidatorDouble);
    ui->cEdit->setValidator(ValidatorDouble);
    ui->dEdit->setValidator(ValidatorDouble);

    ui->xAngleEdit->setValidator(ValidatorDouble);
    ui->yAngleEdit->setValidator(ValidatorDouble);
    ui->zAngleEdit->setValidator(ValidatorDouble);

    ui->xLightEdit->setValidator(ValidatorDouble);
    ui->yLightEdit->setValidator(ValidatorDouble);
    ui->zLightEdit->setValidator(ValidatorDouble);

    ui->xminEdit->setValidator(ValidatorDouble);
    ui->yminEdit->setValidator(ValidatorDouble);
    ui->zminEdit->setValidator(ValidatorDouble);
    ui->xmaxEdit->setValidator(ValidatorDouble);
    ui->ymaxEdit->setValidator(ValidatorDouble);
    ui->zmaxEdit->setValidator(ValidatorDouble);

    ui->rEdit->setValidator(ValidatorDouble);

    ui->maxIterEdit->setValidator(Validator);

    //установка значений по умолчанию
    ui->aEdit->setText("-0.65");
    ui->bEdit->setText("-0.5");

    ui->rEdit->setText("3");
    ui->maxIterEdit->setText("15");

    ui->xminEdit->setText("-2");
    ui->xmaxEdit->setText("2");

    ui->yminEdit->setText("-1");
    ui->ymaxEdit->setText("1");

    ui->zminEdit->setText("-2");
    ui->zmaxEdit->setText("2");

    //TODO
    //data.fon = QColor(255, 255, 255); //фон черный
    //data.color = QColor(0, 0, 0); //цвет наблюдателя
    //colorLine = data.color;
    data.sizePixel = 1;


}
void MyController::GetScene(tScene *scene1)
{
    this->scene.x_center = scene1->x_center;
    this->scene.y_center = scene1->y_center;
    this->scene.scene = scene1->scene;
    image = CImage(scene, data);

}

MyController::~MyController()
{
    delete Validator;
    delete ValidatorDouble;
    delete ui;
}

//получение данных с выбранных полей
double * MyController::GetData(vector <QLineEdit*> &vec)
{
    QString str;
    double *data = new double[vec.size()];
    double x;
    QString mess;
    for(unsigned int i = 0; i < vec.size(); i++) {
        str = vec[i]->text();
        x = Analiz_Text(str);
        switch(LineEditError) {
        case EMPTY:
            mess = "Область текста пуста.\n Введите данные!";
            break;
        case E_SYMBOL:
            mess = "Ошибочный символ\n "
                   "Разрешается использование только цифр, '.'',' и знаков табуляции";
            break;
        }
        if(LineEditError != NO_ER) {
            QErrorMessage errorMessage;
            errorMessage.showMessage(mess);
            errorMessage.exec();
            break;
        }
        data[i] = x;
    }
   return data;
}
//анализ строки данных (проверка, явл-тся ли вещественным числом)
double Analiz_Text(QString str)
{
    LineEditError = NO_ER;
    if(str == "") {
        LineEditError = EMPTY;
        return 0;
    }
    str.replace(QString(","), QString("."));
    //str.replace(QString("\n"), QString(" "));

    QStringList list = str.split(' ', QString::SkipEmptyParts);
    if(list.size() > 1) {
        LineEditError = E_SYMBOL;
        return 0;
    }

    double x;
    bool ok = true;
    for(int i = 0; i < list.size(); i++) {
        x = list.at(i).toDouble(&ok);
        if(!ok) {
            LineEditError = E_SYMBOL;
            return 0;
        }
    }
    return x;
}
BaseFunction* MyController::getFunction(const Quaternion &c)
{
    switch(ui->functionComboBox->currentIndex())
    {
    case 0:
        return new Function1(c);
    //TODO добавить остальные функции
    default:
        return new Function1(c);
    }
}

QString MyController::GetColor(QColor &color)
{
    QString r = QString::number(color.red());
    QString g = QString::number(color.green());
    QString b = QString::number(color.blue());
    QString res = "rgb(" + r + ", " + g + ", " + b + ")";
    return res;
}

void MyController::on_lightcolorButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    if (!color.isValid() ) {
     return;
    }
    ui->lightlabel->setStyleSheet("background-color: " + GetColor(color));
    //data.fon = color;
    m_lightColor = Color(color.red(), color.green(), color.blue());
    //image.changeFon(scene, color);
}


void MyController::on_visorcolorButton_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    if (!color.isValid() ) {
     return;
    }
    ui->visorlabel->setStyleSheet("background-color: " + GetColor(color));
    data.color = color;
    colorLine = color;
}

void MyController::on_clearButton_clicked()
{
    image = CImage(scene, data);
}


void MyController::on_drawButton_clicked()
{
    vector<QLineEdit*> edits;
    edits.push_back(ui->aEdit);
    edits.push_back(ui->bEdit);
    edits.push_back(ui->cEdit);
    edits.push_back(ui->dEdit);

    edits.push_back(ui->xminEdit);
    edits.push_back(ui->xmaxEdit);
    edits.push_back(ui->yminEdit);
    edits.push_back(ui->ymaxEdit);
    edits.push_back(ui->zminEdit);
    edits.push_back(ui->zmaxEdit);

    edits.push_back(ui->rEdit);
    edits.push_back(ui->maxIterEdit);

    edits.push_back(ui->xAngleEdit);
    edits.push_back(ui->yAngleEdit);
    edits.push_back(ui->zAngleEdit);

    edits.push_back(ui->xLightEdit);
    edits.push_back(ui->yLightEdit);
    edits.push_back(ui->zLightEdit);

    double *arr = GetData(edits);

    if(LineEditError != NO_ER)
        return;

    Quaternion c(arr[0], arr[1], arr[2], arr[3]);
    BaseFunction* func = getFunction(c);


    Vector4 lightVector(arr[15], arr[16], arr[17]);
    tParamFractal param = {
        arr[4],
        arr[5],
        arr[6],
        arr[7],
        arr[8],
        arr[9],

        arr[10],
        (int)arr[11],
        arr[12],
        arr[13],
        arr[14],
        lightVector.norm3(),
        m_lightColor
    };

    //image.algo(scene, this->data, func, param);
    image.algoThread2(scene, this->data, func, param);

    delete[] arr;
}
