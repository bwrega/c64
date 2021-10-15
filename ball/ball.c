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
	%01111111,%11111111,%11111100,
	%00111111,%11111111,%11111100,
	%00011111,%11111111,%11111000,
	%00001111,%11111111,%11110000,
	%00000011,%11111111,%11000000,
	%00000000,%11111111,%00000000
};

int spriteX = 100 << 3;
int spriteY = 100 << 3;
int vx = 5;
int vy = 0;
const byte gravity = 1;
const int BORDER_LEFT = BORDER_XPOS_LEFT << 3;
const int BORDER_RIGHT = (BORDER_XPOS_RIGHT - 24) << 3;
const int BORDER_TOP = BORDER_YPOS_TOP << 3;
const int BORDER_BOTTOM = (BORDER_YPOS_BOTTOM - 21) << 3;

void main() {
	clearScr();
	showSprite(0, spriteX>>3, (byte)(spriteY>>3));
	byte * SPRITE_POINTER = DEFAULT_SCREEN + OFFSET_SPRITE_PTRS;
	*SPRITE_POINTER = toSpritePtr(BALL_SPRITE);
	*SPRITES_COLOR = RED;
	*SPRITES_ENABLE = 1;
	VICII->BORDER_COLOR = DARK_GREY;
	VICII->BG_COLOR = BLACK;
	while(1) {
		while (*RASTER < BORDER_YPOS_BOTTOM) {};
		VICII->BORDER_COLOR = RED;

		moveSprite();
		animateSprite();
		showSprite(0, spriteX >> 3, (byte)(spriteY >> 3));
		VICII->BORDER_COLOR = DARK_GREY;
		while (*RASTER >= BORDER_YPOS_BOTTOM) {};
	}
}

void moveSprite() {
	byte joy_read = ~(CIA1->PORT_A);
	if (joy_read & 1) {
		vy -= 1;
	}
	if (joy_read & 2) {
		vy += 1;
	}
	if (joy_read & 4) {
		vx -= 1;
	}
	if (joy_read & 8) {
		vx += 1;
	}
}

void animateSprite() {
	vy = vy + gravity;
	spriteX += vx;
	spriteY += vy;
	if (spriteX <= BORDER_LEFT && vx < 0) {
		vx = -vx;
	}
	if (spriteX >= BORDER_RIGHT && vx > 0) {
		vx = -vx;
	}
	if (spriteY <= BORDER_TOP && vy < 0) {
		vy = -vy;
	}
	if (spriteY >= BORDER_BOTTOM && vy > 0) {
		vy = -vy;
	}
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


