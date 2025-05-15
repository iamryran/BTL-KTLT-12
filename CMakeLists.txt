cmake_minimum_required(VERSION 3.28)
project(BTL_KTLT C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(BTL_KTLT
        invoice.c
        invoice.h
        main.c
        product.c
        product.h)
