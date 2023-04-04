/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-04-02 12:40:12
 * @LastEditTime: 2023-04-04 22:44:01
 */
#include <Arduino.h>
#include <WiFi.h>
#include <ds1302.h>
#include <vfd.h>

const char* ssid = "输入你的WIFI名称";
const char* password = "输入你的WIFI密码";

#define NTP1 "ntp1.aliyun.com"
#define NTP2 "ntp2.aliyun.com"
#define NTP3 "ntp3.aliyun.com"

void setClock();

void setup() {
    Serial.begin(115200);
    //初始化GPIO是输出模式
    pinMode(GPIO_NUM_6, OUTPUT);
    pinMode(GPIO_NUM_4, OUTPUT);
    pinMode(GPIO_NUM_3, OUTPUT);
    pinMode(GPIO_NUM_5, OUTPUT);
    pinMode(GPIO_NUM_1, OUTPUT);
    // pinMode(LED, OUTPUT);

    //设置PWM的频率单位hz
    analogWriteFrequency(10000);

    //初始化VFD
    VFD_Init();
    VFD_Clear();
    VFD_ClearAD();
    VFD_SetString(0, "Connecting..");
    VFD_SetDisplayOnOff(DISPLAY_ON);

    // WIFI Setting
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    configTime(8 * 3600, 0, NTP1, NTP2, NTP3);
    // put your setup code here, to run once:
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

    String datetime = String(timeinfo.tm_mon + 1);
    datetime += "/";
    datetime += timeinfo.tm_mday;  // 日
    datetime += " ";
    datetime += timeinfo.tm_hour;  // 时
    datetime += ":";
    datetime += timeinfo.tm_min;
    datetime += ":";
    datetime += timeinfo.tm_sec;
    //发送到VFD显示
    VFD_Clear();
    VFD_SetString(0, datetime.c_str());
}