#include <Servo.h>

#define RS_SIGNAL 10
#define JS1_SIGNAL 9
#define JS2_SIGNAL 6
#define CS_SIGNAL 5

#define LJOYSTICK_X 2
#define LJOYSTICK_Y 3
#define RJOYSTICK_X 0
#define RJOYSTICK_Y 1

#define ACTIVATION 16


struct servoController {
  Servo servo;
  int position;
  int max_position;
  int control_pin;
} rs_controller, js1_controller, js2_controller, cs_controller;

struct servoController create_servo_controller(int servo_pin, int max_position, int control_pin) {
  struct servoController new_controller;
  new_controller.servo.attach(servo_pin);
  new_controller.max_position = max_position;
  new_controller.position = max_position / 2;
  new_controller.control_pin = control_pin;
  return new_controller;
}

void update_servo_controller(struct servoController *controller) {
  int stick_value = analogRead(controller->control_pin);

  // Update and change the controller's position if the threshold of the stick is met.
  if ((stick_value >= 1024 - ACTIVATION) && (controller->position < controller->max_position)) {controller->position += 1;}
  else if ((stick_value <= ACTIVATION) && (controller->position > 0)) {controller->position -= 1;}
  controller->servo.write(controller->position);
}


void setup() {
  rs_controller = create_servo_controller(RS_SIGNAL, 270, RJOYSTICK_X);
  js1_controller = create_servo_controller(JS1_SIGNAL, 270, RJOYSTICK_Y);
  js2_controller = create_servo_controller(JS2_SIGNAL, 270, LJOYSTICK_X);
  cs_controller = create_servo_controller(CS_SIGNAL, 90, LJOYSTICK_Y);
  Serial.begin(9600);
}

void loop() {
  update_servo_controller(&rs_controller);
  update_servo_controller(&js1_controller);
  update_servo_controller(&js2_controller);
  update_servo_controller(&cs_controller);
  delay(15);
}
