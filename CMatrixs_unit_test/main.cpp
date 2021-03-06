#include <iostream>
#include "Matrixs.h"
#include "Matrix.h"
using namespace std;
void inverseTest();
void add_test();
void sub_test();
void mult_test();

int main()
{
	cout << "start" <<endl;    
    //inverseTest();
    //add_test();
    //sub_test();
    mult_test();
    cin.get();
	return 0;
 	
}

void inverseTest()
{
    cout << "=============== inverse test ==============" << endl;
    const uint16_t MAT_SIZE = 4;
    const float matcs0[MAT_SIZE * MAT_SIZE] = { 0.5f, -0.85f, 0, 20000, 0.85f, 0.5f, 0, 300, 0, 0, 1, 0, 0, 0, 0, 1 };
    double matcs[MAT_SIZE * MAT_SIZE];
    float mats0[MAT_SIZE * MAT_SIZE];
    float mats1[MAT_SIZE * MAT_SIZE];
    float mats2[MAT_SIZE * MAT_SIZE];

    for (int i = 0; i < MAT_SIZE * MAT_SIZE; i++)
    {
        matcs[i] = matcs0[i];
    }
    CMatrixs mat0(MAT_SIZE, mats0);
    mat0.SetData(matcs0);
    CMatrixs mat1(MAT_SIZE, mats1);
    CMatrixs mat2(MAT_SIZE, mats2);

    mat0.InvertGaussJordan(mat1);
    mat0.SetData(matcs0);
    mat1.Mult(mat0, mat2);
    mat0.print("mat0");
    mat1.print("mat1");
    mat2.print("mat2");
    mat2.printRaw("mat2");

    CMatrix mat3(MAT_SIZE);
    CMatrix mat4(MAT_SIZE);
    CMatrix mat5(MAT_SIZE);
    mat3.SetData((const double*)matcs);
    mat4.SetData((const double*)matcs);
    mat3.InvertGaussJordan();
    mat5 = mat3 * mat4;

    cout << "mat3" << endl;
    mat3.print();
    cout << "mat4" << endl;
    mat4.print();
    cout << "mat5" << endl;
    mat5.print();
}

void add_test()
{
    cout << "=============== Add test ==============" << endl;
    const uint16_t MAT_SIZE = 3;
    float mats0[MAT_SIZE * MAT_SIZE];
    float mats1[MAT_SIZE * MAT_SIZE];
    float mats2[MAT_SIZE * MAT_SIZE];
    float mats3[MAT_SIZE * MAT_SIZE];
    float mats4[MAT_SIZE * MAT_SIZE];
    float mats5[MAT_SIZE * MAT_SIZE];

    CMatrixs mat0(MAT_SIZE, mats0);
    CMatrixs mat1(MAT_SIZE, mats1);
    CMatrixs mat2(MAT_SIZE, mats2);
    CMatrixs mat3(MAT_SIZE, mats3);
    CMatrixs mat4(MAT_SIZE, mats4);
    CMatrixs mat5(MAT_SIZE, mats5);

    mat0.MakeUnitMatrix();
    mat1.MakeUnitMatrix();
    mat2.MakeUnitMatrix();
    mat3.MakeUnitMatrix();

    mat0.print("mat0");
    mat1.MakeUnitMatrix();
    mat1 += mat0;

    mat1.print("mat1");

    cout << "mat3 = mat2 + mat0" << endl;
    mat2.Add(mat0, mat3);
    mat0.print("mat0");
    mat2.print("mat2");
    mat3.print("mat3");


}

void sub_test()
{
    cout << "=============== Sub test ==============" << endl;
    const uint16_t MAT_SIZE = 3;
    float mats0[MAT_SIZE * MAT_SIZE];
    float mats1[MAT_SIZE * MAT_SIZE];
    float mats2[MAT_SIZE * MAT_SIZE];
    float mats3[MAT_SIZE * MAT_SIZE];
    float mats4[MAT_SIZE * MAT_SIZE];
    float mats5[MAT_SIZE * MAT_SIZE];

    CMatrixs mat0(MAT_SIZE, mats0);
    CMatrixs mat1(MAT_SIZE, mats1);
    CMatrixs mat2(MAT_SIZE, mats2);
    CMatrixs mat3(MAT_SIZE, mats3);
    CMatrixs mat4(MAT_SIZE, mats4);
    CMatrixs mat5(MAT_SIZE, mats5);

    mat0.MakeUnitMatrix();
    mat1.MakeUnitMatrix();
    mat2.MakeUnitMatrix();
    mat3.MakeUnitMatrix();

    mat0.Scale(10, mat1);

    mat0.print("mat0");
    mat1.print("mat1");

    cout << "mat2 = mat1 - mat0" << endl;
    mat1.Sub(mat0, mat2);
    mat2.print("mat2");
}

void mult_test()
{
    cout << "=============== mult test ==============" << endl;
    const uint16_t MAT_ROW = 2;
    const uint16_t MAT_COL = 4;
    float mats0[MAT_ROW * MAT_COL];
    float mats1[MAT_COL * MAT_ROW];
    float mats2[MAT_ROW * MAT_ROW];
    float mats3[MAT_COL * MAT_COL];
    float mats4[9];
    

    CMatrixs mat0(MAT_ROW , MAT_COL, mats0);
    CMatrixs mat1(MAT_COL , MAT_ROW, mats1);
    CMatrixs mat2(MAT_ROW , MAT_ROW, mats2);
    CMatrixs mat3(MAT_COL , MAT_COL, mats3);
    CMatrixs mat4(3, mats4);
    
    mat4.MakeUnitMatrix();
    for (int i = 0; i < MAT_ROW; i++)
    {
        for (int j = 0; j < MAT_COL; j++)
        {
            mat0.SetElement(i, j, 10*i + j);
            mat1.SetElement(j, i, 1);
        }
    }

    mat0.print("mat0");
    mat1.print("mat1");

    mat0.Mult(mat1, mat2);
    mat0.RightMult(mat1, mat3);

    mat0.RightMult(mat1, mat4);

    cout << "mat2 = mat0 * mat1" << endl;
    mat2.print("mat2");

    cout << "mat3 = mat1 * mat0" << endl;
    mat3.print("mat3");

    cout << "mat4 = mat1 * mat0" << endl;
    mat4.print("mat4");
}
//end of file

