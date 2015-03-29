/*
 * FatalErrorException.h
 *
 *  Created on: 23-Nov-2008
 *      Author: Vile Lasagna
 */

#include <String>


#ifndef FATALERROREXCEPTION_H_
#define FATALERROREXCEPTION_H_


class FatalErrorException
{
	/*
	 * If we've got one of THESE then something went so wrong I don't think there's any way the program can
	 * continue anymore. Any exception of this type will cause the generation of a log and termination of
	 * the program. This treatment has to be done in MAIN
	 */
public:
	FatalErrorException(std::string reason = "Unknown");
	/*
	 * I've provided a default constructor but it's more for good practice than anything else.
	 * If an Unknown fatal error exception was thrown it probably means that someone did something
	 * really sloppy when coding and should be beaten on the head with a stick.
	 */
private:
	std::string cause;
};

#endif /* FATALERROREXCEPTION_H_ */
