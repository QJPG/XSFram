#pragma once

#include <vector>
#include <map>

class XSFML
{
private:
	enum TokenTypes {
		KEYWORD,
		NUMBER,
		STRING_BEGIN,
		STRING_END,
		KEY_DECLARE,
		TYPE_DECLARE,
		SET_OPERATOR,
	};

	struct Token {
		TokenTypes								tk_Type;
		const char*								tk_Value = "";
	};

	struct KeyValue {
		const char*								kv_Name = "";
	};

	struct KeySection {
		const char*								ks_Name = "";
		const char*								ks_Parent = "";

		std::map<const char*, KeyValue>			ks_Values;

	};

	struct Parser {
		std::vector<Token>						vec_Tokens;
		
		std::map<const char*, int>				cache_i32Vars;
		std::map<const char*, unsigned int>		cache_u32Vars;
		std::map<const char*, short>			cache_i16Vars;
		std::map<const char*, unsigned short>	cache_u16Vars;


	};

	Parser* parser = NULL;

public:
	void parse(const char * data);


};

