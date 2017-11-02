/**
******************************************************************************
* @file    Matrixs.h
* @author  Chenxx
* @version V1.0
* @date    2017-10-26
* @brief   This is the static version of matrix class named Matrix.
*		   The head the the origin Matrix.h:
*		//////////////////////////////////////////////////////////
*		//	Interfaces declaration of CMatrix for matrix operation
*		//	Modified by Tang Qing
*       //	Date: Oct 19, 2009
*       //
*       //	modified the dll preprocesser
*       //	Modified by YichaoSun
*       //	Date: Dec 25, 2009
*		//////////////////////////////////////////////////////////
*			Part of the operation of from CMatrix change to use the
*			CMSIS arm_math version.
******************************************************************************/
#ifndef _CMATRIXS_H_
#define _CMATRIXS_H_

#include "arm_math.h"

class CMatrixs
{
	public:

		//
	    // Constructor and destructor
	    //

		CMatrix(int nRows, int nCols, float* pData);//constructor
		CMatrix(int nSize, float* pData);			//squar matrix constructor
		bool MakeUnitMatrix();
		virtual ~CMatrix();

		//
   	    // operation of elements and value
   	    //

		bool	SetElement(int nRow, int nCol,float value);
    	float	GetElement(int nRow, int nCol) const;
        int		GetNumColumns() const;
        int		GetNumRows() const;

        //
        // mathematical operation
        //

        CMatrix& operator=(const CMatrix& other);
        bool operator==(const CMatrix& other) const;
        bool operator!=(const CMatrix& other) const;

        bool add(const CMatrix& other, CMatrix& result) const;
        bool sub(const CMatrix& other, CMatrix& result) const;
 		bool mult(const CMatrix& other, CMatrix& result) const;
		bool scale(float value, CMatrix& result) const;

        bool operator+=(const CMatrix& other);//TODO: test
        bool operator-=(const CMatrix& other);//TODO: test
        bool operator*=(float value) ;
        bool operator*=(const CMatrix& other) ;
        bool operator/=(float value) ;
        //complex mult
        bool CMul(const CMatrix& AR, const CMatrix& AI, const CMatrix& BR, const CMatrix& BI, CMatrix& CR, CMatrix& CI) const;

        bool Transpose();

		bool Transpose(CMatrix& result) const;

        bool SameDimensions(const CMatrix& other) const;

        bool InvertGaussJordan();

		bool InvertGaussJordan(CMatrix& result) const;

    protected:
		arm_matrix_instance_f32 MatIns_;

	private:
};
#endif
//end of file

