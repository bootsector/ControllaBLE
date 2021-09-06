/*
* ControllaBLE - A retro-controllers to Bluetooth BLE adapter
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

#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEHIDDevice.h>

#include "snes.h"

#include "hid_report.h"

static NimBLEServer *pServer;
static NimBLEHIDDevice *hiddevice;

static NimBLECharacteristic *pInputCharacteristic1;
static NimBLECharacteristic *pInputCharacteristic2;

static uint16_t snes_p1_data, snes_p2_data, old_p1_data, old_p2_data;

static uint8_t digital_dir_lookup[16] = {15, 2, 6, 15, 4, 3, 5, 15, 0, 1, 7, 15, 15, 15, 15, 15};

static uint8_t ble_p1_data[] = {0x7F, 0x7F, 0x7F, 0x7F, 0x0F, 0x00, 0x00};
static uint8_t ble_p2_data[] = {0x7F, 0x7F, 0x7F, 0x7F, 0x0F, 0x00, 0x00};

static unsigned long led_change_millis, curr_millis;
static uint8_t led_status = 0;

class ServerCallbacks : public NimBLEServerCallbacks
{
	void onConnect(NimBLEServer *pServer, ble_gap_conn_desc *desc)
	{
		Serial.print("Client address: ");
		Serial.println(NimBLEAddress(desc->peer_ota_addr).toString().c_str());

		Serial.print("Updating client params...");
		pServer->updateConnParams(desc->conn_handle, 6, 12, 0, 600);
	};

	void onDisconnect(NimBLEServer *pServer)
	{
		Serial.println("Client disconnected - start advertising");
		NimBLEDevice::startAdvertising();
	};
};

void led_on() {
	digitalWrite(2, HIGH);
	led_status = 1;
}

void led_off() {
	digitalWrite(2, LOW);
	led_status = 0;
}

void led_toggle() {
	if(led_status) {
		led_off();
	} else {
		led_on();
	}
}

void led_init() {
	pinMode(2, OUTPUT);
	led_off();
}

void setup()
{
	Serial.begin(9600);

	Serial.println("Starting HID Server");

	NimBLEDevice::init("ControllaBLE");
	NimBLEDevice::setPower(ESP_PWR_LVL_P9);
	NimBLEDevice::setSecurityAuth(BLE_SM_PAIR_AUTHREQ_BOND);

	pServer = NimBLEDevice::createServer();

	pServer->setCallbacks(new ServerCallbacks());

	hiddevice = new NimBLEHIDDevice(pServer);

	// DeviceInfoService
	hiddevice->pnp(0x02, 0x0912, 0xCAFA, 0x0210);

	//DeviceInfoService - Manufacturer
	hiddevice->manufacturer()->setValue("www.brunofreitas.com");

	//HidService - hidInfo
	hiddevice->hidInfo(0x00, 0x01);

	//HidService - reportMap
	hiddevice->reportMap((uint8_t *)reportMap, sizeof(reportMap));

	//HidService-input - Player 1 data
	pInputCharacteristic1 = hiddevice->inputReport(1);

	//HidService-input - Player 2 data
	pInputCharacteristic2 = hiddevice->inputReport(2);

	hiddevice->startServices();

	NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
	pAdvertising->setAppearance(HID_JOYSTICK);
	pAdvertising->addServiceUUID(hiddevice->hidService()->getUUID());

	pAdvertising->setScanResponse(true);
	pAdvertising->start();

	snes_init();
	led_init();
}

void loop()
{
	snes_read(&snes_p1_data, &snes_p2_data);

	// P1
	ble_p1_data[4] = digital_dir_lookup[bitRead(snes_p1_data, SNES_UP) << 3 | 
	bitRead(snes_p1_data, SNES_DOWN) << 2 | bitRead(snes_p1_data, SNES_LEFT) << 1 | 
	bitRead(snes_p1_data, SNES_RIGHT)];

	bitRead(snes_p1_data, SNES_START)  ? bitSet(ble_p1_data[5], 5) : bitClear(ble_p1_data[5], 5);
	bitRead(snes_p1_data, SNES_SELECT)  ? bitSet(ble_p1_data[5], 4) : bitClear(ble_p1_data[5], 4);
	
	bitRead(snes_p1_data, SNES_Y)  ? bitSet(ble_p1_data[4], 7) : bitClear(ble_p1_data[4], 7);
	bitRead(snes_p1_data, SNES_B)  ? bitSet(ble_p1_data[4], 6) : bitClear(ble_p1_data[4], 6);
	bitRead(snes_p1_data, SNES_A)  ? bitSet(ble_p1_data[4], 5) : bitClear(ble_p1_data[4], 5);
	bitRead(snes_p1_data, SNES_X)  ? bitSet(ble_p1_data[4], 4) : bitClear(ble_p1_data[4], 4);

	bitRead(snes_p1_data, SNES_R)  ? bitSet(ble_p1_data[5], 3) : bitClear(ble_p1_data[5], 3);
	bitRead(snes_p1_data, SNES_L)  ? bitSet(ble_p1_data[5], 2) : bitClear(ble_p1_data[5], 2);

	// P2
	ble_p2_data[4] = digital_dir_lookup[bitRead(snes_p2_data, SNES_UP) << 3 | 
	bitRead(snes_p2_data, SNES_DOWN) << 2 | bitRead(snes_p2_data, SNES_LEFT) << 1 | 
	bitRead(snes_p2_data, SNES_RIGHT)];

	bitRead(snes_p2_data, SNES_START)  ? bitSet(ble_p2_data[5], 5) : bitClear(ble_p2_data[5], 5);
	bitRead(snes_p2_data, SNES_SELECT)  ? bitSet(ble_p2_data[5], 4) : bitClear(ble_p2_data[5], 4);
	
	bitRead(snes_p2_data, SNES_Y)  ? bitSet(ble_p2_data[4], 7) : bitClear(ble_p2_data[4], 7);
	bitRead(snes_p2_data, SNES_B)  ? bitSet(ble_p2_data[4], 6) : bitClear(ble_p2_data[4], 6);
	bitRead(snes_p2_data, SNES_A)  ? bitSet(ble_p2_data[4], 5) : bitClear(ble_p2_data[4], 5);
	bitRead(snes_p2_data, SNES_X)  ? bitSet(ble_p2_data[4], 4) : bitClear(ble_p2_data[4], 4);

	bitRead(snes_p2_data, SNES_R)  ? bitSet(ble_p2_data[5], 3) : bitClear(ble_p2_data[5], 3);
	bitRead(snes_p2_data, SNES_L)  ? bitSet(ble_p2_data[5], 2) : bitClear(ble_p2_data[5], 2);

	if (pServer->getConnectedCount()) {
		led_on();

		if(old_p1_data != snes_p1_data) {
			pInputCharacteristic1->setValue(ble_p1_data, sizeof(ble_p1_data));
			pInputCharacteristic1->notify();
			old_p1_data = snes_p1_data;
		}
		
		if(old_p2_data != snes_p2_data) {
			pInputCharacteristic2->setValue(ble_p2_data, sizeof(ble_p2_data));
			pInputCharacteristic2->notify();
			old_p2_data = snes_p2_data;
		}
	} else {
		curr_millis = millis();

		if((curr_millis - led_change_millis) > 100) {
			led_toggle();
			led_change_millis = curr_millis;
		}
	}
}