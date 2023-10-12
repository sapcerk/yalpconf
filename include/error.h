#ifndef YALPCONF_INCLUDE_ERROR_H_
#define YALPCONF_INCLUDE_ERROR_H_

#include <string>
#include <unordered_map>

namespace yalpconf {

enum class ErrorCode : int {
  None = 0,
  CantOpenFile,
  UnexpectedSymbol,
  ParserReduce,
  ParserShift,
  ParserGoto,
  ParserUnexpectedToken,
  ParserAlreadyInScope,
};

class Error {
  public:
    explicit Error();
    explicit Error(ErrorCode code);
    explicit Error(ErrorCode code, size_t line);
    explicit Error(ErrorCode code, size_t line, std::string near_string);
    explicit Error(ErrorCode code, size_t line, char near_string);
    explicit Error(ErrorCode code, size_t line, 
        std::string near_string, std::string expected_string);
    Error(const Error& other);
    Error(Error&& other) noexcept;
    ErrorCode GetCode() const;
    int GetCodeInt() const;
    size_t GetLine() const;
    std::string GetNearString() const;
    std::string GetExpectedString() const;
    std::string GetMessage() const;
    Error& operator=(const Error& other);
    Error& operator=(Error&& other) noexcept;
  private:
    ErrorCode code_;
    size_t line_;
    std::string near_string_;
    std::string expected_string_;
    static const std::unordered_map<ErrorCode, std::string> message_;
};

inline const std::unordered_map<ErrorCode, std::string> Error::message_ {
  { ErrorCode::CantOpenFile, "Unable to open file." },
  { ErrorCode::UnexpectedSymbol, "The lexical analyzer detected an unexpected symbol." },
  { ErrorCode::ParserReduce, "Parser unable to perform reduce action." },
  { ErrorCode::ParserShift, "Parser unable to perform shift action." },
  { ErrorCode::ParserGoto, "Parser unable to perform goto action." },
  { ErrorCode::ParserUnexpectedToken, "Parser detected an unexpected item." },
  { ErrorCode::ParserAlreadyInScope, "Setting with the same name already exists in scope." },
};

} // namespace yalpconf

#endif // YALPCONF_INCLUDE_ERROR_H_
