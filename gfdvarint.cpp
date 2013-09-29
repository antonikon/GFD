#include "gfdvarint.h"

GFDVarInt::GFDVarInt():
	_intValue(0)
{
	setType(GFD_VAR_TYPE_INT);
}
