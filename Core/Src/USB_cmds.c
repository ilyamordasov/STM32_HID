#include "USB_cmds.h"
#include "iwdg.h"
#include "usbd_def.h"

#define USBD_PRODUCT_STRING_FS     "USB HID MANIPULATOR"
USB_HIDDEVICE_Keyboard_t Keyboard;
USB_HIDDEVICE_Mouse_t Mouse;

extern USBD_HandleTypeDef hUsbDeviceFS;

void MX_USB_Send_Notification(USB_HIDDEVICE_OS_t os) {
	char buf[128];
	switch (os) {
		case USB_HIDDEVICE_OS_Windows:
			/* GUI+T - Open Terminal */
			sprintf(buf, "notify-send %s Message\r\n", USBD_PRODUCT_STRING_FS);
			MX_USB_SEND_Keyboard(buf);
			break;
		case USB_HIDDEVICE_OS_Linux:
			/* CTRL+GUI+T - Open Terminal */
			sprintf(buf, "notify-send %s MESSAGE\r\n", USBD_PRODUCT_STRING_FS);
			MX_USB_SEND_Keyboard(buf);
			break;
		case USB_HIDDEVICE_OS_OSX:
			/* GUI+T - Open Terminal */
			sprintf(buf, "osascript -e 'display notification MESSAGE with title %s'\r\n", USBD_PRODUCT_STRING_FS);
			MX_USB_SEND_Keyboard(buf);
			break;
		default: break;//Error_Handler();//assert("You have to use one of these OS:\r\nUSB_HIDDEVICE_OS_Windows\r\nUSB_HIDDEVICE_OS_Linux\r\nUSB_HIDDEVICE_OS_OSX");
	}
}

uint8_t MX_USB_KEYBOARD_Send(USB_HIDDEVICE_Keyboard_t* Keyboard_Data, bool release) {
	uint8_t buff[8] = {0};

	buff[0] = 2;

	buff[1] = 0;
	buff[1] |= Keyboard_Data->L_CTRL 	<< 0;	/* Bit 0 */
	buff[1] |= Keyboard_Data->L_SHIFT 	<< 1;	/* Bit 1 */
	buff[1] |= Keyboard_Data->L_ALT 	<< 2;	/* Bit 2 */
	buff[1] |= Keyboard_Data->L_GUI 	<< 3;	/* Bit 3 */
	buff[1] |= Keyboard_Data->R_CTRL 	<< 4;	/* Bit 4 */
	buff[1] |= Keyboard_Data->R_SHIFT 	<< 5;	/* Bit 5 */
	buff[1] |= Keyboard_Data->R_ALT 	<< 6;	/* Bit 6 */
	buff[1] |= Keyboard_Data->R_GUI 	<< 7;	/* Bit 7 */

	/* Padding */
	buff[2] = 0x00;

	/* Keys */
	buff[3] = Keyboard_Data->Key1;
	buff[4] = Keyboard_Data->Key2;
	buff[5] = Keyboard_Data->Key3;
	buff[6] = Keyboard_Data->Key4;
	buff[7] = Keyboard_Data->Key5;

	/* Send to USB */

	USBD_HID_SendReport(&hUsbDeviceFS, buff, 8);
	if (release) {
		uint32_t cnt = 100000;
		while(--cnt){
			HAL_IWDG_Refresh(&hiwdg);
		}
		MX_USB_KEYBOARD_ReleaseAll();
	}
	return USBD_OK;
}

uint8_t MX_USB_KEYBOARD_ReleaseAll(void) {
	uint8_t buff[8] = {0};

	/* Report ID */
	buff[0] = 2; /* Keyboard */

	/* Send to USB */
	uint32_t cnt = 100000;
	USBD_HID_SendReport(&hUsbDeviceFS, buff, 8);
	while(--cnt){
		HAL_IWDG_Refresh(&hiwdg);
	}
	return USBD_OK;
}

uint8_t MX_USB_MOUSE_ScrollUp(void) {
	Mouse.Wheel = -10;
	uint8_t buff[5] = {0};
	buff[0] = 1;
	buff[4] = Mouse.Wheel;
	USBD_HID_SendReport(&hUsbDeviceFS, buff, 5);
	uint32_t cnt = 100000;
	while(--cnt){
		HAL_IWDG_Refresh(&hiwdg);
	}
	MX_USB_MOUSE_ReleaseAll();
	return USBD_OK;
}

uint8_t MX_USB_MOUSE_ScrollDown(void) {
	Mouse.Wheel = 10;
	uint8_t buff[5] = {0};
	buff[0] = 1;
	buff[4] = Mouse.Wheel;
	USBD_HID_SendReport(&hUsbDeviceFS, buff, 5);
	uint32_t cnt = 100000;
	while(--cnt){
		HAL_IWDG_Refresh(&hiwdg);
	}
	MX_USB_MOUSE_ReleaseAll();
	return USBD_OK;
}

uint8_t MX_USB_MOUSE_ReleaseAll(void) {
	uint8_t buff[5] = {0};
	buff[0] = 1;
	USBD_HID_SendReport(&hUsbDeviceFS, buff, 5);
	uint32_t cnt = 100000;
	while(--cnt){
		HAL_IWDG_Refresh(&hiwdg);
	}
	return USBD_OK;
}
