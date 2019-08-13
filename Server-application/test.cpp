#include "test.h"


#ifdef RUN_TESTS

MainWindow *w;
SwarmAlgorithms *swarmAlgorithms;
RobotConnection *robotConnection;
SwarmSimulation *swarmSimulation;
robotDetection *robotDetection;


void Test::prepareAndRunAlgoritm(QString algoritmName, int numBots)
{
    locationManager.resetEverything();
    for(int i = 0; i<numBots;i++){
        locationManager.addSimulatedRobot();
    }
    swarmAlgorithmsSettings.runNewAlgortim(algoritmName, true);

    QBENCHMARK{
        swarmAlgorithms->doTheAlgoritm();
    }
}

void Test::testIfQTestIsWorking()
{
 /*will always output true, a test to see if qtest is working*/
    QVERIFY(true);
}



void Test::initTestCase()
{


    w = new MainWindow();
    swarmAlgorithms = new SwarmAlgorithms();
    robotConnection = new RobotConnection();
    swarmSimulation = new SwarmSimulation();
    robotDetection = new class robotDetection();

    w->show();
    robotDetection->start();

    QObject::connect(robotDetection,SIGNAL(makeANewRobot(int,int)),&locationManager,SLOT(makeNewRealRobot(int,int)));
    QObject::connect(robotDetection,SIGNAL(newFrameFinished()),swarmSimulation,SLOT(startSimulation()));
    QObject::connect(swarmSimulation,SIGNAL(simulationFinished()),swarmAlgorithms,SLOT(update()));
    QObject::connect(swarmAlgorithms,SIGNAL(algoritmFinished()),robotConnection,SLOT(connectionloop()));
    QObject::connect(robotConnection,SIGNAL(done()),w,SLOT(updateGui()));

    //return a.exec();
}

void Test::cleanupTestCase()
{


}
void Test::testMapFunction()
{
    double output;
    output = map(50,0,100,0,1000); // should output 500
    QVERIFY(output == 500);
}
void Test::testDistanceBetweenPoints()
{
    double a = 10;
    double b = 20;
    double distance = sqrt(a*a+b*b);
    double result = distanceBetweenPoints(0,0,a,b);
    QVERIFY(result == distance);
}


void Test::testAddingANewRobot()
{
    int currentSize = locationManager.robots.size();
    locationManager.makeNewRealRobot(123,123);
    int newSize = locationManager.robots.size();

    QVERIFY(newSize == currentSize+1); // see if at least 1 bot has been added

    //check if the bot has been appended to the list with the right parameters
    RobotLocation *ptr =  locationManager.robots.at(newSize-1);

    QVERIFY(ptr->x == 123);
    QVERIFY(ptr->y == 123);
    QVERIFY(ptr->sharedData.status == robotStatus::STARTUP);
    QVERIFY(ptr->ip == "0.0.0.0");

}

void Test::validateInitialGlobalSettings()
{
    QVERIFY(globalSettings.fieldSizeX >0);
    QVERIFY(globalSettings.fieldSizeY >0);
    QVERIFY(globalSettings.cameraX >0);
    QVERIFY(globalSettings.cameraY >0);
    QVERIFY(globalSettings.botDiameter >0);
    QVERIFY(globalSettings.botDistanceBetweenWheels != 0);
    QVERIFY(globalSettings.simulationSpeed >= 0);
}

void Test::testGuiUpdateSpeed(){  // do nothing,, the benchmark will cause a lot of debugging because the image is a nullptr
//    QBENCHMARK{
//        w->updateGui();
    //    }
}

void Test::testAlgorihmSpeed_data()
{


    QTest::addColumn<QString>("AlgoritmName");
    QTest::addColumn<QString>("NumBots");

    QTest::newRow("CircleAlgorirm-10bots") << "CircleAlgorirm" << "10";
    QTest::newRow("CircleAlgorirm-30bots") << "CircleAlgorirm" << "30";
    QTest::newRow("CircleAlgorirm-100bots") << "CircleAlgorirm" << "100";
    QTest::newRow("LineAlgoritm-10bots")     << "LineAlgoritm" << "10";
    QTest::newRow("LineAlgoritm-30bots")     << "LineAlgoritm" << "30";
    QTest::newRow("LineAlgoritm-100bots")     << "LineAlgoritm" << "100";
    QTest::newRow("halfCircleAlgorithm-10bots") << "halfCircleAlgorithm" << "10";
    QTest::newRow("halfCircleAlgorithm-30bots") << "halfCircleAlgorithm" << "30";
    QTest::newRow("halfCircleAlgorithm-100bots") << "halfCircleAlgorithm" << "100";
    QTest::newRow("RemcoAlgoritm-10bots") << "RemcoAlgoritm" << "10";
    QTest::newRow("rectangle-10bots") << "RectangleAlgoritm" << "10";
    QTest::newRow("rectangle-30bots") << "RectangleAlgoritm" << "30";
    QTest::newRow("rectangle-100bots") << "RectangleAlgoritm" << "100";

}

void Test::testAlgorihmSpeed()
{
    QFETCH(QString, AlgoritmName);
    QFETCH(QString, NumBots);
    prepareAndRunAlgoritm(AlgoritmName,NumBots.toInt());
}

QTEST_MAIN(Test)
#endif  //RUN_TEST


//#include "Test.moc"
