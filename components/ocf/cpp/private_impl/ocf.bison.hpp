// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file ocf.bison.hpp
 ** Define the ocf::__private::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_OCF_OCF_BISON_HPP_INCLUDED
# define YY_OCF_OCF_BISON_HPP_INCLUDED
// "%code requires" blocks.
#line 12 "/home/arthurdead/Desktop/temp/honestly/components/ocf/bison/ocf.bison"

namespace ocf::__private {
	class lexer;
	class driver;
}
#line 52 "/home/arthurdead/Desktop/temp/honestly/components/ocf/bison/ocf.bison"

#include <ctl/string>
#include <ctl/variant>
#include <ctl/cstddef>

#line 61 "ocf.bison.hpp"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hpp"
#include <typeinfo>
#ifndef OCF_ASSERT
# include <cassert>
# define OCF_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef OCFDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define OCFDEBUG 1
#  else
#   define OCFDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define OCFDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined OCFDEBUG */

#line 8 "/home/arthurdead/Desktop/temp/honestly/components/ocf/bison/ocf.bison"
namespace ocf { namespace __private {
#line 210 "ocf.bison.hpp"




  /// A Bison parser.
  class parser
  {
  public:
#ifdef OCFSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define OCFSTYPE in C++, use %define api.value.type"
# endif
    typedef OCFSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      OCF_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {
      OCF_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      OCF_ASSERT (!yytypeid_);
      OCF_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      OCF_ASSERT (!yytypeid_);
      OCF_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      OCF_ASSERT (!yytypeid_);
      OCF_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      OCF_ASSERT (yytypeid_);
      OCF_ASSERT (*yytypeid_ == typeid (T));
      OCF_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      OCF_ASSERT (yytypeid_);
      OCF_ASSERT (*yytypeid_ == typeid (T));
      OCF_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      OCF_ASSERT (yytypeid_);
      OCF_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // BOOL_LITERAL
      char dummy1[sizeof (bool)];

      // CHAR_LITERAL
      char dummy2[sizeof (char)];

      // U16CHAR_LITERAL
      char dummy3[sizeof (char16_t)];

      // U32CHAR_LITERAL
      char dummy4[sizeof (char32_t)];

      // U8CHAR_LITERAL
      char dummy5[sizeof (char8_t)];

      // string_literal
      // literal
      // identifier.string_literal
      // identifier.literal
      char dummy6[sizeof (ctl::literal_variant)];

      // DOUBLE_LITERAL
      char dummy7[sizeof (double)];

      // FLOAT_LITERAL
      char dummy8[sizeof (float)];

      // INT_LITERAL
      char dummy9[sizeof (int)];

      // LONG_LITERAL
      char dummy10[sizeof (long)];

      // LONG_DOUBLE_LITERAL
      char dummy11[sizeof (long double)];

      // LONG_LONG_LITERAL
      // SSIZE_LITERAL
      char dummy12[sizeof (long long)];

      // STRING_LITERAL
      // IDENTIFIER
      char dummy13[sizeof (std::string)];

      // U16STRING_LITERAL
      char dummy14[sizeof (std::u16string)];

      // U32STRING_LITERAL
      char dummy15[sizeof (std::u32string)];

      // U8STRING_LITERAL
      char dummy16[sizeof (std::u8string)];

      // WSTRING_LITERAL
      char dummy17[sizeof (std::wstring)];

      // UNSIGNED_INT_LITERAL
      char dummy18[sizeof (unsigned int)];

      // UNSIGNED_LONG_LITERAL
      char dummy19[sizeof (unsigned long)];

      // UNSIGNED_LONG_LONG_LITERAL
      // SIZE_LITERAL
      char dummy20[sizeof (unsigned long long)];

      // WCHAR_LITERAL
      char dummy21[sizeof (wchar_t)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;

    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        OCFEMPTY = -2,
    OCFEOF = 0,                    // "end of file"
    OCFerror = 1,                  // error
    OCFUNDEF = 2,                  // "invalid token"
    THIS = 3,                      // THIS
    OPEN_BRACE = 4,                // OPEN_BRACE
    CLOSE_BRACE = 5,               // CLOSE_BRACE
    OPEN_PARENTHESIS = 6,          // OPEN_PARENTHESIS
    CLOSE_PARENTHESIS = 7,         // CLOSE_PARENTHESIS
    OPEN_BRACKET = 8,              // OPEN_BRACKET
    CLOSE_BRACKET = 9,             // CLOSE_BRACKET
    LESSER = 10,                   // LESSER
    GREATER = 11,                  // GREATER
    BITWISE_OR = 12,               // BITWISE_OR
    EQUAL = 13,                    // EQUAL
    COLON = 14,                    // COLON
    DOUBLE_COLON = 15,             // DOUBLE_COLON
    SEMICOLON = 16,                // SEMICOLON
    COMMA = 17,                    // COMMA
    BOOL_LITERAL = 18,             // BOOL_LITERAL
    DOUBLE_LITERAL = 19,           // DOUBLE_LITERAL
    LONG_DOUBLE_LITERAL = 20,      // LONG_DOUBLE_LITERAL
    FLOAT_LITERAL = 21,            // FLOAT_LITERAL
    INT_LITERAL = 22,              // INT_LITERAL
    LONG_LITERAL = 23,             // LONG_LITERAL
    LONG_LONG_LITERAL = 24,        // LONG_LONG_LITERAL
    SSIZE_LITERAL = 25,            // SSIZE_LITERAL
    UNSIGNED_INT_LITERAL = 26,     // UNSIGNED_INT_LITERAL
    UNSIGNED_LONG_LITERAL = 27,    // UNSIGNED_LONG_LITERAL
    UNSIGNED_LONG_LONG_LITERAL = 28, // UNSIGNED_LONG_LONG_LITERAL
    SIZE_LITERAL = 29,             // SIZE_LITERAL
    STRING_LITERAL = 30,           // STRING_LITERAL
    U8STRING_LITERAL = 31,         // U8STRING_LITERAL
    U16STRING_LITERAL = 32,        // U16STRING_LITERAL
    U32STRING_LITERAL = 33,        // U32STRING_LITERAL
    WSTRING_LITERAL = 34,          // WSTRING_LITERAL
    CHAR_LITERAL = 35,             // CHAR_LITERAL
    U8CHAR_LITERAL = 36,           // U8CHAR_LITERAL
    U16CHAR_LITERAL = 37,          // U16CHAR_LITERAL
    U32CHAR_LITERAL = 38,          // U32CHAR_LITERAL
    WCHAR_LITERAL = 39,            // WCHAR_LITERAL
    IDENTIFIER = 40                // IDENTIFIER
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 41, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_THIS = 3,                              // THIS
        S_OPEN_BRACE = 4,                        // OPEN_BRACE
        S_CLOSE_BRACE = 5,                       // CLOSE_BRACE
        S_OPEN_PARENTHESIS = 6,                  // OPEN_PARENTHESIS
        S_CLOSE_PARENTHESIS = 7,                 // CLOSE_PARENTHESIS
        S_OPEN_BRACKET = 8,                      // OPEN_BRACKET
        S_CLOSE_BRACKET = 9,                     // CLOSE_BRACKET
        S_LESSER = 10,                           // LESSER
        S_GREATER = 11,                          // GREATER
        S_BITWISE_OR = 12,                       // BITWISE_OR
        S_EQUAL = 13,                            // EQUAL
        S_COLON = 14,                            // COLON
        S_DOUBLE_COLON = 15,                     // DOUBLE_COLON
        S_SEMICOLON = 16,                        // SEMICOLON
        S_COMMA = 17,                            // COMMA
        S_BOOL_LITERAL = 18,                     // BOOL_LITERAL
        S_DOUBLE_LITERAL = 19,                   // DOUBLE_LITERAL
        S_LONG_DOUBLE_LITERAL = 20,              // LONG_DOUBLE_LITERAL
        S_FLOAT_LITERAL = 21,                    // FLOAT_LITERAL
        S_INT_LITERAL = 22,                      // INT_LITERAL
        S_LONG_LITERAL = 23,                     // LONG_LITERAL
        S_LONG_LONG_LITERAL = 24,                // LONG_LONG_LITERAL
        S_SSIZE_LITERAL = 25,                    // SSIZE_LITERAL
        S_UNSIGNED_INT_LITERAL = 26,             // UNSIGNED_INT_LITERAL
        S_UNSIGNED_LONG_LITERAL = 27,            // UNSIGNED_LONG_LITERAL
        S_UNSIGNED_LONG_LONG_LITERAL = 28,       // UNSIGNED_LONG_LONG_LITERAL
        S_SIZE_LITERAL = 29,                     // SIZE_LITERAL
        S_STRING_LITERAL = 30,                   // STRING_LITERAL
        S_U8STRING_LITERAL = 31,                 // U8STRING_LITERAL
        S_U16STRING_LITERAL = 32,                // U16STRING_LITERAL
        S_U32STRING_LITERAL = 33,                // U32STRING_LITERAL
        S_WSTRING_LITERAL = 34,                  // WSTRING_LITERAL
        S_CHAR_LITERAL = 35,                     // CHAR_LITERAL
        S_U8CHAR_LITERAL = 36,                   // U8CHAR_LITERAL
        S_U16CHAR_LITERAL = 37,                  // U16CHAR_LITERAL
        S_U32CHAR_LITERAL = 38,                  // U32CHAR_LITERAL
        S_WCHAR_LITERAL = 39,                    // WCHAR_LITERAL
        S_IDENTIFIER = 40,                       // IDENTIFIER
        S_YYACCEPT = 41,                         // $accept
        S_string_literal = 42,                   // string_literal
        S_literal = 43,                          // literal
        S_44_identifier_string_literal = 44,     // identifier.string_literal
        S_45_identifier_literal = 45,            // identifier.literal
        S_object_attributes = 46,                // object_attributes
        S_47_1 = 47,                             // $@1
        S_48_object_attributes_opt = 48,         // object_attributes.opt
        S_object_namespace_header = 49,          // object_namespace_header
        S_50_object_namespace_loop = 50,         // object_namespace.loop
        S_object_namespace = 51,                 // object_namespace
        S_object_header_simple = 52,             // object_header_simple
        S_object_group_header = 53,              // object_group_header
        S_54_object_group_loop = 54,             // object_group.loop
        S_object_group = 55,                     // object_group
        S_this = 56,                             // this
        S_object_header = 57,                    // object_header
        S_object_value = 58,                     // object_value
        S_object_body = 59,                      // object_body
        S_60_object_body_opt = 60,               // object_body.opt
        S_array_pair = 61,                       // array_pair
        S_array_level = 62,                      // array_level
        S_63_array_level_loop_impl = 63,         // array_level.loop_impl
        S_64_array_level_loop = 64,              // array_level.loop
        S_object_array = 65,                     // object_array
        S_object_end = 66,                       // object_end
        S_object_end_simple = 67,                // object_end_simple
        S_object = 68,                           // object
        S_69_semicolon_opt = 69,                 // semicolon.opt
        S_object_section_header = 70,            // object_section_header
        S_object_section_begin = 71,             // object_section_begin
        S_72_2 = 72,                             // $@2
        S_73_3 = 73,                             // $@3
        S_object_section_end = 74,               // object_section_end
        S_top_level = 75,                        // top_level
        S_76_top_level_loop = 76,                // top_level.loop
        S_main = 77                              // main
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_BOOL_LITERAL: // BOOL_LITERAL
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_CHAR_LITERAL: // CHAR_LITERAL
        value.move< char > (std::move (that.value));
        break;

      case symbol_kind::S_U16CHAR_LITERAL: // U16CHAR_LITERAL
        value.move< char16_t > (std::move (that.value));
        break;

      case symbol_kind::S_U32CHAR_LITERAL: // U32CHAR_LITERAL
        value.move< char32_t > (std::move (that.value));
        break;

      case symbol_kind::S_U8CHAR_LITERAL: // U8CHAR_LITERAL
        value.move< char8_t > (std::move (that.value));
        break;

      case symbol_kind::S_string_literal: // string_literal
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_44_identifier_string_literal: // identifier.string_literal
      case symbol_kind::S_45_identifier_literal: // identifier.literal
        value.move< ctl::literal_variant > (std::move (that.value));
        break;

      case symbol_kind::S_DOUBLE_LITERAL: // DOUBLE_LITERAL
        value.move< double > (std::move (that.value));
        break;

      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
        value.move< float > (std::move (that.value));
        break;

      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
        value.move< int > (std::move (that.value));
        break;

      case symbol_kind::S_LONG_LITERAL: // LONG_LITERAL
        value.move< long > (std::move (that.value));
        break;

      case symbol_kind::S_LONG_DOUBLE_LITERAL: // LONG_DOUBLE_LITERAL
        value.move< long double > (std::move (that.value));
        break;

      case symbol_kind::S_LONG_LONG_LITERAL: // LONG_LONG_LITERAL
      case symbol_kind::S_SSIZE_LITERAL: // SSIZE_LITERAL
        value.move< long long > (std::move (that.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.move< std::string > (std::move (that.value));
        break;

      case symbol_kind::S_U16STRING_LITERAL: // U16STRING_LITERAL
        value.move< std::u16string > (std::move (that.value));
        break;

      case symbol_kind::S_U32STRING_LITERAL: // U32STRING_LITERAL
        value.move< std::u32string > (std::move (that.value));
        break;

      case symbol_kind::S_U8STRING_LITERAL: // U8STRING_LITERAL
        value.move< std::u8string > (std::move (that.value));
        break;

      case symbol_kind::S_WSTRING_LITERAL: // WSTRING_LITERAL
        value.move< std::wstring > (std::move (that.value));
        break;

      case symbol_kind::S_UNSIGNED_INT_LITERAL: // UNSIGNED_INT_LITERAL
        value.move< unsigned int > (std::move (that.value));
        break;

      case symbol_kind::S_UNSIGNED_LONG_LITERAL: // UNSIGNED_LONG_LITERAL
        value.move< unsigned long > (std::move (that.value));
        break;

      case symbol_kind::S_UNSIGNED_LONG_LONG_LITERAL: // UNSIGNED_LONG_LONG_LITERAL
      case symbol_kind::S_SIZE_LITERAL: // SIZE_LITERAL
        value.move< unsigned long long > (std::move (that.value));
        break;

      case symbol_kind::S_WCHAR_LITERAL: // WCHAR_LITERAL
        value.move< wchar_t > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, char&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const char& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, char16_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const char16_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, char32_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const char32_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, char8_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const char8_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ctl::literal_variant&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ctl::literal_variant& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, float&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const float& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, long&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const long& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, long double&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const long double& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, long long&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const long long& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::u16string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::u16string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::u32string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::u32string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::u8string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::u8string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::wstring&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::wstring& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, unsigned int&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const unsigned int& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, unsigned long&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const unsigned long& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, unsigned long long&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const unsigned long long& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, wchar_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const wchar_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_BOOL_LITERAL: // BOOL_LITERAL
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_CHAR_LITERAL: // CHAR_LITERAL
        value.template destroy< char > ();
        break;

      case symbol_kind::S_U16CHAR_LITERAL: // U16CHAR_LITERAL
        value.template destroy< char16_t > ();
        break;

      case symbol_kind::S_U32CHAR_LITERAL: // U32CHAR_LITERAL
        value.template destroy< char32_t > ();
        break;

      case symbol_kind::S_U8CHAR_LITERAL: // U8CHAR_LITERAL
        value.template destroy< char8_t > ();
        break;

      case symbol_kind::S_string_literal: // string_literal
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_44_identifier_string_literal: // identifier.string_literal
      case symbol_kind::S_45_identifier_literal: // identifier.literal
        value.template destroy< ctl::literal_variant > ();
        break;

      case symbol_kind::S_DOUBLE_LITERAL: // DOUBLE_LITERAL
        value.template destroy< double > ();
        break;

      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
        value.template destroy< float > ();
        break;

      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
        value.template destroy< int > ();
        break;

      case symbol_kind::S_LONG_LITERAL: // LONG_LITERAL
        value.template destroy< long > ();
        break;

      case symbol_kind::S_LONG_DOUBLE_LITERAL: // LONG_DOUBLE_LITERAL
        value.template destroy< long double > ();
        break;

      case symbol_kind::S_LONG_LONG_LITERAL: // LONG_LONG_LITERAL
      case symbol_kind::S_SSIZE_LITERAL: // SSIZE_LITERAL
        value.template destroy< long long > ();
        break;

      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.template destroy< std::string > ();
        break;

      case symbol_kind::S_U16STRING_LITERAL: // U16STRING_LITERAL
        value.template destroy< std::u16string > ();
        break;

      case symbol_kind::S_U32STRING_LITERAL: // U32STRING_LITERAL
        value.template destroy< std::u32string > ();
        break;

      case symbol_kind::S_U8STRING_LITERAL: // U8STRING_LITERAL
        value.template destroy< std::u8string > ();
        break;

      case symbol_kind::S_WSTRING_LITERAL: // WSTRING_LITERAL
        value.template destroy< std::wstring > ();
        break;

      case symbol_kind::S_UNSIGNED_INT_LITERAL: // UNSIGNED_INT_LITERAL
        value.template destroy< unsigned int > ();
        break;

      case symbol_kind::S_UNSIGNED_LONG_LITERAL: // UNSIGNED_LONG_LITERAL
        value.template destroy< unsigned long > ();
        break;

      case symbol_kind::S_UNSIGNED_LONG_LONG_LITERAL: // UNSIGNED_LONG_LONG_LITERAL
      case symbol_kind::S_SIZE_LITERAL: // SIZE_LITERAL
        value.template destroy< unsigned long long > ();
        break;

      case symbol_kind::S_WCHAR_LITERAL: // WCHAR_LITERAL
        value.template destroy< wchar_t > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      const char *name () const YY_NOEXCEPT
      {
        return parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_kind_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_kind_type (tok), l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::OCFEOF
                   || (token::OCFerror <= tok && tok <= token::COMMA));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, bool v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const bool& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::BOOL_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, char v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const char& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::CHAR_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, char16_t v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const char16_t& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::U16CHAR_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, char32_t v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const char32_t& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::U32CHAR_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, char8_t v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const char8_t& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::U8CHAR_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const double& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::DOUBLE_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, float v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const float& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::FLOAT_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::INT_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, long v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const long& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::LONG_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, long double v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const long double& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::LONG_DOUBLE_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, long long v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const long long& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT ((token::LONG_LONG_LITERAL <= tok && tok <= token::SSIZE_LITERAL));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::STRING_LITERAL
                   || tok == token::IDENTIFIER);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::u16string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::u16string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::U16STRING_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::u32string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::u32string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::U32STRING_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::u8string v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::u8string& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::U8STRING_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::wstring v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::wstring& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::WSTRING_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, unsigned int v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const unsigned int& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::UNSIGNED_INT_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, unsigned long v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const unsigned long& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::UNSIGNED_LONG_LITERAL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, unsigned long long v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const unsigned long long& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT ((token::UNSIGNED_LONG_LONG_LITERAL <= tok && tok <= token::SIZE_LITERAL));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, wchar_t v, location_type l)
        : super_type (token_kind_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const wchar_t& v, const location_type& l)
        : super_type (token_kind_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        OCF_ASSERT (tok == token::WCHAR_LITERAL);
#endif
      }
    };

    /// Build a parser object.
    parser (lexer &__lxr_yyarg, driver &__drv_yyarg);
    virtual ~parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    parser (const parser&) = delete;
    /// Non copyable.
    parser& operator= (const parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if OCFDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static const char *symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OCFEOF (location_type l)
      {
        return symbol_type (token::OCFEOF, std::move (l));
      }
#else
      static
      symbol_type
      make_OCFEOF (const location_type& l)
      {
        return symbol_type (token::OCFEOF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OCFerror (location_type l)
      {
        return symbol_type (token::OCFerror, std::move (l));
      }
#else
      static
      symbol_type
      make_OCFerror (const location_type& l)
      {
        return symbol_type (token::OCFerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OCFUNDEF (location_type l)
      {
        return symbol_type (token::OCFUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_OCFUNDEF (const location_type& l)
      {
        return symbol_type (token::OCFUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THIS (location_type l)
      {
        return symbol_type (token::THIS, std::move (l));
      }
#else
      static
      symbol_type
      make_THIS (const location_type& l)
      {
        return symbol_type (token::THIS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPEN_BRACE (location_type l)
      {
        return symbol_type (token::OPEN_BRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_OPEN_BRACE (const location_type& l)
      {
        return symbol_type (token::OPEN_BRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLOSE_BRACE (location_type l)
      {
        return symbol_type (token::CLOSE_BRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_CLOSE_BRACE (const location_type& l)
      {
        return symbol_type (token::CLOSE_BRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPEN_PARENTHESIS (location_type l)
      {
        return symbol_type (token::OPEN_PARENTHESIS, std::move (l));
      }
#else
      static
      symbol_type
      make_OPEN_PARENTHESIS (const location_type& l)
      {
        return symbol_type (token::OPEN_PARENTHESIS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLOSE_PARENTHESIS (location_type l)
      {
        return symbol_type (token::CLOSE_PARENTHESIS, std::move (l));
      }
#else
      static
      symbol_type
      make_CLOSE_PARENTHESIS (const location_type& l)
      {
        return symbol_type (token::CLOSE_PARENTHESIS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OPEN_BRACKET (location_type l)
      {
        return symbol_type (token::OPEN_BRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_OPEN_BRACKET (const location_type& l)
      {
        return symbol_type (token::OPEN_BRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CLOSE_BRACKET (location_type l)
      {
        return symbol_type (token::CLOSE_BRACKET, std::move (l));
      }
#else
      static
      symbol_type
      make_CLOSE_BRACKET (const location_type& l)
      {
        return symbol_type (token::CLOSE_BRACKET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESSER (location_type l)
      {
        return symbol_type (token::LESSER, std::move (l));
      }
#else
      static
      symbol_type
      make_LESSER (const location_type& l)
      {
        return symbol_type (token::LESSER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER (location_type l)
      {
        return symbol_type (token::GREATER, std::move (l));
      }
#else
      static
      symbol_type
      make_GREATER (const location_type& l)
      {
        return symbol_type (token::GREATER, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BITWISE_OR (location_type l)
      {
        return symbol_type (token::BITWISE_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_BITWISE_OR (const location_type& l)
      {
        return symbol_type (token::BITWISE_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL (location_type l)
      {
        return symbol_type (token::EQUAL, std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL (const location_type& l)
      {
        return symbol_type (token::EQUAL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (location_type l)
      {
        return symbol_type (token::COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const location_type& l)
      {
        return symbol_type (token::COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOUBLE_COLON (location_type l)
      {
        return symbol_type (token::DOUBLE_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_DOUBLE_COLON (const location_type& l)
      {
        return symbol_type (token::DOUBLE_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON (location_type l)
      {
        return symbol_type (token::SEMICOLON, std::move (l));
      }
#else
      static
      symbol_type
      make_SEMICOLON (const location_type& l)
      {
        return symbol_type (token::SEMICOLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOL_LITERAL (bool v, location_type l)
      {
        return symbol_type (token::BOOL_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BOOL_LITERAL (const bool& v, const location_type& l)
      {
        return symbol_type (token::BOOL_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOUBLE_LITERAL (double v, location_type l)
      {
        return symbol_type (token::DOUBLE_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DOUBLE_LITERAL (const double& v, const location_type& l)
      {
        return symbol_type (token::DOUBLE_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LONG_DOUBLE_LITERAL (long double v, location_type l)
      {
        return symbol_type (token::LONG_DOUBLE_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LONG_DOUBLE_LITERAL (const long double& v, const location_type& l)
      {
        return symbol_type (token::LONG_DOUBLE_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT_LITERAL (float v, location_type l)
      {
        return symbol_type (token::FLOAT_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT_LITERAL (const float& v, const location_type& l)
      {
        return symbol_type (token::FLOAT_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT_LITERAL (int v, location_type l)
      {
        return symbol_type (token::INT_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INT_LITERAL (const int& v, const location_type& l)
      {
        return symbol_type (token::INT_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LONG_LITERAL (long v, location_type l)
      {
        return symbol_type (token::LONG_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LONG_LITERAL (const long& v, const location_type& l)
      {
        return symbol_type (token::LONG_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LONG_LONG_LITERAL (long long v, location_type l)
      {
        return symbol_type (token::LONG_LONG_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LONG_LONG_LITERAL (const long long& v, const location_type& l)
      {
        return symbol_type (token::LONG_LONG_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SSIZE_LITERAL (long long v, location_type l)
      {
        return symbol_type (token::SSIZE_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SSIZE_LITERAL (const long long& v, const location_type& l)
      {
        return symbol_type (token::SSIZE_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNSIGNED_INT_LITERAL (unsigned int v, location_type l)
      {
        return symbol_type (token::UNSIGNED_INT_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNSIGNED_INT_LITERAL (const unsigned int& v, const location_type& l)
      {
        return symbol_type (token::UNSIGNED_INT_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNSIGNED_LONG_LITERAL (unsigned long v, location_type l)
      {
        return symbol_type (token::UNSIGNED_LONG_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNSIGNED_LONG_LITERAL (const unsigned long& v, const location_type& l)
      {
        return symbol_type (token::UNSIGNED_LONG_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNSIGNED_LONG_LONG_LITERAL (unsigned long long v, location_type l)
      {
        return symbol_type (token::UNSIGNED_LONG_LONG_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNSIGNED_LONG_LONG_LITERAL (const unsigned long long& v, const location_type& l)
      {
        return symbol_type (token::UNSIGNED_LONG_LONG_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SIZE_LITERAL (unsigned long long v, location_type l)
      {
        return symbol_type (token::SIZE_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SIZE_LITERAL (const unsigned long long& v, const location_type& l)
      {
        return symbol_type (token::SIZE_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING_LITERAL (std::string v, location_type l)
      {
        return symbol_type (token::STRING_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING_LITERAL (const std::string& v, const location_type& l)
      {
        return symbol_type (token::STRING_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U8STRING_LITERAL (std::u8string v, location_type l)
      {
        return symbol_type (token::U8STRING_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U8STRING_LITERAL (const std::u8string& v, const location_type& l)
      {
        return symbol_type (token::U8STRING_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U16STRING_LITERAL (std::u16string v, location_type l)
      {
        return symbol_type (token::U16STRING_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U16STRING_LITERAL (const std::u16string& v, const location_type& l)
      {
        return symbol_type (token::U16STRING_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U32STRING_LITERAL (std::u32string v, location_type l)
      {
        return symbol_type (token::U32STRING_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U32STRING_LITERAL (const std::u32string& v, const location_type& l)
      {
        return symbol_type (token::U32STRING_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WSTRING_LITERAL (std::wstring v, location_type l)
      {
        return symbol_type (token::WSTRING_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WSTRING_LITERAL (const std::wstring& v, const location_type& l)
      {
        return symbol_type (token::WSTRING_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHAR_LITERAL (char v, location_type l)
      {
        return symbol_type (token::CHAR_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CHAR_LITERAL (const char& v, const location_type& l)
      {
        return symbol_type (token::CHAR_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U8CHAR_LITERAL (char8_t v, location_type l)
      {
        return symbol_type (token::U8CHAR_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U8CHAR_LITERAL (const char8_t& v, const location_type& l)
      {
        return symbol_type (token::U8CHAR_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U16CHAR_LITERAL (char16_t v, location_type l)
      {
        return symbol_type (token::U16CHAR_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U16CHAR_LITERAL (const char16_t& v, const location_type& l)
      {
        return symbol_type (token::U16CHAR_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U32CHAR_LITERAL (char32_t v, location_type l)
      {
        return symbol_type (token::U32CHAR_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U32CHAR_LITERAL (const char32_t& v, const location_type& l)
      {
        return symbol_type (token::U32CHAR_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WCHAR_LITERAL (wchar_t v, location_type l)
      {
        return symbol_type (token::WCHAR_LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WCHAR_LITERAL (const wchar_t& v, const location_type& l)
      {
        return symbol_type (token::WCHAR_LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::IDENTIFIER, v, l);
      }
#endif


    class context
    {
    public:
      context (const parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    parser (const parser&);
    /// Non copyable.
    parser& operator= (const parser&);
#endif

    /// Check the lookahead yytoken.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_check_ (symbol_kind_type yytoken) const;
    /// Establish the initial context if no initial context currently exists.
    /// \returns  true iff the token will be eventually shifted.
    bool yy_lac_establish_ (symbol_kind_type yytoken);
    /// Discard any previous initial lookahead context because of event.
    /// \param event  the event which caused the lookahead to be discarded.
    ///               Only used for debbuging output.
    void yy_lac_discard_ (const char* event);

    /// Stored state numbers (used for stacks).
    typedef signed char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;



    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const signed char yytable_[];

    static const signed char yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if OCFDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;
    /// The stack for LAC.
    /// Logically, the yy_lac_stack's lifetime is confined to the function
    /// yy_lac_check_. We just store it as a member of this class to hold
    /// on to the memory and to avoid frequent reallocations.
    /// Since yy_lac_check_ is const, this member must be mutable.
    mutable std::vector<state_type> yylac_stack_;
    /// Whether an initial LAC context was established.
    bool yy_lac_established_;


    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 185,     ///< Last index in yytable_.
      yynnts_ = 37,  ///< Number of nonterminal symbols.
      yyfinal_ = 49 ///< Termination state number.
    };


    // User arguments.
    lexer &__lxr;
    driver &__drv;

  };

  inline
  parser::symbol_kind_type
  parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    return static_cast<symbol_kind_type> (t);
  }

  // basic_symbol.
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_BOOL_LITERAL: // BOOL_LITERAL
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CHAR_LITERAL: // CHAR_LITERAL
        value.copy< char > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U16CHAR_LITERAL: // U16CHAR_LITERAL
        value.copy< char16_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U32CHAR_LITERAL: // U32CHAR_LITERAL
        value.copy< char32_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U8CHAR_LITERAL: // U8CHAR_LITERAL
        value.copy< char8_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_string_literal: // string_literal
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_44_identifier_string_literal: // identifier.string_literal
      case symbol_kind::S_45_identifier_literal: // identifier.literal
        value.copy< ctl::literal_variant > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DOUBLE_LITERAL: // DOUBLE_LITERAL
        value.copy< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
        value.copy< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
        value.copy< int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LONG_LITERAL: // LONG_LITERAL
        value.copy< long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LONG_DOUBLE_LITERAL: // LONG_DOUBLE_LITERAL
        value.copy< long double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LONG_LONG_LITERAL: // LONG_LONG_LITERAL
      case symbol_kind::S_SSIZE_LITERAL: // SSIZE_LITERAL
        value.copy< long long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U16STRING_LITERAL: // U16STRING_LITERAL
        value.copy< std::u16string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U32STRING_LITERAL: // U32STRING_LITERAL
        value.copy< std::u32string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U8STRING_LITERAL: // U8STRING_LITERAL
        value.copy< std::u8string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WSTRING_LITERAL: // WSTRING_LITERAL
        value.copy< std::wstring > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_INT_LITERAL: // UNSIGNED_INT_LITERAL
        value.copy< unsigned int > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_LONG_LITERAL: // UNSIGNED_LONG_LITERAL
        value.copy< unsigned long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UNSIGNED_LONG_LONG_LITERAL: // UNSIGNED_LONG_LONG_LITERAL
      case symbol_kind::S_SIZE_LITERAL: // SIZE_LITERAL
        value.copy< unsigned long long > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WCHAR_LITERAL: // WCHAR_LITERAL
        value.copy< wchar_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  parser::symbol_kind_type
  parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_BOOL_LITERAL: // BOOL_LITERAL
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CHAR_LITERAL: // CHAR_LITERAL
        value.move< char > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_U16CHAR_LITERAL: // U16CHAR_LITERAL
        value.move< char16_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_U32CHAR_LITERAL: // U32CHAR_LITERAL
        value.move< char32_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_U8CHAR_LITERAL: // U8CHAR_LITERAL
        value.move< char8_t > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_string_literal: // string_literal
      case symbol_kind::S_literal: // literal
      case symbol_kind::S_44_identifier_string_literal: // identifier.string_literal
      case symbol_kind::S_45_identifier_literal: // identifier.literal
        value.move< ctl::literal_variant > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_DOUBLE_LITERAL: // DOUBLE_LITERAL
        value.move< double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FLOAT_LITERAL: // FLOAT_LITERAL
        value.move< float > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INT_LITERAL: // INT_LITERAL
        value.move< int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_LONG_LITERAL: // LONG_LITERAL
        value.move< long > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_LONG_DOUBLE_LITERAL: // LONG_DOUBLE_LITERAL
        value.move< long double > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_LONG_LONG_LITERAL: // LONG_LONG_LITERAL
      case symbol_kind::S_SSIZE_LITERAL: // SSIZE_LITERAL
        value.move< long long > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_STRING_LITERAL: // STRING_LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.move< std::string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_U16STRING_LITERAL: // U16STRING_LITERAL
        value.move< std::u16string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_U32STRING_LITERAL: // U32STRING_LITERAL
        value.move< std::u32string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_U8STRING_LITERAL: // U8STRING_LITERAL
        value.move< std::u8string > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_WSTRING_LITERAL: // WSTRING_LITERAL
        value.move< std::wstring > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_UNSIGNED_INT_LITERAL: // UNSIGNED_INT_LITERAL
        value.move< unsigned int > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_UNSIGNED_LONG_LITERAL: // UNSIGNED_LONG_LITERAL
        value.move< unsigned long > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_UNSIGNED_LONG_LONG_LITERAL: // UNSIGNED_LONG_LONG_LITERAL
      case symbol_kind::S_SIZE_LITERAL: // SIZE_LITERAL
        value.move< unsigned long long > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_WCHAR_LITERAL: // WCHAR_LITERAL
        value.move< wchar_t > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  inline
  parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  inline
  void
  parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  parser::symbol_kind_type
  parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  inline
  parser::symbol_kind_type
  parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


#line 8 "/home/arthurdead/Desktop/temp/honestly/components/ocf/bison/ocf.bison"
} } // ocf::__private
#line 2895 "ocf.bison.hpp"




#endif // !YY_OCF_OCF_BISON_HPP_INCLUDED
