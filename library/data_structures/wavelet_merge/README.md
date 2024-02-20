# Memory analysis

let n = size of input array, k = number of leaves

For merge sort tree: k = n, for wavelet tree: k = (maxv - minv)

depth | total memory for depth | big-O | explanation
--- | --- | --- | ---
0 | $\lceil n / 64 \rceil$ | 1 + n/64 |
1 | 2 * $\lceil (n/2) / 64 \rceil$ | 2 + n/64 |
2 | 4 * $\lceil (n/4) / 64 \rceil$ | 4 + n/64 |
...
i | 2^i * $\lceil (n/2^i) / 64 \rceil$ | 2^i + n/64 |
...
log(k)-j | k/(2^j) * $\lceil (n/(k/(2^j))) / 64 \rceil$ |k/(2^j) + n/64 |
...
log(k)-2 | k/4 * $\lceil (n/(k/4)) / 64 \rceil$ | k/4 + n/64 |
log(k)-1 | k/2 * $\lceil (n/(k/2)) / 64 \rceil$ | k/2 + n/64 |
log(k) | k * $\lceil (n/k) / 64 \rceil$ | k + n/64 | <ul><li>if (n/k)>=64 then we can effectively drop the ceil, cancel the k's, leaving n/64 </li><li>if (n/k)<=64 then we have k * ceil(something <= 1) = k * 1</li><li>O(max(f(x), g(x))) = O(f(x) + g(x))</li><li>note, using (n/k) implies each leaf's array has the same size which isn't the case for wavelet tree, so this is a bit handwavy</li></ul>

Sum of big-O = total number of `uint64_t`'s used:
- first part: 1 + 2 + 4 + ... + 2^i + ... + k <= 2*k: at least one `uint64_t` for each node in wavelet tree
- second part: log(k) * n / 64: each of the n values in the input array appear in log(k) `bool_presum`'s as a single bit

= O(k + n * log(k) / 64)

My understanding of wavelet matrix is it has memory = O(n * log(k) / 64), and dropping k can be a big deal, cuz it allows trees with 1e9 leaves
