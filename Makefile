all:
	g++ -O3 -Wall -Wextra -Wpedantic -c -fopenmp -fPIC src/*.cpp -I./include
	g++ -O3 -fopenmp -shared *.o -o libml.so
	rm *.o
	mv libml.so lib

# call as make main=your_file_name.cpp target
target:
	g++ -O3 -Wall -Wextra -Wpedantic -I./include $(main) -L./lib -lml -fopenmp -Wl,-rpath=$$PWD/lib

install:
	cp lib/libml.so /usr/local/lib