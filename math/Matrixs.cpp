#include "Matrixs.h"

/**
* @brief  Constructor
* @param  nRows: rows of the matrix
* @param  nCols: colums of the matrix
* @param  pData: memory that allocated for the matrix
* @retval None
*/
CMatrixs::CMatrixs(int nRows, int nCols,float* pData)
{
	arm_mat_init_f32(&MatIns_, nRows, nCols, pData);
}

/**
* @brief  Constructor for square matrix
* @param  nSize: rows and also colums of the matrix
* @param  pData: memory that allocated for the matrix
* @retval None
*/
CMatrixs::CMatrixs(int nSize, float* pData)
{
    arm_mat_init_f32(&MatIns_, nSize, nSize, pData);
}

/**
* @brief  Destructor
* @param  None
* @retval None
*/
CMatrixs::~CMatrixs()
{

}

/**
* @brief  Set current matrix to unit matrix
* @param  None
* @retval bool: whether the operation is invalid or not
*/
bool CMatrixs::MakeUnitMatrix()
{
    if (MatIns_.numCols != MatIns_.numRows)
    {
        MakeZeroMatrix();
        return false;
    }
        

    for (int i = 0; i < MatIns_.numCols; ++i)
        for (int j = 0; j < MatIns_.numCols; ++j)
            if (i == j)
                SetElement(i, j, 1);
            else
                SetElement(i, j, 0);

    return true;
}

/**
* @brief  Set current matrix to zero matrix
* @param  None
* @retval bool: whether the operation is invalid or not
*/
void CMatrixs::MakeZeroMatrix()
{
    for (int i = 0; i < MatIns_.numCols; ++i)
        for (int j = 0; j < MatIns_.numCols; ++j)
            SetElement(i, j, 0);
}

/**
* @brief  Set the specified element value
* @param  nRows: rows of the element
* @param  nCols: colums of the element
* @param  value: value of the target element
* @retval bool: whether the operation is invalid or not
*/
bool CMatrixs::SetElement(int nRow, int nCol,float value)
{
    if (nCol < 0 || nCol >= MatIns_.numCols || nRow < 0 || nRow >= MatIns_.numRows)
        return false;						// array bounds error
    if (MatIns_.pData == NULL)
        return false;							// bad pointer error

    MatIns_.pData[nCol + nRow * MatIns_.numCols] = value;

    return true;
}

/**
* @brief  Set the data¡¡of the matrix from an array
* @param  pData: pointer of the array
* @retval None
* @Note  This function will not check the length of the array
*/
void CMatrixs::SetData(const float* pData)
{
    memcpy(MatIns_.pData, pData, sizeof(float) * MatIns_.numCols * MatIns_.numRows);
}

/**
* @brief  Get the value of the specified element
* @param  pData: pointer of the array
* @param  nRows: rows of the element
* @param  nCols: colums of the element
* @retval value of the element
*/
float CMatrixs::GetElement(int nRow, int nCol) const
{
    return MatIns_.pData[nCol + nRow * MatIns_.numCols] ;
}

/**
* @brief  Get the column number of the matrix
* @retval column number
*/
int	CMatrixs::GetNumColumns() const
{
    return MatIns_.numCols;
}

/**
* @brief  Get the row number of the matrix
* @retval row number
*/
int	CMatrixs::GetNumRows() const
{
    return MatIns_.numRows;
}

/**
* @brief  Judge whether the two matrices have the same rows and columns
* @param  other: another matrix
* @retval Ture: same; False: Not;
*/
bool CMatrixs::SameDimensions(const CMatrixs& other) const
{
    return (other.GetNumRows() == GetNumRows()
        &&  other.GetNumColumns() == GetNumColumns());
}

/**
* @brief  Copy constructor
* @param  other: another matrix
* @retval Useless
*/
CMatrixs& CMatrixs::operator=(const CMatrixs& other)
{
    if (&other != this && SameDimensions(other))
    {
        memcpy(MatIns_.pData, other.MatIns_.pData, sizeof(float)*MatIns_.numCols*MatIns_.numRows);
    }
    // finally return a reference to ourselves
    return *this ;
}

