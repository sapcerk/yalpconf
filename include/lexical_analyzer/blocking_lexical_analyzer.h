#ifndef YALPCONF_SRC_LEXICAL_ANALYZER_BLOCKING_LEXICAL_ANALYZER_H_
#define YALPCONF_SRC_LEXICAL_ANALYZER_BLOCKING_LEXICAL_ANALYZER_H_

#include <memory>
#include <string>

#include "error.h"
#include "reader/reader.h"
#include "lexical_analyzer/lexical_analyzer.h"
#include "lexical_analyzer/token.h"

namespace yalpconf {

class BlockingLexicalAnalyzer : public LexicalAnalyzer {
  public:
    explicit BlockingLexicalAnalyzer(std::unique_ptr<const Reader> reader);
    ~BlockingLexicalAnalyzer() = default;
    Error ScanTokens() override;
    bool empty() const override;
    Token TakeNextToken() const override;
    Token CheckNextToken() const override;
  private:
    std::vector<Token> tokens_;
    std::string current_token_;
    size_t line_;
    mutable size_t next_token_position_;

    void AddToken(TokenType token_type);
    void AddSymbolToCurrentToken(char symbol);
    char ReaderTakeNextSymbol();

    Error AddString();
    void AddPythonComment();
    Error AddCComment();
    Error IntegerBaseSelect();
    Error AddHexadecimalInteger();
    Error AddBinaryInteger();
    Error AddDecimalInteger();
    void AddIdentifierKeyword();
};

} // namespace yalpconf

#endif // YALPCONF_SRC_LEXICAL_ANALYZER_BLOCKING_LEXICAL_ANALYZER_H_
