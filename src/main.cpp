/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-04-02 12:40:12
 * @LastEditTime: 2023-04-02 13:29:50
 */
#include <Arduino.h>
#include <WiFi.h>
#include <ds1302.h>
#include <vfd.h>

void setup() {
    Serial.begin(115200);

    VFD_Init();
    Ds1302_Init();
}

void loop() {
    delay(1000);
    RtcDateTime now = Ds1302_GetNow();
    Ds1302_PrintDateTime(now);
    Serial.println();
}