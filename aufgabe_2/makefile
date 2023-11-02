CC=gcc
CFLAGS += -W -Wall -Wextra -Werror			#Pflicht
CFLAGS += -pedantic   						#Optional
CFLAGS += -ggdb3 -DDEBUG -fsanitize=address	#Sinnvoll für Debuging

a2_1: a2_1.c 

a2_2: a2_2.c 

a2_3: a2_3.o
	$(CC) a2_3.c $(CFLAGS) -I/usr/lib/x86_64-linux-gnu -lreadline -o a2_3 

clean:
	$(RM) a2_1
	$(RM) a2_2
	$(RM) a2_3


	