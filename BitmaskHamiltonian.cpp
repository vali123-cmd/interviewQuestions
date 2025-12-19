#include <iostream>
#include <vector>

using namespace std;


bool ContainsHamiltonianPath(const vector<vector<int>>& adj)
{
    int N = adj.size();
    if (N == 0) return false;

    int dpSize = 1 << N;
    vector<vector<int>> dp(dpSize, vector<int>(N, 0));

    for (int i = 0; i < N; ++i)
        dp[1 << i][i] = 1;

    for (int mask = 1; mask < dpSize; ++mask)
    {
        for (int i = 0; i < N; ++i)
        {
            if (!((1 << i) & mask))
                continue;

            int prevMask = mask ^ (1 << i);
            if (prevMask == 0) 
                continue;

            for (int j = 0; j < N; ++j)
            {
                if ((prevMask & (1<<j)) && j != i && adj[j][i] && dp[prevMask][j])
                {
                    dp[mask][i] = 1;
                    break;
                }
            }
        }
    }

    int fullMask = (1 << N) - 1;
    for (int i = 0; i < N; ++i)
    {
        if (dp[fullMask][i])
            return true;
    }
    return false;

}


int main()
{
    vector<vector<vector<int>>> tests;
    vector<bool> expected;

    // Test 1: single node -> true
    tests.push_back({ {0} });
    expected.push_back(true);

    // Test 2: simple path 0-1-2 -> true
    tests.push_back({
        {0,1,0},
        {1,0,1},
        {0,1,0}
    });
    expected.push_back(true);

    // Test 3: disconnected (edge 0-1, node 2 isolated) -> false
    tests.push_back({
        {0,1,0},
        {1,0,0},
        {0,0,0}
    });
    expected.push_back(false);

    // Test 4: complete graph of 4 nodes -> true
    tests.push_back(vector<vector<int>>(4, vector<int>(4,1)));
    for (int i = 0; i < 4; ++i) tests.back()[i][i] = 0;
    expected.push_back(true);

    // Test 5: 4-cycle 0-1-2-3-0 -> true
    tests.push_back({
        {0,1,0,1},
        {1,0,1,0},
        {0,1,0,1},
        {1,0,1,0}
    });
    expected.push_back(true);

    for (size_t t = 0; t < tests.size(); ++t)
    {
        bool res = ContainsHamiltonianPath(tests[t]);
        cout << "Test " << (t + 1)
             << ": result=" << (res ? "true" : "false")
             << ", expected=" << (expected[t] ? "true" : "false") << "\n";
    }

    return 0;
}