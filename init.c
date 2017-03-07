#include <stdlib.h>
#include <string.h>
#include "comp.h"

void strncpy0(char *dest, char *source, int len);

void init_commons(struct common_fields *common, char *name, char *producer, int id) {
	strncpy0(common->name, name, MIN(strlen(name), MAX_LEN - 1));
	common->id = id;
	common->count = rand() % 20 + 10;
	common->price = rand() % 50 * 10 + 1000;
	strncpy0(common->producer, producer, MIN(strlen(producer), MAX_LEN - 1));
}

char *display_types[] = {"LCD", "LED"};

void init_display_props(struct item *it) {
	struct display *disp = &it->product.disp;
	strcpy(disp->type, display_types[rand() % 2]);
	disp->diagonal = rand() % 10 + 20;
}

char *motherboard_formats[] = {"ATX", "Mini-ATX", "microATX"};
char *motherboard_processor_sockets[] = {"LGA 1151", "AM3+", "B2"};

void init_motherboard_props(struct item *it) {
	struct motherboard *mboard = &it->product.mboard;
	strcpy(mboard->format, motherboard_formats[rand() % 3]);
	strcpy(mboard->processor_socket, motherboard_processor_sockets[rand() % 3]);
}

void init_processor_props(struct item *it) {
	struct processor *proc = &it->product.proc;
	proc->cores_number = 1 + rand() % 4;
	proc->speed_mhz = 10 * (180 + rand() % 200);
	proc->cache[0] = 2;
	proc->cache[1] = 4;
	proc->cache[2] = 8;
}

int pow2(int n);

char *ram_types[] = {"DDR2", "DDR3"};

void init_ram_props(struct item *it) {
	struct ram *ram_mem = &it->product.ram_mem;
	ram_mem->memory_mb = 1 << (12 + rand() % 3);
	strcpy(ram_mem->type, ram_types[rand() % 2]);
}

struct item *get_random_part_of_type(int type) {
	int i, start_number = rand() % PARTS_COUNT;
	struct item *it;
	for (i = start_number; i < PARTS_COUNT; i++)
		if((it = items + i)->product_type == type)
			return it;
	for (i = 0; i < start_number; i++)
		if((it = items + i)->product_type == type)
			return it;
	new_item(it, -1, type);
	it->common.count = 0;
	return it;
}

void init_computer_props(struct item *it) {
	int i;
	unsigned price = 0, count = UINT_MAX;
	struct computer *comp = &it->product.comp;
	for (i = 0; i < COMPUTER; i++) {
		price += (comp->parts[i] = get_random_part_of_type(i))->common.price;
		count = MIN(count, comp->parts[i]->common.count);
	}
	it->common.price = price;
	it->common.count = count;
}

pfunction init_type_props[PRODUCT_TYPE_COUNT] = {&init_display_props, &init_motherboard_props, &init_processor_props, &init_ram_props, &init_computer_props};

char *type_producers[PRODUCT_TYPE_COUNT][2] = {
	"LG", "Samsung",
	"Asus", "MSI",
	"Intel", "AMD",
	"Gigabyte", "Kingston",
	"Lenovo", "HP"
};

void init(struct item *item, int id) {
	init_commons(&item->common, "product", type_producers[item->product_type][rand() % 2], id);
	init_type_props[item->product_type](item);
}

void new_item(struct item *it, int id, int type) {
	it->product_type = type;
	init(it, id);
}