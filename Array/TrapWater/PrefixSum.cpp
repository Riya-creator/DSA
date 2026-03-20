class Solution {
public:
    int trap(vector<int>& height) {
        if( height.size()==1 || height.size()== 2) return 0; 
        vector<int>leftmax(height.size(), height[0]), rightmax(height.size(), height[height.size()-1]), water(height.size(), 0);
        for( int i=1; i< height.size(); i++) leftmax[i]= max(leftmax[i-1], height[i]);
        for( int i=height.size()-2; i>-1; i--) rightmax[i]= max(height[i], rightmax[i+1]);

        int ans=0;
        for ( int i=0; i< height.size(); i++){
            water [i]= min(rightmax[i], leftmax[i])- height[i];
            ans+=water[i];
        }
        return ans;
    }
};
//time n space:O(N)
