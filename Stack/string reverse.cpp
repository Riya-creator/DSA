#include <iostream>
using namespace std;
class stack{
    public:
    char  *a;
    int top=-1, len;
    
    stack(int len) : a(new char[len]), len(len){
    }
    void push(){
        if(top<len-1){
            top++;
            cin>>a[top];
        }
    }
    void pop(){
        if(top>-1){
            top--;
        }
    }
    void ttop(){
        if(top>-1){
            cout<<a[top];
        }
    }
    void reverse(){
        top=-1;
        cout<<"enter the string to be reversed";
        for(int i=0; i<len; i++){
            push();
        }
        cout<<"Reversed string is :";
        for(int i=top; i>-1; i--){
            ttop();
            pop();
        }
    }
};
int main()
{
    int len;
    while(1){
        cout<<"\nEnter the Length of the string to reverse";
        cin>>len;
        if(len==0)
            return 0;
        stack s(len);
        s.reverse();
    }
}
