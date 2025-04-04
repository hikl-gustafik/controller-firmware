#pragma once

#define FW_PIN_SDA 21
#define FW_PIN_SCL 22

#define FW_I2C_FREQUENCY 1000000

// Screen
#define FW_SCREEN_WIDTH 128
#define FW_SCREEN_HEIGHT 64
#define FW_SCREEN_ADDRESS 0x3C
#define FW_PIN_RESET -1

// Input
#define FW_PIN_RJX 36
#define FW_PIN_RJY 39
#define FW_PIN_RJZ 33
#define FW_PIN_LJX 35
#define FW_PIN_LJY 34
#define FW_PIN_LJZ 32

#define FW_JOYSTICK_THEORETICAL_MAX 4095
#define FW_JOYSTICK_MAX 3600
#define FW_JOYSTICK_MIN 0
#define FW_JOYSTICK_DEADZONE 0.08
#define FW_JOYSTICK_SATURATION 0.97

#define FW_PIN_B1 12
#define FW_PIN_B2 14
#define FW_PIN_B3 13
#define FW_PIN_B4 16

// Vibration
#define FW_PIN_VMOTOR1 5
#define FW_PIN_VMOTOR2 15
#define FW_PIN_VMOTOR3 4
#define FW_PIN_VMOTOR4 23

#define FW_CHANNEL_VMOTOR1 0
#define FW_CHANNEL_VMOTOR2 1
#define FW_CHANNEL_VMOTOR3 2
#define FW_CHANNEL_VMOTOR4 3

// Speakers
#define FW_PIN_LSPEAKER 25
#define FW_PIN_RSPEAKER 26

#define FW_CHANNEL_LSPEAKER 4
#define FW_CHANNEL_RSPEAKER 5
