//Divide the 10*10 matrix into 8 divisions
//cut at every 45 deg from center of the matrix n horizontal line
//min make the things decide which corrdinate will decide the ring in which it is present

#include<bits/stdc++.h>
using namespace std;
 
#define endl '\n'
#define ll long long
 
int main(){
    int t;
    cin>>t;
    char ch;
    while( t--){
        int ans=0;
        for ( int i=1; i<=10; i++){
            for( int j=1; j<=10; j++){
                cin>>ch;
                if( ch=='X'){
// top_distance, bottom_distance, left_distance, right_distance
//min of all is the deciding factor
                    ans+= min({i, 11-i,j, 11-j});
                }
            }
        }
        cout<<ans<<endl;
    }
}
