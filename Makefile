inc = -I./include
lib = -L./lib
flg_win = -DCURL_STATICLIB -lcurl -lws2_32 -lwldap32
windows: 
	g++ http_test.cpp -o http_test -std=c++11 -I.. -Wall -Wextra -pthread $(flg_win) $(lib) $(inc)  -m64
windows-clang: 
	clang++ http_test.cpp -o http_test -std=c++11 -I.. -Wall -Wextra -pthread $(flg_win) $(lib) $(inc) -m64