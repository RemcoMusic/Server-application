#include <Arduino.h>
#include "debug.h"

RemoteDebug Debug;
OTA OTAUpdater;

void processCmdRemoteDebug() 
{
	String lastCmd = Debug.getLastCommand();

    if (lastCmd == "ota") {
        OTAUpdater.startOTA();
        debugE("ota started");
    }

	if (lastCmd == "reset") {
        udpData.status = OFF;
        debugE("Resetting");
    }

	if (lastCmd == "restart") {
        debugE("Esp restarting");
        ESP.restart();
    }

	if (lastCmd == "disableMotor") {
        debugE("Motors disabled");
        globalData.motorsEnabled = false;
    }

	if (lastCmd == "enableMotor") {
        debugE("Motors enabled");
        globalData.motorsEnabled = true;
    }

	if (lastCmd == "debugMotor") {
        debugE("MotorDebug enabled");
        globalData.motorDebug = true;
    }

    if (lastCmd == "disDebugMotor") {
        debugE("MotorDebug disabled");
        globalData.motorDebug = false;
    }

    if (lastCmd == "forward") {
        debugE("Driving forward");
        udpData.status = NORMAL;
        globalData.DriveForward = true;
        delay(2000);
        globalData.DriveForward = false;
        globalData.Stop = true;
        delay(500);
        globalData.Stop = false;
    }

    if (lastCmd == "left") {
        debugE("turning left");
        udpData.status = NORMAL;
        globalData.TurnLeft = true;
        delay(2000);
        globalData.TurnLeft = false;
        globalData.Stop = true;
        delay(500);
        globalData.Stop = false;
    }

    if (lastCmd == "right") {
        debugE("turning right");
        udpData.status = NORMAL;
        globalData.TurnRight = true;
        delay(2000);
        globalData.TurnRight = false;
        globalData.Stop = true;
        delay(500);
        globalData.Stop = false;
    }

    if (lastCmd == "test") {
        debugE("turning left");
        udpData.status = NORMAL;
        globalData.TurnLeft = true;
        delay(2000);
        globalData.TurnLeft = false;
        debugE("turning right");
        globalData.TurnRight = true;
        delay(2000);
        globalData.TurnRight = false;
    }

    if (lastCmd == "stop") {
        debugE("Stopping");
        udpData.status = NORMAL;
        globalData.Stop = true;
        globalData.TurnLeft = false;
        globalData.TurnRight = false;
        delay(2000);
        globalData.Stop = false;
    }

    if (lastCmd == "map") {
        globalData.Map = true;
        debugE("Using mapped speed");
    }

    if (lastCmd == "stopMap") {
        globalData.Map = false;
        debugE("Using fixed speed");
    }

    if (lastCmd == "led") 
    {
       debugE("ledOn");
       globalData.Led = true;
       delay(3000);
       globalData.Led = false;
       debugE("ledOff");
    }

    if (lastCmd == "enableMotor") {
        debugE("Motors enabled");
        globalData.motorsEnabled = true;
    }
}

void debug::setup()
{
    Debug.begin("SwarmbotronDebug");  // Initiaze the telnet server
    Debug.setResetCmdEnabled(false); // Enable the reset command
	Debug.showProfiler(true);  // Profiler measures times
	Debug.showColors(true); // Colors inthe console
    Debug.setCallBackProjectCmds(&processCmdRemoteDebug);
}

void debug::loop()
{
    Debug.handle();  

    debugV("* Status: %u", udpData.status);
    debugV("* CurrentX: %d", udpData.currentX);
    debugV("* CurrentY: %d", udpData.currentY);
    debugV("* NewX: %d", udpData.newX);
    debugV("* NewY: %d", udpData.newY);
    debugV("* Speed: %u", udpData.speed);
    debugV("* DeviceStatus: %u", udpData.status);
    debugV("================================================");
    
    if(globalData.targetFound)
    {
        debugE("Target found!");
        delay(1000);
    }

    delay(250);
}
