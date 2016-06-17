#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QPushButton>
//#include <QInputDialog>
#include <QSpinBox>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <vector>
#include <map>

//#include "hexon.h"
//#include "obstacle.h"
#include "map.h"

namespace Ui {
    class ControlWindow;
}

struct InputWidget
{
    QSpinBox * spinbox;
    QLabel * label;
    InputWidget(QWidget * parent, int X, int Y, int min, int max, int def_val, char * labelText)
    {
        spinbox = new QSpinBox(parent);
        spinbox->setGeometry(X,Y+25,71,22);
        spinbox->setValue(def_val);
        spinbox->setRange(min,max);
        label = new QLabel(parent);
        label->setText(labelText);
        label->setGeometry(X,Y,100,22);
    }

    InputWidget()
    {
        spinbox = new QSpinBox();
        label = new QLabel();
    }

    int value()
    {
        return spinbox->value();
    }
};

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = 0);
    ~ControlWindow();
    QTimer timer;

private:
    Ui::ControlWindow *ui;
    std::map <int, InputWidget*> inputs;
    InputWidget * mapsizeInput;
    QGraphicsScene scene;
    QGraphicsView view;

    Map hex_map;

signals:

protected:

private slots:
    void on_startButton_clicked();
    void tick_update();
};

#endif // CONTROLWINDOW_H
