CC	= g++
CFLAGS	= -O3 -Wall
TARGET 	= sample 
.SUFFIXES: .cpp .o
all:	$(TARGET)
## programs
sample:	main.o
	$(CC) $(CFLAGS) -o $@ $^  
.cpp.o:
	$(CC) $(CFLAGS) -c $< 
clean:
	rm -f *.o *~ $(TARGET)
	rm -f negate.bmp 
check: sample
	./sample -i sample.bmp -o negate.bmp

