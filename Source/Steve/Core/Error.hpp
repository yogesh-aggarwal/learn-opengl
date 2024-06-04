#pragma once

#include <string>
#include <vector>
#include <source_location>

enum ErrorCode
{
   /* Generic Error Codes */

   Undefined = -1,
   Unknown   = 0x00,

   /* Syscalls Error Codes */

   FILE_IO             = EIO,
   FILE_NOT_FOUND      = ENOENT,
   FILE_ALREADY_EXISTS = EEXIST,

   OPERATION_NOT_PERMITTED = EPERM,

   MKDIR_FAILED  = EACCES,
   MKDIR_EXISTED = EEXIST,

   MOUNT_FAILED      = EACCES,
   MOUNT_BIND_FAILED = EACCES,

   RMDIR_FAILED = EACCES,

   /* Reset the enum counter */

   STEVE_ERROR = 1 << 24,

   /* Utility Error Codes */

   STEVE_SHADER_INTIALIZE_FROM_FILE_FAILED,
   STEVE_SHADER_COMPILE_FAILED,
   STEVE_INVALID_SHADER_TYPE,
};

class ErrorUnit
{
private:
   ErrorCode            m_Code;
   std::string          m_Message;
   std::source_location m_Location;

public:
   ErrorUnit(ErrorCode            code,
             std::source_location location = std::source_location::current());
   ErrorUnit(ErrorCode            code,
             std::string          message,
             std::source_location location = std::source_location::current());

   ErrorCode
   GetCode() const;

   std::string
   GetMessage() const;

   const std::source_location &
   GetLocation() const;

   operator std::string() const;
};

class Error
{
private:
   std::vector<ErrorUnit> m_Errors;

public:
   Error();
   Error(const ErrorUnit &unit);
   Error(const std::vector<ErrorUnit> &errors);

   void
   Push(const ErrorUnit &unit);

   void
   Clear();

   operator bool() const;

   const ErrorUnit &
   First() const;

   const ErrorUnit &
   Last() const;

   void
   Print(const std::string &title = "") const;

   void
   Raise() const;

private:
   void
   PrintAtCenter(int         shellColumns,
                 std::string message,
                 std::string startDecorator   = "",
                 std::string endDecorator     = "",
                 bool        separatorAtStart = false,
                 bool        separatorAtEnd   = false) const;
};