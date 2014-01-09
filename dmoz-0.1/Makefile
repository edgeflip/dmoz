#
# TextGarden makefile
#

include ./textgarden/Makefile.config

# dependencies
LIBUV = libuv
GLIB = glib

# library headers include
GLIB_BASE = $(GLIB)/base/
GLIB_NET = $(GLIB)/net/
GLIB_MINE = $(GLIB)/mine/
INCLUDE = -I. -I$(GLIB_BASE) -I$(GLIB_NET) -I$(GLIB_MINE) -I$(LIBUV)

# lib includes
STATIC_LIBS = $(GLIB)/glib.a $(LIBUV)/libuv.a

# main object files
MAINOBJS = textgarden/DMozClassify/DMozClassify.o \
	textgarden/DMozClassifyServer/DMozClassifyServer.o

all: $(MAINOBJS)
	# compile glib
	make -C $(GLIB)
	# create commandline tools
	$(CC) -o textgarden/dmozClassify DMozClassify.o $(STATIC_LIBS) $(LDFLAGS) $(LIBS) 
	$(CC) -o textgarden/dmozClassifyServer DMozClassifyServer.o $(STATIC_LIBS) $(LDFLAGS) $(LIBS) 
	mkdir -p debian/tmp/usr/bin
	cp textgarden/dmozClassify debian/tmp/usr/bin/
	cp textgarden/dmozClassifyServer debian/tmp/usr/bin/
	cp textgarden/Top.BowPart debian/tmp/usr/bin/
	cp textgarden/Top.Bow debian/tmp/usr/bin/

%.o: %.cpp
	$(CC) -c $(CXXFLAGS) $< $(INCLUDE) $(LDFLAGS) $(LIBS)
	
cleanall: clean
	make -C glib clean

clean:
	rm -f textgarden/*.o textgarden/*.gch textgarden/*.a textgarden/dmozClassify textgarden/dmozClassifyServer

