// Citanje EEPROM memorije sa ATtiny85.
// VAZNO! U radu sa EEPROM-om na ATtiny-u, ispostavilo se da se ta memorija cuva samo kad je chip na 8MHz.
// https://arduino.stackexchange.com/questions/25080/can-you-access-the-eeprom-of-an-attiny-with-arduino-code
// + citanje vrednosti sa EEPROM-a. 255 je oznaka za kraj -> kod pisanja u EEPROM vrednost 255 zameniti sa 254
// + prikazivanje tih vrednosti na display, eventualno dodati vracanje vrednosti kao rezultat
//  - dorada: napraviti nekakav "blic" koji ce praviti razgranicenje izmedju prikaza 2 vrednosti,
//  tako da bude jasno kada se prikazuju 2 ili vise istih vrednosti
// / brisanje vrednosti sa EEPROM-a -> postavljanje bajtova na 255, sve dok se ne naidje na 255
// + ValCount(int pos=0) broj upisanih vrednosti
// + pisanje u EEPROM pocevsi od neke adrese (ne mora biti 0)
// - napraviti od ovoga nekakvu biblioteku i mozda je okaciti na GitHub

#include <EEPROM.h>

#include <TM1637Display.h>
TM1637Display display(4, 3); // (CLK, DIO)

#define EEPROM_END 255

// Citanje EEPROM memorije od pozicije start sve do EEPROM_END i prikaz tih vrednosti na TM1637 sa itvDelay delay-em.
void MemToDisplay(int itvDelay = 1000, int start = 0)
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

// Vraca broj upisanih vrednosti od start sve do prve EEPROM_END ili kraja EEPROM memorije.
int ValCount(int start = 0)
{
  int i = start;
  int n = EEPROM.length();
  while (i < n)
    if (EEPROM.read(i++) == EEPROM_END)
      break;
  return (i - 1) - start;
}

int idx = 0;
// Pise vrednost val u EEPROM (na idx poziciji). Vraca true ako je idx < EEPROM.length()
bool Write(int val)
{
  int n = EEPROM.length();
  if (idx < n)
  {
    EEPROM.write(idx++, val);                      // upisivanje date vrednosti val
    if (idx < n && EEPROM.read(idx) != EEPROM_END) // ako na sledecoj poziciji nije EEPROM_END, upisati to
      EEPROM.write(idx, EEPROM_END);               // za slucaj da je ovo poslednji upis pa da se zna da je tu kraj
    return true;
  }
  else
    return false;
}

void setup()
{
  display.setBrightness(2);
  // Write(3);
  // Write(2);
  // MemToDisplay();
  // display.showNumberDec(ValCount());
}

void loop()
{
}
