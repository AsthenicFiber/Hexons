#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <vector>

//#include "hexon.h"
//#include "obstacle.h"
#include "map.h"

namespace Ui {
    class ControlWindow;
}

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ControlWindow(QWidget *parent = 0);
    ~ControlWindow();
    QTimer timer;

private:
    Ui::ControlWindow *ui;
    QPushButton *startButton;
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
