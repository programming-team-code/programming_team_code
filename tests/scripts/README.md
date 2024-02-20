https://unix.stackexchange.com/a/169765 explains how to write good bash (bash=functional; c++=procedural). In particular, I've tried to minimize the number of loops in these scripts (like [this](https://github.com/kth-competitive-programming/kactl/blob/main/doc/scripts/compile-all.sh)).

---
Each script should return a non-zero exit code on failure to make CI fail. 

The return code of the script is the return code of the last command. So if some intermediary command fails, I call `exit 1` to exit early, so I usually put:

```
command || exit 1
```

Although `grep`'s return code is non-zero iff no results are found. But I usually grep the code for things I don't want:

```
grep "something bad" && exit 1
```

When grep is the last command in the script, I use `!` to flip the return code:

```
! command | grep .
```
