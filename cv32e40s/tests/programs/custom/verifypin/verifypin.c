/**************************************************************************/
/*                                                                        */
/*  This file is part of FISSC.                                           */
/*                                                                        */
/*  you can redistribute it and/or modify it under the terms of the GNU   */
/*  Lesser General Public License as published by the Free Software       */
/*  Foundation, version 3.0.                                              */
/*                                                                        */
/*  It is distributed in the hope that it will be useful,                 */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/*  GNU Lesser General Public License for more details.                   */
/*                                                                        */
/*  See the GNU Lesser General Public License version 3.0                 */
/*  for more details (enclosed in the file LICENSE).                      */
/*                                                                        */
/**************************************************************************/

/*$
  @name = VerifyPIN_6_HB+FTL+INL+DPTC+DT
  @authors = Lionel Rivière, SERTIF Consortium
  @feature = verifyPIN
  @target = satisfied oracle
  @countermeasure = Hardened booleans, inlined calls, Decrement PTC first, Double test, Fixed time loop
  @difficulties = none
  @purpose = N/A
*/

#include "interface.h"
#include "types.h"
#include <stddef.h>

BOOL verifyPIN_6(void);
//size_t print(const void *ptr, size_t len);
extern BOOL g_authenticated;

int main()
{
    initialize();
    verifyPIN_6();
    //if(g_authenticated == BOOL_TRUE)
    //  print("successful authentication\n", 26);
    //else if(g_authenticated == BOOL_FALSE)
    //  print("failed authentication\n", 22);
    //else 
    //  print("Error\n", 6);
    return 0;
}