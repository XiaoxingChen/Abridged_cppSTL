#include <iostream>
#include "fixed_vector.h"
#include <stdint.h>
#include <vector>
#include <algorithm>

using namespace std;
#define VECT_LEN 100
#define VECT_TYPE uint16_t

void remove_test(uint16_t test_time);

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
    cout << "start" << endl;
    remove_test(20);
    
    cin.get();
	return 0;
}

void remove_test(uint16_t test_time)
{
    const uint8_t test_buf_len = 30;
	VECT_TYPE originArray[test_buf_len];
    vector<VECT_TYPE> stdv;
    fixed_vector<VECT_TYPE, VECT_LEN> v;

    cout << "*** remove_test ***" << endl;

    for (int j = 0; j < test_time; j++)
    {
        stdv.clear();
        v.clear();
        for (int i = 0; i < test_buf_len; i++)
        {
            originArray[i] = rand() % 10;
            stdv.push_back(originArray[i]);
            v.push_back(originArray[i]);
        }

        VECT_TYPE remove_num = rand() % 10;
        remove(stdv.begin(), stdv.end(), remove_num);
        v.remove(remove_num);

        bool test_ok = true;

        do
        {
            if (v.size() != stdv.size())
            {
                test_ok = false;
                cout << "test faild, length mismatch. fixedv:" << v.size()<< " stdv:" << stdv.size() << endl;
                break;
            }

            for (int i = 0; i < v.size(); i++)
            {
                if (v.at(i) != stdv.at(i))
                {
                    test_ok = false;
                    cout << "test faild, data mismatch" << endl;
                    break;
                }
            }

        } while (0);

        if (!test_ok)
        {
            cout << "test failed" << endl;
            print_vector(v);
            print_vector(stdv);
        }
        else
        {
            cout << "test" << j << "vok!" << endl;
        }
        
    }

    
    
}
