#
# GLib makefile, builds all
#

include ./Makefile.config

# library headers include
LIBUV = ../libuv/include
BASE = ./base/
MINE = ./mine/
# main object files
MAINOBJS = base.o net.o mine.o thread.o
MISCOBJS = nmobj.o htmlclean.o

#entry point
all: libuv glib

# create libuv
libuv:
	make -C ../libuv

# create glib static library
glib: $(MAINOBJS) $(MISCOBJS)
	rm -f glib.a
	ar -cvq glib.a $(MAINOBJS) $(MISCOBJS)

base.o: ./base/*.h ./base/*.cpp
	$(CC) -c $(CXXFLAGS) ./base/base.cpp $(LDFLAGS) $(LIBS)
	
net.o: ./net/*.h ./net/*.cpp
	$(CC) -c $(CXXFLAGS) ./net/net.cpp -I$(BASE) -I$(LIBUV) $(LDFLAGS) $(LIBS)

mine.o: ./mine/*.h ./mine/*.cpp
	$(CC) -c $(CXXFLAGS) ./mine/mine.cpp -I$(BASE) $(LDFLAGS) $(LIBS)

thread.o: ./concurrent/*.h ./concurrent/*.cpp ./concurrent/arch/posix/*.h ./concurrent/arch/posix/*.cpp
	$(CC) -c $(CXXFLAGS) ./concurrent/thread.cpp -I$(BASE) $(LDFLAGS) $(LIBS)
	
nmobj.o: ./misc/nmobj.h ./misc/nmobj.cpp
	$(CC) -c $(CXXFLAGS) ./misc/nmobj.cpp -I$(BASE) -I$(MINE) -I$(LIBUV) $(LDFLAGS) $(LIBS)

htmlclean.o: ./misc/htmlclean.h ./misc/htmlclean.cpp
	$(CC) -c $(CXXFLAGS) ./misc/htmlclean.cpp -I$(BASE) -I$(MINE) -I$(LIBUV) $(LDFLAGS) $(LIBS)

clean:
	#make -C ../libuv clean
	rm -f *.o *.gch *.a