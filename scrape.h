#ifndef SCRAPE_H
#define SCRAPE_H
#include <stddef.h>

typedef struct {
	char *content;
	size_t size;
} Wikitext;

Wikitext *scrape();

#endif
