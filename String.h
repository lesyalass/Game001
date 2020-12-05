#pragma once
#include <cassert>
#include <iostream>

class String
{
	
public:

	String()
	{
		memorySize = 1;
		strSize = 1;
		str = new char[memorySize];
		str[0] = '\0';
	}

	String(const char* strc)
	{
		assert(strc);
		strSize = strLen(strc) + 1;
		memorySize = 2 * strSize;
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = strc[i];
	}

	String(const char* strc, const int memorySizeP)
	{
		assert(strc);
		strSize = strLen(strc) + 1;
		assert(strSize < memorySizeP);
		memorySize = memorySizeP;
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = strc[i];
	}

	String(const String& string)
	{
		strSize = string.strSize;
		memorySize = 2 * strSize;
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = string.str[i];

		//std::cout << "constr1" << '\n';
	}

	String(const String& string, const int memorySizeP)
	{
		memorySize = memorySizeP;
		strSize = string.strSize;
		assert(strSize < memorySize);
		str = new char[memorySize];
		for (int i = 0; i < strSize; ++i)
			str[i] = string.str[i];

		//std::cout << "constr2" << '\n';
	}

	String(const int len)
	{
		strSize = len + 1;
		memorySize = 2 * strSize;
		str = new char[memorySize];
	}

	~String()
	{
		//std::cout << this->str  << '\n';

		delete[] str;

		//std::cout << "destr" << '\n';
	}

	const char operator [] (const int index) const
	{
		assert(index < this->len());        
		return str[index];
	}

	char& operator [] (const int index) 
	{
		assert(index < this->len());
		return str[index];
	}

	bool operator == (String string)
	{
		if (strSize != string.strSize)
			return false;
		for (int i = 0; i < this->len(); i++)
			if (str[i] != string[i])
				return false;
		return true;
	}

	bool operator != (String string)
	{
		if (*this == string)
			return false;
		return true;
	}

	String& operator = (const String& string)
	{
		//std::cout << "=" << '\n';

		int size = string.strSize;
		if (size > memorySize)
		{
			delete[] str;
			str = new char[2 * size];
			memorySize = 2 * size;
		}
		strSize = size;
		for (int i = 0; i < size - 1; i++)
		{
			str[i] = string[i];
		}
		str[size - 1] = '\0';
		return *this;
	}

	int len() const
	{
		return strSize - 1;
	}

	int countChar(char c) const
	{
		int i = 0;
		int count = 0;
		for (int i = 0; i < strSize; ++i)
			if (str[i] == c)
				count++;
		return count;
	}

	int findFirstOf(char c) const
	{
		int i = 0;
		while (str[i] != c)
			i++;
		return i;
	}

	String split(int index)
	{
		String string = String(strSize - index - 2);
		int n = index;
		for (int i = 0; i < strSize - n; ++i)
		{
			string.str[i] = str[i + n];
		}
		strSize = index + 1;
		str[index] = '\0';
		return string;
	}

	String operator + (const String& string) const
	{
		int size = strSize + string.len();
		String retStr (size);
		for (int i = 0; i < strSize - 1; ++i)
			retStr.str[i] = str[i];
		int n = strSize - 1;
		for (int i = 0; i < string.strSize; ++i)
			retStr.str[i + n] = string.str[i];
		return retStr;
	}

	void operator += (const String& string)    
	{
		int size = strSize + string.len();
		if (size > memorySize)
		{
			char* newstr = new char[2 * size];
			memorySize = 2 * size;
			for (int i = 0; i < strSize - 1; ++i)
				newstr[i] = str[i];
			int n = strSize - 1;
			for (int i = 0; i < string.strSize; ++i)
				newstr[i + n] = string.str[i];
			delete[] str;
			str = newstr;
			strSize = size;
		}
		else
		{
			int n = strSize - 1;
			for (int i = 0; i < string.strSize; ++i)
				str[i + n] = string.str[i];
			strSize = size;
		}
	}

	char* c_str()                
	{
		return str;
	}

	bool foundStr(const char* strc)
	{
		assert(strc);

		int len_strc = strLen(strc);
		//std::cout << len_strc << std::endl;
		int* arr = new int[strSize];
		if (str[0] == strc[0])
			arr[0] = 1;
		else
			arr[0] = 0;
		//std::cout << 'm' << arr[0] << std::endl;
		for (int i = 1; i < strSize; ++i)
		{
			//std::cout << str[i] << std::endl;
			//std::cout << i - 1 << 'm' << arr[i - 1] << std::endl;
			//std::cout << str[i - 1] << ' ' << arr[i - 1] << ' ' << len_strc << std::endl;
			if (arr[i - 1] != len_strc)
			{
				//std::cout << str[i - 1] << ' ' << arr[i - 1] << ' ' << len_strc << std::endl;

				if (str[i] == strc[arr[i - 1]])
				{
					arr[i] = arr[i - 1] + 1;
					continue;
				}
				if (str[i] == strc[0])
				{
					arr[i] = 1;
					continue;
				}
				else
				{
					arr[i] = 0;
					continue;
				}
			}
			delete[] arr;
			return true; 
		}
		for (int i = 0; i < strSize; ++i)
		{
			std::cout << str[i] << ' ' << arr[i] << std::endl;
		}
		if (arr[strSize - 2] == len_strc)
		{
			delete[] arr;
			return true;
		}
		delete[] arr;
		return false;
	}

	friend std::ostream& operator << (std::ostream& streamP , const String& string );

private:

	char* str;
	int memorySize;
	int strSize;

	int strLen(const char* str)
	{
		int i = 0;
		while (true)
		{
			if (str[i] == '\0')
			{ 
				return i;
			}
			i++;
		}
	}
	int strCount(char* str, char n)
{
	int i = 0;
	int count = 0;
	while (true)
	{
		if (str[i] == '\0')
			return count;
		i++;
		if (str[i] == n)
		{
			count++;
		}
	}
}
	String arrCharMerge(char* str1, char* str2)
{
	int len = strLen(str1) + strLen(str2) + 1;
	String string(len);
	for (int i = 0; i < strLen(str1); ++i)
	{
		string[i] = str1[i];
	}
	for (int i = 0; i < strLen(str2) + 1; ++i)
	{
		string[i + strLen(str1)] = str2[i];
	}
	return string;
}

};






