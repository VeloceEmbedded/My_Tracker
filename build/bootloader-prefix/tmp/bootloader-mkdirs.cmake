# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Akash/esp/esp-idf/components/bootloader/subproject"
  "D:/My-Project/My_Tracker/Firmware/Code/My_Tracker/build/bootloader"
  "D:/My-Project/My_Tracker/Firmware/Code/My_Tracker/build/bootloader-prefix"
  "D:/My-Project/My_Tracker/Firmware/Code/My_Tracker/build/bootloader-prefix/tmp"
  "D:/My-Project/My_Tracker/Firmware/Code/My_Tracker/build/bootloader-prefix/src/bootloader-stamp"
  "D:/My-Project/My_Tracker/Firmware/Code/My_Tracker/build/bootloader-prefix/src"
  "D:/My-Project/My_Tracker/Firmware/Code/My_Tracker/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/My-Project/My_Tracker/Firmware/Code/My_Tracker/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/My-Project/My_Tracker/Firmware/Code/My_Tracker/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
