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
  return ~((~(x & (~y))) & (~((~x) & y))); // 直接推公式，^可以使用~、&和|表示，而|又可以用~和&表示
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int one = 1;
  return (one << 31); // 最小的有符号数，符号位为1，其余都是0

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
  int neg1;
  neg1 = !(~x); // if x == -1, neg1 == 1, else, neg1 == 0
  return !((~(x+1)^x)|neg1); // add 1, flip, xor, becomes 0 if Tmax (or if -1)
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
  int mask = (0xAA << 8) + 0xAA;
  mask = (mask << 16) + mask; // 构造掩码
  return !((x & mask) ^ mask); // &操作将x的奇数位取出，偶数位置0，之后再与掩码异或判断是否满足条件
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1; // 补码取相反数操作：按位取反再加一
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
  int negative = 1 << 31;
  int lessthan = ~(negative | 0x39); // 构造上界，如果超过，则符号位变为1
  int greatthan = (~(0x30) + 1); // 构造下界，如果不足，则符号位变为1

  lessthan = negative & (lessthan + x) >> 31;
  greatthan = negative & (greatthan + x) >> 31;

  return !(lessthan | greatthan); // 判断符号位是否为1
  return 2;
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  x = !!x; // 判断x是否为0，若x=0，则x赋值为0；若x不为0，则x赋值为1
  x = ~x + 1; // 得到x的补码，0的补码还是0，1的补码为-1(二进制序列全1)

  return (x&y)|(~x&z); // 若x为0，则返回z；若x为1，则返回y
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int minusx = ~x + 1; // -x
  int result = y + minusx; // y - x
  int sign = (result >> 31) & 1; // 如果y>=x，则sign等于0，否则等于1
  int xsign = (x >> 31) & 1; // 取出x的符号
  int ysign = (y >> 31) & 1; // 取出y的符号
  int bitXor = xsign ^ ysign; // 判断x和y符号是否一致
  return ((!bitXor)&(!sign)) | ((bitXor&xsign)); // 要么xy同符号并且y>=x，要么xy不同符号并且x<0
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

  return ((x | (~x + 1)) >> 31) + 1;
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
  // 原理：对于正数，从高位到低位，找第一个位是1的（比如是n），再加上符号位，则最少需要n+1个位；
  // 对于负数，从高位到低位，找第一个位是0的（比如是n），则最少需要n位
  int b16, b8, b4, b2, b1, b0; // 表示0~15、16~23、24~27、28~29、30、31的位置处是否含有1，如有，则对其赋值需要的位数
  int sign = x >> 31; // 取符号位
  x = (sign&~x)|(~sign&x); // 如果x为正则不变，x为负则取反，这里是为了统一正负数，我们之后只用找到含有1的位置即可

  b16 = !!(x >> 16) << 4;// 先看高16位是否含有1，若有则表示至少需要16位，所以给b16赋值为16(1 << 4 = 16)
  x =  x >> b16; // 若有1，则原数右移16位，因为上面已经确定是否至少需要16位(针对0~15)；若没有1，则b16为0，x不用移位，继续往下面判断

  b8 = !!(x >> 8) << 3; // 看剩余位的高8位是否含有1，若有则表示至少还需要8位，给b8赋值为8
  x = x >> b8; // 同理...

  b4 = !!(x >> 4) << 2;
  x = x >> b4;

  b2 = !!(x >> 2) << 1;
  x = x >> b2;

  b1 = !!(x >> 1);
  x = x >> b1;
  b0 = x;
  return b16+b8+b4+b2+b1+b0+1; // 最后加上符号位
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
  int exp = (uf&0x7F800000) >> 23; // 取出阶码
  int sign = uf&(1 << 31); // 取符号位
  if (exp == 0) return uf<<1|sign; // 若为非规格数，直接给uf乘以2后加上符号位即可
  if (exp == 255) return uf; // 若为无穷大或者NaN，直接返回自身
  exp = exp + 1; // 若uf乘以2（也就是阶码加1）后变成255，则返回无穷大
  if (exp == 255) return (0x7F800000|sign);
  return (exp << 23)|(uf&0x807FFFFF); // 返回阶码加1后的原符号数
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
  int exp = ((uf&0x7F800000) >> 23) - 127; // 计算出指数
  int sign = uf >> 31; // 取符号位
  int frac = ((uf&0x007FFFFF) | 0x00800000); 
  if (!(uf&0x7FFFFFFF)) return 0; // 若原浮点数为0，则返回0

  if (exp > 31) return 0x80000000; // 若原浮点数指数大于31，返回溢出值
  if (exp < 0) return 0; // 若浮点数小于0，则返回0；

  if (exp > 23) frac = frac << (exp - 23); // 将小数转化为整数
  else frac = frac >> (23 - exp);

  if (!((frac >> 31) ^ sign)) return frac; // 判断是否溢出，若符号位没有变化，则没有溢出，返回正确的值
  else if (frac >> 31) return 0x80000000; // 原数为正值，现在为负值，返回溢出值
  else return ~frac + 1; // 原数为负值，现在为正值，返回相反数
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
  int INF = 0xFF << 23; // 设定一个最大值，也就是阶码位置都为1
  int exp = x + 127; // 计算阶码
  if (exp <= 0) return 0; // 阶码小于等于0，则返回0
  if (exp >= 255) return INF; // 阶码大于等于255，则返回INF
  return exp << 23;
}
