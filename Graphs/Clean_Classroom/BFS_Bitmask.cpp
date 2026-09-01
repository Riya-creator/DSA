class Solution {
    //shortest Path+ path cost all 1+ State Space ===== BFS
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m= classroom.size(), n =classroom[0].size();

        //id[i][j]= bit number assigned to litter at (i,j)
        vector<vector<int>>id(m, vector<int>(n, -1));

        int sr= 0, sc =0, litterCount = 0;

        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                if (classroom[i][j] == 'S'){
                    sr = i;
                    sc = j;
                }
                else if (classroom[i][j] == 'L'){
                    id[i][j] = litterCount++;
                }
            }
        }
        if (litterCount == 0)
            return 0;

        /*
            mask:
            1 = litter still needs to be collected
            0 = litter already collected
        */
        int startMask= (1<<litterCount)-1;

        /*
            visited[r][c][energy][mask]
        */
        vector<vector<vector<vector<bool>>>> visited(m,vector<vector<vector<bool>>>(n, vector<vector<bool>>(energy + 1,vector<bool>(1 << litterCount, false))));

        queue<tuple<int ,int,int, int>>q;

        q.push({sr, sc, energy, startMask});
        visited[sr][sc][energy][startMask] = true;

        int dist = 0, dr[] = {-1, 1, 0, 0}, dc[] = {0, 0, -1, 1};

        while (!q.empty()) {
            int sz = q.size();

            // All states currently in q are at the same distance.
            while (sz--) {
                auto [r, c, curEnergy, mask] = q.front();
                q.pop();
                if (mask == 0)
                    return dist;
                if (curEnergy == 0)
                    continue;

                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];

                    if (nr<0 ||nr>=m||nc< 0||nc >=n)
                        continue;
                    if (classroom[nr][nc]=='X')
                        continue;

                    int nextEnergy;

                    if (classroom[nr][nc]=='R')
                        nextEnergy= energy;
                    else
                        nextEnergy =curEnergy-1;

                    int nextMask =mask;

                    if(classroom[nr][nc]=='L'){
                        nextMask &= ~(1<<id[nr][nc]);
                    }

                    // Already visited this exact state
                    if(visited[nr][nc][nextEnergy][nextMask])
                        continue;

                    visited[nr][nc][nextEnergy][nextMask] = true;
                    q.push({nr,nc,nextEnergy,nextMask});
                }
            }
            dist++;
        }
        return -1;
    }
};
