#include "BleOta.h"

#define SERVICE_UUID_ESPOTA        "d804b643-6ce7-4e81-9f8a-ce0f699085eb"

#define SERVICE_UUID_OTA                    "651707bb-61f7-4338-b5a9-c36e02c8e2f1" // UART service UUID
#define CHARACTERISTIC_UUID_FW              "9c2f0ede-7162-4504-8ecf-e0a2357d20f5"

#define FULL_PACKET 512
#define CHARPOS_UPDATE_FLAG 5


esp_ota_handle_t otaHandler = 0;

bool updateFlag = false;
bool readyFlag = false;
int bytesReceived = 0;
int timesWritten = 0;

void otaCallback::onWrite(BLECharacteristic *pCharacteristic)
{
  std::string rxData = pCharacteristic->getValue();
  if (!updateFlag) { //If it's the first packet of OTA since bootup, begin OTA
    Serial.println("BeginOTA2");
    esp_ota_begin(esp_ota_get_next_update_partition(NULL), OTA_SIZE_UNKNOWN, &otaHandler);
    updateFlag = true;
  }
  if (_p_ble != NULL)
  {
    if (rxData.length() > 0)
    {
      esp_ota_write(otaHandler, rxData.c_str(), rxData.length());
      if (rxData.length() != FULL_PACKET)
      {
        esp_ota_end(otaHandler);
        Serial.println("EndOTA");
        if (ESP_OK == esp_ota_set_boot_partition(esp_ota_get_next_update_partition(NULL))) {
          delay(2000);
          esp_restart();
        }
        else {
          Serial.println("Upload Error");
        }
      }
    }
  }

  uint8_t txData[5] = {1, 2, 3, 4, 5};
  //delay(1000);
  pCharacteristic->setValue((uint8_t*)txData, 5);
  pCharacteristic->notify();
}

//
// Constructor
BLE::BLE(void) {

}

//
// Destructor
BLE::~BLE(void)
{

}

//
// begin
bool BLE::begin(const char* localName = "UART Service") {
  // Create the BLE Device
  BLEDevice::init(localName);

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new BLECustomServerCallbacks());

  pService = pServer->createService(SERVICE_UUID_OTA);

  pOtaCharacteristic = pService->createCharacteristic(
                         CHARACTERISTIC_UUID_FW,
                         BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_WRITE
                       );

  BLEDescriptor *pClientCharacteristicConfigDescriptor = new BLEDescriptor((uint16_t)0x2902);
  pOtaCharacteristic->addDescriptor(pClientCharacteristicConfigDescriptor);
  pOtaCharacteristic->setCallbacks(new otaCallback(this));

  // Start the service(s)
  pService->start();

  // Start advertising
  pServer->getAdvertising()->addServiceUUID(SERVICE_UUID_ESPOTA);

  pServer->getAdvertising()->setScanResponse(true);
  pServer->getAdvertising()->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  //pServer->getAdvertising()->setMinPreferred(0x12);
  pServer->getAdvertising()->start();

  uint8_t hardwareVersion[5] = {HARDWARE_VERSION_MAJOR, HARDWARE_VERSION_MINOR, SOFTWARE_VERSION_MAJOR, SOFTWARE_VERSION_MINOR, SOFTWARE_VERSION_PATCH};

  return true;
}
