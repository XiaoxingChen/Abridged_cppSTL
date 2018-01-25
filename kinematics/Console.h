#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <stdio.h>
namespace Console
{
#define Instance()->printf(fmt, args...) printf(fmt, ##args)
}


#endif // !_CONSOLE_H_
