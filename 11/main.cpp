#include <iostream>
#include <chrono>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>

using namespace std;

int getCommonLength(string s1, string s2) {
    int i = 0;
    while (i < s1.size() && i < s2.size() && s1[i] == s2[i]) {
        i++;
    }
    return i;
}

vector<int> calculateCommonLengths(const vector<string>& functions) {
    if (functions.size() == 0) {
        return {};
    }

    vector<int> commonPrefixes(functions.size() - 1);
    for (int i = 0; i < functions.size() - 1; i++) {
        commonPrefixes[i] = getCommonLength(functions[i], functions[i + 1]);
    }
    return commonPrefixes;
}

int main() {
    auto startTotal = chrono::steady_clock::now();

    int n;
    cin >> n;
    cin.ignore();
    
    for(int caseNumber = 1; caseNumber <= n; caseNumber++){
        auto startCase = chrono::steady_clock::now();

        int functionCount, functionsPerFile;
        cin >> functionCount >> functionsPerFile;
        cin.ignore();

        vector<string> functions;

        for (int i = 0; i < functionCount; i++) {
            string functionName;
            getline(cin, functionName);
            functions.emplace_back(functionName);
        }

        sort(functions.begin(), functions.end());

        int totalScore = 0;

        if (functionsPerFile == 1) {
            for (string& function : functions) {
                totalScore += function.size();
            }
        } else if (functions.size() > 1) {
            vector<int> commonLengths = calculateCommonLengths(functions);

            int maxCommonLength = *max_element(commonLengths.begin(), commonLengths.end());
            
            while (functions.size() > 0) {
                int contiguousLength = 0;
                int index = 0;
                for (; index < commonLengths.size(); index++) {
                    if (commonLengths[index] >= maxCommonLength) {
                        contiguousLength++;

                        if (contiguousLength == functionsPerFile - 1) {
                            break;
                        }
                    } else {
                        contiguousLength = 0;
                    }
                }

                if (contiguousLength < functionsPerFile - 1) {
                    maxCommonLength--;
                } else {
                    totalScore += maxCommonLength;
                    
                    functions.erase(functions.begin() + index - functionsPerFile + 2, functions.begin() + index + 2);
                }

                if (functions.size() == 1) {
                    totalScore += functions[0].size();
                    break;
                }

                commonLengths = calculateCommonLengths(functions);

                auto nextMaxCommonLength = max_element(commonLengths.begin(), commonLengths.end());
                if (nextMaxCommonLength != commonLengths.end() && *nextMaxCommonLength < maxCommonLength) {
                    maxCommonLength = *nextMaxCommonLength;
                }
            }
        }

        cout << "Case #" << caseNumber << ": "<< totalScore << endl;

        cerr << "Case #" << caseNumber << ": " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startCase).count() << "ms" << endl;
    }

    cerr << "Total: " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTotal).count() << "ms" << endl;
}