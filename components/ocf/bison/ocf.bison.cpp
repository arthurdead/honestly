// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   ocflex



#include "ocf.bison.hpp"


// Unqualified %code blocks.
#line 27 "/hd2/honestly/components/ocf/bison/ocf.bison"

#include "ocf.reflex.hpp"
static ocf::__private::parser::symbol_type ocflex(ocf::__private::lexer &lex) noexcept
{ return lex.lex(); }

#include "../driver.hpp"
#line 91 "/hd2/honestly/components/ocf/bison/ocf.bison"

#include <ctl/string_view>
#include <ocf/object.hpp>

#line 60 "ocf.bison.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if OCFDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !OCFDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !OCFDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 7 "/hd2/honestly/components/ocf/bison/ocf.bison"
namespace ocf { namespace __private {
#line 153 "ocf.bison.cpp"

  /// Build a parser object.
  parser::parser (ocf::__private::lexer &__lex_yyarg, ocf::__private::driver &__drv_yyarg)
#if OCFDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      yy_lac_established_ (false),
      __lex (__lex_yyarg),
      __drv (__drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_BOOL_LITERAL: // BOOL_LITERAL
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CHAR_LITERAL: // CHAR_LITERAL
        value.YY_MOVE_OR_COPY< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U16CHAR_LITERAL: // U16CHAR_LITERAL
        value.YY_MOVE_OR_COPY< char16_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U32CHAR_LITERAL: // U32CHAR_LITERAL
        value.YY_MOVE_OR_COPY< char32_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U8CHAR_LITERAL: // U8CHAR_LITERAL
        value.YY_MOVE_OR_COPY< char8_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string_literal: // string_literal
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_57_identifier_literal: // identifier.literal
      case symbol_kind::S_58_identifier_string_literal: // identifier.string_literal
        value.YY_MOVE_OR_COPY< ctl::literal_variant > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DOUBLE_LITERAL: // DOUBLE_LITERAL
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LONG_LITERAL: // LONG_LITERAL
        value.YY_MOVE_OR_COPY< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LONG_DOUBLE_LITERAL: // LONG_DOUBLE_LITERAL
        value.YY_MOVE_OR_COPY< long double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LONG_LONG_LITERAL: // LONG_LONG_LITERAL
      case symbol_kind::S_SIZE_LITERAL: // SIZE_LITERAL
        value.YY_MOVE_OR_COPY< long long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U16STRING_LITERAL: // U16STRING_LITERAL
        value.YY_MOVE_OR_COPY< std::u16string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U32STRING_LITERAL: // U32STRING_LITERAL
        value.YY_MOVE_OR_COPY< std::u32string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U8STRING_LITERAL: // U8STRING_LITERAL
        value.YY_MOVE_OR_COPY< std::u8string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WSTRING_LITERAL: // WSTRING_LITERAL
        value.YY_MOVE_OR_COPY< std::wstring > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_INT_LITERAL: // UNSIGNED_INT_LITERAL
        value.YY_MOVE_OR_COPY< unsigned int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_LONG_LITERAL: // UNSIGNED_LONG_LITERAL
        value.YY_MOVE_OR_COPY< unsigned long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_LONG_LONG_LITERAL: // UNSIGNED_LONG_LONG_LITERAL
      case symbol_kind::S_UNSIGNED_SIZE_LITERAL: // UNSIGNED_SIZE_LITERAL
        value.YY_MOVE_OR_COPY< unsigned long long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WCHAR_LITERAL: // WCHAR_LITERAL
        value.YY_MOVE_OR_COPY< wchar_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_BOOL_LITERAL: // BOOL_LITERAL
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CHAR_LITERAL: // CHAR_LITERAL
        value.move< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U16CHAR_LITERAL: // U16CHAR_LITERAL
        value.move< char16_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U32CHAR_LITERAL: // U32CHAR_LITERAL
        value.move< char32_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U8CHAR_LITERAL: // U8CHAR_LITERAL
        value.move< char8_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string_literal: // string_literal
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_57_identifier_literal: // identifier.literal
      case symbol_kind::S_58_identifier_string_literal: // identifier.string_literal
        value.move< ctl::literal_variant > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DOUBLE_LITERAL: // DOUBLE_LITERAL
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
        value.move< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
        value.move< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LONG_LITERAL: // LONG_LITERAL
        value.move< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LONG_DOUBLE_LITERAL: // LONG_DOUBLE_LITERAL
        value.move< long double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LONG_LONG_LITERAL: // LONG_LONG_LITERAL
      case symbol_kind::S_SIZE_LITERAL: // SIZE_LITERAL
        value.move< long long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U16STRING_LITERAL: // U16STRING_LITERAL
        value.move< std::u16string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U32STRING_LITERAL: // U32STRING_LITERAL
        value.move< std::u32string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U8STRING_LITERAL: // U8STRING_LITERAL
        value.move< std::u8string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WSTRING_LITERAL: // WSTRING_LITERAL
        value.move< std::wstring > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_INT_LITERAL: // UNSIGNED_INT_LITERAL
        value.move< unsigned int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_LONG_LITERAL: // UNSIGNED_LONG_LITERAL
        value.move< unsigned long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_LONG_LONG_LITERAL: // UNSIGNED_LONG_LONG_LITERAL
      case symbol_kind::S_UNSIGNED_SIZE_LITERAL: // UNSIGNED_SIZE_LITERAL
        value.move< unsigned long long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WCHAR_LITERAL: // WCHAR_LITERAL
        value.move< wchar_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_BOOL_LITERAL: // BOOL_LITERAL
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_CHAR_LITERAL: // CHAR_LITERAL
        value.copy< char > (that.value);
        break;

      case symbol_kind::S_U16CHAR_LITERAL: // U16CHAR_LITERAL
        value.copy< char16_t > (that.value);
        break;

      case symbol_kind::S_U32CHAR_LITERAL: // U32CHAR_LITERAL
        value.copy< char32_t > (that.value);
        break;

      case symbol_kind::S_U8CHAR_LITERAL: // U8CHAR_LITERAL
        value.copy< char8_t > (that.value);
        break;

      case symbol_kind::S_string_literal: // string_literal
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_57_identifier_literal: // identifier.literal
      case symbol_kind::S_58_identifier_string_literal: // identifier.string_literal
        value.copy< ctl::literal_variant > (that.value);
        break;

      case symbol_kind::S_DOUBLE_LITERAL: // DOUBLE_LITERAL
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
        value.copy< float > (that.value);
        break;

      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
        value.copy< int > (that.value);
        break;

      case symbol_kind::S_LONG_LITERAL: // LONG_LITERAL
        value.copy< long > (that.value);
        break;

      case symbol_kind::S_LONG_DOUBLE_LITERAL: // LONG_DOUBLE_LITERAL
        value.copy< long double > (that.value);
        break;

      case symbol_kind::S_LONG_LONG_LITERAL: // LONG_LONG_LITERAL
      case symbol_kind::S_SIZE_LITERAL: // SIZE_LITERAL
        value.copy< long long > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_U16STRING_LITERAL: // U16STRING_LITERAL
        value.copy< std::u16string > (that.value);
        break;

      case symbol_kind::S_U32STRING_LITERAL: // U32STRING_LITERAL
        value.copy< std::u32string > (that.value);
        break;

      case symbol_kind::S_U8STRING_LITERAL: // U8STRING_LITERAL
        value.copy< std::u8string > (that.value);
        break;

      case symbol_kind::S_WSTRING_LITERAL: // WSTRING_LITERAL
        value.copy< std::wstring > (that.value);
        break;

      case symbol_kind::S_UNSIGNED_INT_LITERAL: // UNSIGNED_INT_LITERAL
        value.copy< unsigned int > (that.value);
        break;

      case symbol_kind::S_UNSIGNED_LONG_LITERAL: // UNSIGNED_LONG_LITERAL
        value.copy< unsigned long > (that.value);
        break;

      case symbol_kind::S_UNSIGNED_LONG_LONG_LITERAL: // UNSIGNED_LONG_LONG_LITERAL
      case symbol_kind::S_UNSIGNED_SIZE_LITERAL: // UNSIGNED_SIZE_LITERAL
        value.copy< unsigned long long > (that.value);
        break;

      case symbol_kind::S_WCHAR_LITERAL: // WCHAR_LITERAL
        value.copy< wchar_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_BOOL_LITERAL: // BOOL_LITERAL
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_CHAR_LITERAL: // CHAR_LITERAL
        value.move< char > (that.value);
        break;

      case symbol_kind::S_U16CHAR_LITERAL: // U16CHAR_LITERAL
        value.move< char16_t > (that.value);
        break;

      case symbol_kind::S_U32CHAR_LITERAL: // U32CHAR_LITERAL
        value.move< char32_t > (that.value);
        break;

      case symbol_kind::S_U8CHAR_LITERAL: // U8CHAR_LITERAL
        value.move< char8_t > (that.value);
        break;

      case symbol_kind::S_string_literal: // string_literal
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_57_identifier_literal: // identifier.literal
      case symbol_kind::S_58_identifier_string_literal: // identifier.string_literal
        value.move< ctl::literal_variant > (that.value);
        break;

      case symbol_kind::S_DOUBLE_LITERAL: // DOUBLE_LITERAL
        value.move< double > (that.value);
        break;

      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
        value.move< float > (that.value);
        break;

      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
        value.move< int > (that.value);
        break;

      case symbol_kind::S_LONG_LITERAL: // LONG_LITERAL
        value.move< long > (that.value);
        break;

      case symbol_kind::S_LONG_DOUBLE_LITERAL: // LONG_DOUBLE_LITERAL
        value.move< long double > (that.value);
        break;

      case symbol_kind::S_LONG_LONG_LITERAL: // LONG_LONG_LITERAL
      case symbol_kind::S_SIZE_LITERAL: // SIZE_LITERAL
        value.move< long long > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_U16STRING_LITERAL: // U16STRING_LITERAL
        value.move< std::u16string > (that.value);
        break;

      case symbol_kind::S_U32STRING_LITERAL: // U32STRING_LITERAL
        value.move< std::u32string > (that.value);
        break;

      case symbol_kind::S_U8STRING_LITERAL: // U8STRING_LITERAL
        value.move< std::u8string > (that.value);
        break;

      case symbol_kind::S_WSTRING_LITERAL: // WSTRING_LITERAL
        value.move< std::wstring > (that.value);
        break;

      case symbol_kind::S_UNSIGNED_INT_LITERAL: // UNSIGNED_INT_LITERAL
        value.move< unsigned int > (that.value);
        break;

      case symbol_kind::S_UNSIGNED_LONG_LITERAL: // UNSIGNED_LONG_LITERAL
        value.move< unsigned long > (that.value);
        break;

      case symbol_kind::S_UNSIGNED_LONG_LONG_LITERAL: // UNSIGNED_LONG_LONG_LITERAL
      case symbol_kind::S_UNSIGNED_SIZE_LITERAL: // UNSIGNED_SIZE_LITERAL
        value.move< unsigned long long > (that.value);
        break;

      case symbol_kind::S_WCHAR_LITERAL: // WCHAR_LITERAL
        value.move< wchar_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if OCFDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if OCFDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // OCFDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    /// Discard the LAC context in case there still is one left from a
    /// previous invocation.
    yy_lac_discard_ ("init");

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 97 "/hd2/honestly/components/ocf/bison/ocf.bison"
{
	if(!__drv.init()) {
		YYABORT;
	}
}

#line 786 "ocf.bison.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (__lex));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        if (!yy_lac_establish_ (yyla.kind ()))
           goto yyerrlab;
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        if (!yy_lac_establish_ (yyla.kind ()))
           goto yyerrlab;

        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    yy_lac_discard_ ("shift");
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_BOOL_LITERAL: // BOOL_LITERAL
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_CHAR_LITERAL: // CHAR_LITERAL
        yylhs.value.emplace< char > ();
        break;

      case symbol_kind::S_U16CHAR_LITERAL: // U16CHAR_LITERAL
        yylhs.value.emplace< char16_t > ();
        break;

      case symbol_kind::S_U32CHAR_LITERAL: // U32CHAR_LITERAL
        yylhs.value.emplace< char32_t > ();
        break;

      case symbol_kind::S_U8CHAR_LITERAL: // U8CHAR_LITERAL
        yylhs.value.emplace< char8_t > ();
        break;

      case symbol_kind::S_string_literal: // string_literal
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_57_identifier_literal: // identifier.literal
      case symbol_kind::S_58_identifier_string_literal: // identifier.string_literal
        yylhs.value.emplace< ctl::literal_variant > ();
        break;

      case symbol_kind::S_DOUBLE_LITERAL: // DOUBLE_LITERAL
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
        yylhs.value.emplace< float > ();
        break;

      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
        yylhs.value.emplace< int > ();
        break;

      case symbol_kind::S_LONG_LITERAL: // LONG_LITERAL
        yylhs.value.emplace< long > ();
        break;

      case symbol_kind::S_LONG_DOUBLE_LITERAL: // LONG_DOUBLE_LITERAL
        yylhs.value.emplace< long double > ();
        break;

      case symbol_kind::S_LONG_LONG_LITERAL: // LONG_LONG_LITERAL
      case symbol_kind::S_SIZE_LITERAL: // SIZE_LITERAL
        yylhs.value.emplace< long long > ();
        break;

      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_U16STRING_LITERAL: // U16STRING_LITERAL
        yylhs.value.emplace< std::u16string > ();
        break;

      case symbol_kind::S_U32STRING_LITERAL: // U32STRING_LITERAL
        yylhs.value.emplace< std::u32string > ();
        break;

      case symbol_kind::S_U8STRING_LITERAL: // U8STRING_LITERAL
        yylhs.value.emplace< std::u8string > ();
        break;

      case symbol_kind::S_WSTRING_LITERAL: // WSTRING_LITERAL
        yylhs.value.emplace< std::wstring > ();
        break;

      case symbol_kind::S_UNSIGNED_INT_LITERAL: // UNSIGNED_INT_LITERAL
        yylhs.value.emplace< unsigned int > ();
        break;

      case symbol_kind::S_UNSIGNED_LONG_LITERAL: // UNSIGNED_LONG_LITERAL
        yylhs.value.emplace< unsigned long > ();
        break;

      case symbol_kind::S_UNSIGNED_LONG_LONG_LITERAL: // UNSIGNED_LONG_LONG_LITERAL
      case symbol_kind::S_UNSIGNED_SIZE_LITERAL: // UNSIGNED_SIZE_LITERAL
        yylhs.value.emplace< unsigned long long > ();
        break;

      case symbol_kind::S_WCHAR_LITERAL: // WCHAR_LITERAL
        yylhs.value.emplace< wchar_t > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // string_literal: STRING_LITERAL
#line 105 "/hd2/honestly/components/ocf/bison/ocf.bison"
                       { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::string>(std::move(yystack_[0].value.as < std::string > ())); }
#line 1020 "ocf.bison.cpp"
    break;

  case 3: // string_literal: U8STRING_LITERAL
#line 106 "/hd2/honestly/components/ocf/bison/ocf.bison"
                         {
	#ifdef __cpp_char8_t
		yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::u8string>(std::move(yystack_[0].value.as < std::u8string > ()));
	#else
		yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::string>(std::move(yystack_[0].value.as < std::u8string > ()));
	#endif
	}
#line 1032 "ocf.bison.cpp"
    break;

  case 4: // string_literal: U16STRING_LITERAL
#line 113 "/hd2/honestly/components/ocf/bison/ocf.bison"
                          { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::u16string>(std::move(yystack_[0].value.as < std::u16string > ())); }
#line 1038 "ocf.bison.cpp"
    break;

  case 5: // string_literal: U32STRING_LITERAL
#line 114 "/hd2/honestly/components/ocf/bison/ocf.bison"
                          { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::u32string>(std::move(yystack_[0].value.as < std::u32string > ())); }
#line 1044 "ocf.bison.cpp"
    break;

  case 6: // string_literal: WSTRING_LITERAL
#line 115 "/hd2/honestly/components/ocf/bison/ocf.bison"
                        { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::wstring>(std::move(yystack_[0].value.as < std::wstring > ())); }
#line 1050 "ocf.bison.cpp"
    break;

  case 7: // literal: string_literal
#line 118 "/hd2/honestly/components/ocf/bison/ocf.bison"
                       { yylhs.value.as < ctl::literal_variant > () = std::move(yystack_[0].value.as < ctl::literal_variant > ()); }
#line 1056 "ocf.bison.cpp"
    break;

  case 8: // literal: CHAR_LITERAL
#line 119 "/hd2/honestly/components/ocf/bison/ocf.bison"
                     { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::char_>(yystack_[0].value.as < char > ()); }
#line 1062 "ocf.bison.cpp"
    break;

  case 9: // literal: U8CHAR_LITERAL
#line 120 "/hd2/honestly/components/ocf/bison/ocf.bison"
                       {
	#ifdef __cpp_char8_t
		yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::char8_t_>(yystack_[0].value.as < char8_t > ());
	#else
		yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::char_>(yystack_[0].value.as < char8_t > ());
	#endif
	}
#line 1074 "ocf.bison.cpp"
    break;

  case 10: // literal: U16CHAR_LITERAL
#line 127 "/hd2/honestly/components/ocf/bison/ocf.bison"
                        { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::char16_t_>(yystack_[0].value.as < char16_t > ()); }
#line 1080 "ocf.bison.cpp"
    break;

  case 11: // literal: U32CHAR_LITERAL
#line 128 "/hd2/honestly/components/ocf/bison/ocf.bison"
                        { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::char32_t_>(yystack_[0].value.as < char32_t > ()); }
#line 1086 "ocf.bison.cpp"
    break;

  case 12: // literal: WCHAR_LITERAL
#line 129 "/hd2/honestly/components/ocf/bison/ocf.bison"
                      { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::wchar_t_>(yystack_[0].value.as < wchar_t > ()); }
#line 1092 "ocf.bison.cpp"
    break;

  case 13: // literal: INT_LITERAL
#line 130 "/hd2/honestly/components/ocf/bison/ocf.bison"
                    { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::int_>(yystack_[0].value.as < int > ()); }
#line 1098 "ocf.bison.cpp"
    break;

  case 14: // literal: LONG_LITERAL
#line 131 "/hd2/honestly/components/ocf/bison/ocf.bison"
                     { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::long_>(yystack_[0].value.as < long > ()); }
#line 1104 "ocf.bison.cpp"
    break;

  case 15: // literal: LONG_LONG_LITERAL
#line 132 "/hd2/honestly/components/ocf/bison/ocf.bison"
                          { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::long_long>(yystack_[0].value.as < long long > ()); }
#line 1110 "ocf.bison.cpp"
    break;

  case 16: // literal: SIZE_LITERAL
#line 133 "/hd2/honestly/components/ocf/bison/ocf.bison"
                     { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::ssize_t_>(yystack_[0].value.as < long long > ()); }
#line 1116 "ocf.bison.cpp"
    break;

  case 17: // literal: UNSIGNED_INT_LITERAL
#line 134 "/hd2/honestly/components/ocf/bison/ocf.bison"
                             { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::unsigned_int>(yystack_[0].value.as < unsigned int > ()); }
#line 1122 "ocf.bison.cpp"
    break;

  case 18: // literal: UNSIGNED_LONG_LITERAL
#line 135 "/hd2/honestly/components/ocf/bison/ocf.bison"
                              { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::unsigned_long>(yystack_[0].value.as < unsigned long > ()); }
#line 1128 "ocf.bison.cpp"
    break;

  case 19: // literal: UNSIGNED_LONG_LONG_LITERAL
#line 136 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                   { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::unsigned_long_long>(yystack_[0].value.as < unsigned long long > ()); }
#line 1134 "ocf.bison.cpp"
    break;

  case 20: // literal: UNSIGNED_SIZE_LITERAL
#line 137 "/hd2/honestly/components/ocf/bison/ocf.bison"
                              { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::size_t_>(yystack_[0].value.as < unsigned long long > ()); }
#line 1140 "ocf.bison.cpp"
    break;

  case 21: // literal: DOUBLE_LITERAL
#line 138 "/hd2/honestly/components/ocf/bison/ocf.bison"
                       { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::double_>(yystack_[0].value.as < double > ()); }
#line 1146 "ocf.bison.cpp"
    break;

  case 22: // literal: LONG_DOUBLE_LITERAL
#line 139 "/hd2/honestly/components/ocf/bison/ocf.bison"
                            { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::long_double>(yystack_[0].value.as < long double > ()); }
#line 1152 "ocf.bison.cpp"
    break;

  case 23: // literal: FLOAT_LITERAL
#line 140 "/hd2/honestly/components/ocf/bison/ocf.bison"
                      { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::float_>(yystack_[0].value.as < float > ()); }
#line 1158 "ocf.bison.cpp"
    break;

  case 24: // literal: BOOL_LITERAL
#line 141 "/hd2/honestly/components/ocf/bison/ocf.bison"
                     { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::bool_>(yystack_[0].value.as < bool > ()); }
#line 1164 "ocf.bison.cpp"
    break;

  case 25: // identifier.literal: literal
#line 144 "/hd2/honestly/components/ocf/bison/ocf.bison"
                { yylhs.value.as < ctl::literal_variant > () = std::move(yystack_[0].value.as < ctl::literal_variant > ()); }
#line 1170 "ocf.bison.cpp"
    break;

  case 26: // identifier.literal: IDENTIFIER
#line 145 "/hd2/honestly/components/ocf/bison/ocf.bison"
                   { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::string>(std::move(yystack_[0].value.as < std::string > ())); }
#line 1176 "ocf.bison.cpp"
    break;

  case 27: // identifier.string_literal: string_literal
#line 148 "/hd2/honestly/components/ocf/bison/ocf.bison"
                       { yylhs.value.as < ctl::literal_variant > () = std::move(yystack_[0].value.as < ctl::literal_variant > ()); }
#line 1182 "ocf.bison.cpp"
    break;

  case 28: // identifier.string_literal: IDENTIFIER
#line 149 "/hd2/honestly/components/ocf/bison/ocf.bison"
                   { yylhs.value.as < ctl::literal_variant > ().emplace<ctl::literal_variant::indexes::string>(std::move(yystack_[0].value.as < std::string > ())); }
#line 1188 "ocf.bison.cpp"
    break;

  case 29: // object_value: identifier.literal
#line 152 "/hd2/honestly/components/ocf/bison/ocf.bison"
                           {
		if(!__drv.assign(std::move(yystack_[0].value.as < ctl::literal_variant > ()))) {
			YYABORT;
		}
	}
#line 1198 "ocf.bison.cpp"
    break;

  case 30: // object_group_header: identifier.string_literal
#line 168 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                  {
		if(!__drv.push_group(std::move(yystack_[0].value.as < ctl::literal_variant > ()))) {
			YYABORT;
		}
	}
#line 1208 "ocf.bison.cpp"
    break;

