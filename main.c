#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "comp.h"

void init_random() {
	unsigned i;
	srand(time(NULL));
	for(i = 0; i < PARTS_COUNT; i++)
		new_item(items + i, i + 1, rand() % PARTS_TYPE_COUNT);
	for (; i < COUNT; i++)
		new_item(items + i, i + 1, PARTS_TYPE_COUNT);
}

int main() {
	char c;
	init_random();
	print(items, COUNT);
	do {
		printf("\n");
		order_dialog();
		fflush(stdin);
		printf("\npress 'q' to exit or any other key to continue > ");
	} while((c = getchar()) != 'q');
	return 0;
}