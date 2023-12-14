#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>



using namespace std;

std::unordered_map<std::string, int> colorNumCombo = {
    {"red", 12},
    {"green", 13},
    {"blue", 14}
};

int get_game_number(string line){
    string game_number = "";
    string game = line.substr(0, line.find(":"));
    for (int i = 0; i < game.length(); i++){
        if (isdigit(game[i])){
            game_number += game[i];
        }
    }
    cout << game_number << '\n';
    return stoi(game_number);
}



int partA(){
    fstream newfile;
    int sum = 0;

    newfile.open("/home/tsg/Documents/CalenderTasks/Task2/input", ios::in);
    if (newfile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(newfile, tp)){
            int game_number = get_game_number(tp);
            bool valid = true;
            string game = tp.substr(tp.find(":")+1, tp.length());
            // cout << game << '\n';
            
            std::istringstream iss(game);
            std::string segment;
            while (std::getline(iss, segment, ';')) {
                cout << segment << '\n';
                std::istringstream segmentStream(segment);
                std::string color;
                int count;
                while (segmentStream >> count >> color) {
                    
                    if (color.find(',') != std::string::npos){
                        color.erase(color.size() - 1);
                    }
                    cout << count << " " << color << '\n';
                    if (count > colorNumCombo[color]) {
                        cout << "To big of a number" <<  count << "vs " << colorNumCombo[color] << '\n';
                        valid = false;
                    }
                }
            }   
            if (valid == true){
                sum+=game_number;
            }
        }
    }
    newfile.close(); 
    return sum;
}

int partB(){
    fstream newfile;
    int sum = 0;

    newfile.open("/home/tsg/Documents/CalenderTasks/Task2/input", ios::in);
    if (newfile.is_open()){ //checking whether the file is open
        string tp;
        while(getline(newfile, tp)){
            std::unordered_map<std::string, int> colorNumCombo = {{"red", 0},{"green", 0},{"blue", 0}};
            string game = tp.substr(tp.find(":")+1, tp.length());
            // cout << game << '\n';
            
            std::istringstream iss(game);
            std::string segment;
            while (std::getline(iss, segment, ';')) {
                cout << segment << '\n';
                std::istringstream segmentStream(segment);
                std::string color;
                int count;
                while (segmentStream >> count >> color) {
                    if (color.find(',') != std::string::npos){
                        color.erase(color.size() - 1);
                    }

                    cout << count << " " << color << '\n';
                    if (count > colorNumCombo[color]) {
                        cout << "Smaller number" <<  count << "vs " << colorNumCombo[color] << '\n';
                        colorNumCombo[color] = count;
                    }
                }
            }  
            sum = sum + colorNumCombo["red"]*colorNumCombo["green"]*colorNumCombo["blue"];   
        }
    }
    newfile.close(); 
    return sum;
}


int main(void){
    int result = partB();
    cout << result << '\n';
    return 0;
}