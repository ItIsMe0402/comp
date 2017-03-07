#include <stdio.h>
#include "comp.h"

void print_commons(struct common_fields common) {
	printf("%s (#%d) by %s: price=%d, count=%d\n", common.name, common.id, common.producer, common.price, common.count);
}

void print_display_props(struct item *it) {
	struct display disp = it->product.disp;
	printf("\t%s %d\" monitor\n", disp.type, disp.diagonal);
}

void print_motherboard_props(struct item *it) {
	struct motherboard mboard = it->product.mboard;
	printf("\tformat: %s, socket: %s\n", mboard.format, mboard.processor_socket);
}

void print_processor_props(struct item *it) {
	struct processor proc = it->product.proc;
	printf("\t%d-core @ %d MHz\n", proc.cores_number, proc.speed_mhz);
}

void print_ram_props(struct item *it) {
	struct ram ram_mem = it->product.ram_mem;
	printf("\t%dmb %s RAM\n", ram_mem.memory_mb, ram_mem.type);
}

void print_computer_props(struct item *it) {
	int i;
	struct item **parts = it->product.comp.parts;
	for (i = 0; i < PARTS_TYPE_COUNT; i++) {
		printf("\t");
		item_print(parts[i]);
	}
}

pfunction print_type_props[PRODUCT_TYPE_COUNT] = {&print_display_props, &print_motherboard_props, &print_processor_props, &print_ram_props, &print_computer_props};

void item_print(struct item *item) {
	print_commons(item->common);
	print_type_props[item->product_type](item);
}

void print(struct item *items, unsigned count) {
	struct item *item;
	unsigned i;
	for (i = 0; i < count; i++) {
		item = items + i;
		item_print(item);
		printf("\n");
	}
}