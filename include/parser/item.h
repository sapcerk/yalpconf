#ifndef YALPCONF_SRC_PARSER_ITEMS_H_
#define YALPCONF_SRC_PARSER_ITEMS_H_

#include <unordered_map>

#include "lexical_analyzer/token.h"

namespace yalpconf {

enum class ItemType {
  // terminals
  DecimalInteger,
  BinaryInteger,
  HexadecimalInteger,
  String,
  Boolean,
  SettingName,
  SeparatorComma,
  SeparatorSemicolon,
  SeparatorOpenCurlyBracket,
  SeparatorCloseCurlyBracket,
  SeparatorOpenSquareBracket,
  SeparatorCloseSquareBracket,
  OperatorEquals,

  // non terminals
  ConfigurationFile,
  Object,
  SettingsList,
  ItemSeparators,
  Setting,
  Array,
  SettingValue,
  ValuesList,
  Value,

  Begin,
  End,
  Success,
};

inline std::string GetItemTypeValue(ItemType type) {
  switch (type) {
    case ItemType::DecimalInteger:
      return "DecimalInteger";
    case ItemType::BinaryInteger:
         return "BinaryInteger";
    case ItemType::HexadecimalInteger:
         return "HexadecimalInteger";
    case ItemType::String:
         return "String";
    case ItemType::Boolean:
         return "Boolean";
    case ItemType::SettingName:
         return "SettingName";
    case ItemType::SeparatorComma:
         return "SeparatorComma";
    case ItemType::SeparatorSemicolon:
         return "SeparatorSemicolon";
    case ItemType::SeparatorOpenCurlyBracket:
         return "SeparatorOpenCurlyBracket";
    case ItemType::SeparatorCloseCurlyBracket:
         return "SeparatorCloseCurlyBracket";
    case ItemType::SeparatorOpenSquareBracket:
         return "SeparatorOpenSquareBracket";
    case ItemType::SeparatorCloseSquareBracket:
         return "SeparatorCloseSquareBracket";
    case ItemType::OperatorEquals:
         return "OperatorEquals";
    case ItemType::ConfigurationFile:
         return "ConfigurationFile";
    case ItemType::Object:
         return "Object";
    case ItemType::SettingsList:
         return "SettingsList";
    case ItemType::ItemSeparators:
         return "ItemSeparators";
    case ItemType::Setting:
         return "Setting";
    case ItemType::Array:
         return "Array";
    case ItemType::SettingValue:
         return "SettingValue";
    case ItemType::ValuesList:
         return "ValuesList";
    case ItemType::Value:
         return "Value";
    case ItemType::Begin:
         return "Begin";
    case ItemType::End:
         return "End";
    case ItemType::Success:
         return "Success";
  }
  return "TerminalItem";

};

inline ItemType GetItemFromTokenType(TokenType token_type) {
  switch (token_type) {
    case TokenType::DecimalInteger:
      return ItemType::DecimalInteger;
    case TokenType::BinaryInteger:
      return ItemType::BinaryInteger;
    case TokenType::HexadecimalInteger:
      return ItemType::HexadecimalInteger;
    case TokenType::String:
      return ItemType::String;
    case TokenType::Identifier:
      return ItemType::SettingName;
    case TokenType::SeparatorComma:
      return ItemType::SeparatorComma;
    case TokenType::SeparatorSemicolon:
      return ItemType::SeparatorSemicolon;
    case TokenType::SeparatorOpenCurlyBracket:
      return ItemType::SeparatorOpenCurlyBracket;
    case TokenType::SeparatorCloseCurlyBracket:
      return ItemType::SeparatorCloseCurlyBracket;
    case TokenType::SeparatorOpenSquareBracket:
      return ItemType::SeparatorOpenSquareBracket;
    case TokenType::SeparatorCloseSquareBracket:
      return ItemType::SeparatorCloseSquareBracket;
    case TokenType::OperatorEquals:
      return ItemType::OperatorEquals;
    case TokenType::KeywordTrue:
    case TokenType::KeywordFalse:
      return ItemType::Boolean;
  }
  return ItemType::Begin;
}

class Item {
  public: 
    ItemType type;
    const Token* token;

    explicit Item()
        : type { ItemType::Begin }, token { nullptr } {}

    explicit Item(ItemType type) 
        : type { type }, token { nullptr } {}

    explicit Item(const Token* token) 
        : type { GetItemFromTokenType(token->type) }, token { token } {}
};

} // namespace yalpconf

#endif // YALPCONF_SRC_PARSER_ITEMS_H_
