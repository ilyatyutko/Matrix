#include "Matrix.h"
#include <fstream>
#include <iomanip>

namespace LinearAlgebra {

	ErrorCatch logger("MatrixLib", "files\\Matrix.txt");
	bool aroundNull(double s)
	{
		if (-0.0001 < s && s < 0.0001)
			return true;
		else
			return false;
	}

	Matrix::Matrix(int rows, int columns) : rows(rows), columns(columns), a(new double*[rows])
	{
		if (rows < 1 || columns < 1)
		{
			this->throwError(WRONGINITIALIZATIONSIZE);
			return;
		}
		for (int i = 0; i < rows; ++i)
			a[i] = new double[columns];
	}
	Matrix::Matrix(const Matrix &b) : rows(b.rows), columns(b.columns), a(new double*[b.rows])
	{
		for (int i = 0; i < rows; ++i)
			a[i] = new double[b.columns];
		this->operator=(b);
	}
	Matrix::~Matrix()
	{
		for (int i = 0; i < rows; ++i)
			delete[] a[i];
		delete[] a;

		int i = 0;
		++i;
	}

	void Matrix::newSize(int rows, int columns)
	{
		for (int i = 0; i < this->rows; ++i)
			delete[] a[i];
		delete[] a;
		this->rows = rows;
		this->columns = columns;
		this->a = new double*[rows];
		for (int i = 0; i < rows; ++i)
			a[i] = new double[columns];
	}

	void Matrix::readFrom(const char* fileName)
	{
		std::ifstream input;
		input.open(fileName);
		if (input.is_open())
			for (int m = 0; m < this->rows; ++m)
				for (int n = 0; n < this->columns; ++n)
					input >> this->a[m][n];
		else
			throwError(FILENOTFOUND);
	}
	void Matrix::readFrom(const std::string &fileName)
	{
		std::ifstream input;
		input.open(fileName);
		if (input.is_open())
			for (int m = 0; m < this->rows; ++m)
				for (int n = 0; n < this->columns; ++n)
					input >> this->a[m][n];
		else
			throwError(FILENOTFOUND);
		input.close();
	}
	void Matrix::randomFulling(int minValue, int maxValue)
	{
		for (int m = 0; m < this->rows; ++m)
			for (int n = 0; n < this->columns; ++n)
				this->a[m][n] = rand() % (minValue + maxValue + 2) - minValue - 1;
	}

	void Matrix::writeTo(const char* filename)
	{
		std::ofstream output;
		output.open(filename, std::ios_base::app);
		for (int m = 0; m < this->rows; ++m)
		{
			for (int n = 0; n < this->columns; ++n)
				output << this->a[m][n] << ' ';
			output << std::endl;
		}
		output << std::endl;
		output.close();
	}
	void Matrix::writeTo(const std::string &filename)
	{
		std::ofstream output;
		output.open(filename, std::ios_base::app);
		for (int m = 0; m < this->rows; ++m)
		{
			for (int n = 0; n < this->columns; ++n)
				output << this->a[m][n] << ' ';
			output << std::endl;
		}
		output << std::endl;
		output.close();
	}

	void Matrix::writeTo(const Matrix &b, const char* filename)
	{
		std::ofstream output;
		output.open(filename, std::ios_base::app);
		for (int m = 0; m < b.rows; ++m)
		{
			for (int n = 0; n < b.columns; ++n)
				output << b.a[m][n] << ' ';
			output << std::endl;
		}
		output << std::endl;
		output.close();
	}
	void Matrix::writeTo(const Matrix &b, const std::string &filename)
	{
		std::ofstream output;
		output.open(filename, std::ios_base::app);
		for (int m = 0; m < b.rows; ++m)
		{
			for (int n = 0; n < b.columns; ++n)
				output << b.a[m][n] << ' ';
			output << std::endl;
		}
		output << std::endl;
		output.close();
	}

