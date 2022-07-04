#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "point.hpp"
#include <vector>

template <int dim>
struct Queue
{
	std::vector<Point<dim> > p_que;
	std::vector<double> 	d_que;
	int tam;
	Queue(int t);
	void insert(Point<dim> P, double dist);
};

template <int dim>
Queue<dim>::Queue(int t)
{
	tam = t;
}

template <int dim>
void Queue<dim>::insert(Point<dim> P, double dist)
{
	if (p_que.empty())
	{
		p_que.push_back(P);
		d_que.push_back(dist);
		return;
	}
	typename std::vector<Point<dim> >::iterator p_it;
	std::vector<double>::iterator d_it;

	p_it = p_que.begin();
	d_it = d_que.begin();
	
	for (int i = 0; i < d_que.size(); i++)
	{
		if (dist < d_que[i])
		{
			p_que.insert(p_it + i, P);
			d_que.insert(d_it + i, dist);
			if (d_que.size() > tam)
			{
				p_que.pop_back();
				d_que.pop_back();
			}
			return;
		}
	}

	if (d_que.size() < tam)
	{
		p_que.push_back(P);
		d_que.push_back(dist);
	}

}

#endif