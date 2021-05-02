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

U8G2_SH1106_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /*SCL*/ PB6, /*SDA*/PB7);

//Inialisasikan Variabel Ke Nilai
unsigned long time = 0;
unsigned long preview = 0;
unsigned long interval = 983.38;
int detik = 0;
int menit = 0;
int jam = 0;

//Deklarsi Variabel
byte StateMenit = 0;
byte StateJam = 0;
byte StateSetting = 0;
byte x = 0;

void setup() {
    Serial.begin(115200); //Mengkoneksikan Serial Ke Serial Moitor Laptop Pada Baud 115200
    u8g2.begin(); 

}

void loop() {
    time = millis(); //Menjadikan variabel time sebagai millis
    if((time - preview) >= interval){
        preview = time;
        detik++;
    }
    else if(detik >= 60) 
    {
        detik = 0; //Jika variabel detik = 60, maka nilai variabel akan menjadi  0
    }
    buttonjam();
    buttonsetting();

}

void buttonsetting(){
    StateSetting = digitalRead(ButtonSetting); //Menjadikan variabel StateSetting sebagai penampung nilai ButtonSetting
    if(StateSetting == 0)
    {
        x++;
    }

    if(x > 2) {
        x = 0;
    }

    if(x == 1) {
        buttonjam(); //Memanggil variabel fungsi buttonjam
    }

    else if(x == 2) {
        buttonmenit(); // Memanggil variabel fungsi buttonmenit
    }
    
    waktu(); // Memanggil variabel fungsi waktu 

}

void buttonmenit(){
    StateMenit = digitalRead(ButtonMenit); //Menjadikan variabel StateMenit sebagai penampung nilai ButtonMenit 
    if(StateMenit == 0 || detik == 60) {
        menit+=1; //Jika Variabel StateMenit memiliki niali 1 , maka nilai variabel menit bertambah 1
    }

    if(menit >= 60) 
    {
        menit = 0; //Jika variabel menit = 60 maka menit akan menjadi 0
    }
}

void buttonjam(){
    buttonmenit();
    StateJam = digitalRead(ButtonJam); //Menjadikan variabel StateJam sebagai penampung nilai ButtonJam
    if(StateJam == 0 || menit == 60) {
        jam+=1; //Jika variabel StateJam mempunyai nilai 1, maka nilai variabel jam akan bertambah 1
    }

    if(jam >= 24) 
    {
        jam = 0; //Jika variabel jam > 23, maka jam akan menjadi 0
    }
}

void waktu(){
    char detik_str[3], menit_str[3], jam_str[3];
    strcpy(detik_str, u8x8_u8toa(detik, 2));    /* mengkonversi m untuk menjadi string dengan 2 digit */
    strcpy(menit_str, u8x8_u8toa(menit, 2)); 
    strcpy(jam_str, u8x8_u8toa(jam, 2)); 
    u8g2.firstPage();
    for(int i = 0; i < 10; i++){
        u8g2.setFont(u8g2_font_logisoso24_tn);
        u8g2.drawStr(10,46,jam_str);
        u8g2.drawStr(41,45,":");
        u8g2.drawStr(50,46,menit_str);
        u8g2.drawStr(81,45,":");
        u8g2.drawStr(90,46,detik_str); 
        u8g2.nextPage();
    }
    Serial.println("=========="); 
    Serial.println(String(jam_str) + ":" + String(menit_str) + ":" + String(detik_str));
    Serial.println("==========");     
}