class Solution {
public:
    string multiply(string num1, string num2) {
        int n= num1.size(), m = num2.size();
        vector<int> res(n+m, 0);
        for(int i=n-1; i>= 0; i--){
            for( int j=m-1; j>=0; j--){
                int mul= (num1[i]-'0' )*(num2[j] -'0');
                int posc= i+j;//position fo the carry to be placed
                int posn= i+j+1; //position for the number to be placed

                int sum= res[posn] + mul;

                res[posc] += sum/10;
                res[posn ]= sum%10;
            }
        }
        string ans= "";
        for (int i=0; i< n+m; i++){
            if( ans =="" && res[i] ==0) continue;
            ans+= (res[i]+'0');
        }
        if( ans=="") return "0";
        return ans;
    }
};
//time: O(m*n)
//space: O(m+n)