	void Matrix::writeTable(const char* filename)
	{
		std::ofstream output;
		output.open(filename, std::ios_base::app);
		int len = this->maxElemLength();
		for (int m = 0; m < this->rows; ++m)
		{
			for (int n = 0; n < this->columns; ++n)
			{
				if(-0.0001 < this->a[m][n] && this->a[m][n] < 0.0001)
					output << std::setw(len + 1) << "~0";
				else
					output << std::setw(len + 1) << std::setprecision(4) << this->a[m][n];
			}
			output << std::endl;
		}
		output << std::endl;
		output.close();
	}
	void Matrix::writeTable(const std::string &filename)
	{
		std::ofstream output;
		output.open(filename, std::ios_base::app);
		int len = this->maxElemLength();
		for (int m = 0; m < this->rows; ++m)
		{
			for (int n = 0; n < this->columns; ++n)
			{
				if (-0.0001 < this->a[m][n] && this->a[m][n] < 0.0001)
					output << std::setw(len + 1) << "~0";
				else
					output << std::setw(len + 1) << std::setprecision(3) << this->a[m][n];
			}
			output << std::endl;
		}
		output << std::endl;
		output.close();
	}

	void Matrix::writeTable(Matrix &b, const char* filename)
	{
		b.writeTable(filename);
	}
	void Matrix::writeTable(Matrix &b, const std::string &filename)
	{
		b.writeTable(filename);
	}

	double Matrix::at(int row, int column)
	{
		if (row <= this->rows && column <= this->columns)
			return this->a[this->rows][this->columns];
		else 
			throwError(INCORRECTCELL);
		return 0.0;
	}

	void Matrix::operator=(const Matrix &b)
	{
		if (b.rows != this->rows || b.columns != this->columns)
		{
			this->newSize(b.rows, b.columns);
		}
		for (int m = 0; m < this->rows; ++m)
			for (int n = 0; n < this->columns; ++n)
				this->a[m][n] = b.a[m][n];
	}
	Matrix Matrix::operator+(const Matrix &b)
	{
		Matrix newone(b);
		if (b.rows == this->rows && b.columns == this->columns)
		{
			for (int m = 0; m < this->rows; ++m)
				for (int n = 0; n < this->columns; ++n)
					newone.a[m][n] = this->a[m][n] + b.a[m][n];
		}
		else
			throwError(DIFFERENTSIZES);
		return newone;
	}
	void Matrix::operator+=(const Matrix &b)
	{
		if (b.rows == this->rows && b.columns == this->columns)
		{
			for (int m = 0; m < this->rows; ++m)
				for (int n = 0; n < this->columns; ++n)
					this->a[m][n] += b.a[m][n];
		}
		else
			throwError(DIFFERENTSIZES);
	}
	Matrix Matrix::operator-(const Matrix &b)
	{
		Matrix newone(*(this));
		if (b.rows == this->rows && b.columns == this->columns)
		{
			for (int m = 0; m < this->rows; ++m)
				for (int n = 0; n < this->columns; ++n)
					newone.a[m][n] = this->a[m][n] - b.a[m][n];
		}
		else
			throwError(DIFFERENTSIZES);
		return newone;
	}
	void Matrix::operator-=(const Matrix &b)
	{
		if (b.rows == this->rows && b.columns == this->columns)
		{
			for (int m = 0; m < this->rows; ++m)
				for (int n = 0; n < this->columns; ++n)
					this->a[m][n] -= b.a[m][n];
		}
		else
			throwError(DIFFERENTSIZES);
	}

	Matrix Matrix::operator*(const Matrix &b)
	{
		Matrix newone(this->rows, b.columns);
		if (b.rows == this->columns)
		{
			for (int m = 0; m < this->rows; ++m)
				for (int n = 0; n < b.columns; ++n)
				{
					newone.a[m][n] = 0;
					for (int i = 0; i < this->columns; ++i)
						newone.a[m][n] += this->a[m][i] * b.a[i][n];
				}
		}
		else
			throwError(IMPOSSIBLEMATRIXMULTIPLUCATION);
		return newone;
	}
	void Matrix::operator*=(const Matrix &b)
	{
		if (b.rows == this->columns)
		{
			*(this) = this->operator*(b);
		}
		else
			throwError(IMPOSSIBLEMATRIXMULTIPLUCATION);
	}
	Matrix Matrix::operator*(double multiplier)
	{
		for (int m = 0; m < this->rows; ++m)
			for (int n = 0; n < this->columns; ++n)
			{
				this->a[m][n] *= multiplier;
			}
		return *(this);
	}
	void Matrix::operator*=(double m)
	{
		this->operator=(this->operator*(m));
	}
	Matrix Matrix::operator*(int multiplier)
	{
		for (int m = 0; m < this->rows; ++m)
			for (int n = 0; n < this->columns; ++n)
			{
				this->a[m][n] *= multiplier;
			}
		return*(this);
	}
	void Matrix::operator*=(int m)
	{
		this->operator=(this->operator*(m));
	}

