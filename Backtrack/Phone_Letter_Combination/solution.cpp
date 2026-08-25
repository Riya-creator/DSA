class Solution {
    //need to create this maping only as 7 and 9 have 4 CHARACTERS
    // static inline const vector<string>mp ={..}
    static constexpr string mp[10] = {
        "","","abc","def", "ghi","jkl", "mno", "pqrs", "tuv", "wxyz"
    };
    //vector is not a compile-time integral type. so if static is used then either use inline or define out of the class

    void solve(string digits , vector<string>&ans, int ind, string & cur){
        if(ind== digits.size()){
            ans.push_back(cur);
            return;
        }

        int n = digits[ind] -'0';
        string ch  = mp[n];

        for( char c: ch){
            cur += c;
            solve(digits, ans, ind+1, cur);
            cur.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        vector<string>ans;
        string cur ="";

        solve(digits, ans, 0, cur);
        return ans;
    }
};