  case 31: // object_group_header: THIS
#line 173 "/hd2/honestly/components/ocf/bison/ocf.bison"
             {
		if(!__drv.push_this_group()) {
			YYABORT;
		}
	}
#line 1218 "ocf.bison.cpp"
    break;

  case 32: // $@1: %empty
#line 183 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                  {
		if(!__drv.push_attributes()) {
			YYABORT;
		}
	}
#line 1228 "ocf.bison.cpp"
    break;

  case 33: // $@2: %empty
#line 187 "/hd2/honestly/components/ocf/bison/ocf.bison"
                         {
		if(!__drv.pop()) {
			YYABORT;
		}
	}
#line 1238 "ocf.bison.cpp"
    break;

  case 39: // object_group.loop: object_group.loop_impl
#line 202 "/hd2/honestly/components/ocf/bison/ocf.bison"
                               {
		if(!__drv.end_group()) {
			YYABORT;
		}
	}
#line 1248 "ocf.bison.cpp"
    break;

  case 40: // object_inherit_namespace_header: identifier.string_literal
#line 209 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                  {
		YYABORT;
	}
#line 1256 "ocf.bison.cpp"
    break;

  case 43: // object_inherit_header: identifier.string_literal
#line 218 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                  {
		YYABORT;
	}
#line 1264 "ocf.bison.cpp"
    break;

  case 44: // object_inherit_header: THIS
