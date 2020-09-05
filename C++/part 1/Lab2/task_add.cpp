#include "Task.h"

std::vector<int> number_to_vector(unsigned long int number)
{
	std::vector<int> result;
	int numbers_count = log10(number);

	for (int i = numbers_count; i >= 0; i--)
	{
		int p = std::pow(10, i);
		int d = number / p;
		number -= d * p;

		result.push_back(d);
	}

	return result;
}

void add_task(long number)
{
	std::vector<int> numbers = number_to_vector(number);
	int count = numbers.size();

	if (count > 6 || number < 0)
	{
		std::cout << "Incorrect number" << std::endl;
		return;
	}

	int sum1 = 0;
	int sum2 = 0;

	if (count > 3)
	{
		for (int i = count - 1; i >= 3; i--)
		{
			sum1 += numbers[i];
		}
	}

	int sum2count = (count > 3) ? 3 : count;

	for (int i = 0; i < sum2count; i++)
	{
		sum2 += numbers[i];
	}

	(sum1 == sum2) ? std::cout << "Good ticket" << std::endl : std::cout << "Bad ticket" << std::endl;
}