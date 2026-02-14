// XIAO ESP32-C3 シリアルテストスケッチ
void setup() {
  Serial.begin(115200);       // シリアル開始
  // シリアルが接続されるまで待つ（USB接続が安定するまで）
  while (!Serial) {
    delay(10);
  }
  Serial.println("=== XIAO ESP32-C3 Serial Test Start ===");
}

void loop() {
  Serial.println("Loop running...");
  delay(1000);  // 1秒ごとに出力
}
