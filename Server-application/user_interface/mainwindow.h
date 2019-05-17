#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <algrorithmvisualisation.h>
#include "robotlocation.h"
#include "robotlocationmanager.h"
#include <QDebug>
namespace Ui {
class MainWindow;
}

extern AlgrorithmVisualisation algorithmVisualisation;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

public slots:
    void updateGui();
private:
    QGraphicsScene *dataScene;
    QGraphicsScene *cameraScene;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
