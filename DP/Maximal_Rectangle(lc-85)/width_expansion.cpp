class Solution {
    int rec(vector<int>&dp){
        stack<int>s;
        int ans=0;
            for( int k=0 ; k< dp.size(); k++){
                while(!s.empty() && dp[s.top()]>dp[k]){
                    int h= dp[s.top()];
                    s.pop();

                    int left= s.empty() ? -1 :s.top();
                    int width= k-1 -left;
                    ans = max(ans, h* width);
                }
                s.push(k);
            }        
            while(!s.empty()){
                int h= dp[s.top()];
                s.pop();

                int left= s.empty() ? -1 :s.top();
                int width= dp.size()-1 -left;
                ans = max(ans, h* width); 
            }
            return ans;
    }
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int r= matrix.size(), c= matrix[0].size(), ans=0;
        vector<int> dp(r, 0), temp(r);
        for( int i=0; i< c; i++){
            temp = dp;
            for( int j=0; j<r; j++){
                if( matrix[j][i]=='0'){
                    dp[j]=0;
                    continue;
                }
                dp[j]= temp[j]+1;
            }
            ans = max(ans, rec(dp));
        }
        return ans;
    }
};
