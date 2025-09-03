#include <iostream>
#include <cctype> 
using namespace std;
class stack {
    int len, top = -1;
    int *a;
public:
    stack(int n) {
        len = n;
        a = new int[n];
    }
    void push(char n) {
        if (top >= len - 1) {
            cout << "stack overflowed";
            return;
        }
        a[++top] = n;
    }
    int ttop() {
        if (top >= 0) 
        return a[top];
        return '\0'; 
    }
    void pop() {
        if (top >= 0)
        top--;
        else cout << "stack is already empty\n";
    }
    bool empty() {
        return (top == -1);
    }
};
int eval(char *s, int n) {
    stack o(n);
    for(int i=0; i<n; i++){
        if(isdigit(s[i]))
            o.push(s[i]-'0');
        else {
                int l=o.ttop();
                o.pop();
                int f= o.ttop();
                o.pop();
                switch(s[i]){
                    case '+':
                    o.push(f+l);
                    break;
                    case '-':
                    o.push(f-l);
                    break;
                    case '*':
                    o.push(f*l);
                    break;
                    case '/':
                    o.push(f/l);
                    break;
                    case '^':
                    o.push(f^l);
                    break;
                }
        }
    }
    return o.ttop();
}
int main() {
    int n;
    cout<<"enter the length of the string of expression: ";
    cin>>n;
    char a[n+1];
    cout<<"Enter the expression: ";
    for (int i = 0; i<n;i++) {
        cin>>a[i];
    }
    a[n] = '\0';
    cout<<"Postfix Evaluation is equal to: "<<eval(a, n);
    return 0;
}
