#pragma once

#include "Matrix.h"
#include <iostream>

namespace Crawfis
{
	namespace Math
	{
		static void PrintMatrix(const Matrix4& matrix)
		{
		  std::cout << "[ " << matrix[0] << " " << matrix[4] <<" " << matrix[8 ] << " " << matrix[12] << " ]\n"
					<< "[ " << matrix[1] << " " << matrix[5] <<" " << matrix[9 ] << " " << matrix[13] << " ]\n"
					<< "[ " << matrix[2] << " " << matrix[6] <<" " << matrix[10] << " " << matrix[14] << " ]\n" 
					<< "[ " << matrix[3] << " " << matrix[7] <<" " << matrix[11] << " " << matrix[15] << " ]\n";
		}
		static void PrintMatrix(const Matrix3& matrix)
		{
			std::cout << "[ " << matrix[0] << " " << matrix[3] <<" " << matrix[6] << " ]\n"
					  << "[ " << matrix[1] << " " << matrix[4] <<" " << matrix[7] << " ]\n"
					  << "[ " << matrix[2] << " " << matrix[5] <<" " << matrix[8] << " ]\n";  
		}
	}
}
