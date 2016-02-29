OBJS=main.o strs.o minmax.o dbg.o XMLIOBuf.o XMLIO.o
#-Wallをつけるとlexのリンク時にyywrapのエラーが出る。
CFLAGS=-Wall -g
#LDLIBS=-lmcheck
LDLIBS=-lefence
#LDLIBS=
TARGET=ReplaceStrings2
CC=g++

.SUFIXES: .cpp .o

.PHONY: all
all: $(TARGET)


$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDLIBS)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
