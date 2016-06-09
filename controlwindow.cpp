#include "controlwindow.h"
#include "ui_controlwindow.h"

#include <QCoreApplication>
#include <iostream>

// Constructor for ControlWindow
// Generates interactive elements, and attaches signals
ControlWindow::ControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ControlWindow)
{
    ui->setupUi(this);

    startButton = new QPushButton("Start",this);
    startButton->setGeometry(QRect(QPoint(100,100),QSize(50,25)));

    connect(startButton, SIGNAL(clicked()), this, SLOT(on_startButton_clicked()));
    //connect(&timer, SIGNAL(timeout()), &scene, SLOT(tick_update()));
}

// Destructor
// Stops timer, and deletes UI before exiting
ControlWindow::~ControlWindow()
{
    timer.stop();
    delete ui;
}

// Slot for when start button is pressed
// Sets up view, hex_map, and timer
void ControlWindow::on_startButton_clicked()
{
    // Set Global variables - #from control window values
    set_map_size(20); // radius of map
    set_visibility(4); // visibility range of Hexons
    int size = get_map_size();

    // Scaled size of scene
    scene.setSceneRect(-50*size, -50*size, 100*size, 100*size);

    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    srand(0);
    // Generate random Hexons
    for (unsigned int i = 0; i < 200; i++) // #from control window value
    {
        bool s = false;
        while (!s)
        {
            // generate random position in hexagon #make new function?
            int a = (rand() % (2*size+1)) - size;
            int b = (rand() % (2*size-std::abs(a)+1)) - size;
            if (a < 0)
            {
                b = b - a;
            }
            cube h = {a,b,-a-b};
            // add hexon to map
            s = hex_map.AddHexItem(new Hexon(h), &scene);
        }
    }

    for (unsigned int i = 0; i < 1; i++) // #from control window value
    {
        bool s = false;
        while (!s)
        {
            // generate random position in hexagon #make new function?
            int a = (rand() % (2*size+1)) - size;
            int b = (rand() % (2*size-std::abs(a)+1)) - size;
            if (a < 0)
            {
                b = b - a;
            }
            cube h = {a,b,-a-b};
            // add obstacle to map
            s = hex_map.AddHexItem(new Obstacle(h), &scene);
        }
    }

    // attach scene to view, and adjust settings
    view.setScene(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(Qt::black);

    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate); // FullViewportUpdate
    view.setDragMode(QGraphicsView::ScrollHandDrag);

    view.setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Hexons"));
    view.resize(800, 800);

    // display view (new window)
    view.showMaximized();

    // connect timer to update function
    connect(&timer, SIGNAL(timeout()), this, SLOT(tick_update()));
    // start timer with msec milliseconds
    timer.start(1000/2);
}

// Slot for timer tick
// runs map update
void ControlWindow::tick_update()
{
    hex_map.map_update();
    return;
}
