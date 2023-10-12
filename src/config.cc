#include <memory>
#include <string>

#include "config.h"
#include "reader/reader.h"
#include "lexical_analyzer/lexical_analyzer.h"
#include "parser/parser.h"
#include "error.h"
#include "types/object.h"
#include "reader/blocking_file_reader.h"
#include "lexical_analyzer/blocking_lexical_analyzer.h"
#include "parser/lr0_parser.h"

namespace yalpconf {

Config::Config(const std::string& file_name) 
    : file_name_ { file_name } {}

Error Config::ReadConfiguration() {
  Error error(ErrorCode::None);
  std::unique_ptr<BlockingFileReader> reader { 
      std::make_unique<BlockingFileReader>(file_name_) };
  error = reader->ReadConfiguration();
  if (error.GetCode() != ErrorCode::None || reader->empty())
    return error;
  std::unique_ptr<BlockingLexicalAnalyzer> lexical_analyzer {
    std::make_unique<BlockingLexicalAnalyzer>(std::move(reader)) };
  error = lexical_analyzer->ScanTokens();
  if (error.GetCode() != ErrorCode::None || lexical_analyzer->empty())
    return error;
  yalpconf::Lr0Parser parser(std::move(lexical_analyzer));
  error = parser.ParseTokens();
  if (error.GetCode() != ErrorCode::None)
    return error;
  root_object_ = parser.GetRootObject();
  return error;
}

std::shared_ptr<Object> Config::GetRootObject() {
  return root_object_;
}

} // namespace yalpconf
