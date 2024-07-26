// Copyright 2022 Silicon Labs, Inc.
//
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1
//
// Licensed under the Solderpad Hardware License v 2.1 (the "License"); you
// may not use this file except in compliance with the License, or, at your
// option, the Apache License version 2.0.
//
// You may obtain a copy of the License at
// https://solderpad.org/licenses/SHL-2.1/
//
// Unless required by applicable law or agreed to in writing, any work
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//
// See the License for the specific language governing permissions and
// limitations under the License.


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#include "bsp.h"

#define CSRADDR_CPUCTRL     0xBF0
#define CSRADDR_SECURESEED0 0xBF9
#define CSRADDR_SECURESEED1 0xBFA
#define CSRADDR_SECURESEED2 0xBFC

// Macros for using defines in inline asm
#define S(x) #x
#define STR(s) S(s)

static void  test_csr_accesses(void) {
  uint32_t rd;
  uint32_t rs1 = 0xFFFFFFFF;

  //printf("Test cpuctrl\n");

    // Lê o conteúdo inicial do registrador cpuctrl
    __asm__ volatile("csrr %0, " STR(CSRADDR_CPUCTRL) : "=r"(rd));
    //printf("Initial value of cpuctrl: 0x%x\n", rd);

    // Escreve o valor 0x19 no registrador cpuctrl
    //__asm__ volatile("csrwi " STR(CSRADDR_CPUCTRL) ", 0x19");
    __asm__ volatile("csrwi 0xBF0, 0x19");
    // Lê o valor após a escrita
    __asm__ volatile("csrr %0, " STR(CSRADDR_CPUCTRL) : "=r"(rd));
    //printf("Value of cpuctrl after csrwi: 0x%x\n", rd);

    // Define bits específicos no registrador cpuctrl usando rs1
    rs1 = 0x3; // Exemplo: definindo o bit 0 1
    __asm__ volatile("csrrs %0, " STR(CSRADDR_CPUCTRL) ", %1" : "=r"(rd) : "r"(rs1));

    // Lê o valor após definir bits
    __asm__ volatile("csrr %0, " STR(CSRADDR_CPUCTRL) : "=r"(rd));
    //printf("Value of cpuctrl after csrrs: 0x%x\n", rd);

    // Limpa bits específicos no registrador cpuctrl usando rs1
    __asm__ volatile("csrrc %0, " STR(CSRADDR_CPUCTRL) ", %1" : "=r"(rd) : "r"(rs1));

    // Lê o valor final do registrador cpuctrl
    __asm__ volatile("csrr %0, " STR(CSRADDR_CPUCTRL) : "=r"(rd));
    //printf("Final value of cpuctrl after csrrc: 0x%x\n", rd);

}

int main(void) {
  test_csr_accesses();
  //printf("Test 'xsecure_csrs' done\n");
  return EXIT_SUCCESS;
}
