#include <WiFi.h>

// --- WiFi設定 ---
const char* ssid     = "あなたのSSID";         // ←自宅WiFiに変更
const char* password = "あなたのWiFiパスワード"; // ←自宅WiFiに変更

WiFiServer server(80);  // ポート80でサーバー起動

// --- LED用ピン（外部LED接続の場合） ---
const int ledPin = LED_BUILTIN; // 内蔵LEDは赤LEDなので点滅確認用に外部LEDを使うこと推奨

void setup() {
  // シリアル初期化
  Serial.begin(115200);
  delay(1000); // 書き込み直後でも出力確認できるように少し待つ
  Serial.println("Starting XIAO ESP32-C3 WiFi server demo...");

  // LEDピン初期化
  pinMode(ledPin, OUTPUT);

  // WiFi接続
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // 接続待ち
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // サーバー開始
  server.begin();
  Serial.println("Server started, waiting for clients...");
}

void loop() {
  // LEDを0.5秒周期で点滅
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);

  // クライアント接続待ち
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected");

    // HTTPレスポンス送信
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<h1>Hello from XIAO ESP32-C3!</h1>");
    client.println("<p>This is a test page.</p>");
    
    delay(1);
    client.stop();
    Serial.println("Client disconnected");
  }
}