cmake_minimum_required(VERSION 3.20)
project(BTP_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(BTP_Project
        A2/MS3/a2ms3.c A2/MS3/commonHelpers.h A2/MS3/commonHelpers.c A2/MS3/account.h A2/MS3/account.c
        A2/MS3/accountTicketingUI.h A2/MS3/accountTicketingUI.c A2/MS3/ticket.h A2/MS3/ticket.c)
