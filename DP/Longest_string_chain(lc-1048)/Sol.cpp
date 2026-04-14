/*This problem is secretly:

Longest path in a DAG

Where:

Edge = “can form by adding one character”

And your hashmap DP = optimized topological DP*/
class Solution {
public:
    int longestStrChain(vector<string>& words) {
        sort(words.begin(), words.end(), [](string &a, string &b){
            return a.size()< b.size();
            //compartors alwyas want a strict ordering no = sign allowed here then
        });
        int ans=1;
        unordered_map<string, int>dp;
        for( string &w:words){
            dp[w]=1;
            for(int j=0; j< w.size(); j++){
                string prev = w.substr(0, j) + w.substr(j+1);
//o->i-1
                // prev = w;
                // prev.erase(j, 1);
                if(dp.count(prev)){
                    dp[w] = max(dp[prev]+1, dp[w]);
                    
                }
            }
            ans= max(ans, dp[w]);
        }
        return ans;
    }
};
//time:O(N log N + N * L²)
//space:O(N * L)
