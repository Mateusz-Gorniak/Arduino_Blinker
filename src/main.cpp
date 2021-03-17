#include <Arduino.h>

bool isButtonPressed(int pinButton);

int main()
{
  DDRD |= 0b00111100; // setting PORTD GPIOs as output
  DDRD &= ~((1 << PD6) | (1 << PD7));
  PORTD |= (1 << PD6) | (1 << PD7); //pullup resistors
  //PORTD |= (1 << PD5) | (1 << PD4) | (1 << PD3) | (1 << PD2);

  while (1)
  {
    if (isButtonPressed(PD6))
    {
      PORTD ^= (1 << PD2);
    }
    if (isButtonPressed(PD7))
    {
      PORTD ^= (1 << PD3);
    }
  }
}
bool isButtonPressed(int pinButton)
{
  if (!(PIND & (1 << pinButton)))
  {
    _delay_ms(50);
    if (!(PIND & (1 << pinButton)))
    {
      _delay_ms(200);
      return true;
    }
  }
  return false;
}