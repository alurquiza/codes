//1208D
#include <bits/stdc++.h>

using namespace::std;

struct ABI{
    vector<long long> T;
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

    long long query(int pos){
        long long r = 0;
        for(;pos > 0;pos -= (pos & -pos))
            r += T[pos];
        return r;
    }

    long long query(int i,int f){
        return query(f) - query(i - 1);
    }

	long long binaryLifting(long long q){
		int num = 0;
		long long sum = 0;

		for(int i = log2(_SIZE) + 1;i >= 0;i--){
			if(num + (1 << i) < _SIZE && sum + T[num + (1 << i)] <= q){
				sum += T[num + (1 << i)];
				num += 1 << i;
			}
		}

		return num + 1;
	}

};

int main(){

	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	//freopen(".in","r",stdin);

	int N;
	cin >> N;

	ABI A(N);

	std::vector<long long> S(N);
	for(int i = 1;i <= N;i++){
		cin >> S[i - 1];
		A.update(i,i);
	}

	std::vector<int> sol(N);
	for(int i = N;i >= 1;i--){

		sol[i - 1] = A.binaryLifting(S[i - 1]);
		A.update(sol[i - 1],-sol[i - 1]);
	}

	for(int i = 0;i < N;i++)
		cout << sol[i] << ' ';
	cout << '\n';

	return 0;
}
