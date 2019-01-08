all: main.o dump_trace.o
	g++ -g main.o dump_trace.o -o main

%.o:%.cpp
	g++ -c -g -finstrument-functions $< -o $@

clean:
	rm -rf *.o main
