#define GenList (Name_)					\
enum class Name_ : std::uint64_t		\
{										\
#define code_							\
	None = 0							\
#include ErrorFile_						\
	, Maximum							\
};				


//#include <vector>															
//#include <map>																	
//#include <cstdint>																
//
//#define ErrorClassGen(name_)													\
//																				\
//																				\
//class name_																		\
//{																				\
//public:																			\
//	enum class Code : std::uint64_t												\
//	{																			\
//		None = 0,																\
//																				\
//		Maximum																	\
//	};																			\
//																				\
//private:																		\
//	static const std::map<const Code, const std::string> Messages;				\
//																				\
//public:																			\
//	static const std::string GetErrorMessage(const Code& code)					\
//	{																			\
//		auto found = Messages.find(code);										\
//		return (*found).second;													\
//	}																			\
//																				\
//	const Code code;															\
//																				\
//	name_()																		\
//		:																		\
//		code(Code::None)														\
//	{																			\
//	}																			\
//																				\
//	name_(const Code code)														\
//		:																		\
//		code(code)																\
//	{																			\
//	}																			\
//																				\
//	name_(const name_& other)													\
//		:																		\
//		code(other.code)														\
//	{																			\
//	}																			\
//																				\
//	name_(const name_&& other)													\
//		:																		\
//		code(std::move(other.code))												\
//	{																			\
//	}																			\
//																				\
//	~name_() = default;															\
//																				\
//	const bool operator!=(const name_& other) const noexcept					\
//	{																			\
//		return code != other.code;												\
//	}																			\
//																				\
//	const bool operator(const name_::Code& other) const noexcept				\
//	{																			\
//		return code != other;													\
//	}																			\
//																				\
//	const bool operator!=(const int& codeValue) const noexcept					\
//	{																			\
//		return static_cast<int>(code) != codeValue;								\
//	}																			\
//																				\
//	const uint64_t ToInt() const noexcept										\
//	{																			\
//		return static_cast<uint64_t>(code);										\
//	}																			\
//																				\
//	operator Code() const noexcept												\
//	{																			\
//		return code;															\
//	}																			\
//																				\
//	const std::string Message() const noexcept									\
//	{																			\
//		return GetErrorMessage(code);											\
//	}																			\
//																				\
//	const bool IsNone() const noexcept											\
//	{																			\
//		return code == Code::None;												\
//	}																			\
//																				\
//	const bool IsMaximum() const noexcept										\
//	{																			\
//		return code == Code::Maximum;											\
//	}																			\
//																				\	
//																				\
//};																				\
//																				\
//const std::map<const name_::Code, const std::string> name_::Messages =			\
//{																				\
//	{	name_::Code::None, "None" }												\
//																				\
//	,{ name_::Code::Maximum, "Maximum" }										\
//};																				
