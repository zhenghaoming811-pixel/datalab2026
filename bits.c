/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    return !((x ^ y) >> 31) && !(!x ^ !y);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
  int r = 0;
  int shift;

  shift = (v >> 16 > 0) << 4;
  r = r | shift;
  v = v >> shift;

  shift = (v >> 8 > 0) << 3;
  r = r | shift;
  v = v >> shift;

  shift = (v >> 4 > 0) << 2;
  r = r | shift;
  v = v >> shift;

  shift = (v >> 2 > 0) << 1;
  r = r | shift;
  v = v >> shift;

  shift = (v >> 1 > 0);
  r = r | shift;

  return r;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nshift = n << 3;
    int mshift = m << 3;
    int diff = ((x >> nshift) ^ (x >> mshift)) & 0xFF;
    int ndiff = diff << nshift;
    int mdiff = diff << mshift;
    x = x ^ ndiff ^ mdiff;
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
  v = (v >> 16) | (v << 16);
  v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
  v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
  v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
  v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
  return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = ~(((1 << 31) >> n) << 1); 
    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int result = 0;
    int c;

    c = !~(x >> 16);
    result += c << 4;
    x <<= c << 4;

    c = !~(x >> 24);
    result += c << 3;
    x <<= c << 3;

    c = !~(x >> 28);
    result += c << 2;
    x <<= c << 2;

    c = !~(x >> 30);
    result += c << 1;
    x <<= c << 1;

    c = !~(x >> 31);
    result += c;
    x <<= c;

    c = !~(x >> 31);
    result += c;

    return result;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned int sign =  x & 0x80000000; //存符号
    unsigned int absx = x;//备份x顺便取绝对值
    if (x >> 31)
    {
        absx = -absx;
    }
    unsigned int temp = absx;
    if (!absx)
    {
        return 0;
    }
    int exp_true = 0;
    while (temp >>= 1)
    {
        exp_true = exp_true + 1;
    }
    //已得到符号与真实指数（同时也是整数x的最高有效位数exp_true+1），接下来重点判断尾数frac
    int frac;
    if (exp_true <= 23)
    {
        //最简单的情况，尾数位数小于单精度浮点数的23位
        frac = (absx << (23 - exp_true)) & 0x7FFFFF;
    }
    else
    {
        int shift = exp_true - 23;
        frac = (absx + (1 << (shift - 1)) - 1 + ((absx >> shift) & 1)) >> shift;
        if (frac >> 24)
        {
            frac >>= 1;
            exp_true = exp_true + 1;
        }
        frac = frac & 0x7FFFFF;
    }
    return sign | (exp_true + 127) << 23 | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned int exp = (uf >> 23) & 0xFF;
    if (exp == 255)
    {
        return uf;
    }
    if (exp == 0)
    {
        int sign = uf & 0x80000000;
        return sign | (uf << 1);
    }
    else
    {
        return uf + 0x00800000;
    }
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign = uf2 >> 31;
    int exp = (uf2 >> 20) & 0x7FF;
    
    if (!(exp - 0x7FF))
    {
        return 0x80000000;
    }
    if (!exp)
    {
        return 0;
    }
    int e = exp - 1023;
    if (e < 0)
    {
        return 0;
    }
    if (e >= 31)
    {
        return 0x80000000;
    }
    int frac_true;
    if (e <= 20)
    {
        frac_true = (uf2 & 0xFFFFF) >> (20 - e);
    }
    else
    {
        frac_true = ((uf2 & 0xFFFFF) << (e - 20)) | (uf1 >> (52 - e));
    }
    
    int result = (1 << e) + frac_true;
    if (sign)
    {
        result = -result;
    }
    return result;
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
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149)
    {
        return 0;
    }
    if (x >= 128)
    {
        return 0x7F800000;
    }
    if (x >= -126)
    {
        return (x + 127) << 23;
    }
    else
    {
        return 0x1 << (x + 149);
    }
}
