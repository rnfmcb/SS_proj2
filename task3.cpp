//Software Security
//Grayson Hart and Rachel Festervand
//Task 3 

#include <iomanip>
#include <cmath>
#include <openssl/sha.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <unistd.h>
#define SIZE 100
using namespace std;
//vector<string> generated;
char hexBuffer[128];
/*
char hexBuffer[128];
        hexBuffer[127] = 0;
        ofstream myfile;
        myfile.open("pass2.txt", std::ios_base::app);
        myfile.write(user.username, strlen(user.username));
        myfile << " ";
        for(int i = 0; i < 32; i++){
                sprintf(&hexBuffer[2*i], "%02x ", user.hashedPass[i]);
        }
*/
string salt[100];
string lines[100];
string decision;
int type;
int passCompare(string generatedUnhashedString){
	
	hexBuffer[127] = 0;
	char generatedUnhashedcString[strlen(generatedUnhashedString.c_str())+8*type];
	
	unsigned char unsignedGeneratedUnhashedcString[strlen(generatedUnhashedString.c_str())+8*type];
        unsigned char unsignedGeneratedHashedcString[64];
	char generatedHashedcString[64];
	strcpy(generatedUnhashedcString, generatedUnhashedString.c_str()); //generated pass is now a c string
	//cout << generatedUnhashedcString << endl;
	if(type == 0){
		for(int i = 0; i < strlen(generatedUnhashedcString); i++){
			unsignedGeneratedUnhashedcString[i] = generatedUnhashedcString[i]; //making a buffer of unhashed input
		}
	
		SHA256(unsignedGeneratedUnhashedcString,strlen(generatedUnhashedcString),unsignedGeneratedHashedcString);
		for(int i = 0; i < 32; i++){
			sprintf(&hexBuffer[2*i], "%02x", unsignedGeneratedHashedcString[i]);	
		}
	}
	int length = strlen(generatedUnhashedcString);
	for(int i = 0; i < 100; i++){
	//	if(generatedUnhashedString == "z28"){
	//		cout << "Here i guess\n";	
	//	}
		if(type == 1){
                	for(int j = length; j < length+8; j++){
                        	generatedUnhashedcString[j] = salt[i].c_str()[j-length];
                	}
                	//cout << generatedUnhashedcString;
			for(int k = 0; k < strlen(generatedUnhashedcString); k++){
                        	unsignedGeneratedUnhashedcString[k] = generatedUnhashedcString[k]; //making a buffer of unhashed input
                	}
                	SHA256(unsignedGeneratedUnhashedcString,strlen(generatedUnhashedcString),unsignedGeneratedHashedcString);
                	for(int l = 0; l < 32; l++){
                        	sprintf(&hexBuffer[2*l], "%02x", unsignedGeneratedHashedcString[l]);
                	}
        	}
		if(strcmp(hexBuffer, lines[i].c_str()) == 0){
                	printf("Match found:\n");
			printf("Line # %d\n", i+1);
			cout << generatedUnhashedString << endl;
			cout << hexBuffer << endl;
			cout << lines[i] << endl;
			return 1;
                }

	}
	return 0;
}

int gen_random(string s, const int len) {
    static const char alphanum[] =
	"abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"0123456789";
        //"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        //"abcdefghijklmnopqrstuvwxyz";
	if(len == 0){
		//cout << s << "\n";
//		cout << "Sending: "; 
//		cout << s << endl;
		if(passCompare(s) == 1){
			return 1;
		}
		//generated.push_back(s);
		return 0;
	}
   	for (int i = 0; i < 62; ++i) {
       		string appended = s + alphanum[i];
		if(gen_random(appended, len - 1) == 1){
			return 1;
		}
    	}
	return 0;
}

int main() {
	static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
	srand(time(NULL));
	string inputLine;
	string line;
	string s, pass2 = "pass2.txt", pass3 = "pass3.txt";
	char filename[10];
	char cline[32];
	//int type;
	cout << "Crack salt? y/n" << endl;
	cin >> decision;
	if(decision == "y"){
		
		type = 1;
		strcpy(filename, pass3.c_str());
	}else if (decision == "n"){
		
		type = 0;
		strcpy(filename, pass2.c_str());
	} else {
		return 0;
	}
	ifstream myfile (filename);
	if(myfile.is_open()){
		int i = 0;
		while(getline(myfile,line)){
			if(type == 1){
				salt[i] = line.substr(line.find("-")+1, 8);
			}	
			line = line.substr(line.find(" ")+1, 64);
                	lines[i] = line;
			i++;
		}
		/*for(i = 0; i < 100; i++){
			cout << salt[i] << endl;
			cout << lines[i] << endl;
		}*/
		for(i = 3; i < 8; i++){
			printf("i loop is %d \n", i);
			if(gen_random(s, i) == 1){
				break;
			}
			//for(int j = 0; j < generated.size(); j++){
				//printf("%d %d\n",i, j);
				//if(passCompare(generated[j]) == 1){
				//	break;
				//}
			//}
			//generated.clear();		
		}
	}
 	/*static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
 
        srand(time(NULL));
        char salt[20];
	int passnum = 3;
        unsigned char ibuf[SIZE];
	unsigned char genHashedPass[32];

	int cracked = 0;
	string line, generatedPass;
	char cline[32], cgeneratedPass[8];
	ifstream myfile ("pass2.txt");
	if(myfile.is_open()){
		while(cracked == 0){
			gen_random(generatedPass, passnum);
			strcpy(cgeneratedPass, generatedPass.c_str());
                        for(int i = 0; i < strlen(cgeneratedPass); i++){
                        	ibuf[i] = cgeneratedPass[i];
                        }
                        SHA256(ibuf,strlen(cgeneratedPass),genHashedPass);
			
			while(getline(myfile,line)){
				strcpy(cline, line.c_str());
				if(strcmp(cline, line.c_str()) == 0){
					cracked = 1;
				} 
			}
			passnum++;	
		}
	} */
       return 0;
}

