#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define SEALEVELPRESSURE_HPA (1034.25) 

Adafruit_BME280 bme; // Création objet "bme" pour le capteur température

int incomingByte = 0; // for incoming serial data


#define ADAFRUIT_CC3000_IRQ   3  // Pin interruption pour Serial3
#define ADAFRUIT_CC3000_VBAT  47 // Pin Enable 
#define ADAFRUIT_CC3000_CS    45 // Pin ChipSelect

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                         SPI_CLOCK_DIVIDER); // Initialisation du module Weather

#define WLAN_SSID       "COUCOU"           
#define WLAN_PASS       ""  

// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data 
// received before closing the connection.  If you know the server
// you're accessing is quick to respond, you can reduce this value.

uint32_t ip;


 /******************************************************************************************/

void setup(void)
{
  unsigned status;
  status = bme.begin(0x76); //Démarrage du Weather en I2C

  Serial1.begin(115200); //Démarrage des liaisons série
  Serial.begin(115200);
  Serial.println(F("Hello, CC3000!\n"));

  Serial.print("Free RAM: "); Serial.println(getFreeRam(), DEC);

  /* Initialise the module */
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while (1);
  }


  Serial.print(F("\nAttempting to connect to ")); Serial.println(WLAN_SSID);
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    Serial.println(F("Failed!"));
    while (1);
  }

  Serial.println(F("Connected!"));

  /* Wait for DHCP to complete */
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }

  /* Display the IP address DNS, Gateway, etc. */
  while (! displayConnectionDetails()) {
    delay(1000);
  }

  ip = cc3000.IP2U32(192, 168, 4, 1); //Définition ip static du site à visiter
  // Try looking up the website's IP address
  /*Serial.print(WEBSITE); Serial.print(F(" -> "));
  while (ip == 0) {
    if (! cc3000.getHostByName(WEBSITE, &ip)) {
      Serial.println(F("Couldn't resolve!"));
    }
    delay(500);
  }*/

  cc3000.printIPdotsRev(ip); //Affichage de l'IP

  // Optional: Do a ping test on the website
  /*
    Serial.print(F("\n\rPinging ")); cc3000.printIPdotsRev(ip); Serial.print("...");
    replies = cc3000.ping(ip, 5);
    Serial.print(replies); Serial.println(F(" replies"));
  */

  /* Try connecting to the website.
     Note: HTTP/1.1 protocol is used to keep the server from closing the connection before all data is read.
  */




  

//  Serial.println(F("-------------------------------------"));
//
//  /* Read data until either the connection is closed, or the idle timeout is reached. */
//  unsigned long lastRead = millis();
//  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
//    while (www.available()) {
//      char c = www.read();
//      Serial.print(c);
//      lastRead = millis();
//    }
//  }
//  
//  Serial.println(F("-------------------------------------"));
//
//  /* You need to make sure to clean up after yourself or the CC3000 can freak out */
//  /* the next time your try to connect ... */
//  Serial.println(F("\n\nDisconnecting"));

}

void loop(void)
{
  float P=0;
  float A=0;
  float H=0;
  float T=0;
  String P1;
  String H1;
  String T1;
  String A1;
  //Serial.println("Test");
  if (Serial1.available() > 0) { //Attente de réception d'un caractère sur Serial1
    // read the incoming byte:
    incomingByte = Serial1.read(); //Lecture du caractère reçu sur Serial1
    
   

    if (incomingByte == 1) { // Pression
      Serial.print("Pression = ");
      Serial.print(bme.readPressure() / 100.0F);
      Serial.println(" hPa");
      P=bme.readPressure()/100.0F;
      

      /*Envoie des données vers un autre appareil du réseau*/
      Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 8000);
       if (www.connected()) {
        //www.print("P=");
        P1 = String(P);
        P1="P="+P1;
        www.print(P1);
        //www.print(bme.readPressure()/100.0F);
        www.print("\r\n");
      } else {
        Serial.println(F("Connection failed"));
        return;
      }
      www.close();
      

    }
    if (incomingByte == 2) { // Altitude
      Serial.print("Approx. Altitude = ");
      Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
      Serial.println(" m");

      
      Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 8000);
       if (www.connected()) {
        A=bme.readAltitude(SEALEVELPRESSURE_HPA);
        A1= String(A);
        A1="A="+A1;
        www.print(A1);
        //www.print(A);
        www.print("\r\n");
        //www.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
      } else {
        Serial.println(F("Connection failed"));
        return;
      }
      www.close();
    }
    if (incomingByte == 3) { // Humidité
      Serial.print("Humidité = ");
      Serial.print(bme.readHumidity());
      Serial.println(" %");

      
      Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 8000);
       if (www.connected()) {
        //www.print("H=");
        H=bme.readHumidity();
        H1=String(H);
        H1="H="+H1;
        www.print(H1);
        www.print("\r\n");
      } else {
        Serial.println(F("Connection failed"));
        return;
      }
      www.close();
    }
    if (incomingByte == 4) { // Température
      Serial.print("Température = ");
      Serial.print(bme.readTemperature());
      Serial.println(" *C");
      //consumer_key = String("CPCPU");

      
      Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 8000);
       if (www.connected()) {
        //www.print("t=");
        T=bme.readTemperature();
        T1=String(T);
        T1="T="+T1;
        www.print(T1);
        www.print("\r\n");
      } else {
        Serial.println(F("Connection failed"));
        return;
      }
      www.close();
    }

    if (incomingByte == 5) { // Quel temps fait-il ?
      Serial.print("\n\rTempérature = ");
      Serial.print(bme.readTemperature());
      Serial.print("\n\rPression = ");
      Serial.print(bme.readPressure() / 100.0F);
      Serial.print("\n\rHumidité = ");
      Serial.print(bme.readHumidity());
      //consumer_key = String("CPCPU");

      
      Adafruit_CC3000_Client www = cc3000.connectTCP(ip, 8000);
       if (www.connected()) {
        www.print("\nT=");
        www.println(bme.readTemperature());
        www.print("\n");
        www.print("\nP=");
        www.println(bme.readPressure()/100.0F);
        www.print("\n");
        www.print("\nH=");
        www.println(bme.readHumidity());
        www.print("\n");
        www.print("\nA=");
        www.println(bme.readAltitude(SEALEVELPRESSURE_HPA));
      } else {
        Serial.println(F("Connection failed"));
        return;
      }
      www.close();
    }
  }
}



/**************************************************************************/
/*!
    @brief  Tries to read the IP address and other connection details
*/
/**************************************************************************/
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;

  if (!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}
