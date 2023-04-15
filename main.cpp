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

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Not enough args!" << std::endl;
		return (1);
	}

	std::vector<int> to_sort = parseAndErrorCheckArgv(argc, argv);

	return (0);
}