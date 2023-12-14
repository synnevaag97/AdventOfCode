#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>



using namespace std;


void fill_matrix(vector<vector<char>> &mat){
    fstream input_file;
    input_file.open("/home/tsg/Documents/CalenderTasks/Task3/input", ios::in);
    if (input_file.is_open()){ //checking whether the file is open
        string tp;
        
        int j = 0;
        while(getline(input_file, tp)){
            // cout << tp.length() << '\n';
            for (int i = 0; i < tp.length(); i++){
                mat[j][i] = tp[i];
            }
            j++;
        }
    }
}

string extract_number(vector<vector<char>> &mat, int j_index, int i_index){
    string number = "";
    number += mat[j_index][i_index];
    if(isdigit(mat[j_index][i_index+1])){
        number += mat[j_index][i_index+1];
    }
    if(isdigit(mat[j_index][i_index+2])){
        number += mat[j_index][i_index+2];
        // cout << "is digit: " << number << '\n';
    }
    // if(isdigit(mat[j_index][i_index+3])){
    //     number += mat[j_index][i_index+3];
    //     cout << "is digit: " << number << '\n';
    // }
    return number;
}


bool searh_for_symbol(vector<vector<char>> &mat, int j_index, int i_index, string number){
    int start_col;
    int end_col;
    int start_row;
    int end_row;
    // Define before and after row number
    if (i_index == 0){
        start_row = i_index;
    } else {
        start_row = i_index - 1;
    }
    if ( (i_index + number.length()-1) == 139 ){
        end_row = i_index + number.length();
    } else {
        end_row = i_index + number.length() + 1;
    }

    // Define above and under number
    if (j_index == 0){
        start_col = j_index;
    } else {
        start_col = j_index - 1;
    }
    if (j_index == 139){
        end_col = j_index + 1;
    } else {
        end_col = j_index + 2;
    }

    for (int k =start_col; k < end_col; k++){
        for (int l = start_row; l < end_row; l++){
            if (mat[k][l] != '.' && !isdigit(mat[k][l])) {
                return true;
            }
        }
    }
    return false;
}


int partA(vector<vector<char>> &mat){
    int sum = 0;
    for (int j = 0; j<140;j++){
        for (int i = 0; i<140; i++){
            if (isdigit(mat[j][i])){
                // Search 15x around 3 siffer number. 
                string number = extract_number(mat, j, i);
                bool part_number = searh_for_symbol(mat, j, i, number);
                

                if (part_number){
                    cout << " " << number << "  "; // << number << " so before sum: " << sum << "  ";
                    sum += stoi(number);
                    // cout << sum << "   " ;
                    
                }else{
                    // cout << "Not a part number : " << number << "  ";
                }
                i += number.length()-1;
            }
        }
        cout << '\n';
    }
    return sum;
}


int main(){
    int rows = 140;
    int cols = 140;
    vector<vector<char>> matrix(rows, vector<char>(cols));
    fill_matrix(matrix);

    int result = partA(matrix);

    cout << result << '\n';
    return 0;
}