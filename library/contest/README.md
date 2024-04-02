## Tips and Tricks

If you changed something for debugging, add a `cout << "don't submit" << endl;`
or `assert(0);` at the end of the code

for policy base DS:
```
#include <bits/extc++.h>
```

for -std=c++17
```
#define ssize(x) (int)(x).size()
```

don't use cin for doubles/floats, it's slow, read into string, then convert to double/float
- [C++ tips and tricks](https://codeforces.com/blog/entry/74684)
- invokes RTE (Run Time Error) upon integer overflow
```
#pragma GCC optimize "trapv"
```
- invoke RTE for input error (e.g. reading a int64_t into an int)
```
cin.exceptions(cin.failbit);
```

- use pramgas for C++ speed boost
```
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
```

### Troubleshooting
```
/* stuff you should look for
	* int overflow, array bounds
	* special cases (n=1?)
	* do smth instead of nothing and stay organized
	* WRITE STUFF DOWN
	* DON'T GET STUCK ON ONE APPROACH
*/
```
Author: Benq

- refer to https://github.com/kth-competitive-programming/kactl/ blob/main/content/contest/troubleshoot.txt

## Sources

- [[Tutorial] GCC Optimization Pragmas](https://codeforces.com/blog/entry/96344)
- [Don't use rand(): a guide to random number generators in C++](https://codeforces.com/blog/entry/61587)
- [faster adjacency list](https://codeforces.com/blog/entry/110222)
