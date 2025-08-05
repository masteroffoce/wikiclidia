#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "scrape.h"

static size_t write_callback(void *contents, size_t size, size_t amount, void *userp) {
	int real_size = size * amount;
	Wikitext *mem = (Wikitext *)userp;

	if (!mem || !contents) {
		fprintf(stderr, "Invalid input to write_callback.");
		return 1;
	}

	char *ptr = realloc(mem->content, mem->size + real_size + 1); //In case realloc fails, we have old mem
	if (!ptr) {
		fprintf(stderr, "Realloc failed.");
		return 1;
	}

	mem->content = ptr;

	memcpy(&(mem->content[mem->size]), contents, real_size); //Append data, might come in chunks
	mem->size += real_size;
	mem->content[mem->size] = '\0';

	return real_size;
}


/*
void scrape() {
	CURL *curl;
	CURLcode result;

	Memory chunk = {0};
	chunk.data = malloc(1); //Realloc when it's used
	chunk.size = 0;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://en.wikipedia.org/api/rest_v1/page/html/Dihydrogen_monoxide_parody");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
	}

		result = curl_easy_perform(curl);
		if (result != CURLE_OK)
			fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(result));

		printf("%s",chunk.data);
		free(chunk.data);
		curl_easy_cleanup(curl);

	curl_global_cleanup();
}
*/

Wikitext *scrape() {
	CURL *curl;
	CURLcode result;

	Wikitext *chunk = malloc(sizeof(Wikitext));
	chunk->content = malloc(1);
	chunk->size = 0;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl) {
		//curl_easy_setopt(curl, CURLOPT_URL, "https://en.wikipedia.org/api/rest_v1/page/html/Dihydrogen_monoxide_parody");
		curl_easy_setopt(curl, CURLOPT_URL, "https://en.wikipedia.org/api/rest_v1/page/html/Dog");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)chunk);
	}

	result = curl_easy_perform(curl);
	if (result != CURLE_OK)
		fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(result));

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	return chunk;
}
