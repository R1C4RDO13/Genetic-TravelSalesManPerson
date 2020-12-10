#pragma once
#include "solution.h"

class GeneticAlgorithm
{

public:
	GeneticAlgorithm(int PopulationSize , 
		int numberOfGenerations, 
		int TournamentGroupSize,
		double CrossoverProbability,
		double MutationProbability
		);
	solution run(int numberOfBits , int** adjacency );

private:
	int mPopulationSize , mGenerations;
	int mTournamentGroupSize;

	solution tournamentWinner(std::vector<solution> const& currentGeneration);
	std::vector<solution> tournamentCrossover(std::vector<solution> const &currentGeneration);


	double mCrossoverProbability , mMutationProbability;
};

