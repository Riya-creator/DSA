#include <iostream>
#include <cctype> 
using namespace std;

class stack {
    int len, top = -1;
    char *a;
public:
    stack(int n) {
        len = n;
        a = new char[n];
    }
    void push(char n) {
        if (top >= len - 1) {
            cout << "stack overflowed";
            return;
        }
        a[++top] = n;
    }
    char ttop() {
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
    int pre(char op) {
        switch (op) {
            case '^': return 3;
            case '*': case '/': return 2;
            case '+': case '-': return 1;
            default: return 0;
        }
    }
};

void postfix(char *s, int n) {
    stack o(n);
    int j = 0;
    for (int i=0;i<n;i++) {
        if (isalpha(s[i])) {
            s[j++] = s[i];
        }
        else if (s[i] == '(') {
            o.push(s[i]);
        }
        else if (s[i] == ')') {
            while (!o.empty() && o.ttop() != '(') {
                s[j++] = o.ttop();
                o.pop();
            }
            if (!o.empty()) o.pop(); 
        }
        else {
            while (!o.empty() && o.ttop() != '(' && o.pre(o.ttop()) >= o.pre(s[i])) {
                s[j++] = o.ttop();
                o.pop();
            }
            o.push(s[i]);
        }
    }
    while (!o.empty()) { 
        s[j++] = o.ttop();
        o.pop();
    }
    s[j] = '\0'; 
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
    postfix(a, n);
    cout<<"Postfix: "<<a<<"\n";
    return 0;
}
