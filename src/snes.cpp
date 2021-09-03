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

void snes_read(uint16_t *p1data, uint16_t *p2data) {
	uint16_t p1, p2;

	digitalWrite(LATCH_PIN, LOW);
	digitalWrite(CLOCK_PIN, LOW);

	digitalWrite(LATCH_PIN, HIGH);
	delayMicroseconds(1);
	digitalWrite(LATCH_PIN, LOW);
	delayMicroseconds(1);

	p1 = digitalRead(P1DAT_PIN);
	p2 = digitalRead(P2DAT_PIN);

	for(int i = 1; i < 16; i++) {
		digitalWrite(CLOCK_PIN, HIGH);
		delayMicroseconds(1);
		digitalWrite(CLOCK_PIN, LOW);
		delayMicroseconds(1);

		p1 |= (digitalRead(P1DAT_PIN) << i);
		p2 |= (digitalRead(P2DAT_PIN) << i);
	}

	*p1data = ~p1;
	*p2data = ~p2;
}