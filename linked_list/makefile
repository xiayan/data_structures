CXX = g++
CFLAGS = -c -Wall
LDFLAGS =
SRCS = main.cpp List.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = lab3

all: $(SRCS) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJS) 
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

# Default suffix rule.  Can be ommitted
.cpp.o:
	$(CXX) $(CFLAGS) $<

clean:
	rm $(OBJS)

clean-all:
	rm $(OBJS) $(EXECUTABLE)
