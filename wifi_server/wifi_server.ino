#include <WiFi.h>

// --- WiFi設定 ---

//const char* ssid     = "TP-Link_7392";         // ←自宅WiFiに変更
//const char* password = "59258056"; // ←自宅WiFiに変更
const char* ssid     = "TP-Link_7392_Guest";         // ←自宅WiFiに変更
const char* password = "pochipochi"; // ←自宅WiFiに変更
//const char* ssid     = "masaki's iPhone v3";         // ←自宅WiFiに変更
//const char* password = "kumanopusan"; // ←自宅WiFiに変更

WiFiServer server(80);  // ポート80でサーバー起動

// --- LED用ピン（外部LED接続の場合） ---
const int ledPin = LED_BUILTIN; // 内蔵LEDは赤LEDなので点滅確認用に外部LEDを使うこと推奨


// Convert WiFi status to human-readable string
const char* getWiFiStatusString(wl_status_t status) {
  switch (status) {
    case WL_CONNECTED:      return "WL_CONNECTED (3) - Connected";
    case WL_NO_SSID_AVAIL:  return "WL_NO_SSID_AVAIL (2) - SSID Not Found";
    case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED (4) - Auth Failed";
    case WL_IDLE_STATUS:    return "WL_IDLE_STATUS (0) - Idle";
    case WL_DISCONNECTED:   return "WL_DISCONNECTED (6) - Disconnected";
    default:                return "UNKNOWN_STATUS";
  }
}

void setup() {
  // シリアル初期化
  Serial.begin(115200);
  delay(1000); // 書き込み直後でも出力確認できるように少し待つ

  // LEDピン初期化
  pinMode(ledPin, OUTPUT);


  Serial.println("Starting Wi-Fi scan...");

  // Wi-Fiスキャン実行
  int n = WiFi.scanNetworks();
  Serial.printf("Found %d networks:\n", n);

  for (int i = 0; i < n; i++) {
    Serial.printf("%d: SSID: %s, RSSI: %d dBm, Channel: %d\n",
                  i + 1,
                  WiFi.SSID(i).c_str(),
                  WiFi.RSSI(i),
                  WiFi.channel(i));
  }

  Serial.println("Scan complete.");

  // WiFi接続
  Serial.println("Starting XIAO ESP32-C3 WiFi server demo...");
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // 接続待ち
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Attempting connection, status: ");
    Serial.print(WiFi.status());  // 接続状況のコードを表示
    Serial.println(getWiFiStatusString(WiFi.status()));
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

    // 受信リクエストを読み飛ばす（ブラウザは最初にGETリクエストを送信します）
    while (client.connected() && client.available()) {
      String line = client.readStringUntil('\n');
      //Serial.println(line); // デバッグ用
    }

    // HTTPレスポンス送信
    client.print("HTTP/1.1 200 OK\r\n");
    client.print("Content-Type: text/html\r\n");
    client.print("Connection: close\r\n");  // ブラウザに切断を通知
    client.print("\r\n");                  // ヘッダ終わりの空行
    client.print("<!DOCTYPE html><html><body>");
    client.print("<h1>Hello from XIAO ESP32-C3!</h1>");
    client.print("<p>This is a test page.</p>");
    client.print("</body></html>\r\n");
    
    delay(1);
    client.stop();
    Serial.println("Client disconnected");
  }
}