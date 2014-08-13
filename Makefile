src=./src

objects=main.o ui.o readjpg.o fitsarrayvv.o

vpath %.h $(src)
vpath %.c $(src)

CC=gcc
CFLAGS=-Wall -W -O -pedantic -I$(src)
LDLIBS=-lcfitsio -pthread -ljpeg -lm

jpgtofits: $(objects) 
	@$(CC) -o jpgtofits $(objects) $(LDLIBS) 
	@rm *.o
#	./jpgtofits -f -ib.jpg

.SILENT: $(objects)

.PHONY: install

install:
	cp ./jpgtofits /usr/local/bin/
