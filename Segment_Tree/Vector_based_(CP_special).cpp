#include <bits/stdc++.h>
using namespace std;
// no pointer overhead as left n right 
// no node creation only a value stored as in vector we store
class SegmentTree{
    vector<int> tree;
    int n;

    void build(vector<int>& a, int node, int l, int r){
        if(l==r){
            tree[node]=a[l];
            return;
        }

        int mid=l+(r-l)/2;
        build(a, 2*node, l, mid);
        build(a, 2*node+1, mid+1, r);

        tree[node]=tree[2*node]+tree[2*node+1];
    }

    int sum(int node, int l, int r, int ql, int qr){
        if(ql<=l && r<=qr) return tree[node];
        if(qr<l || ql>r) return 0;

        int mid=l+(r-l)/2;

        return sum(2*node, l, mid, ql, qr)
             + sum(2*node+1, mid+1, r, ql, qr);
    }

    void update(int index, int val, int node, int l, int r){
        if(l==r){
            tree[node]=val;
            return;
        }

        int mid=l+(r-l)/2;

        if(index<=mid)
            update(index, val, 2*node, l, mid);
        else
            update(index, val, 2*node+1, mid+1, r);

        tree[node]=tree[2*node]+tree[2*node+1];
    }

public:
    SegmentTree(vector<int>& a){
        n=a.size();
        tree.resize(4*n); // 4*n -> safer upper bound for CP no much hard thinking over that
        build(a, 1, 0, n-1);
    }

    int sum(int l, int r){
        return sum(1, 0, n-1, l, r);
    }

    void update(int index, int val){
        update(index, val, 1, 0, n-1);
    }
};

int main(){
    vector<int> a={1,2,3,4,5,6,7,8,9,10};

    SegmentTree st(a);

    cout<<"Sum of index 2 to 5 is: "<<st.sum(2,5)<<endl;

    st.update(3,10);

    cout<<"Sum of index 2 to 5 after update is: "<<st.sum(2,5)<<endl;
}
