#pragma once
#include "fstream"

class FileInput {
    private:
        std::ifstream file;
    public:
        FileInput(std::string fileName);
        ~FileInput();
        std::ifstream* getStream();
};

class FileOutput {
    private:
        std::ofstream file;
    public:
        FileOutput(std::string fileName);
        ~FileOutput();
        std::ofstream* getStream();
};