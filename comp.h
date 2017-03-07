#ifndef _SHOP
	#define _SHOP
	#define TRUE 1
	#define NAME_LEN 30
	#define TYPE_LEN 10
	#define FORMAT_LEN TYPE_LEN
	#define SOCKET_LEN NAME_LEN
	#define COUNT 50
	#define PARTS_COUNT (4 * COUNT / 5)
	#define QUERY_LEN 50
	#define MIN_LEN 3
	#define MAX_LEN 30
	#define MAX_RESULTS 10
	#define PARTS_TYPE_COUNT COMPUTER
	#define MIN(A, B) ((A) < (B) ? A : B)

	enum product_type {DISPLAY, MOTHERBOARD, PROCESSOR, RAM, COMPUTER, PRODUCT_TYPE_COUNT};

	typedef void (*pfunction)(struct item *);

	struct common_fields {
		char name[NAME_LEN];
		char producer[NAME_LEN];
		int id;
		unsigned price;
		unsigned count;
	};

	struct display {
		char type[TYPE_LEN];
		int diagonal;
	};

	struct motherboard {
		char format[FORMAT_LEN];
		char processor_socket[SOCKET_LEN];
	};

	struct processor {
		int speed_mhz;
		int cores_number;
		int cache[3];
	};

	struct ram {
		int memory_mb;
		char type[TYPE_LEN];
	};

	struct computer {
		struct item *parts[PARTS_TYPE_COUNT];
	};

	struct item {
		struct common_fields common;
		int product_type;
		union {
			struct display disp;
			struct motherboard mboard;
			struct processor proc;
			struct ram ram_mem;
			struct computer comp;
		} product;
	};

	struct search_result {
		struct item *items[MAX_RESULTS];
		unsigned count;
	};

	struct order {
		int id;
		unsigned count;
	};

	struct item items[COUNT];

	void new_item(struct item *it, int id, int type);

	struct search_result find(char *query);

	void item_print(struct item *item);

	void print(struct item *items, unsigned count);

	int order_dialog();

#endif