#ifndef YALPCONF_INCLUDE_LEXICAL_ANALYZER_LEXICAL_ANALYZER_H_
#define YALPCONF_INCLUDE_LEXICAL_ANALYZER_LEXICAL_ANALYZER_H_

#include <memory>

#include "error.h"
#include "reader/reader.h"
#include "lexical_analyzer/token.h"

namespace yalpconf {

class LexicalAnalyzer {
  public:
    explicit LexicalAnalyzer(std::unique_ptr<const Reader> reader)
        : reader_ { std::move(reader) } {};
    virtual ~LexicalAnalyzer() = default;
    virtual Error ScanTokens() = 0;
    virtual bool empty() const = 0;
    virtual const Token& TakeNextToken() const = 0;
    virtual const Token& CheckNextToken() const = 0;
  protected:
    std::unique_ptr<const Reader> reader_;
};

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_LEXICAL_ANALYZER_LEXICAL_ANALYZER_H_
