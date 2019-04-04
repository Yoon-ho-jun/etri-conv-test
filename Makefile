CC = g++
CFLAGS = -Wall -std=c++11
SRCS = $(shell find . -name "*.cpp")
OBJS = ${SRCS:.cpp=.o}
PROG = ${OBJS:.o=.bin}

OPENCV_FLAGS = `pkg-config opencv --cflags`
OPENCV_LIBS = `pkg-config opencv --libs`

LIBS += $(OPENCV_LIBS)
CFLAGS += $(OPENCV_FLAGS)

binaries: $(PROG)

$(PROG): %.bin : %.o
	@$(CC) $(CFLAGS) -o $@ $< $(LIBS)

$(OBJS): %.o : %.cpp
	@$(CC) -c $(CFLAGS) $<

clean:
	@- rm -rf $(PROG)
	@- rm -rf $(OBJS)