#line 221 "/hd2/honestly/components/ocf/bison/ocf.bison"
             {
		YYABORT;
	}
#line 1272 "ocf.bison.cpp"
    break;

  case 45: // object_inherit_header: object_inherit_namespace.loop
#line 224 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                      {
		YYABORT;
	}
#line 1280 "ocf.bison.cpp"
    break;

  case 48: // object_inherit.loop: object_inherit.loop_impl
#line 233 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                 {
		YYABORT;
	}
#line 1288 "ocf.bison.cpp"
    break;

  case 49: // this: THIS
#line 238 "/hd2/honestly/components/ocf/bison/ocf.bison"
             {
		if(!__drv.push_this()) {
			YYABORT;
		}
	}
#line 1298 "ocf.bison.cpp"
    break;

  case 50: // object_header_simple: identifier.string_literal
#line 245 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                  {
		if(!__drv.push(std::move(yystack_[0].value.as < ctl::literal_variant > ()))) {
			YYABORT;
		}
	}
#line 1308 "ocf.bison.cpp"
    break;

  case 52: // object_namespace_header: identifier.string_literal
#line 253 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                  {
		if(!__drv.push_namespace(std::move(yystack_[0].value.as < ctl::literal_variant > ()))) {
			YYABORT;
		}
	}
