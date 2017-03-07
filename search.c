#include <stdlib.h>
#include <string.h>
#include "comp.h"
#define MAX_PARAMS 3
#define STARTS_WITH(STR, PREFIX) STR == strchr(STR, PREFIX)
#define CHKXASGN(RES) if (RES.count < MAX_RESULTS) RES.items[res.count++] = item; else return RES

struct parse_return {
	int argc;
	char argv[MAX_PARAMS][MAX_LEN];
};

void strncpy0(char *dest, char *source, int len) {
	strncpy(dest, source, len);
	dest[len] = '\0';
}

struct parse_return parse_query(char *query) {
	struct parse_return ret;
	int argc = 0;
	char *prev;
	while (argc < MAX_PARAMS) {
		prev = query;
		query = strstr(query, " -");
		if (query != NULL)
			strncpy0(ret.argv[argc++], prev, MIN(query - prev, MAX_LEN));
		else {
			strncpy0(ret.argv[argc++], prev, MAX_LEN);
			ret.argc = argc;
			return ret;
		}
		query += 2;
	}
	ret.argc = 0;
	return ret;
}

enum fields {NAME, ID, PRODUCER, FIELDS_COUNT};

char make_mask(int argc, char (*argv)[MAX_LEN]) {
	int i, j;
	char mask = 0;
	char params[MAX_PARAMS] = {'n', 'd', 'p'};
	for (i = 1; i < argc; i++)
		for (j = 0; j < MAX_PARAMS; j++)
			if (STARTS_WITH(argv[i], params[j]))
				mask |= 1 << j;
	if (mask == 0)
		mask = 1;
	return mask;
}

struct search_result find_items(int argc, char (*argv)[MAX_LEN]) {
	int i, id = atoi(argv[0]);
	struct item *item;
	struct search_result res;
	char mask = make_mask(argc, argv);
	res.count = 0;
	for (i = 0; i < COUNT; i++) {
		item = items + i;
		if (mask & 1 && (strstr(item->common.name, argv[0]) != NULL))
			CHKXASGN(res);
		else if (mask & 2 && item->common.id == id)
			CHKXASGN(res);
		else if (mask & 4 && (strstr(item->common.producer, argv[0]) != NULL))
			CHKXASGN(res);
	}
	return res;
}

struct search_result find(char *query) {
	struct search_result res;
	struct parse_return args = parse_query(query);
	free(query);
	if (args.argc == 0) {
		res.count = 0;
		return res;
	}
	res = find_items(args.argc, args.argv);
	return res;
}