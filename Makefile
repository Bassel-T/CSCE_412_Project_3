Proj3.out: MitriToubbeh_Project3.o LoadBalancer.o Request.o WebServer.o
	g++ -Wall MitriToubbeh_Project3.o LoadBalancer.o Request.o WebServer.o -o Proj3.out

MitriToubbeh_Project3.o: MitriToubbeh_Project3.cpp LoadBalancer.h
	g++ -Wall -c MitriToubbeh_Project3.cpp -o MitriToubbeh_Project3.o

LoadBalancer.o: LoadBalancer.cpp LoadBalancer.h Request.h WebServer.h
	g++ -Wall -c LoadBalancer.cpp LoadBalancer.h -o LoadBalancer.o

WebServer.o: WebServer.cpp WebServer.h Request.h
	g++ -Wall -c WebServer.cpp WebServer.h -o WebServer.o

Request.o: Request.cpp Request.h
	g++ -Wall -c Request.cpp Request.h -o Request.o

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~ *.h.gch *#

run:
	./Proj3.out

all:
	make clean
	make
	make run