#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

int incomingByte = 0; // for incoming serial data


void setup() {

 unsigned status;

 status = bme.begin(0x76);
 Serial.begin(115200);
 Serial1.begin(115200); // opens serial port, sets data rate to 9600 bps

    //Serial.println(Serial2.available());
    // Wait for five characters
  

  Serial.println("Received data = ");

}

void loop() {
  //SPEAKUP/////////////////////////////////////////////
  if (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read();  

    if (incomingByte == 1){ // Pression
                 Serial.print("Pression = ");
                 Serial.print(bme.readPressure() / 100.0F);
                 Serial.println(" hPa");
                }
    if (incomingByte == 2){ // Altitude
                  Serial.print("Approx. Altitude = ");
                  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
                  Serial.println(" m");
                }
    if (incomingByte == 3){ // Humidité
                  Serial.print("Humidité = ");
                  Serial.print(bme.readHumidity());
                  Serial.println(" %");
                }
    if (incomingByte == 4){ // Température
                  Serial.print("Température = ");
                  Serial.print(bme.readTemperature());
                  Serial.println(" *C");
                }
  }
////////////////////////////////////////////////////////

}
