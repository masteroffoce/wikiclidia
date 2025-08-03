#include <stdio.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
#include <libxml/HTMLparses.h>
#include <libxml/tree.h>

int main() {
	CURL *curl;
	CURLcode res;
	char *data = NULL;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://en.wikipedia.org/api/rest_v1/page/html/Dihydrogen_monoxide_parody");
	}

		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));

		curl_easy_cleanup(curl);
		free(data);

	curl_global_cleanup();

	return 0;
}
