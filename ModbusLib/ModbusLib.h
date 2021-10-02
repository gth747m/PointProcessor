#pragma once

#include <iostream>
#include <stdint.h>
#include <vector>

#ifdef _WIN32
#    define WIN32_LEAN_AND_MEAN
#    include <Windows.h>
#endif

#include "Crc16.h"
#include "FunctionCode.h"
#include "Parameter.h"
#include "Protocol.h"
#include "Request.h"
#include "Response.h"
#include "ValueType.h"