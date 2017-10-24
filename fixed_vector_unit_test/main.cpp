#include <iostream>
#include "fixed_vector.h"
#include <stdint.h>

using namespace std;
#define VECT_LEN 10
#define VECT_TYPE uint16_t
fixed_vector<VECT_TYPE, VECT_LEN> tv;

void print_vector(fixed_vector<VECT_TYPE, VECT_LEN>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        cout << v.at(i) << " ";
    }
    cout << endl;
}

int main()
{
    /*cin.get();*/
    cout << "hello" << endl;
    /*cin.get();*/
    tv.push_back(10);
    tv.push_back(10);
    tv.push_back(10);
    tv.push_back(10);
    print_vector(tv);
    
    cin.get();
	return 0;
}
