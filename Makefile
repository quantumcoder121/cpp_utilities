Lib:
	g++ -O3 -Wall -Wextra -Wpedantic -c -fopenmp -fPIC src/*.cpp -I./include
	g++ -O3 -fopenmp -shared cppdl.o  math.o  mllib.o -o libml.so
	rm cppdl.o  math.o  mllib.o
	mv libml.so lib

# call as make main=your_file_name.cpp target
target:
	g++ -O3 -Wall -Wextra -Wpedantic -I./include $(main) -L./lib -lml -fopenmp -Wl,-rpath=$$PWD/lib

install:
	cp lib/* /usr/local/lib
	cp include/* /usr/local/include