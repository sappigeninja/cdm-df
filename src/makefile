CFLAGS = -std=c11 -O0 -c -Wall -Wextra -ggdb # Debug flags
#CFLAGS = -std=c11 -O2 -c -Wall -Wextra # -ggdb # do i need -ggdb?
LIBS   = -lncurses -lmenu -ltinfo -lconfig

OBJECTS = main.o config.o fire.o matrix.o grid.o menu.o utils.o
#VPATH = src

cdm-df:$(OBJECTS)
	gcc -O2 -o $@ $^ $(LIBS)

main.o: main.c config.o fire.o matrix.o menu.o
	gcc $(CFLAGS) $<

config.o: config.c config.h utils.o
	gcc $(CFLAGS) $<

fire.o: fire.c fire.h grid.o 
	gcc $(CFLAGS) $<

matrix.o: matrix.c matrix.h grid.o utils.o
	gcc $(CFLAGS) $<

grid.o: grid.c grid.h utils.o
	gcc $(CFLAGS) $<

menu.o: menu.c menu.h utils.o
	gcc $(CFLAGS) $<

utils.o: utils.c utils.h
	gcc $(CFLAGS) $<

# Miscellaneous:
install: cdm-df
	sudo mkdir -p /usr/local/bin
	sudo mv cdm-df /usr/local/bin
	sudo mkdir -p /etc/cdm-df
	sudo cp ../configs/config /etc/cdm-df/

# Phony targets:
uninstall: # uninstall cdm-df
	rm /usr/local/bin/cdm-df

clean: # Remove all the object files
	rm cdm-df $(wildcard *.o)

todo: # List all TODO:
	grep -n "TODO:" *.[ch]

tree: # List the dependency tree
	gcc -MM $(LIBS) *.[ch]

tags: # update the tags file
	etags *.[ch]

# Set phony targets
.PHONY: uninstall clean todo tree tags
