/*
* ControlaBLE - A retro-controllers to Bluetooth BLE adapter
*
* Copyright (c) 2021
* Bruno Freitas - bruno@brunofreitas.com - http://www.brunofreitas.com/
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

const uint8_t reportMap[] = {
	0x05, 0x01,		  // Usage Page (Generic Desktop Ctrls)
	0x09, 0x04,		  // Usage (Joystick)
	0xA1, 0x01,		  // Collection (Application)
	0x85, 0x01,		  //   Report ID (1)
	0xA1, 0x02,		  //   Collection (Logical)
	0x75, 0x08,		  //     Report Size (8)
	0x95, 0x04,		  //     Report Count (4)
	0x15, 0x00,		  //     Logical Minimum (0)
	0x26, 0xFF, 0x00, //     Logical Maximum (255)
	0x35, 0x00,		  //     Physical Minimum (0)
	0x46, 0xFF, 0x00, //     Physical Maximum (255)
	0x09, 0x32,		  //     Usage (Z)
	0x09, 0x35,		  //     Usage (Rz)
	0x09, 0x30,		  //     Usage (X)
	0x09, 0x31,		  //     Usage (Y)
	0x81, 0x02,		  //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x75, 0x04,		  //     Report Size (4)
	0x95, 0x01,		  //     Report Count (1)
	0x25, 0x07,		  //     Logical Maximum (7)
	0x46, 0x3B, 0x01, //     Physical Maximum (315)
	0x65, 0x14,		  //     Unit (System: English Rotation, Length: Centimeter)
	0x09, 0x39,		  //     Usage (Hat switch)
	0x81, 0x42,		  //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
	0x65, 0x00,		  //     Unit (None)
	0x75, 0x01,		  //     Report Size (1)
	0x95, 0x0C,		  //     Report Count (12)
	0x25, 0x01,		  //     Logical Maximum (1)
	0x45, 0x01,		  //     Physical Maximum (1)
	0x05, 0x09,		  //     Usage Page (Button)
	0x19, 0x01,		  //     Usage Minimum (0x01)
	0x29, 0x0C,		  //     Usage Maximum (0x0C)
	0x81, 0x02,		  //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x06, 0x00, 0xFF, //     Usage Page (Vendor Defined 0xFF00)
	0x75, 0x01,		  //     Report Size (1)
	0x95, 0x08,		  //     Report Count (8)
	0x25, 0x01,		  //     Logical Maximum (1)
	0x45, 0x01,		  //     Physical Maximum (1)
	0x09, 0x01,		  //     Usage (0x01)
	0x81, 0x02,		  //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,			  //   End Collection
	0xA1, 0x02,		  //   Collection (Logical)
	0x75, 0x08,		  //     Report Size (8)
	0x95, 0x04,		  //     Report Count (4)
	0x46, 0xFF, 0x00, //     Physical Maximum (255)
	0x26, 0xFF, 0x00, //     Logical Maximum (255)
	0x09, 0x02,		  //     Usage (0x02)
	0x91, 0x02,		  //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0xC0,			  //   End Collection
	0xC0,			  // End Collection
	0x05, 0x01,		  // Usage Page (Generic Desktop Ctrls)
	0x09, 0x04,		  // Usage (Joystick)
	0xA1, 0x01,		  // Collection (Application)
	0x85, 0x02,		  //   Report ID (2)
	0xA1, 0x02,		  //   Collection (Logical)
	0x75, 0x08,		  //     Report Size (8)
	0x95, 0x04,		  //     Report Count (4)
	0x15, 0x00,		  //     Logical Minimum (0)
	0x26, 0xFF, 0x00, //     Logical Maximum (255)
	0x35, 0x00,		  //     Physical Minimum (0)
	0x46, 0xFF, 0x00, //     Physical Maximum (255)
	0x09, 0x32,		  //     Usage (Z)
	0x09, 0x35,		  //     Usage (Rz)
	0x09, 0x30,		  //     Usage (X)
	0x09, 0x31,		  //     Usage (Y)
	0x81, 0x02,		  //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x75, 0x04,		  //     Report Size (4)
	0x95, 0x01,		  //     Report Count (1)
	0x25, 0x07,		  //     Logical Maximum (7)
	0x46, 0x3B, 0x01, //     Physical Maximum (315)
	0x65, 0x14,		  //     Unit (System: English Rotation, Length: Centimeter)
	0x09, 0x39,		  //     Usage (Hat switch)
	0x81, 0x42,		  //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
	0x65, 0x00,		  //     Unit (None)
	0x75, 0x01,		  //     Report Size (1)
	0x95, 0x0C,		  //     Report Count (12)
	0x25, 0x01,		  //     Logical Maximum (1)
	0x45, 0x01,		  //     Physical Maximum (1)
	0x05, 0x09,		  //     Usage Page (Button)
	0x19, 0x01,		  //     Usage Minimum (0x01)
	0x29, 0x0C,		  //     Usage Maximum (0x0C)
	0x81, 0x02,		  //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x06, 0x00, 0xFF, //     Usage Page (Vendor Defined 0xFF00)
	0x75, 0x01,		  //     Report Size (1)
	0x95, 0x08,		  //     Report Count (8)
	0x25, 0x01,		  //     Logical Maximum (1)
	0x45, 0x01,		  //     Physical Maximum (1)
	0x09, 0x01,		  //     Usage (0x01)
	0x81, 0x02,		  //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,			  //   End Collection
	0xA1, 0x02,		  //   Collection (Logical)
	0x75, 0x08,		  //     Report Size (8)
	0x95, 0x04,		  //     Report Count (4)
	0x46, 0xFF, 0x00, //     Physical Maximum (255)
	0x26, 0xFF, 0x00, //     Logical Maximum (255)
	0x09, 0x02,		  //     Usage (0x02)
	0x91, 0x02,		  //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0xC0,			  //   End Collection
	0xC0			  // End Collection
};