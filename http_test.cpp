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
 

void upload_sync(std::string fname){
  std::string file_name=fname;
  CURL *curl;
  CURLcode res;
 
  curl_mime *form = NULL;
  curl_mimepart *field = NULL;
  struct curl_slist *headerlist = NULL;
  static const char buf[] = "Expect:";
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  curl = curl_easy_init();
  if(curl) {
    form = curl_mime_init(curl);
    field = curl_mime_addpart(form);
    curl_mime_name(field, "sendfile");
    curl_mime_filedata(field, (file_name).c_str());
 
    field = curl_mime_addpart(form);
    curl_mime_name(field, "filename");
    curl_mime_data(field, (file_name).c_str(), CURL_ZERO_TERMINATED);
 
    field = curl_mime_addpart(form);
    curl_mime_name(field, "submit");
    curl_mime_data(field, "send", CURL_ZERO_TERMINATED);
 
    headerlist = curl_slist_append(headerlist, buf);
    curl_easy_setopt(curl, CURLOPT_URL, "pdm.pw:8080/file_up/UploadServlet");
    // if((argc == 2) && (!strcmp(argv[1], "noexpectheader")))
    //   curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
 
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    curl_easy_cleanup(curl);
 
    curl_mime_free(form);
    curl_slist_free_all(headerlist);
  }
}

int main(int argc, char *argv[])
{
  upload_sync("test_file.txt");
  download_sync("test_file.txt");
  return 0;
}