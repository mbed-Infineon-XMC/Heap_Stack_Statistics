# Heap Stack Statistics Ecample

Heap and stack overflows are a common problem when developping embedded system sofware with an RTOS.
The following example shows how you can monitor heap and stack size during the runtime of the system.

Add the following compile flags to enable heap and stack statistics to your debug build:<br />
`-DMBED_HEAP_STATS_ENABLED=1 -DMBED_STACK_STATS_ENABLED=1`

NOTE: Connect the default UART to get kernel messages. (Default: TX=P0_5; RX=P0_4 9600 8N1)<br />
Read more about runtime statistics [here.](https://docs.mbed.com/docs/mbed-os-handbook/en/latest/advanced/runtime_stats/)<br /><br />

You can find information about the mbed-os memory model [here.](https://os.mbed.com/docs/v5.7/reference/memory.html)<br /><br />

## Step 1: Download mbed CLI

* [Mbed CLI](https://docs.mbed.com/docs/mbed-os-handbook/en/latest/dev_tools/cli/#installing-mbed-cli) - Download and install mbed CLI.

## Step 2: Import USBSerial-Example project

Import USBSerial-Example project from GitHub.

```
mbed import https://github.com/mbed-Infineon-XMC/USBSerial-Example.git
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
mbed compile -m XMC_4500_RELAX_KIT -t GCC_ARM
```
mbed creates a BUID directory where you can find the executables (bin, elf, hex ...).

## Step 6: Flash to board

* [Segger JLink](https://www.segger.com/downloads/jlink) - Install the JLink software for your platform.
* Navigate to the BUILD directory and execute the following JLinkExe commands.
```
$ JLinkExe
J-LINK> device xmc4500-1024
J-LINK> h
J-Link> loadfile USBSerial-Example.git.hex
J-Link> r
J-Link> g
```
* Choose SWD, 4000kHz as interface settings!!

