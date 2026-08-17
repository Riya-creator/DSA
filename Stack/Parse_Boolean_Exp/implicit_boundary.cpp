class Solution {
//seems similar but mistaken when code
//time n space:O (n)
public:
    bool parseBoolExpr(string exp) {
        stack<char>s;

        for( int i=0; i< exp.size(); i++){
            if(exp[i] == '('  ||exp[i]==',')
                continue;
            if(exp[i]!=')'){
                s.push(exp[i]);
            }else{
                int t=0, f=0;
                while(s.top() == 'f' ||s.top() == 't'){
                    if(s.top()=='f') f++;
                    else t++;
                    s.pop();
                }
                char op = s.top();
                s.pop();

                if(op== '!' ){
                    if( t==1 ) s.push('f');
                    else s.push('t');
                    continue;
                }
                if((op=='|' && t>0) ||(op== '&' && f==0)){
                    s.push('t');
                }else
                    s.push('f');

            }
        }
        return s.top()== 't';
    }
};
