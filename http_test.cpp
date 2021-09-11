// #define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <stdio.h>

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
