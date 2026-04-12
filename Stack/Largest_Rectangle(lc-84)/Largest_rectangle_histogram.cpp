//even if the step where there is smaller ahead may cause the best result is covered i.e the part of right expansion :
// as we cover that with the width as stack holds the nearest smaller n if all prev are removed that means they will be some value greater then this value n if smaller than that will still exist there 
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n= heights.size(), ans =0;
        stack<int>s;
        //keeping the index of heights in increasing order
        //but store the nearest left smaler element eventually in the first loop

        for( int i=0; i<n; i++){
            
            while(!s.empty() && heights[s.top()]> heights[i]){
                int h= heights[s.top()];
                //changing the height at every new height po i,e the smaller height is considered 
                s.pop();
                
                int right =i-1;
                int left=s.empty() ? -1: s.top();//in case empty when pop in loop then that is the first index need to be -1 with flow 

                int width= right-left ;
                ans = max(ans, width*h);
            }
            s.push(i);
        }

        //in case there is no smaller height reached n array ends
        while(!s.empty() ){
            int h= heights[s.top()];
            s.pop();

            int right= n-1;//always this as the max height reached to this point only rest all smaller are poped if in bewtween
            int left = s.empty()? -1 : s.top();
            int width = right-left ;
            ans = max(ans, width* h);
        }
        return ans;
    }
};

//time: O(n) amortised as every element is once poped n pushed operations:2n
//space : O(n) 
