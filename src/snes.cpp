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

#include "snes.h"

#define CLOCK_PIN 19
#define LATCH_PIN 21
#define P1DAT_PIN 22
#define P2DAT_PIN 23

void snes_init() {
	pinMode(CLOCK_PIN, OUTPUT);
	pinMode(LATCH_PIN, OUTPUT);

	pinMode(P1DAT_PIN, INPUT_PULLUP);
	pinMode(P2DAT_PIN, INPUT_PULLUP);
}

void snes_read(uint16_t *p1data) {
	uint16_t p1;

	digitalWrite(LATCH_PIN, LOW);
	digitalWrite(CLOCK_PIN, LOW);

	digitalWrite(LATCH_PIN, HIGH);
	delayMicroseconds(1);
	digitalWrite(LATCH_PIN, LOW);
	delayMicroseconds(1);

	p1 = digitalRead(P1DAT_PIN);

	for(int i = 1; i < 16; i++) {
		digitalWrite(CLOCK_PIN, HIGH);
		delayMicroseconds(1);
		digitalWrite(CLOCK_PIN, LOW);
		delayMicroseconds(1);

		p1 |= (digitalRead(P1DAT_PIN) << i);
	}

	*p1data = ~p1;
}