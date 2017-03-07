#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "comp.h"

char *dialog_query() {
	int c, i;
	char *query = (char *) malloc(MAX_LEN * sizeof(char));
	fflush(stdin);
	printf("type your query> ");
	fgets(query, MAX_LEN, stdin);
	for (i = 0; i < MAX_LEN; i++)
		if ((c = query[i]) != ' ' && isspace(c)) {
			query[i] = '\0';
			break;
		}
	return query;
}

unsigned dialog_count() {
	unsigned count;
	fflush(stdin);
	printf("\ntype count to purchase> ");
	fscanf(stdin, "%d", &count);
	return count;
}

int dialog_confirmed(struct item it, int count) {
	char c;
	fflush(stdin);
	do {
		printf("\nYou will pay %d, are you agree? (y/n) > ", it.common.price * count);
		c = getchar();
		if(c == 'y')
			return 1;
		else if(c == 'n')
			return 0;
	} while(TRUE);
}

void substract_count(struct item *it, unsigned count) {
	unsigned *p_old_count;
	if(it->product_type == COMPUTER) {
		int i;
		struct computer *comp = &it->product.comp;
		for (i = 0; i < COMPUTER; i++) {
			p_old_count = &comp->parts[i]->common.count;
			*p_old_count = *p_old_count - count;
		}
	} else {
		p_old_count = &it->common.count;
		*p_old_count = *p_old_count - count;
	}
}

int choose_item(struct search_result res) {
	unsigned n;
	do {
		printf("\nType your product's number in result set > ");
		fscanf(stdin, "%d", &n);
	} while(n < 1 || n > res.count);
	return n - 1;
}

int order_dialog() {
	unsigned n, order_count;
	struct search_result res;
	struct item *it;
	res = find(dialog_query());
	if(res.count == 0) {
		printf("\nNo products found\n\n");
		return 1;
	}
	for (n = 0; n < res.count; n++) {
		printf("%d) ", n + 1);
		item_print(res.items[n]);
	}
	n = choose_item(res);
	it = res.items[n];
	if(it->common.count < (order_count = dialog_count())) {
		printf("\nToo big count: max available is %d\n", it->common.count);
		return 1;
	}
	if(dialog_confirmed(*it, order_count)) {
		substract_count(it, order_count);
		printf("Success!\n");
	}
	return 0;
}