CC	= g++ -ldl -pthread -lssl -lcrypto -I${HOME}/usr/local/openssl/include -L${HOME}/usr/local/openssl/lib
#CC	= g++ -ldl -pthread -lssl -lcrypto -I/accounts/students/r/rnfmcb/usr/local/openssl/include -L/accounts/students/r/rnfmcb/usr/local/opendssl/lib
DEBUG = -g
all: task1 task2
OBJS = task1.o task2.o 

task1: task1.cpp
	$(CC)  -o task1 task1.cpp

task2: task2.cpp
	$(CC)  -o task2 task2.cpp 

task1.o:  task1.cpp
	$(CC) -c task1.cpp
 
task2.o:  task2.cpp
	 $(CC) -c task2.cp

clean:
	rm -f *.o task2 task1 pass1.txt pass2.txt pass3.txt

