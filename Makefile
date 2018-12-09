CC	= g++ -ldl -pthread -lssl -lcrypto -I${HOME}/usr/local/openssl/include -L${HOME}/usr/local/openssl/lib
#CC	= g++ -ldl -pthread -lssl -lcrypto -I/accounts/students/r/rnfmcb/usr/local/openssl/include -L/accounts/students/r/rnfmcb/usr/local/opendssl/lib
DEBUG = -g
TARGET	=	task1
OBJS	=	task1.o task2.o 

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

task1.o:	task1.cpp 
	$(CC) -c  task1.cpp

task2.o:	task2.cpp 
	$(CC) -c task2.cpp 

clean:
	rm -f *.o $(TARGET) pass1.txt pass2.txt pass3.txt

