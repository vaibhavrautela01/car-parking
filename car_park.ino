#include <Servo.h>

Servo tap_servo;

int sensor_pin1 = 1;
int sensor_pin2 = 4;

int ir_car1 = 5;
int ir_car2 = 6;
int ir_car3 = 7;

int tap_servo_pin = 3;

int S1 = 0, S2 = 0, S3 = 0;
int slot = 3;

void setup() {
  pinMode(sensor_pin1, INPUT);
  pinMode(sensor_pin2, INPUT);
  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);

  tap_servo.attach(tap_servo_pin);

  Serial.begin(9600);
}

void loop() {
  int val1 = digitalRead(sensor_pin1);
  int val2 = digitalRead(sensor_pin2);

  if (val1 == 0 && val2 == 0) {
    tap_servo.write(0);
  } else if (val1 == 1 && val2 == 0) {
    tap_servo.write(90);
    slot++;
  } else if (val1 == 0 && val2 == 1) {
    tap_servo.write(90);
    slot--;
  } else if (val1 == 1 && val2 == 1) {
    tap_servo.write(0);
  }

  updateParkingStatus();

  Serial.print("Slot: ");
  Serial.println(slot);
  Serial.print("S1: ");
  Serial.println(S1 == 1 ? "Fill" : "Empty");
  Serial.print("S2: ");
  Serial.println(S2 == 1 ? "Fill" : "Empty");
  Serial.print("S3: ");
  Serial.println(S3 == 1 ? "Fill" : "Empty");

  if (S1 == 1 && S2 == 1 && S3 == 1) {
    Serial.println("Sorry, Parking Full");
  }

  delay(1500);
}

void updateParkingStatus() {
  S1 = digitalRead(ir_car1);
  S2 = digitalRead(ir_car2);
  S3 = digitalRead(ir_car3);
}
