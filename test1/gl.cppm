export module gl;
export {
#include "GLES/gl.h"
#include "GLES3/gl31.h"
#include <GLES3/gl3ext.h>
#include "KHR/khrplatform.h"
using khronos_int8_t = signed char;
using khronos_uint8_t = unsigned char;
using khronos_int16_t = signed short int;
using khronos_uint16_t = unsigned short int;
using khronos_intptr_t = signed long int;
using khronos_uintptr_t = unsigned long int;
using khronos_ssize_t = signed long int;
using khronos_usize_t = unsigned long int;
}