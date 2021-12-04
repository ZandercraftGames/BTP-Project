cmake_minimum_required(VERSION 3.20)
project(BTP_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(BTP_Project
        A2/MS4/a2ms4.c A2/MS4/commonHelpers.h A2/MS4/commonHelpers.c A2/MS4/account.h A2/MS4/account.c
        A2/MS4/accountTicketingUI.h A2/MS4/accountTicketingUI.c A2/MS4/ticket.h A2/MS4/ticket.c)
