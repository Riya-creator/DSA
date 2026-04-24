class Solution {
    /*three possibity of the route in this:
    1.from the direct h1-h2
    2. from y-h1
    3. from 
    */
public:
    vector<int> countOfPairs(int n, int x, int y) {
        x--;y--;//to make them 0-indexed only
        vector<int> ans(n);
        for( int i=0; i< n; i++){
            for( int j=i+1; j< n;j++){
                int d= j-i, viax= abs(x-i)+1+abs(j-y), viay= abs(y-i)+abs(j-x)+1;
                int dis= min({d, viax, viay});
                ans[dis-1] +=2;
            }
        }
        return ans;
    }
};
