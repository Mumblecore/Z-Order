#include <iostream>
#include <stdlib.h>
#include <random>
#include <cmath>
#include <vector>
#include <chrono>

#include "point.hpp"
#include "queue.hpp"

#define ui64 uint64_t

typedef std::chrono::high_resolution_clock myclock;
myclock::time_point beginning = myclock::now();

// Calcula el número necesario de bits para representar x
int bit_length(int x)
{
	int max_bit = 1;
	while (x)
	{
		x >>= 1;
		max_bit++;
	}
	return max_bit;
}

// el mayor numero es 2^(dim * lg (arg max(p)))
template <int dim>
int z_order(Point<dim> &P)
{
	if (dim == 0)
		return -1;

	int max_bit = bit_length(P.max_coord());

	// realizar el algoritmo de Morton
	int result = 0;
	for (int i = max_bit - 1; i >= 0; i--)
		for (int j = dim - 1; j >= 0; j--)
		{
			int tmp = (P[j] >> i) & 1;
			result <<= 1;
			result += tmp;
		}
	return result;
}

// Halla los k vecinos más cercanos de data[P] en
// 'data' y los almacena en 'dest' de forma exhaustiva
template <int dim>
void knn(std::vector<Point<dim> > & data, Queue<dim> &dest, int P)
{
	for (int i = 0; i < data.size(); i++)
	{
		if (i == P) continue;
		double dist = distance<dim>(data[i], data[P]);
		dest.insert(data[i], dist);
	}
}

template <int d>
int compare(Queue<d> Q1, Queue<1> Q2)
{
	int size = Q1.tam;
	int hints = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (z_order<d>(Q1.p_que[i]) == Q2.p_que[j].coords[0])
				hints++;

	return 100*hints/size;
}

int main(int argc, char *argv[])
{
	// Generar un vector con 5000 puntos 10-D
	myclock::duration d = myclock::now() - beginning;
  	unsigned seed = d.count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> dis(0, 7);
	std::vector<Point<10> > mydata;
	int number[10];
	for (int i = 0; i < 5000; i++)
	{
		for (int j = 0; j < 10; j++)
			number[j] = dis(generator);
		mydata.push_back(number);
	}

	// Mapear los 5000 puntos a 1-D con Z-order
	std::vector<Point<1> > z_data;
	for (int i = 0; i < 5000; i++)
	{
		number[0] = z_order<10>(mydata[i]);
		z_data.push_back(number);
	}

	// Capturar 10 elementos
	std::uniform_int_distribution<int> dis2(0, 4999);
	int elems[10];
	for (int i = 0; i < 10; i++)
		elems[i] = dis2(generator);

	// Hallar los k más cercanos en ambas dimensiones
	int promedio = 0;
	for (int i = 0; i < 10; i++)
	{
		std::cout << "Punto #" << elems[i] << ": ";
		std::cout << mydata[elems[i]] << "->" << z_data[elems[i]] << std::endl;
		Queue<10> results10d(atoi(argv[1]));
		Queue<1>  results1d(atoi(argv[1]));
		knn<10>(mydata, results10d, elems[i]);
		knn<1>(z_data, results1d, elems[i]);

		// Hallar el porcentaje de similitud entre las busquedas

		// Descomentar para ver los puntos encontrados
		// std::cout << "10D\t\t1D\n";
		// for (int j = 0; j < atoi(argv[1]); j++)
		// {
		// 	std::cout << z_order<10>(results10d.p_que[j]) << "\t";
		// 	std::cout << results1d.p_que[j][0] << std::endl;
		// }
		int comp = compare<10>(results10d,results1d);
		std::cout << "Similitud: " << comp << "%\n";
		promedio += comp;
	}

	// Imprimir promedio
	std::cout << "Promedio: " << promedio/10 << std::endl;
}
