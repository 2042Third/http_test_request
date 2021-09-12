#include "httplib.h"
// #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
// #else
#include <stdio.h>
#include <iostream>
// #endif

int main (int argc, char ** argv){
  // HTTP
  httplib::Client cli("http://pdm.pw/file_up/UploadServlet",8080);


  httplib::Params params;
  params.emplace("file", "test_file.txt");
  // auto res = cli.Post("/post", params);
  // res->status;
  // res->body;
  if(auto res = cli.Post("/post", params)){
    int tmp = res->status;
    std::cout<<tmp<<std::endl;
    if (tmp == 200) {
      std::cout << res->body << std::endl;
    }
  } else {

    auto err = res.error();
    std::cout<<"error_code="<<res.error()<<std::endl;
  }
}
