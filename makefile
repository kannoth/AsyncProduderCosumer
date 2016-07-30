CC=gcc
ROOT= src
CFLAGS=-c -Wall
LDFLAGS=-pthread
SOURCES=$(ROOT)/main.c $(ROOT)/fpgaSM.c $(ROOT)/hpsSM.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=fpga2hps

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(ROOT)/*o fpga2hps
