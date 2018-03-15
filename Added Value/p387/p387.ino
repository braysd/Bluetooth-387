#include <PololuLedStrip.h>

// Create an ledStrip object and specify the pin it will use.
PololuLedStrip<11> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 60
rgb_color colors[LED_COUNT];

int LEDnum;

void setup()
{
  // Start up the serial port, for communication with the PC.
  Serial.begin(115200);
  Serial.println("Type num,r,g,b");
}

void loop()
{
  // If any digit is received, we will go into integer parsing mode
  // until all three calls to parseInt return an interger or time out.
  if (Serial.available())
  {
    char c = Serial.peek();
    if(c == 'z') //clear LEDs
    {
      rgb_color off; //all colors off
      off.red = 0;
      off.green = 0;
      off.blue = 0;

      // Update the colors buffer.
      for(int i = 0; i < LED_COUNT; i++)
        {
          colors[i] = off;
        }
    }
    else if(c == 'x'){ //x denotes change all colors
      if (!(c >= '0' && c <= '9'))
      {
        Serial.read(); // Discard non-digit character
      }
      else
      {
        // Read the color from the computer.
        rgb_color LED_color;
        LED_color.red = Serial.parseInt();
        LED_color.green = Serial.parseInt();
        LED_color.blue = Serial.parseInt();
  
        // Update the colors buffer.
        for(int i = 0; i < LED_COUNT; i++)
        {
          colors[i] = LED_color;
        }
  
        // Write to the LED strip.
        ledStrip.write(colors, LED_COUNT);
  
        Serial.print("Showing color: ");
        Serial.print(LED_color.red);
        Serial.print(",");
        Serial.print(LED_color.green);
        Serial.print(",");
        Serial.println(LED_color.blue);
      }
    }
    else if (!(c >= '0' && c <= '9'))
    {
      Serial.read(); // Discard non-digit character
    }
    else
    {
      // Read the color from the computer.
      rgb_color color;
      LEDnum = Serial.parseInt(); //LED to change
      color.red = Serial.parseInt();
      color.green = Serial.parseInt();
      color.blue = Serial.parseInt();

      // Update the colors buffer.
      if (LEDnum > -1 && LEDnum < LED_COUNT)
      {
        colors[LEDnum] = color;
      }

      // Write to the LED strip.
      ledStrip.write(colors, LED_COUNT);

      Serial.print("Showing color: ");
      Serial.print(color.red);
      Serial.print(",");
      Serial.print(color.green);
      Serial.print(",");
      Serial.println(color.blue);
    }
  }
}
