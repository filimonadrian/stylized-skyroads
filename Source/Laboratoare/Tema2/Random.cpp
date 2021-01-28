# include "Random.h"


float generateFloat(float rangeFrom, float rangeTo) {
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_real_distribution<float> distr(rangeFrom, rangeTo);

	float random = distr(generator) + (float)distr(generator) / 10;
	return random;
}

int generateInt(int rangeFrom, int rangeTo) {
	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> distr(rangeFrom, rangeTo);

	int random = distr(generator);
	return random;
}