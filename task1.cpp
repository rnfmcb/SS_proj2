// Software Security Project  
// Rachel Festervand and Grayson Hart 
//#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define SIZE 100
using namespace std;

int main() {


         //Ask user to login or create account 
         int login[2]; 
         cout << "Type 0 to login and 1 to create a new account";  
         cin.getline(login,SIZE);  
           if(login == 0){ //login 
              //Get user  name  
	      char username[SIZE];	
	      cout << "Please enter user name";
              cin.getline(username,SIZE);
	      // Will hold string for user  
              unsigned char usernamebuf[SIZE];
                 for(int i = 0; i < 100; i++){
                   usernamebuf[i] = username[i]; 
                 } 
                      

	// SHA256 hash, so only needs to be 32 bytes
	//unsigned char hashbuf[32];
	
	/*cout << "Before hash:" << endl;
	for (int i = 0; i < strlen(orig); i++) {
		printf("%02x ", ibuf[i]);
	}
	cout << endl;
	
	SHA256(ibuf, strlen(orig), hashbuf);

	cout << "After hash:" << endl;

	for (int i = 0; i < 32; i++) {
		printf("%02x ", hashbuf[i]);
	}

	printf("\n");*/
	return 0;
}
