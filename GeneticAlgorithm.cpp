#include "GeneticAlgorithm.h"
#include <iostream>
#include <cTime>
#include <set>
#include "Utils.h"

GeneticAlgorithm::GeneticAlgorithm(int PopulationSize, int numberOfGenerations, int TournamentGroupSize , double CrossoverProbability
	, double MutationProbability) :
	mPopulationSize(PopulationSize), mGenerations(numberOfGenerations),
	mTournamentGroupSize(TournamentGroupSize) ,
	mCrossoverProbability(CrossoverProbability),
	mMutationProbability(MutationProbability)
{
}

solution GeneticAlgorithm::run(int numberOfBits, int** adjacency)
{
	

	srand(time(NULL)); //To get actual random numbers

	//1st generation 
	std::vector<solution> currentGeneration;

	for (int i = 0; i < mPopulationSize; i++)
	{
		currentGeneration.push_back(solution(numberOfBits, adjacency));
	}

	std::cout << "First Generation\n";

	for (solution s : currentGeneration)
	{
		std::cout << s.toString() << "\n";
	}


	//elitism , is saving always the best from each generation
	solution best = currentGeneration[0];
	double maxFitness = currentGeneration[0].fitness();
	int indexWorst = 0;
	double worstSolution;
	bool isBestInCurrentAllReady = false;
	
	//to find the fittest from the initial generation
	for (solution s : currentGeneration)
	{
		double newFitness = s.fitness();
		if (newFitness > maxFitness)
		{
			maxFitness = newFitness;
			best = s;
		}
	}

	std::cout << "\n Best initial Gen " << best.toString() << "\n";

	//tournament crossover 
	for (int i = 0; i < mGenerations; i++)
	{
		std::vector<solution> crossedSolutions = tournamentCrossover(currentGeneration);

		//std::cout << "Crossed Solutions n_: " << i << " \n";

		for (solution s : crossedSolutions)
		{
			//std::cout << s.toString() << "\n";
			s.Mutate(mMutationProbability);
		}

		currentGeneration = crossedSolutions;
		
		//elitism , is saving always the best from each generation
		//to find the fittest in the group
		isBestInCurrentAllReady = false;
		worstSolution = currentGeneration[0].fitness();
		for (size_t i = 0; i < currentGeneration.size() ; i++)
		{
			solution s = currentGeneration[i];
			double newFitness = s.fitness();
			if (newFitness > maxFitness)
			{
				isBestInCurrentAllReady = true;
				maxFitness = newFitness;
				best = s;
			}
			if (newFitness < worstSolution) //the best way to do elitism is passing it to the nextGeneration
			{
				worstSolution = newFitness;
				indexWorst = i;
			}

		}
		//the best way to do elitism is passing it to the nextGeneration
		if (!isBestInCurrentAllReady) //only passes if i's not in it already
		{
			currentGeneration[indexWorst] = best; //in this case i'm performing elitism by replacing the indexWorst by the best
		}												 

		std::cout << "\n Best " << i  << " gen" << best.toString() << "\n";
	}


	

	return best;
}


solution GeneticAlgorithm::tournamentWinner(std::vector<solution> const& currentGeneration)
{
	std::vector<solution> candidates;
	std::set<int> randomNumbers1 = randomDistinctNumbers(mPopulationSize, mTournamentGroupSize);
	for (int rn : randomNumbers1)
	{
		candidates.push_back(
		currentGeneration[rn]
		);
	}

	solution bestCandidate = candidates[0];
	double maxFitness = candidates[0].fitness();

	//to find the fittest in the group
	for (solution s : candidates)
	{
		double newFitness = s.fitness();
		if (newFitness > maxFitness)
		{
			maxFitness = newFitness;
			bestCandidate = s;
		}
	}

	return bestCandidate;
}

//tournament crossover 
std::vector<solution> GeneticAlgorithm::tournamentCrossover(std::vector<solution> const& currentGeneration)
{
	std::vector<solution> newSolutions;

	//we will keep adding to this vector until we have a full generation 
	while (newSolutions.size() < mPopulationSize)
	{
		//candidates for tournament
		solution winner1 = tournamentWinner(currentGeneration);
		solution winner2 = tournamentWinner(currentGeneration);

		//std::cout << "Crossing the winners " << winner1.toString() << "&" << winner2.toString();

		//perform crossover
		std::vector<solution> children = winner1.single_point_crossover(winner2, mCrossoverProbability);
		
		newSolutions.push_back(children[0]);
		newSolutions.push_back(children[1]);
		//std::cout << "Children " << children[0].toString() << "&"	<< children[1].toString() << "\n";
	}

	return newSolutions;
}

