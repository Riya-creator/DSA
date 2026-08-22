class Solution {
    //time:O(n)
    //space:O(n)
public:
    string convert(string s, int numRows) {
        if(numRows ==1) return s;
        //as in this case logic for coming doesn't work n infinite loop case formed
        string rows[numRows];

        int n = s.size(), i=0, r= 0;
        while(i<n){
            while(r<numRows && i<n){
                rows[r++] += s[i++];
            }
            r-=2;
            while(r>=0 && i<n){
                rows[r--] += s[i++];
            }
            r+=2;
        }
        string ans ="";
        for( auto c:rows){
            ans+= c;
        }

        return ans;
    }
};
