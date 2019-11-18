// Citanje EEPROM memorije sa ATtiny85.
// VAZNO! U radu sa EEPROM-om na ATtiny-u, ispostavilo se da se ta memorija cuva samo kad je chip na 8MHz.
// https://arduino.stackexchange.com/questions/25080/can-you-access-the-eeprom-of-an-attiny-with-arduino-code
// + citanje vrednosti sa EEPROM-a. 255 je oznaka za kraj -> kod pisanja u EEPROM vrednost 255 zameniti sa 254
// + prikazivanje tih vrednosti na display, eventualno dodati vracanje vrednosti kao rezultat
// - brisanje vrednosti sa EEPROM-a -> postavljanje bajtova na 255, sve dok se ne naidje na 255
// - pisanje u EEPROM pocevsi od neke adrese (ne mora biti 0)
// - napraviti od ovoga nekakvu biblioteku i mozda je okaciti na GitHub

#include <EEPROM.h>

#include <TM1637Display.h>
TM1637Display display(4, 3); // (CLK, DIO)

#define EEPROM_END 255

// Citanje EEPROM memorije od pozicije start sve do EEPROM_END i prikaz tih vrednosti na TM1637 sa itvDelay delay-em.
void MemToDisplay(int itvDelay = 1000, int start = 1)
{
  int i = start;
  int n = EEPROM.length();
  int val;
  while (i < n)
  {
    val = EEPROM.read(i++);
    if (val == EEPROM_END)
    {
      display.showNumberDec(0, true); // "0000" - oznaka za kraj prikazivanja sadrzaja EEPROM memorije
      break;
    }
    display.showNumberDec(val);
    delay(itvDelay);
  }
}

void setup()
{
  display.setBrightness(2);
  MemToDisplay();
}

void loop()
{
}
