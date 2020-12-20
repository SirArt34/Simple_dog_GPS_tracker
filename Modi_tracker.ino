// Karta SD
#include <SD.h>
#include <SPI.h>
const int CSPin = 10;

// GPS
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

// LEDs
#define LEDerr 6
#define LEDok 7
void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  pinMode(CSPin, OUTPUT);

  pinMode(LEDerr, OUTPUT);
  pinMode(LEDok, OUTPUT);
  
  digitalWrite(LEDerr, HIGH);
  delay(100);
  digitalWrite(LEDerr, LOW);
  digitalWrite(LEDok, HIGH);
  delay(100);
  digitalWrite(LEDok, LOW);

if (!SD.begin(CSPin))
  {
    SDerror();
    return;
  }
    SDok();
}

void loop()
{
  while (ss.available() > 0)
    if (gps.encode(ss.read())){
   
  File myFile = SD.open("GPS.txt", FILE_WRITE);
  
  if (myFile){
  myFile.print(gps.location.lat(), 6);
  myFile.print(", ");
  myFile.print(gps.location.lng(), 6);
  myFile.print(", ");
  myFile.println(gps.speed.kmph());
  myFile.print(" km/h");
  myFile.close();
 
    SDok();
  }else{
    SDerror();
  }
delay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
    }
}

void SDerror()
{
  digitalWrite(LEDerr, HIGH);
  delay(100);
  digitalWrite(LEDerr, LOW);
  delay(100);
  digitalWrite(LEDerr, HIGH);
  delay(100);
  digitalWrite(LEDerr, LOW);
  delay(100);
  digitalWrite(LEDerr, HIGH);
  delay(1000);
  digitalWrite(LEDerr, LOW);
  delay(100);
}
void SDok()
{
  digitalWrite(LEDok, HIGH);
  delay(100);
  digitalWrite(LEDok, LOW);
}
void GPSerr()
{
digitalWrite(LEDerr, HIGH);
  delay(100);
  digitalWrite(LEDerr, LOW);
  delay(100);
  digitalWrite(LEDok, HIGH);
  delay(100);
  digitalWrite(LEDok, LOW);
}
