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

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        //QCoreApplication a(argc, argv);

        cout << "Hello World!\n";

        NNBase NN(10, 5, 20);
        NN.feedforward().print_matrix();

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
