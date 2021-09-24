#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>


const int r_speed = 10;
const int r_motor = 12;

const int l_speed = 11;
const int l_motor = 13;

const int buzzer = 4;
const int led = 5;

void Motor(char state, char speed) {
    if (state == 'w') {
        digitalWrite(r_motor, HIGH);
        digitalWrite(l_motor, HIGH);
        analogWrite(r_speed, speed);
        analogWrite(l_speed, speed);
    } else if (state == 's') {
        digitalWrite(r_motor, LOW);
        digitalWrite(l_motor, LOW);
        analogWrite(r_speed, 0);
        analogWrite(l_speed, 0);
    } else if (state == 'd') {
        digitalWrite(r_motor, HIGH);
        digitalWrite(l_motor, LOW);
        analogWrite(r_speed, speed);
        analogWrite(l_speed, 0);
    } else if (state == 'a') {
        digitalWrite(r_motor, LOW);
        digitalWrite(l_motor, HIGH);
        analogWrite(r_speed, 0);
        analogWrite(l_speed, speed);
    } else if (state == 'x') {
        digitalWrite(r_motor, HIGH);
        digitalWrite(l_motor, HIGH);
        analogWrite(r_speed, -speed);
        analogWrite(l_speed, -speed);
    }
    Serial.print("state: ");
    Serial.print(state);
    Serial.print("speed: ");
    Serial.print(speed);
}

void controller (const std_msgs::String& keystroke) {
    char state = keystroke.data[0];
    char speed = keystroke.data[1];
    Motor(state, 255);
}

void Buzzer() {

}

void Led() {

}

ros::NodeHandle nh;
ros::Subscriber <std_msgs::String> sub("controller", controller);  // for pub input
//ros::Subscriber sub("cmd_vel", cmd_vel_cb);  // for teleop

void setup() {
    pinMode(r_speed, OUTPUT);
    pinMode(r_motor, OUTPUT);
    pinMode(l_speed, OUTPUT);
    pinMode(l_motor, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(led, OUTPUT);

    nh.initNode();
    nh.subscribe(sub);
}

void loop() {
    nh.spinOnce();
    delay(1);
}
