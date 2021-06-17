#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN    5

// Hardware SPI connection
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary output pins
// MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup(void)
{
  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.displayClear();
  myDisplay.displayText("Text Berjalan", PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop(void)
{
  if(myDisplay.displayAnimate()){
    myDisplay.displayReset();
    myDisplay.setTextAlignment(PA_CENTER);
    myDisplay.print("Center");
    delay(1000);
    myDisplay.setTextAlignment(PA_LEFT);
    myDisplay.print("Left");
    delay(1000);
    myDisplay.setTextAlignment(PA_RIGHT);
    myDisplay.print("Right");
    delay(1000);
    myDisplay.setTextAlignment(PA_CENTER);
    myDisplay.setInvert(true);
    myDisplay.print("Invert");
    delay(1000);
    myDisplay.setInvert(false);
    myDisplay.print(1234);
    delay(1000);
  }
}