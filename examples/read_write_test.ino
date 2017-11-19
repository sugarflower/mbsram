#include <Gamebuino.h>
#include <mbsram.h>
#include <SPI.h>

Gamebuino gb;
mbsram sram;

uint16_t address;
uint8_t data;
boolean running;

//game initialize
void game_init(){
	sram.begin();
	SPI.begin();
        gb.pickRandomSeed();
	gb.frameCount = LCDWIDTH*8;
	gb.setFrameRate(30);
	address = 0;
	running = true;
}

void setup() {
	gb.begin();
	gb.titleScreen(F("SRAM Test"));
	game_init();
}

void loop() {
	if(gb.update()) {
		if( !running ){
			gb.display.println("Test End. All OK!");	
		} else {
			gb.display.println("SRAM read write Test");
			gb.display.print("Address:");
			gb.display.println(address);
			
			data = random(256);

			// write data
			sram.write(address,data);
		
			// read and check data
			if( data == sram.read(address) ){
				gb.display.println("is OK!");
				address ++;
				if( address == 0 ){
					running = false;
				}
			} else {
				gb.display.println("is Error!");	
			}
		}
		if(gb.buttons.pressed(BTN_C)) {
			init();
			gb.titleScreen(F("SRAM Test"));
		}
	}
}
