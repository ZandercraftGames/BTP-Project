cmake_minimum_required(VERSION 3.20)
project(BTP_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(BTP_Project
        A1/MS2/a1ms2.c A1/MS2/commonHelpers.h A1/MS2/commonHelpers.c A1/MS2/account.h)
