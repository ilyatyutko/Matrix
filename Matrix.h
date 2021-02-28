#pragma once
#include "Matrix_Additional.h"
#include "ErrorCatch.h"
#include <string>

namespace LinearAlgebra {

	using ErrorList::ErrorCatch;

	struct NullRow
	{
	public:
		int row;
		int number;
		bool active = false;
		NullRow() : row(0), number(0) {}
		NullRow(int row, int number) : row(row), number(number) {}
		void operator=(NullRow a) { this->row = a.row; this->number = a.number; }
	};

	struct NullColumn
	{
	public:
		int column;
		int number;
		bool active = false;
		NullColumn() : column(0), number(0) {}
		NullColumn(int column, int number) : column(column), number(number) {}
		void operator=(NullColumn a) { this->column = a.column; this->number = a.number; }
	};

	class Matrix
	{
	public:
		Matrix(int rows, int columns);
		Matrix(const Matrix &b);
		~Matrix();

		void readFrom(const char* fileName);
		void readFrom(const std::string &fileName);
		void randomFulling(int minValue, int maxValue);

		void writeTo(const char* filename);
		void writeTo(const std::string &filename);

		static void writeTo(const Matrix &b, const char* filename);
		static void writeTo(const Matrix &b, const std::string &filename);

		void writeTable(const char* filename);
		void writeTable(const std::string &filename);

		static void writeTable(Matrix &b, const char* filename);
		static void writeTable(Matrix &b, const std::string &filename);

		double at(int row, int column);
		
		bool isSquare();
		bool isDownTriangle();
		bool isUpTriangle();
		bool isTriangle();
		//bool isOrthogonal();
		bool isDiagonal();
		bool isNullMatrix();

		void operator=(const Matrix &b);
		Matrix operator+(const Matrix &b);
		void operator+=(const Matrix &b);
		Matrix operator-(const Matrix &b);
		void operator-=(const Matrix &b);
		Matrix operator*(const Matrix &b);
		void operator*=(const Matrix &b);
		Matrix operator*(double m);
		void operator*=(double m);
		Matrix operator*(int m);
		void operator*=(int m);

		void multiplyRow(int which, double m);
		void multiplyRow(int which, int m);
		void multiplyColumn(int which, double m);
		void multiplyColumn(int which, int m);

		void addRow(int to, int which, double multiplier = 1);
		void addColumn(int to, int which, double multiplier = 1);

		void subtractRow(int from, int which, double multiplier = 1);
		void subtractColumn(int from, int which, double multiplier = 1);

		Matrix transpose();
		void transpose_self();
		Matrix erase(int row, int column);

		double getDeterminant();

		double algApplied(int row, int column);

		Matrix matrixOfAlgApplied();
		Matrix inversed();

	private:
		double** a;
		int rows;
		int columns;

		void throwError(Errors s);
		void newSize(int rows, int columns);
	public:
		int maxElemLength();
		NullRow rowWithMaxNulls();
		NullColumn columnWithMaxNulls();
	};
}