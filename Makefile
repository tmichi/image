all:
	make -C java
	make -C cpp
	make -C doc
clean:
	make clean -C java
	make clean -C cpp
	make clean -C doc
	rm *~