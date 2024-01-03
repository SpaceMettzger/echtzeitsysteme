CC=gcc
CFLAGS += -W -Wall -Wextra -Werror			#Pflicht
CFLAGS += -pedantic   						#Optional
CFLAGS += -ggdb3 -DDEBUG -fsanitize=address	#Sinnvoll für Debuging

queuedemo: queue.c process.c

processdemo: processdemo.c process.c

processmodeldemo: processmodeldemo.c processmodel.c queue.c process.c

clean:
	$(RM) queuedemo
	$(RM) processdemo
	$(RM) processmodeldemo


	