#ifndef YALPCONF_SRC_PARSER_GOTO_TABLE_H_
#define YALPCONF_SRC_PARSER_GOTO_TABLE_H_

#include <vector>
#include "parser/item.h"

namespace yalpconf {
  
struct GotoTable {
  public:
    struct Cell {
      ItemType item_top_stack;
      int goto_state;

      explicit Cell(ItemType item, int state) 
          : item_top_stack { item }, goto_state { state } {}
    };

    struct Result {
      bool found;
      const Cell* cell;

      explicit Result(bool found, const Cell* cell)
          : found { found }, cell { cell } {}
    };

    static Result Find(int state, ItemType item) {
      const auto& state_table { goto_table_[state] };
      const auto& cell { std::find_if(state_table.begin(), 
          state_table.end(), 
          [item](const Cell& cell) { 
              return cell.item_top_stack == item; 
          }) };
      if (cell != state_table.end()) {
        return Result(true, &(*cell));
      }  
      return Result(false, nullptr);
    } 
  private:
    static const std::vector<std::vector<Cell>> goto_table_;
};

inline const std::vector<std::vector<GotoTable::Cell>> GotoTable::goto_table_ {
  // state: 0
  { 
    Cell(ItemType::ConfigurationFile, 3), 
    Cell(ItemType::Object, 1),
    Cell(ItemType::SettingsList, 2),
    Cell(ItemType::ItemSeparators, 8),
    Cell(ItemType::Setting, 10),
  },
  // state: 1
  { 
  },
  // state: 2
  { 
    Cell(ItemType::SettingsList, 2),
    Cell(ItemType::ItemSeparators, 9),
    Cell(ItemType::Setting, 12),
  },
  // state: 3
  { 
  },
  // state: 4
  { 
    Cell(ItemType::SettingsList, 5),
    Cell(ItemType::ItemSeparators, 8),
    Cell(ItemType::Setting, 10),
  },
  // state: 5
  { 
    Cell(ItemType::SettingsList, 5),
    Cell(ItemType::ItemSeparators, 9),
    Cell(ItemType::Setting, 12),
  },
  // state: 6
  { 
  },
  // state: 7
  { 
  },
  // state: 8
  { 
  },
  // state: 9
  { 
  },
  // state: 10
  { 
    Cell(ItemType::ItemSeparators, 11),
  },
  // state: 11
  { 
  },
  // state: 12
  { 
    Cell(ItemType::ItemSeparators, 13),
  },
  // state: 13
  { 
  },
  // state: 14
  { 
  },
  // state: 15
  { 
    Cell(ItemType::Object, 18),
    Cell(ItemType::Array, 19),
    Cell(ItemType::Value, 17),
    Cell(ItemType::SettingValue, 16),
  },
  // state: 16
  { 
  },
  // state: 17
  { 
  },
  // state: 18
  { 
  },
  // state: 19
  { 
  },
  // state: 20
  { 
  },
  // state: 21
  { 
  },
  // state: 22
  { 
  },
  // state: 23
  { 
  },
  // state: 24
  { 
  },
  // state: 25
  { 
    Cell(ItemType::ItemSeparators, 27),
    Cell(ItemType::ValuesList, 26),
    Cell(ItemType::Value, 29),
  },
  // state: 26
  { 
    Cell(ItemType::ItemSeparators, 28),
    Cell(ItemType::ValuesList, 26),
    Cell(ItemType::Value, 31),
  },
  // state: 27
  { 
  },
  // state: 28
  { 
  },
  // state: 29
  { 
    Cell(ItemType::ItemSeparators, 30),
  },
  // state: 30
  { 
  },
  // state: 31
  { 
    Cell(ItemType::ItemSeparators, 32),
  },
  // state: 32
  { 
  },
  // state: 33
  { 
  },
  // state: 34
  { 
  },
  // state: 35
  { 
  },
  // state: 36
  { 
  },
};

} // namespace yalpconf

#endif // YALPCONF_SRC_PARSER_GOTO_TABLE_H_
