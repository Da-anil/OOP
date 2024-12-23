#include "File.h"

FileInput::FileInput(std::string fileName) { 
    file.open(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
}

FileInput::~FileInput() {
    file.close();
}

std::ifstream* FileInput::getStream() {
    return &file;
}

FileOutput::FileOutput(std::string fileName) {
    file.open(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
}

FileOutput::~FileOutput() {
    file.close();
}

std::ofstream* FileOutput::getStream() {
    return &file;
}