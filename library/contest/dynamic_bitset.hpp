//! https://codeforces.com/blog/entry/129454
//! https://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/a09090.html
#include <tr2/dynamic_bitset>
using namespace tr2;
void f() {
  dynamic_bitset<> bs(65);
  assert(bs.bits_per_block == 64);
  assert(bs.num_blocks() == 2);
  assert(bs.none());
  bs[1] = bs[3] = 1;
  assert(bs.any());
  assert(bs.count() == 2);
  assert(ssize(bs) == 65);
  bs |= bs & bs;
  assert(
    bs == bs && !(bs != bs) && !(bs < bs) && bs <= bs);
  bs.resize(10);
  bs.push_back(0);
  cerr << bs << endl;
  for (int i = bs.find_first(); i != ssize(bs);
    i = bs.find_next(i))
    cerr << i << endl;
  bs -= bs; // bs &= ~bs;
}
