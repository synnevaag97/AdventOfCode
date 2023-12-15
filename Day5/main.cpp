

// Extract each map and convert into actual maps. This will give 7 maps. 
// But the input data numbers are large! Creating 7 maps with very large numbers is not the solution. 
// SKal jeg beholde råverdien, finne hvilke intervall den passer inn i og så interpolere? 
// Altså jeg finner hvilke verdi i mapet som er under verdien. Så finner jeg differansen på de og bruker den differansen til å finne riktig verdig på mapet. 
// Dette må gjøre 7 ganger per seed. 


// Kunne brukt nested maps e.g. std::map<int, std::map<int, std::map<int, std::string>>> nestedMaps; Men verdiene er så jævlig store, mapsene blir svære?

// Then create a function that extract location from seed. Going through all the maps. 


// KOnklsjon:
// Maps blir for stort. Så helle lagre intervallene i f.eks: vector<vector<tuple<int, int, int>>> og så gå gjennom hvert map for å finne verdiene mer manuelt. 


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <algorithm> // To use find function

static constexpr int number_of_mappings = 7;

std::vector<unsigned int> parse_line(const std::string& line) {
    std::vector<unsigned int> numbers;
    std::istringstream iss(line);
    // std::cout << "String in: " << line << '\n';
    unsigned int num;
    while (iss >> num) {
        numbers.push_back(num);
        // std::cout << "Number found: " << num << '\n';
    }
    return numbers;
}

void create_map_structure(std::vector<std::vector<std::tuple<unsigned int, unsigned int, unsigned int>>>& (maps_vec), std::vector<unsigned int> &seeds){
    std::fstream input_file;
    input_file.open("/home/tsg/Documents/CalenderTasks/AdventOfCode/Day5/input", std::ios::in);
    if (input_file.is_open()){ //checking whether the file is open
        int map_order = 0;
        std::string line;
        std::string current_map;
        while(std::getline(input_file, line)){
            if (line.empty()) {
                continue; // Skip empty lines
            }
            if (line.find("map:") != std::string::npos) {
                current_map = line.substr(0, line.find(":"));
                // std::cout << "Current map: " << current_map << '\n';
                map_order++;
                // std::vector<std::tuple<int, int, int>> new_vec;
                // maps_vec.push_back(new_vec);
                continue;
            }   

            std::vector<unsigned int> numbers = parse_line(line.substr(line.find(":") + 1, line.length()));
            // std::cout << "Parsed data to vec" << '\n';
            if (current_map.empty()) {
                // Seed-related information
                // std::cout << "Seed data" << '\n';
                seeds.insert(seeds.end(), numbers.begin(), numbers.end());
            } else {
                // Map-related information
                //  std::cout << "Added to map: " << numbers.size() << '\n';
                std::tuple<unsigned int, unsigned int, unsigned int> num(numbers[0], numbers[1], numbers[2]);
                // std::cout << "Accessing map: " << map_order-1 << '\n';
                maps_vec[map_order-1].push_back(num);
               
            }
        }
    }
}


unsigned int partA(){
    std::vector<unsigned int> seeds;
    std::vector<std::vector<std::tuple<unsigned int, unsigned int, unsigned int>>> maps_vec(number_of_mappings);
    // std::unordered_map<std::string, std::vector<std::tuple<int, int, int>>> maps;
    create_map_structure(maps_vec, seeds);


    unsigned int lowest_loc = 1;
    for (const unsigned int& seed : seeds){
        std::cout << "Iterating through seeds: " << seed << '\n';
        unsigned int matching_pair = seed;
        unsigned int map_iterating = 1;
        int found_all_mappings = 0;
        for (const auto& map : maps_vec){
            // std::cout << "Iterating through maps: " << map_iterating << '\n';
            
            for (const auto& line: map){
                unsigned int dest_range_start, src_range_start, range_len;
                std::tie(dest_range_start, src_range_start, range_len) = line;
                std::cout << "Iterating through tuple: " << dest_range_start << " " << src_range_start << " " << range_len << '\n';
                std::cout << matching_pair << "   " << src_range_start << "    " << (matching_pair == src_range_start) << '\n';
                if (!((matching_pair >= src_range_start) && (matching_pair < (src_range_start+range_len)))){
                    
                    continue;
                }
                unsigned int diff = matching_pair - src_range_start;
                matching_pair = dest_range_start + diff;
                
                found_all_mappings ++;
                break;
            }
            std::cout << "FOund range: " << matching_pair << " at " << map_iterating<< '\n';
            map_iterating++;

        }

        std::cout << "FOund location: " << matching_pair << " all maps " << found_all_mappings << '\n';
        if (lowest_loc == 1){
            lowest_loc = matching_pair;
        }else if(lowest_loc > matching_pair){
            lowest_loc = matching_pair;
        }
    }
    return lowest_loc;
}

int main(){
    unsigned int result = partA();
    std::cout << " Lowest location: " <<  result;
    return 0;
}
