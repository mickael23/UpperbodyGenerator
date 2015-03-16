#ifndef INFO_H
#define INFO_H

#include <string>

using namespace std;

class Info{
	public:
		string  fileName;
		int		headUp_x, headUp_y;
		int		left, right;
		int		headMiddle_x, headMiddle_y;
		bool	valid;

		Info(string s);
};

#endif