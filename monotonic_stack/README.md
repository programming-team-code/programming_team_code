`vi l = mono_st(a, less());`

![](mono_stack_le.png)

`vi r = mono_range(l);`

![](mono_stack_ri.png)

For cartesian binary tree, the invariant is on the `i`-th iteration, the
cartesian tree is built for the `i`-th prefix. Then the inner `j` loop can be
thought of as looping up the "right spine" of blue nodes:

![](cartesian_binary_tree_before.png)

![](cartesian_binary_tree_after.png)
