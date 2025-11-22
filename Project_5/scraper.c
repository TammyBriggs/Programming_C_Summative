#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <curl/curl.h>

#define MAX_URLS 5

// Struct to pass data to the thread function
typedef struct {
    int id;
    char url[256];
    char filename[50];
} DownloadRequest;

// Helper function: CURL needs this to write received data to a file
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}

// THE WORKER THREAD FUNCTION
// This runs in parallel for each URL
void *download_page(void *args) {
    DownloadRequest *req = (DownloadRequest *)args;
    CURL *curl;
    CURLcode res;
    FILE *fp;

    printf("[Thread %d] Starting download: %s\n", req->id, req->url);

    curl = curl_easy_init();
    if (curl) {
        // Open file for writing
        fp = fopen(req->filename, "wb");
        if (!fp) {
            fprintf(stderr, "[Thread %d] Error opening file %s\n", req->id, req->filename);
            curl_easy_cleanup(curl);
            return NULL;
        }

        // Configure CURL options
        curl_easy_setopt(curl, CURLOPT_URL, req->url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L); // Fail on 404 errors

        // Perform the request (Blocking, but only blocks THIS thread)
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "[Thread %d] Download Failed: %s\n", req->id, curl_easy_strerror(res));
        } else {
            printf("[Thread %d] Finished! Saved to %s\n", req->id, req->filename);
        }

        // Cleanup
        fclose(fp);
        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "[Thread %d] Failed to init curl.\n", req->id);
    }

    return NULL;
}

int main() {
    pthread_t threads[MAX_URLS];
    DownloadRequest requests[MAX_URLS];
    
    // List of URLs to scrape
    const char *urls[] = {
        "https://www.google.com",
        "https://www.fifa.com",
        "https://www.alueducation.com",
        "https://www.instructure.com",
        "https://invalid-url-for-testing.com" // This tests error handling
    };

    int num_urls = 5;

    // Initialize CURL global state (must be done once in main)
    curl_global_init(CURL_GLOBAL_ALL);

    printf("=== Starting Multi-threaded Web Scraper ===\n");

    // 1. CREATE THREADS
    for (int i = 0; i < num_urls; i++) {
        requests[i].id = i + 1;
        strcpy(requests[i].url, urls[i]);
        sprintf(requests[i].filename, "file_%d.txt", i + 1);

        // pthread_create(thread_pointer, attributes, function, argument)
        if (pthread_create(&threads[i], NULL, download_page, &requests[i]) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    // 2. JOIN THREADS (Wait for all to finish)
    for (int i = 0; i < num_urls; i++) {
        pthread_join(threads[i], NULL);
    }

    // Cleanup Global State
    curl_global_cleanup();
    printf("=== All downloads complete. Check your directory. ===\n");

    return 0;
}
