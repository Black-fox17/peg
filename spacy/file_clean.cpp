#include <iostream>
#include <string>
#include <fstream>

bool is_empty_line(std::string& line) {
    for (char c : line) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

std::string clean_line(std::string& line) {
    std::string result;
    bool spaceFound = false;
    bool started = false;

    for (char c : line) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (!started){
            if(!std::isspace(uc)){
                started = true;
                result += c;
            }
            continue;
        }
        if (std::isspace(uc) ) {
            if (!spaceFound) {
                result += ' ';
                spaceFound = true;
            }
        } else {
            result += c;
            spaceFound = false;
        }
    }

    return result;
}

int main(int argc, char *argv[]){
    std::string line;
    if (argc != 2) {
        std::cerr << "The input file is not provided";
        return 1;
    }
    std::ifstream input_file(argv[1]);
    if (!input_file.is_open()){
        std::cerr << "Unable to open file: " << argv[1] << '\n';
        return 1;
    }
    std::string outputFilename = argv[1];
    size_t lastDot = outputFilename.find_last_of(".");
    if (lastDot != std::string::npos) {
        outputFilename = outputFilename.substr(0, lastDot) + ".clean";
    } else {
        outputFilename += ".clean";
    }
    std::ofstream output_file(outputFilename);
    while (getline(input_file, line)) {
        if (is_empty_line(line)){
            continue;
        }
        output_file << clean_line(line) << '\n';
    }  
    input_file.close();
    output_file.close();
    std::cout << "File cleaned successfully: " << outputFilename << '\n';
    return 0;
}