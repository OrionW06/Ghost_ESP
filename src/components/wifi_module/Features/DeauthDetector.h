#pragma once
#include <Arduino.h>
#include "../wifi_module.h"
#include "esp_wifi_types.h" 
#include <core/globals.h>
#include <HTTPClient.h>
const int MAX_CHANNELS = 12;


struct Wifianalyticsdata {
    unsigned long deauthCount[MAX_CHANNELS];
    unsigned long authCount[MAX_CHANNELS];
    unsigned long beaconCount[MAX_CHANNELS];
    unsigned long probeReqCount[MAX_CHANNELS];
    unsigned long probeRespCount[MAX_CHANNELS];
    unsigned long otherPktCount[MAX_CHANNELS];
    unsigned long startTime[MAX_CHANNELS];
    unsigned long endTime[MAX_CHANNELS];         
    String deviceMac;
};

struct DeauthDetectorConfig
{
unsigned long deauthCount = 0;
unsigned long lastCheckTime = 0;
unsigned long lastChannelCheckTime = 0;
unsigned long startTime = 0;
unsigned long checkInterval = 1000;
unsigned long ChannelHopInterval = 5000;
unsigned long scanDuration = 2 * 60000;
unsigned long deauthThreshold = 20;
int CurrentChannel;
bool ConfigHasChannel;
Wifianalyticsdata* analyticsdata;
};

DeauthDetectorConfig Config;

void AnalyticsCallback(void* buf, wifi_promiscuous_pkt_type_t type) {
    if (type != WIFI_PKT_MGMT) return;

    const wifi_promiscuous_pkt_t *ppkt = (wifi_promiscuous_pkt_t *)buf;
    const wifi_ieee80211_packet_t_2 *ipkt = (wifi_ieee80211_packet_t_2 *)ppkt->payload;
    const wifi_ieee80211_mac_hdr_t *hdr = &ipkt->hdr;


    switch(hdr->frame_ctrl & 0xFC) { // Mask to get type and subtype only
        case 0xB0: // Authentication frame
            Config.analyticsdata->authCount[Config.CurrentChannel]++;
            Serial.println("Got Auth Frame");
            break;
        case 0xC0: // Deauthentication frame
            Config.analyticsdata->deauthCount[Config.CurrentChannel]++;
            Config.deauthCount++;
            Serial.println("Got Deauth Frame");
            break;
        case 0x00: // Association request frame
            Config.analyticsdata->probeReqCount[Config.CurrentChannel]++;
            Serial.println("Got Association request Frame");
            break;
        case 0x30: // Reassociation response frame
            Config.analyticsdata->probeRespCount[Config.CurrentChannel]++;
            Serial.println("Got Reassociation Response Frame");
            break;
        case 0x40: // Probe request frame
            Config.analyticsdata->probeReqCount[Config.CurrentChannel]++;
            Serial.println("Got Probe request frame");
            break;
        case 0x50: // Probe response frame
            Config.analyticsdata->probeRespCount[Config.CurrentChannel]++;
                Serial.println("Got Probe response frame");
            break;
        case 0x80: // Beacon frame
            Config.analyticsdata->beaconCount[Config.CurrentChannel]++;
            break;
        default: 
            Config.analyticsdata->otherPktCount[Config.CurrentChannel]++;
            break;
    }
}


