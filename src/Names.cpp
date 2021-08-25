/*

This file is part of STEMI hexapod library.

Copyright (C) 2017 STEMI d.o.o.
Authors: Luka Fucek, et al.
Contact: info@stemi.education
Web: https://www.stemi.education/

STEMI hexapod library is free software exclusively
for non-commercial activities.

In case of developing any comercial activities involving STEMI
hexapod library please contact stemi.education for providing custom
license at: info@stemi.education.

For non-commercial activities you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

STEMI hexapod library is
distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with STEMI hexapod library.
If not, see http://www.gnu.org/licenses/.

For additional information please check http://www.stemi.education.

*/


#include "Names.h"

Names::Names()
{

}

std::string Names::generateName(uint16_t number)
{


	return names[number%NUMBER_OF_NAMES];
}

uint16_t Names::sumStringMemberValues(uint8_t str[6])
{
	uint16_t sum = 0;
	for (unsigned i = 0; i<6; ++i)
	{
		sum += str[i];
	}
	return sum;
}

void Names::storeInit()
{
	preferences.begin("my-app", false);
}

void Names::store(std::string name)
{
	preferences.putString("hexName", name.c_str());
}

void Names::load(std::string *name)
{
	*name = preferences.getString("hexName", "\0").c_str();
}

