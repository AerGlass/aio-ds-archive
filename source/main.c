// WARNING: THIS IS MADE TO MAKE IT NOOB-PROOF AS POSSIBLE, THERE ARE A LOT OF INSTRUCTIONS. BUT IF YOU DON'T UDERSTAND WHAT THIS IS
// THEN DO NOT CONTINUE, IF YOU ARE A NOOB, THEN IS OK. LEARN FROM IT
// I am not responsible for damages THAT THIS PROGRAM MAY CAUSE 


// MORE NOTES FOR NOOBS: what you need
// devkitarm (included on devkitpro), some way to edit this file and a BRAIN.


#include <nds.h>
#include <stdio.h>
#define FRAMES_PER_ANIMATION 3
#include "drunkenlogo.h"
#include "font.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

volatile int frame = 0;

//---------------------------------------------------------------------------------
void Vblank() {
//---------------------------------------------------------------------------------
	frame++;
}
	
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
// init some thing (I don't understand what this is).
		touchPosition touchXY;
		
	const int tile_base = 0;
	const int map_base = 20;
	
		videoSetModeSub(MODE_0_2D);	
	vramSetBankC(VRAM_C_SUB_BG); 
	
	PrintConsole *console = consoleInit(0,0, BgType_Text4bpp, BgSize_T_256x256, map_base, tile_base, false, false);
		
	PrintConsole topScreen;
	PrintConsole bottomScreen;
	
		videoSetModeSub(MODE_0_2D);	
	vramSetBankC(VRAM_C_SUB_BG); 
	
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);

	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);

	videoSetMode(MODE_5_2D);

	videoSetModeSub(MODE_0_2D);
	
	consoleInit(&topScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
	consoleInit(&bottomScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);

		
	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();
	

	// Configure font
	ConsoleFont font;

	font.gfx = (u16*)fontTiles;
	font.pal = (u16*)fontPal;
	font.numChars = 95;
	font.numColors =  fontPalLen / 2;
	font.bpp = 4;
	font.asciiOffset = 32;
	font.convertSingleColor = false;
	
	consoleSetFont(console, &font);
	
	// print text
	
	printf("\x1b[01;00H All In One Program pack TCH562");
	printf("\x1b[02;00H A= Button Tester.");
	printf("\x1b[03;00H B= Spamer");
	printf("\x1b[04;00H Y= Animate Simple :D");
	printf("\x1b[05;00H Start= Exit");
	printf("\x1b[06;00H Just a simple program :D Is in development");
	
	consoleSelect(&bottomScreen);
	
	bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);
	
	decompress(drunkenlogoBitmap, BG_GFX,  LZ77Vram);
	
	
//loop forever
	while(1) {
	//scan keys
		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		
// if pressed start, power off the system
		if (keys & KEY_START) break;

		touchRead(&touchXY); 
		// if you press A it will start button tester
							// Loop forever.
		if (keys & KEY_A)	{ 
	printf("\e[1;1H\e[2J");
		printf("I HAZ SUCCESS");
		while(1) {
			
// scan keys
		touchRead(&touchXY);
		swiWaitForVBlank();
		scanKeys();
		int keys = keysDown();
		if (keys & KEY_START) break;

		touchRead(&touchXY);
		//Button tester source code
		//updated to support more buttons, also, clean up the screen.
		consoleSelect(&bottomScreen);
	if(keys & KEY_A) printf("\e[1;1H\e[2J");
	if(keys & KEY_A) printf("\x1b[16;02HYou Pressed A Button!");
	if(keys & KEY_B) printf("\e[1;1H\e[2J");
	if(keys & KEY_B) printf("\x1b[16;02HYou Pressed B Button!");
	if(keys & KEY_Y) printf("\e[1;1H\e[2J");
	if(keys & KEY_Y) printf("\x1b[16;02HYou Press Y Button");
	if(keys & KEY_X) printf("\e[1;1H\e[2J");
	if(keys & KEY_X) printf("\x1b[16;02HYou Press X Button");
	if(keys & KEY_R) printf("\e[1;1H\e[2J");
	if(keys & KEY_R) printf("\x1b[16;02HYou Press R");
	if(keys & KEY_L) printf("\e[1;1H\e[2J");
	if(keys & KEY_L) printf("\x1b[16;02HYou press L");
	if(keys & KEY_UP) printf("\e[1;1H\e[2J");
	if(keys & KEY_UP) printf("\x1b[16;02HYou press DPAD UP");
	if(keys & KEY_DOWN) printf("\e[1;1H\e[2J");
	if(keys & KEY_DOWN) printf("\x1b[16;02HYou press DPAD DOWN");
	
	if(keys & KEY_RIGHT) printf("\e[1;1H\e[2J");
	if(keys & KEY_RIGHT) printf("\x1b[16;02HYou press DPAD RIGHT");
	if(keys & KEY_LEFT) printf("\e[1;1H\e[2J");
	if(keys & KEY_LEFT) printf("\x1b[16;02HYou press DPAD LEFT");
	
	if (keys & KEY_START) break;
		}

	}
	if (keys & KEY_B) {
		while (1)	{
			// spammer source code. bruh
	consoleSelect(&topScreen);
		printf(ANSI_COLOR_BLUE" NO SI NO SI");
		printf(ANSI_COLOR_RED"SI NO SI NO");
		consoleSelect(&bottomScreen);
		printf(ANSI_COLOR_BLUE" NO SI NO SI");
		printf(ANSI_COLOR_RED"SI NO SI NO");
	}
	}
	
	}


	return 0;
}