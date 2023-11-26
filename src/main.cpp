#include <ArduinoBLE.h>
#include <Arduino_LSM9DS1.h>

// Declare a BLE service with UUID:
BLEService IMUservice("19B10010-E8F2-537E-4F6C-D104768A1214");
// Declare two BLE characteristics for the accelerometer and gyroscope data, both with UUIDs:
BLECharacteristic accelData("19B10011-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 20);
BLECharacteristic gyroData("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify, 20);


void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Started");

  // Initialize the BLE module
  if (!BLE.begin()) {
    // If the BLE module fails to initialize, enter an infinite loop
    while (1) {
    }
  }

  // Initialize the IMU
  if (!IMU.begin()) {
    // If the IMU fails to initialize, enter an infinite loop
    while (1) {
    }
  }

  // Set the device name and local name to "IMU"
  BLE.setDeviceName("IMU");
  BLE.setLocalName("IMU");

  // Add the service to the BLE module
  BLE.setAdvertisedService(IMUservice);

  // Add the two characteristics to the service
  IMUservice.addCharacteristic(accelData);
  IMUservice.addCharacteristic(gyroData);

  // Add the service to the BLE module
  BLE.addService(IMUservice);

  // Set the connection interval for the BLE connection
  BLE.setConnectionInterval(8, 8);

  // Enable the BLE module to be connectable
  BLE.setConnectable(true);

  // Start advertising the BLE connection
  BLE.advertise();
}

void loop() {
  float acX, acY, acZ, gX, gY, gZ;

  // Get the connected BLE central device
  BLEDevice central = BLE.central();
  Serial.println("Got connected central BLE device");
  if (central) {
    // If there is a connected BLE central device, enter an infinite loop
    Serial.println("Connected to central BLE device");
    while (central.connected()) {
      // Read the accelerometer data from the IMU device
      IMU.readAcceleration(acX, acY, acZ);

      // Create a string with the accelerometer data
      String accelString = String(acX) + "," + String(acY) + "," + String(acZ);

      // Write the accelerometer data to the BLE characteristic
      accelData.writeValue(accelString.c_str());

      // Read the gyroscope data from the IMU device
      IMU.readGyroscope(gX, gY, gZ);

      // Create a string with the gyroscope data
      String gyroString = String(gX) + "," + String(gY) + "," + String(gZ);

      // Write the gyroscope data to the BLE characteristic
      gyroData.writeValue(gyroString.c_str());

      // Wait 7 milliseconds before sending the next data
      delay(1000);
    }
  }
}