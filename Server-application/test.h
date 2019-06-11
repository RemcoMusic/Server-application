#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest>
#include <main.h>
#include "globalhelperfunctions.h"
#include "locationmanager.h"

class Test: public QObject
{
    Q_OBJECT
private slots:
    void testIfQTestIsWorking();
    void initTestCase();
    void cleanupTestCase();

    //global helper functions
    void testMapFunction();
    void testDistanceBetweenPoints();


    //locationmanager
    void testAddingANewRobot();

    //global settings
    void validateInitialGlobalSettings();

    //gui
    void testGuiUpdateSpeed();

};




#endif // TEST_H
