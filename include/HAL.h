/*
 * HAL.h
 * Author: Cyrille Ngassam Nkwenga
 */

#ifndef HAL_H_
#define HAL_H_

#include <cstdint>
#include "GPIO.h"

using namespace std;
namespace core {

enum LEDID {
	START_LED, RESET_LED, Q1_LED, Q2_LED
};

enum LIGHTID {
	RED_LIGHT, GREEN_LIGHT, YELLOW_LIGHT
};


enum DIRECTION {
	LEFT, RIGHT
};

typedef struct {
	uint32_t id;
	uint32_t data;
	uint32_t type;

} Data;

class AbstractHAL {

public:

	virtual ~AbstractHAL() {
	}
	/**
	 * Start the Festo System
	 */
	virtual void start()=0;
	/**
	 * Stop the Festo System.
	 */
	virtual void stop()=0;
	/**
	 * Reset the Festo System
	 */
	virtual void reset()=0;
	/**
	 *
	 * @param led the LED to be turned ON/OFF
	 * @param level defines whether the LED should be turn ON or OFF
	 * 		level = LEVEL::OFF --> turn OFF
	 * 		level = LEVEL::ON --> turn ON
	 */
	virtual void ledOnOFF(LEDID led, PINLEVEL level) = 0;
	/**
	 *
	 * @param light the Light to be turned ON/OFF
	 * @param level defines whether the Light should be turn ON or OFF
	 * 		level = LEVEL::OFF --> turn OFF
	 * 		level = LEVEL::ON --> turn ON
	 */
	virtual void lightOnOFF(LIGHTID light, PINLEVEL level) = 0;

	/**
	 * readHeight : read the height of an item
	 * @return the Height of the Item that is current at the height sensor.
	 */
	virtual float readHeight() = 0;

	/**
	 * open or close the switch depending the level parameter
	 * @param level the new state of the switch
	 * 		  level = LEVEL::OFF --> close the Switch
	 * 		  level = LEVEL::ON	 --> open the Switch
	 */
	virtual void switchOnOFF(PINLEVEL level) = 0;

	/**
	 * Turn the motor the direction incated by dir.
	 * @param dir the direction of the motor
	 * 		  dir = DIRECTION::LEFT --> Motor runs left
	 * 		  dir = DIRECTION::RIGHT --> Motor runs right
	 */
	virtual void motorDirection(DIRECTION dir) = 0;

	/**
	 * Turn the motor ON or OFF depending the level parameter
	 * @param level defines the state of the Motor :
	 * 		  level = LEVEL::OFF --> Motor OFF
	 * 		  level = LEVEL::ON  --> Motor ON
	 */
	virtual void motorOnOFF(PINLEVEL level) = 0;

	/**
	 *
	 * @return the state of the Slide
	 * 		0 --> Slide not full, may be empty
	 * 		1 --> Slide Full.
	 */
	virtual int slideState() = 0;

	/**
	 * Send data through the serial port.
	 * @param data
	 */
	virtual void sendData(Data data) = 0;

	/**
	 * This method return complete HAL State flags.
	 * All Sensor & GPIO state are read by this method.
	 * @return the HAL peripheral State.
	 */
	virtual uint32_t getStateFlag() = 0;

};

class HAL : public AbstractHAL {

private:
	uint32_t peripheral_states;



private:
	void updatePeripheralState();

public:
	virtual uint32_t getStateFlag();

};

} /* namespace core */
#endif /* HAL_H_ */
