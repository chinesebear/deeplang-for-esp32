/* 
Author: chinesebear
Email: swubear@163.com
Website: http://chinesebear.github.io
Date: 2020/11/10
Description: deep common functions
*/
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "driver/uart.h"
#include "driver/gpio.h"
#include "deep_common.h"

#define LINE_MAX (120)

void deep_printf (const char *format, ...)
{
    char buffer[LINE_MAX] = {0};
	va_list arg;
	va_start(arg, format);
    int len = vsnprintf(buffer, LINE_MAX, format, arg); 
	va_end(arg);
    uart_write_bytes(UART_NUM_0, (const char *) buffer, len);
}