#pragma once

#include <vector>
#include <string>
//the solution class will wrap around the bits
class solution
{
public:
	solution(int number_of_cities, int** adjacency);
	solution(int number_of_cities, int** adjacency , std::vector<int> cities );
	std::string toString() const;
	double fitness() const;
	std::vector<solution> single_point_crossover(solution Other, double CrossoverProbability);
	void Mutate(double mutationProbability);

private:
	
	int number_of_cities;
	int** adjacency;
	std::vector<int> cities; //chromosomes



};



