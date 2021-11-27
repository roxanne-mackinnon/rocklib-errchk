/**
 * errchk.h - Error correction routines based on CRC-3
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
