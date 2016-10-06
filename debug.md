Disassembling the object file
```
gobjdump -M intel -D a.out | grep -A22 main.:
```

```
otool -arch x86_64 -tv a.out
```

Running GDB
```
sudo gdb -q a.out
```


Running LLDB
```
# From inside lldb:
settings set target.x86-disassembly-flavor intel

# Show where you are in the source code
f

# Show assembly
disassemble --flavor=intel

# Show all thread registers
register read

# Show variables in scope
frame variable

# Dump of assembler code for function main()
# Useful when we're not actively running the debugger
disassemble --flavor=intel --name=main

# Set break point on specific line of file
breakpoint set --file a.out --line 12

breakpoint set --name=main

# Show source code for `main` method
_regexp-list main
l main
```


### Examine registers

The examine command (x) expects two arguments:

(1) the location in memory to examine
(2) and how to display that memory

```
# Display format options
o = octal
x = hexidecimal
u = unsigned, standard base 10
t = binary

# Change the size of the display units
b = a single byte
h = a halfword, which is two bytes in size
w = a word, which is four bytes in size
g = a giant, which is eight bytes in size


# Here we see the rax register contains a pointer
# to an array of chars:

rax = 0x0000000100000e62  "The `int` datatype is \t\t %lu bytes\n"

# We see the byte stored at that memory address
x/t 0x0000000100000e62 => 0b01010100   # binary
x/o 0x0000000100000e62 => 0124         # octal
x/b 0x0000000100000e62 => 0x54         # hex
x/u 0x0000000100000e62 => 84           # base-10

`84` is the character code for the uppercase letter `T`.

```Ruby
84.chr == 'T'
```


ATTENTION: MacOSX is an x86_64 architecture. The achitecture the hacking book uses is x86. Make sure
you take this into account when trying to follow the examples in the book.

For example, the size of a pointer on an x86 architecture is 4 bytes. But the size of a pointer on x86_64 is 8 bytes.

The book might want you to examine memory like this:

x/3xw <address>

But you would need to use x/3xg <address> because the g modifier is 8 bytes.


# How would we examine an array of strings in LLDB?

Given a multi-demensional array of characters
```
(char *[5]) = (
  [0] = "Alan", 
  [1] = "Frank", 
  [2] = "Mary", 
  [3] = "John", 
  [4] = "Lisa"
)
```

We can get the start of the array by examining its hexidecimal representation:

```
x/b *names
``` 

The return value of this is `0x100000f64: 65` which is the location in memory
of the first character in the first string of the first element of the names
array `names[0][0]`.

We can also use `x/s *names` to return the entire string printed out to the
debugger console.

We can also read the entire block of memory with `memory read *names`

#### What would we see if we read an array of integers?

Given an array of integers 
```
(int [5]) = (
  [0] = 23, 
  [1] = 43, 
  [2] = 12, 
  [3] = 89, 
  [4] = 2
)
```

By typing `p &ages` we can learn that the location in memory 
of `ages[]` is `0x00007fff5fbff6c0`.

We can print out the memory using the command `memory read 0x00007fff5fbff6c0` 
and we'll get an output that looks like this:

```
0x7fff5fbff6c0: 17 00 00 00 2b 00 00 00 0c 00 00 00 59 00 00 00
0x7fff5fbff6d0: 02 00 00 00 00 00 00 00 55 7d 55 2b 57 d9 00 00
```

An easier way to get the same output is `memory read &ages` or `x &ages`.

There are two things we need to keep in mind here. First is that we're seeing 
memory represented in hexidecimal format. The second thing to remember is that 
on OSX the size of an integer is 4 bytes.

Based on that we can actually see the integer values in memory:

`00 00 00 17` is the number 23.
`00 00 00 2b` is the number 43.
`00 00 00 0c` is the number 12.
`00 00 00 59` is the number 89.
`00 00 00 02` is the number 2.


# What's the deal with the `po` command?

Check this out:

The command `po names` returns:

```

(
  [0] = "Alan", 
  [1] = "Frank", 
  [2] = "Mary", 
  [3] = "John", 
  [4] = "Lisa"
)
```

The command `po *names` returns:

```
"Alan
```

The command `po **names` returns:
```
'A'
```

The command `po ages` returns:
```
(
  [0] = 23, 
  [1] = 43, 
  [2] = 12, 
  [3] = 89, 
  [4] = 2
)
```

The command `po *ages` returns:
```
23
```

The command `po **ages` returns:
```
error: indirection requires pointer operand ('int' invalid)
error: 1 errors parsing expression
```


#### What does it look like to examine a struct in memory?

Here's a struct called Person:

```
struct Person {
  char *name;
  int age;
  int height;
  int weight;
}
```
Assume we've allocated some memory for a Person struct and assigned it to
a pointer called `joe`.

If we examine `joe` with `memory read joe` this is what we find:

```
0x100103b40: 60 3b 10 00 01 00 00 00 20 00 00 00 3f 00 00 00  `;...... ...?...
0x100103b50: 8c 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00  ................
```

The memory address of `joe` is `0x100103b40`. From there we see that the 
next 8 bytes are `60 3b 10 00 01 00 00 00`. What are these?

Remember when we defined the Person struct we place the `name` element in
first position. We also know that the size of a pointer is 8 bytes. So
these 8 bytes are the memory address of the `name` element.

We can confirm that by taking the reverse of these 8 bytes and examining 
them in memory. First let's find the reverse:

```
60 3b 10 00 01 00 00 00
00 00 00 01 00 10 3b 60
```

Now when we read from memory using `memory read 0x0000000100103b60` we get:

```
0x100103b60: 4a 6f 65 20 41 6c 65 78 00 00 00 00 00 00 00 00  Joe Alex........
0x100103b70: 90 3b 10 00 01 00 00 00 14 00 00 00 48 00 00 00  .;..........H...
```

We could have achieved the same result using `memory read joe->name`.

The remaining 3 bytes we see in memory correspond to the `age`, `height`, and
`width` elements of the struct.

For example, if we want to confirm `20 00 00 00` is the age we set when we
created the struct, run `po &joe->age` to get the address of `age`. 


