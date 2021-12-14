#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>
#include <bitset>


using namespace std;

string readFile(const string& fileName) {
    ifstream file(fileName);
    ostringstream sstr;
    sstr << file.rdbuf();
    return sstr.str();
}

int main() {
    string file = readFile("Invictus.txt");
    string result;
    string secondaryValue;

    int lastPos = 0;
    int pos = 0;

    while ((pos = file.find(0xF3, lastPos)) != string::npos) {
        secondaryValue += file[pos + 2];
        result += file[pos + 3];
        //cerr << (int)file[pos + 3] << endl;

        lastPos = pos + 1;
    }

    int diff = (int)result[17] - (int)'O';

    for (int i=0; i<result.size(); i++) {
        bool isSpecial = ((unsigned char)secondaryValue[i]) == 0x82;
        char c = (char)(result[i] - diff);

        if (isSpecial) {
            c += 'T' - 20;
        }

        cerr << c;
    }
    cerr << endl;

    /*for (int i = 0; i < result.size() - 1; i++) {
        cerr << (int)(result[i] - result[i+1]) << " -> " << i << endl;
    }

    cerr << "SPACE" << endl;

    string myStr = "ROLIHLAHLA";

    for (int i = 0; i < myStr.size() - 1; i++) {
        cerr << (int)(myStr[i] - myStr[i+1]) << endl;
    }*/

    /*cerr << result << endl;
    cout << result << endl;*/
}