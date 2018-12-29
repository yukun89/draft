// Example program
#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
  std::string name;
  std::cout << "What is your name? ";
  std::cout << "Hello, " << name << "!\n";
  std::unordered_map<int, int> test;
  std::unordered_map<int, int> test2;
  if (test.end() == test2.end())
  std::cout << "The same end" <<std::endl;
  std::cout << &(*test.end()) << std::endl;
  std::cout << &(*test2.end()) << std::endl;

}


