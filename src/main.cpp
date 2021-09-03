#include <Arduino.h>
#include <NimBLEDevice.h>
#include <NimBLEHIDDevice.h>

const uint8_t reportMap[] = {
	0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
	0x09, 0x04,        // Usage (Joystick)
	0xA1, 0x01,        // Collection (Application)
	0x85, 0x01,        //   Report ID (1)
	0xA1, 0x02,        //   Collection (Logical)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x04,        //     Report Count (4)
	0x15, 0x00,        //     Logical Minimum (0)
	0x26, 0xFF, 0x00,  //     Logical Maximum (255)
	0x35, 0x00,        //     Physical Minimum (0)
	0x46, 0xFF, 0x00,  //     Physical Maximum (255)
	0x09, 0x32,        //     Usage (Z)
	0x09, 0x35,        //     Usage (Rz)
	0x09, 0x30,        //     Usage (X)
	0x09, 0x31,        //     Usage (Y)
	0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x75, 0x04,        //     Report Size (4)
	0x95, 0x01,        //     Report Count (1)
	0x25, 0x07,        //     Logical Maximum (7)
	0x46, 0x3B, 0x01,  //     Physical Maximum (315)
	0x65, 0x14,        //     Unit (System: English Rotation, Length: Centimeter)
	0x09, 0x39,        //     Usage (Hat switch)
	0x81, 0x42,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
	0x65, 0x00,        //     Unit (None)
	0x75, 0x01,        //     Report Size (1)
	0x95, 0x0C,        //     Report Count (12)
	0x25, 0x01,        //     Logical Maximum (1)
	0x45, 0x01,        //     Physical Maximum (1)
	0x05, 0x09,        //     Usage Page (Button)
	0x19, 0x01,        //     Usage Minimum (0x01)
	0x29, 0x0C,        //     Usage Maximum (0x0C)
	0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x06, 0x00, 0xFF,  //     Usage Page (Vendor Defined 0xFF00)
	0x75, 0x01,        //     Report Size (1)
	0x95, 0x08,        //     Report Count (8)
	0x25, 0x01,        //     Logical Maximum (1)
	0x45, 0x01,        //     Physical Maximum (1)
	0x09, 0x01,        //     Usage (0x01)
	0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,              //   End Collection
	0xA1, 0x02,        //   Collection (Logical)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x04,        //     Report Count (4)
	0x46, 0xFF, 0x00,  //     Physical Maximum (255)
	0x26, 0xFF, 0x00,  //     Logical Maximum (255)
	0x09, 0x02,        //     Usage (0x02)
	0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0xC0,              //   End Collection
	0xC0,              // End Collection
	0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
	0x09, 0x04,        // Usage (Joystick)
	0xA1, 0x01,        // Collection (Application)
	0x85, 0x02,        //   Report ID (2)
	0xA1, 0x02,        //   Collection (Logical)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x04,        //     Report Count (4)
	0x15, 0x00,        //     Logical Minimum (0)
	0x26, 0xFF, 0x00,  //     Logical Maximum (255)
	0x35, 0x00,        //     Physical Minimum (0)
	0x46, 0xFF, 0x00,  //     Physical Maximum (255)
	0x09, 0x32,        //     Usage (Z)
	0x09, 0x35,        //     Usage (Rz)
	0x09, 0x30,        //     Usage (X)
	0x09, 0x31,        //     Usage (Y)
	0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x75, 0x04,        //     Report Size (4)
	0x95, 0x01,        //     Report Count (1)
	0x25, 0x07,        //     Logical Maximum (7)
	0x46, 0x3B, 0x01,  //     Physical Maximum (315)
	0x65, 0x14,        //     Unit (System: English Rotation, Length: Centimeter)
	0x09, 0x39,        //     Usage (Hat switch)
	0x81, 0x42,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
	0x65, 0x00,        //     Unit (None)
	0x75, 0x01,        //     Report Size (1)
	0x95, 0x0C,        //     Report Count (12)
	0x25, 0x01,        //     Logical Maximum (1)
	0x45, 0x01,        //     Physical Maximum (1)
	0x05, 0x09,        //     Usage Page (Button)
	0x19, 0x01,        //     Usage Minimum (0x01)
	0x29, 0x0C,        //     Usage Maximum (0x0C)
	0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x06, 0x00, 0xFF,  //     Usage Page (Vendor Defined 0xFF00)
	0x75, 0x01,        //     Report Size (1)
	0x95, 0x08,        //     Report Count (8)
	0x25, 0x01,        //     Logical Maximum (1)
	0x45, 0x01,        //     Physical Maximum (1)
	0x09, 0x01,        //     Usage (0x01)
	0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,              //   End Collection
	0xA1, 0x02,        //   Collection (Logical)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x04,        //     Report Count (4)
	0x46, 0xFF, 0x00,  //     Physical Maximum (255)
	0x26, 0xFF, 0x00,  //     Logical Maximum (255)
	0x09, 0x02,        //     Usage (0x02)
	0x91, 0x02,        //     Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
	0xC0,              //   End Collection
	0xC0               // End Collection
};

static NimBLEServer* pServer;
static NimBLEHIDDevice *hiddevice;

NimBLECharacteristic* pInputCharacteristic1;
NimBLECharacteristic* pInputCharacteristic2;

void setup() {

    NimBLEDevice::init("BLEsSTer");
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
	hiddevice->reportMap((uint8_t *) reportMap, sizeof(reportMap));

    //HidService-input - Player 1 data
	pInputCharacteristic1 = hiddevice->inputReport(1);

    //HidService-input - Player 2 data
	pInputCharacteristic2 = hiddevice->inputReport(2);

	hiddevice->startServices();

    NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->setAppearance(HID_JOYSTICK);
    pAdvertising->addServiceUUID(hiddevice->hidService()->getUUID());

    pAdvertising->setScanResponse(true);
    pAdvertising->start();
}

void loop() {
  /** Do your thing here, this just spams notifications to all connected clients */
    if(pServer->getConnectedCount()) {
                    uint8_t a[] = {0x7F, 0x7F, 0x7F, 0x7F, 0x0F, 0x00, 0x00};
					uint8_t b[] = {0x7F, 0x7F, 0x7F, 0x7F, 0x0F, 0x00, 0x00};
                    
					pInputCharacteristic1->setValue(a, sizeof(a));
                    pInputCharacteristic1->notify();
                    
					pInputCharacteristic2->setValue(b, sizeof(b));
                    pInputCharacteristic2->notify();
                    
					delay(5000);
                    
					a[4] = 0x00;
                    b[4] = 0x00;

					pInputCharacteristic1->setValue(a, sizeof(a));
                    pInputCharacteristic1->notify();

					pInputCharacteristic2->setValue(b, sizeof(b));
                    pInputCharacteristic2->notify();
                    
					delay(200);
    }
    delay(2000);
}