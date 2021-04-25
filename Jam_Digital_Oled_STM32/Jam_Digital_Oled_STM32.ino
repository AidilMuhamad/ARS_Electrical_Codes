//Deklarasi Library
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//Inialisasikan PIN Ke Variabel
#define ButtonMenit PB3
#define ButtonJam PB4
#define ButtonSetting PB5

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, PB6, PB7);

//Inialisasikan Variabel Ke Nilai
unsigned long time = 0;
unsigned long preview = 0;
unsigned long interval = 50;
int detik = 0;
int menit = 0;
int jam = 0;

//Deklarsi Variabel
byte StateMenit, StateJam, StateSetting, x;

void setup() {
    Serial.begin(115200); //Mengkoneksikan Serial Ke Serial Moitor Laptop Pada Baud 115200
    u8g2.begin(); 

}

void loop() {
    StateMenit = digitalRead(ButtonMenit);
    StateJam = digitalRead(ButtonJam);
    StateSetting = digitalRead(ButtonSetting);
    time = millis();
    if((time - preview) >= interval){
        preview = time;
        detik++;
    }

    if(x == 2) {
        buttonmenit();
    }
    else if(x == 1) {
        buttonjam();
    }
    else{
        waktu();
    }

    if(x > 2) x = 0;

}


void buttonjam(){
    if(StateJam == 1) {
        jam++;
    }
    else if(menit == 60) 
    {
        menit = 0;
        jam++;
    }
    else if(jam < 23) 
    {
        jam = 0;
    }
}

void buttonmenit(){
    if(StateMenit == 1) {
        menit++;
    }
    else if(detik == 60) 
    {
        menit++;
        detik = 0;
    }
}

void waktu(){
    char detik_str[3], menit_str[3], jam_str[3];
    strcpy(detik_str, u8x8_u8toa(detik, 2));    /* mengkonversi m untuk menjadi string dengan 2 digit */
    strcpy(menit_str, u8x8_u8toa(menit, 2)); 
    strcpy(jam_str, u8x8_u8toa(jam, 2)); 
    u8g2.firstPage();
    u8g2.setFont(u8g2_font_logisoso24_tn);
    u8g2.drawStr(10,53,jam_str);
    u8g2.drawStr(40,53,":");
    u8g2.drawStr(50,53,menit_str);
    u8g2.drawStr(80,53,":");
    u8g2.drawStr(90,53,detik_str); 
    u8g2.nextPage();
    Serial.println("=========="); 
    Serial.println(String(jam_str) + ":" + String(menit_str) + ":" + String(detik_str));
    Serial.println("==========");     
}