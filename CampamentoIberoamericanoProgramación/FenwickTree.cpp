/*alurquiza*/
//830B
#include <bits/stdc++.h>

using namespace std;

struct ABI{
    vector<int> T;
    int _SIZE;

    ABI(int SIZE){
        _SIZE = SIZE;
        T.resize(_SIZE + 1);
        fill(T.begin(),T.end(),0);
    }

    void update(int pos,int value){
        for(;pos <= _SIZE;pos += (pos & -pos))
            T[pos] += value;
    }

    int query(int pos){
        int r = 0;
        for(;pos > 0;pos -= (pos & -pos))
            r += T[pos];
        return r;
    }

    int query(int i,int f){
        return query(f) - query(i - 1);
    }

}A(1e5);

const int SIZE = 1e5 + 1;
vector<int> F[SIZE];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

//    freopen(".in","r",stdin);
//    freopen("F.out","w",stdout);

    int N;
    cin >> N;

    for(int i = 1;i <= N;i++){
        int ent;
        cin >> ent;

        F[ent].push_back(i);
    }

    long long sol = 0;
    int j = 0;
    for(int i = 1;i < SIZE;i++){
        if(F[i].size() == 0)
            continue;

        int it = lower_bound(F[i].begin(),F[i].end(),j) - F[i].begin();

        for(int aux = it;aux < F[i].size();aux++){
            int pos = F[i][aux];
            if(pos < j){
                sol += N - j - A.query(j + 1,N);
                j = 0;
            }

            sol += pos - j - A.query(j + 1,pos);
            A.update(pos,1);
            j = pos;
        }

        for(int aux = 0;aux < it;aux++){
            int pos = F[i][aux];
            if(pos < j){
                sol += N - j - A.query(j + 1,N);
                j = 0;
            }

            sol += pos - j - A.query(j + 1,pos);
            A.update(pos,1);
            j = pos;
        }
    }

    cout << sol << '\n';

    return 0;
}
