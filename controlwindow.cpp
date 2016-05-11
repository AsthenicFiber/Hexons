#include "controlwindow.h"
#include "ui_controlwindow.h"

#include <QCoreApplication>
#include <iostream>

ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);

    startButton = new QPushButton("Start",this);
    startButton->setGeometry(QRect(QPoint(100,100),QSize(200,50)));

    connect(startButton, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    //connect(&timer, SIGNAL(timeout()), &scene, SLOT(tick_update()));
}

ControlWindow::~ControlWindow()
{
    timer.stop();
    delete ui;
}

void ControlWindow::on_startButton_clicked()
{
    //QGraphicsScene scene;
    scene.setSceneRect(-2000, -2000, 4000, 4000);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    //for (unsigned int i = 0; i < hexons.size(); i++)
    for (unsigned int i = 0; i < 30; i++)
    {
        //scene.addItem(hexons[i]);
        int a = (rand() % 39) - 20;
        int b = (rand() % 39) - 20;
        cube h = {a,b,-a-b};
        hex_map.AddHexItem(new Hexon(h), &scene);
        //scene.addItem(hex_map[h]);
    }

    for (unsigned int i = 0; i < 30; i++)
    {
        //obstacles.push_back(new Obstacle());
        //scene.addItem(obstacles[i]);

        int a = (rand() % 39) - 20;
        int b = (rand() % 39) - 20;
        cube h = {a,b,-a-b};
        hex_map.AddHexItem(new Obstacle(h), &scene);
        //scene.addItem(hex_map[h]);
    }

    view.setScene(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(Qt::black);

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Hexons"));
    view.resize(800, 800);
    view.show();

    connect(&timer, SIGNAL(timeout()), this, SLOT(tick_update()));
    timer.start(1000/2);
}

void ControlWindow::tick_update()
{
    hex_map.map_update();
    return;
}
