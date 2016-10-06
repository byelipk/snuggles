# What's going on with memory alignment?

This analysis is based off of `alignment.c`.

We already established that our program is using the stack. But we'll go
over it again for the sake of completeness.

Take the following main function as an example:

```
int main(int argc, char *argv[])
{
  char *p = "Hello";
  char c  = 'h';
  int  x  = 1;

  return 0;
}
```

We've defined and initialized 3 variables. If we look at how these variables
are stored in memory we will see that `p` has the highest address and `x`
has the lowest. 

```
Address of `p` is 0x7fff5fbff6c8
Address of `c` is 0x7fff5fbff6c7
Address of `x` is 0x7fff5fbff6c0
```

But let's dig a little deeper and take a look at how bytes are allocated in
memory to drive home what the stack is doing. 

Run the command `memory read &p`:

```
0x7fff5fbff6c8: 52 0f 00 00 01 00 00 00 00 f7 bf 5f ff 7f 00 00 R........??_?...
0x7fff5fbff6d8: 01 00 00 00 00 00 00 00 f0 f6 bf 5f ff 7f 00 00 ........???_?...
```

*If we count 8 bytes and respect the little-endian byte storage scheme we'll
have the memory address for the first char of our string. We can examine 
that memory address with `memory read 0x0000000100000f52`.*

Notice that after examining the memory location of `p` we didn't see the 
hex representation of the letter 'h' which is `0x68`. That's because since
we're working on the stack we have to remember that address shrink as more
data is added to the stack.

Run `memory read &c` to see `0x68` in memory:

```
0x7fff5fbff6c7: 68 52 0f 00 00 01 00 00 00 00 f7 bf 5f ff 7f 00 hR........??_?..
0x7fff5fbff6d7: 00 01 00 00 00 00 00 00 00 f0 f6 bf 5f ff 7f 00 .........???_?..
```

Boom! There's our `char c` in first position with a value of `0x68`. It is 
sitting right beside the memory location pointed to by `p`.

We can do the same thing to find our `int x`.


After running `memory read &x` we see:

```
0x7fff5fbff6c0: 01 00 00 00 00 00 00 68 52 0f 00 00 01 00 00 00 .......hR.......
0x7fff5fbff6d0: 00 f7 bf 5f ff 7f 00 00 01 00 00 00 00 00 00 00 .??_?...........
```

Now it gets interesting. 

We know the size of `int x` is 4 bytes. So unsuprisingly our integer takes up 
memory addresses `0x7fff5fbff6c0` to `0x7fff5fbff6c3`.

That leaves us with three extra bytes before we hit `0x7fff5fbff6c7` which is
the location of `char c`. 

What is the purpose of these three extra bytes?

The storage for `char *p` starts on a self-aligned 8-byte memory boundary. This
is called *pointer alignment*. 

The storage for `char c` follows immediately. There is, however, a 4 byte
alignment requirement which forces the gap between `char c` and `int x`.








