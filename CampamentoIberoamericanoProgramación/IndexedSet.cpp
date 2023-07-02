//AtCoder-abc241_d
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

typedef tree<long long,null_type,less_equal<long long>,rb_tree_tag,
 tree_order_statistics_node_update> indexed_set;

int main()
{
//    freopen(".in","r",stdin);

    indexed_set S;

    S.insert(4);
    S.insert(4);
    S.insert(9);
    S.insert(2);
    S.insert(5);

    for(auto i : S){
        cerr << i << ' ';
    }
    cerr << '\n';

    S.erase(S.find_by_order(S.order_of_key(4)));

    for(auto i : S){
        cerr << i << ' ';
    }
    cerr << '\n';

    // cout << S.order_of_key(4) << '\n';

    // cout << S.size() << '\n';//4

    // cout << *S.find_by_order(2) << '\n';

    // cout << S.order_of_key(9) << '\n';

    // cout << S.order_of_key(8) << '\n';
    // cout << S.order_of_key(10) << '\n';

    return 0;


    int Q;
    cin >> Q;

    while(Q--){
        int tq;
        long long x;
        cin >> tq >> x;

        if(tq == 1){
            S.insert(x);
        }
        else{
            int k;
            cin >> k;

            if(tq == 2){
                int pos = S.order_of_key(x + 1) - 1;

                if(pos + 1 >= k){
                    cout << *S.find_by_order(pos - k + 1) << '\n';
                }
                else{
                    cout << "-1\n";
                }
            }
            else{
                int pos = S.order_of_key(x);

                if(pos + k - 1 < S.size()){
                    cout << *S.find_by_order(pos + k - 1) << '\n';
                }
                else{
                    cout << "-1\n";
                }
            }
        }
    }

    return 0;
}
