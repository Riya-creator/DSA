#include <iostream>
using namespace std;
int main()
{
    //diagonal matrix
    
    int n;
    cout<<"Enter the number of diagonals ";
    cin>>n;
    int dia[n]={0};
    int ldia[n-1]={};
    int udia[n-1]={};
    cout<<"enter the values of the main diagonal:\n";
    for( int i=0; i<n; i++){
        cin>> dia[i];
    }
    cout<<"\n enter the values of the upper diagonal than the main one:\n";
    for( int i=0; i<n-1; i++){
        cin>> udia[i];
    }
    cout<<"\n enter the values of the lower diagonal than the main one:\n";
    
    for( int i=0; i<n-1; i++){
        cin>> ldia[i];
        
    }
    for( int i=0; i<n; i++){
        for( int j=0;j<n; j++){
            if( i==j)
            cout<<dia[i]<<"   ";
            else if(i==j-1){
                cout<<udia[i]<<"   ";
            }
            else if( i== (j+1)){
                cout<<ldia[j]<<"   ";
            }
            else 
            cout<<0<<"   ";
        }
        cout<<endl;
    }
}
