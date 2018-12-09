// Software Security Project  
// Rachel Festervand and Grayson Hart 
//#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <iostream> 
#include <fstream>
#define SIZE 100
using namespace std;
struct user_t {
	char username[100];
	char plaintextPass[100];
	char hashedPass[100];
}user;

void writeToPass1(user_t user); 

int main() {


         //Ask user to login or create account 
         int login; 
         cout << "Type 0 to login and 1 to create a new account:" << endl; 
         cin >> login;  
           if(login == 0){ //login 
              //Get user  name  
	      char username[SIZE];	
	      cout << "Please enter user name\n";
              cin.ignore(100,'\n');
		cin.getline(user.username,SIZE);
      
               // Will hold string for user  
              unsigned char usernamebuf[SIZE];
                 for(int i = 0; i < 100; i++){
                   //user.username[i] = username[i]; 
                 }
                 ////writeToPass1(user); 
              //cin.get();   
              //Get password 
              char password[SIZE];  
              cout << "Please enter password\n";
              cin.getline(password,SIZE); 
              //cin.get();  
              unsigned char passwordbuf[SIZE]; 
                 for(int i = 0; i < 100; i++) { 
                    user.plaintextPass[i]  = password[i]; 
                 } 
                writeToPass1(user);  
            
             } 
             if (login == 1) { 
                //Ask for user nbame 
                char newName[SIZE]; 
                cout << "Enter a user name\n"; 
                cin.getline(newName, SIZE);
                cin.get();  
                //Holds string for new user
                unsigned char newNamebuf[SIZE]; 
                  for(int i = 0; i < 100; i++){
                    user.username[i] = newName[i]; 
                  } 
                writeToPass1(user); 
                //Get a password
                char newPassword[SIZE]; 
                cout << "Enter a password\n"; 
                cin.getline(newPassword,SIZE);
                cin.get();  
                //Holds string for new password
                unsigned char newPasswordbuf[SIZE]; 
                   for(int i = 0; i < 100; i++){ 
                      user.plaintextPass[i] = newPassword[i]; 
                   } 
              writeToPass1(user); 
              
             }                   

	// SHA256 hash, so only needs to be 32 bytes
	//
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

void writeToPass1(user_t user){
	ofstream myfile;
	myfile.open("pass1.txt");
	myfile << user.username; 
	myfile << " ";
	myfile << user.plaintextPass << endl;
	myfile.close();
}
	
void writeToPass2(){
	//myfile.open("pass2.txt");
	//
        //myfile << user.username + " " + user.hashedPass + "\n";
}

void writeToPass3(){
	//myfile.open("pass3.txt");
        //myfile << user.username + " " + user.hashedPass + "\n";
}
