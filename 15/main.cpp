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


int main() {
    auto startTotal = chrono::steady_clock::now();

    int n;
    cin >> n;
    cin.ignore();
    
    for(int caseNumber = 1; caseNumber <= n; caseNumber++){
        auto startCase = chrono::steady_clock::now();
        
        long long number;
        cin >> number;

        cout << "Case #" << caseNumber << ": "<< "" << endl;

        cerr << "Case #" << caseNumber << ": " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startCase).count() << "ms" << endl;
    }

    cerr << "Total: " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTotal).count() << "ms" << endl;
}