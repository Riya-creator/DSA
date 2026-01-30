class Solution {
  public:
    int minPlatform(vector<int>& arr, vector<int>& dep) {
        sort(arr.begin() ,arr.end());
        sort(dep.begin(), dep.end());
        int platform=0, maxplatform=0,i=0,j=0;
        while( i<arr.size() && j<dep.size() ){
            if(arr[i]>dep[j]){
                platform--;
                j++;
            }else{
                platform++;
                i++;
            }
            maxplatform=max(platform, maxplatform);
        }
        return maxplatform;
    }
};
