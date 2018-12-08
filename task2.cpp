// Basic use of openssl library function SHA256
// by Mark Hauschild
#include "ssfun.h"
//#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define SIZE 100
using namespace std;

int main() {
	char orig[SIZE];
	
	cout << "Please enter string to hash:";

	cin.getline(orig,SIZE);

	// Will hold string, so should be size of our max string
	unsigned char ibuf[SIZE];

	// SHA256 hash, so only needs to be 32 bytes
	unsigned char hashbuf[32];

	// copy over string to buffer
	for (int i = 0; i < 100; i++) {
		ibuf[i] = orig[i];
	}
	
	cout << "Before hash:" << endl;
	for (int i = 0; i < strlen(orig); i++) {
		printf("%02x ", ibuf[i]);
	}
	cout << endl;
	
	SHA256(ibuf, strlen(orig), hashbuf);

	cout << "After hash:" << endl;

	for (int i = 0; i < 32; i++) {
		printf("%02x ", hashbuf[i]);
	}

	printf("\n");
	return 0;
}
