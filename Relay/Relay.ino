#define relay 25

void setup()
{
    Serial.begin(9600);
    pinMode(relay, OUTPUT);
}

void loop()
{
    digitalWrite(relay, HIGH);
    Serial.println("Lampu Hidup");
    delay(5000);
    digitalWrite(relay, LOW);
    Serial.println("Lampu Mati");
    delay(2000);
}