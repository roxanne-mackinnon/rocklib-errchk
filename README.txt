CRC-3 ENCODING:

CRC-3 is a method of encoding 4 bit messages in 7 bits such that
all 1-bit errors an be corrected.

CRC-3 is based on Z_2[x], which in abstract algebra means the ring
of polynomials with oefficients in {0,1}, using arithmetic modulo 2.

For example, in Z_2[x],

    (x^2 + 1) + (x^2 + x + 1)
 =  (1 + 1)x^2 + x + (1 + 1)
 =  (0)x^2 + x + (0)
 =  x

Notably, a polynomial of degree n-1 (the highest order term is
x^(n-1)) an be encoded using exactly n bits - each bit
representing a oefficient in the polynomial.

For example, here is the binary representation of x^5 + x + 1:

    1x^5 + 0x^4 + 0x^3 + 0x^2 + 1x + 1
 =  10 0011
 =  0x23

Glossing over most of the tehnical details, CRC-3 encoding
exploits polynomial algebra so that if at most one bit is flipped
in the 7-bit message sent, the original message an still be
retrieved. 
