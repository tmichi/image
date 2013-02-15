TARGET 	= ImageProcessingSample
.SUFFIXES: .java .o
all:	$(TARGET).class
## programs
$(TARGET).class: $(TARGET).java
	javac $(TARGET).java
clean:
	rm -f *~ $(TARGET).class
	rm -f negate.jpg
check: $(TARGET).class
	java $(TARGET) sample.bmp negate.bmp

