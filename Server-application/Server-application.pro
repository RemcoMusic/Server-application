#-------------------------------------------------
#
# Project created by QtCreator 2019-05-09T09:58:29
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server-application
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
QMAKE_CXXFLAGS += "-Wno-old-style-cast"
QMAKE_CXXFLAGS += "-Wconversion"
SOURCES += \
    globalhelperfunctions.cpp \
    locationmanager.cpp \
    main.cpp \
    objects/ball.cpp \
    objects/chargestation.cpp \
    objects/objectsbase.cpp \
    robotlocationpainter.cpp \
    simulatedrobot.cpp \
    swarm_algorithms/chargealgorithm.cpp \
    swarm_algorithms/circlealgorithm.cpp \
    swarm_algorithms/halfcirclealgorithm.cpp \
    swarm_algorithms/linealgorithm.cpp \
    swarm_algorithms/linearmotionalgorithms.cpp \
    swarm_algorithms/rectanglealgorithm.cpp \
    swarm_algorithms/robotdisplacementdetection.cpp \
    swarm_algorithms/userinputfunctions.cpp \
    swarm_simulation/robotcode/arduino.cpp \
    test.cpp \
    user_interface\mainwindow.cpp \
    swarm_algorithms\swarmalgorithms.cpp \
    swarm_algorithms\swarmalgorithmssettings.cpp \
    robot_detection\robotdetection.cpp \
    robot_detection\robotdetectionsettings.cpp \
    swarm_simulation\swarmsimulation.cpp \
    swarm_simulation\swarmsimulationsettings.cpp \
    robot_connection\robotconnection.cpp \
    robot_connection\swarmbotcommunicationsettings.cpp \
    robotlocation.cpp \
    swarm_algorithms/swarmalgorithmbase.cpp \
    globalsettings.cpp \
    robotgroup.cpp \
    swarm_simulation/robotcode/motorDriver.cpp \
    swarm_simulation/robotcode/globals.cpp

HEADERS += \
    globalhelperfunctions.h \
    main.h \
    objects/chargestation.h \
    simulatedrobot.h \
    locationmanager.h \
    objects/ball.h \
    objects/objectsbase.h \
    swarm_algorithms/chargealgorithm.h \
    swarm_algorithms/circlealgorithm.h \
    swarm_algorithms/halfcirclealgorithm.h \
    swarm_algorithms/linealgorithm.h \
    swarm_algorithms/linearmotionalgorithms.h \
    swarm_algorithms/rectanglealgorithm.h \
    swarm_algorithms/robotdisplacementdetection.h \
    swarm_algorithms/userinputfunctions.h \
    swarm_simulation/robotcode/Arduino.h \
    swarm_simulation/robotcode/debug.h \
    test.h \
    user_interface\mainwindow.h \
    swarm_algorithms\swarmalgorithms.h \
    robot_detection\robotdetection.h \
    robot_connection\robotconnection.h \
    swarm_simulation\swarmsimulation.h \
    robot_detection\robotdetectionsettings.h \
    swarm_algorithms\swarmalgorithmssettings.h \
    robot_connection\swarmbotcommunicationsettings.h \
    swarm_simulation\swarmsimulationsettings.h \
    robotlocation.h \
    swarm_algorithms/swarmalgorithmbase.h \
    globalsettings.h \
    robotgroup.h \
    swarm_simulation/robotcode/motorDriver.h \
    swarm_simulation/robotcode/globals.h
FORMS += \
        user_interface/mainwindow.ui


INCLUDEPATH += swarm_simulation
INCLUDEPATH += swarm_simulation/robotcode
INCLUDEPATH += swarm_algorithms
INCLUDEPATH += robot_detection
INCLUDEPATH += robot_connection
INCLUDEPATH += user_interface
INCLUDEPATH += objects

INCLUDEPATH += $$(OPENCV_INCLUDE)

LIBS += $$(OPENCV_PATH)\bin\libopencv_core410.dll
LIBS += $$(OPENCV_PATH)\bin\libopencv_highgui410.dll
LIBS += $$(OPENCV_PATH)\bin\libopencv_imgcodecs410.dll
LIBS += $$(OPENCV_PATH)\bin\libopencv_imgproc410.dll
LIBS += $$(OPENCV_PATH)\bin\libopencv_features2d410.dll
LIBS += $$(OPENCV_PATH)\bin\libopencv_calib3d410.dll
LIBS += $$(OPENCV_PATH)\bin\libopencv_videoio410.dll

# more correct variant, how set includepath and libs for mingw
# add system variable: OPENCV_SDK_DIR=D:/opencv/opencv-build/install
# read http://doc.qt.io/qt-5/qmake-variable-reference.html#libs

#INCLUDEPATH += $$(OPENCV_SDK_DIR)/include

#LIBS += -L$$(OPENCV_SDK_DIR)/x86/mingw/lib \
#        -lopencv_core320        \
#        -lopencv_highgui320     \
#        -lopencv_imgcodecs320   \
#        -lopencv_imgproc320     \
#        -lopencv_features2d320  \
#        -lopencv_calib3d320

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