#line 1318 "ocf.bison.cpp"
    break;

  case 55: // object_namespace: object_namespace.loop
#line 264 "/hd2/honestly/components/ocf/bison/ocf.bison"
                              {
		if(!__drv.end_namespace()) {
			YYABORT;
		}
	}
#line 1328 "ocf.bison.cpp"
    break;

  case 70: // $@3: %empty
#line 297 "/hd2/honestly/components/ocf/bison/ocf.bison"
               {
		if(!__drv.pre_section(false)) {
			YYABORT;
		}
	}
#line 1338 "ocf.bison.cpp"
    break;

  case 71: // object_section_begin: LESSER $@3 object_header GREATER
#line 301 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                {
		if(!__drv.after_section(false)) {
			YYABORT;
		}
	}
#line 1348 "ocf.bison.cpp"
    break;

  case 72: // $@4: %empty
#line 306 "/hd2/honestly/components/ocf/bison/ocf.bison"
                         {
		if(!__drv.pre_section(true)) {
			YYABORT;
		}
	}
#line 1358 "ocf.bison.cpp"
    break;

  case 73: // object_section_begin: OPEN_PARENTHESIS $@4 object_header CLOSE_PARENTHESIS
#line 310 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                          {
		if(!__drv.after_section(true)) {
			YYABORT;
		}
	}
