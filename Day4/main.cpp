/*
Improvments:
- Use descriptive variable names: tp, num and iss are not good. 
- Use const correctly: Consider setting vectors winning and elf to const as they are not changed. 
- Avoid Global Using Directicves: std
- Add error handling where possible. 
- Breakt the code into smaller functions. 
- Use algorithms for fast searching. 
- Using range based loop as for (const int& elfNumber : elfNumbers) is better than for (int j = 0; j < elf_num.size(); j++)
        - Readability: More concise and easier to read. 
        - Avoiding potential off-by-one errors. 
        - No need for index access. 
        - Immutable elements using const int&.
        - But the performance is negligable. 
*/

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> // To use find function



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

// vector<int> create_vec(string numbers){
//     vector<int> numbers_vec;
//     string num;
//     istringstream iss_numbers(numbers);
//     while (iss_numbers >> num){
//         numbers_vec.push_back(stoi(num));
//     }
//     return numbers_vec;
// }

int get_card_number(string card){
    string game_number = "";
    for (int i = 0; i < card.length(); i++){
        if (isdigit(card[i])){
            game_number += card[i];
        }
    }
    cout << game_number << '\n';
    return stoi(game_number);
}

void update_card_map(unordered_map<int, int> &card_count, int matches, int card_number){
    for (int i = 1; i <= matches; i++){
        if (card_count[card_number+i] == 0){
            card_count[card_number+i] = 1;
        }
            card_count[card_number+i] = card_count[card_number+i] + 1;
            cout << "Updated map, " << card_number + i << " : " << card_count[card_number+i] << '\n';       
    }
}

int partB(){
    fstream input_file;
    unordered_map<int, int> card_count = {{1,1}};

    input_file.open("/home/tsg/Documents/CalenderTasks/AdventOfCode/Day4/input", ios::in);
    if (input_file.is_open()){ //checking whether the file is open
        string tp;
        while(getline(input_file, tp)){
            
            int pints_card_it = 1;

            string card_game = tp.substr(0, tp.find(":"));
            cout << "Card number: " << card_game << '\n';
            int card_game_num = get_card_number(card_game);
            if (card_count[card_game_num] == 0){
                card_count[card_game_num] = 1;
             }

            string card_numbers = tp.substr(tp.find(":")+1, tp.length());
            string winning_numbers_str = card_numbers.substr(0, card_numbers.find("|"));
            string elfs_numbers_str = card_numbers.substr(card_numbers.find("|")+1, tp.length());

            // cout << "Creating vectors." << '\n';
            const vector<int> winning_numbers = create_vec(winning_numbers_str);
            const vector<int> elfs_numbers = create_vec(elfs_numbers_str);
            cout << "Iterating card " << card_game_num << ": "<< card_count[card_game_num] << "times "  << '\n';
            for (int i = 0; i < card_count[card_game_num]; i++ ){
                int matches = 0;
                for (const int& elf_number : elfs_numbers){
                    // cout << "Comparing number: "<< elf_number << " "  << '\n';
                    if (find(winning_numbers.begin(), winning_numbers.end(), elf_number) != winning_numbers.end()){
                        // cout << "MATCH!" << '\n';
                        matches ++;
                    }    
                }
                // Add the matches to the map. 
                update_card_map(card_count, matches, card_game_num);
                // cout << "Is it correct:" << card_count[2] << '\n';

            }
        }
    }
    // Sum over the map. 
    int total_scratchcards = 0;
    for (const auto& [card, count] : card_count) {
        total_scratchcards += count;
    }
    return total_scratchcards;
}


int main(){
    int sum = partB();
    cout << "Total scratchcards: "<<  sum << '\n';
    return 0;
}