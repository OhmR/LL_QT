#ifndef SINGLEPARSER_H
#define SINGLEPARSER_H

#include <blockparser.h>

class SingleParser {
 public:
  SingleParser(QString Path);
  ~SingleParser();
  BlockParser* request();
  void release();  // may be use in Multi-thread safe

 private:
  BlockParser* pointer;
};

#endif  // SINGLEPARSER_H
