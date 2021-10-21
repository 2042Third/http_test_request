inc = -I./include
lib = -L./lib
inc_mac = -I./include_mac
inc_lin = -I./include_liux
lib_mac = -L./lib_mac
lib_lin = -L./lib_linux
flg_win = -DCURL_STATICLIB -lcurl -lws2_32 -lwldap32
flg = -DCURL_STATICLIB -lcurl 
windows: 
	g++ http_test.cpp -o http_test -std=c++11 -I.. -Wall -Wextra -pthread $(flg_win) $(lib) $(inc)  -m64
windows-lib: 
	g++ -c http_test.cpp -D LIB_VERSION -o http_lib -std=c++11 -I.. -Wall -Wextra -pthread $(flg_win) $(lib) $(inc)  -m64
mac: 
	g++ http_test.cpp -o http_lib -std=c++11 -I.. -Wall -Wextra -pthread $(flg) $(lib_mac) $(inc_mac)  -m64
linux:
	g++ http_test.cpp -o http_test -std=c++11 -I.. -Wall -Wextra -pthread $(flg) $(lib_lin) $(inc_lin)  -m64
windows_fd: 
	g++ file_down.cpp -o file_down -std=c++11 -I.. -Wall -Wextra -pthread $(flg_win) $(lib) $(inc)  -m64
windows-clang: 
	clang++ http_test.cpp -o http_test -std=c++11 -I.. -Wall -Wextra -pthread $(flg_win) $(lib) $(inc) -m64
