#ifndef PARSE_H
#define PARSE_H
#include "scrape.h"

//void print_text_nodes(xmlNode *node);
void html_to_text(const char *html);
void master();
void parse(Wikitext *text);

#endif
