#include <iostream>
using namespace std;
void low(int n, int m){
    int e[n], t=0;
    cout<<"Enter the non zero values of the matrix";
    for( int i=0;i <n; i++){
        cin>>e[i];
    }
    for(int i=0; i<m; i++){
        for( int j=0; j<m; j++){
            if( i<=j){
            cout<<e[t]<<"  ";
            t++;
            }
            else cout<<0<<"  ";
        }
        cout<<"\n";
    }
}
void up(int n, int m){
    int e[n], t=0;
    cout<<"Enter the non zero values of the matrix";
    for( int i=0;i <n; i++){
        cin>>e[i];
    }
    for(int i=0; i<m; i++){
        for( int j=0; j<m; j++){
            if( i>=j){
            cout<<e[t]<<"  ";
            t++;
            }
            else cout<<0<<"  ";
        }
        cout<<"\n";
    }
}
int main()
{
    int n, op;
    cout<<"enter the order of matrix";
    cin>>n;
    cout<<"Lower triangle -> press 1\n Upper triangel press 2";
    cin>>op;
    if( op==1)
    low((n*(n+1))/2, n);
    else up((n*(n+1))/2, n);
    
}