#line 1368 "ocf.bison.cpp"
    break;

  case 78: // object_section_end: LESSER GREATER
#line 323 "/hd2/honestly/components/ocf/bison/ocf.bison"
                       {
		if(!__drv.end_section(false)) {
			YYABORT;
		}
	}
#line 1378 "ocf.bison.cpp"
    break;

  case 79: // object_section_end: OPEN_PARENTHESIS CLOSE_PARENTHESIS
#line 328 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                           {
		if(!__drv.end_section(true)) {
			YYABORT;
		}
	}
#line 1388 "ocf.bison.cpp"
    break;

  case 82: // array_pair: identifier.literal
#line 339 "/hd2/honestly/components/ocf/bison/ocf.bison"
                           {
		if(!__drv.array_value(std::move(yystack_[0].value.as < ctl::literal_variant > ()))) {
			YYABORT;
		}
	}
#line 1398 "ocf.bison.cpp"
    break;

  case 83: // array_pair: identifier.string_literal EQUAL identifier.literal
#line 344 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                                           {
		if(!__drv.array_value(std::move(yystack_[2].value.as < ctl::literal_variant > ()), std::move(yystack_[0].value.as < ctl::literal_variant > ()))) {
			YYABORT;
		}
	}
#line 1408 "ocf.bison.cpp"
    break;

  case 89: // object_body: OPEN_BRACE top_level.loop CLOSE_BRACE
#line 362 "/hd2/honestly/components/ocf/bison/ocf.bison"
                                              {
		if(!__drv.section_end()) {
			YYABORT;
		}
	}
