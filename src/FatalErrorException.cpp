/*
 * FatalErrorException.cpp
 *
 *  Created on: 23-Nov-2008
 *      Author: Vile Lasagna
 */

#include "FatalErrorException.h"

FatalErrorException::FatalErrorException(std::string reason)
{
	cause = reason;
}
