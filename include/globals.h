#ifndef __GLOBALS_H__
#define __GLOBALS_H__

//==============================================================
//                  Global Values
//==============================================================
struct structGlobalValues{
  double TempSetValue; //PID SetPoint
  // bool   SetPointEditMode;
  // bool PIDactive;
  double TempValue;    //PID Input
  double Pid_Percent;  //PID OutPut in percent
} globalValues;

#define EEPROM_KEY    945487320 //4 bytes
struct structConfigValues {
  unsigned int key;
  double TempSetValue; //PID SetPoint

  struct {
    double consKp;
    double consKi;
    double consKd;
    uint8_t Gap4BoostParameter;
    double boostKp;
    double boostKi;
    double boostKd;
  } PID;

  struct {
    uint8_t TempMinError;
    uint8_t TempStabilizingTime;
    double Preinfusion_Duration;
    double Preinfusion_PumpDuration;
    double Brewing_Duration;
    uint8_t BrewingTempSetpointIncrease;
    double Flush_Duration;
  } stateMaschine;

} configValues;


#ifdef ESP32
#define EEPROM_SIZE     1024

void getConfiguration() {

  structConfigValues buffer;

  EEPROM.begin(EEPROM_SIZE);
  EEPROM.get( 0, buffer);

  if(buffer.key == EEPROM_KEY) {
    memcpy(&configValues, &buffer, sizeof(structConfigValues));
    Serial.print("Configuration loaded from EEPROM. (");Serial.print(configValues.key); Serial.println(")");

  } else {  // Use Default Values
    Serial.print("Default configuration is used. (");Serial.print(configValues.key); Serial.println(")");
  }

  globalValues.TempValue        = configValues.TempSetValue; //&Pid_Input;
  globalValues.Pid_Percent      = 0; //&Pid_Percent;
}

void saveConfiguration() {

  configValues.key        = EEPROM_KEY;
  configValues.TempSetValue  = globalValues.TempSetValue;

  EEPROM.put(0, configValues);
  EEPROM.commit();
  Serial.print("Configuration safed (");Serial.print(configValues.key); Serial.println(")");
}

void removeConfiguration() {
  configValues.key = 0;
  EEPROM.put(0, configValues);
  EEPROM.commit();
}
#else
  void getConfiguration() {}
  void saveConfiguration() {}
  void removeConfiguration() {}
#endif

#endif
