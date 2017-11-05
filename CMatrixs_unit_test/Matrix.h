//////////////////////////////////////////////////////////////////////
// Matrix.h
//
// ����������� CMatrix �������ӿ�
//	Modified by Tang Qing
//	Date: Oct 19, 2009
//
//  �޸���dll����ͷ
//	Modified by YichaoSun
//	Date: Dec 25, 2009

//////////////////////////////////////////////////////////////////////
#ifndef _TANGTANG_CMATRIX_
#define _TANGTANG_CMATRIX_

//#include <windows.h>
#include <iostream>
#include <cmath>
#include "string.h"

class CMatrix
{
    //
    // ���нӿں���
    //
public:

    //
    // ����������
    //

    CMatrix();										// �������캯��
    CMatrix(int nRows, int nCols);					// ָ�����й��캯��
    CMatrix(int nRows, int nCols,const double value[]);	// ָ�����ݹ��캯��
    CMatrix(int nSize);								// �����캯��
    CMatrix(int nSize, const double value[]);				// ָ�����ݷ����캯��
    CMatrix(const CMatrix& other);					// �������캯��
    bool	Init(int nRows, int nCols);				// ��ʼ������
    bool	MakeUnitMatrix(int nSize);				// �������ʼ��Ϊ��λ����
    virtual ~CMatrix();								// ��������

    ////
    //// ��������ʾ
    ////
    // �����ʾ
    bool print(void);


    //// ���ַ���ת��Ϊ��������
    //bool FromString(CString s, const CString& sDelim = " ", bool bLineBreak = TRUE);
    //// ������ת��Ϊ�ַ���
    //CString ToString(const CString& sDelim = " ", bool bLineBreak = TRUE) const;
    //// �������ָ����ת��Ϊ�ַ���
    //CString RowToString(int nRow, const CString& sDelim = " ") const;
    //// �������ָ����ת��Ϊ�ַ���
    //CString ColToString(int nCol, const CString& sDelim = " ") const;

    //
    // Ԫ����ֵ����
    //

    bool	SetElement(int nRow, int nCol,double value);	// ����ָ��Ԫ�ص�ֵ
    double	GetElement(int nRow, int nCol) const;			// ��ȡָ��Ԫ�ص�ֵ
    void    SetData(const double value[]);						// ���þ����ֵ
    void	SetDataF(double value[], int nRows, int nCols);	// ���þ����ֵ������Fortranר�á����ã���
    void    SetDataVertical(double value[]);						// ���þ����ֵ��ֱ����
    int		GetNumColumns() const;							// ��ȡ���������
    int		GetNumRows() const;								// ��ȡ���������
    int     GetRowVector(int nRow, double* pVector) const;	// ��ȡ�����ָ���о���
    int     GetColVector(int nCol, double* pVector) const;	// ��ȡ�����ָ���о���
    double* GetData() const;								// ��ȡ�����ֵ

    //
    // ��ѧ����
    //

    CMatrix& operator=(const CMatrix& other);
    bool operator==(const CMatrix& other) const;
    bool operator!=(const CMatrix& other) const;
    CMatrix	operator|(const CMatrix& other) const;		// Column Add
    CMatrix	operator&(const CMatrix& other) const;		// Row Add
    CMatrix	operator+(const CMatrix& other) const;
    CMatrix	operator-(const CMatrix& other) const;
    CMatrix	operator*(double value) const;
    CMatrix	operator*(const CMatrix& other) const;
    CMatrix	operator/(double value) const;
    // ������˷�
    bool CMul(const CMatrix& AR, const CMatrix& AI, const CMatrix& BR, const CMatrix& BI, CMatrix& CR, CMatrix& CI) const;
    // �����ת��
    CMatrix Transpose() const;

    double operator[](int index) const;

    //
    // �㷨
    //

    // ʵ���������ȫѡ��Ԫ��˹��Լ����
    bool InvertGaussJordan();
    // �����������ȫѡ��Ԫ��˹��Լ����
    bool InvertGaussJordan(CMatrix& mtxImag);
    // �Գ��������������
    bool InvertSsgj();
    // �в����Ⱦ�������İ����ط���
    bool InvertTrench();
    // ������ʽֵ��ȫѡ��Ԫ��˹��ȥ��
    double DetGauss();
    // ������ȵ�ȫѡ��Ԫ��˹��ȥ��
    int RankGauss();
    // �Գ��������������˹���ֽ�������ʽ����ֵ
    bool DetCholesky(double* dblDet);
    // ��������Ƿֽ�
    bool SplitLU(CMatrix& mtxL, CMatrix& mtxU);
    // һ��ʵ�����QR�ֽ�
    bool SplitQR(CMatrix& mtxQ);
    // һ��ʵ���������ֵ�ֽ�
    bool SplitUV(CMatrix& mtxU, CMatrix& mtxV, double eps = 0.000001);
    // ������������ֵ�ֽⷨ
    bool GInvertUV(CMatrix& mtxAP, CMatrix& mtxU, CMatrix& mtxV, double eps = 0.000001);
    // Լ���Գƾ���Ϊ�Գ����Խ���ĺ�˹�ɶ��±任��
    bool MakeSymTri(CMatrix& mtxQ, CMatrix& mtxT, double dblB[], double dblC[]);
    // ʵ�Գ����Խ����ȫ������ֵ�����������ļ���
    bool SymTriEigenv(double dblB[], double dblC[], CMatrix& mtxQ, int nMaxIt = 60, double eps = 0.000001);
    // Լ��һ��ʵ����Ϊ���겮�����ĳ������Ʊ任��
    void MakeHberg();
    // ����겮�����ȫ������ֵ��QR����
    bool HBergEigenv(double dblU[], double dblV[], int nMaxIt = 60, double eps = 0.000001);
    // ��ʵ�Գƾ�������ֵ�������������ſɱȷ�
    bool JacobiEigenv(double dblEigenValue[], CMatrix& mtxEigenVector, int nMaxIt = 60, double eps = 0.000001);
    // ��ʵ�Գƾ�������ֵ�������������ſɱȹ��ط�
    bool JacobiEigenv2(double dblEigenValue[], CMatrix& mtxEigenVector, double eps = 0.000001);



    // Get the sub matrix from the parents' matrix
    CMatrix GetSubMatrix(int row1, int row2, int col1, int col2);

    double norm(void) const;


    CMatrix GetColVectorMat(int nCol);


    //
    // ���������ݳ�Ա
    //
protected:
    int	m_nNumColumns;			// ��������
    int	m_nNumRows;				// ��������
    double*	m_pData;			// �������ݻ�����

    //
    // �ڲ�����
    //
private:
    void ppp(double a[], double e[], double s[], double v[], int m, int n);
    void sss(double fg[2], double cs[2]);


};


#endif
