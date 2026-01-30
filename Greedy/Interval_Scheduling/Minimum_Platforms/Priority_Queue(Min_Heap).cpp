class Solution {
public:
    int minPlatform(vector<int>& arr, vector<int>& dep) {
        int ans = 0;
        vector<pair<int, int>> v;
        for (int i = 0; i < arr.size(); i++)
            v.push_back({arr[i], dep[i]});
        priority_queue<int, vector<int>, greater<int>> pq;
        sort(v.begin(), v.end());
        for (int i = 0; i < arr.size(); i++) {
            if (pq.empty() || pq.top() >= v[i].first) {
                ans++;
            } else {
                pq.pop();
            }
            pq.push(v[i].second);
        }
        return ans;
    }
};
