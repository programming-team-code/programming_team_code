`vector<int> le = mono_st(a, less());`

![](mono_stack_le.png)

`vector<int> ri = mono_range(le);`

![](mono_stack_ri.png)

For cartesian binary tree, if you reverse the direction of the outer `i`-loop,
    then it can be thought of as building the cartesian tree for each suffix.
    Then the inner `j` loop can be thought of as looping up the stack of blue nodes:

![](cartesian_binary_tree_reversed_after.png)

![](cartesian_binary_tree_reversed_before.png)
