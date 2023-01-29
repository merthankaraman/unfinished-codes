#include <Servo.h>
#define servo_1_pin 3
#define servo_2_pin 5
#define servo_3_pin 6

#define servo_4_pin 9
#define servo_5_pin 10
#define servo_6_pin 11

int servo_1_aci = 0, servo_2_aci = 0, servo_3_aci = 0;
int servo_4_aci = 0, servo_5_aci = 0, servo_6_aci = 0;

#define joystick_x A0
#define joystick_y A1
#define pot_z A2

Servo servo_1, servo_2, servo_3, servo_4, servo_5, servo_6;

void baglantilar_setup(){
  servo_1.attach(servo_1_pin); servo_2.attach(servo_2_pin); servo_3.attach(servo_3_pin);
  servo_4.attach(servo_4_pin); servo_5.attach(servo_5_pin); servo_6.attach(servo_6_pin);
}
