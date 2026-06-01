#include <Bluepad32.h>

ControllerPtr controller1;
HardwareSerial MotionSerial(2);   // UART2
char cmd =0;

// CONTROLLER 

void onConnectedController(ControllerPtr ctl) {
    Serial.println("Controller Connected");
    controller1 = ctl;
}

void onDisconnectedController(ControllerPtr ctl) {
    Serial.println("Controller Disconnected ");
    controller1 = nullptr;
}


// GAMEPAD
void processGamepad(ControllerPtr ctl) {

    // ARM CONTROL 
    if (ctl->y())              cmd = 'a'; // Triangle
    else if (ctl->a())         cmd = 'b'; // X
    else if (ctl->b())         cmd = 'c'; // Circle
    else if (ctl->x())         cmd = 'd'; // Square
    else if (ctl->dpad() == DPAD_UP)        cmd = 'e'; 
    else if (ctl->dpad() == DPAD_DOWN)      cmd = 'f'; 
    else if (ctl->dpad() == DPAD_RIGHT)     cmd = 'j'; 
    else if (ctl->dpad() == DPAD_LEFT)      cmd = 'k'; 

    //CAR CONTROL
    else if (ctl->l1())        cmd = 'B'; // L1
    else if (ctl->r1())        cmd = 'F'; // R1
    else if (ctl->l2())        cmd = 'L'; // L2 
    else if (ctl->r2())        cmd = 'R'; // R2 
    else                       cmd = 'N';

    MotionSerial.print(cmd);
    Serial.println(cmd);   

}
  
// PROCESS 

void processController() {
    if (controller1 && controller1->isConnected() && controller1->hasData()) {
        processGamepad(controller1);
    }
}


void setup() {
  // put your setup code here, to run once:
    Serial.begin(115200);

    // UART communication to Motion 2350 Pro
    MotionSerial.begin(115200, SERIAL_8N1, 16, 17);

    BP32.setup(&onConnectedController, &onDisconnectedController);

    BP32.forgetBluetoothKeys();
}

void loop() {
    BP32.update();

    processController();

    delay(50);
}
