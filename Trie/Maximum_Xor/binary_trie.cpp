//time & space: O(32*n) = O(n) 
struct Node{
    Node * child[2];
    Node (){
        child[0] = NULL;
        child[1] = NULL;
    }
};
class BinaryTrie{
    Node * root ;
    public:
    BinaryTrie(){
        root= new Node();
    }

    void insert( int num){
        Node * curr = root;
        // 31 is for sign bit here so can leave that too
        for( int bit=30 ; bit>=0; bit--){
            int b = (num>>bit) &1;
            if(curr->child[b] == NULL ){
                curr->child[b] = new Node();
            }

            curr = curr->child[b];
        }
    }

    int getMax(int x){
        Node * cur = root;
        int ans = 0;
        for(int bit=30; bit>=0; bit--){
            int b= (x>>bit) & 1, opp= 1-b;
            if( cur->child[opp]!= NULL){
                ans |= (1<<bit) ;
                cur  = cur->child[opp];
            }else {
                cur = cur->child[b];
            }
        }
        return ans;
    }
};
class Solution {
public:
    int findMaximumXOR(vector<int>& nums) {
        BinaryTrie bt;
        for( int n: nums){
            bt.insert(n);
        }

        int ans =0;

        for( int n : nums){
            ans = max( ans, bt.getMax(n));
        }
        return ans;
    }
};
//XOR + lots of numbers + need max/min --> binary trie
