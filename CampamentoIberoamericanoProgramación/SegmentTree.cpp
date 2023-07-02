#include <bits/stdc++.h>

using namespace std;

const int SIZE = 2e5;

int ST[4 * SIZE];

int merge(int a,int b){
    return a + b;
}

void build(int nod,int ini,int fin, vector<int> &V){
    if(ini == fin){
        ST[nod] = V[ini];

        return ;
    }

    int mit = (ini + fin) >> 1;

    build(nod * 2,ini,mit,V);
    build(nod * 2 + 1,mit + 1,fin,V);

    ST[nod] = merge(ST[nod * 2],ST[nod * 2 + 1]);
}

void update(int nod,int ini,int fin,int A,int value){
    if(fin < A || A < ini || fin < ini)
        return ;
    if(A <= ini && fin <= A){
        ST[nod] = value;
        return;
    }

    int mit = (ini + fin) >> 1;

    update(nod * 2,ini,mit,A,value);
    update(nod * 2 + 1,mit + 1,fin,A,value);

    ST[nod] = merge(ST[nod * 2],ST[nod * 2 + 1]);
}

int query(int nod,int ini,int fin,int A,int B){
    if(fin < A || B < ini || fin < ini)
        return 0;
    if(A <= ini && fin <= B){
        return ST[nod];
    }

    int mit = (ini + fin) >> 1;

    return merge(query(nod * 2,ini,mit,A,B),query(nod * 2 + 1,mit + 1,fin,A,B));
}

int32_t main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n,q;
    cin >> n >> q;

    vector<int> V(n + 1);
    for(int i = 1;i <= n;i++){
        cin >> V[i];
    }

    build(1,1,n,V);

    while(q--){
        int tq;
        cin >> tq;

        if(tq == 1){
            int k,u;
            cin >> k >> u;

            update(1,1,n,k,u);
        }
        else{
            int a,b;
            cin >> a >> b;

            cout << query(1,1,n,a,b) << '\n';
        }
    }

    return 0;
}