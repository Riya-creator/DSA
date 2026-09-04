class Solution {
public:
//making string is very large so tracing theindex back n where found index returned
    char processStr(string s, long long k) {
        int n= s.size();
        long long cur=0;
        vector<long long>len(n);
        for(int i=0;i<n;i++){
            char c= s[i];
            if( c>='a' && c<='z') cur++;
            else if(c=='*') cur= max(0LL, cur-1);
            else if(c=='#') cur = cur*2;

            len[i] = cur;
        }
        if(cur <=k) return '.';

        for( int i=n-1; i>=0; i--){
            char c = s[i];
            long long prevLen = (i==0 ? 0: len[i-1]);

            if( c>='a' && c<='z'){
                //as 0-based index so prevLen
                if(prevLen==k) return c;
            }else if(c=='#'){
                if(k>=prevLen)
                    k -=prevLen;
            }
            else if(c=='%') k = len[i]-k-1;
            
        }

        return '.';
    }
};
