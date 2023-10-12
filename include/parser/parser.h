#ifndef YALPCONF_INCLUDE_PARSER_PARSER_H_
#define YALPCONF_INCLUDE_PARSER_PARSER_H_

#include <memory>

#include "lexical_analyzer/lexical_analyzer.h"
#include "error.h"
#include "types/object.h"

namespace yalpconf {

class Parser {
  public:
    explicit Parser(std::unique_ptr<const LexicalAnalyzer> lexical_analyzer)
        : lexical_analyzer_ { std::move(lexical_analyzer) } {}
    virtual ~Parser() = default;
    virtual Error ParseTokens() = 0;
    virtual std::shared_ptr<Object> GetRootObject() = 0;
  protected:
    std::unique_ptr<const LexicalAnalyzer> lexical_analyzer_;
};

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_PARSER_PARSER_H_
