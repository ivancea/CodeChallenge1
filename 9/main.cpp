#include <iostream>
#include <chrono>
#include <cmath>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <bitset>

using namespace std;

struct Sprite {
    const vector<vector<bool>>& mask;
    const int x, y;

    Sprite(const vector<vector<bool>>& mask, int x, int y) : mask(mask), x(x), y(y) {}

    bool collidesWith(const Sprite& other) const {
        if (x + mask[0].size() <= other.x || other.x + other.mask[0].size() <= x) {
            return false;
        }

        if (y + mask.size() <= other.y || other.y + other.mask.size() <= y) {
            return false;
        }

        int minX = max(x, other.x);
        int maxX = min(x + mask[0].size(), other.x + other.mask[0].size());
        int minY = max(y, other.y);
        int maxY = min(y + mask.size(), other.y + other.mask.size());

        for (int i = minX; i < maxX; ++i) {
            for (int j = minY; j < maxY; ++j) {
                if (mask[j - y][i - x] && other.mask[j - other.y][i - other.x]) {
                    return true;
                }
            }
        }

        return false;
    }
};


int main() {
    auto startTotal = chrono::steady_clock::now();

    int n;
    cin >> n;
    cin.ignore();
    
    int spriteCount;
    cin >> spriteCount;
    cin.ignore();

    vector<vector<vector<bool>>> spriteMasks;

    for (int spriteIndex = 0; spriteIndex < spriteCount; ++spriteIndex) {
        int width, height;
        cin >> width >> height;
        cin.ignore();

        vector<vector<bool>> mask(height, vector<bool>(width, false));

        for (int y = 0; y < height; ++y) {
            string row;
            getline(cin, row);

            for (int x = 0; x < width; ++x) {
                mask[y][x] = row[x] == '1';
            }
        }

        spriteMasks.emplace_back(move(mask));
    }

    for(int caseNumber = 1; caseNumber <= n; caseNumber++){
        auto startCase = chrono::steady_clock::now();

        int spritePositionCount;
        cin >> spritePositionCount;

        vector<Sprite> sprites;

        for (int spritePositionIndex = 0; spritePositionIndex < spritePositionCount; ++spritePositionIndex) {
            int spriteIndex, x, y;
            cin >> spriteIndex >> x >> y;

            sprites.emplace_back(spriteMasks[spriteIndex], x, y);
        }

        int collisions = 0;

        // Can be optimized creating quadrants to avoid comparing every sprite with every other one
        for (int i = 0; i < sprites.size(); ++i) {
            for (int j = i + 1; j < sprites.size(); ++j) {
                if (sprites[i].collidesWith(sprites[j])) {
                    collisions++;
                }
            }
        }

        cout << "Case #" << caseNumber << ": "<< collisions << endl;

        cerr << "Case #" << caseNumber << ": " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startCase).count() << "ms" << endl;
    }

    cerr << "Total: " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - startTotal).count() << "ms" << endl;
}