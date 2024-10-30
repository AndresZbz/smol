#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

void read_and_show_file(const std::string& path) {
    std::ifstream myfile(path);
    std::string content;
    if(myfile.is_open()) {
        while(std::getline(myfile, content)) {
            std::cout << content << std::endl;
        }
    }
}

void read_and_edit_file(const std::string& path, const std::string& line_to_edit) {
    std::ifstream myfile(path);
    std::vector<std::string> lines;
    std::string content;
    bool line_found = false;

    if(myfile.is_open()) {
        while(std::getline(myfile, content)) {
            lines.push_back(content);
            if(content == line_to_edit) {
                std::cout << "Current line: " << content << std::endl;
                line_found = true;
            } 
        }
        myfile.close();

        if(!line_found) {
            std::cout << "Line not found in the file.\n";
            return;
        }

        std::string new_text;
        std::cout << "Enter new text: ";
        std::getline(std::cin, new_text);

        // Update the line in the vector
        for (auto& line : lines) {
            if (line == line_to_edit) {
                line = new_text; // Update the line
                break;
            }
        }

        // Write back to the file
        std::ofstream outfile(path);
        for (const auto& line : lines) {
            outfile << line << "\n";; // Write each line back
        }
        outfile.close();

        std::cout << "Line updated successfully.\n";
    } else {
        std::cout << "Unable to open the file\n";
    }
}

int main(int argc, char** argv) {
    if(argc == 1) {
        std::cout <<"Commands: <argument1> <argument2>\n= read <file> reads the file specified\n= edit <file> <line> reads and allows to edit the line specified";
        return 0;
    }

    if(argc > 1 && std::strcmp(argv[1], "read") == 0) {
        system("clear");
        std::string file = argv[2];
        read_and_show_file(file);

    } else if(argc > 1 && std::strcmp(argv[1], "edit") == 0) {
        system("clear");
        std::string file = argv[2];
        std::string content = argv[3];
        read_and_edit_file(file, content);

    } else {
        system("clear");
        std::cout << "Unable to continue, write with empty arguments to check the help section.";
        return 0;
    }

    return 0;
}