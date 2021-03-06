#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1300, 700);
    //QHBoxLayout *mainLayout = new QHBoxLayout;
    //ui->centralWidget->setLayout(ui->mainLayout);
    //QTabWidget *tab = new QTabWidget();
    //mainLayout->addWidget(tab);
    QHBoxLayout *layout = new QHBoxLayout;
    //tab->addTab(layout, "draw");
    ui->centralWidget->setLayout(layout);
    this->setWindowTitle("Курсовой проект");
   // ui->analiz->setVisible(false);
    myPicture   = new MyGraphicView();
    layout->addWidget(myPicture);

    myController   = new MyController();
    layout->addWidget(myController);
    myController->setFixedWidth(495); //magic :)

    QObject::connect(myPicture, SIGNAL(SendScene(tScene*)),
            this, SLOT(SendingScene(tScene*)));
    myPicture->Connect();


    //QHBoxLayout *layout2 = new QHBoxLayout;
    //ui->analiz->setLayout(layout2);
    //myTimeanaliz = new MyTimeanaliz;
    //layout2->addWidget(myTimeanaliz);
}
void MainWindow::SendingScene(tScene* my_scene)
{
    std::cout << "window:" << my_scene->x_center << endl;
    myController->GetScene(my_scene);
}

MainWindow::~MainWindow()
{
    delete myPicture;
    delete myController;
    delete ui;
}
