//#include <QCoreApplication>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <math.h>
#include <iostream>
#include <fstream>

#include "hexon.h"
#include "controlwindow.h"
//#include "matrix.h"
#include "nnbase.h"

//using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        //QCoreApplication a(argc, argv);

        std::cout << "Hello World!\n";

        ControlWindow w;
        //w.showMaximized();
        w.show();

        a.exec();
    }
    catch(const std::exception&)
    {
        return 1;
    }

    return 0;
}