	void Matrix::multiplyRow(int which, double m)
	{
		for (int i = 0; i < this->columns; ++i)
			this->a[which][i] *= m;
	}
	void Matrix::multiplyRow(int which, int m)
	{
		for (int i = 0; i < this->columns; ++i)
			this->a[which][i] *= m;
	}
	void Matrix::multiplyColumn(int which, double m)
	{
		for (int i = 0; i < this->rows; ++i)
			this->a[i][which] *= m;
	}
	void Matrix::multiplyColumn(int which, int m)
	{
		for (int i = 0; i < this->rows; ++i)
			this->a[i][which] *= m;
	}

	void Matrix::addRow(int to, int which, double multiplier)
	{
		for (int i = 0; i < this->columns; ++i)
			this->a[to][i] += this->a[which][i] * multiplier;
	}
	void Matrix::addColumn(int to, int which, double multiplier)
	{
		for (int i = 0; i < this->rows; ++i)
			this->a[i][to] += this->a[i][which] * multiplier;
	}

	void Matrix::subtractRow(int from, int which, double multiplier)
	{
		for (int i = 0; i < this->columns; ++i)
			this->a[from][i] -= this->a[which][i] * multiplier;
	}
	void Matrix::subtractColumn(int from, int which, double multiplier)
	{
		for (int i = 0; i < this->rows; ++i)
			this->a[i][from] -= this->a[i][which] * multiplier;
	}

	Matrix Matrix::transpose()
	{
		Matrix newone(this->columns, this->rows);
		for (int x = 0; x < this->rows; ++x)
			for (int y = 0; y < this->columns; ++y)
				newone.a[y][x] = this->a[x][y];
		return newone;
	}

	void Matrix::transpose_self()
	{
	
		double temporary;
		for (int x = 0; x < this->rows; ++x)
			for (int y = 0; y < this->columns; ++y)
			{
				temporary = this->a[x][y];
				this->a[x][y] = this->a[y][x];
				this->a[y][x] = temporary;
			}
	}

	bool Matrix::isSquare()
	{
		return (this->rows == this->columns);
	}
	bool Matrix::isDownTriangle()
	{
		if (!this->isSquare()) return false;
		for(int n = 0; n < this->columns; ++n)
			for(int m = n + 1; m < this->rows; ++m)
				if (!aroundNull(this->a[m][n]))
					return false;
		return true;
	}
	bool Matrix::isUpTriangle()
	{
		if (!this->isSquare()) return false;
		for (int n = 0; n < this->columns; ++n)
			for (int m = 0; m < n; ++m)
				if (!aroundNull(this->a[m][n]))
					return false;
		return true;
	}
	bool Matrix::isTriangle()
	{
		return this->isUpTriangle() || this->isDownTriangle();
	}
	bool Matrix::isDiagonal()
	{
		return this->isDownTriangle() && this->isUpTriangle();
	}
	bool Matrix::isNullMatrix()
	{
		for (int m = 0; m < this->rows; ++m)
			for (int n = 0; n < this->columns; ++n)
				if (!aroundNull(this->a[m][n]))
					return false;
		return true;
	}

	Matrix Matrix::erase(int row, int column)
	{
		Matrix newone(this->rows - 1, this->columns - 1);
		bool getRow = false;
		bool getColumn = false;
		for (int m = 0; m < this->rows; ++m)
		{
			if (m == row)
			{
				getRow = true;
				continue;
			}
			getColumn = false;
			for (int n = 0; n < this->columns; ++n)
			{
				if (n == column)
				{
					getColumn = true; 
					continue;
				}
				newone.a[m - getRow][n - getColumn] = this->a[m][n];
			}
		}
		return newone;
	}

