#include <Bluepad32.h>
ControllerPtr controller1;
HardwareSerial ArduinoSerial(2);

char cmd = '0';

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
  if (ctl->a())              cmd = '1'; // X
  else if (ctl->b())         cmd = '3'; // Circle
  else if (ctl->x())         cmd = '2'; // Square

  else if (ctl->dpad() == DPAD_UP)      cmd = 'x';
  else if (ctl->dpad() == DPAD_DOWN)    cmd = '4';
  else if (ctl->dpad() == DPAD_RIGHT)   cmd = '6';
  else if (ctl->dpad() == DPAD_LEFT)    cmd = '5';
  else if (ctl->thumbL())               cmd = 's';
  else if (ctl->thumbR())               cmd = 'z';
  //CAR CONTROL
  else if (ctl->l1())        cmd = 'L'; // L1
  else if (ctl->r1())        cmd = 'R'; // R1
  else if (ctl->l2())        cmd = 'B'; // L2
  else if (ctl->r2())        cmd = 'F'; // R2
  else if (ctl->y())         cmd = 'S'; // Triangle

  ArduinoSerial.write(cmd);
}


// PROCESS
void processController() {
    if (controller1 && controller1->isConnected() && controller1->hasData()) {
        processGamepad(controller1);
    }
}

void setup() {

  Serial.begin(9600);

 // ESP32 TX (GPIO17) with Arduino RX (Pin 1)
  ArduinoSerial.begin(9600, SERIAL_8N1, 16, 17);
  BP32.setup(&onConnectedController, &onDisconnectedController);
  BP32.forgetBluetoothKeys();
}

void loop() {
    BP32.update();
    processController();
    delay(50);
}