#line 1418 "ocf.bison.cpp"
    break;

  case 93: // top_level: object semicolon.opt
#line 376 "/hd2/honestly/components/ocf/bison/ocf.bison"
                             {
		if(!__drv.pop()) {
			YYABORT;
		}
	}
#line 1428 "ocf.bison.cpp"
    break;


#line 1432 "ocf.bison.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      yy_lac_discard_ ("error recovery");
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  const char *
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    static const char *const yy_sname[] =
    {
    "end of file", "error", "invalid token", "IDENTIFIER", "STRING_LITERAL",
  "U8STRING_LITERAL", "U16STRING_LITERAL", "U32STRING_LITERAL",
  "WSTRING_LITERAL", "CHAR_LITERAL", "U8CHAR_LITERAL", "U16CHAR_LITERAL",
  "U32CHAR_LITERAL", "WCHAR_LITERAL", "OPEN_BRACE", "CLOSE_BRACE",
  "OPEN_BRACKET", "CLOSE_BRACKET", "OPEN_PARENTHESIS", "CLOSE_PARENTHESIS",
  "PLUS", "MINUS", "DIVIDE", "MULTIPLY", "EQUAL", "LOGICAL_NOT", "COLON",
  "SEMICOLON", "TERNARY", "MODULO", "BITWISE_OR", "BITWISE_AND",
  "BITWISE_XOR", "LESSER", "GREATER", "BITWISE_NOT", "COMMA", "DOT",
  "DOUBLE_COLON", "PLUS_PLUS", "MINUS_MINUS", "THIS", "BOOL_LITERAL",
  "INT_LITERAL", "LONG_LITERAL", "LONG_LONG_LITERAL", "SIZE_LITERAL",
  "UNSIGNED_INT_LITERAL", "UNSIGNED_LONG_LITERAL",
  "UNSIGNED_LONG_LONG_LITERAL", "UNSIGNED_SIZE_LITERAL", "DOUBLE_LITERAL",
  "LONG_DOUBLE_LITERAL", "FLOAT_LITERAL", "$accept", "string_literal",
  "literal", "identifier.literal", "identifier.string_literal",
  "object_value", "object_group_header", "object_attributes", "$@1", "$@2",
  "object_attributes.opt", "object_group.loop_impl", "object_group.loop",
  "object_inherit_namespace_header", "object_inherit_namespace.loop",
  "object_inherit_header", "object_inherit.loop_impl",
  "object_inherit.loop", "this", "object_header_simple",
  "object_namespace_header", "object_namespace.loop", "object_namespace",
  "object_header_nosimple", "object_header", "object_inherit",
  "object_body.opt", "object.end", "object.end_simple",
  "object_section_begin", "$@3", "$@4", "object_section",
  "object_section_end", "object", "array_pair", "comma.opt",
  "array_level.loop_impl", "array_level.loop", "object_body", "array_body",
  "semicolon.opt", "top_level", "top_level.loop", "main", YY_NULLPTR
    };
    return yy_sname[yysymbol];
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

#if OCFDEBUG
    // Execute LAC once. We don't care if it is successful, we
    // only do it for the sake of debugging output.
    if (!yyparser_.yy_lac_established_)
      yyparser_.yy_lac_check_ (yyla_.kind ());
