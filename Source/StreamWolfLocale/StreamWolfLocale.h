// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the STREAMWOLFLOCALE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// STREAMWOLFLOCALE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#ifdef _MSC_VER

#define LOCALE_NOT_FOUND 1

#ifdef STREAMWOLFLOCALE_EXPORTS
#define STREAMWOLFLOCALE_API __declspec(dllexport)
#else
#define STREAMWOLFLOCALE_API __declspec(dllimport)
#endif

#elif __CYGWIN

#ifdef STREAMWOLFLOCALE_EXPORTS
#define STREAMWOLFLOCALE_API __attribute__ ((dllexport))
#else
#define STREAMWOLFLOCALE_API __attribute__ ((dllimport))
#endif

#else

#if __GNUC__ >= 4
#define STREAMWOLFLOCALE_API __attribute__ ((visibility ("default")))
#else
#define STREAMWOLFLOCALE_API
#endif

#define NOEXCEPT noexcept
#endif

#include <boost/noncopyable.hpp>
#include <pugixml/pugixml.hpp>
#include <memory>
#include <string>
#include <map>

class STREAMWOLFLOCALE_API StringTable : public boost::noncopyable
{
public:
    StringTable(const std::string& locale);
    ~StringTable();

    std::string GetString(const std::string& variable) const;

private:

    std::shared_ptr<pugi::xml_document> mFile;
};

typedef std::shared_ptr<StringTable> StringTablePtr;

STREAMWOLFLOCALE_API StringTablePtr GetStringTable(const std::string& locale);