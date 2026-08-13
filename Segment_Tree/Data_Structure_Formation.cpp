#include<bits/stdc++.h>
using namespace std;
//update n query: fast O(logn) 
struct node{
    
    node * left, *right;
    int value ; 
    
    node(int value){
        left= NULL;
        right = NULL;
        this->value = value;
    }
    
    node (int value, node * left,  node * right){
        this->value = value;
        this->left= left;
        this->right = right;
    }
};

class SegmentTree{
    
    public:
    node * root;
    
    SegmentTree(){
        root = NULL;
    }
    
//no inserting as it is building it in once
    node * build(int (&a)[10], int l, int r){
//pass by refernece when we know  the array size else { int arr[] } here no size known n also need to track the size elsewhere 
        
        if(l==r) {
            node * leaf = new node (a[l]);
            return leaf;
        }
        int mid = l+ (r-l )/2;
        
        node * left = build(a, l, mid), *right = build(a, mid+1, r);
        
        return  new node ( left->value + right->value, left, right);
        
    }
    
    int sum(int l, int r, int ql, int qr, node *cur){
        
        if(ql<= l && qr>=r)  return cur->value;
        if(qr< l || ql>r ) return 0;
        
        int mid = l+ (r-l)/2;
        
        return sum( l, mid, ql,qr, cur->left) + sum( mid+1, r, ql, qr, cur->right);
    }
    
    void update(int index, int val, int l, int r, node *cur) {

    if(l == r) {
        cur->value = val;
        return;
    }

    int mid = l + (r - l) / 2;

    if(index <= mid)
        update(index, val, l, mid, cur->left);
    else
        update(index, val, mid + 1, r, cur->right);

    cur->value = cur->left->value + cur->right->value;// apply the tru tree aproach 
}

//this is my appraoch but not the fundamental one
    // int update(int index, int val, int l, int r, node * cur){
    //     if(l==r ){
    //         int ret =  val - cur->value;
    //         cur->value =  val;
    //         return ret;
    //     } 
    //     int mid = l+ (r-l)/2, got =0;
    //     if(index>mid)
    //         got = update(index, val, mid+1, r, cur->right);
    //     else got = update(index, val, l, mid, cur->left);
        
    //     cur->value += got;
    //     return got;
    // }
};

int main(){
    int a[] = {1, 2 ,3, 4, 5, 6 ,7 , 8, 9, 10};
    SegmentTree st;
    st.root = st.build(a,0, 9);
    cout<<"Sum of index 2 to 5 is : "<<st.sum(0, 9, 2, 5, st.root);
    cout<<"\nUpdate the index at 4 to 10";
    st.update(4 ,10,0,9, st.root);
    cout<<"\n ans after updation: "<<st.sum(0, 9, 2, 5, st.root);
}
