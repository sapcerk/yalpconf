#ifndef YALPCONF_INCLUDE_PARSER_LR0_PARSER_H_
#define YALPCONF_INCLUDE_PARSER_LR0_PARSER_H_

#include <memory>
#include <vector>
#include <stack>

#include "parser/parser.h"
#include "lexical_analyzer/lexical_analyzer.h"
#include "error.h"
#include "parser/item.h"
#include "types/object.h"
#include "types/array.h"

namespace yalpconf {

class Lr0Parser : public Parser {
  public:
    explicit Lr0Parser(std::unique_ptr<const LexicalAnalyzer> lexical_analyzer);
    Error ParseTokens() override;
    std::shared_ptr<Object> GetRootObject() override;
  private:
    std::stack<Item> items_stack_;
    std::stack<int> states_stack_;
    std::shared_ptr<Array> current_array_;
    std::stack<std::shared_ptr<Object>> objects_stack_;
    const Token* setting_name_token_;
    std::shared_ptr<Value> value_;
    ItemType setting_value_type;

    void Shift(Item& item, int next_state);
    Error Reduce(Item& item, int reduce_rule_number);
    Error Goto();
    void CreateValueContainer(TokenType token_type);
    void CreateValue(ItemType item_type);
    Error AppendToObject();
    void AppendToArray();
    Error InsertToParseTree(ItemType reduce_result);
};

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_PARSER_LR0_PARSER_H_