/**
* @brief  Judge whether the two matrices are the same
* @param  other: another matrix
* @retval The same or not
*/
bool CMatrixs::operator==(const CMatrixs& other) const
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

/**
* @brief  Judge whether the two matrices are different
* @param  other: another matrix
* @retval Different or not
*/
bool CMatrixs::operator!=(const CMatrixs& other) const
{
    return !(*this == other);
}

/**
* @brief Floating-point matrix addition.
* @param[in]    other ref to the second input matrix structure
* @param[out]   result ref to output matrix structure
* @return       Wheter function success
*/
bool CMatrixs::Add(const CMatrixs& other, CMatrixs& result) const
{
	arm_status status  =  arm_mat_add_f32(&MatIns_, &other.MatIns_, &result.MatIns_);
    if (ARM_MATH_SUCCESS != status)
    {
        result.MakeZeroMatrix();
        return false;
    }
    return true;
}

/**
* @brief Floating-point matrix subtraction.
* @param[in]    other ref to the second input matrix structure
* @param[out]   result ref to output matrix structure
* @return       Wheter function success
*/
bool CMatrixs::Sub(const CMatrixs& other, CMatrixs& result) const
{
    arm_status status  =  arm_mat_sub_f32(&MatIns_, &other.MatIns_, &result.MatIns_);
    if (ARM_MATH_SUCCESS != status)
    {
        result.MakeZeroMatrix();
        return false;
    }
    return true;
}

/**
* @brief Floating-point matrix multiplication.
* @param[in]    other ref to the second input matrix structure
* @param[out]   result ref to output matrix structure
* @return       Wheter function success
*/
bool CMatrixs::Mult(const CMatrixs& other, CMatrixs& result) const
{
    arm_status status  =  arm_mat_mult_f32(&MatIns_, &other.MatIns_, &result.MatIns_);
    if (ARM_MATH_SUCCESS != status)
    {
        result.MakeZeroMatrix();
        return false;
    }
    return true;
}

/**
* @brief Floating-point matrix right multiplication.
* @param[in]    other ref to the second input matrix structure
* @param[out]   result ref to output matrix structure
* @return       Wheter function success
*/
bool CMatrixs::RightMult(const CMatrixs& other, CMatrixs& result) const
{
    arm_status status = arm_mat_mult_f32(&other.MatIns_, &MatIns_, &result.MatIns_);
    if (ARM_MATH_SUCCESS != status)
    {
        result.MakeZeroMatrix();
        return false;
    }
    return true;
}

/**
* @brief Floating-point matrix scaling..
* @param[in]    other ref to the second input matrix structure
* @param[out]   result ref to output matrix structure
* @return       Wheter function success
*/
bool CMatrixs::Scale(float value, CMatrixs& result) const
{
	arm_status status  =  arm_mat_scale_f32(&MatIns_, value, &result.MatIns_);
    if (ARM_MATH_SUCCESS != status)
    {
        result.MakeZeroMatrix();
        return false;
    }
    return true;
}

/**
* @brief Floating-point matrix addition operator reload
* @param[in]    other ref to the second input matrix structure
* @return       Wheter function success
*/
bool CMatrixs::operator+=(const CMatrixs& other)
{
    arm_status status = arm_mat_add_f32(&MatIns_, &other.MatIns_, &MatIns_);
    if (ARM_MATH_SUCCESS != status)
    {
        MakeZeroMatrix();
        return false;
    }
    return true;
}

/**
* @brief Floating-point matrix subtraction operator reload
* @param[in]    other ref to the second input matrix structure
* @return       Wheter function success
*/
bool CMatrixs::operator-=(const CMatrixs& other)
{
    arm_status status = arm_mat_sub_f32(&MatIns_, &other.MatIns_, &MatIns_);
    if (ARM_MATH_SUCCESS != status)
    {
        MakeZeroMatrix();
        return false;
    }
    return true;
}

