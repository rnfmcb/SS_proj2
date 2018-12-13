//Software security project 
//Rachel Festervand and Grayson Hart 
//Task 2 


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
        char salt[8];
}users[100];

void gen_username(char *s, const int len){
        static const char alphanum[] =
                "0123456789"
                "abcdefghijklmnopqrstuvwxyz";
        for(int i = 0; i < len; ++i){
                s[i] = alphanum[rand()%(sizeof(alphanum)-1)];
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

        for(int j = 0; j < 100; j++){
                unsigned char ibuf[SIZE];
                char salt[8];
                user_t user = users[j];
                int passnum = (rand()%6)+3; //Password limit 3 - 8 characters
                int namenum = (rand()%6)+3; //name num

                gen_username(user.username, namenum);
                gen_random(user.plaintextPass, passnum);

                SHA256(ibuf,strlen(user.plaintextPass),user.hashedPass); //This hashes the password with NO salt

                writeToPass1(user);
                writeToPass2(user);

                gen_random(salt, 8);    //This calls the above function dont ask how it works I got it off stack overflow
                                        //salt is now 8 random characters that I print out later
                strcpy(user.salt, salt);
                int passSize = strlen(user.plaintextPass); //this is unnecessary
                int combinedSize = strlen(user.plaintextPass) + strlen(user.salt); //this combines the size of the salt and user password length for the next function
        //      printf("%d\n", combinedSize);
                for(int i = strlen(user.plaintextPass); i < combinedSize; i++){ //this adds the salt to the end of the users password length. Note the ++i
                        user.plaintextPass[i] = user.salt[i - passSize];
                }

                for(int i = 0; i < strlen(user.plaintextPass); i++){ //this assigns ibuf to the new password which is plaintext + salt
                        ibuf[i] = user.plaintextPass[i];
                }

                SHA256(ibuf,strlen(user.plaintextPass),user.hashedPass); //calling hash function again on salted string
                writeToPass3(user);     //writes the third file
                                        //so I also realised that salt is actually stored with your account, and when you log in it adds it to the end of your pass then hashes it to verify
                                        //I dont think we need to store the salt since we have all three files to work with
                                        //also, theres a bunch of openssl salting stuff but I wasnt too familiar and frankly didnt care becaause this popped in my head first. .
         }

        return 0;
}

void writeToPass1(user_t user){
        ofstream myfile;
        myfile.open("pass1.txt",std::ios_base::app);
        myfile.write(user.username, strlen(user.username));
        //myfile << user.username;
        myfile << " ";
        myfile.write(user.plaintextPass, strlen(user.plaintextPass));
        myfile << "\n";
        //myfile.close();
        //myfile.clear();
}

void writeToPass2(user_t user){
        //cout << user.plaintextPass << endl;
        char hexBuffer[128];
        hexBuffer[127] = 0;
        ofstream myfile;
        myfile.open("pass2.txt", std::ios_base::app);
        myfile.write(user.username, strlen(user.username));
        myfile << " ";
        for(int i = 0; i < 32; i++){
                sprintf(&hexBuffer[2*i], "%02x ", user.hashedPass[i]);
        }
        myfile.write(hexBuffer, strlen(hexBuffer));
        myfile << "\n";
}

void writeToPass3(user_t user){
        //cout << user.plaintextPass << endl;
        char hexBuffer[128];
        hexBuffer[127] = 0;
        ofstream myfile;
        myfile.open("pass3.txt", std::ios_base::app);
        myfile.write(user.username, strlen(user.username));
        myfile << "-";
        myfile.write(user.salt, 8);
        myfile << " ";
        for(int i = 0; i < 32; i++){
                sprintf(&hexBuffer[2*i], "%02x ", user.hashedPass[i]);
        }
        myfile.write(hexBuffer, strlen(hexBuffer));
        myfile << "~";
        myfile.write(user.plaintextPass, strlen(user.plaintextPass));
        myfile << "\n";
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
