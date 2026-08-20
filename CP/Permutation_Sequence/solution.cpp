class Solution {
    //time: O(n2) , space: O(n)
    int fac( int n, vector<int>&f){
        if( n== 0) return 1;
        if ( n==1 || n==2) return n;
        if( f[n] != -1 ) return f[n];
        return f[n] = fac(n-1, f) * n;
    }
//must seperate the concept of deleted n left seperate like take set then make deletions
//can make the fact precomputed for such a small length or the upper bound like 9
public:
    string getPermutation(int n, int k) {
        int turn = 0;
        string ans = "";

        vector<int> f(n+1, -1);
        vector<bool> used(n+1, false);

        int t= n;
        while(t){
            int num  = fac(t-1, f);
            for( int i=1; i<= n; i++){
                if( used[i] ) continue;
                if( num >=k) {
                    used[i] = true;
                    ans+= ('0' + i);
                    break;
                }
                k -= num;
            }
            t--;
        }
        return ans;
    }
};
