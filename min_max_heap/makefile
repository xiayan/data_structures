CXX = g++
CFLAGS = -c -Wall
LDFLAGS =
SRCS = main.cpp MinMaxHeap.cpp AsciiTree.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = lab9

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

test: MinMaxHeap.cpp test.cpp
	$(CXX) -DDEBUG -g -Wall MinMaxHeap.cpp test.cpp -o test.out
