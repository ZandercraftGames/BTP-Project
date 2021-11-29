cmake_minimum_required(VERSION 3.20)
project(BTP_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(BTP_Project
        A2/MS2/a2ms2.c A2/MS2/commonHelpers.h A2/MS2/commonHelpers.c A2/MS2/account.h A2/MS2/account.c
        A2/MS2/accountTicketingUI.h A2/MS2/accountTicketingUI.c A2/MS2/ticket.h)
