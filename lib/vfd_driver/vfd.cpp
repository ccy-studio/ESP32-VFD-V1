/*
 * @Description:
 * @Author: chenzedeng
 * @Date: 2023-03-210 22:310:17
 * @LastEditTime: 2023-04-01 15:28:00
 */
#include "vfd.h"

/**
 * 数据写入 八位
 * @param w_data
 */
void write_6302(unsigned char w_data) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        CLK_L;
        delayMicroseconds(2);
        if ((w_data & 0x01) == 0x01) {
            DIN_H;
        } else {
            DIN_L;
        }
        w_data >>= 1;
        delayMicroseconds(2);
        CLK_H;
        delayMicroseconds(2);
    }
}

/**
 * 重置为初始化
 */
void VFD_Init() {
    pinMode(GPIO_NUM_6, OUTPUT);
    pinMode(GPIO_NUM_4, OUTPUT);
    pinMode(GPIO_NUM_3, OUTPUT);
    pinMode(GPIO_NUM_5, OUTPUT);
    pinMode(GPIO_NUM_1, OUTPUT);

    RST_H;
    CS_H;
    CLK_H;
    DIN_H;

    delay(50);

    RST_L;
    delay(500);
    RST_H;
    delay(500);

    // 设置显示位数
    CS_L;
    delayMicroseconds(2);
    write_6302(0x64);  // GR1 ~ GR16
    delayMicroseconds(17);
    CS_H;

    delayMicroseconds(2);  // 两次连续通讯中间需要间隔至少300ns

    // 设置显示占空比
    CS_L;
    delayMicroseconds(2);
    write_6302(0x57);
    delayMicroseconds(17);
    CS_H;

    delayMicroseconds(2);  // 两次连续通讯中间需要间隔至少300ns

    PWM_START;
}

void VFD_SetString(uint8_t index, const char* str) {
    delayMicroseconds(2);  // 两次连续通讯中间需要间隔至少300ns
    CS_L;
    delayMicroseconds(2);
    // 起始点位数
    write_6302(0x10 + index);
    delayMicroseconds(10);  // 连续间隔最小要8us
    while (*str) {
        write_6302(*str);       // ascii与对应字符表转换
        delayMicroseconds(10);  // 连续间隔最小要8us
        str++;
    }
    delayMicroseconds(17);
    CS_H;
}

void VFD_WriteOnece(uint8_t index, const char str) {
    delayMicroseconds(2);  // 两次连续通讯中间需要间隔至少300ns
    CS_L;
    delayMicroseconds(2);
    // 起始点位数
    write_6302(0x10 + index);
    delayMicroseconds(10);  // 连续间隔最小要8us
    write_6302(str);
    delayMicroseconds(17);
    CS_H;
}

void VFD_SetAD(int index, bool state) {
    delayMicroseconds(2);
    CS_L;
    delayMicroseconds(2);
    write_6302(0x30 + index);
    delayMicroseconds(10);            // 连续间隔最小要8us
    write_6302(state ? 0xff : 0x00);  // ascii与对应字符表转换
    delayMicroseconds(17);
    CS_H;
}

void VFD_ClearAD() {
    delayMicroseconds(2);
    CS_L;
    delayMicroseconds(2);
    write_6302(0x30);
    delayMicroseconds(10);  // 连续间隔最小要8us
    for (int i = 0; i < 12; i++) {
        write_6302(0x00);       // ascii与对应字符表转换
        delayMicroseconds(10);  // 连续间隔最小要8us
    }
    delayMicroseconds(17);
    CS_H;
}

void VFD_Clear() {
    delayMicroseconds(2);  // 两次连续通讯中间需要间隔至少300ns
    CS_L;
    delayMicroseconds(2);
    // 起始点位数
    write_6302(0x10);
    delayMicroseconds(10);  // 连续间隔最小要8us
    for (int i = 0; i < 12; i++) {
        write_6302(0xff);       // ascii与对应字符表转换
        delayMicroseconds(10);  // 连续间隔最小要8us
    }
    delayMicroseconds(17);
    CS_H;
}

/**
 * 设置灯光的开关
 * @param value
 */
void VFD_SetDisplayOnOff(uint8_t value) {
    delayMicroseconds(2);  // 两次连续通讯中间需要间隔至少300ns
    CS_L;
    delayMicroseconds(2);
    write_6302(value);
    delayMicroseconds(17);
    CS_H;
}