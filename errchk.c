/**
 * errchk.c - Implementation of routines in errchk.h
 * 
 *  Copyright (C) 2021, Roxanne MacKinnon
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *  <rdm3@williams.edu> Roxanne MacKinnon
 */

#include "errchk.h"

/**
 * Use the result from a polynomial division to find the location of
 * any bit errors.
 *
 * Returns an 8-bit number that is 1 in the position of a bit error,
 * and 0 otherwise.
 *
 * Notes: Limited to at most 1-bit errors. See README for details.
 */
static uint8_t error_bit (uint8_t remainder);

/**
 * Divide divisor by dividend and return the remainder of the
 * polynomial division.
 *
 * Notes: See README for details of polynomial algebra.
 */
static uint8_t poly_rem (uint8_t divisor, uint8_t dividend);

/**
 * Translate a 4-bit message to a 7-bit polynomial representation.
 *
 * message: an 8 bit int containing a message in its lower 4 bits.
 *
 * Notes:
 * If the given message is represnted by the polynomial M(x), then the resulting translation is
 *     (M(x) * x^3) + ((M(x) * x^3) mod D(x))
 * where D(x) = x^3 + x + 1
 * Research "Cyclic redundancy check" for further technical details.
 */
uint8_t errchk_encode
(uint8_t bits)
{
  // translate bits ABCD to ABCD 000
  uint8_t fourbits = bits & 0xf;
  uint8_t divisor = fourbits << 3;

  // divide the polynomial by special polynomial x^3 + x + 1
  // (note: this remainder will always be 3 bits or fewer
  uint8_t remainder = poly_rem(divisor, CRC_POLYNOMIAL);

  // return ABCD XYZ where ABCD is the original message, and XYZ is
  // the 3-bit remainder polynomial
  return divisor | remainder;
}

/**
 * Translate and correct an encoded 7-bit message to a 4-bit message
 *
 * message: a 7-bit message returned from errchk_encode
 *
 * Notes: 
 * Research "Cyclic redundancy check" for technical details.
 */
uint8_t errchk_decode
(uint8_t message)
{
  // mask off the lower 7 bits of the received message
  uint8_t result = message & 127;

  // find the polynomial remainder after dividing by CRC_POLYNOMIAL
  uint8_t remainder = poly_rem(result, CRC_POLYNOMIAL);

  // if remainder is non-zero, then an error must have occurred
  if (remainder) {
    // flip the offending bit
    result = result ^ error_bit(remainder);
  }

  // translate from ABCD XYZ to ABCD by shifting down and masking
  // out upper bits
  return (result >> 3) & 15;
}

static uint8_t
error_bit
(uint8_t remainder)
{
  // there is no good non-mathematical explaination for this code.
  //
  // essentially,for each possible 3-bit remainder, determine which
  // bit needs to be flipped by examining cosets of <x^3 + x + 1>
  switch (remainder) {
  case (1): return 1;
  case (2): return 2;
  case (3): return 8;
  case (4): return 4;
  case (5): return 64;
  case (6): return 16;
  case (7): return 32;
  default: return 0;
  }
}

static uint8_t
poly_rem
(uint8_t divisor, uint8_t polynomial)
{

  // division in Z_2[x] is equivalent to XORING the divisor against
  // the dividend until the upper 4 bits of the 7 bit divisor are 0.
  
  if (divisor & 64) {
    divisor = divisor ^ (polynomial << 3);
  }
  if (divisor & 32) {
    divisor = divisor ^ (polynomial << 2);
  }
  if (divisor & 16) {
    divisor = divisor ^ (polynomial << 1);
  }
  if (divisor & 8) {
    divisor = divisor ^ polynomial;
  }
  return divisor;
}
