#include <iostream>
#include "fixed_vector.h"
#include <stdint.h>
#include <vector>
#include <algorithm>

using namespace std;
#define VECT_LEN 100
#define VECT_TYPE uint16_t

void remove_test(uint16_t test_time);
void erase_test(uint16_t test_time);
void push_remove_test();
void resize_test(uint16_t test_time);
void front_test(uint16_t test_time);

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

void print_array(VECT_TYPE* array, uint16_t len)
{
    cout << "origin_array:\t";
    for (int i = 0; i < len; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main()
{
    cout << "start" << endl;
    remove_test(20);
    erase_test(50);
    resize_test(100);
    front_test(50);

    cin.get();
	return 0;
}

void remove_test(uint16_t test_time)
{
    const uint8_t test_buf_len = 30;
	VECT_TYPE originArray[test_buf_len];
    vector<VECT_TYPE> stdv;
    fixed_vector<VECT_TYPE, VECT_LEN> v;

    cout << endl <<  "********* remove_test *********" << endl;
    bool test_ok = true;

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
            /*cout << "test" << j << "vok!" << endl;*/
        }
#if     0
        cout << "remove num = " << remove_num << endl;
        print_array(originArray, test_buf_len);
        print_vector(v);
        print_vector(stdv);
#endif


    }
    if (test_ok)
    {
        cout << "test for " << test_time << "times passed!" << endl;
    }
}

void erase_test(uint16_t test_time)
{
    const uint8_t test_buf_len = 30;
    VECT_TYPE originArray[test_buf_len];
    vector<VECT_TYPE> stdv;
    fixed_vector<VECT_TYPE, VECT_LEN> v;

    cout << endl << "********* erase_test *********" << endl;
    bool test_ok = true;

    for (int t = 0; t < test_time; t++)
    {
        stdv.clear();
        v.clear();
        for (int i = 0; i < test_buf_len; i++)
        {
            originArray[i] = rand() % 10;
            stdv.push_back(originArray[i]);
            v.push_back(originArray[i]);
        }

        stdv.erase(stdv.begin());
        v.erase(v.begin());

        do
        {
            if (v.size() != stdv.size())
            {
                test_ok = false;
                cout << "test faild, length mismatch. fixedv:" << v.size() << " stdv:" << stdv.size() << endl;
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
            print_array(originArray, test_buf_len);
            print_vector(v);
            print_vector(stdv);
        }
        else
        {
            /*cout << "test" << j << "vok!" << endl;*/
        }

    }
    if (test_ok)
    {
        cout << "test for " << test_time << "times passed!" << endl;
    }

}

void push_remove_test()
{
    fixed_vector<VECT_TYPE, VECT_LEN> v;

    v.push_back(10);
    v.push_back(12);
    v.push_back(0);
    v.push_back(7);
    v.push_back(5);
    print_vector(v);
    v.remove(7);
    cout << "remove(7)" << endl;
    print_vector(v);


}

void resize_test(uint16_t test_time)
{
    const uint8_t test_buf_len = 30;
    VECT_TYPE originArray[test_buf_len];
    vector<VECT_TYPE> stdv;
    fixed_vector<VECT_TYPE, VECT_LEN> v;

    cout << endl << "********* resize_test *********" << endl;
    bool test_ok = true;

    for (int t = 0; t < test_time; t++)
    {
        stdv.clear();
        v.clear();
        for (int i = 0; i < test_buf_len; i++)
        {
            originArray[i] = rand() % 10;
            stdv.push_back(originArray[i]);
            v.push_back(originArray[i]);
        }

        uint16_t rand_size = rand() % (test_buf_len - 1);

        stdv.resize(rand_size);
        v.resize(rand_size);

        do
        {
            if (v.size() != stdv.size())
            {
                test_ok = false;
                cout << "test faild, length mismatch. fixedv:" << v.size() << " stdv:" << stdv.size() << endl;
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
            print_array(originArray, test_buf_len);
            print_vector(v);
            print_vector(stdv);
        }
        else
        {
            /*cout << "test" << j << "vok!" << endl;*/
        }

    }
    if (test_ok)
    {
        cout << "test for " << test_time << "times passed!" << endl;
    }

}


void front_test(uint16_t test_time)
{
    const uint8_t test_buf_len = 30;
    VECT_TYPE originArray[test_buf_len];
    vector<VECT_TYPE> stdv;
    fixed_vector<VECT_TYPE, VECT_LEN> v;

    cout << endl << "********* fronts_test *********" << endl;
    bool test_ok = true;

    for (int t = 0; t < test_time; t++)
    {
        stdv.clear();
        v.clear();
        for (int i = 0; i < test_buf_len; i++)
        {
            originArray[i] = rand() % 10;
            stdv.push_back(originArray[i]);
            v.push_back(originArray[i]);
        }

        do
        {
            if (v.front() != stdv.front())
            {
                test_ok = false;
                cout << "test faild, front mismatch. fixedv:" << v.front() << " stdv:" << stdv.front() << endl;
                break;
            }

        } while (0);

        if (!test_ok)
        {
            cout << "test failed" << endl;
            print_array(originArray, test_buf_len);
            print_vector(v);
            print_vector(stdv);
        }
        else
        {
            /*cout << "test" << j << "vok!" << endl;*/
        }

    }
    if (test_ok)
    {
        cout << "test for " << test_time << "times passed!" << endl;
    }

}
