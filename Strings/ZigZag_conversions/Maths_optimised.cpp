class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows == 1 || numRows >= s.length())
            return s;

        string ans = "";
        int cycle = 2 * (numRows - 1);

        for(int row = 0; row < numRows; row++) {
            int i = row;

            while(i < s.length()) {
                ans += s[i];
                
                if(row == 0 || row == numRows - 1) {
                    i += cycle;
                }
                else {
                    int downGap = cycle - 2 * row;
                    int upGap = 2 * row;

                    if(downGap > 0) {
                        i += downGap;
                        if(i < s.length())
                            ans += s[i];
                    }

                    i += upGap;
                }
            }
        }

        return ans;
    }
};
