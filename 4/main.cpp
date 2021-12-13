#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

const vector<char> notes{'A', ' ', 'B', 'C', ' ', 'D', ' ', 'E', 'F', ' ', 'G', ' '};

int getNoteIndex(const string& note) {
    for (int i = 0; i < notes.size(); i++) {
        if (notes[i] == note[0]) {
            if (note.size() != 2) {
                return i;
            }

            if (note[1] == '#') {
                return i + 1;
            }

            return i - 1;
        }
    }

    return 0;
}

bool isValidScale(const string& scale) {
    if (scale.empty()) {
        return false;
    }

    if (scale[0] != scale[scale.size() - 1 - (scale[scale.size() - 1] == '#' ? 1 : scale[scale.size() - 1] == 'b' ? 1 : 0)]) {
        return false;
    }

    unordered_map<char, int> notes;

    notes[scale[0]] = -1;

    for (int i = 1; i < scale.size(); i++) {
        if (scale[i] == '#' || scale[i] == 'b') {
            continue;
        }

        if ((++notes[scale[i]]) > 1) {
            return false;
        }
    }

    return notes.size() == 7;
}

string generateScale(const string& scale, const string& steps, int noteIndex) {
    if (steps.empty()) {
        return scale;
    }

    noteIndex += steps[0] == 'T' ? 2 : 1;
    string nextSteps = steps.substr(1);

    if (notes[noteIndex % notes.size()] != ' ') {
        string newScale = generateScale(scale + notes[noteIndex % notes.size()], nextSteps, noteIndex);

        if (isValidScale(newScale)) {
            return newScale;
        }
    }
    if (notes[(noteIndex - 1) % notes.size()] != ' ') {
        string newScale = generateScale(scale + notes[(noteIndex - 1) % notes.size()] + '#', nextSteps, noteIndex);

        if (isValidScale(newScale)) {
            return newScale;
        }
    }
    if (notes[(noteIndex + 1) % notes.size()] != ' ') {
        string newScale = generateScale(scale + notes[(noteIndex + 1) % notes.size()] + 'b', nextSteps, noteIndex);

        if (isValidScale(newScale)) {
            return newScale;
        }
    }

    return "";
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    for(int caseNumber=1; caseNumber<=n; caseNumber++){
        string note;
        getline(cin, note);

        string steps;
        getline(cin, steps);

        int initialIndex = getNoteIndex(note);

        string scale = generateScale(note, steps, initialIndex);

        cout << "Case #" << caseNumber << ": " << scale << endl;
    }
}