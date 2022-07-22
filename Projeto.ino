#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int R1 = 9845;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  TextoInicial();
  
}

void loop() {
  double resistencia, aux;
  aux = (float)analogRead(A0)/1023;
  resistencia = aux * (float) R1 / (1 - aux);
  Serial.println("O valor da resistencia é: "+ String(resistencia) + " Ω");
  ImprimeOled(resistencia);
  delay(2000);
}

void TextoInicial(void){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(10,20);             // Start at top-left corner
  display.println(F("Ohmimetro"));
  display.setCursor(20,40);
  display.println(F("Arduino"));
  display.display();
  delay(3000);
}

void ImprimeOled(float resistencia){
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(30,30);             // Start at top-left corner
  if (resistencia < 1000) {
  display.print(resistencia);
  }
  else if(resistencia < 1000000){
    display.print((resistencia/1000));
    display.print("K");
  }
  else if(resistencia < 1000000000){
    display.print((resistencia/1000000));
    display.print("M");
  }
  else
    display.println(resistencia);
  display.display();
}