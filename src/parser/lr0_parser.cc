#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

#include "parser/parser.h"
#include "parser/lr0_parser.h"
#include "lexical_analyzer/lexical_analyzer.h"
#include "lexical_analyzer/token.h"
#include "error.h"
#include "parser/item.h"
#include "types/object.h"
#include "types/array.h"
#include "types/int.h"
#include "types/boolean.h"
#include "types/string.h"

#include "src/parser/action_table.h"
#include "src/parser/goto_table.h"
#include "src/parser/reduce_rules.h"

namespace yalpconf {

Lr0Parser::Lr0Parser(std::unique_ptr<const LexicalAnalyzer> lexical_analyzer) 
    : Parser(std::move(lexical_analyzer)) {
  objects_stack_.push(std::make_shared<Object>());
};

void Lr0Parser::CreateValueContainer(TokenType token_type) {
  if (token_type == TokenType::SeparatorOpenCurlyBracket && 
      states_stack_.top() != 0) {
    objects_stack_.push(std::make_shared<Object>());
  } else if (token_type == TokenType::SeparatorOpenSquareBracket) {
    current_array_ = std::make_shared<Array>();
  } 
}

void Lr0Parser::Shift(Item& item, int next_state) {
  if (!lexical_analyzer_->empty()) {
    TokenType token_type = lexical_analyzer_->TakeNextToken().type;
    if (token_type == TokenType::SeparatorOpenCurlyBracket || 
        token_type == TokenType::SeparatorOpenSquareBracket)
      CreateValueContainer(token_type);
  }
  items_stack_.push(item);
  states_stack_.push(next_state);
}

void Lr0Parser::CreateValue(ItemType item_type) {
  switch (item_type) {
    case ItemType::DecimalInteger:
    case ItemType::HexadecimalInteger:
    case ItemType::BinaryInteger:
      value_ = std::make_shared<Int>(*items_stack_.top().token);
      break;
    case ItemType::Boolean:
      value_ = std::make_shared<Boolean>(items_stack_.top().token->type);
      break;
    case ItemType::String:
      value_ = std::make_shared<String>(items_stack_.top().token->value);
      break;
  }
}

Error Lr0Parser::AppendToObject() {
  switch (setting_value_type) {
    case ItemType::Value:
      if (objects_stack_.top()->exist(setting_name_token_->value))
        return Error(ErrorCode::ParserAlreadyInScope, 
            setting_name_token_->line, setting_name_token_->value);
      objects_stack_.top()->add(std::move(setting_name_token_->value), std::move(value_));
      value_.reset();
      break;
    case ItemType::Object: 
      {
        std::shared_ptr<Object> obj { std::move(objects_stack_.top()) };
        objects_stack_.pop();
        if (objects_stack_.top()->exist(setting_name_token_->value))
          return Error(ErrorCode::ParserAlreadyInScope, 
              setting_name_token_->line, setting_name_token_->value);
        objects_stack_.top()->add(std::move(setting_name_token_->value), std::move(obj));
      }
      break;
    case ItemType::Array:
      if (objects_stack_.top()->exist(setting_name_token_->value))
        return Error(ErrorCode::ParserAlreadyInScope, 
            setting_name_token_->line, setting_name_token_->value);
      objects_stack_.top()->add(std::move(setting_name_token_->value), std::move(current_array_));
      current_array_.reset();
      break;
  }
  return Error(ErrorCode::None);
}

void Lr0Parser::AppendToArray() {
  current_array_->add(std::move(value_));
  value_.reset();
}

Error Lr0Parser::InsertToParseTree(ItemType reduce_result) {
  if (reduce_result == ItemType::Value) {
    CreateValue(items_stack_.top().type);
  } else if (reduce_result == ItemType::SettingValue) {
    setting_value_type = items_stack_.top().type;
  } else if (reduce_result == ItemType::Setting && 
      items_stack_.top().type == ItemType::SettingName) {
    setting_name_token_ = items_stack_.top().token;
  } else if (reduce_result == ItemType::SettingsList && 
      items_stack_.top().type == ItemType::Setting) {
    return AppendToObject();
  } else if (reduce_result == ItemType::ValuesList && 
      items_stack_.top().type == ItemType::Value) {
    AppendToArray();
  }
  return Error(ErrorCode::None);
}

Error Lr0Parser::Reduce(Item& item, int reduce_rule_number) {
  states_stack_.pop();
  const ReduceRules::Rule& reduce_rule { ReduceRules::FindRule(reduce_rule_number) };
  for (auto reduce_item { reduce_rule.items_types.crbegin() }; 
    reduce_item < reduce_rule.items_types.crend(); ++reduce_item) {
    if (*reduce_item == items_stack_.top().type) {
      Error error { InsertToParseTree(reduce_rule.result) };
      if (error.GetCode() != ErrorCode::None)
        return error;
      items_stack_.pop();
    } else {
      if (item.token) {
        return Error(ErrorCode::ParserReduce, item.token->line,
            item.token->value, GetItemTypeValue(*reduce_item));
      } else {
        return Error(ErrorCode::ParserReduce, 0, "", 
            GetItemTypeValue(*reduce_item));
      }
    }
  }
  items_stack_.push(Item(reduce_rule.result));
  return Error(ErrorCode::None);
}

Error Lr0Parser::Goto() {
  ItemType item_top_stack { items_stack_.top().type };
  while (!states_stack_.empty()) {
    const GotoTable::Result goto_state { GotoTable::Find(states_stack_.top(), item_top_stack) };
    if (goto_state.found) {
      if (states_stack_.top() != goto_state.cell->goto_state)
        states_stack_.push(goto_state.cell->goto_state);
      break;
    } else {
      states_stack_.pop();
    }
  }
  if (states_stack_.empty() && items_stack_.top().type != ItemType::Success) {
    Item& item { items_stack_.top() };
    if (item.token) {
      return Error(ErrorCode::ParserGoto, item.token->line,
          item.token->value, GetItemTypeValue(item.type));
    } else {
      return Error(ErrorCode::ParserGoto, 0, "", 
          GetItemTypeValue(item.type));
    }
  }
  return Error(ErrorCode::None);
}

Error Lr0Parser::ParseTokens() {
  items_stack_.push(Item(ItemType::Begin));
  states_stack_.push(0);
  Item current_item;
  Error error;
  while (items_stack_.top().type != ItemType::Success) {
    if (lexical_analyzer_->empty()) {
      current_item = Item(ItemType::End);
    } else {
      current_item = Item(&lexical_analyzer_->CheckNextToken());
    }
    const int current_state { states_stack_.top() };
    const ActionTable::Result shift_state {
        ActionTable::FindShiftState(current_state, current_item.type) };
    const ActionTable::Result reduce_rule {
        ActionTable::FindReduceRule(current_state, current_item.type) };
    if (reduce_rule.found) {
      error = Reduce(current_item, reduce_rule.cell->reduce_rule);
      if (error.GetCode() == ErrorCode::None)
        error = Goto();
    } else if (shift_state.found) {
      Shift(current_item, shift_state.cell->next_state);
    } else {
      if (current_item.token) {
        return Error(ErrorCode::ParserUnexpectedToken, current_item.token->line,
            current_item.token->value, ActionTable::FindExpected(current_state));
      } else {
        return Error(ErrorCode::ParserUnexpectedToken, 0, "", 
            ActionTable::FindExpected(current_state));
      }
    }
    if (error.GetCode() != ErrorCode::None)
      return error;
  }
  return Error(ErrorCode::None);
}

std::shared_ptr<Object> Lr0Parser::GetRootObject() {
  return objects_stack_.top();
}

} // namespace yalpconf
