/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-03-25 22:33:29
 * @LastEditTime: 2023-04-04 22:42:59
 */

#ifndef _VFD_H_
#define _VFD_H_

#include <Arduino.h>

// 在这里设置你的GPIO对应的引脚
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

/**
 * 初始化
 */
void VFD_Init();

/**
 * 设置灯光的开关
 * @param value 常量
 */
void VFD_SetDisplayOnOff(uint8_t value);

/**
 * 设置显示的字符 index从0开始
 */
void VFD_SetString(uint8_t index, const char* str);

/**
 * 清屏
 */
void VFD_Clear();

/**
 * 熄灭点阵上方的ICON图标
 */
void VFD_ClearAD();

/**
 * 指定某个位置设置一个字符
 */
void VFD_WriteOnece(uint8_t index, const char str);

/**
 * 在某个位置段上设置点亮或者熄灭ICON图标
 * index从0开始
 * state： true点亮、false熄灭
 */
void VFD_SetAD(int index, bool state);

#endif