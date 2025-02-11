//! @time O(mx log mx)
//! @space O(mx)
vector<int> mobius(100'005);
mobius[1] = 1;
for (int i = 1; i < ssize(mobius); i++)
  for (int j = i + i; j < ssize(mobius); j += i)
    mobius[j] -= mobius[i];
