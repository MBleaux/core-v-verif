#!/bin/csh -f

set C_ERR = "\e[1;31m" # Red
set C_TOP = "\e[1;32m" # Green
set C_MSG = "\e[1;34m" # Blue
set C_WRN = "\e[1;35m" # Magenta
set C_RST = "\e[1;0m"  # Default

setenv PROJECT_DIR ${cwd}

# CAO setup
##################################################
# Create a ucd file
setenv vsim_version "questasim 2023.3"
echo $vsim_version > .ucdprod
echo $C_MSG">> CAO Setup" $C_RST
which setcad > /dev/null
if ($? == 1) then
   echo $C_WRN"SETCAD DOES NOT WORK: ADD THIS SOURCE IN YOUR ~/.cshrc"$C_RST
   echo $C_WRN"     --> source /home/cao/setup/env_cao.csh"$C_RST
   exit
else
   echo "SETCAD OK"
   setcad -b .ucdprod
  if ( `where vsim` == "" ) then
    echo $C_ERR"ERROR : vsim command does not exist"$C_RST
    echo $C_ERR"    Verify your file .ucdprod"$C_RST
    exit 1;
endif

# Setup required COREV environement variables
#############################################
echo $C_MSG">> Setup COREV environement variables :"$C_RST
# vsim simulator to use for all tools
setenv CV_SIMULATOR vsim
echo "- Simulator : ${CV_SIMULATOR}"
# The core to simulate
setenv CV_CORE CV32E40S
# Value of the specific tag you wish to clone
# setenv CV_CORE_TAG cv32e40s/release
# echo "- Core V to simulate : ${CV_CORE} tag ${CV_CORE_TAG}"
# setenv CV_CORE_BRANCH master
# Points to SW toolchain installation
echo "- Setup CORE-V Tool Chain"
setenv CV_SW_TOOLCHAIN /home/share/360-Architecture_Conception_Logiciel/360.1-Projets/360.1.521-FIA_in_RTL/mario/corev-openhw-gcc-centos7-20230622
# Prefix of the SW toolchain installation
setenv CV_SW_PREFIX riscv32-corev-elf-
# Flags to be used during the compilation
setenv CV_SW_CC gcc
#setenv CV_SW_CFLAGS "-static -ffreestanding -w -Wl,--gc-sections -nostartfiles -nostdlib -nodefaultlibs -Ibsp -march=rv32im_zba1p00_zbb1p00_zbc1p00_zbs1p00_zicsr_zca_zcb_zcmp_zcmt_zifencei -Og -Wall -Wextra"
#setenv CFLAGS ?= -Og -g -static -mabi=ilp32 -march=$(RISCV_MARCH) -Wall -Wextra -pedantic $(RISCV_CFLAGS) -ffreestanding -w -Wl,--gc-sections -nostartfiles -nostdlib -nodefaultlibs -Ibsp #-fdump-rtl-all
# Instructions to be used
#setenv CV_SW_MARCH rv32im_zba1p00_zbb1p00_zbc1p00_zbs1p00_zicsr_zca_zcb_zcmp_zcmt_zifencei # Cela ne marche pas
#setenv CV_SW_MARCH rv32imc_zba1p00_zbb1p00_zbc1p00_zbs1p00_zicsr_zca_zcb_zcmp_zcmt_zifencei # Il y a des conflits entre les instructions zcm* et c
#setenv CV_SW_MARCH rv32imc # Il faut avoir l'extension zicsr
#setenv CV_SW_MARCH rv32imc_zicsr
#setenv CV_SW_MARCH rv32imc_zba1p00_zbb1p00_zbc1p00_zbs1p00_zicsr_zca_zcb_zifencei
#setenv CV_SW_MARCH rv32imc_zba1p00_zbb1p00_zbc1p00_zbs1p00_zicsr_zca_zcb_zcmp_zifencei # Error: Zcm* is not compatible with the `c' extension
setenv CV_SW_MARCH rv32im_zicsr
#setenv CV_SW_MARCH rv32im_zba1p00_zbb1p00_zbc1p00_zbs1p00_zicsr_zca_zcb_zcmp_zifencei

#setenv LIB_UVM_AGENT /home/md278709/share_podman_gre051573/core-v-verif/lib/uvm_agents
#setenv DV_UVMA_RVFI_PATH /home/md278709/share_podman_gre051573/core-v-verif/lib/uvm_agents/uvma_rvfi
#setenv DV_UVMA_RVVI_PATH /home/md278709/share_podman_gre051573/core-v-verif/lib/uvm_agents/uvma_rvvi
#setenv DV_UVMA_RVVI_OVPSIM_PATH /home/md278709/share_podman_gre051573/core-v-verif/lib/uvm_agents/uvma_rvvi_ovpsim