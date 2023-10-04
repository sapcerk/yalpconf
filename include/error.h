#ifndef YALPCONF_SRC_ERROR_H_
#define YALPCONF_SRC_ERROR_H_

namespace yalpconf {

enum class ErrorCode : int {
  None = 0,
  CantOpenFile,
  UnexpectedSymbol,
};

class Error {
  public:
    explicit Error();
    explicit Error(ErrorCode code);
    explicit Error(ErrorCode code, size_t line);
    explicit Error(ErrorCode code, size_t line, std::string near_string);
    explicit Error(ErrorCode code, size_t line, char near_string);
    Error(const Error& other);
    Error(Error&& other) noexcept;
    ErrorCode GetCode() const;
    int GetCodeInt() const;
    size_t GetLine() const;
    std::string GetNearString() const;
    std::string GetMessage() const;
    Error& operator=(const Error& other);
    Error& operator=(Error&& other) noexcept;
  private:
    ErrorCode code_;
    size_t line_;
    std::string near_string_;
};

} // namespace yalpconf

#endif // YALPCONF_SRC_ERROR_H_
