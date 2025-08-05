#ifndef NEW_H
#define NEW_H
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>

void extract_text(xmlNodePtr node, char **text, int *text_len);
char *html2txt(char *html);
int masterrrr();

#endif
