#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

const int I2C_SDA_PIN = 6;
const int I2C_SCL_PIN = 7;
const uint8_t MPU6060_ADDRESS = 0x68;

// 50Hz sample rate = 20 milliseconds between reads
const uint32_t INTERVAL_MS = 20;
uint32_t lastReadAt = 0;

Adafruit_MPU6050 mpu;

void steup() {
  Serial.begin(115200);

  // Wait for the serial monitor to connect before starting
  while (!Serial) delay(10);

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  if (!mpu.begin(MPU6050_ADDRESS, &Wire)) {
    Serial.println("MPU6050 not found. Check wiring.")
    while (1) {
      delay(10);
    }
  }

  // Match the ranges to the original Starbie firmware
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  // Print the CSV header for the Edge Impulse CLI
  Serial.println("ax,ay,az,gx,gy,gz");
}

void loop() {
  uint32_t now = millis();

  if (now - lastReadAt >= INTERVAL_MS) {
    lastReadAt = now

    sensor_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Print raw data as comma separated values
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print(a.acceleration.y);
    Serial.print(",");
    Serial.print(a.acceleration.x);
    Serial.print(",");
    Serial.print(g.gyro.x);
    Serial.print(",");
    Serial.print(g.gyro.y);
    Serial.print(",");
    Serial.println(g.gyro.z);
  }
}
