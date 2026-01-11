/*
https://algo.monster/liteproblems/359

You need to design a logger system that handles incoming messages with
timestamps. The key requirement is that each unique message should only be
printed at most once every 10 seconds.

Here's how the system works:
When a message arrives at timestamp t and gets printed, any identical
message that arrives within the next 10 seconds (before timestamp t + 10) should
not be printed Messages always arrive in chronological order (timestamps are
non-decreasing) Multiple messages can arrive at the same timestamp

You need to implement a Logger class with two methods:

Logger(): Initializes the logger object

shouldPrintMessage(timestamp, message): Takes a timestamp (integer) and a
message (string) as input, and returns: true if the message should be printed
(either it's the first time seeing this message, or it's been at least 10
seconds since it was last printed) false if the message should not be printed
(it was printed less than 10 seconds ago)

For example:
If message "foo" is printed at timestamp 1, it cannot be printed again until
timestamp 11 or later If the same "foo" arrives at timestamps 2, 5, or 10, the
method should return false If "foo" arrives at timestamp 11 or later, it can be
printed again (method returns true)

The solution uses a hash map (limiter) to track each message and the earliest
timestamp when it can be printed again. When a message should be printed, the
map is updated with timestamp + 10 to block printing for the next 10 seconds.
*/

// System includes
#include <algorithm>
#include <string>

#include <unordered_map>

// Project includes
#include <spdlog/fmt/ranges.h>
#include <spdlog/spdlog.h>

class Logger {
public:
  // contrusctor
  Logger() {};
  ~Logger() = default;

  Logger(Logger &copy_constructor) = delete;
  Logger(Logger &&move_constructor) = delete;
  Logger &operator=(Logger &&move_assignment) = delete;
  Logger &operator=(Logger &copy_assignment) = delete;

  bool shouldPrintMessage(int timestamp, std::string message) {
    bool should_print = true;
    // The message has never been sent before
    if (logHistory.count(message) == false) {
      logHistory[message] = timestamp;
      // early return
      return should_print;
    }

    int last_timestamp = logHistory[message];

    // T.now - T.past = T.delta < rateLimit
    if (timestamp - last_timestamp >= rateLimit) {
      // allowed to print
      // setting the new past timestamp
      logHistory[message] = timestamp;
    } else {
      // rate limited
      should_print = false;
    }

    spdlog::debug("ShouldPrint: M:{}, L:{}, T:{}, P:{}", message,
                  last_timestamp, timestamp, should_print);
    return should_print;
  }

private:
  const int rateLimit = 10;
  std::unordered_map<std::string, int> logHistory;
};

int main(int argc, char **argv) {
  spdlog::set_level(spdlog::level::debug);

  spdlog::info("Backend Coding - Data Structures Interview");
  spdlog::debug("Sriteja Parimi (Senior Software Engineer)");

  Logger logger = Logger();
  spdlog::info("Should print. {}, {} - {}", 1, "foo",
               logger.shouldPrintMessage(1, "foo"));
  spdlog::info("Should print. {}, {} - {}", 2, "foo",
               logger.shouldPrintMessage(2, "bar"));
  spdlog::info("Should print. {}, {} - {}", 3, "foo",
               logger.shouldPrintMessage(3, "foo"));
  spdlog::info("Should print. {}, {} - {}", 8, "foo",
               logger.shouldPrintMessage(8, "bar"));
  spdlog::info("Should print. {}, {} - {}", 10, "foo",
               logger.shouldPrintMessage(10, "foo"));
  spdlog::info("Should print. {}, {} - {}", 11, "foo",
               logger.shouldPrintMessage(11, "foo"));
  // expecting
  // [true, true, false, false, false, true]

  return 0;
}