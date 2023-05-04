#include <iostream>
#include <vector>
#include <sstream>

std::vector<int> parseAndErrorCheckArgv(int argc, char **argv) 
{
  std::vector<int> numbers;
  try {
    for (int i = 1; i < argc; i++) {
      std::stringstream ss(argv[i]);
      long num;
      while (ss >> num) {
        if (ss.fail() || num < 0 || num > INT_MAX) {
          throw std::invalid_argument("invalid argument");
        }
        numbers.push_back(num);
      }
    }
  } catch (std::exception &e) {
    std::cout << "Error: " << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }
  return numbers;
}

void print_int_vector(std::vector<int> to_print, 
					const std::vector<int>::iterator from,
					const std::vector<int>::iterator to)
{
	for (std::vector<int>::iterator it = from; it != to; it++)
		std::cout << *it;
	std::cout << std::endl;
}

void swap_ints(std::vector<int>::iterator& a, std::vector<int>::iterator& b)
{
	int swap_holder = *a;
	*a = *b;
	*b = swap_holder;
	return;
}

bool should_swap(int a, int b)
{
	if (a > b) //Or any other comparison.
		return true;
	return false;
}

void ms_merge(std::vector<int>& to_sort, 
				std::vector<int>::iterator first, 
				std::vector<int>::iterator mid, 
				std::vector<int>::iterator last)
{
	std::cout << "ms_merge - segment: ";
	std::vector<int> sorted;
	print_int_vector(to_sort, first, last);
	while( first < last && mid < last && first < mid)
	{
		std::cout << "Comparing " << first - first << " and " << mid - first << std::endl;
		if (!should_swap(*first, *mid))
		{
			sorted.push_back(*first);
			first++;
		}
		else
		{
			sorted.push_back(*mid);
			mid++;
		}
	}
	std::cout << "Storing result" << std::endl;
	for (std::vector<int>::reverse_iterator rit = sorted.rbegin(); rit != sorted.rend(); ++rit)
	{
		last--;
		*last = *rit;
	}
	return;
}

void ms_split(std::vector<int>& to_sort, 
				std::vector<int>::iterator first, 
				std::vector<int>::iterator last)
{
	std::vector<int>::iterator mid = ((last - first) / 2) + first;
	std::cout << "ms_split - Mid: " << mid - first << std::endl;
	if ((last - first) > 1)
	{
		ms_split(to_sort, first, mid);
		ms_split(to_sort, mid + 1, last);
	}
	if (first != mid)
		ms_merge(to_sort, first, mid, last);
	return;
}

int main(int argc, char **argv)
{
	// Parse input
	if (argc < 2)
	{
		std::cout << "Not enough args!" << std::endl;
		return (1);
	}
	std::vector<int> to_sort = parseAndErrorCheckArgv(argc, argv);

	//Perform sorting
	ms_split(to_sort, to_sort.begin(), to_sort.end());

	//Print answer
	print_int_vector(to_sort, to_sort.begin(), to_sort.end());

	return (0);
}