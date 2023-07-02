/*alurquiza*/
/*
 problem: https://codeforces.com/gym/103373/problem/F
 Algorithm: Segment Tree with Lazy Propagation
 Costo del Algoritmo:
 - build -> O(N log N)
 - update -> O(log N)
 - query -> O(log N)
 - propagation -> O(1)
*/
#include <bits/stdc++.h>
#define mp make_pair
#define F first
#define S second

using namespace std;
typedef long long LL;

const int SIZE = 2e5 + 3;

bool A[SIZE];

struct node{
	LL aa;
	int ia[2],fa[2];

	node(int _aa = 0,int _a = 0,int _b = 0,int _c = 0,int _d = 0){
		aa = _aa;
		ia[0] = _a;
		ia[1] = _b;
		fa[0] = _c;
		fa[1] = _d;
	}
}a1(1,0,1,0,1),a0(1,1,0,1,0);

struct SegmentTree{
    vector<bool> noprop;
    vector<node> T;

    SegmentTree(int N,bool A[]){
        T.resize(4*N);
        noprop.resize(4*N);

        fill(T.begin(),T.begin() + 2 * N,node());
        fill(noprop.begin(),noprop.begin() + 2 * N,0);

       build(1,1,N,A);
    }

    node une(node a,node b,int lena,int lenb){
		node c = node();

		c.aa = a.aa + b.aa + 1LL * a.fa[1] * b.ia[0] + 1LL * a.fa[0] * b.ia[1];

		c.ia[0] = a.ia[0];
		c.ia[1] = a.ia[1];

		c.fa[0] = b.fa[0];
		c.fa[1] = b.fa[1];

		for(int i = 0;i < 2;i++){
			for(int j = 0;j < 2;j++){
				if(a.ia[i] == lena && a.fa[j] == lena)
					c.ia[i] = lena + b.ia[!j];
			}
		}

		for(int i = 0;i < 2;i++){
			for(int j = 0;j < 2;j++){
				if(b.fa[i] == lenb && b.ia[j] == lenb)
					c.fa[i] = lenb + a.fa[!j];
			}
		}

		return c;
    }

    void build(int nodo,int ini,int fin,bool A[]){
        if(ini == fin){
            T[nodo] = a1;
			if(A[ini] == 0)
				T[nodo] = a0;
            return;
        }

        int mit = (ini + fin) >> 1;

        build(nodo * 2,ini,mit,A);
        build(nodo * 2 + 1,mit + 1,fin,A);

        T[nodo] = une(T[nodo * 2],T[nodo * 2 + 1],mit - ini + 1,fin - mit);
    }

    void propagation(int nodo,int ini,int fin){
        swap(T[nodo].ia[0],T[nodo].ia[1]);
		swap(T[nodo].fa[0],T[nodo].fa[1]);

        if(ini != fin){
            noprop[nodo * 2] = !noprop[nodo * 2];
            noprop[nodo * 2 + 1] = !noprop[nodo * 2 + 1];
        }

        noprop[nodo] = 0;
    }

    void update(int nodo,int ini,int fin,int A,int B){
        if(noprop[nodo])
            propagation(nodo,ini,fin);
        if(ini > B || fin < A)
            return;
        if(A <= ini && fin <= B){
            noprop[nodo] = 1;
            propagation(nodo,ini,fin);
            return;
        }

        int mit = (ini + fin) >> 1;

        update(nodo * 2,ini,mit,A,B);
        update(nodo * 2 + 1,mit + 1,fin,A,B);

        T[nodo] = une(T[nodo * 2],T[nodo * 2 + 1],mit - ini + 1,fin - mit);
    }

    node query(int nodo,int ini,int fin,int A,int B){
        if(ini > B || fin < A)
            return node();
        if(noprop[nodo])
            propagation(nodo,ini,fin);
        if(A <= ini && fin <= B){
            return T[nodo];
		}

        int mit = (ini + fin) >> 1;

		int lena = max(min(B,mit) - max(A,ini) + 1,0);
		int lenb = max(min(B,fin) - max(mit + 1,A) + 1,0);

		node ret = une( query(nodo * 2,ini,mit,A,B),query(nodo * 2 + 1,mit + 1,fin,A,B), lena, lenb);
        return ret;
    }

};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int n,q;
	cin >> n >> q;

	for(int i = 1;i <= n;i++)
		cin >> A[i];

	SegmentTree ST(n,A);

	while(q--){
		int tp,l,r;
		cin >> tp >> l >> r;

		if(tp == 1){ //update
			ST.update(1,1,n,l,r);
		}
		else{ // query
			cout << ST.query(1,1,n,l,r).aa << '\n';
		}
	}

    return 0;
}
// g++ --std=c++11 -Wall A.cpp -o main
// ./main < test
