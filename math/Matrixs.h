/**
******************************************************************************
* @file    Matrixs.h
* @author  Chenxx
* @version V1.0
* @date    2017-10-26
* @brief   This is the static version of matrix class named Matrix.
*		   The head the the origin Matrix.h:
*		//////////////////////////////////////////////////////////
*		//	Interfaces declaration of CMatrixs for matrix operation
*		//	Modified by Tang Qing
*       //	Date: Oct 19, 2009
*       //
*       //	modified the dll preprocesser
*       //	Modified by YichaoSun
*       //	Date: Dec 25, 2009
*		//////////////////////////////////////////////////////////
*			Part of the operation of from CMatrixs change to use the
*			CMSIS arm_math version.
******************************************************************************/
#ifndef _CMATRIXS_H_
#define _CMATRIXS_H_

#include "arm_math.h"

#define ENABLE_PRINT 1

class CMatrixs
{
	public:

		//
	    // Constructor and destructor
	    //

		CMatrixs(int nRows, int nCols, float* pData);//constructor
		CMatrixs(int nSize, float* pData);			//squar matrix constructor
		bool MakeUnitMatrix();
        void MakeZeroMatrix();
		virtual ~CMatrixs();

        // Output and display
#if ENABLE_PRINT
        bool print(char* matname = "");
        bool printRaw(char* matname = "");
#endif

		//
   	    // operation of elements and value
   	    //

		bool	SetElement(int nRow, int nCol,float value);
    	float	GetElement(int nRow, int nCol) const;
        void    SetData(const float* pData);
        int		GetNumColumns() const;
        int		GetNumRows() const;

        //
        // mathematical operation
        //

        CMatrixs& operator=(const CMatrixs& other);
        bool operator==(const CMatrixs& other) const;
        bool operator!=(const CMatrixs& other) const;

        bool Add(const CMatrixs& other, CMatrixs& result) const;
        bool Sub(const CMatrixs& other, CMatrixs& result) const;
 		bool Mult(const CMatrixs& other, CMatrixs& result) const;
        bool RightMult(const CMatrixs& other, CMatrixs& result) const;
		bool Scale(float value, CMatrixs& result) const;

        bool operator+=(const CMatrixs& other);//TODO: test
        bool operator-=(const CMatrixs& other);//TODO: test
        bool operator*=(float value) ;
        bool operator*=(const CMatrixs& other) ;
        bool operator/=(float value) ;
        //complex mult
        bool CMul(const CMatrixs& AR, const CMatrixs& AI, const CMatrixs& BR, const CMatrixs& BI, CMatrixs& CR, CMatrixs& CI) const;

        //bool Transpose();

		bool Transpose(CMatrixs& result) const;

        bool SameDimensions(const CMatrixs& other) const;

        //bool InvertGaussJordan();

		bool InvertGaussJordan(CMatrixs& result) const;

    protected:
		arm_matrix_instance_f32 MatIns_;

	private:
};
#endif
//end of file

