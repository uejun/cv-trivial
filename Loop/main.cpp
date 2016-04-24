#include <iostream>
#include <vector>

using namespace std;

int main() {

    string temp;
    cout  << "Input text: " << flush;
    cin >> temp;
    while (true) {
        if (temp != "|") {
            cout << temp << endl;
            cout << "Input text: " << flush;
            cin >> temp;
        }else {
            break;
        }
    }

    cout << "The Process is end." << endl;

    return 0;
}
