#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <algrorithmvisualisation.h>
#include "robotlocation.h"
#include "robotlocationmanager.h"
#include <QTime>
#include <QDebug>
#include <robotdetectionsettings.h>
#include <QObject>

extern QGraphicsScene *dataScene; //forward declaration (made in cpp)

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void colorSlidersChanged(int c);
    void on_pushButton_clicked();

    void on_colorComboBox_currentIndexChanged(int index);


public slots:
    void updateGui();
private:
    //QGraphicsScene *dataScene;
    //QGraphicsScene *cameraScene;
    QTime *fpsTimer;
    Ui::MainWindow *ui;
    bool flipFlop = true;
};

#endif // MAINWINDOW_H
