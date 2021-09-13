/**
 * http c++ testing program for pdm.pw syncing.
 * 
 * Yi Yang
 * 
 * */

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <winsock2.h>
#include <windows.h>
#else
#include <iostream>
#endif

#include <stdio.h>
#include <string>
#include <curl/curl.h>

struct FtpFile {
  const char *filename;
  FILE *stream;
};
 
static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
  struct FtpFile *out = (struct FtpFile *)stream;
  if(!out->stream) {
    /* open file for writing */
    out->stream = fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure, can't open file to write */
  }
  return fwrite(buffer, size, nmemb, out->stream);
}
 
 
int main(void)
{
  CURL *curl;
  CURLcode res;
  struct FtpFile ftpfile = {
    "downed_test_file.txt", /* name to store the file as if successful */
    NULL
  };
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();
  if(curl) {
    /*
     * You better replace the URL with one that works!
     */
    curl_easy_setopt(curl, CURLOPT_URL,
                     "pdm.pw:8080/file_up/download/test_file.txt");
    /* Define our callback to get called when there's data to be written */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    /* Set a pointer to our struct to pass to the callback */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
 
    /* Switch on full protocol/debug output */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    res = curl_easy_perform(curl);
 
    /* always cleanup */
    curl_easy_cleanup(curl);
 
    if(CURLE_OK != res) {
      /* we failed */
      fprintf(stderr, "curl told us %d\n", res);
    }
  }
 
  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */
 
  curl_global_cleanup();
 
  return 0;
}