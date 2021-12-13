#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

void clearSpaces(string& s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            s.erase(i, 1);
            i--;
        }
    }
}

string removeAll(const unordered_set<string>& pokemons, const string& map) {
    if (pokemons.empty()) {
        return map;
    }
    
    for (auto& pokemon : pokemons) {
        auto pos = map.find(pokemon);
        if (pos != string::npos) {
            string newMap = map.substr(0, pos) + map.substr(pos + pokemon.length());
            unordered_set<string> newPokemons = pokemons;
            newPokemons.erase(pokemon);

            string cleanMap = removeAll(newPokemons, newMap);

            if (cleanMap.length() < map.length()) {
                return cleanMap;
            }
        }

        // Reverse pokemon
        string reversedPokemon{pokemon.rbegin(), pokemon.rend()};
        pos = map.find(reversedPokemon);
        if (pos != string::npos) {
            string newMap = map.substr(0, pos) + map.substr(pos + pokemon.length());
            unordered_set<string> newPokemons = pokemons;
            newPokemons.erase(pokemon);

            string cleanMap = removeAll(newPokemons, newMap);

            if (cleanMap.length() < map.length()) {
                return cleanMap;
            }
        }
    }

    return "";
}

int main(){
    int n;
    cin >> n;
    cin.ignore();

    for(int caseNumber=1; caseNumber<=n; caseNumber++){
        int pokemonCount, rows, columns;
        cin >> pokemonCount >> rows >> columns;
        cin.ignore();

        unordered_set<string> pokemons;

        for(int i=0; i<pokemonCount; i++){
            string pokemon;
            getline(cin, pokemon);
            
            pokemons.insert(pokemon);
        }

        string map;

        for(int i=0; i<rows; i++){
            string row;
            getline(cin, row);
            clearSpaces(row);

            map += row;
        }

        string finalMap = removeAll(pokemons, map);
        
        cout << "Case #" << caseNumber << ": " << finalMap << endl;
    }
}