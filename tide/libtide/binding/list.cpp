/*
 * Appcelerator Kroll - licensed under the Apache Public License 2
 * see LICENSE in the root folder for details on the license.
 * Copyright (c) 2008 Appcelerator, Inc. All Rights Reserved.
 */

#include "../tide.h"
#include <sstream>
#include <cmath>
#include <climits>

namespace tide
{

	void List::ResizeTo(unsigned int size)
	{
		if (size < 0 || size == this->Size())
		{
			return;
		}

		while (size < this->Size())
		{
			this->Remove(this->Size() - 1);
		}

		while (size > this->Size())
		{
			this->Append(Value::Undefined);
		}
	}

	SharedString List::DisplayString(int levels)
	{
		std::ostringstream oss;
		oss << "(" << this->GetType() << ")" << " [";
		for (unsigned int i = 0; i < this->Size(); i++)
		{
			ValueRef list_val = this->At(i);
			SharedString list_str = list_val->DisplayString(levels-1);
			oss << " " << *list_str << ",";
		}
		//int before_last_comma = oss.tellp() - 1;
		//oss.seekp(before_last_comma);
		oss << " ]";

		return new std::string(oss.str());
	}

	/*static*/
	std::string List::IntToChars(unsigned int value)
	{
		std::stringstream ss;
		ss << value;
		return ss.str();
	}

	/*static*/
	bool List::IsInt(const std::string& name)
	{
		for (size_t i = 0; i < strlen(name.c_str()); i++)
		{
			if (!isdigit(name[i]))
				return false;
		}
		return true;
	}

	/*static*/
	unsigned int List::ToIndex(const std::string& str)
	{
		char* endPointer = 0;
		unsigned long result = strtoul(str.c_str(), &endPointer, 10);

		if ((endPointer == str.c_str() && result == 0) || result > UINT_MAX)
		{
			throw ValueException::FromFormat("Could not convert %s to an unsigned int",
				str.c_str());
		}

		return result;
	}

	/*static*/
	ListRef List::Unwrap(ListRef o)
	{
		AutoPtr<ProfiledBoundList> plist = o.cast<ProfiledBoundList>();
		if (plist.isNull())
		{
			return o;
		}
		else
		{
			return plist->GetDelegate();
		}
	}
}
