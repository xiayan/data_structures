CXX = g++
CFLAGS = -c -Wall
LDFLAGS =
SRCS = main.cpp TwoThreeTree.cpp TQueue.cpp AsciiTree.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = lab8

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

