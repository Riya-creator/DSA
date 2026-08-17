class Solution {
public:
    bool parseBoolExpr(string expression) {
        stack<char> st;

        for ( char ch: expression){
            if( ch==',') continue;
            if( ch != ')'){
                st.push(ch);
                continue;
            }

            bool hasFalse=false, hasTrue = false;

            while(st.top()!='('){
                if( st.top()=='f') hasFalse = true;
                else hasTrue = true;
                st.pop();
            }

            st.pop();
            char result ;
            char op = st.top();
            st.pop();

            if( op=='!') {
                result = (hasTrue) ? 'f':'t';
            }else if( op=='&'){
                result = (hasFalse) ? 'f': 't';
            }else{
                result = (hasTrue) ? 't' :'f';
            }
            st.push(result);
            
        }

        return st.top()=='t';
    }
};
