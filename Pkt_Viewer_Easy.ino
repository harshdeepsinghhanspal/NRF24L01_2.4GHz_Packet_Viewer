#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

RF24 radio(9, 10); // CE, CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
}

void loop() {
  if (radio.available()) {
    uint8_t data;
    radio.read(&data, sizeof(data));
    Serial.println(data);

    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Signal Intensity:");
    display.setTextSize(2);
    display.println(data);
    display.display();
  }
}
