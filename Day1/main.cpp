#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;



int part1(){
    fstream newfile;
    int sum = 0;

    newfile.open("/home/tsg/Documents/CalenderTasks/Task1/input", ios::in);
    if (newfile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(newfile, tp)){ //read data from file object and put it into string.
            
            string numbers = "";
            string number = "";
            // cout << tp << "\n"; //print the data of the string
            for (int i = 0; i < tp.length(); i++){
                if (isdigit(tp[i])){
                    numbers += tp[i];
                }
            }
            if (numbers.size() > 0){
                number += numbers.front();
                number += numbers.back();
                int num = stoi(number);
                sum += num;
            }
        }
    }
    newfile.close(); //close the file object.
    // cout << "Num in in word: " << tp << ", is: " << num_integer << "alle number: " << numbers << '\n';
    // cout << "Num we want: " << numbers.front() << ", " << numbers.back() << '\n';
    return sum;
}



std::unordered_map<std::string, std::string> spelledOutMapping = {
    {"one", "on1ne"},
    {"two", "tw2wo"},
    {"three", "thre3hree"},
    {"four", "fou4our"},
    {"five", "fiv5ive"},
    {"six", "si6ix"},
    {"seven", "seve7even"},
    {"eight", "eigh8ight"},
    {"nine", "nin9ine"}
};

int part2(){
    fstream newfile;
    int sum = 0;
    newfile.open("/home/tsg/Documents/CalenderTasks/Task1/input", ios::in);
    if (newfile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(newfile, tp)){ 
            cout << tp << '\n';
            for (const auto& entry : spelledOutMapping) {
                size_t found = tp.find(entry.first);
                while (found != std::string::npos) {
                    tp.replace(found, entry.first.length(), entry.second);
                    found = tp.find(entry.first, found+1);
                }
            }
            
            string numbers = "";
            string number = "";
            cout << tp << "\n"; //print the data of the string
            for (int i = 0; i < tp.length(); i++){
                if (isdigit(tp[i])){
                    numbers += tp[i];
                }
            }
            cout << "Num in in word: " << tp << ", is: " << numbers << '\n';
                cout << "Num we want: " << numbers.front() << ", " << numbers.back() << '\n';
            if (numbers.size() > 0){
                number += numbers.front();
                number += numbers.back();
                cout << number << '\n';
                int num = stoi(number);
                cout << num << '\n';
                sum += num;
                cout << sum << '\n';
            }
            cout << '\n' << '\n'; 
        }
    }
    newfile.close(); //close the file object.
   
    return sum;
}

int main(void){
    int result = part2();
    cout << result << '\n';
    return 0;
}