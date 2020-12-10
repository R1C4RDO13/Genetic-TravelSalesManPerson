// TravelSalesManPerson.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>


#include "GeneticAlgorithm.h"
#include "solution.h"
std::string file = "graph.txt";



//params
int populationSize = 10;
//int low = 0, high = 4;
int generations = 10; //não vale a pena muitas gerações
int GroupsSizeForTournament = 3; //quanto mais pequeno até melhor
double CrossoverProbability = 0.7;
double MutationProbability = 0.01;


int main()
{
    //(1) read files distances 'graph.txt'
	std::fstream data_file;

	data_file.open(file);
    if (!data_file.is_open()) //error opening the file
    {
		throw std::runtime_error("Couldn't open the file");
    }

	int number_of_cities;
	data_file >> number_of_cities; //the first line in the file is the number of cities

	std::cout << "Number of cities found: " << number_of_cities << std::endl;

	int** adjacency = new int* [number_of_cities]; // initializes an array to receive the distances between cities

	//(2) initializes the adjacency array with the huge number


	for(int i = 0 ; i < number_of_cities ; i ++)
	{
		adjacency[i] = new int[number_of_cities];

		for (int j = 0; j < number_of_cities; j++)
		{
			if (i == j)
				adjacency[i][j] = 0; //the distance between a city and self is zero
			else
				adjacency[i][j] = INT_MAX;
		}
	}

	//(3) reads the rest of the file, the distances between cities ... IN_FILE -> from to distance
    while (data_file.good()) //checks f the file reach the end
    {
		int from, to, distance;
		data_file >> from;
		data_file >> to;
		data_file >> distance;
		std::cout << "From " << from << " To " << to << "distance = " << distance << std::endl;
		adjacency[from - 1][to - 1] = distance;
		adjacency[to - 1][from - 1] = distance;
    }
	data_file.close();

	//prints the matrix.. .. ... 
	for (int i = 0; i < number_of_cities; i++)
	{
		for (int j = 0; j < number_of_cities; j++)
		{
			std::cout << adjacency[i][j] << ' ';
		}
		std::cout << '\n';
	}

	std::cout << "Hello World!\n";
	GeneticAlgorithm ga(populationSize, generations,
		GroupsSizeForTournament, CrossoverProbability, MutationProbability);

	solution bestSolution = ga.run(number_of_cities,adjacency);

	std::cout << "\nBest Solution - " << bestSolution.toString() << "\n";



	//TODO: catch exceptions and deallocate the arrays in those cases as well
	for (int i = 0; i < number_of_cities; i++) {
		delete[] adjacency[i];
	}
	delete[] adjacency;

	return 0;
	
}


