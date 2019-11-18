// Primer koriscenja metoda klase EEPROMing

#include <EEPROMing.h>

void setup()
{
  EEPROMing ee;
  ee.SetWritePos(100);
  ee.Write(123);
  ee.Write(8);
  ee.Write(8);
  ee.Write(255);
  ee.MemToDisplay(101);
  delay(1000);
  ee.GetDisplay()->showNumberDec(ee.GetWritePos());
}

void loop()
{
}
