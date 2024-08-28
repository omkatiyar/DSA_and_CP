#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define IO ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
#define all(x) x.begin(), (x).end()
#define el '\n'
#define sz(v) (int)(v).size()
#define yes cout << "YES" << el
#define no cout << "NO" << el
#define N (int)1e6 + 4

int n, m;
vector<vector<char>> arr;
map<pair<int, int>, pair<int, int>> parent;
map<pair<int, int>, int> siz;

// Function to create a set with a single pair
void make_set(pair<int, int> v)
{
    parent[v] = v;
    siz[v] = 1;
}

// Function to find the representative of the set containing the pair
pair<int, int> find_set(pair<int, int> v)
{
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

// Function to union two sets represented by pairs
void union_sets(pair<int, int> a, pair<int, int> b)
{
    a = find_set(a);
    b = find_set(b);
    if (a != b)
    {
        if (siz[a] < siz[b])
            swap(a, b);
        parent[b] = a;
        siz[a] += siz[b];
    }
}

void solve()
{
    cin >> n >> m;
    arr.resize(n);
    for (int i = 0; i < n; i++)
    {
        arr[i].resize(m);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; ++j)
        {
            cin >> arr[i][j];
            make_set({i, j});
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; ++j)
        {
            if (i + 1 < n && arr[i][j] == '#' && arr[i + 1][j] == '#')
                union_sets({i, j}, {i + 1, j});
            if (j + 1 < m && arr[i][j] == '#' && arr[i][j + 1] == '#')
                union_sets({i, j}, {i, j + 1});
        }
    ll cnt, ans = 0;
    for (int i = 0; i < n; i++)
    {
        cnt = 0;
        set<pair<int, int>> par;
        // the selected row
        for (int j = 0; j < m; ++j)
        {
            if (arr[i][j] == '.')
            {
                // union i+1
                if (i + 1 < n && arr[i + 1][j] == '#')
                {
                    if (!par.count(find_set({i + 1, j})))
                    {
                        cnt += siz[find_set({i + 1, j})];
                        par.emplace(find_set({i + 1, j}));
                    }
                }
                // union i-1
                if (i - 1 >= 0 && arr[i - 1][j] == '#')
                {
                    if (!par.count(find_set({i - 1, j})))
                    {
                        cnt += siz[find_set({i - 1, j})];
                        par.emplace(find_set({i - 1, j}));
                    }
                }
                cnt++;
            }
            else
            {
                if (!par.count(find_set({i, j})))
                {
                    cnt += siz[find_set({i, j})];
                    par.emplace(find_set({i, j}));
                }
            }
        }
        // cout << cnt << " ";
        ans = max(ans, cnt);
    }
    for (int j = 0; j < m; ++j)
    {
        cnt = 0;
        set<pair<int, int>> par;
        // the selected column
        for (int i = 0; i < n; i++)
        {
            if (arr[i][j] == '.')
            {
                // union j+1
                if (j + 1 < m && arr[i][j + 1] == '#')
                {
                    if (!par.count(find_set({i, j + 1})))
                    {
                        cnt += siz[find_set({i, j + 1})];
                        par.emplace(find_set({i, j + 1}));
                    }
                }
                // union j-1
                if (j - 1 >= 0 && arr[i][j - 1] == '#')
                {
                    if (!par.count(find_set({i, j - 1})))
                    {
                        cnt += siz[find_set({i, j - 1})];
                        par.emplace(find_set({i, j - 1}));
                    }
                }
                cnt++;
            }
            else
            {
                if (!par.count(find_set({i, j})))
                {
                    cnt += siz[find_set({i, j})];
                    par.emplace(find_set({i, j}));
                }
            }
        }
        // cout << cnt << " ";
        ans = max(ans, cnt);
    }
    cout << ans << el;
    parent.clear();
    siz.clear();
}

int main()
{
    IO 
    int tc = 1;
    cin >> tc;
    while (tc--)
        solve();

    return 0;
}

/*
#...#
....#
#...#
.....
...##

*/
