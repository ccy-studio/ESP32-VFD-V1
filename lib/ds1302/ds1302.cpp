#include <ds1302.h>
#define countof(a) (sizeof(a) / sizeof(a[0]))

ThreeWire rtcWire(DS1302_IO, DS1302_SCLK, DS1302_CE);  // IO, SCLK, CE
RtcDS1302<ThreeWire> rtc(rtcWire);

void Ds1302_Init(void) {
    rtc.Begin();
    // RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    // printDateTime(compiled);

    if (rtc.GetIsWriteProtected()) {
        Serial.println("RTC was write protected, enabling writing now");
        rtc.SetIsWriteProtected(false);
    }

    if (!rtc.GetIsRunning()) {
        Serial.println("RTC was not actively running, starting now");
        rtc.SetIsRunning(true);
    }
    Serial.println();
}

void Ds1302_SetRtcDateTime(RtcDateTime datetime) {
    rtc.SetDateTime(datetime);
}

RtcDateTime Ds1302_GetNow() {
    return rtc.GetDateTime();
}

void Ds1302_PrintDateTime(const RtcDateTime& dt) {
    char datestring[20];

    snprintf_P(datestring, countof(datestring),
               PSTR("%02u/%02u/%04u %02u:%02u:%02u"), dt.Month(), dt.Day(),
               dt.Year(), dt.Hour(), dt.Minute(), dt.Second());
    Serial.print(datestring);
}