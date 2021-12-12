%require "3.4"

%skeleton "lalr1.cc"
%language "C++"

%defines "ocf.bison.hpp"
%output "ocf.bison.cpp"
%define api.namespace {ocf::__private}
%define api.parser.class {parser}
%define api.prefix {ocf}

%code requires {
namespace ocf::__private {
	class lexer;
	class driver;
}
}

%parse-param {lexer &__lxr} {driver &__drv}
%lex-param {lexer &__lxr}

%code {
#include "ocf.reflex.hpp"
static inline ocf::__private::parser::symbol_type ocflex(ocf::__private::lexer &__lxr) noexcept
{ return __lxr.lex(); }
}

%define parse.assert true
%define parse.error detailed
%define parse.lac full

%define api.token.constructor
%define api.token.raw
%define api.value.type variant

%locations
%define api.location.file "location.hpp"
%define api.location.include {"location.hpp"}
%define api.filename.type {std::string}

%token THIS

%token OPEN_BRACE CLOSE_BRACE
		OPEN_PARENTHESIS CLOSE_PARENTHESIS
		OPEN_BRACKET CLOSE_BRACKET
		LESSER GREATER

%token BITWISE_OR EQUAL COLON
		DOUBLE_COLON SEMICOLON
		COMMA

%code requires {
#include <ctl/string>
#include <ctl/variant>
#include <ctl/cstddef>
}

%token <bool> BOOL_LITERAL

%token <double> DOUBLE_LITERAL
%token <long double> LONG_DOUBLE_LITERAL
%token <float> FLOAT_LITERAL

%token <int> INT_LITERAL
%token <long> LONG_LITERAL
%token <long long> LONG_LONG_LITERAL
%token <long long> SSIZE_LITERAL

%token <unsigned int> UNSIGNED_INT_LITERAL
%token <unsigned long> UNSIGNED_LONG_LITERAL
%token <unsigned long long> UNSIGNED_LONG_LONG_LITERAL
%token <unsigned long long> SIZE_LITERAL

%token <std::string> STRING_LITERAL
%token <std::u8string> U8STRING_LITERAL
%token <std::u16string> U16STRING_LITERAL
%token <std::u32string> U32STRING_LITERAL
%token <std::wstring> WSTRING_LITERAL

%token <char> CHAR_LITERAL
%token <char8_t> U8CHAR_LITERAL
%token <char16_t> U16CHAR_LITERAL
%token <char32_t> U32CHAR_LITERAL
%token <wchar_t> WCHAR_LITERAL

%token <std::string> IDENTIFIER

%nterm <ctl::literal_variant> string_literal literal
								identifier.literal
								identifier.string_literal

%code {
#include "../driver.hpp"
}

%initial-action {
	if(!__drv.init()) {
		YYABORT;
	}
}

%start main

%%
string_literal:
	STRING_LITERAL { $$.emplace<ctl::literal_variant::indexes::string>(std::move($1)); } |
	U8STRING_LITERAL {
	#ifdef __cpp_char8_t
		$$.emplace<ctl::literal_variant::indexes::u8string>(std::move($1));
	#else
		$$.emplace<ctl::literal_variant::indexes::string>(std::move($1));
	#endif
	} |
	U16STRING_LITERAL { $$.emplace<ctl::literal_variant::indexes::u16string>(std::move($1)); } |
	U32STRING_LITERAL { $$.emplace<ctl::literal_variant::indexes::u32string>(std::move($1)); } |
	WSTRING_LITERAL { $$.emplace<ctl::literal_variant::indexes::wstring>(std::move($1)); } |
	CHAR_LITERAL { $$.emplace<ctl::literal_variant::indexes::char_>(std::move($1)); } |
	U8CHAR_LITERAL {
	#ifdef __cpp_char8_t
		$$.emplace<ctl::literal_variant::indexes::char8_t_>(std::move($1));
	#else
		$$.emplace<ctl::literal_variant::indexes::char_>(std::move($1));
	#endif
	} |
	U16CHAR_LITERAL { $$.emplace<ctl::literal_variant::indexes::char16_t_>(std::move($1)); } |
	U32CHAR_LITERAL { $$.emplace<ctl::literal_variant::indexes::char32_t_>(std::move($1)); } |
	WCHAR_LITERAL { $$.emplace<ctl::literal_variant::indexes::wchar_t_>(std::move($1)); }

