CC = g++ 
CFLAGS = -lpthread 
CPPFLAGS = -I 
FOLDER = -I include 

SOURSES = src/function.cpp src/server.cpp

EXECUTABLE = server


.PHONY : all, debug, release, clean

all:$(EXECUTABLE)

debug: CFLAGS += -g
debug: $(EXECUTABLE)

release: CFLAGS += -DNDEBUG -O3
release: $(EXECUTABLE)

$(EXECUTABLE): $(SOURSES)
	$(CC)  $(SOURSES)  $(FOLDER) $(CFLAGS) -o server
	
clean:
	rm *.out