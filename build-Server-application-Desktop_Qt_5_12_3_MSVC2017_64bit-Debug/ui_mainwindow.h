/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *cameraFeedLabel;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QLCDNumber *fpsNumber;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_5;
    QGraphicsView *graphicsView_Data;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_2;
    QLabel *label_9;
    QLabel *label_8;
    QLabel *label_10;
    QLCDNumber *lcdNumberSimulatedRobots;
    QLCDNumber *lcdNumberTotalRobots;
    QLCDNumber *lcdNumberRealRobots;
    QLCDNumber *lcdNumberTotalObstacles;
    QLabel *label_12;
    QGridLayout *gridLayout_3;
    QCheckBox *checkAccelerationControl;
    QCheckBox *checkInconsisentMotors;
    QCheckBox *checkUADWLB;
    QFrame *line_2;
    QCheckBox *checkRealSimulation;
    QCheckBox *checkDynamicSpeed;
    QCheckBox *checkRotationTime;
    QGridLayout *gridLayout_4;
    QLabel *label_11;
    QSlider *SliderRobotSpeed;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *AddSimulatedRobotButton;
    QPushButton *addSimulatedObjectButton;
    QPushButton *resetSimulationButton;
    QGridLayout *gridLayout_5;
    QLabel *label_13;
    QComboBox *ActiveAlgoritmList;
    QLabel *label_14;
    QComboBox *algorithmInputComboBox;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QGraphicsView *graphicsView_data_large;
    QWidget *tab_3;
    QHBoxLayout *horizontalLayout_3;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_7;
    QLabel *cameraFeedLabel_Large;
    QWidget *tab_5;
    QVBoxLayout *verticalLayout_8;
    QLabel *cameraRedFeed;
    QWidget *tab_6;
    QVBoxLayout *verticalLayout_9;
    QLabel *cameraGreenFeed;
    QWidget *tab_7;
    QVBoxLayout *verticalLayout_10;
    QLabel *cameraBlueFeed;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLabel *label_5;
    QComboBox *colorComboBox;
    QLCDNumber *lcdNumberVDinges;
    QSlider *sliderSaturation;
    QSlider *sliderVDinges;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QSlider *sliderHue;
    QFrame *line;
    QLCDNumber *lcdNumberSaturation;
    QLCDNumber *lcdNumberHue;
    QLabel *sli;
    QSlider *sliderDilate;
    QSlider *sliderDeviation;
    QSlider *sliderErode;
    QLCDNumber *lcdNumberDilate;
    QLCDNumber *lcdNumberDeviation;
    QLCDNumber *lcdNumberErode;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1288, 694);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        cameraFeedLabel = new QLabel(tab);
        cameraFeedLabel->setObjectName(QString::fromUtf8("cameraFeedLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraFeedLabel->sizePolicy().hasHeightForWidth());
        cameraFeedLabel->setSizePolicy(sizePolicy);
        cameraFeedLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(cameraFeedLabel);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_4->addWidget(label);

        fpsNumber = new QLCDNumber(tab);
        fpsNumber->setObjectName(QString::fromUtf8("fpsNumber"));

        verticalLayout_4->addWidget(fpsNumber);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));

        horizontalLayout_4->addLayout(verticalLayout_5);


        verticalLayout_2->addLayout(horizontalLayout_4);

        graphicsView_Data = new QGraphicsView(tab);
        graphicsView_Data->setObjectName(QString::fromUtf8("graphicsView_Data"));

        verticalLayout_2->addWidget(graphicsView_Data);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        label_10 = new QLabel(tab);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 2, 0, 1, 1);

        lcdNumberSimulatedRobots = new QLCDNumber(tab);
        lcdNumberSimulatedRobots->setObjectName(QString::fromUtf8("lcdNumberSimulatedRobots"));

        gridLayout_2->addWidget(lcdNumberSimulatedRobots, 1, 1, 1, 1);

        lcdNumberTotalRobots = new QLCDNumber(tab);
        lcdNumberTotalRobots->setObjectName(QString::fromUtf8("lcdNumberTotalRobots"));

        gridLayout_2->addWidget(lcdNumberTotalRobots, 0, 1, 1, 1);

        lcdNumberRealRobots = new QLCDNumber(tab);
        lcdNumberRealRobots->setObjectName(QString::fromUtf8("lcdNumberRealRobots"));

        gridLayout_2->addWidget(lcdNumberRealRobots, 2, 1, 1, 1);

        lcdNumberTotalObstacles = new QLCDNumber(tab);
        lcdNumberTotalObstacles->setObjectName(QString::fromUtf8("lcdNumberTotalObstacles"));

        gridLayout_2->addWidget(lcdNumberTotalObstacles, 3, 1, 1, 1);

        label_12 = new QLabel(tab);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 3, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout_2);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        checkAccelerationControl = new QCheckBox(tab);
        checkAccelerationControl->setObjectName(QString::fromUtf8("checkAccelerationControl"));
        checkAccelerationControl->setChecked(true);

        gridLayout_3->addWidget(checkAccelerationControl, 1, 1, 1, 1);

        checkInconsisentMotors = new QCheckBox(tab);
        checkInconsisentMotors->setObjectName(QString::fromUtf8("checkInconsisentMotors"));
        checkInconsisentMotors->setChecked(true);

        gridLayout_3->addWidget(checkInconsisentMotors, 2, 0, 1, 1);

        checkUADWLB = new QCheckBox(tab);
        checkUADWLB->setObjectName(QString::fromUtf8("checkUADWLB"));
        checkUADWLB->setChecked(true);

        gridLayout_3->addWidget(checkUADWLB, 2, 1, 1, 1);

        line_2 = new QFrame(tab);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_2, 0, 0, 1, 1);

        checkRealSimulation = new QCheckBox(tab);
        checkRealSimulation->setObjectName(QString::fromUtf8("checkRealSimulation"));
        checkRealSimulation->setChecked(true);

        gridLayout_3->addWidget(checkRealSimulation, 1, 0, 1, 1);

        checkDynamicSpeed = new QCheckBox(tab);
        checkDynamicSpeed->setObjectName(QString::fromUtf8("checkDynamicSpeed"));
        checkDynamicSpeed->setChecked(true);

        gridLayout_3->addWidget(checkDynamicSpeed, 3, 0, 1, 1);

        checkRotationTime = new QCheckBox(tab);
        checkRotationTime->setObjectName(QString::fromUtf8("checkRotationTime"));
        checkRotationTime->setChecked(true);

        gridLayout_3->addWidget(checkRotationTime, 3, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_3);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_4->addWidget(label_11, 0, 0, 1, 1);

        SliderRobotSpeed = new QSlider(tab);
        SliderRobotSpeed->setObjectName(QString::fromUtf8("SliderRobotSpeed"));
        SliderRobotSpeed->setMaximum(100);
        SliderRobotSpeed->setValue(50);
        SliderRobotSpeed->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(SliderRobotSpeed, 0, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        AddSimulatedRobotButton = new QPushButton(tab);
        AddSimulatedRobotButton->setObjectName(QString::fromUtf8("AddSimulatedRobotButton"));

        horizontalLayout_5->addWidget(AddSimulatedRobotButton);


        verticalLayout_3->addLayout(horizontalLayout_5);

        addSimulatedObjectButton = new QPushButton(tab);
        addSimulatedObjectButton->setObjectName(QString::fromUtf8("addSimulatedObjectButton"));

        verticalLayout_3->addWidget(addSimulatedObjectButton);

        resetSimulationButton = new QPushButton(tab);
        resetSimulationButton->setObjectName(QString::fromUtf8("resetSimulationButton"));

        verticalLayout_3->addWidget(resetSimulationButton);

        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_13 = new QLabel(tab);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_5->addWidget(label_13, 0, 0, 1, 1);

        ActiveAlgoritmList = new QComboBox(tab);
        ActiveAlgoritmList->setObjectName(QString::fromUtf8("ActiveAlgoritmList"));

        gridLayout_5->addWidget(ActiveAlgoritmList, 0, 1, 1, 1);

        label_14 = new QLabel(tab);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_5->addWidget(label_14, 1, 0, 1, 1);

        algorithmInputComboBox = new QComboBox(tab);
        algorithmInputComboBox->addItem(QString());
        algorithmInputComboBox->addItem(QString());
        algorithmInputComboBox->addItem(QString());
        algorithmInputComboBox->addItem(QString());
        algorithmInputComboBox->addItem(QString());
        algorithmInputComboBox->addItem(QString());
        algorithmInputComboBox->setObjectName(QString::fromUtf8("algorithmInputComboBox"));

        gridLayout_5->addWidget(algorithmInputComboBox, 1, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_3->addItem(horizontalSpacer);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_3->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout_3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_2 = new QHBoxLayout(tab_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        graphicsView_data_large = new QGraphicsView(tab_2);
        graphicsView_data_large->setObjectName(QString::fromUtf8("graphicsView_data_large"));

        horizontalLayout_2->addWidget(graphicsView_data_large);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        horizontalLayout_3 = new QHBoxLayout(tab_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        tabWidget_2 = new QTabWidget(tab_3);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_7 = new QVBoxLayout(tab_4);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        cameraFeedLabel_Large = new QLabel(tab_4);
        cameraFeedLabel_Large->setObjectName(QString::fromUtf8("cameraFeedLabel_Large"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cameraFeedLabel_Large->sizePolicy().hasHeightForWidth());
        cameraFeedLabel_Large->setSizePolicy(sizePolicy1);

        verticalLayout_7->addWidget(cameraFeedLabel_Large);

        tabWidget_2->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        verticalLayout_8 = new QVBoxLayout(tab_5);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        cameraRedFeed = new QLabel(tab_5);
        cameraRedFeed->setObjectName(QString::fromUtf8("cameraRedFeed"));

        verticalLayout_8->addWidget(cameraRedFeed);

        tabWidget_2->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        verticalLayout_9 = new QVBoxLayout(tab_6);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        cameraGreenFeed = new QLabel(tab_6);
        cameraGreenFeed->setObjectName(QString::fromUtf8("cameraGreenFeed"));

        verticalLayout_9->addWidget(cameraGreenFeed);

        tabWidget_2->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        verticalLayout_10 = new QVBoxLayout(tab_7);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        cameraBlueFeed = new QLabel(tab_7);
        cameraBlueFeed->setObjectName(QString::fromUtf8("cameraBlueFeed"));

        verticalLayout_10->addWidget(cameraBlueFeed);

        tabWidget_2->addTab(tab_7, QString());

        horizontalLayout_3->addWidget(tabWidget_2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 7, 0, 1, 1);

        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        colorComboBox = new QComboBox(tab_3);
        colorComboBox->addItem(QString());
        colorComboBox->addItem(QString());
        colorComboBox->addItem(QString());
        colorComboBox->addItem(QString());
        colorComboBox->addItem(QString());
        colorComboBox->addItem(QString());
        colorComboBox->setObjectName(QString::fromUtf8("colorComboBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(colorComboBox->sizePolicy().hasHeightForWidth());
        colorComboBox->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(colorComboBox, 0, 2, 1, 1);

        lcdNumberVDinges = new QLCDNumber(tab_3);
        lcdNumberVDinges->setObjectName(QString::fromUtf8("lcdNumberVDinges"));

        gridLayout->addWidget(lcdNumberVDinges, 3, 3, 1, 1);

        sliderSaturation = new QSlider(tab_3);
        sliderSaturation->setObjectName(QString::fromUtf8("sliderSaturation"));
        sliderSaturation->setMaximum(255);
        sliderSaturation->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderSaturation, 2, 2, 1, 1);

        sliderVDinges = new QSlider(tab_3);
        sliderVDinges->setObjectName(QString::fromUtf8("sliderVDinges"));
        sliderVDinges->setMaximum(255);
        sliderVDinges->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderVDinges, 3, 2, 1, 1);

        label_7 = new QLabel(tab_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 5, 0, 1, 1);

        label_4 = new QLabel(tab_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_2 = new QLabel(tab_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        sliderHue = new QSlider(tab_3);
        sliderHue->setObjectName(QString::fromUtf8("sliderHue"));
        sliderHue->setMaximum(179);
        sliderHue->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderHue, 1, 2, 1, 1);

        line = new QFrame(tab_3);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 4, 2, 1, 1);

        lcdNumberSaturation = new QLCDNumber(tab_3);
        lcdNumberSaturation->setObjectName(QString::fromUtf8("lcdNumberSaturation"));

        gridLayout->addWidget(lcdNumberSaturation, 2, 3, 1, 1);

        lcdNumberHue = new QLCDNumber(tab_3);
        lcdNumberHue->setObjectName(QString::fromUtf8("lcdNumberHue"));

        gridLayout->addWidget(lcdNumberHue, 1, 3, 1, 1);

        sli = new QLabel(tab_3);
        sli->setObjectName(QString::fromUtf8("sli"));

        gridLayout->addWidget(sli, 6, 0, 1, 1);

        sliderDilate = new QSlider(tab_3);
        sliderDilate->setObjectName(QString::fromUtf8("sliderDilate"));
        sliderDilate->setMinimum(1);
        sliderDilate->setMaximum(20);
        sliderDilate->setValue(8);
        sliderDilate->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderDilate, 5, 2, 1, 1);

        sliderDeviation = new QSlider(tab_3);
        sliderDeviation->setObjectName(QString::fromUtf8("sliderDeviation"));
        sliderDeviation->setMinimum(1);
        sliderDeviation->setMaximum(200);
        sliderDeviation->setValue(30);
        sliderDeviation->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderDeviation, 6, 2, 1, 1);

        sliderErode = new QSlider(tab_3);
        sliderErode->setObjectName(QString::fromUtf8("sliderErode"));
        sliderErode->setMinimum(1);
        sliderErode->setMaximum(20);
        sliderErode->setValue(3);
        sliderErode->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderErode, 7, 2, 1, 1);

        lcdNumberDilate = new QLCDNumber(tab_3);
        lcdNumberDilate->setObjectName(QString::fromUtf8("lcdNumberDilate"));

        gridLayout->addWidget(lcdNumberDilate, 5, 3, 1, 1);

        lcdNumberDeviation = new QLCDNumber(tab_3);
        lcdNumberDeviation->setObjectName(QString::fromUtf8("lcdNumberDeviation"));

        gridLayout->addWidget(lcdNumberDeviation, 6, 3, 1, 1);

        lcdNumberErode = new QLCDNumber(tab_3);
        lcdNumberErode->setObjectName(QString::fromUtf8("lcdNumberErode"));

        gridLayout->addWidget(lcdNumberErode, 7, 3, 1, 1);


        verticalLayout_6->addLayout(gridLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_3);


        horizontalLayout_3->addLayout(verticalLayout_6);

        tabWidget->addTab(tab_3, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);
        QObject::connect(sliderDilate, SIGNAL(valueChanged(int)), lcdNumberDilate, SLOT(display(int)));
        QObject::connect(sliderDeviation, SIGNAL(valueChanged(int)), lcdNumberDeviation, SLOT(display(int)));
        QObject::connect(sliderErode, SIGNAL(valueChanged(int)), lcdNumberErode, SLOT(display(int)));

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        cameraFeedLabel->setText(QApplication::translate("MainWindow", "No camera feed", nullptr));
        label->setText(QApplication::translate("MainWindow", "FPS:", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Number of simulated robots", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Total number of robots", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "Number of real robots", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "Number Of Obstacles", nullptr));
        checkAccelerationControl->setText(QApplication::translate("MainWindow", "Acceleration Control", nullptr));
        checkInconsisentMotors->setText(QApplication::translate("MainWindow", "Inconsistent Motors", nullptr));
        checkUADWLB->setText(QApplication::translate("MainWindow", "UADWLB", nullptr));
        checkRealSimulation->setText(QApplication::translate("MainWindow", "Real Simulation", nullptr));
        checkDynamicSpeed->setText(QApplication::translate("MainWindow", "Dynamic Speed", nullptr));
        checkRotationTime->setText(QApplication::translate("MainWindow", "Use Rotation Time as Weight", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "Robot Speed", nullptr));
        AddSimulatedRobotButton->setText(QApplication::translate("MainWindow", "Add Simulated Robot", nullptr));
        addSimulatedObjectButton->setText(QApplication::translate("MainWindow", "Add Simulated Object", nullptr));
        resetSimulationButton->setText(QApplication::translate("MainWindow", "Reset Simulation", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "Select Active Algoritm", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "Select Algiritm Input Source", nullptr));
        algorithmInputComboBox->setItemText(0, QApplication::translate("MainWindow", "None", nullptr));
        algorithmInputComboBox->setItemText(1, QApplication::translate("MainWindow", "Real Objects Center Outer", nullptr));
        algorithmInputComboBox->setItemText(2, QApplication::translate("MainWindow", "Real Objects Outer Outer", nullptr));
        algorithmInputComboBox->setItemText(3, QApplication::translate("MainWindow", "Hand gesture", nullptr));
        algorithmInputComboBox->setItemText(4, QApplication::translate("MainWindow", "Robot Movement", nullptr));
        algorithmInputComboBox->setItemText(5, QApplication::translate("MainWindow", "Robot Movement With Angle", nullptr));

        pushButton->setText(QApplication::translate("MainWindow", "thisButttonDoesNothing", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Overview", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Simulation View", nullptr));
        cameraFeedLabel_Large->setText(QApplication::translate("MainWindow", "No camera feed", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("MainWindow", "RGB", nullptr));
        cameraRedFeed->setText(QApplication::translate("MainWindow", "no red feed", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("MainWindow", "Red", nullptr));
        cameraGreenFeed->setText(QApplication::translate("MainWindow", "No green feed", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("MainWindow", "Green", nullptr));
        cameraBlueFeed->setText(QApplication::translate("MainWindow", "No blue feed", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QApplication::translate("MainWindow", "Blue", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Erode Object", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "V-Dinges", nullptr));
        colorComboBox->setItemText(0, QApplication::translate("MainWindow", "Red_Low", nullptr));
        colorComboBox->setItemText(1, QApplication::translate("MainWindow", "Red_High", nullptr));
        colorComboBox->setItemText(2, QApplication::translate("MainWindow", "Blue_Low", nullptr));
        colorComboBox->setItemText(3, QApplication::translate("MainWindow", "Blue_High", nullptr));
        colorComboBox->setItemText(4, QApplication::translate("MainWindow", "Green_Low", nullptr));
        colorComboBox->setItemText(5, QApplication::translate("MainWindow", "Green_High", nullptr));

        label_7->setText(QApplication::translate("MainWindow", "Dilate Object", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Saturation", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Hue", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Color:", nullptr));
        sli->setText(QApplication::translate("MainWindow", "Detection Deviation", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Camera View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
