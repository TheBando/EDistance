// No Copyright
// Derek Bandouveres

#include <iostream>

#include <SFML/System.hpp>

#include "EDistance.h"

EDistance::EDistance(std::string n, std::string m) {
    x = n; y = m;
    dimX = x.size()+2;
    dimY = y.size()+2;
    matrix = new int*[dimX];
    for (int i = 0; i < dimX; i++) {
        matrix[i] = new int[dimY];
    }
    dimX--;
    dimY--;
}

int EDistance::optDistance() {
    matrix[dimX][dimY] = 0;
    int match, del, ins;
    for (int k=dimY; k >= 1; k--) {
        matrix[dimX][k-1] = matrix[dimX][k] + 2;
    }
    for (int t=dimX; t >= 1; t--) {
        matrix[t-1][dimY] = matrix[t][dimY] + 2;
    }
    for (int i = dimX-1; i >= 0; i--) {
        for (int j = dimY-1; j >= 0; j--) {
            match = matrix[i+1][j+1] + penalty(x[i], y[j]);
            del = matrix[i+1][j] + 2;
            ins = matrix[i][j+1] + 2;
            matrix[i][j] = min(match, del, ins);
        }
    }
    return matrix[0][0];
}

std::string EDistance::testPrint() {
    std::string s = "";
    for (int i=0; i <= dimX; i++) {
        for (int j=0; j <= dimY; j++) {
            if (matrix[i][j] < 10) {
                s+="  "+std::to_string(matrix[i][j]);
            } else { s+=" "+std::to_string(matrix[i][j]); }
        }
        s+="\n";
    }
    return s;
}

std::string EDistance::alignment() {
    int safety = 0;

    std::vector<int> costs;

    std::string sX = "";
    std::string sY = "";
    int i = 0, j = 0;
    int cur, down, right, diag;
    int costIndex = 0;
    std::string tempString;
    while (i < dimX && j < dimY) {
        cur = matrix[i][j]; diag = matrix[i+1][j+1];
        down = matrix[i][j+1]; right = matrix[i+1][j];
        if (cur == diag + penalty(x[i], y[j])) {
            tempString = x[i];
            sX += tempString;
            tempString = y[j];
            sY += tempString;
            i++; j++;
            costs.push_back(penalty(x[i-1], y[j-1]));
            costIndex++;
        } else if (cur == right + 2) {
            sX += x[i];
            sY += "-";
            i++;
            costs.push_back(2);
            costIndex++;
        } else if (cur == down + 2) {
            sY += y[j];
            sX += "-";
            j++;
            costs.push_back(2);
            costIndex++;
        } else { safety++; }

        if (safety >= 9) {
            std::cout << "Safety Engaged" << std::endl;
            break;
        }
    }
    while (j < dimY) {
        sY += std::to_string(y[j]);
        sX += "-";
        j++;
        costs.push_back(2);
        costIndex++;
    }
    while (i < dimX) {
        sY += "-";
        sX += std::to_string(x[i]);
        i++;
        costs.push_back(2);
        costIndex++;
    }
    int total = 0;
    for (int c : costs) {
        total += c;
    }
    std::string s = "";
    s += "Edit Distance = ";
    s += std::to_string(total);
    s += "\n";
    s += " x  y  cost \n";

    for (int l = 0; l < sX.size(); l++) {
        s += " ";
        s += sX[l]; s += "  ";
        s += sY[l]; s += "\t";
        s += std::to_string(costs[l]);
        s += '\n';
    }

    s += "Edit Distance = ";
    s += std::to_string(total);
    s += "\n";


    return s;
}

int main() {
    std::string IN, X, Y;
    std::cin >> IN;
    X = IN;
    std::cin >> IN;
    Y = IN;

    std::cout << "X / Y len: " << std::to_string(X.length()) << " / "
    << std::to_string(Y.length()) << std::endl;
    sf::Clock clock;
    sf::Time t;
    EDistance ed(X, Y);
    ed.optDistance();
    // Uncomment out this line to print the matrix.
    // Not tested in large files.
    // std::cout << ed.testPrint() << std::endl;
    std::cout << ed.alignment() << std::endl;
    t = clock.getElapsedTime();
    std::cout << std::fixed << "Execution time is: "
    << t.asSeconds() << " seconds \n";
    return -1;
}
