all: crack overflow

crack: crack.cpp
	gcc crack.cpp -o crack -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

overflow: overflow.cpp
	gcc overflow.cpp -o overflow

clean:
	rm -rf *.o
	ls | grep -v "\.\|Makefile" | xargs rm
