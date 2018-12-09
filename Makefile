CC	= g++ -ldl -pthread -lssl -lcrypto -I${HOME}/usr/local/openssl/include -L${HOME}/usr/local/openssl/lib
#CC	= g++ -ldl -pthread -lssl -lcrypto -I/accounts/students/r/rnfmcb/usr/local/openssl/include -L/accounts/students/r/rnfmcb/usr/local/opendssl/lib
DEBUG = -g
TARGET	=	task2
OBJS	=	task2.o 

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

task2.o:	task2.cpp 
	$(CC) -c task2.cpp 

clean:
	rm -f *.o $(TARGET) pass1.txt pass2.txt pass3.txt

