cmake_minimum_required(VERSION 3.20)
project(BTP_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(BTP_Project
        A1/MS4/a1ms4.c A1/MS4/commonHelpers.h A1/MS4/commonHelpers.c A1/MS4/account.h A1/MS4/account.c
        A1/MS4/accountTicketingUI.h A1/MS4/accountTicketingUI.c)
