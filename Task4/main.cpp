/*
Improvments:
- Use descriptive variable names: tp, num and iss are not good. 
- Use const correctly: Consider setting vectors winning and elf to const as they are not changed. 
- Avoid Global Using Directicves: std
- Add error handling where possible. 
- Breakt the code into smaller functions. 
- Use algorithms for fast searching. 
- 
*/

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>



using namespace std;


// cREATE A FUNCTION ADDING THEM TO A VECTOR I CAN ITERATE THROUGH. 
vector<int> create_vec(string numbers){
    vector<int> numbers_vec;
    string num;
    istringstream iss_numbers(numbers);
    while (iss_numbers >> num){
        numbers_vec.push_back(stoi(num));
    }
    return numbers_vec;
}


int partA(){
    fstream input_file;
    int sum = 0;
    input_file.open("/home/tsg/Documents/CalenderTasks/Task4/input", ios::in);
    if (input_file.is_open()){ //checking whether the file is open
        string tp;
        while(getline(input_file, tp)){
            int points_card = 0;
            int pints_card_it = 1;
            string card = tp.substr(tp.find(":")+1, tp.length());
            string winning_numbers = card.substr(0, card.find("|"));
            string elfs_numbers = card.substr(card.find("|")+1, tp.length());

            vector<int> winning_num = create_vec(winning_numbers);
            vector<int> elf_num = create_vec(elfs_numbers);
            for (int i = 0; i < winning_num.size(); i++){
                for (int j = 0; j < elf_num.size(); j++){
                    cout << "Comparing number: "<< elf_num[j] << " " << winning_num[i]  << '\n';
                     if (elf_num[j] == winning_num[i]){
                        cout << "MATCH!" << '\n';
                        if (points_card == 0){
                            points_card = 1;
                        } else {
                            points_card = points_card*2;
                        }
                        // cout << "Winning number: "<< num_elf << " " << num_winning  << '\n';
                    }
                }
            }
        cout << '\n' << "Points on this card: " << points_card << '\n';
        sum += points_card;
        }
    }

    return sum;
}

int partB(){
    fstream input_file;
    int sum = 0;
    input_file.open("/home/tsg/Documents/CalenderTasks/Task4/input", ios::in);
    if (input_file.is_open()){ //checking whether the file is open
        string tp;
        while(getline(input_file, tp)){
            int points_card = 0;
            int pints_card_it = 1;
            string card = tp.substr(tp.find(":")+1, tp.length());
            string winning_numbers = card.substr(0, card.find("|"));
            string elfs_numbers = card.substr(card.find("|")+1, tp.length());

            vector<int> winning_num = create_vec(winning_numbers);
            vector<int> elf_num = create_vec(elfs_numbers);
            for (int i = 0; i < winning_num.size(); i++){
                for (int j = 0; j < elf_num.size(); j++){
                    cout << "Comparing number: "<< elf_num[j] << " " << winning_num[i]  << '\n';
                     if (elf_num[j] == winning_num[i]){
                        cout << "MATCH!" << '\n';
                        if (points_card == 0){
                            points_card = 1;
                        } else {
                            points_card = points_card*2;
                        }
                        // cout << "Winning number: "<< num_elf << " " << num_winning  << '\n';
                    }
                }
            }
        cout << '\n' << "Points on this card: " << points_card << '\n';
        sum += points_card;
        }
    }

    return sum;

}


int main(){
    int sum = partA();
    cout << sum << '\n';
    return 0;
}