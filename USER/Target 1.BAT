SET PATH=E:\keil5\ARM\ARMCC\Bin;C:\Program Files\Common Files\Siemens\Automation\Simatic OAM\bin;E:\Python27\;E:\Python27\Scripts;C:\ProgramData\Oracle\Java\javapath;C:\MentorGraphics\9.5PADS\SDD_HOME\common\win32\bin;C:\MentorGraphics\9.5PADS\SDD_HOME\common\win32\lib;C:\MentorGraphics\9.5PADS\MGC_HOME.ixn\bin;C:\MentorGraphics\9.5PADS\MGC_HOME.ixn\lib;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;E:\Git\cmd;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;E:\adtide\bin;E:\adtide\GnuTools\bin;C:\Users\DELL\AppData\Local\Programs\Python\Python36-32\Scripts\;C:\Users\DELL\AppData\Local\Programs\Python\Python36-32\;E:\Microsoft VS Code Insiders\bin;F:\opencv\build\x64\vc14\bin;E:\Python27\Scripts;E:\Python27
SET CPU_TYPE=STM32F103RC
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x007A1200
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\main.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_it.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\system_stm32f10x.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\misc.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_usart.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_tim.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_spi.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_rtc.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_gpio.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_dbgmcu.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\stm32f10x_rcc.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\core_cm3.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmAsm" --Via ".\startup_stm32f10x_hd._ia"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\delay.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\usart.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\led.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\spi.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmCC" --Via ".\time_test.__i"
"E:\keil5\ARM\ARMCC\Bin\ArmLink" --Via ".\qx.lnp"
"E:\keil5\ARM\ARMCC\Bin\fromelf.exe" ".\qx.axf" --i32combined --output ".\qx.hex"
