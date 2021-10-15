#include <c64.h>
#include <stdio.h>


__address(0x2000) const byte[] BALL_SPRITE = {
	%00000000,%11111111,%00000000,
	%00000011,%11111111,%11100000,
	%00001111,%11111111,%11110000,
	%00011111,%11111111,%11111000,
	%00111111,%11111111,%11111100,
	%01111111,%11111111,%11111100,
	%01111111,%11111111,%11111110,
	%01111111,%11111111,%11111110,
	%11111111,%11111111,%11111111,
	%11111111,%11111111,%11111111,
	%11111111,%11111111,%11111111,
	%11111111,%11111111,%11111111,
	%11111111,%11111111,%11111111,
	%01111111,%11111111,%11111110,
	%01111111,%11111111,%11111110,
	%00111111,%11111111,%11111100,
	%00011111,%11111111,%11111100,
	%00001111,%11111111,%11111000,
	%00000111,%11111111,%11110000,
	%00000011,%11111111,%11000000,
	%00000000,%11111111,%00000000
};

int spriteX = 100;
byte spriteY = 100;

void main() {
	clearScr();
	showSprite(0, spriteX, spriteY);
	byte * SPRITE_POINTER = DEFAULT_SCREEN + OFFSET_SPRITE_PTRS;
	*SPRITE_POINTER = toSpritePtr(BALL_SPRITE);
	*SPRITES_ENABLE = 1;
	int sleepCounter = 0;
	while(1) {
		sleepCounter ++ ;
		if (sleepCounter < 1000) {
			continue;
		} else {
			sleepCounter = 0;
		}
		moveSprite();
	}
}

void moveSprite() {
	const byte* JOYSTICK = 56320;
	byte joy_read = (* JOYSTICK) ^ 0xff;
	if (joy_read & 1) {
		spriteY -= 1;
	}
	if (joy_read & 2) {
		spriteY += 1;
	}
	if (joy_read & 4) {
		spriteX -= 1;
	}
	if (joy_read & 8) {
		spriteX += 1;
	}
	showSprite(0, spriteX, spriteY);
}

void clearScr() {
	byte *screen = 0x400;
	for (int y = 0 ; y<25 ; y++) {
		for (int x = 0 ; x<40 ; x++) {
			screen[y*40+x] = 32;
		}
	}
}

void showSprite(byte spriteNo, int x, byte y) {
	SPRITES_XPOS[spriteNo] = (byte) x;
	SPRITES_YPOS[spriteNo] = y;
	if (x > 255) {
		*SPRITES_XMSB |= 1 << spriteNo;
	} else {
		*SPRITES_XMSB &= ~(1 << spriteNo);
	}
}


