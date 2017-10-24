#include <iostream>
#include "fixed_vector.h"
#include <stdint.h>

using namespace std;
fixed_vector<uint8_t, 10> tv;
int main()
{
	cout << "hello" << endl;
    tv.push_back(0);
	return 0;
}
