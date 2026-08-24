class Solution {
public:
    bool sumGame(string num) {
        int l=0, r=0, ql =0, qr=0, n= num.size(), i;

        for( i=0 ;i< n/2; i++){
            if(num[i]== '?') ql++;
            else l+= num[i]-'0';
        }
        for( ;i<n; i++ ){
            if(num[i]== '?') qr++;
            else r+= num[i]-'0';
        }

        if((ql+qr)%2 ==1) return true;//odd== alice final say

        if( l-r == (9*(qr-ql)/2)) return false;
        //bob wining condition all cases covered
        //if existing summ of one side is greater on one side then other side ? must be more n acc the sign is consider
        //alice: make variation in sum: max 9 by one move
        //so per 2 moves bob can counterfiet that so used this formulae
        return true;
    }
};
