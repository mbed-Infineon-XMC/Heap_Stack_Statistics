# Heap Stack Statistics Ecample

Heap and stack overflows are a common problem when developping embedded system sofware with an RTOS.
The following example shows how you can monitor heap and stack size during the runtime of the system.

Add the following compile flags to enable heap and stack statistics to your debug build:<br />
`-DMBED_HEAP_STATS_ENABLED=1 -DMBED_STACK_STATS_ENABLED=1`

NOTE: Connect the default UART to get kernel messages. (Default: TX=P0_5; RX=P0_4 9600 8N1)<br />
Read more about runtime statistics [here.](https://docs.mbed.com/docs/mbed-os-handbook/en/latest/advanced/runtime_stats/)<br />

You can find information about the mbed-os memory model [here.](https://os.mbed.com/docs/v5.7/reference/memory.html)<br /><br />

Example Description:
* Stack overflow<br />
Set the following define to simulate an stack overflow:<br />
`#define STACK_ERROR`<br />
Every 4 seconds 500 bytes more are allocated from the task stack memory. Every Task has a default stack size from 4096 byte.
If the task increase this value a kernel error message is printet over the STDIO UART. 
If a runtime error occurs mbed-os enables the Light of Death to let you know that an error has occured.
* Heap overflow<br />
Remove the following define to simulate an heap overflow:<br />
`//#define STACK_ERROR`<br />
In this example every 2 seconds a block of 3000 bytes is allocated from the heap memory. If there is no free heap memory availabe malloc() retuns a NULL pointer.

## Step 1: Download mbed CLI

* [Mbed CLI](https://docs.mbed.com/docs/mbed-os-handbook/en/latest/dev_tools/cli/#installing-mbed-cli) - Download and install mbed CLI.

## Step 2: Import Heap_Stack_Statistics Example project

Import Heap_Stack_Statistics Example project from GitHub.

```
mbed import https://github.com/mbed-Infineon-XMC/Heap_Stack_Statistics.git
```

## Step 3: Install ARM GCC toolchain

* [GNU ARM toolchain](https://launchpad.net/gcc-arm-embedded) - Download and install the last stable version of the ARM GCC toolchain.
* Open the file "mbed_settings.py" and add the ARM GCC install path.

Example:
```
#GCC_ARM_PATH = "home/bin/arm_gcc_toolchain/gcc-arm-none-eabi-5_4-2016q2/arm-none-eabi/bin"
```

## Step 4: Compile project

Navigate into the project folder and execute the following command:
```
mbed compile -m XMC_4500_RELAX_KIT -t GCC_ARM -DMBED_HEAP_STATS_ENABLED=1 -DMBED_STACK_STATS_ENABLED=1 --profile ${CWD}mbed-os/tools/profiles/debug.json
```
mbed creates a BUID directory where you can find the executables (bin, elf, hex ...).

## Step 6: Flash to board

* [Segger JLink](https://www.segger.com/downloads/jlink) - Install the JLink software for your platform.
* Navigate to the BUILD directory and execute the following JLinkExe commands.
```
$ JLinkExe
J-LINK> device xmc4500-1024
J-LINK> h
J-Link> loadfile Heap_Stack_Statistics.git.hex
J-Link> r
J-Link> g
```
* Choose SWD, 4000kHz as interface settings!!

