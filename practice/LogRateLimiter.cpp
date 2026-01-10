// System includes
#include <algorithm>
#include <string>

#include <unordered_map>

// Project includes
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ranges.h>

class Logger
{
    public:
    // contrusctor
    Logger(){};
    ~Logger() = default;

    Logger(Logger& copy_constructor) = delete;
    Logger(Logger&& move_constructor) = delete;
    Logger& operator=(Logger&& move_assignment) = delete;
    Logger& operator=(Logger& copy_assignment) = delete;

    bool shouldPrintMessage(int timestamp, std::string message)
    {
        bool should_print = true;
        // The message has never been sent before
        if(logHistory.count(message) == false)
        {
            logHistory[message] = timestamp;
            // early return
            return should_print;
        }

        int last_timestamp = logHistory[message];
        

        // T.now - T.past = T.delta < rateLimit
        if(timestamp - last_timestamp >= rateLimit)
        {
            // allowed to print
            // setting the new past timestamp
            logHistory[message] = timestamp;
        }
        else 
        {
            // rate limited
            should_print = false;
        }

        spdlog::debug("ShouldPrint: M:{}, L:{}, T:{}, P:{}", message, last_timestamp, timestamp, should_print);
        return should_print;
    }

    private:
    const int rateLimit = 10;
    std::unordered_map<std::string, int> logHistory;
};

int main(int argc, char** argv)
{
    spdlog::set_level(spdlog::level::debug);

    spdlog::info("Backend Coding - Data Structures Interview");
    spdlog::debug("Sriteja Parimi (Senior Software Engineer)");

    Logger logger = Logger();
    spdlog::info("Should print. {}, {} - {}", 1, "foo", logger.shouldPrintMessage(1, "foo"));
    spdlog::info("Should print. {}, {} - {}", 2, "foo", logger.shouldPrintMessage(2, "bar"));
    spdlog::info("Should print. {}, {} - {}", 3, "foo", logger.shouldPrintMessage(3, "foo"));
    spdlog::info("Should print. {}, {} - {}", 8, "foo", logger.shouldPrintMessage(8, "bar"));
    spdlog::info("Should print. {}, {} - {}", 10, "foo", logger.shouldPrintMessage(10, "foo"));
    spdlog::info("Should print. {}, {} - {}", 11, "foo", logger.shouldPrintMessage(11, "foo"));
    // expecting 
    // [true, true, false, false, false, true]

    return 0;
}