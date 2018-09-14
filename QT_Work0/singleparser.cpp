#include "singleparser.h"

SingleParser::SingleParser(QString Path) { pointer = new BlockParser(Path); }

SingleParser::~SingleParser() { delete pointer; }

BlockParser* SingleParser::request() {
  if (pointer == NULL) {
    throw - 1;
  }
  return pointer;
}

void SingleParser::release() {}
