all: main.o dump_trace.o
	g++ -g main.o dump_trace.o -o main

dump_trace.o:dump_trace.cpp
	g++ -c -g $< -o $@

%.o:%.cpp
	g++ -c -g -finstrument-functions $< -o $@

clean:
	rm -rf *.o main
