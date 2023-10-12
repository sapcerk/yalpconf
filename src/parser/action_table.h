#ifndef YALPCONF_SRC_PARSER_ACTION_TABLE_H_
#define YALPCONF_SRC_PARSER_ACTION_TABLE_H_

#include <vector>
#include <string>
#include "parser/item.h"

namespace yalpconf {

class ActionTable {
  public:
    struct Cell {
      ItemType item;
      union {
        int next_state;
        int reduce_rule;
      };

      explicit Cell(ItemType item, int state) 
          : item { item }, next_state { state } {}
    };

    struct TableTypes {
      enum class Type {
        shift,
        reduce,
      };
      std::vector<Cell> shift;
      std::vector<Cell> reduce;

      TableTypes(std::vector<Cell> shift,
          std::vector<Cell> reduce) 
          : shift { shift }, reduce { reduce } {}
    };

    struct Result {
      bool found;
      const Cell* cell;

      explicit Result(bool found, const Cell* cell)
          : found { found }, cell { cell } {}
    };

    static Result FindShiftState(int state, ItemType item) {
      return FindState(state, item, TableTypes::Type::shift);
    }

    static Result FindReduceRule(int state, ItemType item) {
      return FindState(state, item, TableTypes::Type::reduce);
    }

    static std::string FindExpected(int state) {
      const auto& table_shift { action_table_[state].shift }; 
      const auto& table_reduce { action_table_[state].reduce }; 
      std::string result;
      for (auto cell : table_shift) {
        result.append(" " + GetItemTypeValue(cell.item));
      } 
      for (auto cell : table_reduce) {
        result.append(" " + GetItemTypeValue(cell.item));
      } 
      return result;
    }
   
  private:
    static const std::vector<TableTypes> action_table_;

