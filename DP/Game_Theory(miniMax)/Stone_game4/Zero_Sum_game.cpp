//Time  : O(n√n)  Space : O(n)
class Solution {
    vector<int> sq;//already sorted so use vector as insertion O(1)
    void precompute(int n){//root n

        for(int i= 1;i*i<=n; i++){
            sq.push_back(i*i);
        }
    }

    bool find(int n, vector<int>&dp){//O(n)
        if( dp[n]!= -1) return (bool) dp[n];
//log root n
        auto it = upper_bound( sq.begin(), sq.end(), n );//no lowerbound as then may cause the negative index for find case then make the dp wrong
        it--;

        for( ; ; it-- ){//o(root n) {O(log n + √n) = O(√n)}
            if( ! find(n- *it , dp ) ) return dp[n] = true;
            if(it == sq.begin()) break;
        }

        return dp[n] = false;
    }
public:
    bool winnerSquareGame(int n) {
        precompute(n);
        vector<int> dp(n+1, -1);// 1-> true , 0->false

        dp[1]= 1;
        dp[0]= 0;
        return find(n, dp);
    }
};
