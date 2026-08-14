#include <bits/stdc++.h>
using namespace std;

struct node {
    node *left, *right;

    long long value;   
    long long lazy;    // used long long as in lazy updates may pile up greater 
    
    node(long long value) {
        left = NULL;
        right = NULL;

        this->value = value;
        lazy = 0;
    }

    node(long long value, node *left, node *right) {
        this->value = value;

        this->left = left;
        this->right = right;

        lazy = 0;
    }
};


class SegmentTree {
public:
    node *root;

    SegmentTree() {
        root = NULL;
    }

    node *build(int (&a)[10], int l, int r) {
        if(l == r) {
            return new node(a[l]);
        }

        int mid = l + (r - l) / 2;

        node *left = build(a, l, mid);
        node *right = build(a, mid + 1, r);

        return new node(left->value + right->value, left, right );
    }

    void push(node *cur, int l, int r) {
        if(cur->lazy == 0)
            return;

        if(l == r) { //leaf no update ahead
            cur->lazy = 0;
            return;
        }

        int mid = l + (r - l) / 2;

        long long pending = cur->lazy;
        int leftLength = mid - l + 1;

        cur->left->value += pending * leftLength;
        cur->left->lazy += pending;// ADDition as they may be updates piled up

        int rightLength = r - mid;
        cur->right->value += pending * rightLength;
        cur->right->lazy += pending;

        cur->lazy = 0; //work done
    }

    void update( int ql, int qr, long long val, int l, int r, node *cur ) {
        if(qr < l || ql > r)
            return;

        if(ql <= l && r <= qr) {//complete overlap
            int length = r - l + 1;
            cur->value += val * length;
            
            cur->lazy += val;
            return;
        }
        push(cur, l, r); //push in partial case as moving down
        int mid = l + (r - l) / 2;

        update(ql, qr, val, l, mid, cur->left );
        update( ql, qr,val, mid + 1, r, cur->right );

        cur->value = cur->left->value + cur->right->value;
    }

    long long sum(int ql, int qr, int l, int r, node *cur ) {
        if(qr < l || ql > r)
            return 0;

        if(ql <= l && r <= qr)
            return cur->value;
            
        push(cur, l, r);
        int mid = l + (r - l) / 2;

        return sum( ql,qr,l,mid,cur->left) + sum( ql, qr, mid + 1, r,cur->right );
    }
};
