#include "Matrixs.h"

//////////////////////////////////////////////////////////////////////
// Constructor for CMSIS matrix operation
// Created at 2017/07/21 by chenxx
//////////////////////////////////////////////////////////////////////
CMatrix::CMatrix(int nRows, int nCols,float* pData)
{
	arm_mat_init_f32(&MatIns_, nRows, nCols, pData);
}

CMatrix::~CMatrix()
{

}

bool CMatrix::MakeUnitMatrix()
{
	if(MatIns_.numCols != MatIns_.numRows)
		return false;

	for (int i=0; i < MatIns_.numCols; ++i)
        for (int j=0; j < MatIns_.numCols; ++j)
            if (i == j)
                SetElement(i, j, 1);

    return true;
}

bool CMatrix::SetElement(int nRow, int nCol,float value)
{
    if (nCol < 0 || nCol >= MatIns_.numCols || nRow < 0 || nRow >= MatIns_.numRows)
        return false;						// array bounds error
    if (MatIns_.pData == NULL)
        return false;							// bad pointer error

    MatIns_.pData[nCol + nRow * MatIns_.numCols] = value;

    return true;
}

float CMatrix::GetElement(int nRow, int nCol) const
{
    return MatIns_.pData[nCol + nRow * MatIns_.numCols] ;
}

int	CMatrix::GetNumColumns() const
{
    return MatIns_.numCols;
}

int	CMatrix::GetNumRows() const
{
    return MatIns_.numRows;
}

bool CMatrix::SameDimensions(const CMatrix& other) const
{
    return (other.GetNumRows() == GetNumRows()
        &&  other.GetNumColumns() == GetNumColumns());
}

CMatrix& CMatrix::operator=(const CMatrix& other)
{
    if (&other != this && SameDimensions(other))
    {
        memcpy(MatIns_.pData, other.MatIns_.pData, sizeof(float)*MatIns_.numCols*MatIns_.numRows);
    }
    // finally return a reference to ourselves
    return *this ;
}

bool CMatrix::operator==(const CMatrix& other) const
{
    if (!SameDimensions(other))
        return false;

    for (int i=0; i<MatIns_.numRows; ++i)
    {
        for (int j=0; j<MatIns_.numCols; ++j)
        {
            if (GetElement(i, j) != other.GetElement(i, j))
                return false;
        }
    }

    return true;
}

bool CMatrix::operator!=(const CMatrix& other) const
{
    return !(*this == other);
}

bool CMatrix::add(const CMatrix& other, CMatrix& result) const
{
	return arm_mat_add_f32(&MatIns_, &other.MatIns_, &result.MatIns_);
}

bool CMatrix::sub(const CMatrix& other, CMatrix& result) const
{
    return arm_mat_sub_f32(&MatIns_, &other.MatIns_, &result.MatIns_);
}

bool CMatrix::mult(const CMatrix& other, CMatrix& result) const
{
    return arm_mat_mult_f32(&MatIns_, &other.MatIns_, &result.MatIns_);
}

bool CMatrix::scale(float value, CMatrix& result) const
{
	return arm_mat_scale_f32(&MatIns_, value, &result.MatIns_);
}

bool CMatrix::operator+=(const CMatrix& other) const
{
    return arm_mat_add_f32(&MatIns_, &other.MatIns_, &MatIns_);
}

bool CMatrix::operator-=(const CMatrix& other) const
{
    return arm_mat_sub_f32(&MatIns_, &other.MatIns_, &MatIns_);
}

bool CMatrix::operator*=(float value) const
{
    return arm_mat_scale_f32(&MatIns_, value, &MatIns_);
}

bool CMatrix::operator*=(const CMatrix& other) 
{
	return arm_mat_mult_f32(&MatIns_, &other.MatIns_, &MatIns_);
}

bool CMatrix::operator/=(float value) 
{
	return arm_mat_scale_f32(&MatIns_, (1.0f / value), &MatIns_);
}

bool CMatrix::Transpose()
{
	arm_mat_trans_f32(&MatIns_, &MatIns_);
}

bool CMatrix::Transpose(CMatrix& result) const
{
	arm_mat_trans_f32(&MatIns_, &result.MatIns_);
}

bool CMatrix::InvertGaussJordan()
{
	arm_status status = arm_mat_inverse_f32(&MatIns_, &MatIns_);
	return (ARM_MATH_SUCCESS == status);
}

bool CMatrix::InvertGaussJordan(CMatrix& result) const
{
	arm_status status = arm_mat_inverse_f32(&MatIns_, &result.MatIns_);
	return (ARM_MATH_SUCCESS == status);
}

