/*
 * GPIO.h
 *
 *  Created on: Oct 7, 2017
 *      Author: cyrildz
 */

#ifndef GPIO_H_
#define GPIO_H_
#include <cstdint>
#include <hw/inout.h>

// PORT ADDRESSES
#define PORTA_ADDR 0x300
#define PORTB_ADDR 0x301
#define PORTC_ADDR 0x302
#define CONFIG_REG 0x303
/****************************************************/
// PORT A CONTROLS : ALL SIGNAL ARE OUTPUT
//MOTO CONTROLS
#define MOTOR_RIGHT				(1 << 0)
#define MOTOR_LEFT				(1 << 1)
#define MOTOR_SLOW				(1 << 2)
#define MOTOR_STOP				(1 << 3)

// SWITCH CONTROLS
#define SWITCH_OPEN				(1 << 4)
// LIGHTS CONTROLS
#define GREEN_LIGHT_ON			(1 << 5)
#define YELLOW_LIGHT_ON			(1 << 6)
#define RED_LIGHT_ON			(1 << 7)
/****************************************************/


// PORT B CONTROLS : ALL SIGNAL ARE INPUTS
#define ITEM_ON_INPUT			(1 << 0)
#define ITEM_ON_HIGHT			(1 << 1)
#define ITEM_SIZE_OK			(1 << 2)
#define ITEM_AT_SWITCH			(1 << 3)
#define ITEM_IS_METAL			(1 << 4)
#define SWITCH_IS_OPENED 		(1 << 5)
#define SLIDE_NOT_FULL			(1 << 6)
#define ITEM_ON_OUTPUT			(1 << 7)
/*****************************************************/


// PORT C CONTROLS :
// OUTPUT SIGNALS
#define START_LED_ON			(1 << 0)
#define RESET_LED_ON			(1 << 1)
#define Q1_LED_ON				(1 << 2)
#define Q2_LED_ON				(1 << 3)

// INPUT SIGNALS
#define START_PRESSED			(1 << 4)
#define STOP_NOT_PRESSED		(1 << 5)
#define RESET_PRESSED			(1 << 6)
#define ESTOP_NOT_PRESSED		(1 << 7)
/****************************************************/
namespace core {
enum PINLEVEL{
			OFF,ON
		};

class GPIO {
public:
	GPIO();
	virtual ~GPIO();
};

class Motor{
private:
	uintptr_t port_addr;
	bool running_state;
public:
	enum SPEED{
		SLOW, FAST
	};
public:

	Motor();
	Motor(const Motor &)=delete;
	Motor &operator=(const Motor &)=delete;
	/**
	 * starts the motor running forward at the normal speed.
	 */
	void start();
	/**
	 * stops the motor. The direction and the speed of the motor is
	 * preserved. This method does nothing if the motor is not running.
	 */
	void stop();
	/**
	 * run the motor forward. If the motor was stopped when
	 * calling this method then it will be started. The speed
	 * won't be changed if the motor was running.
	 */
	void forward();
	/**
	 * run the motor backward. If the motor was stopped when
	 * calling this method then it will be started. The speed
	 * won't be changed if the motor was running.
	 */

	void backward();
	/**
	 * changes the current motor's speed.
	 * @param speed
	 */
	void setSpeed(SPEED speed);
	/**
	 * query the motor current state :
	 *
	 * @return true --> motor is running
	 * 		   false--> motor is not running
	 */

	bool isRunning()const;

};

class Switch{
private:
	uintptr_t port_addr;
	bool opened;

public:
	Switch();
	Switch(const Switch &)= delete;
	Switch& operator=(const Switch&)=delete;
	/**
	 * Opens the Switch. Does nothing if the Switch is already opened.
	 */
	void open();
	/**
	 * closed the Switch. Does nothing if the Switch is already closed.
	 */
	void close();
	/**
	 * queries the Switch state
	 * @return the Switch's state.
	 * true --> the Switch is opened
	 * false --> the Switch is closed.
	 */
	bool isOpened()const;
};

class Light{
private:
	uintptr_t port_addr;

public:
	enum LIGHT{
		RED,GREEN,YELLOW
	};
	enum LIGHTLEVEL{
		OFF,ON
	};

public:
	Light();
	Light(const Light &)=delete;
	Light& operator=(const Light &)=delete;
	/**
	 * turn the desired light ON orOFF depending on the
	 * the level parameter
	 * @param light The light to be turn ON/OFF
	 * light = RED --> Red Light will be affected
	 * light = GREEN --> Green light will be affected
	 * light = YELLOW --> YELLOW light will be affected
	 * @param level the new light state
	 * ON-->Turn the light ON
	 * OFF-->Turn the light OFF
	 *
	 */
	void turnLight(LIGHT light,PINLEVEL level);

};

class Led{
private:
	uintptr_t port_addr;
public:
	enum LED{
		START,RESET,Q1,Q2
	};

public:
	Led();
		Led(const Led &)=delete;
		Led& operator=(const Led &)=delete;
		/**
		 * turn the desired led ON orOFF depending on the
		 * the level parameter
		 * @param led The led to be turn ON/OFF

		 * @param level the new led state
		 * ON-->Turn the led ON
		 * OFF-->Turn the led OFF
		 *
		 */
		void turnLed(LED led,PINLEVEL level);
};

} /* namespace core */
#endif /* GPIO_H_ */
