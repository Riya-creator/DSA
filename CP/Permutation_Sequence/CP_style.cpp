class Solution {
    //time: O(N2)
    //space: o(n)
    //but more faster for even little more constraints
public:
    string getPermutation(int n, int k) {
        vector<int> nums;
        string ans;

        for(int i = 1; i <= n; i++)
            nums.push_back(i);

        vector<int> fact(n + 1, 1);
        for(int i = 1; i <= n; i++)
            fact[i] = fact[i - 1] * i;

        k--;// to make that to the 0-index to get direct the number to use 

        while(n) {
            int idx = k / fact[n - 1];//  index now to be used 

            ans += to_string(nums[idx]);
            nums.erase(nums.begin() + idx);

            k %= fact[n - 1];// move to next block left k value
            n--;
        }

        return ans;
    }
};
