#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

using namespace std;


set<int> solve(const vector<string>& cities, const unordered_map<int, unordered_set<int>>& edges) {
    set<int> result;

    for (int possibleCriticalCity = 0; possibleCriticalCity < cities.size(); ++possibleCriticalCity) {
        unordered_set<int> visited;
        unordered_set<int> toVisit;

        // Already visited == Won't be crossed
        visited.insert(possibleCriticalCity);

        // First city, a random one
        toVisit.insert(possibleCriticalCity == 0 ? 1 : 0);

        while (toVisit.size() > 0) {
            int currentCity = *toVisit.begin();
            toVisit.erase(toVisit.begin());

            visited.insert(currentCity);

            for (int nextCity : edges.at(currentCity)) {
                if (visited.find(nextCity) == visited.end()) {
                    toVisit.insert(nextCity);
                }
            }
        }

        if (visited.size() != cities.size()) {
            result.insert(possibleCriticalCity);
        }
    }

    return result;
}

int main() {
    auto startTotal = chrono::steady_clock::now();

    int n;
    cin >> n;
    cin.ignore();

    for(int caseNumber=1; caseNumber<=n; caseNumber++){
        auto startCase = chrono::steady_clock::now();

        int ticketCount;
        cin >> ticketCount;
        cin.ignore();

        map<string, int> citiesToIndex;
        unordered_map<string, unordered_set<string>> rawTickets;

        for(int i=0; i<ticketCount; i++){
            string ticket;
            getline(cin, ticket);

            string city1 = ticket.substr(0, ticket.find(','));
            string city2 = ticket.substr(ticket.find(',') + 1);

            citiesToIndex[city1] = -1;
            citiesToIndex[city2] = -1;
            rawTickets[city1].insert(city2);
        }

        vector<string> cities;

        for (auto& city : citiesToIndex) {
            cities.push_back(city.first);
            city.second = cities.size() - 1;
        }

        unordered_map<int, unordered_set<int>> edges;

        for(auto ticket : rawTickets){
            for (auto city : ticket.second) {
                edges[citiesToIndex[ticket.first]].insert(citiesToIndex[city]);
                edges[citiesToIndex[city]].insert(citiesToIndex[ticket.first]);
            }
        }

        auto results = solve(cities, edges);

        cout << "Case #" << caseNumber << ": ";

        int count = 0;
        for(auto result : results){
            if (count++ > 0) {
                cout << ",";
            }
            cout << cities[result];
        }

        if (results.size() == 0) {
            cout << "-";
        }

        cout << endl;

        cerr << "Case #" << caseNumber << ": " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startCase).count() << "ms" << endl;
    }

    cerr << "Total: " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTotal).count() << "ms" << endl;
}