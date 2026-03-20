class Solution {
public:
//2 pointer appproach
//time:O(n)
//space: O(1)
    int trap(vector<int>& height) {
        int leftmax= height[0], rightmax= height[height.size()-1], right= height.size()-1, left=0, water=0;
        while( left<right){
            if( height[right]> height[left]){
                
                if( height[left]>leftmax){
                    leftmax= height[left];
                }else{
                    water+=leftmax- height[left];
                }
                left++;
            }else{
                if(height[right]> rightmax){
                    rightmax= height[right];
                }else{
                    water += rightmax -height[right];
                }
                right--;
            }
        }   
        return water;     
    }
};
