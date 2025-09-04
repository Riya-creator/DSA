#include <iostream>
using namespace std;

int main() {
    int non, non2;
    cout << "Enter total nonzero values of matrix 1: ";
    cin >> non;

   
    int values[100][3]; 

    cout << "Enter row, col, value for matrix 1:\n";
    for (int i = 0; i < non; i++) {
        cin >> values[i][0] >> values[i][1] >> values[i][2];
    }

    int r, c;
    cout << "enter original matrix rows and cols: ";
    cin >> r >> c;

    cout << "\nMatrix 1:\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int printed = 0;
            for (int k = 0; k < non; k++) {
                if (values[k][0] == i && values[k][1] == j) {
                    cout << values[k][2] << " ";
                    printed = 1;
                    break;
                }
            }
            if (!printed) cout << 0 << " ";
        }
        cout << endl;
    }

    // input for 2nd matrix
    cout << "\nenter total nonzero values of matrix 2: ";
    cin >> non2;
    int values2[100][3];

    cout << "Enter row, col, value for matrix 2:\n";
    for (int i = 0; i < non2; i++) {
        cin >> values2[i][0] >> values2[i][1] >> values2[i][2];
    }

    cout << "\nMatrix 2:\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int printed = 0;
            for (int k = 0; k < non2; k++) {
                if (values2[k][0] == i && values2[k][1] == j) {
                    cout << values2[k][2] << " ";
                    printed = 1;
                    break;
                }
            }
            if (!printed) cout << 0 << " ";
        }
        cout << endl;
    }

    cout << "\nAddition Matrix:\n";
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            int sum = 0;
            for (int k = 0; k < non; k++) {
                if (values[k][0] == i && values[k][1] == j) {
                    sum += values[k][2];
                    break;
                }
            }
            for (int k = 0; k < non2; k++) {
                if (values2[k][0] == i && values2[k][1] == j) {
                    sum += values2[k][2];
                    break;
                }
            }
            cout << sum << " ";
        }
        cout << endl;
    }

    // transpose of first matrix
    cout << "\nTranspose of Matrix 1:\n";
    for (int i = 0; i < c; i++) {    
        for (int j = 0; j < r; j++) {
            int printed = 0;
            for (int k = 0; k < non; k++) {
                if (values[k][0] == j && values[k][1] == i) {
                    cout << values[k][2] << " ";
                    printed = 1;
                    break;
                }
            }
            if (!printed) cout << 0 << " ";
        }
        cout << endl;
    }

    return 0;
}
