inc = -I./include
lib = -L./lib
inc_mac = -I./include_mac
lib_mac = -L./lib_mac
flg_win = -DCURL_STATICLIB -lcurl -lws2_32 -lwldap32
flg = -DCURL_STATICLIB -lcurl 
windows: 
	g++ http_test.cpp -o http_test -std=c++11 -I.. -Wall -Wextra -pthread $(flg_win) $(lib) $(inc)  -m64
linux: 
	g++ http_test.cpp -o http_test -std=c++11 -I.. -Wall -Wextra -pthread $(flg) $(lib_mac) $(inc_mac)  -m64
windows_fd: 
	g++ file_down.cpp -o file_down -std=c++11 -I.. -Wall -Wextra -pthread $(flg_win) $(lib) $(inc)  -m64
windows-clang: 
	clang++ http_test.cpp -o http_test -std=c++11 -I.. -Wall -Wextra -pthread $(flg_win) $(lib) $(inc) -m64