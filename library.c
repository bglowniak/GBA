#include "library.h"

void waitForVblank() {
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void delay(int n) {
	volatile int size = 0;
	for(int i = 0; i < n * 4000; i++) {
		size = size + 1;
	}
}
