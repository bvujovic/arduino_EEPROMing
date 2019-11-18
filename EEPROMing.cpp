#include "EEPROMing.h"

EEPROMing::EEPROMing()
{
	display = new TM1637Display(4, 3); // (CLK, DIO)
	display->setBrightness(2);
	const int digitCount = 4;
	clearScreen = new uint8_t[digitCount];
	for (int i = 0; i < digitCount; i++)
		clearScreen[i] = 0;
}

// Citanje EEPROM memorije od pozicije startPos sve do EEPROM_END i prikaz tih vrednosti na TM1637 sa itvDelay delay-em.
void EEPROMing::MemToDisplay(int startPos, int itvDelay)
{
	int i = startPos;
	int n = EEPROM.length();
	int val;
	while (i < n)
	{
		val = EEPROM.read(i++);
		if (val == EEPROM_END)
		{
			display->showNumberDec(0, true); // "0000" - oznaka za kraj prikazivanja sadrzaja EEPROM memorije
			break;
		}
		display->showNumberDec(val);
		delay(itvDelay);
		display->setSegments(clearScreen);
		delay(ITV_SMALL_DELAY);
	}
}

// Vraca broj upisanih vrednosti od startPos sve do prve EEPROM_END ili kraja EEPROM memorije.
int EEPROMing::ValCount(int startPos)
{
	int i = startPos;
	int n = EEPROM.length();
	while (i < n)
		if (EEPROM.read(i++) == EEPROM_END)
			break;
	return (i - 1) - startPos;
}

// Pise vrednost val u EEPROM (na startPos poziciji). Vraca true ako je startPos < EEPROM.length()
bool EEPROMing::Write(int val)
{
	int n = EEPROM.length();
	if (startPos < n)
	{
		if (val == EEPROM_END)
			val = EEPROM_END - 1;
		EEPROM.write(startPos++, val);							 // upisivanje date vrednosti val
		if (startPos < n && EEPROM.read(startPos) != EEPROM_END) // ako na sledecoj poziciji nije EEPROM_END, upisati to
			EEPROM.write(startPos, EEPROM_END);					 // za slucaj da je ovo poslednji upis pa da se zna da je tu kraj
		return true;
	}
	else
		return false;
}
