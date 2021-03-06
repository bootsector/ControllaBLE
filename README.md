**ControllaBLE - A retro-controllers to Bluetooth BLE adapter**

This is an ESP32 based controller adapter that outputs as a dual joypad through
Bluetooth (BLE).

This was created using VSCode + PlatformIO extension.

ESP32 Arduino framework was used, along with the NimBLE Arduino library.

[This is the ESP32-WROOM-32 dev board](https://www.amazon.com/VKLSVAN-ESP-WROOM-32-Development-Dual-Mode-Microcontroller/dp/B07T6J3PXZ/ref=sr_1_21) you'll need to run this adapter.

For now it supports only up to 2 SNES controllers connected as:

- SNES pad (both) CLOCK Arduino pin: 19
- SNES pad (both) LATCH Arduino pin: 21
- SNES pad P1 DATA Arduino pin: 22
- SNES pad P2 DATA Arduino pin: 23

![alt text](https://i.imgur.com/05jYEEO.png)

Support for more controllers will be added soon!
