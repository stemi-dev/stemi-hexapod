#include <WiFi.h>
#include <Hash.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#include <Preferences.h>
#include "SharedData.h"

Preferences preferencesMain;

AsyncWebServer server(80);

bool begin = false;
int byteCounter = 0;

void initServer() {
    robot.loadName();
    char ssid[50] = "STEMI Hexapod ";
	  char nameDummy[20];
	  strcpy(nameDummy, robot.name.c_str());
    for (int i = 0; true; i++) {
        ssid[14 + i] = nameDummy[i];
        if (nameDummy[i] == '\0') {
          break;
        }
    }
    const char* password = "";
    delay(10);
    Serial.println("Configuring access point...");
    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/plain", "Hi! I am ESP32.");
    });

    AsyncElegantOTA.begin(&server);
    server.begin();
    Serial.println("HTTP server started");
}

void serverLoop() {
    AsyncElegantOTA.loop();
}

void uploadServer() {
    initServer();
    while(true) {
        serverLoop();
    }
}

void checkIsServerOn() {
    preferencesMain.begin("server-data", false);
    if (preferencesMain.getBool("isServerOn")) {
        preferencesMain.putBool("isServerOn", false);
        preferencesMain.end();
        uploadServer();
        return;
    }
    preferencesMain.end();
}

void startOtaServer() {
 	preferencesMain.begin("server-data", false);
    preferencesMain.putBool("isServerOn", true);
    preferencesMain.end();
    ESP.restart();
}

void initServer2() {
    robot.loadName();
    char ssid[50] = "STEMI Hexapod ";
	  char nameDummy[20];
	  strcpy(nameDummy, robot.name.c_str());
    for (int i = 0; true; i++) {
        ssid[14 + i] = nameDummy[i];
        if (nameDummy[i] == '\0') {
          break;
        }
    }
    const char* password = "";
    delay(10);
    Serial.println("Configuring access point...");
    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(ssid, password);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);

    server.on("/", HTTP_OPTIONS, [](AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse(200);
        request->send(response);
    });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
      request->send(200, "text/plain", "Hi! I am ESP32.");
    });

    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
        int params = request->params();
        int br = 0;
        for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
            if(p->isFile()){
                Serial.printf("FILE[%s]: %s, size: %u\n", p->name().c_str(), p->value().c_str(), p->size());
            } else if(p->isPost()){
                Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
            } else {
                Serial.printf("GET[%s]: %s\n", p->name().c_str(), p->value().c_str());
                robot.data[br] = p->value().c_str();
                br++;
            }
        }
        robot.dataCounter = br;
        AsyncWebServerResponse *response = request->beginResponse_P(200, "text/plain", "Ok.");
        request->send(response);
    });

    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT");
    DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");
    server.begin();
    Serial.println("HTTP server started");
}