/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /*
  ~: filpping bits

  &: AND operation for each digit

  ^: the digit is 1 if x and y is different in that digit

  4: 0b0100; 5: 0b0101. 0b0100^0b0101 = 0b0001

  Exercise: Using bis and bic to build x|y and x^y, where bis(int x,int m) change every bit position where m is 1 to 1 in x and bic(int x,int m) change
            x to 0 in every bit position where m is 1. 

  Solution: 
  1. x|y is trivial. we can achieve it by x|y = bis(x,y).
  2. x^y is difficult. We could first try bic(x,y). what we get is close to the final x^y we want but in those position that x is 0 and y is 1. 
    In this case, bic(x,y) would be 0 rather than 1. Similarly, when we do bic(y,x), the result is same as x^y expect when y is 0 and x is 1, where it should be 1 
    in x^y but it is 0 in bic(y,x). hence, other than the bit positions that one of x,y is 1 and another is 0, bic(x,y) and bic(y,x) is same. In these bit positions, it is 1 in one of them
    and 0 in another. Hence, we can simply do bis(bic(x,y),bic(y,x)). This action would not affect bit positions that these two are same but change all (0,1)/(1,0) positions into 1. 

  IDEA 1: 
  It is similar to what we did in the x^y part of the exercise. 
  (~x)&y: let all the digit that same in x and y to be 0; for those digits that x and y are different, 
          it is 0 if x is 1 it that digit. otherwise, it would be 1. 

  Hence, if we do A = (~x)&y and B = x&(~y), then the final answer C would be 1 in every digit that either be 1 in A or B. 
  Now, The problem is become: how can be gain C from A and B using only A and B?

  for example, if we have A = 0b1100 and B = 0b0001, how can we get C = 0b1101? 

  Apparently, A OR operation is all we need. Now, let's consider how to build up OR by filpping and AND operations?
  In the exercise, we can use bis which is OR directly. In this case,
  what we can do is ~((~A)&(~B)) where only the bit position that are 0 in both A and B would be 1 after filpping+AND. Then it is trivial that after filpping back, all the bit positions that have
  1 in either A or B would be 1. I find it by randomly checking. However, by seeing the chapter 2.1.6, we know that Boolean Algebra is logic operation and you might deduce OR from NOT and AND under
  logic operation transformation.

  IDEA 2:
  we can try to get the 0 mask of 1 mask for x and y. 
  let M = x & y and N = (~x)&(~y). 
  Then, if a digit is 1 in M, it means that both x and y are 1 here. 
  Similarly, if a digit is 1 in N, it means that both x and y are 0 here.


    
  
  */
  int A = (~x)&y;
  int B = x&(~y);
  return ~((~A)&(~B));
}

/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int A = 1;
  A = A << 31;
  return A;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /*
  It is clear that the basic idea for solving this question is that find a transformation such that all integer in [0, 2^32-1] would not be 0 except the maximum two's complement number.
  Now, we are trying to find this transformation.

  We can denote the maximum 2's implement integer as x(0b01111111111111111111111111111111), then:
  IDEA 1:
  use the property that x+1 = 0b10000000000000000000000000000000. Then, flipping x+1+x would be 0. However, 0xffffffff also have this property.
  IDEA 2:
  if we do ~x+x+1, the flipping of x also have this property.


  Hence, let's try to consider, what is the key difference between 0b11111111111111111111111111111111 and x when we do these legit operations?

  */
  // int A = x+1;
  int A = x+(!!(~x));
  int B = ~(A+x);
  // int C = B^x;
  // int test = 0b01111111111111111111111111111111;
  // int test_2 = ~test;
  // printf("this is the value of maximum 2's implement integer: %d\n",test);
  // printf("this is what we get after flipping the maximum one: %d\n",test_2);
  // printf("----------------DEBUG START--------------------\n"); // Debugging section begins
  // printf("this is x:%d\n",x);
  // printf("This is A:%d\n",A);
  // printf("This is B:%d\n",B);
  // // printf("This is C:%d\n",C);
  // printf("----------------DEBUG END--------------------\n");
  return !B;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  /*
  Similar to last question, the key of this one should be the difference between odd bits and even bits.
  (that is, how can we design a transformation such that it only works for all odd bits number)

  */
  int A = 0xaa;
  A = 0xaa+(A<<8);
  A = 0xaa+(A<<8);
  int odd_mask = 0xaa+(A<<8);
  
  return !(~((~odd_mask)|x));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x)+1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */ 
