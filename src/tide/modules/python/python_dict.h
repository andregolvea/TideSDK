/**
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#ifndef _PYTHON_DICT_H_
#define _PYTHON_DICT_H_

#include "python_module.h"

namespace tide
{
	class KPythonDict : public Object
	{
	public:
		KPythonDict(PyObject *obj);
		virtual ~KPythonDict();

		virtual void Set(const char *name, ValueRef value);
		virtual ValueRef Get(const char *name);
		virtual bool Equals(ObjectRef);
		virtual SharedStringList GetPropertyNames();

		PyObject* ToPython();

	private:
		PyObject *object;
		DISALLOW_EVIL_CONSTRUCTORS(KPythonDict);
	};
}
#endif
