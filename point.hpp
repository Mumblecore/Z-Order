#ifndef POINT_HPP
#define POINT_HPP

#include <array>
#include <cmath>

template <int dim>
struct Point
{
    std::array<int,dim> coords;

    Point(int *c);
    Point();

    int max_coord();

    int operator [](int i) const {return coords[i];}
    int & operator [](int i) {return coords[i];}

    template <int U>
    friend std::ostream& operator<< (std::ostream&, const Point<U>&);
};

template <int dim>
Point<dim>::Point(int *c)
{
    for (int i = 0; i < dim; i++)
        coords[i] = c[i];
}

template <int dim>
Point<dim>::Point()
{
    for (int i = 0; i < dim; i++)
        coords[i] = 0;
}

template <int dim>
double distance(Point<dim> &A, Point<dim> &B)
{
	double dist = 0.0;
	for (int i = 0; i < dim; i++)
		dist += pow(B[i] - A[i], 2);
	dist = sqrt(dist);
	return dist;
}

// Retorna la mayor coordenada del punto
template <int dim>
int Point<dim>::max_coord()
{
	int max = coords[0];
	for (int i = 1; i < dim; i++)
		if (coords[i] > max)
			max = coords[i];
	return max;
}

template <int dim>
std::ostream& operator<<( std::ostream& os, const Point<dim>& P)
{
    os << "(" << P.coords[0];
    for (int i = 1; i < dim; i++)
        os << "," << P.coords[i];
    os << ")";
    return os;
}

#endif