	void Matrix::throwError(Errors s)
	{
		switch (s)
		{
		case FILENOTFOUND:logger.setError("FILE NOT FOUND");
			break;
		case INCORRECTCELL:logger.setError("INCORRECT CELL's POSITION");
			break;
		case DIFFERENTSIZES:logger.setError("DIFFERENT MATRIX' SIZES");
			break;
		case IMPOSSIBLEMATRIXMULTIPLUCATION:logger.setError("IMPOSSIBLE MATRIX MULTIPLUCATION - INCORRECT SIZES");
			break;
		case NOTSQUARENODETERMINER:logger.setError("MATRIX IS NOT SQUARE NO DETERMINER");
			break;
		default:logger.setError("SOMETHING HAD GONE WRONG");
			break;
		}
	}
	int Matrix::maxElemLength()
	{
		int max = 0;
		for (int m = 0; m < this->rows; ++m)
			for (int n = 0; n < this->columns; ++n)
			{
				if (-1000000000000 < this->a[m][n] && this->a[m][n] < 1000000000000) max = 18;
				if (-1000000000 < this->a[m][n] && this->a[m][n] < 1000000000) max = 15;
				if (-1000000 < this->a[m][n] && this->a[m][n] < 1000000) max = 12;
				if (-1000 < this->a[m][n] && this->a[m][n] < 1000) max = 9;
			}
		return max;
	}
	NullRow Matrix::rowWithMaxNulls()
	{
		int max = 0;
		int row = 0;
		for (int m = 0; m < this->rows; ++m)
		{
			int localNum = 0;
			for(int n = 0; n < this->columns; ++n)
				if (aroundNull(this->a[m][n]))
					++localNum;
			if (localNum > max)
			{
				row = m;
				max = localNum;
			}
		}
		NullRow newone(row, max);
		return newone;
	}
	NullColumn Matrix::columnWithMaxNulls()
	{
		int max = 0;
		int column = 0;
		for (int n = 0; n < this->columns; ++n)
		{
			int localNum = 0;
			for (int m = 0; m < this->rows; ++m)
				if (aroundNull(this->a[m][n]))
					++localNum;
			if (localNum > max)
			{
				column = n;
				max = localNum;
			}
		}
		NullColumn newone(column, max);
		return newone;
	}

	double Matrix::getDeterminant()
	{
		if (!(this->isSquare()))
		{
			this->throwError(NOTSQUARENODETERMINER);
			return 0;
		}
		if (this->rows < 4)
		{
			if (this->rows == 3)
				return a[0][0] * a[1][1] * a[2][2] + a[0][1] * a[1][2] * a[2][0] + a[0][2] * a[1][0] * a[2][1] - a[0][0] * a[1][2] * a[2][1] - a[0][1] * a[1][0] * a[2][2] - a[0][2] * a[1][1] * a[2][0];
			else if (this->rows == 2)
				return a[0][0] * a[1][1] - a[0][1] * a[1][0];
			else
				return a[0][0];
		}
		else
		{
			double determinant = 0;
			int sign = 1;
			NullRow r = this->rowWithMaxNulls();
			NullColumn c = this->columnWithMaxNulls();
			if (r.number > c.number)
			{
				for (int i = 0; i < this->rows; ++i)
				{
					if (this->a[r.row][i] == 0) continue;
					Matrix a(this->erase(r.row, i));
					sign = (r.row + i + 1) % 2 * 2 - 1;
					determinant += this->a[r.row][i] * a.getDeterminant() * sign;
				}
			}
			else
			{
				for (int i = 0; i < this->columns; ++i)
				{
					if (this->a[i][c.column] == 0) continue;
					Matrix a(this->erase(i, c.column));
					sign = (c.column + i + 1) % 2 * 2 - 1;
					determinant += this->a[i][c.column] * a.getDeterminant() * sign;
				}
			}
			return determinant;
		}
	}

	double Matrix::algApplied(int row, int column)
	{
		Matrix t(*(this));
		t = t.erase(row,column);
		return t.getDeterminant() * ((row + column + 1)%2*2-1);
	}

	Matrix Matrix::matrixOfAlgApplied()
	{
		Matrix newone(this->rows, this->columns);
		for (int m = 0; m < this->rows; ++m)
			for (int n = 0; n < this->columns; ++n)
				newone.a[n][m] = this->algApplied(m,n);
		return newone;
	}

	Matrix Matrix::inversed()
	{
		double d = 1.0 / this->getDeterminant();
		Matrix newone(this->matrixOfAlgApplied());
		newone *= d;
		return newone;
	}
}