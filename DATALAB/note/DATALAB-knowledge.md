# Covering Chapters of the CSAPP Book

The whole chapter 2: Representing and Manipulating Information, including 2.1 Information Storage, 2.2 Integer Representation, 2.3 Integer Arithmetic and 2.4 Floating Point.

# Related Theory:

#### 1. Two's Complementary Encoding

In Data Lab, we assume that our machine is using 2s complement. It is covered in chapter 2.2.3 of CSAPP.

# Related C grammar

## Bitwise operators

#### 1. ``<<``

**Syntax:** 

```c
x << n // x here is a integer
```

**Usage:** 

See integer ``x`` as a binary, then ``x``  is shifted ``n`` bits to the left, dropping off ``n`` most significant bits (the first ``n`` bits from right end) and filling the right end with ``n`` zeros.

**Example:** 

```c
int x = 3;     // Binary: 0000 0011
int y = x << 2; // Shift left 2 → 0000 1100 (decimal 12)
```

#### 2.  ``~``

**Syntax:** 

```c
~x
```

**Usage:** 

See integer ``x`` as a binary, flip every bit of it. 

**Example:** 

```c
int x = 0;     // 00000000 00000000 00000000 00000000
int y = ~x;    // 11111111 11111111 11111111 11111111 → -1

// In data lab, we assume that the machine uses 2s complement and 32-bit representations of integers. So we use 32-bit representation as examples. 
```

#### 3.  ``&``

**Syntax:** 

```c
a&b
```

**Usage:** 

See ``a``  and ``b``  as binary. ``a&b`` return a new integer (denoted as ``A`` ) such that each digit of ``A``  in binary is 1 if and only if both ``a`` and ``b`` is 1 in that digit.

**Example:** 

```c
int a = 0b0110; // or int a = 6;
int b = 12;    // or int b = 0b1100;
int A = a&b // A = 0b0100 = 4 here
```