void sendWifiAnalitics(String Channel, String SSID, String Password, String WebHookUrl) {
#ifdef OLD_LED
rgbmodule->breatheLED(rgbmodule->greenPin, 1000);
#endif

#ifdef NEOPIXEL_PIN
neopixelmodule->breatheLED(neopixelmodule->strip.Color(0, 255, 0), 1000, false);
#endif

if (!WebHookUrl.isEmpty())
{
    WiFi.begin(SSID, Password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    String host = WebHookUrl.substring(7, WebHookUrl.indexOf('/', 7)); // Skipping 'http://'
    String path = WebHookUrl.substring(WebHookUrl.indexOf('/', 7));
    int port = 443; // Or 443 for https

    WiFiClient wifiClient;
    HttpClient http(wifiClient, host, port);
    
    
    String message;
    
    unsigned long duration = Config.analyticsdata->endTime - Config.analyticsdata->startTime; 

    
    for (int channelIndex = 1; channelIndex < MAX_CHANNELS; channelIndex++) {
        
        String message = "{\"content\": \"\", \"embeds\": [{";
        message += "\"title\": \"WiFi Analytics Summary - Channel " + String(channelIndex) + "\",";
        message += "\"color\": 3447003,";
        message += "\"fields\": [";
        message += "{\"name\":\"Monitored Channel\",\"value\":\"" + String(channelIndex) + "\",\"inline\":true},";
        message += "{\"name\":\"Monitoring Duration\",\"value\":\"" + String((Config.analyticsdata->endTime[channelIndex] - Config.analyticsdata->startTime[channelIndex]) / 60000) + " minutes (" + String((Config.analyticsdata->endTime[channelIndex] - Config.analyticsdata->startTime[channelIndex]) / 1000) + " seconds)\",\"inline\":true},";
        message += "{\"name\":\"Deauthentication Packets\",\"value\":\"" + String(Config.analyticsdata->deauthCount[channelIndex]) + "\",\"inline\":false},";
        message += "{\"name\":\"Authentication Packets\",\"value\":\"" + String(Config.analyticsdata->authCount[channelIndex]) + "\",\"inline\":false},";
        message += "{\"name\":\"Beacon Packets\",\"value\":\"" + String(Config.analyticsdata->beaconCount[channelIndex]) + "\",\"inline\":false},";
        message += "{\"name\":\"Probe Request Packets\",\"value\":\"" + String(Config.analyticsdata->probeReqCount[channelIndex]) + "\",\"inline\":false},";
        message += "{\"name\":\"Probe Response Packets\",\"value\":\"" + String(Config.analyticsdata->probeRespCount[channelIndex]) + "\",\"inline\":false},";
        message += "{\"name\":\"Other Packet Types\",\"value\":\"" + String(Config.analyticsdata->otherPktCount[channelIndex]) + "\",\"inline\":false}";
        message += "]}]}";

        
        http.beginRequest();
        http.post(path, "application/json", message);
       int httpResponseCode = http.responseStatusCode();
        if (httpResponseCode > 0) {
            Serial.print("Data for channel ");
            Serial.print(channelIndex);
            Serial.println(" sent successfully");
        } else {
            Serial.print("Error sending data for channel ");
            Serial.println(channelIndex);
        }
        http.endRequest();

        
        delay(1000);
    }
    WiFi.disconnect();

}


Serial.println("WiFi Analytics Summary:");
Serial.println("------------------------------");

for (int channelIndex = 1; channelIndex < MAX_CHANNELS; channelIndex++) {
    Serial.print("Monitored Channel: ");
    Serial.println(channelIndex);
    Serial.print("Monitoring Duration: ");
    
    Serial.print((Config.analyticsdata->endTime[channelIndex] - Config.analyticsdata->startTime[channelIndex]) / 60000);
    Serial.print(" minutes (");
    Serial.print((Config.analyticsdata->endTime[channelIndex] - Config.analyticsdata->startTime[channelIndex]) / 1000);
    Serial.println(" seconds)");
    Serial.print("Deauthentication Packets: ");
    Serial.println(Config.analyticsdata->deauthCount[channelIndex]);
    Serial.print("Authentication Packets: ");
    Serial.println(Config.analyticsdata->authCount[channelIndex]);
    Serial.print("Beacon Packets: ");
    Serial.println(Config.analyticsdata->beaconCount[channelIndex]);
    Serial.print("Probe Request Packets: ");
    Serial.println(Config.analyticsdata->probeReqCount[channelIndex]);
    Serial.print("Probe Response Packets: ");
    Serial.println(Config.analyticsdata->probeRespCount[channelIndex]);
    Serial.print("Other Packet Types: ");
    Serial.println(Config.analyticsdata->otherPktCount[channelIndex]);
    Serial.println("------------------------------");
}
#ifdef OLD_LED
rgbmodule->breatheLED(rgbmodule->greenPin, 1000);
#endif

#ifdef NEOPIXEL_PIN
neopixelmodule->breatheLED(neopixelmodule->strip.Color(0, 255, 0), 1000, false);
#endif

delete Config.analyticsdata;

Serial.println("Command Finished");
}


void InitDeauthDetector(String Channel, String SSID, String Password, String WebHookUrl) 
{
    Config.startTime = millis();

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Channel.trim();

    Config.analyticsdata = new Wifianalyticsdata();

    Config.ConfigHasChannel = !Channel.isEmpty();

    if (Config.ConfigHasChannel)
    {
        Config.CurrentChannel = Channel.toInt();
    }

    Serial.println("Channel");
    Serial.println(Config.CurrentChannel);

    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_filter(&filt);
    esp_wifi_set_promiscuous_rx_cb(AnalyticsCallback);
    esp_wifi_set_channel(Config.CurrentChannel, WIFI_SECOND_CHAN_NONE);

    while (millis() - Config.startTime < Config.scanDuration) {
        if (millis() - Config.lastCheckTime > Config.checkInterval) {
            if (Config.deauthCount > Config.deauthThreshold) {
                Serial.println("Deauth attack detected!");
                #ifdef OLD_LED
                rgbmodule->breatheLED(rgbmodule->redPin, 1000);
                #endif
                #ifdef NEOPIXEL_PIN
                neopixelmodule->breatheLED(neopixelmodule->strip.Color(255, 0, 0), 1000, false);
                #endif
            } else {
                Serial.println("Normal network behavior.");
                rgbmodule->breatheLED(rgbmodule->greenPin, 1000);
<<<<<<< Updated upstream
=======
                #endif
                #ifdef NEOPIXEL_PIN
                neopixelmodule->breatheLED(neopixelmodule->strip.Color(0, 255, 0), 1000, false);
                #endif
>>>>>>> Stashed changes
            }
            Config.deauthCount = 0;
            Config.lastCheckTime = millis();
        }

        if (millis() - Config.lastChannelCheckTime > Config.ChannelHopInterval && !Config.ConfigHasChannel)
        {
            Config.CurrentChannel = (Config.CurrentChannel % MAX_CHANNELS) + 1;
            esp_wifi_set_channel(Config.CurrentChannel, WIFI_SECOND_CHAN_NONE);
            Config.lastChannelCheckTime = millis();
        }
    }

    for (int channelIndex = 1; channelIndex < MAX_CHANNELS; channelIndex++) 
    {
        Config.analyticsdata->endTime[channelIndex] = millis();
        Config.analyticsdata->startTime[channelIndex] =  Config.startTime;
    }


    
    esp_wifi_set_promiscuous(false);
    sendWifiAnalitics(Channel, SSID, Password, WebHookUrl);
}