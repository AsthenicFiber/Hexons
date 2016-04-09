//#include <QCoreApplication>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <math.h>
#include <iostream>
#include <fstream>

#include "hexon.h"
#include "controlwindow.h"

using namespace std;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QCoreApplication a(argc, argv);

    cout << "Hello World!\n";

    ControlWindow w;
    //w.showMaximized();
    w.show();

    a.exec();
    //cin.get();

    //QTimer timer;
    //QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    //timer.start(1000);

    //return a.exec();
    return 0;
}
