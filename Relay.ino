#define relay 25

void setup()
{
    Serial.begin(9600);
    pinMode(relay, OUTPUT);
}

void loop()
{
    digitalWrite(relay, HIGH);
    delay(5000);
    digitalWrite(relay, LOW);
    delay(2000);
}