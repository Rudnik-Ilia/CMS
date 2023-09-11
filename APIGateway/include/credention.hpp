#pragma once

#include <stdlib.h>

enum CREDENTION: u_int8_t
{
    ADMIN = 0b11111111,
    MAIN_MANAGER = 15,
    MANAGER = 20,
    USER = 30
};

enum SET_REQUEST: u_int8_t
{
    TYPE_GET = 1,
    TYPE_POST = 2,
    TYPE_PUT = 4,
    TYPE_DELETE = 8,
    TYPE_GET_WITH_BODY = 129,
    TYPE_POST_WITH_BODY = 130,
    TYPE_PUT_WITH_BODY  = 132,
    TYPE_DELETE_WITH_BODY  = 136
};

enum METHODS: u_int8_t
{
    GET_METHOD = 0,
    POST_METHOD = 1,
    PUT_METHOD = 2,
    DELETE_METHOD = 3
};

enum DEBUG_LEVEL: u_int8_t
{
    INFO = 0,
    WARNING,
    ERROR
};