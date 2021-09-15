SOURCE1		= signalwaiting1 bloom_filter
SOURCE2		= signalwaiting2 bloom_filter
CFLAGS		= -c
CC		= gcc
OUT1		= travelMonitor
OUT2		= mysig
LIBS		=
INCS		=

all: $(OUT1) $(OUT2)

$(OUT1): $(SOURCE1).c types.h
	gcc -o $(OUT1) $(SOURCE1).c -lpthread

$(OUT2): $(SOURCE2).c types.h
	gcc -o $(OUT2) $(SOURCE2).c -lpthread

clean:
	rm -f $(SOURCE1).o $(OUT1) $(SOURCE2) $(OUT2) a.out;
	touch $(SOURCE1).c $(SOURCE2).c
