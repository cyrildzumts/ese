/*
 * GPIO.cpp
 *
 *  Created on: Oct 7, 2017
 *      Author: cyrildz
 */

#include "GPIO.h"

namespace core {

GPIO::GPIO() {
	// TODO Auto-generated constructor stub

}

GPIO::~GPIO() {
	// TODO Auto-generated destructor stub
}

} /* namespace core */

core::Motor::Motor() {
	port_addr = PORTA_ADDR;
	running_state = false;
}

void core::Motor::start() {
	uint8_t porta = in8(port_addr);
	uint8_t motor_bits = porta & 0x0F;
	motor_bits |=MOTOR_RIGHT;
	motor_bits &= ~(MOTOR_STOP | MOTOR_LEFT);
	porta = (porta & 0xF0) | motor_bits;
	out8(port_addr, porta);
	running_state = true;

}

void core::Motor::stop() {
	uint8_t motor_bits = in8(port_addr) & 0x000F;
	motor_bits |=MOTOR_STOP;
	out8(port_addr, motor_bits);
}

void core::Motor::forward() {
	start();
}

void core::Motor::backward() {
	uint8_t porta = in8(port_addr);
		uint8_t motor_bits = porta & 0x0F;
		motor_bits |=MOTOR_LEFT;
		motor_bits &= ~(MOTOR_STOP | MOTOR_RIGHT);
		porta = (porta & 0xF0) | motor_bits;
		out8(port_addr, porta);
		running_state = true;
}

void core::Motor::setSpeed(SPEED speed) {
	uint8_t porta = in8(port_addr);
	uint8_t motor_bits = porta & 0x0F;
	if(speed == SPEED::SLOW){
		motor_bits |= MOTOR_SLOW;
		motor_bits &= ~(MOTOR_STOP);
	}
	else{
		motor_bits &= ~(MOTOR_STOP | MOTOR_SLOW);
	}
	porta = (porta & 0xF0) | motor_bits;
	out8(port_addr, porta);
	running_state = true;
}

bool core::Motor::isRunning() const {
	return running_state;
}

core::Switch::Switch():opened(false), port_addr(PORTA_ADDR){
}

void core::Switch::open() {
	uint8_t porta = in8(port_addr);
	porta |= SWITCH_OPEN;
	out8(port_addr, porta);
	opened = true;

}

void core::Switch::close() {
	uint8_t porta = in8(port_addr);
	porta &= ~SWITCH_OPEN;
	out8(port_addr, porta);
	opened = false;
}

bool core::Switch::isOpened() const {
	return opened;
}

core::Light::Light():port_addr(PORTA_ADDR) {
}

void core::Light::turnLight(LIGHT light, PINLEVEL level) {
	uint8_t porta = in8(port_addr);
	uint8_t offset=0;
	switch(light){
	case RED:
		offset = RED_LIGHT_ON;
		break;
	case GREEN:
		offset = GREEN_LIGHT_ON;
		break;
	case YELLOW:
		offset = YELLOW_LIGHT_ON;
		break;
	}

	if(level== ON){
		porta |= offset;
	}
	else if(level == OFF){
		porta &= ~offset;
	}
	out8(port_addr, porta);
}

core::Led::Led() : port_addr(PORTC_ADDR){
}

void core::Led::turnLed(LED led, PINLEVEL level) {
	uint8_t portc = in8(port_addr);
	uint8_t offset=0;
	switch(led){
	case START:
		offset = START_LED_ON;
		break;
	case RESET:
		offset = RESET_LED_ON;
		break;
	case Q1:
		offset = Q1_LED_ON;
		break;
	case Q2:
		offset = Q2_LED_ON;
		break;
	}

	if(level== ON){
		portc |= offset;
	}
	else if(level == OFF){
		portc &= ~offset;
	}
	out8(port_addr, portc);
}
