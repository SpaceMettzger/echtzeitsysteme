CC=gcc
CFLAGS += -W -Wall -Wextra -Werror			#Pflicht
CFLAGS += -pedantic   						#Optional
CFLAGS += -ggdb3 -DDEBUG -fsanitize=address	#Sinnvoll für Debuging

all: a5_1

a5_1: a5_1.c 
	$(CC) a5_1.c $(CFLAGS) -o a5_1  

clean:
	$(RM) a5_1
