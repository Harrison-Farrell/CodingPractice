// Logger Rate Limitier
// Desgin a logger system receives a stream of messages along with their timestamps.
// Each unique message should only be printed at most every 10 seconds.
// I.E. a message printed at timestamp 't' will prevent other identical messages from
// being printed until timestamp 't + 10'
//
// All messages will come in chronological order.
// Several messages may arrive at the same timestamp


// Implement the 'Logger' class
// Logger() initializes the logger
// bool shouldPrintMessage(int timestamp, string message) returns true if the message
// should be printed in a given timestamp, otherwise returns false.

#include <iostream>
#include <unordered_map>
#include <string>


class Logger {
  public: 
    std::unordered_map<std::string, int> lastLog;
    bool shouldPrintMessage(int timestamp, std::string message)
    {
      if(lastLog.count(message) && timestamp - lastLog[message] < 10)
        return false;
      lastLog[message] = timestamp;
      return true;
    }
};

int main(int argc, char** argv)
{
  Logger* logger = new Logger();
  std::cout << "1, foo: " << logger->shouldPrintMessage(1, "foo") << std::endl;// return true, next allowed timestamp for "foo" is 1 + 10 = 11
  std::cout << "2, bar: " << logger->shouldPrintMessage(2, "bar") << std::endl;  // return true, next allowed timestamp for "bar" is 2 + 10 = 12
  std::cout << "3, foo: " << logger->shouldPrintMessage(3, "foo") << std::endl;  // 3 < 11, return false
  std::cout << "8, bar: " << logger->shouldPrintMessage(8, "bar") << std::endl;  // 8 < 12, return false
  std::cout << "10, foo: " << logger->shouldPrintMessage(10, "foo") << std::endl; // 10 < 11, return false
  std::cout << "11, foo: " << logger->shouldPrintMessage(11, "foo") << std::endl; // 11 >= 11, return true, next allowed timestamp for "foo" is 11 + 10 = 21
}
