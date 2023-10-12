#ifndef YALPCONF_SRC_PARSER_REDUCE_RULES_H_
#define YALPCONF_SRC_PARSER_REDUCE_RULES_H_

#include <vector>
#include "parser/item.h"

namespace yalpconf {
  
class ReduceRules {
  public: 
    struct Rule {
      ItemType result;
      std::vector<ItemType> items_types;

      Rule(ItemType result, std::vector<ItemType> items_types) 
          : result { result }, items_types { items_types } {}
    };

    static const Rule& FindRule(int reduce_rule_number) {
      return reduce_rules_[reduce_rule_number];
    }

  private:
    static const std::vector<Rule> reduce_rules_;
};

inline const std::vector<ReduceRules::Rule> ReduceRules::reduce_rules_ {
  // rule: 0 
  Rule(ItemType::Success, { ItemType::ConfigurationFile }),
  // rule: 1 
  Rule(ItemType::ConfigurationFile, { ItemType::Begin, ItemType::Object }),
  // rule: 2 
  Rule(ItemType::ConfigurationFile, { ItemType::Begin, ItemType::SettingsList }),
  // rule: 3 
  Rule(ItemType::Object, { 
      ItemType::SeparatorOpenCurlyBracket, 
      ItemType::SettingsList, 
      ItemType::SeparatorCloseCurlyBracket, 
  }),
  // rule: 4 
  Rule(ItemType::Object, { 
      ItemType::SeparatorOpenCurlyBracket, 
      ItemType::SeparatorCloseCurlyBracket, 
  }),
  // rule: 5 
  Rule(ItemType::SettingsList, { 
      ItemType::Setting, 
  }),
  // rule: 6 
  Rule(ItemType::SettingsList, { 
      ItemType::ItemSeparators, 
  }),
  // rule: 7 
  Rule(ItemType::SettingsList, { 
      ItemType::Setting, 
      ItemType::ItemSeparators, 
  }),
  // rule: 8 
  Rule(ItemType::SettingsList, { 
      ItemType::SettingsList, 
      ItemType::Setting, 
  }),
  // rule: 9 
  Rule(ItemType::SettingsList, { 
      ItemType::SettingsList, 
      ItemType::ItemSeparators, 
  }),
  // rule: 10 
  Rule(ItemType::SettingsList, { 
      ItemType::SettingsList, 
      ItemType::Setting, 
      ItemType::ItemSeparators, 
  }),
  // rule: 11 
  Rule(ItemType::Setting, { 
      ItemType::SettingName, 
      ItemType::OperatorEquals, 
      ItemType::SettingValue, 
  }),
  // rule: 12 
  Rule(ItemType::SettingValue, { 
      ItemType::Value, 
  }),
  // rule: 13 
  Rule(ItemType::SettingValue, { 
      ItemType::Object, 
  }),
  // rule: 14 
  Rule(ItemType::SettingValue, { 
      ItemType::Array, 
  }),
  // rule: 15 
  Rule(ItemType::Array, { 
      ItemType::SeparatorOpenSquareBracket, 
      ItemType::ValuesList, 
      ItemType::SeparatorCloseSquareBracket, 
  }),
  // rule: 16 
  Rule(ItemType::Array, { 
      ItemType::SeparatorOpenSquareBracket, 
      ItemType::SeparatorCloseSquareBracket, 
  }),
  // rule: 17 
  Rule(ItemType::ValuesList, { 
      ItemType::Value, 
  }),
  // rule: 18 
  Rule(ItemType::ValuesList, { 
      ItemType::ItemSeparators, 
  }),
  // rule: 19
  Rule(ItemType::ValuesList, { 
      ItemType::Value, 
      ItemType::ItemSeparators, 
  }),
  // rule: 20
  Rule(ItemType::ValuesList, { 
      ItemType::ValuesList, 
      ItemType::Value, 
  }),
  // rule: 21
  Rule(ItemType::ValuesList, { 
      ItemType::ValuesList, 
      ItemType::ItemSeparators, 
  }),
  // rule: 22
  Rule(ItemType::ValuesList, { 
      ItemType::ValuesList, 
      ItemType::Value, 
      ItemType::ItemSeparators, 
  }),
  // rule: 23
  Rule(ItemType::ItemSeparators, { 
      ItemType::SeparatorComma, 
  }),
  // rule: 24
  Rule(ItemType::ItemSeparators, { 
      ItemType::SeparatorSemicolon, 
  }),
  // rule: 25
  Rule(ItemType::Value, { 
      ItemType::DecimalInteger, 
  }),
  // rule: 26
  Rule(ItemType::Value, { 
      ItemType::HexadecimalInteger, 
  }),
  // rule: 27
  Rule(ItemType::Value, { 
      ItemType::BinaryInteger, 
  }),
  // rule: 28
  Rule(ItemType::Value, { 
      ItemType::Boolean, 
  }),
  // rule: 29
  Rule(ItemType::Value, { 
      ItemType::String, 
  }),
};

} // namespace yalpconf

#endif // YALPCONF_SRC_PARSER_REDUCE_RULES_H_
