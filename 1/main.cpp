#include <iostream>
#include <map>
#include <cmath>

using namespace std;

int main(){
    int n;
    cin >> n;
    cin.ignore();

    for(int caseNumber=1; caseNumber<=n; caseNumber++){
        int a, b;
        cin >> a;
        cin.ignore();
        cin >> b;

        if (a + b == 6*2) {
            cout << "Case #" << caseNumber << ": -" << endl;
        } else {
            cout << "Case #" << caseNumber << ": " << (a + b + 1) << endl;
        }
    }
}