CC = gcc
CFLAGS = -W -Wall -Wextra -Werror		# Pflicht
CFLAGS += -pedantic   					# Optional
CFLAGS += -ggdb3 -DDEBUG -fsanitize=address	# Sinnvoll für Debuging

all: pkp

pkp: pkp.c semaphore.c

clean:
	$(RM) pkp
