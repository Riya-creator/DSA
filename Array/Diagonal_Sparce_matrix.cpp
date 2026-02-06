#include <iostream>
using namespace std;
int main()
{
    //diagonal matrix
    
    int n;
    cout<<"Enter the number of diagonals ";
    cin>>n;
    int dia[n]={0};
    for( int i=0; i<n; i++){
        cin>> dia[i];
    }
    for( int i=0; i<n; i++){
        for( int j=0;j<n; j++){
            if( i==j)
            cout<<dia[i]<<"   ";
            else cout<<0<<"   ";
        }
        cout<<endl;
    }
}
