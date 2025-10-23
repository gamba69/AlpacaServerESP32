#pragma once
#include "AlpacaDevice.h"

#define ALPACA_FOCUSER_INTERFACE_VERSION "3"

class AlpacaFocuser : public AlpacaDevice {
  protected:
    // alpaca commands
    void aGetInterfaceVersion(AsyncWebServerRequest *request);
    virtual void aGetAbsolute(AsyncWebServerRequest *request) = 0;
    virtual void aGetIsMoving(AsyncWebServerRequest *request) = 0;
    virtual void aGetMaxIncrement(AsyncWebServerRequest *request) = 0;
    virtual void aGetMaxStep(AsyncWebServerRequest *request) = 0;
    virtual void aGetPosition(AsyncWebServerRequest *request) = 0;
    virtual void aGetStepSize(AsyncWebServerRequest *request) = 0;
    virtual void aGetTempComp(AsyncWebServerRequest *request) = 0;
    virtual void aPutTempComp(AsyncWebServerRequest *request) = 0;
    virtual void aGetTempCompAvailable(AsyncWebServerRequest *request) = 0;
    virtual void aGetTemperature(AsyncWebServerRequest *request) = 0;
    virtual void aPutHalt(AsyncWebServerRequest *request) = 0;
    virtual void aPutMove(AsyncWebServerRequest *request) = 0;
    AlpacaFocuser() { strcpy(_device_type, "focuser"); }

  public:
    void registerCallbacks();
};