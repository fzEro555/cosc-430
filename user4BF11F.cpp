#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <string>
#include <fstream>
#include <ctime>
#include <stdlib.h>

using namespace std;

#include <openssl/sha.h>

string sha(const string str)
{
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA_CTX sha;
    SHA_Init(&sha);
    SHA_Update(&sha, str.c_str(), str.size());
    SHA_Final(hash, &sha);
    stringstream ss;
    for(int i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

//This function is used to check the username and password.
bool check_login(string username, string password){
    bool flag = false;
    string str;
    ifstream file("user4BF11F.cfg");
    //file.open("user4BF11F.cfg");
    if(file){
        char* str1 = NULL;
        char* str2 = NULL;
        char* delimiter = ":";
        while(getline(file, str)){
            char* p = (char*)str.c_str();
            str1 = strtok_r(p, delimiter, &str2);
            if(str1 == username && str2 == password){
                flag = true;
            }
        }
        file.close();
    }
    return flag;
}

//This function is used to print the content of the txt file
void file_content(){
    char buffer[1024];
    string str;
    ifstream file;
    file.open("user4BF11F.txt");
    if(file.is_open()){
        while(file.good() && !file.eof()){
            memset(buffer,0,1024);
            file.getline(buffer,1024);
            str = buffer;
            cout << str <<endl;
        }
        file.close();
    }
}

//This function is used to log the time and user who execute the program.
void log_content(string str){
    ofstream file("user4BF11F.log", ios::app);
    if(file.is_open())
    {
        file<<endl;
        time_t t;
        t=time(NULL);
        file<<"User " + str + "try to login on " + ctime(&t) <<endl;
        file.close();
    }
}

int main() {
    // Get the username and password from the input.
    // If the username or password is wrong, warning.
    char *username = malloc(26);
    char *password = malloc(26);
    cout << "Please enter your username:";
    fgets(username, 26, stdin);
    if(username[strlen(username)-1] == '\n')
        username[strlen(username)-1] = '\0';
    cout << "Please enter your password:";
    fgets(password, 26, stdin);
    if(password[strlen(username)-1] == '\n')
        password[strlen(username)-1] = '\0';
    string pass_encrypt = sha(password);
    bool flag = check_login(username, pass_encrypt);
    memset(username,0,26);
    memset(password,0,26);
    free(username);
    free(password);
    if(flag){
        file_content();
        log_content(username);
    }
    else{
        cout << "Invalid username or password" <<endl;
    }
    return 0;
}