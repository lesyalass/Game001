#include "String.h"

std::ostream& operator << (std::ostream& streamP , const String& string )
{
	for (int i = 0; i < string.len(); i++)
		streamP << string[i];
	return streamP;
}