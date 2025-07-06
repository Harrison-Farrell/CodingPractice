#include <iostream>
#include <unordered_map>


class HitCounter {
  // Use an unordered map to store the count of hits for each timestamp
  private:
    std::unordered_map<int, int> hitCounts;

  public:
    HitCounter(){};

  void hit(int timestamp) {
    hitCounts[timestamp]++;
  }

  int getHits(int timestamp)
  {
    int hits = 0;

    for (auto& entry : hitCounts) {
      if (timestamp - entry.first < 200) {
        hits += entry.second;
      }
    }
    return hits;
  }
};

int main(int argc, char** argv)
{
  HitCounter* counter = new HitCounter();
  counter->hit(10);
  counter->hit(30);

  std::cout << counter->getHits(40) << std::endl; // 2

  counter->hit(60);
  counter->hit(60); // multiple  hits for the same time
  counter->hit(70);

  std::cout << counter->getHits(80) << std::endl; // 4, time 1 is out of context now
  std::cout << counter->getHits(150) << std::endl; // 3 time 3 is out of context now
  std::cout << counter->getHits(300) << std::endl; // 0 all hits are out of context now

  return 0;

}

