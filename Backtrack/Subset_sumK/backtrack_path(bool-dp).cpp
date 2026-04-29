void printSubsets(int i, int sum, vector<int>& arr, 
                  vector<vector<bool>>& dp, vector<int>& path) {

    if (sum == 0) {
        for (int x : path) cout << x << " ";
        cout << endl;
        return;
    }

    if (i == 0) return;

    // NOT TAKE
    if (dp[i-1][sum]) {
        printSubsets(i-1, sum, arr, dp, path);
    }

    // TAKE
    if (sum >= arr[i-1] && dp[i-1][sum - arr[i-1]]) {
        path.push_back(arr[i-1]);
        printSubsets(i-1, sum - arr[i-1], arr, dp, path);
        path.pop_back();
    }
}
//oder of the path will be reversed 
//may also casue duplicates in case of duplicates prersent in array
