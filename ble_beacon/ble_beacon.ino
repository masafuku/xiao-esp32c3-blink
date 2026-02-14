#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEAdvertising.h>

#define SERVICE_UUID "12345678-1234-1234-1234-1234567890ab"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE advertising...");

  // デバイス名（Scannerに表示される）
  BLEDevice::init("XIAO-C3-BLE");

  // サーバとサービス作成
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pService->start();

  // 広告開始
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->start();

  // デバイス名、UUIDを表示
  Serial.print("Device name: ");
  Serial.println(BLEDevice::getDeviceName().c_str());
  Serial.print("Service UUID: ");
  Serial.println(SERVICE_UUID);

  // start advetising
  Serial.println("Advertising started");
}

void loop() {
  delay(1000);
}
