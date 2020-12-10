#include "solution.h"
#include <sstream>
#include "Utils.h"
#include <iostream>
#include  <algorithm>


solution::solution(int number_of_cities, int** adjacency) : number_of_cities(number_of_cities), adjacency(adjacency) //this initializes automatically the values
{
	cities.reserve(number_of_cities); // we do this to avoid relocate the vector
	for (size_t i = 0; i < number_of_cities; i++)
		cities.push_back(i); //random number from 0 - number_of_cities
	
	std::random_shuffle(cities.begin(), cities.end()); // #include  <algorithm> randomizes this array

}

solution::solution(int number_of_cities, int** adjacency, std::vector<int> cities) : number_of_cities(number_of_cities), adjacency(adjacency) , cities(cities)
//this initializes automatically the values
{

}

//to return the solution decoded /to print the solution 
std::string solution::toString() const
{
	std::ostringstream stream;
	stream << "[";
	for (int bit : cities)
	{
		stream << bit << " ";
	}
	stream << "] fitness = " << fitness();
	return stream.str();
}


//In short, Himmelblau's function is this:

//tsp FITNESS
double solution::fitness() const	//function to minimize
{
	int total_travel_distance = 0;

	//cities 1 2 3 4
	for(int i = 0 ; i < number_of_cities -1 ; i++)
	{
		int from = cities[i];
		int to = cities[i + 1];
		total_travel_distance += adjacency[to][from];
	}
	total_travel_distance += adjacency[0][number_of_cities - 1];
	return (-1) * total_travel_distance;

}


//
////00110001 => double?
//
//Point solution::bitsToDouble() const
//{
//
//	double PrecX = precision(nLow.X, nHigh.X, nNumberOfBits /2);
//	double PrecY = precision(nLow.Y, nHigh.Y, nNumberOfBits /2);
//
//	//		x		   |	y
//	//( 0 0 1 1 0 0 1 0| 1 1 1 0 0 1 0 1)
//
//	double Xtemp  = 0;
//	
//	for (int i = 0; i < nNumberOfBits / 2; i++)	//conversion of X
//	{
//		Xtemp = Xtemp + pow(2, i) * nBits[i];		//conversion from base 2 to base 10
//	}
//
//	double Ytemp = 0;
//
//	for (int i = nNumberOfBits / 2; i < nNumberOfBits ; i++) //conversion of Y
//	{
//		Ytemp = Ytemp + pow(2, i - nNumberOfBits / 2) * nBits[i];		//conversion from base 2 to base 10
//	}
//
//	Xtemp = Xtemp * PrecX + nLow.X;
//	Ytemp = Ytemp * PrecY + nLow.Y;
//	Point p;
//	p.X = Xtemp;
//	p.Y = Ytemp;
//
//	return p;
//}

std::vector<solution> solution::single_point_crossover (solution Other, double CrossoverProbability)
{

	bool cross = randomProbability(CrossoverProbability);
	//std::cout << "Crossed ? -> " << cross;
	if (cross)
	{
		//simgle point
		int crossPoint = rand() % number_of_cities;

		std::vector<int> bits1;
		std::vector<int> bits2;

		//copies the first part of this solution to the first crossover vector
		std::copy(this->cities.begin(), this->cities.begin() + crossPoint,
			std::back_inserter(bits1));

		int currentPos = crossPoint;

		//can not add a city if it already exists 
		while (bits1.size() < number_of_cities)
		{
			int city = Other.cities[currentPos];
			bool found = false;
			
			for (int cit : bits1)
			{
				if (cit == city)
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				bits1.push_back(city);
			}
			currentPos++;
			if (currentPos >= number_of_cities )
			{
				currentPos = 0;
			}
		}
		
		//std::copy(Other.nBits.begin() + crossPoint, Other.nBits.end(),
			//std::back_inserter(bits1));
		//
		//copies the first part of the other solution to the second crossover vector
		std::copy(Other.cities.begin(), Other.cities.begin() + crossPoint,
			std::back_inserter(bits2));
//		std::copy(this->nBits.begin() + crossPoint, this->nBits.end(),
			//std::back_inserter(bits2));

		while (bits2.size() < number_of_cities)
		{
			int city = this->cities[currentPos];
			bool found = false;

			for (int cit : bits2)
			{
				if (cit == city)
				{
					found = true;
				}
			}
			if (!found)
			{
				bits2.push_back(city);
			}
			currentPos++;
			if (currentPos > number_of_cities - 1)
			{
				currentPos = 0;
			}
		}
		
		solution child1{ number_of_cities , adjacency , bits1 };

		solution child2{ number_of_cities , adjacency , bits2 };


		return { child1 , child2 };
		/*int half = (int)number_of_cities / 2;
		int crossPoint1 = rand() % half;
		int crossPoint2 = (rand() % half) + half;


		std::vector<int> bits1;
		std::vector<int> bits2;

		//1 Point X
		std::copy(this->cities.begin(), this->cities.begin() + crossPoint1,
			std::back_inserter(bits1));


		
		std::copy(Other.nBits.begin() + crossPoint1, Other.nBits.begin() + half,
			std::back_inserter(bits1));


		//1 point Y
		std::copy(this->cities.begin() + half, this->cities.begin() + crossPoint2,
			std::back_inserter(bits1));

		std::copy(Other.nBits.begin() + crossPoint2, Other.nBits.end(),
			std::back_inserter(bits1));



		//2 Point X
		std::copy(Other.nBits.begin(), Other.nBits.begin() + crossPoint1,
			std::back_inserter(bits2));

		std::copy(this->nBits.begin() + crossPoint1, this->nBits.begin() + half,
			std::back_inserter(bits2));


		//2 point Y
		std::copy(Other.nBits.begin() + half, Other.nBits.begin() + crossPoint2,
			std::back_inserter(bits2));

		std::copy(this->nBits.begin() + crossPoint2, this->nBits.end(),
			std::back_inserter(bits2));

			
		solution child1{ nNumberOfBits , nLow , nHigh , bits1 };

		solution child2{ nNumberOfBits , nLow , nHigh , bits2 };


		return {child1 , child2};*/
	}
	else
	{
		return { *this , Other };
	}

}

//performs mutations to the chromosomes
void solution::Mutate(double mutationProbability)
{
	//std::cout << "\nBefore mutation " << this->toString() << "\n";
	for (int i = 0; i < number_of_cities; i++) {
		bool mutateBool = randomProbability(mutationProbability);
		if (mutateBool) //if mutate swap with other random city
		{
			int other = rand() % number_of_cities;
			while (other == i)
				other = rand() % number_of_cities;
			
			int cityOne = cities[other];
			cities[other] =  cities[i]; //swaps
			cities[i] = cityOne;
			
			std::cout << "[Mutated] " << toString() << std::endl;
		}
	}

	//std::cout << "After mutation " << this->toString() << "\n";
}

