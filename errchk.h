#ifndef __ERRCHK_H__
#define __ERRCHK_H__

#include <stdint.h>

// the polynomial: x^3 + x + 1 (1011 in binary)
#define CRC_POLYNOMIAL 0xb

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
uint8_t errchk_encode (uint8_t message);

/**
 * Translate and correct an encoded 7-bit message to a 4-bit message
 *
 * message: a 7-bit message returned from errchk_encode
 *
 * Notes: 
 * Research "Cyclic redundancy check" for technical details.
 */
uint8_t errchk_decode (uint8_t message);

#endif
