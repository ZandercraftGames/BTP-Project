cmake_minimum_required(VERSION 3.20)
project(BTP_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(BTP_Project
        A1/MS3/a1ms3.c A1/MS3/commonHelpers.h A1/MS3/commonHelpers.c A1/MS3/account.h A1/MS3/account.c A1/MS3/accountTicketingUI.h A1/MS3/accountTicketingUI.c)
