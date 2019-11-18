# arduino_EEPROMing
Rad sa EEPROM memorijom na ATtiny-u

## VAZNO!
U radu sa EEPROM-om na ATtiny-u, ispostavilo se da se ta memorija cuva samo kad je chip na 8MHz.
https://arduino.stackexchange.com/questions/25080/can-you-access-the-eeprom-of-an-attiny-with-arduino-code

## TODO
+ citanje vrednosti sa EEPROM-a. 255 je oznaka za kraj -> kod pisanja u EEPROM vrednost 255 zameniti sa 254
+ prikazivanje tih vrednosti na display, eventualno dodati vracanje vrednosti kao rezultat
+ dorada: napraviti nekakav "blic" koji ce praviti razgranicenje izmedju prikaza 2 vrednosti,
    tako da bude jasno kada se prikazuju 2 ili vise istih vrednosti
/ brisanje vrednosti sa EEPROM-a -> postavljanje bajtova na 255, sve dok se ne naidje na 255
+ ValCount(int pos=0) broj upisanih vrednosti
+ pisanje u EEPROM pocevsi od neke adrese (ne mora biti 0)
+ napraviti od ovoga nekakvu biblioteku i mozda je okaciti na GitHub
