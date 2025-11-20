#pragma once
#include <Arduino.h>
#include <AsyncUDP.h>
#include <LittleFS.h>
#include <esp_system.h>
// #include <WebServer.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>
#include <ESPAsyncWebServer.h>

#include "AlpacaHelpers.h"
#include "config.h"

// Lambda Handler Function for calling object function
#define LHF(method) \
    (ArRequestHandlerFunction)[this](AsyncWebServerRequest * request) { this->method(request); }

// Forward declare AlpacaDevice to avoid circular includes
class AlpacaDevice;

class AlpacaServer {
  private:
    // Logger println
    std::function<void(String)> logLine = NULL;
    // Logger print
    std::function<void(String)> logLinePart = NULL;
    // Logger time function
    std::function<String()> logTime = NULL;

    AsyncWebServer *_serverTCP;
    AsyncUDP _serverUDP;
    uint16_t _portTCP;
    uint16_t _portUDP;
    volatile int _serverTransactionID = 0;
    int _serverID;
    char _uid[13];
    char _name[32];
    char _version[32] = "";
    char _build_date[32] = "";
    AlpacaDevice *_device[ALPACA_MAX_DEVICES];
    int _n_devices = 0;

    void _registerCallbacks();
    void _getApiVersions(AsyncWebServerRequest *request);
    void _getDescription(AsyncWebServerRequest *request);
    void _getConfiguredDevices(AsyncWebServerRequest *request);
    int _paramIndex(AsyncWebServerRequest *request, const char *name);
    void _readJson(JsonObject &root);
    void _writeJson(JsonObject &root);
    void _getJsondata(AsyncWebServerRequest *request);
    void _getLinks(AsyncWebServerRequest *request);

    String _ipReadable(IPAddress address);

  public:
    // Print a log message, can be overwritten
    virtual void logMessage(String msg, bool showtime = true);
    // Print a part of log message, can be overwritten
    virtual void logMessagePart(String msg, bool showtime = false);
    // Set current logger
    void setLogger(std::function<void(String)> logLineCallback = NULL, std::function<void(String)> logLinePartCallback = NULL, std::function<String()> logTimeCallback = NULL);

    AlpacaServer(const char *name, const char *version = "", const char *build_date = "");
    void begin(uint16_t udp_port, uint16_t tcp_port);
    void beginTcp(AsyncWebServer *tcp_server, uint16_t tcp_port);
    void beginUdp(uint16_t udp_port);
    void addDevice(AlpacaDevice *device);
    bool getParam(AsyncWebServerRequest *request, const char *name, bool &value);
    bool getParam(AsyncWebServerRequest *request, const char *name, float &value);
    bool getParam(AsyncWebServerRequest *request, const char *name, int &value);
    bool getParam(AsyncWebServerRequest *request, const char *name, char *buffer, int buffer_size);
    void respond(AsyncWebServerRequest *request, bool value, int32_t error_number = 0, const char *error_message = "");
    void respond(AsyncWebServerRequest *request, int value, int32_t error_number = 0, const char *error_message = "");
    void respond(AsyncWebServerRequest *request, float value, int32_t error_number = 0, const char *error_message = "");
    void respond(AsyncWebServerRequest *request, const char *value, int32_t error_number = 0, const char *error_message = "");
    bool loadSettings();
    bool saveSettings();
    void onAlpacaDiscovery(AsyncUDPPacket &udpPacket);
    AsyncWebServer *getServerTCP() { return _serverTCP; }
    const char *getUID() { return _uid; }
};
