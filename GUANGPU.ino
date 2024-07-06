#include <Wire.h>

#include <AS726X.h>

#include <Arduino.h>



AS726X spectralSensor;
#define LED_PIN 2 

// 定义 AS726X 的 I2C 地址
#define AS726X_ADDR 0x49

void setup() {
  Serial.begin(9600);
  while (!Serial) {}  // 等待串口连接
  pinMode(LED_PIN, OUTPUT);
  Wire.begin();
  
  // 初始化 AS726X 光谱传感器
  spectralSensor.begin(Wire, AS726X_ADDR);
  
  if (spectralSensor.begin()) {
    Serial.println("AS726X initialization complete");
  } else {
    Serial.println("Failed to initialize AS726X!");
  }
}

void loop() {
  // 打开光源，采集测量数据，关闭光源
  spectralSensor.enableBulb();
  spectralSensor.takeMeasurements();
  spectralSensor.disableBulb();

  // 打印所有通道的测量值
  Serial.print("V: ");
  Serial.print(spectralSensor.getCalibratedViolet());
  Serial.print(", B: ");
  Serial.print(spectralSensor.getCalibratedBlue());
  Serial.print(", G: ");
  Serial.print(spectralSensor.getCalibratedGreen());
  Serial.print(", Y: ");
  Serial.print(spectralSensor.getCalibratedYellow());
  Serial.print(", O: ");
  Serial.print(spectralSensor.getCalibratedOrange());
  Serial.print(", R: ");
  Serial.println(spectralSensor.getCalibratedRed());

  // 等待一段时间再进行下一次采集
  delay(1000);
}