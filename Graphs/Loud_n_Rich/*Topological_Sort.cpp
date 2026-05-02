class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
    //toposort
    int n = quiet.size();
    vector<vector<int>> graph(n);
    vector<int> indegree(n, 0);

    for (auto &r : richer) {
        graph[r[0]].push_back(r[1]); // a -> b
        indegree[r[1]]++;
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) ans[i] = i;

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }

    while (!q.empty()) {
        int node = q.front(); q.pop();

        for (int nei : graph[node]) {
            if (quiet[ans[node]] < quiet[ans[nei]]) {
                ans[nei] = ans[node];
            }

            if (--indegree[nei] == 0) {
                q.push(nei);
            }
        }
    }

    return ans;
}
};
