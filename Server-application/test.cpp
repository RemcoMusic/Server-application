#include "test.h"



void Test::testIfQTestIsWorking()
{
 /*will always output true, a test to see if qtest is working*/
    QVERIFY(true);
}

#ifdef RUN_TESTS
MainWindow *w;
SwarmAlgorithms *swarmAlgorithms;
RobotConnection *robotConnection;
SwarmSimulation *swarmSimulation;
robotDetection *robotDetection;
#endif

void Test::initTestCase()
{
    #ifdef RUN_TESTS

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

    #endif
    //return a.exec();
}

void Test::cleanupTestCase()
{


}
void Test::testMapFunction()
{
    double output = map(50,0,100,0,1000); // should output 500
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

    //check if the bot has been appended to the list
    RobotLocation *ptr =  locationManager.robots.at(newSize-1);

    QVERIFY(ptr->x = 123 &&\
            ptr->y == 123 &&\
            ptr->sharedData.status == robotStatus::STARTUP &&\
            ptr->ip == "0.0.0.0");

}

#ifdef RUN_TESTS
QTEST_MAIN(Test)
#endif


//#include "Test.moc"