#endif

    for (int yyx = 0; yyx < YYNTOKENS; ++yyx)
      {
        symbol_kind_type yysym = YY_CAST (symbol_kind_type, yyx);
        if (yysym != symbol_kind::S_YYerror
            && yysym != symbol_kind::S_YYUNDEF
            && yyparser_.yy_lac_check_ (yysym))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
      }
    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }


  bool
  parser::yy_lac_check_ (symbol_kind_type yytoken) const
  {
    // Logically, the yylac_stack's lifetime is confined to this function.
    // Clear it, to get rid of potential left-overs from previous call.
    yylac_stack_.clear ();
    // Reduce until we encounter a shift and thereby accept the token.
#if OCFDEBUG
    YYCDEBUG << "LAC: checking lookahead " << symbol_name (yytoken) << ':';
#endif
    std::ptrdiff_t lac_top = 0;
    while (true)
      {
        state_type top_state = (yylac_stack_.empty ()
                                ? yystack_[lac_top].state
                                : yylac_stack_.back ());
        int yyrule = yypact_[+top_state];
        if (yy_pact_value_is_default_ (yyrule)
            || (yyrule += yytoken) < 0 || yylast_ < yyrule
            || yycheck_[yyrule] != yytoken)
          {
            // Use the default action.
            yyrule = yydefact_[+top_state];
            if (yyrule == 0)
              {
                YYCDEBUG << " Err\n";
                return false;
              }
          }
        else
          {
            // Use the action from yytable.
            yyrule = yytable_[yyrule];
            if (yy_table_value_is_error_ (yyrule))
              {
                YYCDEBUG << " Err\n";
                return false;
              }
            if (0 < yyrule)
              {
                YYCDEBUG << " S" << yyrule << '\n';
                return true;
              }
            yyrule = -yyrule;
          }
        // By now we know we have to simulate a reduce.
        YYCDEBUG << " R" << yyrule - 1;
        // Pop the corresponding number of values from the stack.
        {
          std::ptrdiff_t yylen = yyr2_[yyrule];
          // First pop from the LAC stack as many tokens as possible.
          std::ptrdiff_t lac_size = std::ptrdiff_t (yylac_stack_.size ());
          if (yylen < lac_size)
            {
              yylac_stack_.resize (std::size_t (lac_size - yylen));
              yylen = 0;
            }
          else if (lac_size)
            {
              yylac_stack_.clear ();
              yylen -= lac_size;
            }
          // Only afterwards look at the main stack.
          // We simulate popping elements by incrementing lac_top.
          lac_top += yylen;
        }
        // Keep top_state in sync with the updated stack.
        top_state = (yylac_stack_.empty ()
                     ? yystack_[lac_top].state
                     : yylac_stack_.back ());
        // Push the resulting state of the reduction.
        state_type state = yy_lr_goto_state_ (top_state, yyr1_[yyrule]);
        YYCDEBUG << " G" << int (state);
        yylac_stack_.push_back (state);
      }
  }

  // Establish the initial context if no initial context currently exists.
  bool
  parser::yy_lac_establish_ (symbol_kind_type yytoken)
  {
    /* Establish the initial context for the current lookahead if no initial
       context is currently established.

       We define a context as a snapshot of the parser stacks.  We define
       the initial context for a lookahead as the context in which the
       parser initially examines that lookahead in order to select a
       syntactic action.  Thus, if the lookahead eventually proves
       syntactically unacceptable (possibly in a later context reached via a
       series of reductions), the initial context can be used to determine
       the exact set of tokens that would be syntactically acceptable in the
       lookahead's place.  Moreover, it is the context after which any
       further semantic actions would be erroneous because they would be
       determined by a syntactically unacceptable token.

       yy_lac_establish_ should be invoked when a reduction is about to be
       performed in an inconsistent state (which, for the purposes of LAC,
       includes consistent states that don't know they're consistent because
       their default reductions have been disabled).

       For parse.lac=full, the implementation of yy_lac_establish_ is as
       follows.  If no initial context is currently established for the
       current lookahead, then check if that lookahead can eventually be
       shifted if syntactic actions continue from the current context.  */
    if (!yy_lac_established_)
      {
#if OCFDEBUG
        YYCDEBUG << "LAC: initial context established for "
                 << symbol_name (yytoken) << '\n';
#endif
        yy_lac_established_ = true;
        return yy_lac_check_ (yytoken);
      }
    return true;
  }

  // Discard any previous initial lookahead context.
  void
  parser::yy_lac_discard_ (const char* evt)
  {
   /* Discard any previous initial lookahead context because of Event,
      which may be a lookahead change or an invalidation of the currently
      established initial context for the current lookahead.

      The most common example of a lookahead change is a shift.  An example
      of both cases is syntax error recovery.  That is, a syntax error
      occurs when the lookahead is syntactically erroneous for the
      currently established initial context, so error recovery manipulates
      the parser stacks to try to find a new initial context in which the
      current lookahead is syntactically acceptable.  If it fails to find
      such a context, it discards the lookahead.  */
    if (yy_lac_established_)
      {
        YYCDEBUG << "LAC: initial context discarded due to "
                 << evt << '\n';
        yy_lac_established_ = false;
      }
  }

  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
         In the first two cases, it might appear that the current syntax
         error should have been detected in the previous state when
         yy_lac_check was invoked.  However, at that time, there might
         have been a different syntax error that discarded a different
         initial context during error recovery, leaving behind the
         current lookahead.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -65;

  const signed char parser::yytable_ninf_ = -53;

  const short
  parser::yypact_[] =
  {
      36,   -65,   -65,   -65,   -65,   -65,   -65,   -12,    -9,     2,
     -65,    18,     5,     8,   -65,   -65,     7,    30,    38,   -65,
      -2,    31,   -65,   -65,    43,   -65,    36,    79,   -65,   169,
     -65,   169,   175,   175,    64,    92,   181,   -65,    67,    71,
     -65,   -65,    57,    57,   -65,   106,   -65,    71,   -65,   -65,
     -65,   -65,   -65,   -65,    69,    55,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,    36,   118,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,    71,   -65,   -65,   -65,    82,    94,
      95,   110,   111,   -65,   -65,    67,   -65,   -65,   -65,    71,
     -65,   -65,   -65,    36,    12,    83,   166,   -65,   167,   -65,
     156,    76,    67,    57,    57,   181,   181,   -65,   -65,   -65,
      36,   -65,   106,   118,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   176,   -65,   -65,   177,   -65
  };

  const signed char
  parser::yydefact_[] =
  {
       0,    28,     2,     3,     4,     5,     6,    72,    70,    49,
      27,    50,     0,    39,    56,    57,    69,     0,    55,    51,
      36,    36,    94,    77,    92,    96,    97,     0,    79,     0,
      78,     0,     0,     0,     0,     0,     0,    35,     0,    36,
      68,    81,     0,     0,    80,     0,    76,    36,    91,    93,
      95,     1,    59,    58,     0,     0,    31,    30,    38,    37,
      32,    26,     8,     9,    10,    11,    12,     0,     0,    24,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,     7,    25,    29,    36,    65,    67,    44,    43,     0,
      45,     0,    48,    60,    66,    62,    52,    54,    53,    36,
      75,    73,    71,     0,     0,    26,     7,    82,     0,    87,
      85,     0,    62,     0,     0,     0,     0,    64,    61,    74,
      33,    89,     0,    84,    88,    90,    63,    40,    42,    41,
      47,    46,     0,    83,    86,     0,    34
  };

  const short
  parser::yypgoto_[] =
  {
     -65,   -32,   -65,   -64,   -31,   150,    -4,   -65,   -65,   -65,
     -13,   -65,   -65,   -47,   -65,   -43,   -65,   -65,   -65,    20,
      32,   -65,   -65,    21,   165,   178,    85,   180,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,    75,   -65,   -65,   -65,   -29,
     -65,   -65,   -26,   -57,   -65
  };

  const unsigned char
  parser::yydefgoto_[] =
  {
       0,    10,    82,    83,    11,    84,    12,    37,   103,   132,
      38,    13,    14,    89,    90,    91,    92,    93,    15,    16,
      17,    18,    19,    20,    54,    39,   117,    40,    41,    21,
      31,    29,    22,    23,    24,   109,   124,   110,   111,   118,
      86,    49,    25,    26,    27
  };

  const short
  parser::yytable_[] =
  {
      50,    57,    57,    81,   107,    88,    85,    28,    46,    94,
     104,    96,    96,    81,    34,     1,     2,     3,     4,     5,
       6,   -36,    35,    34,    36,    30,    95,   121,    58,    59,
       7,    35,   -31,    36,   100,    32,   106,   108,    33,     1,
       2,     3,     4,     5,     6,     8,   120,    34,   -30,    52,
      53,    52,    53,     9,     7,    45,   -52,    36,   133,   107,
       1,     2,     3,     4,     5,     6,   128,   129,    42,     8,
      48,   112,   130,   131,    97,    98,    43,     9,    50,    51,
      60,    67,   127,   127,    88,    88,   119,    34,   101,   102,
      81,   106,   108,   125,    50,    61,     2,     3,     4,     5,
       6,    62,    63,    64,    65,    66,    67,   -28,    68,    61,
       2,     3,     4,     5,     6,    62,    63,    64,    65,    66,
     -40,   105,     2,     3,     4,     5,     6,    62,    63,    64,
      65,    66,   113,   114,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,   115,   116,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     1,     2,     3,     4,     5,     6,     1,     2,
       3,     4,     5,     6,     1,     2,     3,     4,     5,     6,
     -27,   122,   123,   135,   136,    99,    55,   126,   134,    47,
      44,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       9,     0,     0,     0,     0,     0,    56,     0,     0,     0,
       0,     0,    87
  };

  const signed char
  parser::yycheck_[] =
  {
      26,    32,    33,    35,    68,    36,    35,    19,    21,    38,
      67,    42,    43,    45,    16,     3,     4,     5,     6,     7,
       8,    14,    24,    16,    26,    34,    39,    15,    32,    33,
      18,    24,    30,    26,    47,    30,    68,    68,    30,     3,
       4,     5,     6,     7,     8,    33,   103,    16,    30,    29,
      29,    31,    31,    41,    18,    24,    38,    26,   122,   123,
       3,     4,     5,     6,     7,     8,   113,   114,    38,    33,
      27,    84,   115,   116,    42,    43,    38,    41,   104,     0,
      16,    14,   113,   114,   115,   116,    99,    16,    19,    34,
     122,   123,   123,    17,   120,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    24,    16,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      38,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    38,    38,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    36,    36,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,     3,     4,     5,     6,     7,     8,     3,     4,
       5,     6,     7,     8,     3,     4,     5,     6,     7,     8,
      24,    24,    36,    17,    17,    45,    31,   112,   123,    21,
      20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      -1,    -1,    41
  };

  const signed char
  parser::yystos_[] =
  {
       0,     3,     4,     5,     6,     7,     8,    18,    33,    41,
      55,    58,    60,    65,    66,    72,    73,    74,    75,    76,
      77,    83,    86,    87,    88,    96,    97,    98,    19,    85,
      34,    84,    30,    30,    16,    24,    26,    61,    64,    79,
      81,    82,    38,    38,    81,    24,    64,    79,    27,    95,
      96,     0,    73,    77,    78,    78,    41,    58,    60,    60,
      16,     3,     9,    10,    11,    12,    13,    14,    16,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    55,    56,    57,    59,    93,    94,    41,    58,    67,
      68,    69,    70,    71,    93,    64,    58,    74,    74,    59,
      64,    19,    34,    62,    97,     3,    55,    57,    58,    89,
      91,    92,    64,    38,    38,    36,    36,    80,    93,    64,
      97,    15,    24,    36,    90,    17,    80,    58,    67,    67,
      69,    69,    63,    57,    89,    17,    17
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    54,    55,    55,    55,    55,    55,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    57,    57,    58,    58,    59,
      60,    60,    62,    63,    61,    64,    64,    65,    65,    66,
      67,    68,    68,    69,    69,    69,    70,    70,    71,    72,
      73,    73,    74,    75,    75,    76,    77,    77,    78,    78,
      79,    80,    80,    81,    81,    81,    81,    81,    82,    82,
      84,    83,    85,    83,    86,    86,    86,    86,    87,    87,
      88,    88,    89,    89,    90,    90,    91,    91,    92,    93,
      94,    95,    95,    96,    96,    97,    97,    98
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     0,     7,     1,     0,     3,     3,     1,
       1,     3,     3,     1,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     1,     1,     1,
       2,     1,     0,     4,     3,     2,     2,     2,     1,     0,
       0,     4,     0,     4,     4,     3,     2,     1,     2,     2,
       2,     2,     1,     3,     1,     0,     3,     1,     2,     3,
       3,     1,     0,     2,     1,     2,     1,     1
  };




#if OCFDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   105,   105,   106,   113,   114,   115,   118,   119,   120,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   144,   145,   148,   149,   152,
     168,   173,   183,   187,   183,   194,   195,   198,   199,   202,
     209,   214,   215,   218,   221,   224,   229,   230,   233,   238,
     245,   250,   253,   260,   261,   264,   271,   272,   275,   276,
     279,   282,   283,   286,   287,   288,   289,   290,   293,   294,
     297,   297,   306,   306,   317,   318,   319,   320,   323,   328,
     335,   336,   339,   344,   351,   352,   355,   356,   359,   362,
     369,   372,   373,   376,   381,   384,   385,   388
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // OCFDEBUG


#line 7 "/hd2/honestly/components/ocf/bison/ocf.bison"
} } // ocf::__private
#line 2122 "ocf.bison.cpp"

#line 389 "/hd2/honestly/components/ocf/bison/ocf.bison"


void ocf::__private::parser::error(const location_type &loc, const std::string &msg)
{ __drv.error(loc, msg); }
