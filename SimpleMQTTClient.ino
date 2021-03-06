#include "EspMQTTClient.h"
#include <Wire.h>  

const uint8_t MPU6050SlaveAddress = 0x68; // Select SDA and SCL pins for I2C communication 
const uint8_t scl = D1;
const uint8_t sda = D2;     // sensitivity scale factor respective to full scale setting 
        // provided  in datasheet 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131; // MPU6050 few configuration register addresses
const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;
int16_t AccelX, AccelY, AccelZ,GyroX, GyroY, GyroZ;


EspMQTTClient client(
  "gambiran",
  "haraptenang",
  "192.168.1.10",  // MQTT Broker server ip
  "Mpu6050Pubs",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void setup()
{
  Serial.begin(115200);
  Wire.begin(sda, scl);  
  MPU6050_Init();
  // Optionnal functionnalities of EspMQTTClient : 
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  client.enableLastWillMessage("Mpu6050Pubs/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  double Ax, Ay, Az, Gx, Gy, Gz;     
  Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);    
  //divide each with their sensitivity scale factor  
  Ax = (double)AccelX/AccelScaleFactor;  
  Ay = (double)AccelY/AccelScaleFactor;  
  Az = (double)AccelZ/AccelScaleFactor;  
  Gx = (double)GyroX / GyroScaleFactor;
  Gy = (double)GyroY / GyroScaleFactor;
  Gz = (double)GyroZ / GyroScaleFactor;

  // Publish a message to "acc/1"
  client.publish("acc/1", (String(Ax)+";"+String(Ay)+";"+String(Az)+";"+String(Gx)+";"+String(Gy)+";"+String(Gz)));
}

void loop()
{
  client.loop();
  onConnectionEstablished();
  delay(5000);
}

void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data)
{  
  Wire.beginTransmission(deviceAddress);  
  Wire.write(regAddress);  Wire.write(data);  
  Wire.endTransmission();   // read all 14 register
}

void Read_RawValue(uint8_t deviceAddress, uint8_t regAddress)
{  
  Wire.beginTransmission(deviceAddress);  
  Wire.write(regAddress);  
  Wire.endTransmission();  
  Wire.requestFrom(deviceAddress, (uint8_t)14);  
  AccelX = (((int16_t)Wire.read()<<8) | Wire.read());  
  AccelY = (((int16_t)Wire.read()<<8) | Wire.read());  
  AccelZ = (((int16_t)Wire.read()<<8) | Wire.read());  
  GyroX = (((int16_t)Wire.read() << 8) | Wire.read());
  GyroY = (((int16_t)Wire.read() << 8) | Wire.read());
  GyroZ = (((int16_t)Wire.read() << 8) | Wire.read()); 
}

//configure MPU6050

void MPU6050_Init()
{   
  delay(150);  
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SMPLRT_DIV, 0x07);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_1, 0x01);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_CONFIG, 0x00);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_GYRO_CONFIG, 0x00);    
  //set +/-250 degree/second full scale  
  
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_CONFIG, 0x00);   // set +/- 2g full scale   I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_FIFO_EN, 0x00);  
  I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_INT_ENABLE, 0x01);    I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SIGNAL_PATH_RESET,   0x00);   I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_USER_CTRL, 0x00);
}
