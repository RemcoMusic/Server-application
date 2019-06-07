#include <Arduino.h>
#include "debug.h"

RemoteDebug Debug;

void processCmdRemoteDebug() 
{
	String lastCmd = Debug.getLastCommand();

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
        globalData.DriveForward = true;
        delay(2000);
        globalData.DriveForward = false;
    }

    if (lastCmd == "left") {
        debugE("turning left");
        globalData.TurnLeft = true;
        delay(2000);
        globalData.TurnLeft = false;
    }

    if (lastCmd == "right") {
        debugE("turning right");
        globalData.TurnRight = true;
        delay(2000);
        globalData.TurnRight = false;
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
    }

    delay(250);
}
