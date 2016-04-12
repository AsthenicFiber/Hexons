//#include <QCoreApplication>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <math.h>
#include <iostream>
#include <fstream>

#include "hexon.h"
#include "controlwindow.h"
#include "matrix.h"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        //QCoreApplication a(argc, argv);

        cout << "Hello World!\n";

        Matrix A(2,2);
        A.get(0,0) = 1;
        A.get(0,1) = 2;
        A.get(1,0) = 3;
        A.get(1,1) = 4;
        A.print_matrix();

        Matrix B(2,2), C(2,2);
        B = A;
        B.print_matrix();
        C = A + B;

        std::cout << A.get(0,0) << "\t" << A[1][1] << "\t" << A(0,1) << std::endl;
        C.print_matrix();

        A[1][0] = A[0][1];
        A.print_matrix();
        C(1,0) = C(0,0);
        C.print_matrix();
        B++.print_matrix();


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
