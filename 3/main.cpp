#include <iostream>
#include <string>
#include <map>
#include <regex>

using namespace std;

// Decode function
map<char, double> decode(string& input) {
    map<char, double> letterValues;

    regex r(input[0] == '{'
        ? "'(\\w)': (\\d+)(?:/(\\d+))?"
        : input[0] == '['
        ? "\\('(\\w)', (\\d+)(?:/(\\d+))?\\)"
        : "(\\w)=(\\d+)(?:/(\\d+))?");

    auto start = sregex_iterator(input.begin(), input.end(), r);
    auto end = sregex_iterator();

    for (auto i = start; i != end; ++i) {
        auto match = *i;
        
        string letter = match[1];
        string value = match[2];
        string divisor = match[3];

        if (divisor.empty()) {
            letterValues[letter[0]] = stod(value);
        } else {
            letterValues[letter[0]] = stod(value) / stod(divisor);
        }
    }

    return letterValues;
}

double calculate(const map<char, double>& letterValues, const string& word) {
    double result = 0;

    for (char c : word) {
        result += letterValues.at(c);
    }

    return result;
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    for(int caseNumber=1; caseNumber<=n; caseNumber++){
        string input;
        getline(cin, input);

        int hyphenPos = input.find("-");
        string word1 = input.substr(0, hyphenPos);

        int separator = input.find("|", hyphenPos);
        string word2 = input.substr(hyphenPos + 1, separator - hyphenPos - 1);

        string lettersInput = input.substr(separator + 1);

        map<char, double> letterValues = decode(lettersInput);

        double value1 = calculate(letterValues, word1);
        double value2 = calculate(letterValues, word2);

        string winningWord = value1 == value2
            ? "-"
            : value1 > value2
            ? word1
            : word2;

        cout << "Case #" << caseNumber << ": " << winningWord << endl;
    }
}