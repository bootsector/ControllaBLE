#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEHIDDevice.h>

#include "snes.h"

#include "hid_report.h"

static NimBLEServer *pServer;
static NimBLEHIDDevice *hiddevice;

static NimBLECharacteristic *pInputCharacteristic1;
static NimBLECharacteristic *pInputCharacteristic2;

static uint16_t snes_p1_data, snes_p2_data;

static uint8_t digital_dir_lookup[16] = {15, 2, 6, 15, 4, 3, 5, 15, 0, 1, 7, 15, 15, 15, 15, 15};

static uint8_t ble_p1_data[] = {0x7F, 0x7F, 0x7F, 0x7F, 0x0F, 0x00, 0x00};
static uint8_t ble_p2_data[] = {0x7F, 0x7F, 0x7F, 0x7F, 0x0F, 0x00, 0x00};

void setup()
{

	NimBLEDevice::init("ControlaBLE");
	NimBLEDevice::setPower(ESP_PWR_LVL_P9);
	NimBLEDevice::setSecurityAuth(BLE_SM_PAIR_AUTHREQ_BOND);

	pServer = NimBLEDevice::createServer();

	hiddevice = new NimBLEHIDDevice(pServer);

	// DeviceInfoService
	hiddevice->pnp(0x02, 0x1008, 0x0100, 0x0210);

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
	bitRead(snes_p1_data, SNES_X)  ? bitSet(ble_p2_data[4], 4) : bitClear(ble_p2_data[4], 4);

	bitRead(snes_p2_data, SNES_R)  ? bitSet(ble_p2_data[5], 3) : bitClear(ble_p2_data[5], 3);
	bitRead(snes_p2_data, SNES_L)  ? bitSet(ble_p2_data[5], 2) : bitClear(ble_p2_data[5], 2);

	if (pServer->getConnectedCount()) {
		pInputCharacteristic1->setValue(ble_p1_data, sizeof(ble_p1_data));
		pInputCharacteristic2->setValue(ble_p2_data, sizeof(ble_p2_data));
		
		pInputCharacteristic1->notify();
		pInputCharacteristic2->notify();
	}
}