#include<stdio.h> 
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<random>
#include<vector>

int main() {
    srand (time(NULL));

    int lineamount = 50;
    std::string filename = "hw0.cpp";
    std::vector<std::string> contents;
    int filelength = 0;

    std::ifstream infile;
    infile.open(filename);

    std::cout << "a" << std::endl;

    while(!infile.eof()) {
        std::string tsrc = "";
        std::getline(infile, tsrc);
        std::cout << "a.5" << std::endl;
        contents.push_back(tsrc);
        ++filelength;
    }
    infile.close();
    std::cout << "b" << std::endl;

    std::string linespicked [lineamount];
    for(int i=0; i<lineamount; ++i) {
        linespicked[i] = contents[rand() % filelength];
        std::cout << linespicked[i] << std::endl;
    }

    return 0;
}