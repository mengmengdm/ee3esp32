# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/fhr/esp/v5.3.1/esp-idf/components/bootloader/subproject"
  "C:/codes/esp32/ex1/blink/build/bootloader"
  "C:/codes/esp32/ex1/blink/build/bootloader-prefix"
  "C:/codes/esp32/ex1/blink/build/bootloader-prefix/tmp"
  "C:/codes/esp32/ex1/blink/build/bootloader-prefix/src/bootloader-stamp"
  "C:/codes/esp32/ex1/blink/build/bootloader-prefix/src"
  "C:/codes/esp32/ex1/blink/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/codes/esp32/ex1/blink/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/codes/esp32/ex1/blink/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
