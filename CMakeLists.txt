cmake_minimum_required(VERSION 3.20)
project(BTP_Project C)

set(CMAKE_C_STANDARD 11)

add_executable(BTP_Project
        A2/MS1/a2ms1.c A2/MS1/commonHelpers.h A2/MS1/commonHelpers.c A2/MS1/account.h A2/MS1/account.c
        A2/MS1/accountTicketingUI.h A2/MS1/accountTicketingUI.c A2/MS1/ticket.h)
