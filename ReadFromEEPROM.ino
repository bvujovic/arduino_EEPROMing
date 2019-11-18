// Citanje EEPROM memorije sa ATtiny85. 
// VAZNO! U radu sa EEPROM-om na ATtiny-u, ispostavilo se da se ta memorija cuva samo kad je chip na 8MHz.
// https://arduino.stackexchange.com/questions/25080/can-you-access-the-eeprom-of-an-attiny-with-arduino-code
// - citanje vrednosti sa EEPROM-a. 255 je oznaka za kraj -> kod pisanja u EEPROM vrednost 255 zameniti sa 254
// - prikazivanje tih vrednosti na display, eventualno dodati vracanje vrednosti kao rezultat
// - brisanje vrednosti sa EEPROM-a -> postavljanje bajtova na 255, sve dok se ne naidje na 255
// - pisanje u EEPROM pocevsi od neke adrese (ne mora biti 0)
// - napraviti od ovoga nekakvu biblioteku i mozda je okaciti na GitHub


#include <EEPROM.h>

#include <TM1637Display.h>
TM1637Display display(4, 3); // (CLK, DIO)

void setup()
{
  display.setBrightness (2);
  delay(1000);
  EEPROM.write(1, 8);
  display.showNumberDec(EEPROM.length());
  delay(1000);
  display.showNumberDec(EEPROM.read(1));
  while (1)
    ;
}

void loop()
{

}