/**
* @brief Floating-point matrix dot subtraction operator reload
* @param[in]    other ref to the second input matrix structure
* @return       Wheter function success
*/
bool CMatrixs::operator*=(float value)
{
    arm_status status = arm_mat_scale_f32(&MatIns_, value, &MatIns_);
    return (ARM_MATH_SUCCESS == status);
}

/**
* @brief Floating-point matrix cross subtraction operator reload
* @param[in]    other ref to the second input matrix structure
* @return       Wheter function success
*/
bool CMatrixs::operator*=(const CMatrixs& other) 
{
    arm_status status = arm_mat_mult_f32(&MatIns_, &other.MatIns_, &MatIns_);
    if (ARM_MATH_SUCCESS != status)
    {
        MakeZeroMatrix();
        return false;
    }
    return true;
}

/**
* @brief Floating-point matrix div operator reload
* @param[in]    other ref to the second input matrix structure
* @return       Wheter function success
*/
bool CMatrixs::operator/=(float value) 
{
    arm_status status = arm_mat_scale_f32(&MatIns_, (1.0f / value), &MatIns_);
    return (ARM_MATH_SUCCESS == status);
}

/**
* @brief Floating-point matrix transpose.
* @param[out] result reference to the output matrix
* @return       Wheter function success
*/
bool CMatrixs::Transpose(CMatrixs& result) const
{
    arm_status status  = arm_mat_trans_f32(&MatIns_, &result.MatIns_);
    if (ARM_MATH_SUCCESS != status)
    {
        result.MakeZeroMatrix();
        return false;
    }
    return true;
}

/**
* @brief Floating-point matrix inverse.
* @param[out]   result reference to the output matrix
* @return       Wheter function success
* @note    The origin matrix will become unit matrix after calculation
*/
bool CMatrixs::InvertGaussJordan(CMatrixs& result) const
{
	arm_status status = arm_mat_inverse_f32(&MatIns_, &result.MatIns_);
    if (ARM_MATH_SUCCESS != status)
    {
        result.MakeZeroMatrix();
        return false;
    }
    return true;
}

#if ENABLE_PRINT
#define STDIO_OUTPUT 1
const uint16_t PRINT_BUFF_LEN = 200;
static uint8_t printbuff[PRINT_BUFF_LEN];
#include <stdio.h>
bool CMatrixs::print(char* matname)
{
    uint16_t cnt = 0;
    cnt += sprintf((char*)(printbuff + cnt), "\t\t\t\t%s", matname);
    for (int i = 0; i < MatIns_.numRows; i++)
    {
        for (int j = 0; j < MatIns_.numCols; j++)
        {
            cnt += sprintf((char*)(printbuff + cnt), " %f", GetElement(i, j));
        }
    }
    cnt += sprintf((char*)(printbuff + cnt), "\r\n");
#if STDIO_OUTPUT
    puts((const char*)printbuff);
#else
    Console::Instance()->puts((const char*)printbuff);
#endif

    return false;
}

bool CMatrixs::printRaw(char* matname)
{
    uint16_t cnt = 0;
    cnt += sprintf((char*)(printbuff + cnt), "\t\t\t\t%s", matname);
    for (int i = 0; i < MatIns_.numRows; i++)
    {
        for (int j = 0; j < MatIns_.numCols; j++)
        {
            cnt += sprintf((char*)(printbuff + cnt), " %X", *(uint32_t*)&MatIns_.pData[j + i * MatIns_.numCols]);
        }
    }
    cnt += sprintf((char*)(printbuff + cnt), "\r\n");
#if STDIO_OUTPUT
    puts((const char*)printbuff);
#else
    Console::Instance()->puts((const char*)printbuff);
#endif
    return false;
}
#endif
