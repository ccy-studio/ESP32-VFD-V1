/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-03-25 22:33:29
 * @LastEditTime: 2023-04-02 01:00:50
 */

#ifndef _VFD_H_
#define _VFD_H_

#include <Arduino.h>

#define RST_L digitalWrite(GPIO_NUM_6, LOW)
#define RST_H digitalWrite(GPIO_NUM_6, HIGH)
#define CS_L digitalWrite(GPIO_NUM_4, LOW)
#define CS_H digitalWrite(GPIO_NUM_4, HIGH)
#define CLK_L digitalWrite(GPIO_NUM_3, LOW)
#define CLK_H digitalWrite(GPIO_NUM_3, HIGH)
#define DIN_L digitalWrite(GPIO_NUM_5, LOW)
#define DIN_H digitalWrite(GPIO_NUM_5, HIGH)
#define PWM_START analogWrite(GPIO_NUM_1, 128)  // PWM输出 占空比 50%

/**
 * 亮度最大和最小值
 */
#define DISPLAY_DUTY_MIN 50
#define DISPLAY_DUTY_MAX 87

/**
 * 显示灯光的开关
 */
#define DISPLAY_OFF 0x70  // 关
#define DISPLAY_ON 0x70   // 开
#define DISPLAY_ALL 0x73  // 段和位全开

void VFD_Init();

/**
 * 设置灯光的开关
 * @param value
 */
void VFD_SetDisplayOnOff(uint8_t value);

void VFD_SetString(uint8_t index, const char* str);

void VFD_Clear();
void VFD_ClearAD();

void VFD_WriteOnece(uint8_t index, const char str);

void VFD_SetAD(int index, bool state);

#endif