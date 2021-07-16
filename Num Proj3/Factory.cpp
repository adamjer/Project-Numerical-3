#include "Factory.h"


namespace Interpolation
{
	Factory::Factory()
	{
		this->h = std::vector<double>();
		this->M = std::vector<double>(N + 1, 0.0);
		this->matrix = std::vector<std::vector<double>>();
		this->range = X[N] - X[0];
	}


	Factory::~Factory()
	{
	}

	void Factory::createH()
	{
		this->h.push_back(0.0);
		for (int i = 0; i < N; ++i)
		{
			this->h.push_back(X[i + 1] - X[i]);
		}
		this->h.push_back(0.0);
	}

	void Factory::fillMatrix()
	{
		std::vector<double> temp = std::vector<double>(N + 2, 0.0);
		for (int i = 0; i < N + 1; ++i)
		{
			this->matrix.push_back(temp);
			if (i == 0 || i == N)
			{
				this->matrix[i][i] = 2.0;
				//this->matrix[i][N + 1] = 0.0;
			}
			else
			{
				this->matrix[i][i - 1] = this->h[i] / (this->h[i] + this->h[i + 1]);
				this->matrix[i][i] = 2.0;
				this->matrix[i][i + 1] = this->h[i + 1] / (this->h[i] + this->h[i + 1]);
				this->matrix[i][N + 1] = (6 / (h[i] + h[i + 1])) * (((S21[i + 1] - S21[i]) / this->h[i + 1]) - ((S21[i] - S21[i - 1]) / this->h[i]));
			}	
		}
		//this->displayMatrix();
	}

	void Factory::interpolate(int n)
	{
		if (n < 0)
			n = 0;
		int i, j;
		double x = X[0], S, t = this->range / n;

		printf("Interpolation: %d\n", n);

		for (i = 0; i < n; ++i)
		{
			//szukanie przedzia³u
			for (j = 0; j < K - 1; ++j)
				if (x >= X[j] && x <= X[j + 1])
					break;

			S = (this->M[j] * pow(X[j + 1] - x, 3.0) / (6 * this->h[j + 1])) 
				+ (M[j + 1] * pow(x - X[j], 3.0) / (6 * this->h[j + 1]))
				+ ((((S21[j + 1] - S21[j]) / this->h[j + 1]) - (this->h[j + 1] / 6 * (this->M[j + 1] - this->M[j]))) * (x - X[j]))
				+ S21[j] 
				- (this->M[j] * pow(this->h[j + 1], 2.0) / 6);
			printf("%f\t%.15f\n", x, S);
			x += t;
		}
		printf("%f\t%.15f\n", X[K - 1], S21[K - 1]);
	}

	void Factory::solveGaussMatrix()
	{
		double coefficient = 0.0;

		//wybór kolumny
		for (int i = 0; i < N; ++i)
		{
			//wybór wiersza
			for (int j = i + 1; j < N + 1; ++j)
			{
				if (this->matrix[j][i] != 0.0)
				{
					coefficient = -this->matrix[j][i] / this->matrix[i][i];
					this->matrix[j][i] = 0.0;
					for (int k = i + 1; k <= N + 1; ++k)
					{
						this->matrix[j][k] += (coefficient * this->matrix[i][k]);
					}
				}
			}
		}
		//this->displayMatrix();
	}

	void Factory::init()
	{
		this->createH();
		this->fillMatrix();
		this->solveGaussMatrix();
		this->calculateM();
	}

	void Factory::displayMatrix()
	{
		puts("");
		for (int i = 0; i < N + 1; ++i)
		{
			for (int j = 0; j < N + 2; ++j)
				printf("%.2f ", this->matrix[i][j]);
			printf("\n");
		}
	}

	void Factory::calculateM()
	{
		double sum = 0.0;
		int i, j;
		for (i = N; i >= 0; --i)
		{
			sum = this->matrix[i][N + 1];
			for (j = N; j >= i + 1; --j)
			{
				if (this->M[j] != 0.0)
				{
					sum -= this->matrix[i][j] * this->M[j];
				}
			}
			this->M[i] = sum / this->matrix[i][i];
		}
	}
}