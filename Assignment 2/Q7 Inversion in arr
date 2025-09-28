#include <iostream>
using namespace std;
void findInversion(int * a, int n){
    int flag=0;
    for( int i=0; i<n; i++){
        flag= 0;
        for( int j=0; j<n-1-i;j++){
            if(a[j]> a[j+1]){
                cout<<"\n inversion :"<<a[j+1]<<", "<<a[j]<<"\n";
                flag=1;
                int temp= a[j];
                a[j]= a[j+1];
                a[j+1]= temp;
            }
        }
            if( flag== 0){
                cout<<"No more inversions left..";
                break;
            }
    }
}
void show(int *a, int n){
    cout<<"Array is :\n";
    for( int i=0; i< n; i++){
        cout<<a[i]<<", ";
    }
}
int main()
{
    int a[7]={64, 34, 25, 12, 22, 11, 90};
    show(a,7);
    findInversion(a, 7);
}
////------------------------------to  be considered

#include <bits/stdc++.h>
using namespace std;

long long countInversionsCountingSort(vector<int> &arr, int maxVal) {
    int n = arr.size();
    vector<int> freq(maxVal + 1, 0); // frequency array

    long long invCount = 0;

    // Traverse from right to left
    for (int i = n - 1; i >= 0; i--) {
        int x = arr[i];

        // Count how many numbers smaller than x have appeared
        for (int j = 0; j < x; j++) {
            invCount += freq[j];
        }

        // Mark this number as seen
        freq[x]++;
    }

    return invCount;
}

int main() {
    vector<int> arr = {2, 4, 1, 3, 5};
    int maxVal = *max_element(arr.begin(), arr.end());

    cout << "Number of inversions = "
         << countInversionsCountingSort(arr, maxVal) << endl;

    return 0;
}

