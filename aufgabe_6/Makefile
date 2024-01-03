CC=gcc
CFLAGS += -W -Wall -Wextra -Werror			#Pflicht
CFLAGS += -pedantic   						#Optional
CFLAGS += -ggdb3 -DDEBUG -fsanitize=address	#Sinnvoll für Debuging

all: a6_1 a6_2 a6_3 a6_4

a6_1: 
	$(CC) a6_1.c $(CFLAGS) -o a6_1

a6_2: a6_2.c
	$(CC) $^ $(CFLAGS) -o $@

a6_3: a6_3.c
	$(CC) $^ $(CFLAGS) -o $@

a6_4: a6_4.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	$(RM) a6_1 a6_2 a6_3