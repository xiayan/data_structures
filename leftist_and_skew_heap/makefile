CXX = g++
CFLAGS = -c -Wall
LDFLAGS =
SRCS = main.cpp BinaryHeap.cpp LeftistHeap.cpp SkewHeap.cpp AsciiTree.cpp TQueue.cpp
OBJS = $(SRCS:.cpp=.o)
EXECUTABLE = lab10

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

test:
	$(CXX) $(LDFLAGS) TestHeaps.cpp BinaryHeap.cpp LeftistHeap.cpp SkewHeap.cpp AsciiTree.cpp TQueue.cpp -o test
