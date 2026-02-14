#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

const char* targetName = "MyTag";   // iPhoneで設定した名前
int rssiThreshold = -65;            // 近いと判定するRSSI

BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {

    if (advertisedDevice.haveName()) {

      String name = advertisedDevice.getName().c_str();

      if (name == targetName) {

        int rssi = advertisedDevice.getRSSI();

        Serial.print("Found: ");
        Serial.print(name);
        Serial.print("  RSSI: ");
        Serial.println(rssi);

        if (rssi > rssiThreshold) {
          Serial.println(">>> NEAR <<<");
        }
      }
    }
  }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE scan...");

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);     // より詳細取得
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {
  pBLEScan->start(2, false);   // 2秒スキャン
  delay(500);
}