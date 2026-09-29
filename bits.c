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
    return ~(~x & ~y)&~(x & y);
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
    int sx=x>>31;
    int sy=y>>31;
    return !(sx^sy)&!((!x)^(!y));
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
    int t;
    t = (v > 0xFFFF) << 4;  r = r | t;  v = v >> t;
    t = (v > 0xFF)   << 3;  r = r | t;  v = v >> t;
    t = (v > 0xF)    << 2;  r = r | t;  v = v >> t;
    t = (v > 0x3)    << 1;  r = r | t;  v = v >> t;
    t = (v > 0x1);          r = r | t;
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
    int n8 = n << 3;
    int m8 = m << 3;
    int bn = (x >> n8) & 0xFF;
    int bm = (x >> m8) & 0xFF;
    int mn = 0xFF << n8;
    int mm = 0xFF << m8;
    return (x & ~(mn | mm)) | (bn << m8) | (bm << n8);
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
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    v = (v >> 16) | (v << 16);
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
   return (x >> n) & ~((~0 << (31 + ~n + 1)) << 1);
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
    int v = ~x;
    int r = 0;
    int t;
    t = !(v >> 16);  r = r + (t << 4);  v = v << (t << 4);
    t = !(v >> 24);  r = r + (t << 3);  v = v << (t << 3);
    t = !(v >> 28);  r = r + (t << 2);  v = v << (t << 2);
    t = !(v >> 30);  r = r + (t << 1);  v = v << (t << 1);
    t = !(v >> 31);  r = r + t;
    t = !v;          r = r + t;
    return r;
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
    unsigned m, e, frac, half, rest, sign;
    if (x == 0)
        return 0;
    m = x;
    sign = 0;                        /* 赋值不占符号数 */
    if (x < 0) {
        m = ~m + 1;                  /* 无符号取反加一 = 绝对值，INT_MIN 安全 */
        sign = 0x80000000;
    }
    e = 31;
    while (!(m >> e))
        e = e - 1;
    if (e > 23) {
        frac = (m >> (e - 23)) & 0x7FFFFF;
        half = 1 << (e - 24);
        rest = m & (half + half - 1);
        if (rest > half)
            frac = frac + 1;
        if (rest == half)
            if (frac & 1)
                frac = frac + 1;
    } else {
        frac = (m << (23 - e)) & 0x7FFFFF;
    }
    return sign + ((e + 127) << 23) + frac;
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
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned sign = uf & 0x80000000;
    if (exp == 0xFF) {              /* NaN 或无穷：返回原值 */
        return uf;
    }
    if (exp == 0) {                 /* 非规格化数或 0：尾数左移 */
        return sign | (uf << 1);
    }
    exp = exp + 1;
    if (exp == 0xFF) {              /* 指数溢出：变为无穷 */
        return sign | 0x7F800000;
    }
    return (uf & 0x807FFFFF) | (exp << 23);
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
    int e = (uf2 >> 20) & 0x7FF;
    int sign = uf2 >> 31;
    unsigned mh = (uf2 & 0xFFFFF) | 0x100000;   /* 尾数高20位 + 隐含1 */
    unsigned mag;
    if (e >= 2047) return 0x80000000;           /* NaN / 无穷 */
    if (e < 1023) return 0;                     /* |x| < 1，向零舍入 */
    e = e - 1023;
    if (e > 30) return 0x80000000;              /* 溢出 */
    if (e > 20) {
        mag = (mh << (e - 20)) | (uf1 >> (52 - e));
    } else {
        mag = mh >> (20 - e);
    }
    if (sign) mag = -mag;                       /* 无符号取反即补码，无 UB */
    return mag;
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
        if (x > 127)
        return 0x7F800000;          /* 太大：+INF */
    if (x + 126 >= 0)
        return (x + 127) << 23;     /* 规格化数 */
    if (x + 149 >= 0)
        return 1 << (x + 149);      /* 非规格化数 */
    return 0;   
}
