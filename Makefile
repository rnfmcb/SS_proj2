CC	= g++ -ldl -pthread -lssl -lcrypto -I${HOME}/usr/local/openssl/include/openssl -L${HOME}/usr/local/openssl/lib
#CC	= g++ -ldl -pthread -lssl -lcrypto -I/accounts/students/r/rnfmcb/usr/local/openssl/include -L/accounts/students/r/rnfmcb/usr/local/opendssl/lib
DEBUG = -g
TARGET	=	ssfun
OBJS	=	ssfun.o

$(TARGET):	$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

ssfun.o:	ssfun.cpp ssfun.h
	$(CC) -c ssfun.cpp

clean:
	rm -f *.o $(TARGET)
