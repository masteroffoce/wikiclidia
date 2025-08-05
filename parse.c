#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/HTMLparser.h>
#include <libxml/tree.h>
#include "scrape.h"

void print_text_nodes(xmlNode *node);
void html_to_text(const char *html);
void master();
void parse(Wikitext *text);
void add_nodes(Wikitext *text, xmlNode *root);

void master() {
	FILE *file = fopen("html.txt", "r");
	if (file == NULL) {
		fprintf(stderr, "Couldn't read file.");
		return;
	}

	fseek(file, 0, SEEK_END);
	int filesize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *buffer = malloc(filesize + 1);
	if (buffer == NULL) {
		fprintf(stderr, "Memory alloc failed.");
		fclose(file);
		return;
	}

	size_t size = fread(buffer, 1, filesize - 1, file);
	buffer[size] = '\0';
	
	html_to_text(buffer);
	free(buffer);
}

void parse(Wikitext *text) {
	htmlDocPtr doc = htmlReadMemory(text->content, (int)strlen(text->content), NULL, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING );

	xmlNode *root = xmlDocGetRootElement(doc);

	text->content[0] = '\0';

	add_nodes(text, root);


}

void add_nodes(Wikitext *text, xmlNode *root) {
	for (xmlNode *cur = root; cur != NULL; cur = cur->next) {
		if (cur->type == XML_TEXT_NODE) {
			int len = snprintf(NULL, 0, "%s", cur->content);
			size_t len2 = strlen(text->content) + len + 1;
			text->content = realloc(text->content, len2);
			strcat(text->content, (char *)cur->content);
		}
		add_nodes(text, cur->children);
	}
}


void print_text_nodes(xmlNode *node) {
	for (xmlNode *cur = node; cur != NULL; cur = cur->next) {
		if (cur->type == XML_TEXT_NODE) {
			printf("%s", (char *)cur->content);
		}
		print_text_nodes(cur->children);
	}
}

void html_to_text(const char *html) {
	if (html == NULL) {
		fprintf(stderr, "Input string is NULL");
		return;
	}

	htmlDocPtr doc = htmlReadMemory(html, (int)strlen(html), NULL, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING );
	if (doc == NULL) {
		fprintf(stderr, "Empty but not NULL HTML document.");
		return;
	}

	xmlNode *root = xmlDocGetRootElement(doc);
	if (root == NULL) {
		fprintf(stderr, "Empty HTML document. If you're here, something has gone terribly wrong. :(");
		xmlFreeDoc(doc);
		return;
	}

	print_text_nodes(root);
	
	xmlFreeDoc(doc);
	xmlCleanupParser();
}

