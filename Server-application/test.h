#ifndef TEST_H
#define TEST_H
#include <main.h>   //--> contains RUN_TEST macro
#ifdef RUN_TESTS

#include <QObject>
#include <QtTest>
#include "globalhelperfunctions.h"
#include "locationmanager.h"
#include "swarmalgorithms.h"

class Test: public QObject
{
    Q_OBJECT
private:
    void prepareAndRunAlgoritm(QString algoritmName, int numBots);
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

    //algoritms
    void testAlgorihmSpeed_data();  // data for the test
    void testAlgorihmSpeed();       // the actual test

};




#endif // TEST_H
#endif //RUN_TEST