literal:
	string_literal |
	BOOL_LITERAL { $$.emplace<ctl::literal_variant::indexes::bool_>(std::move($1)); } |
	DOUBLE_LITERAL { $$.emplace<ctl::literal_variant::indexes::double_>(std::move($1)); } |
	LONG_DOUBLE_LITERAL { $$.emplace<ctl::literal_variant::indexes::long_double>(std::move($1)); } |
	FLOAT_LITERAL { $$.emplace<ctl::literal_variant::indexes::float_>(std::move($1)); } |
	INT_LITERAL { $$.emplace<ctl::literal_variant::indexes::int_>(std::move($1)); } |
	LONG_LITERAL { $$.emplace<ctl::literal_variant::indexes::long_>(std::move($1)); } |
	LONG_LONG_LITERAL { $$.emplace<ctl::literal_variant::indexes::long_long>(std::move($1)); } |
	SSIZE_LITERAL { $$.emplace<ctl::literal_variant::indexes::ssize_t_>(std::move($1)); } |
	UNSIGNED_INT_LITERAL { $$.emplace<ctl::literal_variant::indexes::unsigned_int>(std::move($1)); } |
	UNSIGNED_LONG_LITERAL { $$.emplace<ctl::literal_variant::indexes::unsigned_long>(std::move($1)); } |
	UNSIGNED_LONG_LONG_LITERAL { $$.emplace<ctl::literal_variant::indexes::unsigned_long_long>(std::move($1)); } |
	SIZE_LITERAL { $$.emplace<ctl::literal_variant::indexes::size_t_>(std::move($1)); }

identifier.string_literal:
	string_literal { $$ = std::move($1); } |
	IDENTIFIER { $$.emplace<ctl::literal_variant::indexes::string>(std::move($1)); }

identifier.literal:
	literal { $$ = std::move($1); } |
	IDENTIFIER { $$.emplace<ctl::literal_variant::indexes::string>(std::move($1)); }

object_attributes:
	OPEN_BRACKET OPEN_BRACKET {
		if(!__drv.push_attributes()) {
			YYABORT;
		}
	} top_level.loop CLOSE_BRACKET CLOSE_BRACKET

object_attributes.opt:
	object_attributes |
	%empty

object_namespace_header:
	identifier.string_literal {
		if(!__drv.push_namespace(std::move($1))) {
			YYABORT;
		}
	}

object_namespace.loop:
	object_namespace_header DOUBLE_COLON object_namespace_header DOUBLE_COLON object_namespace.loop |
	object_namespace_header DOUBLE_COLON object_namespace_header

object_namespace:
	object_namespace.loop {
		if(!__drv.end_namespace()) {
			YYABORT;
		}
	}

object_header_simple:
	identifier.string_literal {
		if(!__drv.push(std::move($1))) {
			YYABORT;
		}
	} |
	object_namespace

object_group_header:
	identifier.string_literal {
		if(!__drv.push_group(std::move($1))) {
			YYABORT;
		}
	} |
	THIS {
		if(!__drv.push_this_group()) {
			YYABORT;
		}
	}

object_group.loop:
	object_group_header BITWISE_OR object_group_header BITWISE_OR object_group.loop |
	object_group_header BITWISE_OR object_group_header

object_group:
	object_group.loop {
		if(!__drv.end_group()) {
			YYABORT;
		}
	}

this:
	THIS {
		if(!__drv.push_this()) {
			YYABORT;
		}
	}

object_header:
	this |
	object_group

object_value:
	identifier.literal {
		if(!__drv.assign(std::move($1))) {
			YYABORT;
		}
	}

object_body:
	OPEN_BRACE top_level.loop CLOSE_BRACE {
		if(!__drv.section_end()) {
			YYABORT;
		}
	}

object_body.opt:
	object_body |
	%empty

array_pair:
	identifier.string_literal EQUAL identifier.literal {
		if(!__drv.array_value(std::move($1), std::move($3))) {
			YYABORT;
		}
	} |
	identifier.literal {
		if(!__drv.array_value(std::move($1))) {
			YYABORT;
		}
	}

array_level:
	array_pair COMMA

array_level.loop_impl:
	array_level array_level.loop |
	array_level

array_level.loop:
	array_level.loop_impl |
	array_pair

object_array:
	OPEN_BRACKET array_level.loop CLOSE_BRACKET

object_end:
	EQUAL object_value object_attributes.opt object_body.opt |
	EQUAL object_body |
	object_attributes object_body.opt |
	object_body |
	EQUAL object_array

object_end_simple:
	object_end |
	%empty

object:
	object_header_simple object_end_simple |
	object_header object_end

semicolon.opt:
	SEMICOLON |
	%empty

object_section_header:
	object_header_simple |
	object_header

object_section_begin:
	LESSER {
		if(!__drv.pre_section(false)) {
			YYABORT;
		}
	} object_section_header GREATER {
		if(!__drv.after_section(false)) {
			YYABORT;
		}
	} |
	OPEN_PARENTHESIS {
		if(!__drv.pre_section(true)) {
			YYABORT;
		}
	} object_section_header CLOSE_PARENTHESIS {
		if(!__drv.after_section(true)) {
			YYABORT;
		}
	}

object_section_end:
	LESSER GREATER {
		if(!__drv.end_section(false)) {
			YYABORT;
		}
	} |
	OPEN_PARENTHESIS CLOSE_PARENTHESIS {
		if(!__drv.end_section(true)) {
			YYABORT;
		}
	}

top_level:
	object semicolon.opt {
		if(!__drv.pop()) {
			YYABORT;
		}
	} |
	object_section_begin |
	object_section_end

top_level.loop:
	top_level top_level.loop |
	top_level

main:
	top_level.loop
%%

void ocf::__private::parser::error(const location_type &loc, const std::string &msg)
{ __drv.error(loc, msg); }