#include <iostream>
using namespace std;

int main () {
    int input;
    cin >> input;
    int answer = 1;
    for (int i = 1; i <= input; ++i) {
	answer = answer * i;
    }
    cout << answer << endl;
    return (0);
}
