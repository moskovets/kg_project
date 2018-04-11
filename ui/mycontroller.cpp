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
#include "graphic/dimension4.h"
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

    ui->xminEdit->setValidator(ValidatorDouble);
    ui->yminEdit->setValidator(ValidatorDouble);
    ui->zminEdit->setValidator(ValidatorDouble);
    ui->xmaxEdit->setValidator(ValidatorDouble);
    ui->ymaxEdit->setValidator(ValidatorDouble);
    ui->zmaxEdit->setValidator(ValidatorDouble);

    ui->rEdit->setValidator(ValidatorDouble);

    ui->maxIterEdit->setValidator(Validator);

    //ui->xAngleEdit->setValidator(ValidatorDouble);
    //ui->yAngleEdit->setValidator(ValidatorDouble);
    //ui->zAngleEdit->setValidator(ValidatorDouble);

    ui->xLightEdit->setValidator(ValidatorDouble);
    ui->yLightEdit->setValidator(ValidatorDouble);
    ui->zLightEdit->setValidator(ValidatorDouble);

    ui->radSphereEdit->setValidator(ValidatorDouble);

    ui->wEdit->setValidator(ValidatorDouble);

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

    ui->xLightEdit->setText(QString::number(1/sqrt(3)));
    ui->yLightEdit->setText(QString::number(1/sqrt(3)));
    ui->zLightEdit->setText(QString::number(1/sqrt(3)));

    ui->radSphereEdit->setText("0.01");

    //TODO
    m_lightColor = Color(255, 255, 255);
    m_fonColor = Color(0, 0, 0);
    //data.fon = QColor(255, 255, 255); //фон черный
    //data.color = QColor(0, 0, 0); //цвет наблюдателя
    //colorLine = data.color;
    data.sizePixel = 1;

    ui->previewButton->clicked();
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
void MyController::on_drawButton_clicked()
{
    try {
        this->on_drawButtom_clicked();
    }
    catch(...) {
    }
    std::cout << "end\n";
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
    case 1:
        return new Function2(c);
    //TODO добавить остальные функции
    default:
        return new Function1(c);
    }
}

double MyController::m_getScaleResolution()
{
    double scale = 1;
    if (ui->resolution16radioButton->isChecked()) {
        return scale / 4;
    }
    if (ui->resolution9radioButton->isChecked()) {
        return scale / 3;
    }
    if (ui->resolution4radioButton->isChecked()) {
        return scale / 2;
    }
    if (ui->resolution1radioButton->isChecked()) {
        return scale;
    }
    if (ui->resolution_2radioButton->isChecked()) {
        return scale * sqrt(2);
    }
    return 1.0;
}

int MyController::m_getThreadNumber()
{
    if (ui->thread1radioButton->isChecked()) {
        return 1;
    }
    if (ui->thread2radioButton->isChecked()) {
        return 2;
    }
    if (ui->thread4radioButton->isChecked()) {
        return 4;
    }
    if (ui->thread8radioButton->isChecked()) {
        return 8;
    }
    if (ui->thread3radioButton->isChecked()) {
        return 3;
    }
    return 1;
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
    m_fonColor = Color(color.red(), color.green(), color.blue());
    //colorLine = color;
}

void MyController::on_clearButton_clicked()
{
    image = CImage(scene, data);
}




void MyController::on_drawButtom_clicked()
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

    //edits.push_back(ui->xAngleEdit);
    //edits.push_back(ui->yAngleEdit);
    //edits.push_back(ui->zAngleEdit);

    edits.push_back(ui->xLightEdit);
    edits.push_back(ui->yLightEdit);
    edits.push_back(ui->zLightEdit);

    edits.push_back(ui->radSphereEdit);

    edits.push_back(ui->wEdit);

    double *arr = GetData(edits);

    if(LineEditError != NO_ER)
        return;

    Quaternion c(arr[0], arr[1], arr[2], arr[3]);
    BaseFunction* func = getFunction(c);


    Vector4 lightVector(arr[12], arr[13], arr[14]);
    tParamFractal param = {
        arr[4],
        arr[5],
        arr[6],
        arr[7],
        arr[8],
        arr[9],

        arr[10],
        (int)arr[11],
        lightVector.norm3(),
        m_lightColor,
        m_fonColor
    };
    param.scale = m_getScaleResolution();
    param.thread_count = m_getThreadNumber();
    param.radiusSphere = arr[15];

    double w = arr[16];
    param.w = w;
    if (ui->colorModecheckBox->isChecked()) {
        if (w >= -1 && w <= 1) {
            double w0 = (w + 1) / 2;
            Dimension4 d;
            param.lightColor = d.getColorForNormCoord(w0);
        }
    }
    //image.algo(scene, this->data, func, param);
    if (ui->algoradioButton->isChecked()) {
        image.algoThread2(scene, this->data, func, param);
    }
    else {
        image.algoThread(scene, this->data, func, param);
    }
    delete[] arr;

}

void MyController::on_previewButton_clicked()
{
    vector<QLineEdit*> edits;

    edits.push_back(ui->xLightEdit);
    edits.push_back(ui->yLightEdit);
    edits.push_back(ui->zLightEdit);

    double *arr = GetData(edits);

    if(LineEditError != NO_ER)
        return;

    Vector4 lightVector(arr[0], arr[1], arr[2]);
    lightVector.normalize3();
    SetDrawer setDrawer(ui->prewiewlabel->size().height(), ui->prewiewlabel->size().width(), 20, 20, 0.75, Light(lightVector, m_lightColor), m_fonColor);
    setDrawer.setPixel(Vector4(0, 0, 10), Color(255, 255, 255));
    QImage image = setDrawer.getImage().scaled(ui->prewiewlabel->size().height(), ui->prewiewlabel->size().width());
    QPixmap pixmap;
    pixmap.convertFromImage(image);
    ui->prewiewlabel->setPixmap(pixmap);
}
