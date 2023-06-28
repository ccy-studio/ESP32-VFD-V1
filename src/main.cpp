/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-04-02 12:40:12
 * @LastEditTime: 2023-06-28 22:26:20
 */
#include <Arduino.h>
#include <FastLED.h>
#include <WiFi.h>
#include <vfd.h>

#define NUM_LEDS 1
#define DATA_PIN GPIO_NUM_0

const char* ssid = "Connect-YC";
const char* password = "13083278337";

#define NTP1 "ntp1.aliyun.com"
#define NTP2 "ntp2.aliyun.com"
#define NTP3 "ntp3.aliyun.com"

CRGB leds[NUM_LEDS];

void setClock();

void setup() {
    Serial.begin(115200);
    // 初始化GPIO是输出模式
    pinMode(GPIO_NUM_6, OUTPUT);
    pinMode(GPIO_NUM_4, OUTPUT);
    pinMode(GPIO_NUM_3, OUTPUT);
    pinMode(GPIO_NUM_5, OUTPUT);
    pinMode(GPIO_NUM_1, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);

    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

    // WIFI Setting
    WiFi.begin(ssid, password);
    uint8_t hue = 0;
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        // let's set an led value
        hue += 10;
        leds[0] = CHSV(hue, 255, 255);
        FastLED.delay(33);
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // 设置PWM的频率单位hz
    analogWriteFrequency(15000);
    // 初始化VFD
    VFD_Init();
    VFD_Clear();
    VFD_ClearAD();
    VFD_SetString(0, "Initializing");
    VFD_SetDisplayOnOff(DISPLAY_ON);

    configTime(8 * 3600, 0, NTP1, NTP2, NTP3);
}

void loop() {
    // put your main code here, to run repeatedly:
    delay(1000);
    setClock();
}

void setClock() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {  // 如果获取失败，就开启联网模式，获取时间
        Serial.println("Failed to obtain time");
        WiFi.mode(WIFI_STA);  // 开启网络
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        configTime(8 * 3600, 0, NTP1, NTP2, NTP3);
        return;
    }
    // Serial.println(&timeinfo,
    //                "%F %T %A");  // 格式化输出:2021-10-24 23:00:44 Sunday
    // Serial.print(asctime(&timeinfo));  // 默认打印格式：Mon Oct 25 11:13:29
    // 2021

    String datetime = String(timeinfo.tm_mday);
    // datetime += timeinfo.tm_mday;  // 日
    datetime += "D ";
    datetime += timeinfo.tm_hour;  // 时
    datetime += ":";
    datetime += timeinfo.tm_min;
    datetime += ":";
    datetime += timeinfo.tm_sec;
    // 发送到VFD显示
    VFD_Clear();
    VFD_SetString(0, datetime.c_str());
}