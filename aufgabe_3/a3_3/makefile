CC=gcc
CFLAGS += -W -Wall -Wextra -Werror			#Pflicht
CFLAGS += -pedantic   						#Optional
CFLAGS += -ggdb3 -DDEBUG -fsanitize=address	#Sinnvoll für Debuging

a3_3: 
	$(CC) childwait.c $(CFLAGS) -o a3_3  

clean:
	$(RM) a3_3

	