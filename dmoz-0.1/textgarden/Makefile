#
# TextGarden makefile
#

include ./Makefile.config

# dependencies
LIBUV = ../libuv
GLIB = ../glib

# library headers include
GLIB_BASE = $(GLIB)/base/
GLIB_NET = $(GLIB)/net/
GLIB_MINE = $(GLIB)/mine/
INCLUDE = -I. -I$(GLIB_BASE) -I$(GLIB_NET) -I$(GLIB_MINE) -I$(LIBUV)

# lib includes
STATIC_LIBS = $(GLIB)/glib.a $(LIBUV)/libuv.a

# main object files
MAINOBJS = DMozClassify/DMozClassify.o \
	DMozClassifyServer/DMozClassifyServer.o

all: $(MAINOBJS)
	# compile glib
	make -C $(GLIB)
	# create commandline tools
	$(CC) -o dmozClassify DMozClassify.o $(STATIC_LIBS) $(LDFLAGS) $(LIBS) 
	$(CC) -o dmozClassifyServer DMozClassifyServer.o $(STATIC_LIBS) $(LDFLAGS) $(LIBS) 

%.o: %.cpp
	$(CC) -c $(CXXFLAGS) $< $(INCLUDE) $(LDFLAGS) $(LIBS)
	
cleanall: clean
	make -C ../glib clean

clean:
	rm -f *.o *.gch *.a dmozClassify dmozClassifyServer

