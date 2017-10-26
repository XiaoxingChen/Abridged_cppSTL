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

	private:
};
#endif
//end of file

