// System includes
#include <algorithm>
#include <string>
#include <vector>

// Project includes
#include <spdlog/spdlog.h>

class Solution {
public:
  // constructor
  Solution() {};

  ~Solution() = default;

  Solution(Solution &copy_constructor) = delete;
  Solution operator=(Solution &copy_assignment) = delete;

  Solution(Solution &&move_constructor) = delete;
  Solution operator=(Solution &&move_assignment) = delete;

  std::string sortVotes(std::vector<std::string> votes) {
    if (votes.size() == 1) {
      // Only one person voted
      return votes[0];
    }

    int number_of_candidates = votes[0].size();
    // vector of candiadates and their votes
    std::vector<std::vector<int>> counted_votes(
        26, std::vector<int>(number_of_candidates, 0));

    // step through the persons
    for (std::string &vote : votes) {
      spdlog::debug("Counting Persons Votes: {}", vote);
      for (int i = 0; i < number_of_candidates; ++i) {
        spdlog::debug("Candiate: {} at ranking {}", vote[i], i);
        // Offsetting Char Hex value by 'A' (65 Dec)
        // Add vote to the candiate at the ranking position
        // for example Adam : Secondary ++
        // for example Bob  : Primaary ++
        counted_votes[vote[i] - 'A'][i]++;
      }
    }

    std::string results = votes[0];
    // Sort the teams according to their rank counts
    std::sort(results.begin(), results.end(),
              [&](char &canidate_A, char &canidate_B) {
                // Retrieve the rank array indices corresponding to the teams
                int person_A_idx = canidate_A - 'A';
                int person_B_idx = canidate_B - 'A';

                // Iterate over each rank position
                for (int rank = 0; rank < number_of_candidates; ++rank) {
                  // If count for a rank position is different, determine order
                  // by the higher count
                  if (counted_votes[person_A_idx][rank] !=
                      counted_votes[person_B_idx][rank]) {
                    return counted_votes[person_A_idx][rank] >
                           counted_votes[person_B_idx][rank];
                  }
                }

                // If the teams are tied in all rank positions, order
                // alphabetically
                return canidate_A < canidate_B;
              });

    return results;
  }
};

int main() {
  spdlog::set_level(spdlog::level::debug);

  Solution comupter = Solution();

  std::vector<std::string> input_votes = {"ABC", "ACB", "ABC", "ACB", "ACB"};
  spdlog::info("Results: {}", comupter.sortVotes(input_votes));

  return 0;
}