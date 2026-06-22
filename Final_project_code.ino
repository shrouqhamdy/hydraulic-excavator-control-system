char command = '0';
int speed = 180;

const int relayPin1 = 2; // relay 1
const int relayPin2 = 3; // relay 2
const int relayPin3 = 4; // relay 3

const int relayPump3 = 10;

// Pump1
#define P1_IN1 5
#define P1_IN2 6

// Pump2
#define P2_IN1 7
#define P2_IN2 30

// Pump4
#define P4_IN1 26
#define P4_IN2 28

// For Motors
#define ENA 9
#define ENB 8

// Left Motor
#define ML_IN1 22
#define ML_IN2 24

// Right Motor
#define MR_IN1 12
#define MR_IN2 13

// MOTOR FUNC
void forward() {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);

  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);
}

void backward() {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);

  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);
}

void turnRight() {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);

  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);
}

void turnLeft() {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);

  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);

  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, LOW);

  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, LOW);
}

//CAR FUNC
void drive(){
  switch(command) {
    case 'F': forward();    Serial.println("forward");    break;
    case 'B': backward();   Serial.println("backward");   break;
    case 'R': turnRight();  Serial.println("Right");      break;
    case 'L': turnLeft();   Serial.println("Left");       break;
    case 'S': stopMotors(); Serial.println("stop");       break;
  }
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);

  pinMode(relayPump3, OUTPUT);

  pinMode(P1_IN1, OUTPUT);
  pinMode(P1_IN2, OUTPUT);

  pinMode(P2_IN1, OUTPUT);
  pinMode(P2_IN2, OUTPUT);

  pinMode(P4_IN1, OUTPUT);
  pinMode(P4_IN2, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(ML_IN1, OUTPUT);
  pinMode(ML_IN2, OUTPUT);

  pinMode(MR_IN1, OUTPUT);
  pinMode(MR_IN2, OUTPUT);

  digitalWrite(relayPin1, LOW);
  digitalWrite(relayPin2, LOW);
  digitalWrite(relayPin3, LOW);

  digitalWrite(relayPump3, LOW);

  digitalWrite(P1_IN1, LOW);
  digitalWrite(P1_IN2, LOW);

  digitalWrite(P2_IN1, LOW);
  digitalWrite(P2_IN2, LOW);

  digitalWrite(P4_IN1, LOW);
  digitalWrite(P4_IN2, LOW);

}

void readSerial() {
  while (Serial1.available()) {
    command = Serial1.read();
    Serial.println(command);
  }
}

void control(){
  if (command == '1') {
  digitalWrite(relayPin1, HIGH);
  digitalWrite(P1_IN1, HIGH);
  digitalWrite(P1_IN2, LOW);

  digitalWrite(P2_IN1, HIGH);
  digitalWrite(P2_IN2, LOW);

  }
  else if (command == '4') {
    digitalWrite(relayPin1, LOW);
    digitalWrite(P1_IN1, LOW);
    digitalWrite(P1_IN2, LOW);

    digitalWrite(P2_IN1, LOW);
    digitalWrite(P2_IN2, LOW);
  }

  else if (command == '2') {
    digitalWrite(relayPin2, HIGH);
    digitalWrite(P1_IN1, HIGH);
    digitalWrite(P1_IN2, LOW);

    digitalWrite(P2_IN1, HIGH);
    digitalWrite(P2_IN2, LOW);

  }
  else if (command == '5') {
    digitalWrite(relayPin2, LOW);
    digitalWrite(P1_IN1, LOW);
    digitalWrite(P1_IN2, LOW);

    digitalWrite(P2_IN1, LOW);
    digitalWrite(P2_IN2, LOW);
  }

  else if (command == '3') {
    digitalWrite(relayPin3, HIGH);
    digitalWrite(P1_IN1, HIGH);
    digitalWrite(P1_IN2, LOW);

    digitalWrite(P2_IN1, HIGH);
    digitalWrite(P2_IN2, LOW);

  }
  else if (command == '6') {
    digitalWrite(relayPin3, LOW);
    digitalWrite(P1_IN1, LOW);
    digitalWrite(P1_IN2, LOW);

    digitalWrite(P2_IN1, LOW);
    digitalWrite(P2_IN2, LOW);
  }
  else if (command == 'x') {
    digitalWrite(relayPump3, HIGH);
    Serial.println("Pump3");
  }
  else if (command == 's') {
    digitalWrite(relayPump3, LOW);

  }
  else if (command == 'z') {
    digitalWrite(P4_IN1, HIGH);
    digitalWrite(P4_IN2, LOW);

  }
  else if (command == 'a') {
    digitalWrite(P4_IN1, LOW);
    digitalWrite(P4_IN2, LOW);

  }
}

void loop() {
  readSerial();
  control();
  drive();
}

