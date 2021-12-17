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

struct Solution {
    int steps;
    int amount;

    Solution(): steps(100), amount(1) {}
    Solution(int steps, int amount): steps(steps), amount(amount) {}
    Solution(const Solution& other): steps(other.steps), amount(other.amount) {}
    Solution& operator=(const Solution& other) {
        steps = other.steps;
        amount = other.amount;
        return *this;
    }

    static Solution best(const Solution& a, const Solution& b) {
        if (a.steps < b.steps) {
            return a;
        }
        if (a.steps > b.steps) {
            return b;
        }
        return a.amount > b.amount ? a : b;
    }
};

Solution solve(const unordered_map<string, unordered_map<string, int>>& trades, unordered_set<string>& visited, unordered_map<string, Solution>& solutionsByCurrency, string currency, int steps, int amount) {
    auto it = trades.find(currency);

    if (it == trades.end()) {
        return Solution();
    }

    if (solutionsByCurrency.find(currency) != solutionsByCurrency.end()) {
        return solutionsByCurrency[currency];
    }

    Solution bestSolution;

    for (const auto& [target, value] : it->second) {
        if (visited.find(target) != visited.end()) {
            continue;
        }

        int nextSteps = steps + 1;
        int nextAmount = amount * value;

        if (target == "BTC") {
            bestSolution = Solution::best(bestSolution, Solution(nextSteps, nextAmount));
        } else {
            visited.insert(target);

            bestSolution = Solution::best(bestSolution, solve(trades, visited, solutionsByCurrency, target, nextSteps, nextAmount));

            visited.erase(target);
        }
    }

    return solutionsByCurrency[currency] = bestSolution;
}

int main() {
    auto startTotal = chrono::steady_clock::now();

    int n;
    cin >> n;
    cin.ignore();
    
    for(int caseNumber = 1; caseNumber <= n; caseNumber++){
        auto startCase = chrono::steady_clock::now();
        
        unordered_map<string, unordered_map<string, int>> trades;

        int websiteCount;
        cin >> websiteCount;

        for (int i = 0; i < websiteCount; i++) {
            string website;
            int availableTrades;
            cin >> website >> availableTrades;

            for (int j = 0; j < availableTrades; j++) {
                string source, target;
                int amount;
                cin.width(3);
                cin >> source;
                cin.ignore();
                cin.width(0);
                cin >> amount;
                cin.ignore();
                cin.width(3);
                cin >> target;
                cin.width(0);

                if (amount > 0) {
                    trades[source][target] = amount;
                }
            }
        }

        unordered_set<string> visited;
        unordered_map<string, Solution> solutionsByCurrency;

        Solution solution = solve(trades, visited, solutionsByCurrency, "BTC", 0, 1);

        cout << "Case #" << caseNumber << ": "<< solution.amount << endl;

        cerr << "Case #" << caseNumber << ": " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startCase).count() << "ms" << endl;
    }

    cerr << "Total: " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTotal).count() << "ms" << endl;
}