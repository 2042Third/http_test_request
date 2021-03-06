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
 
std::string test_user="username3";
/**
 * From https://curl.se/libcurl/c/ftpget.html
 * */
struct FtpFile {
  const char *filename;
  FILE *stream;
};

/**
 * Writes the file to local disk.
 * Modification: Overwrites the file if t file of the same name exists.
 * 
 * Parts from https://curl.se/libcurl/c/ftpget.html
 * */
static size_t my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
  struct FtpFile *out = (struct FtpFile *)stream;
  if(!out->stream) {

    out->stream = fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure, can't open file to write */
  }
  return fwrite(buffer, size, nmemb, out->stream);
}

void upload_sync_multi(std::string fname){
    std::string file_name=fname;
    CURL *curl;
    CURLcode res;

    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;
    struct curl_slist *headerlist = NULL;
    static const char buf[] = "Expect:";

    curl_global_init(CURL_GLOBAL_ALL);

    /* Fill in the file upload field */
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "file",
                 CURLFORM_FILE, (file_name).c_str(),
                 CURLFORM_END);

    /* Fill in the filename field */
    curl_formadd(&formpost,
                 &lastptr,
                 CURLFORM_COPYNAME, "user_name",
                 CURLFORM_COPYCONTENTS, (test_user).c_str(),
                 CURLFORM_END);


    // /* Fill in the submit field too, even if this is rarely needed */
     curl_formadd(&formpost,
                  &lastptr,
                  CURLFORM_COPYNAME, "serv_type",
                  CURLFORM_COPYCONTENTS, "pdm_note_sync",
                  CURLFORM_END);

    curl = curl_easy_init();
    /* initialize custom header list (stating that Expect: 100-continue is not
       wanted */
    headerlist = curl_slist_append(headerlist, buf);
    if(curl) {
        /* what URL that receives this POST */
        curl_easy_setopt(curl, CURLOPT_URL, "https://pdm.pw/file_up/UploadServlet");
        // if((argc == 2) && (!strcmp(argv[1], "noexpectheader")))
        //   curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Skip peer
        // curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // Skip host
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);

        /* then cleanup the formpost chain */
        curl_formfree(formpost);
        /* free slist */
        curl_slist_free_all(headerlist);
    }
}

void download_sync(std::string fname){
  std::string file_name = fname;
  CURL *curl;
  CURLcode res;
  struct FtpFile ftpfile = {
    "synced_file", /* name to store the file as if successful */
    // ((const char*) ("downloaded_"+file_name).c_str()), /* name to store the file as if successful */
    NULL
  };
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL,
                     // ("pdm.pw:8080/file_up/download/test_file.txt"));
                     ("https://pdm.pw/file_up/download/"+test_user+"/"+file_name).c_str());

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // Skip peer
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
 

    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
 
    res = curl_easy_perform(curl);
 
    curl_easy_cleanup(curl);
    if(CURLE_OK != res) {
      fprintf(stderr, "failure caused by: %d\n", res);
    }
  }
  if(ftpfile.stream)
    fclose(ftpfile.stream); /* close the local file */
  curl_global_cleanup();
}

// #ifdef LIB_VERSION
int main(int argc, char *argv[])
{
  upload_sync_multi("test_file.txt");
  download_sync("test_file.txt");
  return 0;
}
// #endif
