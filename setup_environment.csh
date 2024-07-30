#!/bin/csh -f

# Define color codes for output
set C_ERR = "\e[1;31m"  # Red
set C_TOP = "\e[1;32m"  # Green
set C_MSG = "\e[1;34m"  # Blue
set C_WRN = "\e[1;35m"  # Magenta
set C_RST = "\e[1;0m"   # Default

setenv PROJECT_DIR ${cwd}

# CAO setup
##################################################
# Create a .ucdprod file with the vsim version
setenv vsim_version "questasim 2023.3"
echo $vsim_version > .ucdprod
echo "${C_MSG}>> CAO Setup${C_RST}"

which setcad > /dev/null
if ($? != 0) then
   echo "${C_WRN}SETCAD DOES NOT WORK: ADD THIS SOURCE IN YOUR ~/.cshrc${C_RST}"
   echo "${C_WRN}     --> source /home/cao/setup/env_cao.csh${C_RST}"
   exit 1
else
   echo "SETCAD OK"
   setcad -b .ucdprod
   if (`which vsim` == "") then
      echo "${C_ERR}ERROR: vsim command does not exist${C_RST}"
      echo "${C_ERR}    Verify your file .ucdprod${C_RST}"
      exit 1
   endif
endif

# Setup required COREV environment variables
#############################################
setenv CV_SIMULATOR vsim
setenv CV_CORE CV32E40S
setenv CV_SW_TOOLCHAIN /home/share/360-Architecture_Conception_Logiciel/360.1-Projets/360.1.521-FIA_in_RTL/mario/corev-openhw-gcc-centos7-20230622
setenv CV_SW_PREFIX riscv32-corev-elf-
setenv CV_SW_CC gcc
setenv CV_SW_MARCH rv32imc_zicsr
#setenv CFLAGS "-Og -g -static -mabi=ilp32 -march=${CV_SW_MARCH} -Wall -Wextra -pedantic -ffreestanding -w -Wl,--gc-sections -nostartfiles -nostdlib -nodefaultlibs -Ibsp" #-fdump-rtl-all
setenv USE_ISS NO
setenv GUI YES