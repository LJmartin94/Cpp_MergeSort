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

void ms_split(std::vector<int>& to_sort, std::vector<int>::iterator first, std::vector<int>::iterator last)
{
	std::vector<int>::iterator mid = ((last - first) / 2) + first;
	std::cout << "Mid: " << mid - first << std::endl;
	if ((last - first) > 1)
	{
		ms_split(to_sort, first, mid);
		ms_split(to_sort, mid + 1, last);
	}
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
	for (std::vector<int>::iterator it = to_sort.begin(); it != to_sort.end(); it++)
		std::cout << *it << std::endl;
	return (0);
}