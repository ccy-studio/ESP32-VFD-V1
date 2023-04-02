#ifndef _DS1302_
#define _DS1302_

#include <Arduino.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

// IO, SCLK, CE
#define DS1302_IO GPIO_NUM_7
#define DS1302_SCLK GPIO_NUM_10
#define DS1302_CE GPIO_NUM_11

/**
 * 初始化
 */
void Ds1302_Init(void);

/**
 * 设置时间
 */
void Ds1302_SetRtcDateTime(RtcDateTime datetime);

/**
 * 获取当前时间
 */
RtcDateTime Ds1302_GetNow();

/**
 * 控制台输出格式化打印时间
 */
void Ds1302_PrintDateTime(const RtcDateTime& dt);

#endif