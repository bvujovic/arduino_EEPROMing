#ifndef EEPROMING_H
#define EEPROMING_H

#define EEPROM_END 255
#define ITV_SMALL_DELAY 100

#include "Arduino.h"
#include <EEPROM.h>
#include <TM1637Display.h>

class EEPROMing
{
private:
	TM1637Display* display;
	uint8_t* clearScreen;
	int writePos = 0;
	
public:
	EEPROMing();

	void MemToDisplay(int start = 0, int itvDelay = 1000);
	int ValCount(int start = 0);
	bool Write(int val);

	// Dohvati poziciju u EEPROM memoriji na kojoj ce sledeci podatak biti upisan.
	int GetWritePos() { return writePos; };
	// Postavi poziciju u EEPROM memoriji na kojoj ce sledeci podatak biti upisan.
	void SetWritePos(int val) { writePos = val; };

	// Dohvati display koji se koristi za prikaz podataka iz EEPROM memorije.
	TM1637Display* GetDisplay() { return display; };
};

#endif