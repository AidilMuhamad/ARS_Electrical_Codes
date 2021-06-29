#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DATA_PIN 23
#define CLK_PIN 18
#define CS_PIN 5

const char *ssid     = "Redmi13";
const char *password = "rahasia123";

unsigned long waktu = 0;
unsigned long preview = 0;
unsigned long epchoTime;
String Kat, les, res;
int jam, menit, tgl, bulan, tahun;
byte x = 0;

// Hardware SPI connection
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary output pins
// MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

const long utcOffsetInSeconds = 3600*7;
//area saya ada di WIB Indonesia,
//dan itu harus +7jam dari GMT
//sehingga program diatas harus dikalikan dengan 7 saja
 
char daysOfTheWeek[7][12] = {"Minggu", "Senin ", "Selasa", "Rabu  ", "Kamis ", "Jumat ", "Sabtu "};
 
//Definisi tool NTP nya
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup()
{
  Serial.begin(115200);
  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.displayClear();

  WiFi.begin(ssid, password);
 
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    myDisplay.setIntensity(0);
    myDisplay.print ("Connecting");
  }
  timeClient.begin();
}

void loop()
{
  waktu = millis();
    timeClient.update();
    epchoTime = timeClient.getEpochTime();
    jam = timeClient.getHours();
    menit = timeClient.getMinutes();
    if (timeClient.getHours() <= 9) {
      les = "0";
    }
    else{
      les = "";
    }
    if (timeClient.getMinutes() <= 9) {
      res = "0";
    }
    else{
      res = "";
    }/*
    if(timeClient.getHours() >= 00 && timeClient.getHours() <= 11){
      Kat = "AM";
    } 
    else{
      Kat = "PM";
    }*/
  struct tm *ptm = gmtime ((time_t *)&epchoTime);
  tgl = ptm->tm_mday;
  bulan = ptm->tm_mon+1;
  tahun = ptm->tm_year+1900;
  myDisplay.setTextAlignment(PA_CENTER);
  if(x == 0){
    myDisplay.print(les + String(jam) + ":" + res + String(menit));
    if(5000 <= (waktu - preview)){
      x++;
      preview = waktu;
    }
  }
  if(x == 1){
    myDisplay.print(daysOfTheWeek[timeClient.getDay()]);
    if(2000 <= (waktu - preview)){
      x++;
      preview = waktu;
    }
  }
  if(x == 2){
    String Date  = String(tgl) + "/" + String(bulan);
    myDisplay.print(Date);
    if(2000 <= (waktu - preview)){
      x++;
      preview = waktu;
    }
  }
  if(x > 2){
    x = 0;
  }
  Serial.println(timeClient.getFormattedTime());
}