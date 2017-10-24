#include <iostream>
#include "fixed_vector.h"
#include <stdint.h>
#include <vector>
#include <algorithm>

using namespace std;
#define VECT_LEN 50
#define VECT_TYPE uint16_t

void remove_test();

void print_vector(fixed_vector<VECT_TYPE, VECT_LEN>& v)
{
    cout << "fixed_vector:\t";
    for (int i = 0; i < v.size(); i++)
    {
        cout << v.at(i) << " ";
    }
    cout << endl;
}

void print_vector(vector<VECT_TYPE>& v)
{
    cout << "std_vector:\t";
	for(int i = 0; i < v.size(); i++)
	{
		cout << v.at(i) << " ";
	}
	cout << endl;

}

int main()
{
    /*cin.get();*/
    cout << "start" << endl;
    /*cin.get();*/
    remove_test();
    
    cin.get();
	return 0;
}

void remove_test()
{
    const uint8_t test_buf_len = 30;
	VECT_TYPE originArray[test_buf_len];
    vector<VECT_TYPE> stdv;
    fixed_vector<VECT_TYPE, VECT_LEN> v;

    for (int i = 0; i < test_buf_len; i++)
    {
        originArray[i] = rand() % 10;
        stdv.push_back(originArray[i]);
        v.push_back(originArray[i]);
    }

    VECT_TYPE remove_num = 5;
    remove(stdv.begin(), stdv.end(), remove_num);
    v.remove(remove_num);

    bool test_ok = true;
   
    do 
    {
        if (v.size() != stdv.size())
        {
            test_ok = false;
            cout << "test faild, length mismatch" << endl;
            break;
        }
    
    } while (0);

    if (!test_ok)
    {
        print_vector(v);
        print_vector(stdv);
    }
}
