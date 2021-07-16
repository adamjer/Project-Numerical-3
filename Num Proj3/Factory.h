#pragma once
#include "Headers.h"


namespace Interpolation
{
	class Factory
	{
	public:
		Factory();
		~Factory();

		void init();
		void interpolate(int);

	private:
		std::vector<double> h, M;
		std::vector<std::vector<double>> matrix;
		double range;

		void createH();
		void calculateM();
		void fillMatrix();
		void solveGaussMatrix();
		void displayMatrix();
	};
}
