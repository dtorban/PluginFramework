/* ================================================================================

This file is part of the PluginFramework Open Source Project.

File: extend/PluginInterface.h

Original Author(s) of this File:
	Dan Orban, 2015, University of Minnesota

Author(s) of Significant Updates/Modifications to the File:
	...

-----------------------------------------------------------------------------------
Copyright (c) 2015 Regents of the University of Minnesota
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

* The name of the University of Minnesota, nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
================================================================================ */

#ifndef PLUGININTERFACE_H_
#define PLUGININTERFACE_H_

#include <string>
#include <memory>
#include <iostream>
#include <typeinfo>

namespace PluginFW {

class PluginInterface {
public:
	virtual ~PluginInterface() {}

	virtual std::string getName() = 0;
	virtual const std::type_info& getType() = 0;
	virtual int getMinVersion() = 0;

	template<typename T>
	inline T* getInterface()
	{
		if (getType() != typeid(T))
		{
			return NULL;
		}

		if (this->getMinVersion() > T::getVersion())
		{
			std::cout << "Cannot use plugin for interface " << getName() << " as the minimum version is " << this->getMinVersion() << " but found " << T::getVersion() << std::endl;
			return NULL;
		}

		return dynamic_cast<T*>(this);
	}
};

}

#endif /* PLUGININTERFACE_H_ */
