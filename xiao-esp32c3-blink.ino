// XIAO ESP32-C3 Blink Sample

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(115200);
    Serial.println("XIAO ESP32-C3 Blink Example");
}

void loop() {
    Serial.println("Blinking LED...");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}
