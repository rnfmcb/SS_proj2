// Software Security Project  
// Rachel Festervand and Grayson Hart 
#include <iomanip>
#include<cmath>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h> 
#include <fstream>
#define SIZE 100
using namespace std;
struct user_t {
	char username[100];
	char plaintextPass[100];
	unsigned char hashedPass[32];
}user;

void gen_username(char *s, const int len){
	static const alplhanum[] = 
		"0123456789"
		"abcdefghijklmnopqrstuvwxyz";
	for(int i = 0; i < len; ++i){
		s[i] = alphanum[rand()%(sizeof(alphanum)-1]
	}
	s[len] = 0;
}

void gen_random(char *s, const int len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
}

void writeToPass1(user_t user); 
void writeToPass2(user_t user);
void writeToPass3(user_t user);
int main() {
	//THIS IS A TEST CAN I PUSH WAHT;
        //Ask user to login or create account 
	srand(time(NULL));
	char salt[20];
	unsigned char ibuf[SIZE];
	
	int login; 
	cout << "Type 1 to login and 0 to create a new account:" << endl; 
	cin >> login;  
	if(login == 0){ //login 
		cout << "Please enter user name\n";
		cin.ignore(100,'\n');
		cin.getline(user.username,SIZE);
    
		cout << "Please enter password\n";	//You may be wondering how this works
		cin.getline(user.plaintextPass,SIZE);   

		cout << endl;		
		
		SHA256(ibuf,strlen(user.plaintextPass),user.hashedPass); //This hashes the password with NO salt
		
		writeToPass1(user);  
		writeToPass2(user);			
			
		gen_random(salt, 20); 	//This calls the above function dont ask how it works I got it off stack overflow
					//salt is now 20 random characters that I print out later
		int passSize = strlen(user.plaintextPass); //this is unnecessary
		int combinedSize = passSize + strlen(salt); //this combines the size of the salt and user password length for the next function
		for(int i = strlen(user.plaintextPass); i < combinedSize; ++i){ //this adds the salt to the end of the users password length. Note the ++i
			user.plaintextPass[i] = salt[i - passSize];
		}
		for(int i = 0; i < strlen(user.plaintextPass); i++){ //this prints out the plaint text password
			cout << user.plaintextPass[i];
		}
		cout <<endl;
		for(int i = 0; i < strlen(salt); i++){ //this prints out the salt
			cout << salt[i];
		}
		for(int i = 0; i < strlen(user.plaintextPass); i++){ //this assigns ibuf to the new password which is plaintext + salt
			ibuf[i] = user.plaintextPass[i];
		}
		SHA256(ibuf,strlen(user.plaintextPass),user.hashedPass); //calling hash function again on salted string
		cout << endl;	
		writeToPass3(user); 	//writes the third file
					//so I also realised that salt is actually stored with your account, and when you log in it adds it to the end of your pass then hashes it to verify
					//I dont think we need to store the salt since we have all three files to work with
					//also, theres a bunch of openssl salting stuff but I wasnt too familiar and frankly didnt care becaause this popped in my head first. . 
		
	} else if (login == 1) { 
             //Ask for user name 
		char newName[SIZE]; 
		cout << "Enter a user name\n"; 
		cin.getline(newName, SIZE);
		cin.get();  
                //Checks if username is valid 
                int isUser = 0; 
    		for(int i = 0; i < SIZE; i++){ 
 		  if(newName[i] != user.username[i])
                    isUser = 1; 
       	        }
		//writeToPass1(user); 
       	         //Get a password
		char newPassword[SIZE]; 
		cout << "Enter a password\n"; 
		cin.getline(newPassword,SIZE);
		cin.get();  
                //Checks if password is valid 
                int isPassword; 
		  for(int i = 0; i < SIZE; i++){ 
		     if(newName[i] != user.username[i]) 
                       isPassword = 1; 
		}
               //Prints an error if password or username is invalid 
               if(isPassword == 1 || isUser == 1)
 	           cout << "Username or Password is invalid" << endl;
               else 
 	           cout << "Successful Login" << endl;   
	       //writeToPass1(user); 
        } 	
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
	
void writeToPass2(user_t user){
	char hexBuffer[128];
	hexBuffer[127] = 0;
	ofstream myfile;
	myfile.open("pass2.txt");
	myfile << user.username;
	myfile << " ";
	for(int i = 0; i < 32; i++){
		sprintf(&hexBuffer[2*i], "%02x ", user.hashedPass[i]);
	}
	myfile << hexBuffer;
	myfile << "" << endl;
	myfile.close();
}

void writeToPass3(user_t user){
	char hexBuffer[128];
        hexBuffer[127] = 0;
        ofstream myfile;
        myfile.open("pass3.txt");
        myfile << user.username;
        myfile << " ";
        for(int i = 0; i < 32; i++){
                sprintf(&hexBuffer[2*i], "%02x ", user.hashedPass[i]);
        }
        myfile << hexBuffer;
        myfile << "" << endl;
        myfile.close();
}

//Validates passwords and usernames. Returns true if valid 
bool readPassword(user_t user, string search){
	size_t pos; 
	ifstream inFile;
	string line;
	inFile.open("pass1.txt");
        if(!inFile){
          cout << "Unable to open file" << endl;
          exit(1);
         }
         //search for word 
         if(inFile.is_open()) { 
	   while(getline(inFile,line)){ 
	     pos = line.find(search); 
                if(pos!=string::npos)//string not found  
 		    return false; 
                else 
                   return true; 
            }
         } 
}