    static Result FindState(int state, ItemType item, TableTypes::Type table_type) {
      const auto& table { table_type == TableTypes::Type::shift ? 
          action_table_[state].shift : action_table_[state].reduce };
      const auto& cell { std::find_if(table.begin(), 
          table.end(), 
          [item](const Cell& cell) { 
              return cell.item == item; 
          }) };
      if (cell != table.end()) {
        return Result(true, &(*cell));
      }  
      return Result(false, nullptr);
    } 
};

inline const std::vector<ActionTable::TableTypes> ActionTable::action_table_ {
  // state: 0
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 7),
      Cell(ItemType::SeparatorOpenCurlyBracket, 4),
      Cell(ItemType::SettingName, 14),
    },
    // reduce
    {
    }
  ),
  // state: 1
  TableTypes(
    // shift
    {
    },
    // reduce
    { 
      Cell(ItemType::End, 1),
    }
  ),
  // state: 2
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 7),
      Cell(ItemType::SettingName, 14),
    }, 
    // reduce
    { 
      Cell(ItemType::End, 2),
    }
  ),
  // state: 3
  TableTypes(
    // shift
    {
    },
    // reduce
    { 
      Cell(ItemType::End, 0),
    }
  ),
  // state: 4
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 7),
      Cell(ItemType::SeparatorCloseCurlyBracket, 33),
      Cell(ItemType::SettingName, 14),
    }, 
    // reduce
    { 
    }
  ),
  // state: 5
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 7),
      Cell(ItemType::SeparatorCloseCurlyBracket, 34),
      Cell(ItemType::SettingName, 14),
    }, 
    // reduce
    { 
    }
  ),
  // state: 6
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 23),
      Cell(ItemType::SeparatorSemicolon, 23),
      Cell(ItemType::SeparatorCloseCurlyBracket, 23),
      Cell(ItemType::SeparatorCloseSquareBracket, 23),
      Cell(ItemType::End, 23),
      Cell(ItemType::SettingName, 23),
      Cell(ItemType::DecimalInteger, 23),
      Cell(ItemType::HexadecimalInteger, 23),
      Cell(ItemType::BinaryInteger, 23),
      Cell(ItemType::Boolean, 23),
      Cell(ItemType::String, 23),
    }
  ),
  // state: 7
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 24),
      Cell(ItemType::SeparatorSemicolon, 24),
      Cell(ItemType::SeparatorCloseCurlyBracket, 24),
      Cell(ItemType::SeparatorCloseSquareBracket, 24),
      Cell(ItemType::End, 24),
      Cell(ItemType::SettingName, 24),
      Cell(ItemType::DecimalInteger, 24),
      Cell(ItemType::HexadecimalInteger, 24),
      Cell(ItemType::BinaryInteger, 24),
      Cell(ItemType::Boolean, 24),
      Cell(ItemType::String, 24),
    }
  ),
  // state: 8
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 6),
      Cell(ItemType::SeparatorCloseCurlyBracket, 6),
      Cell(ItemType::End, 6),
      Cell(ItemType::SettingName, 6),
    }
  ),
  // state: 9
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 9),
      Cell(ItemType::SeparatorSemicolon, 9),
      Cell(ItemType::SeparatorCloseCurlyBracket, 9),
      Cell(ItemType::End, 9),
      Cell(ItemType::SettingName, 9),
    }
  ),
  // state: 10
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 7),
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorCloseCurlyBracket, 5),
      Cell(ItemType::End, 5),
    }
  ),
  // state: 11
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 7),
      Cell(ItemType::SeparatorSemicolon, 7),
      Cell(ItemType::SeparatorCloseCurlyBracket, 7),
      Cell(ItemType::End, 7),
      Cell(ItemType::SettingName, 7),
    }
  ),
  // state: 12
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 7),
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorCloseCurlyBracket, 8),
      Cell(ItemType::End, 8),
    }
  ),
  // state: 13
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 10),
      Cell(ItemType::SeparatorSemicolon, 10),
      Cell(ItemType::SeparatorCloseCurlyBracket, 10),
      Cell(ItemType::End, 10),
      Cell(ItemType::SettingName, 10),
    }
  ),
  // state: 14
  TableTypes(
    // shift
    { 
      Cell(ItemType::OperatorEquals, 15),
    }, 
    // reduce
    { 
    }
  ),
  // state: 15
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorOpenCurlyBracket, 4),
      Cell(ItemType::SeparatorOpenSquareBracket, 25),
      Cell(ItemType::DecimalInteger, 20),
      Cell(ItemType::HexadecimalInteger, 21),
      Cell(ItemType::BinaryInteger, 22),
      Cell(ItemType::Boolean, 23),
      Cell(ItemType::String, 24),
    }, 
    // reduce
    { 
    }
  ),
  // state: 16
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 11),
      Cell(ItemType::SeparatorSemicolon, 11),
      Cell(ItemType::SeparatorCloseCurlyBracket, 11),
      Cell(ItemType::End, 11),
    }
  ),
  // state: 17
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 12),
      Cell(ItemType::SeparatorSemicolon, 12),
      Cell(ItemType::SeparatorCloseCurlyBracket, 12),
      Cell(ItemType::End, 12),
    }
  ),
  // state: 18
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 13),
      Cell(ItemType::SeparatorSemicolon, 13),
      Cell(ItemType::SeparatorCloseCurlyBracket, 13),
      Cell(ItemType::End, 13),
    }
  ),
  // state: 19
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 14),
      Cell(ItemType::SeparatorSemicolon, 14),
      Cell(ItemType::SeparatorCloseCurlyBracket, 14),
      Cell(ItemType::End, 14),
    }
  ),
  // state: 20
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 25),
      Cell(ItemType::SeparatorSemicolon, 25),
      Cell(ItemType::SeparatorCloseCurlyBracket, 25),
      Cell(ItemType::SeparatorCloseSquareBracket, 25),
      Cell(ItemType::End, 25),
    }
  ),
  // state: 21
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 26),
      Cell(ItemType::SeparatorSemicolon, 26),
      Cell(ItemType::SeparatorCloseCurlyBracket, 26),
      Cell(ItemType::SeparatorCloseSquareBracket, 26),
      Cell(ItemType::End, 26),
    }
  ),
  // state: 22
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 27),
      Cell(ItemType::SeparatorSemicolon, 27),
      Cell(ItemType::SeparatorCloseCurlyBracket, 27),
      Cell(ItemType::SeparatorCloseSquareBracket, 27),
      Cell(ItemType::End, 27),
    }
  ),
  // state: 23
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 28),
      Cell(ItemType::SeparatorSemicolon, 28),
      Cell(ItemType::SeparatorCloseCurlyBracket, 28),
      Cell(ItemType::SeparatorCloseSquareBracket, 28),
      Cell(ItemType::End, 28),
    }
  ),
  // state: 24
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 29),
      Cell(ItemType::SeparatorSemicolon, 29),
      Cell(ItemType::SeparatorCloseCurlyBracket, 29),
      Cell(ItemType::SeparatorCloseSquareBracket, 29),
      Cell(ItemType::End, 29),
    }
  ),
  // state: 25
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 7),
      Cell(ItemType::SeparatorCloseSquareBracket, 35),
      Cell(ItemType::DecimalInteger, 20),
      Cell(ItemType::HexadecimalInteger, 21),
      Cell(ItemType::BinaryInteger, 22),
      Cell(ItemType::Boolean, 23),
      Cell(ItemType::String, 24),
    }, 
    // reduce
    { 
    }
  ),
  // state: 26
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 7),
      Cell(ItemType::SeparatorCloseSquareBracket, 36),
      Cell(ItemType::DecimalInteger, 20),
      Cell(ItemType::HexadecimalInteger, 21),
      Cell(ItemType::BinaryInteger, 22),
      Cell(ItemType::Boolean, 23),
      Cell(ItemType::String, 24),
    }, 
    // reduce
    { 
    }
  ),
  // state: 27
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 18),
      Cell(ItemType::SeparatorSemicolon, 18),
      Cell(ItemType::SeparatorCloseSquareBracket, 18),
      Cell(ItemType::DecimalInteger, 18),
      Cell(ItemType::HexadecimalInteger, 18),
      Cell(ItemType::BinaryInteger, 18),
      Cell(ItemType::Boolean, 18),
      Cell(ItemType::String, 18),
    }
  ),
  // state: 28
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 21),
      Cell(ItemType::SeparatorSemicolon, 21),
      Cell(ItemType::SeparatorCloseSquareBracket, 21),
      Cell(ItemType::DecimalInteger, 21),
      Cell(ItemType::HexadecimalInteger, 21),
      Cell(ItemType::BinaryInteger, 21),
      Cell(ItemType::Boolean, 21),
      Cell(ItemType::String, 21),
    }
  ),
  // state: 29
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 7),
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorCloseSquareBracket, 17),
    }
  ),
  // state: 30
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 19),
      Cell(ItemType::SeparatorSemicolon, 19),
      Cell(ItemType::SeparatorCloseSquareBracket, 19),
      Cell(ItemType::DecimalInteger, 19),
      Cell(ItemType::HexadecimalInteger, 19),
      Cell(ItemType::BinaryInteger, 19),
      Cell(ItemType::Boolean, 19),
      Cell(ItemType::String, 19),
    }
  ),
  // state: 31
  TableTypes(
    // shift
    { 
      Cell(ItemType::SeparatorComma, 6),
      Cell(ItemType::SeparatorSemicolon, 7),
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorCloseSquareBracket, 20),
    }
  ),
  // state: 32
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 22),
      Cell(ItemType::SeparatorSemicolon, 22),
      Cell(ItemType::SeparatorCloseSquareBracket, 22),
      Cell(ItemType::DecimalInteger, 22),
      Cell(ItemType::HexadecimalInteger, 22),
      Cell(ItemType::BinaryInteger, 22),
      Cell(ItemType::Boolean, 22),
      Cell(ItemType::String, 22),
    }
  ),
  // state: 33
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 4),
      Cell(ItemType::SeparatorSemicolon, 4),
      Cell(ItemType::SeparatorCloseCurlyBracket, 4),
      Cell(ItemType::End, 4),
    }
  ),
  // state: 34
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 3),
      Cell(ItemType::SeparatorSemicolon, 3),
      Cell(ItemType::SeparatorCloseCurlyBracket, 3),
      Cell(ItemType::End, 3),
    }
  ),
  // state: 35
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 16),
      Cell(ItemType::SeparatorSemicolon, 16),
      Cell(ItemType::SeparatorCloseCurlyBracket, 16),
      Cell(ItemType::End, 16),
    }
  ),
  // state: 36
  TableTypes(
    // shift
    { 
    }, 
    // reduce
    { 
      Cell(ItemType::SeparatorComma, 15),
      Cell(ItemType::SeparatorSemicolon, 15),
      Cell(ItemType::SeparatorCloseCurlyBracket, 15),
      Cell(ItemType::End, 15),
    }
  ),
};

} // namespace yalpconf

#endif // YALPCONF_SRC_PARSER_ACTION_TABLE_H_

