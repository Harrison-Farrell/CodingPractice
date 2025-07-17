#include <iostream>
#include <unordered_map>

class HitCounter {
  // Use an unordered map to store the count of hits for each timestamp
private:
  std::unordered_map<int, int> hitCounts;

public:
  HitCounter() {};

  void hit(int timestamp) { hitCounts[timestamp]++; }

  int getHits(int timestamp) {
    int hits = 0;

    for (auto &entry : hitCounts) {
      if (timestamp - entry.first < 10) {
        hits += entry.second;
      }
    }
    return hits;
  }
};

int main(int argc, char **argv) {
  HitCounter *counter = new HitCounter();
  counter->hit(1);
  counter->hit(3);

  int hits4 = counter->getHits(4); // 2

  counter->hit(6);
  counter->hit(6); // multiple  hits for the same time
  counter->hit(7);

  int hits7 = counter->getHits(7);   // 4, time 1 is out of context now
  int hits10 = counter->getHits(10); // 3 time 3 is out of context now
  int hits15 = counter->getHits(15); // 0 all hits are out of context now

  std::cout << "First Hit: " << hits4 << std::endl;
  std::cout << "Second Hit: " << hits7 << std::endl;
  std::cout << "Third Hit: " << hits10 << std::endl;
  std::cout << "Fourth Hit: " << hits15 << std::endl;

  return 0;
}
