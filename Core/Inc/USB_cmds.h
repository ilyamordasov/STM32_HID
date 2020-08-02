/*
 * USB_cmds.h
 *
 *  Created on: Jul 29, 2020
 *      Author: Ilya Mordasov
 */

#ifndef INC_USB_CMDS_H_
#define INC_USB_CMDS_H_

#include "stm32f1xx_hal.h"
#include <stdbool.h>

#ifdef NDEBUG
	#define assert(condition) ((void)0)
#else
	#define assert(condition) /*implementation defined*/
#endif

typedef enum {
	USB_HIDDEVICE_OS_Windows = 0x00,		/*!< Windows */
	USB_HIDDEVICE_OS_Linux,					/*!< Linux */
	USB_HIDDEVICE_OS_OSX                 	/*!< MacOS */
} USB_HIDDEVICE_OS_t;

typedef enum {
	USB_HIDDEVICE_Button_Released = 0x00, /*!< Button is not pressed */
	USB_HIDDEVICE_Button_Pressed = 0x01   /*!< Button is pressed */
} USB_HIDDEVICE_Button_t;

typedef struct {
	USB_HIDDEVICE_Button_t L_CTRL;  /*!< Left CTRL button. This parameter can be a value of @ref USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t L_ALT;   /*!< Left ALT button. This parameter can be a value of @ref USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t L_SHIFT; /*!< Left SHIFT button. This parameter can be a value of @ref USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t L_GUI;   /*!< Left GUI (Win) button. This parameter can be a value of @ref USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t R_CTRL;  /*!< Right CTRL button. This parameter can be a value of @ref USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t R_ALT;   /*!< Right ALT button. This parameter can be a value of @ref USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t R_SHIFT; /*!< Right SHIFT button. This parameter can be a value of @ref USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t R_GUI;   /*!< Right GUI (Win) button. This parameter can be a value of @ref USB_HIDDEVICE_Button_t enumeration */
	uint8_t Key1;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
	uint8_t Key2;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
	uint8_t Key3;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
	uint8_t Key4;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
	uint8_t Key5;                      /*!< Key used with keyboard. This can be whatever. Like numbers, letters, everything. */
} USB_HIDDEVICE_Keyboard_t;

typedef struct {
	USB_HIDDEVICE_Button_t LeftButton;   /*!< Detect if left button is pressed and set this to send command to computer, This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t RightButton;  /*!< Detect if right button is pressed and set this to send command to computer, This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	USB_HIDDEVICE_Button_t MiddleButton; /*!< Detect if middle button is pressed and set this to send command to computer, This parameter can be a value of @ref TM_USB_HIDDEVICE_Button_t enumeration */
	int8_t XAxis;                           /*!< Mouse X axis */
	int8_t YAxis;                           /*!< Mouse Y axis */
	int8_t Wheel;                           /*!< Mouse wheel rotation */
} USB_HIDDEVICE_Mouse_t;

void MX_USB_Send_Notification(USB_HIDDEVICE_OS_t os);
uint8_t MX_USB_KEYBOARD_Send(USB_HIDDEVICE_Keyboard_t* Keyboard_Data, bool release);
uint8_t MX_USB_KEYBOARD_ReleaseAll(void);
uint8_t MX_USB_MOUSE_ScrollUp(void);
uint8_t MX_USB_MOUSE_ScrollDown(void);
uint8_t MX_USB_MOUSE_ReleaseAll(void);

#endif /* INC_USB_CMDS_H_ */
