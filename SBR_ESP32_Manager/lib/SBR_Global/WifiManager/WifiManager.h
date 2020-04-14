#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


class WifiManager
{

public:
    char* m_ssid;
    char* m_password;
    char* m_hostName;

    WifiManager(char* ssid, char* password, char* hostName);
    ~WifiManager();

    void ConfigureWifi();
    void ConnectWifi();
    void WiFiEvent(WiFiEvent_t event,system_event_info_t info);

    void ConfigureOTA();
    void HandleOTA();

    //void ServerConfig(char* IP, char* PORT);

    void Run();
   


};

#endif // WIFIMANAGER_H