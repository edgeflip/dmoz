#include "net.h"

// code without dependancy to networking layer
#include "geoip.cpp"

// windows system libs required by libuv

#ifdef GLib_WIN
	#pragma comment(lib, "psapi.lib")
	#pragma comment(lib, "WS2_32.lib")
	#pragma comment(lib, "IPHLPAPI.lib")
	// include external libuv
	#include "libuv/uv.h"
#else
	// include external libuv
	typedef size_t ULONG;
	#include <uv.h>
#endif
// wrapper around libuv
#include "socksys.cpp"
// pure glib implementation
#include "sock.cpp"
// web-client
#include "webpgfetch.cpp"
// web-server
#include "websrv.cpp"
// app-server
#include "sappsrv.cpp"
