#include <iostream>
using namespace std;
class stack {
    int len, top=-1 ;
    char *a;
    public:
    stack(int n){
        len =n;
        a= new char [n];
    }
    void push( char n){
        if(top>=len){
            cout<<"stack overflowed";
            return;
        }
        else {
            top++;
            a[top]= n;
        }
    }
    char ttop(){
        return a[top];
    }
    void pop(){
        if( top>=0){
            top--;
        }
        else cout<<"stack is already empty\n";
    }
    bool empty(){
        if(top==-1)
        return true;
        else return false;
    }
};
    bool isValid(char * s, int n) {
        stack o(n);
        for(int i=0; i<n; i++){
            char ch= s[i];
            if(ch== '[' || ch=='{'|| ch=='('){
                o.push(ch);
            }
            else {
                if(o.empty())
                    return false;
                char c= o.ttop();
                if((c== '['&& s[i]== ']')||(c=='{'&& s[i]=='}')|| (c=='('&& s[i]== ')'))
                    o.pop();
                else return false;
            }
        }
        if( o.empty())
            return true;
            else return false;
    }
int main()
{
    int n;
    cout<<"Enter the length of expression of the string";
    cin>>n;
    char a[n];
    for( int i=0; i<n; i++){
        cin>>a[i];
    }
    cout<<"is valid test "<<isValid(a,n);
}
