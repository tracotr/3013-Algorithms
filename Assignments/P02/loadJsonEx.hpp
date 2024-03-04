#include "./headers/json.hpp" // Make sure this points to the correct path of json.hpp
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

using json = nlohmann::json;

// Function to load a json
// input takes a string to the filepath
json loadJsonFile(string filePath) {
    ifstream fileStream(filePath);
    json myJson; // return variable
    if (fileStream.is_open()) {
        fileStream >> myJson;
        fileStream.close();
    } else {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }

    return myJson;
}