#include <iostream>

using namespace std;
void binSearch(int * a, int n, int num){
    
    int b=0, e=n, mid=0 ;
    for( int i=0; i<n; i++){
        for( int j=0; j<n-1-i;j++){
            if(a[j]> a[j+1]){
                int temp= a[j];
                a[j]= a[j+1];
                a[j+1]= temp;
            }
        }
    }
    while( b<=e){
        mid=b+(e-b)/2;
        if( a[mid]== num){
            cout<<"found the element at: "<<mid<<" by binary search with time complexeity O(log n)\n";
            return ;
        }
        if( a[mid]>num){
            e= mid-1;
        }
        else b=mid+1;
    }
    cout<<"Element doesn't found";
    
}
void linSearch(int * a, int n, int num){
    for( int i=0; i< n; i++){
        if( a[i]== num){
            cout<<"found the element at index: "<<i<<" by linear search by time complexity as O(n)";
            return;
        }
    }
    cout<<"Element doesn't found";
}

int main()
{
    int n, num;
    cout<<"Enter the number of the array in which u need to search:";
    cin>>n;
    int a[n];
    cout<<"\nEnter the values to the arry:";
    for( int i=0;i<n; i++){
        cin>>a[i];
    }
    cout<<"Enter the number to be searched in this";
    cin>>num;
    binSearch(a, n,  num);
    linSearch(a, n, num);
}
