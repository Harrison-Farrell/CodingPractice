#include <iostream>
#include <unordered_map>
#include <vector>

/*
 *
 * Given an array of integers `nums` and an integer `target`
 * return indices of the two numbers such that they add up to `target`.
 *
 * You may assume that each input would have exactly one solution,
 * and you may not use the same element twice.
 *
 * You can return the answer in any order.
 **/

std::vector<int> HashMapSum(std::vector<int> number_set, int target) {
  std::unordered_map<int, int> hash_map;
  int set_size = number_set.size();
  // Setting the value as the key, the index as the value
  for (int i = 0; i < set_size; i++) {
    hash_map[number_set[i]] = i;
  }

  // Find the numbers complement. Complement = Tagart - Value;
  for (int i = 0; i < set_size; i++) {
    int complement = target - number_set[i];
    if (hash_map.count(complement) && hash_map[complement] != i) {
      std::cout << "i: " << number_set[i] << "\t j: " << complement
                << std::endl;
      return {i, hash_map[complement]};
    }
  }

  return {};
};

int main(int argc, char **argv) {
  std::vector<int> first_set = {2, 7, 11, 15};
  int first_target = 9;

  std::vector<int> second_set = {3, 4, 2};
  int second_target = 6;

  std::vector<int> third_set = {3, 3};
  int third_target = 6;

  std::vector<int> result = HashMapSum(first_set, first_target);
  std::cout << "[" << result[0] << ":" << result[1] << "]" << std::endl;

  result = HashMapSum(second_set, second_target);
  std::cout << "[" << result[0] << ":" << result[1] << "]" << std::endl;

  result = HashMapSum(third_set, third_target);
  std::cout << "[" << result[0] << ":" << result[1] << "]" << std::endl;

  return 0;
};
