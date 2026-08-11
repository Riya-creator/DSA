class Solution {
    //prefix set+ greedy+ bitmask method
    //time n space: O(32*n) ~ O(n)
public:
    int findMaximumXOR(vector<int>& nums) {
        int ans =0, mask =0;

        for( int bit = 30 ; bit>=0; bit--){
            mask |= (1<<bit);

            unordered_set<int>prefixes;

            for( int n: nums){
                prefixes.insert(n&mask);
            }

            int candidate = ans | (1<<bit);
            for( int prefix: prefixes){
                int needed=  candidate ^  prefix;

                if( prefixes.count(needed)){
                    ans = candidate;
                    break;
                }
            }
        }
        return ans;
    }
};
