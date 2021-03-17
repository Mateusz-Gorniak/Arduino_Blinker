#include <Arduino.h>
#include <avr/io.h>

//Function declatration
bool isButtonPressed(uint16_t pinButton);
void digitalToggle(uint16_t pinButton);
//Global variables declaration
uint32_t Time = 1000; // miliseconds
uint32_t previous_millis;
long int presentTime;

int main()
{
  init();
  Serial.begin(9600);
  DDRD |= 0b00111100; // setting PORTD GPIOs as output
  DDRD &= ~((1 << PD6) | (1 << PD7));
  PORTD |= (1 << PD6) | (1 << PD7); //pullup resistors

  while (1)
  {
    // if (isButtonPressed(PD6))
    // {
    // }
    presentTime = millis();
    //Serial.println(presentTime);

    if (isButtonPressed(PD6))
    {
      Time += 50;
    }

    if (isButtonPressed(PD7))
    {
      if (Time >= 100)
      {
        Time -= 50;
      }
      else
      {
        continue;
      }
    }

    if ((presentTime - previous_millis) >= Time)
    {
      previous_millis = millis();
      digitalToggle(PD2);
      digitalToggle(PD3);
      digitalToggle(PD4);
      digitalToggle(PD5);
    }
  }
}
bool isButtonPressed(uint16_t pinButton)
{
  if (!(PIND & (1 << pinButton)))
  {
    //Simple debouncing code
    _delay_ms(50);
    if (!(PIND & (1 << pinButton)))
    {
      _delay_ms(100);
      return true;
    }
  }
  return false;
}
void digitalToggle(uint16_t pinButton)
{
  PORTD ^= (1 << pinButton);
}