int isAsciiDigit(int x) {
  /*
  9: 0b1001
  The idea should be similar to above: you should desisn sort of transformation such that only 0x30<=x<=0x39 can become 0xFFFFFFFF of 0x00000000 while any else cannot. 
  the difference between this question and pervious one is that: the property underlying the allodd one and the isTmax one are both about the bit position, while the current one are mostly
  about the value.
  (from 0x30 to 0x39, there is no special pattern in the most 4 significant bit positions)
  
  those numbers must have these property: 
  1. the first 28 bits digits would be 0---03 
  2. the first 28 bits digits would still be 0---03 atfer adding 0d6.
  So we might just design some transformation to detect this property.
  0x30 = 0b 000-000 0011 0000
  */
  int A = 3;
  A = A << 4;
  A = ~A;
  int B = A^x;
  int C = x+6;
  int D = A^C;
  // if x is between 0x30 and 0x39, first 28 bits would be all 1 for both B and D right now.
  int E = B&D; 
  E = E >> 4;
  E = E << 4;
  int F = 0b1111;
  int G = E^F;
  return !~G;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int A = !x;// True-0 False-1

  /*
  now we need to design two transformation M and N.
  M: convert 0b0 into 0, convert 0b1 into 0xFFFFFFFF;
  N: convert 0b1 into 0, convert 0b0 into 0xFFFFFFFF;
  */
  
  int M = (~A)+1;
  int N = ~M;
  
  return (N&y) + (M&z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* 
  
  */
  int mask = 1;
  mask = mask << 31;
  mask = ~mask;

  int detect_Tmin = x^mask;
  // if x is Tmin, detect_Tmin would be 0. if x is Tmin, y >= x must be true and the final result would be 1;
  detect_Tmin = ~detect_Tmin;

  int minus_x = ~x+1;

  /*
  if both y and minus_x have different sign, detect_same_sign = 0b1.....1;
  if both y and minus_x have same sign, detect_same_sign = 0b0....0;
  */
  int detect_same_sign = y^minus_x;
  detect_same_sign = detect_same_sign >> 31;

  /*
  when y and minus_x have same sign a.k.a detect_same_sign = 0b0.....0:

  If both y and minus_x are negative which means y must smaller than minus_x, same_sign_condition = ob1....1;
  In this case, the final result should be 0;

  If both y and minus_x are positive which means y must bigger than minus_x, same_sign_condition = ob0....0;
  In this case, the final result should be 1;
  */
  int same_sign_condition = y&minus_x;
  same_sign_condition = same_sign_condition >> 31;

  // we only use y-x when y and minus_x have different sign otherwise there is a risk of overflowing.
  int y_minus_x = y+minus_x;

  /*
  when y>x, sign of y-x is 0;
  */
  int sign_y_minus_x = y_minus_x >> 31;
  int B;
  // printf('this is x:%d',x);
  // printf('this is y:%d',y);
  // printf('this is the result:%d',!((detect_same_sign|same_sign_condition)&((~detect_same_sign)|sign_y_minus_x)&detect_Tmin));
  return !((detect_same_sign|same_sign_condition)&((~detect_same_sign)|sign_y_minus_x)&detect_Tmin);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  return 2;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  return 0;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  return 2;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  return 2;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    return 2;
}
