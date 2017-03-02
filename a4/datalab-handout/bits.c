/* 
 * CS:APP Data Lab 
 * 
 * <Phornphawit Manasut, 5780995>
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int x_is_zero, translate;
  x_is_zero =  !!(z ^ (z + x)); //if x == 0, this is 0, otherwise 1 
  translate = (~x_is_zero)+1; 
  return (~(translate)&z) | ((translate)&y);
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  int i = 0x55;
  i = (i << 8) + 0x55;
  i = (i << 8) + 0x55;
  i = (i << 8) + 0x55;
  return !(i ^ (i & x));
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
    return !(x^y) | (!x^0);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int even_bit_mask = 0x55;
  even_bit_mask = (even_bit_mask << 8) + 0x55;
  even_bit_mask = (even_bit_mask << 8) + 0x55;
  even_bit_mask = (even_bit_mask << 8) + 0x55;

  //shift x by one to make all odd bits become even bits then mask with even bit mask
  // printf("x: %x, x>>1: %x, mask: %x,odd_x: %x\n", x, x>>1, even_bit_mask ,(x>>1) & even_bit_mask);
  int odd_x = (even_bit_mask & (x >> 1));
  int even_x = even_bit_mask & x;
  // printf("odd_x: %x, even_x: %x\n", odd_x, even_x);

  int sum = odd_x + even_x;
  // printf("sum: %x\n", sum);

  int output = 0;
  int two_bit_mask = 0x3;

  output = output + (two_bit_mask & (sum));
  output = output + (two_bit_mask & (sum >> 2));
  output = output + (two_bit_mask & (sum >> 4));
  output = output + (two_bit_mask & (sum >> 6));
  output = output + (two_bit_mask & (sum >> 8));
  output = output + (two_bit_mask & (sum >> 10));
  output = output + (two_bit_mask & (sum >> 12));
  output = output + (two_bit_mask & (sum >> 14));
  output = output + (two_bit_mask & (sum >> 16));
  output = output + (two_bit_mask & (sum >> 18));
  output = output + (two_bit_mask & (sum >> 20));
  output = output + (two_bit_mask & (sum >> 22));
  output = output + (two_bit_mask & (sum >> 24));
  output = output + (two_bit_mask & (sum >> 26));
  output = output + (two_bit_mask & (sum >> 28));
  output = output + (two_bit_mask & (sum >> 30));

  return output;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int n, y;
  n = ~x +1;
  y  = (~(x | n)) >> 31;
  return y & 1;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  // printf("input: %x, shift: %d\n", x,n);
  // int output, n_is_zero, mask_out_sign,left,right;

  // n_is_zero = !!(x ^ (x+n));
  // mask_out_sign = ((~n_is_zero) + 1); 

  // left = ((~mask_out_sign)&x);

  // right = (mask_out_sign) & (~(1 << 31));
  // right = right >> (n + (~1 + 1));
  // right = (x >> n) & right;

  // output = left | right;

  int mask, output;
  mask = ~(((1 << 31) >> n) << 1);
  output = x >> n;
  output = output & mask;
  return output;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int n_mask, m_mask, new_x, swapped_x;
  //Get the n_byte area, the rest 0, also shift them to designated place
  n_mask = (255 << (n<<3)) & x;

  //Get the m_byte area, the rest 0, also shift them to designated place
  m_mask = (255 << (m<<3)) & x;
  

  //Empited out the n_byte area and m_byte area
  //So these areas will be 0
  new_x = (x ^ n_mask) ^ m_mask;

  n_mask = (n_mask >> (n<<3)) & 255;
  n_mask = n_mask << (m<<3);

  m_mask = (m_mask >> (m<<3)) & 255;
  m_mask = m_mask << (n<<3);

  //Just add the m_byte and n_byte to fill those area
  swapped_x = new_x | n_mask | m_mask;
  return swapped_x;
}

/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  return (~x+1)&x;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int is_equal = !(x^y);

  int x_most_sig = (x >> 31) & 1;
  int y_most_sig = (y >> 31) & 1;

  int x_negative_y_positive = (x_most_sig & !(y_most_sig));
  int x_positive_y_negative = (!x_most_sig & y_most_sig);

  int diff = (x ^ y);
  int diff_x = x&diff;
  int diff_y = y&diff;
  int total_diff = (diff_x + (~diff_y+1)) >> 31;

  
  return !x_positive_y_negative & (is_equal | x_negative_y_positive | total_diff);
}






