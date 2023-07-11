// No Copyright
// Written by: Derek Bandouveres
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
// #include <regex>

class EDistance {
 public:
    EDistance(std::string n, std::string m);

    ~EDistance() { delete [] matrix; }

    static int penalty(char a, char b) {
        if (a != b) {
            return 1;
        } else { return 0; }
    }

    std::string testPrint();
    static int min(int a, int b, int c) {
        if (a < b) {
            if (a < c) {
                return a;
            } else { return c; }
        } else {
            if ( b < c) {return b;} else {return c;}
        }
    }
    int optDistance();
    std::string alignment();

 private:
    int ** matrix;
    std::string x, y;
    int dimX, dimY;
};
