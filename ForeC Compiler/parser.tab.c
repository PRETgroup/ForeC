// A Bison parser, made by GNU Bison 3.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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


// First part of user declarations.

#line 37 "parser.tab.c" // lalr1.cc:407

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.tab.h"

// User implementation prologue.

#line 51 "parser.tab.c" // lalr1.cc:415
// Unqualified %code blocks.
#line 99 "parser.y" // lalr1.cc:416

	// Prototype for the yylex function
	static int yylex(forec::loader::Parser::semantic_type * yylval, forec::loader::Parser::location_type * yylloc, forec::loader::Scanner &scanner);

#line 58 "parser.tab.c" // lalr1.cc:416


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
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 12 "parser.y" // lalr1.cc:491
namespace forec { namespace loader {
#line 153 "parser.tab.c" // lalr1.cc:491

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (forec::loader::Scanner &scanner_yyarg, forec::ast::Node &rootNode_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      rootNode (rootNode_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
    , location ()
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value (other.value)
    , location (other.location)
  {
  }

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (const stack_symbol_type& that)
    : super_type (that.state, that.location)
  {
    value = that.value;
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.value, that.location)
  {
    // that is emptied.
    that.type = empty_symbol;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  void
  Parser::yypop_ (unsigned n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, scanner));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
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
  case 2:
#line 196 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PreProcessorDirective(*(yystack_[0].value.str), "include"); }
#line 615 "parser.tab.c" // lalr1.cc:870
    break;

  case 3:
#line 197 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PreProcessorDirective(*(yystack_[0].value.str), "define"); }
#line 621 "parser.tab.c" // lalr1.cc:870
    break;

  case 4:
#line 201 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier"); }
#line 627 "parser.tab.c" // lalr1.cc:870
    break;

  case 5:
#line 202 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PrimaryExpression(*(yystack_[0].value.str), "terminal"); }
#line 633 "parser.tab.c" // lalr1.cc:870
    break;

  case 6:
#line 203 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PrimaryExpression(*(yystack_[0].value.str), "terminal"); }
#line 639 "parser.tab.c" // lalr1.cc:870
    break;

  case 7:
#line 204 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PrimaryExpression(*(yystack_[0].value.str), "terminal"); }
#line 645 "parser.tab.c" // lalr1.cc:870
    break;

  case 8:
#line 205 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PrimaryExpression(*(yystack_[0].value.str), "terminal"); }
#line 651 "parser.tab.c" // lalr1.cc:870
    break;

  case 9:
#line 206 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PrimaryExpression(*(yystack_[1].value.nodeList), "expression"); }
#line 657 "parser.tab.c" // lalr1.cc:870
    break;

  case 10:
#line 210 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 663 "parser.tab.c" // lalr1.cc:870
    break;

  case 11:
#line 211 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PostfixExpression(*(yystack_[3].value.node), *(yystack_[1].value.nodeList), "index"); }
#line 669 "parser.tab.c" // lalr1.cc:870
    break;

  case 12:
#line 212 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PostfixExpression(*(yystack_[2].value.node), "function0"); }
#line 675 "parser.tab.c" // lalr1.cc:870
    break;

  case 13:
#line 213 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PostfixExpression(*(yystack_[3].value.node), *(yystack_[1].value.nodeList), "function1"); }
#line 681 "parser.tab.c" // lalr1.cc:870
    break;

  case 14:
#line 214 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PostfixExpression(*(yystack_[2].value.node), *(new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier")), "member"); }
#line 687 "parser.tab.c" // lalr1.cc:870
    break;

  case 15:
#line 215 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PostfixExpression(*(yystack_[2].value.node), *(new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier")), "pointer"); }
#line 693 "parser.tab.c" // lalr1.cc:870
    break;

  case 16:
#line 216 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PostfixExpression(*(yystack_[1].value.node), "increment"); }
#line 699 "parser.tab.c" // lalr1.cc:870
    break;

  case 17:
#line 217 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PostfixExpression(*(yystack_[1].value.node), "decrement"); }
#line 705 "parser.tab.c" // lalr1.cc:870
    break;

  case 18:
#line 218 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PostfixExpression(*(yystack_[4].value.node), *(yystack_[1].value.node), "cast0"); }
#line 711 "parser.tab.c" // lalr1.cc:870
    break;

  case 19:
#line 219 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PostfixExpression(*(yystack_[5].value.node), *(yystack_[2].value.node), "cast1"); }
#line 717 "parser.tab.c" // lalr1.cc:870
    break;

  case 20:
#line 223 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::ArgumentExpressionList(*(yystack_[0].value.node)); }
#line 723 "parser.tab.c" // lalr1.cc:870
    break;

  case 21:
#line 224 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[2].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 729 "parser.tab.c" // lalr1.cc:870
    break;

  case 22:
#line 228 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 735 "parser.tab.c" // lalr1.cc:870
    break;

  case 23:
#line 229 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::UnaryExpression(*(yystack_[0].value.node), "increment"); }
#line 741 "parser.tab.c" // lalr1.cc:870
    break;

  case 24:
#line 230 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::UnaryExpression(*(yystack_[0].value.node), "decrement"); }
#line 747 "parser.tab.c" // lalr1.cc:870
    break;

  case 25:
#line 231 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::UnaryExpression(*(yystack_[1].value.str), *(yystack_[0].value.node), "cast"); }
#line 753 "parser.tab.c" // lalr1.cc:870
    break;

  case 26:
#line 232 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::UnaryExpression(*(yystack_[0].value.node), "sizeof0"); }
#line 759 "parser.tab.c" // lalr1.cc:870
    break;

  case 27:
#line 233 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::UnaryExpression(*(yystack_[1].value.node), "sizeof1"); }
#line 765 "parser.tab.c" // lalr1.cc:870
    break;

  case 28:
#line 237 "parser.y" // lalr1.cc:870
    { (yylhs.value.str) = new std::string("&"); }
#line 771 "parser.tab.c" // lalr1.cc:870
    break;

  case 29:
#line 238 "parser.y" // lalr1.cc:870
    { (yylhs.value.str) = new std::string("*"); }
#line 777 "parser.tab.c" // lalr1.cc:870
    break;

  case 30:
#line 239 "parser.y" // lalr1.cc:870
    { (yylhs.value.str) = new std::string("+"); }
#line 783 "parser.tab.c" // lalr1.cc:870
    break;

  case 31:
#line 240 "parser.y" // lalr1.cc:870
    { (yylhs.value.str) = new std::string("-"); }
#line 789 "parser.tab.c" // lalr1.cc:870
    break;

  case 32:
#line 241 "parser.y" // lalr1.cc:870
    { (yylhs.value.str) = new std::string("~"); }
#line 795 "parser.tab.c" // lalr1.cc:870
    break;

  case 33:
#line 242 "parser.y" // lalr1.cc:870
    { (yylhs.value.str) = new std::string("!"); }
#line 801 "parser.tab.c" // lalr1.cc:870
    break;

  case 34:
#line 246 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::CastExpression(*(yystack_[0].value.node)); }
#line 807 "parser.tab.c" // lalr1.cc:870
    break;

  case 35:
#line 247 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); (yylhs.value.node)->prepend(*(yystack_[2].value.node)); }
#line 813 "parser.tab.c" // lalr1.cc:870
    break;

  case 36:
#line 251 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "cast"); }
#line 819 "parser.tab.c" // lalr1.cc:870
    break;

  case 37:
#line 252 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), "*"); }
#line 825 "parser.tab.c" // lalr1.cc:870
    break;

  case 38:
#line 253 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), "/"); }
#line 831 "parser.tab.c" // lalr1.cc:870
    break;

  case 39:
#line 254 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), "%"); }
#line 837 "parser.tab.c" // lalr1.cc:870
    break;

  case 40:
#line 258 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "multiplicative"); }
#line 843 "parser.tab.c" // lalr1.cc:870
    break;

  case 41:
#line 259 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " + "); }
#line 849 "parser.tab.c" // lalr1.cc:870
    break;

  case 42:
#line 260 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " - "); }
#line 855 "parser.tab.c" // lalr1.cc:870
    break;

  case 43:
#line 264 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "additive"); }
#line 861 "parser.tab.c" // lalr1.cc:870
    break;

  case 44:
#line 265 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " << "); }
#line 867 "parser.tab.c" // lalr1.cc:870
    break;

  case 45:
#line 266 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " >> "); }
#line 873 "parser.tab.c" // lalr1.cc:870
    break;

  case 46:
#line 270 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "shift"); }
#line 879 "parser.tab.c" // lalr1.cc:870
    break;

  case 47:
#line 271 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " < "); }
#line 885 "parser.tab.c" // lalr1.cc:870
    break;

  case 48:
#line 272 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " > "); }
#line 891 "parser.tab.c" // lalr1.cc:870
    break;

  case 49:
#line 273 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " <= "); }
#line 897 "parser.tab.c" // lalr1.cc:870
    break;

  case 50:
#line 274 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " >= "); }
#line 903 "parser.tab.c" // lalr1.cc:870
    break;

  case 51:
#line 278 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "relational"); }
#line 909 "parser.tab.c" // lalr1.cc:870
    break;

  case 52:
#line 279 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " == "); }
#line 915 "parser.tab.c" // lalr1.cc:870
    break;

  case 53:
#line 280 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " != "); }
#line 921 "parser.tab.c" // lalr1.cc:870
    break;

  case 54:
#line 284 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "equality"); }
#line 927 "parser.tab.c" // lalr1.cc:870
    break;

  case 55:
#line 285 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " & "); }
#line 933 "parser.tab.c" // lalr1.cc:870
    break;

  case 56:
#line 289 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "and"); }
#line 939 "parser.tab.c" // lalr1.cc:870
    break;

  case 57:
#line 290 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " ^ "); }
#line 945 "parser.tab.c" // lalr1.cc:870
    break;

  case 58:
#line 294 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "exclusiveOr"); }
#line 951 "parser.tab.c" // lalr1.cc:870
    break;

  case 59:
#line 295 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " | "); }
#line 957 "parser.tab.c" // lalr1.cc:870
    break;

  case 60:
#line 299 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "inclusiveOr"); }
#line 963 "parser.tab.c" // lalr1.cc:870
    break;

  case 61:
#line 300 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " && "); }
#line 969 "parser.tab.c" // lalr1.cc:870
    break;

  case 62:
#line 304 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "logicalAnd"); }
#line 975 "parser.tab.c" // lalr1.cc:870
    break;

  case 63:
#line 305 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[2].value.node), *(yystack_[0].value.node), " || "); }
#line 981 "parser.tab.c" // lalr1.cc:870
    break;

  case 64:
#line 309 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TernaryExpression(*(yystack_[0].value.node), "logicalOr"); }
#line 987 "parser.tab.c" // lalr1.cc:870
    break;

  case 65:
#line 310 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TernaryExpression(*(yystack_[4].value.node), *(yystack_[2].value.nodeList), *(yystack_[0].value.node)); }
#line 993 "parser.tab.c" // lalr1.cc:870
    break;

  case 66:
#line 314 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentExpression(*(yystack_[0].value.node), "conditional"); }
#line 999 "parser.tab.c" // lalr1.cc:870
    break;

  case 67:
#line 315 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentExpression(*(yystack_[2].value.node), *(yystack_[1].value.node), *(yystack_[0].value.node)); }
#line 1005 "parser.tab.c" // lalr1.cc:870
    break;

  case 68:
#line 319 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator("="); }
#line 1011 "parser.tab.c" // lalr1.cc:870
    break;

  case 69:
#line 320 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator("*="); }
#line 1017 "parser.tab.c" // lalr1.cc:870
    break;

  case 70:
#line 321 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator("/="); }
#line 1023 "parser.tab.c" // lalr1.cc:870
    break;

  case 71:
#line 322 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator("%="); }
#line 1029 "parser.tab.c" // lalr1.cc:870
    break;

  case 72:
#line 323 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator("+="); }
#line 1035 "parser.tab.c" // lalr1.cc:870
    break;

  case 73:
#line 324 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator("-="); }
#line 1041 "parser.tab.c" // lalr1.cc:870
    break;

  case 74:
#line 325 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator("<<="); }
#line 1047 "parser.tab.c" // lalr1.cc:870
    break;

  case 75:
#line 326 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator(">>="); }
#line 1053 "parser.tab.c" // lalr1.cc:870
    break;

  case 76:
#line 327 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator("&="); }
#line 1059 "parser.tab.c" // lalr1.cc:870
    break;

  case 77:
#line 328 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator("^="); }
#line 1065 "parser.tab.c" // lalr1.cc:870
    break;

  case 78:
#line 329 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AssignmentOperator("|="); }
#line 1071 "parser.tab.c" // lalr1.cc:870
    break;

  case 79:
#line 333 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::Expression(*(yystack_[0].value.node)); }
#line 1077 "parser.tab.c" // lalr1.cc:870
    break;

  case 80:
#line 334 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[2].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 1083 "parser.tab.c" // lalr1.cc:870
    break;

  case 81:
#line 338 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1089 "parser.tab.c" // lalr1.cc:870
    break;

  case 82:
#line 346 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Declaration(*(yystack_[1].value.nodeList), "declaration"); }
#line 1095 "parser.tab.c" // lalr1.cc:870
    break;

  case 83:
#line 347 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Declaration(*(yystack_[2].value.nodeList), *(yystack_[1].value.nodeList), "initDeclaration"); }
#line 1101 "parser.tab.c" // lalr1.cc:870
    break;

  case 84:
#line 348 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Declaration(*(yystack_[1].value.nodeList), "threadDeclaration"); }
#line 1107 "parser.tab.c" // lalr1.cc:870
    break;

  case 85:
#line 352 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::DeclarationSpecifiers(*(yystack_[0].value.node), "storageClassSpecifier"); }
#line 1113 "parser.tab.c" // lalr1.cc:870
    break;

  case 86:
#line 353 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[0].value.nodeList); (yystack_[0].value.nodeList)->prepend(*(yystack_[1].value.node)); }
#line 1119 "parser.tab.c" // lalr1.cc:870
    break;

  case 87:
#line 354 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::DeclarationSpecifiers(*(yystack_[0].value.node), "typeSpecifier"); }
#line 1125 "parser.tab.c" // lalr1.cc:870
    break;

  case 88:
#line 355 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[0].value.nodeList); (yystack_[0].value.nodeList)->prepend(*(yystack_[1].value.node)); }
#line 1131 "parser.tab.c" // lalr1.cc:870
    break;

  case 89:
#line 356 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::DeclarationSpecifiers(*(yystack_[0].value.node), "typeQualifier"); }
#line 1137 "parser.tab.c" // lalr1.cc:870
    break;

  case 90:
#line 357 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[0].value.nodeList); (yystack_[0].value.nodeList)->prepend(*(yystack_[1].value.node)); }
#line 1143 "parser.tab.c" // lalr1.cc:870
    break;

  case 91:
#line 358 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::DeclarationSpecifiers(*(yystack_[0].value.node), "functionSpecifier"); }
#line 1149 "parser.tab.c" // lalr1.cc:870
    break;

  case 92:
#line 359 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[0].value.nodeList); (yystack_[0].value.nodeList)->prepend(*(yystack_[1].value.node)); }
#line 1155 "parser.tab.c" // lalr1.cc:870
    break;

  case 93:
#line 363 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::InitDeclaratorList(*(yystack_[0].value.node)); }
#line 1161 "parser.tab.c" // lalr1.cc:870
    break;

  case 94:
#line 364 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[2].value.nodeList); (yystack_[2].value.nodeList)->append(*(yystack_[0].value.node)); }
#line 1167 "parser.tab.c" // lalr1.cc:870
    break;

  case 95:
#line 368 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[0].value.node), "declarator"); }
#line 1173 "parser.tab.c" // lalr1.cc:870
    break;

  case 96:
#line 369 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(yystack_[1].value.node), *(yystack_[0].value.node), "declarator"); }
#line 1179 "parser.tab.c" // lalr1.cc:870
    break;

  case 97:
#line 370 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(new forec::ast::BinaryExpression(*(yystack_[2].value.node), "declarator")), *(yystack_[0].value.node), " = "); }
#line 1185 "parser.tab.c" // lalr1.cc:870
    break;

  case 98:
#line 371 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::BinaryExpression(*(new forec::ast::BinaryExpression(*(yystack_[3].value.node), "declarator")), *(yystack_[1].value.node), *(yystack_[0].value.node), " = "); }
#line 1191 "parser.tab.c" // lalr1.cc:870
    break;

  case 99:
#line 375 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StorageClassSpecifier("typedef"); }
#line 1197 "parser.tab.c" // lalr1.cc:870
    break;

  case 100:
#line 376 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StorageClassSpecifier("extern"); }
#line 1203 "parser.tab.c" // lalr1.cc:870
    break;

  case 101:
#line 377 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StorageClassSpecifier("static"); }
#line 1209 "parser.tab.c" // lalr1.cc:870
    break;

  case 102:
#line 378 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StorageClassSpecifier("auto"); }
#line 1215 "parser.tab.c" // lalr1.cc:870
    break;

  case 103:
#line 379 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StorageClassSpecifier("register"); }
#line 1221 "parser.tab.c" // lalr1.cc:870
    break;

  case 104:
#line 383 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("void"); }
#line 1227 "parser.tab.c" // lalr1.cc:870
    break;

  case 105:
#line 384 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("char"); }
#line 1233 "parser.tab.c" // lalr1.cc:870
    break;

  case 106:
#line 385 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("short"); }
#line 1239 "parser.tab.c" // lalr1.cc:870
    break;

  case 107:
#line 386 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("int"); }
#line 1245 "parser.tab.c" // lalr1.cc:870
    break;

  case 108:
#line 387 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("long"); }
#line 1251 "parser.tab.c" // lalr1.cc:870
    break;

  case 109:
#line 388 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("float"); }
#line 1257 "parser.tab.c" // lalr1.cc:870
    break;

  case 110:
#line 389 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("double"); }
#line 1263 "parser.tab.c" // lalr1.cc:870
    break;

  case 111:
#line 390 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("signed"); }
#line 1269 "parser.tab.c" // lalr1.cc:870
    break;

  case 112:
#line 391 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("unsigned"); }
#line 1275 "parser.tab.c" // lalr1.cc:870
    break;

  case 113:
#line 392 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("_Bool"); }
#line 1281 "parser.tab.c" // lalr1.cc:870
    break;

  case 114:
#line 393 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("_Complex"); }
#line 1287 "parser.tab.c" // lalr1.cc:870
    break;

  case 115:
#line 394 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier("_Imaginary"); }
#line 1293 "parser.tab.c" // lalr1.cc:870
    break;

  case 116:
#line 395 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1299 "parser.tab.c" // lalr1.cc:870
    break;

  case 117:
#line 396 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1305 "parser.tab.c" // lalr1.cc:870
    break;

  case 118:
#line 397 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeSpecifier(*(new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier")), "typedef"); }
#line 1311 "parser.tab.c" // lalr1.cc:870
    break;

  case 119:
#line 401 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StructUnionSpecifier(*(yystack_[4].value.str), *(new forec::ast::PrimaryExpression(*(yystack_[3].value.str), yystack_[3].location.begin.line, "identifier")), *(yystack_[1].value.nodeList), "definition"); }
#line 1317 "parser.tab.c" // lalr1.cc:870
    break;

  case 120:
#line 402 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StructUnionSpecifier(*(yystack_[3].value.str), *(yystack_[1].value.nodeList), "anonymous"); }
#line 1323 "parser.tab.c" // lalr1.cc:870
    break;

  case 121:
#line 403 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StructUnionSpecifier(*(yystack_[1].value.str), *(new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier")), "declaration"); }
#line 1329 "parser.tab.c" // lalr1.cc:870
    break;

  case 122:
#line 407 "parser.y" // lalr1.cc:870
    { (yylhs.value.str) = new std::string("struct"); }
#line 1335 "parser.tab.c" // lalr1.cc:870
    break;

  case 123:
#line 408 "parser.y" // lalr1.cc:870
    { (yylhs.value.str) = new std::string("union"); }
#line 1341 "parser.tab.c" // lalr1.cc:870
    break;

  case 124:
#line 412 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::StructDeclarationList(*(yystack_[0].value.node)); }
#line 1347 "parser.tab.c" // lalr1.cc:870
    break;

  case 125:
#line 413 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[1].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 1353 "parser.tab.c" // lalr1.cc:870
    break;

  case 126:
#line 417 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StructDeclaration(*(yystack_[2].value.nodeList), *(yystack_[1].value.nodeList)); }
#line 1359 "parser.tab.c" // lalr1.cc:870
    break;

  case 127:
#line 421 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[0].value.nodeList); (yystack_[0].value.nodeList)->prepend(*(yystack_[1].value.node)); }
#line 1365 "parser.tab.c" // lalr1.cc:870
    break;

  case 128:
#line 422 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::SpecifierQualifierList(*(yystack_[0].value.node), "typeSpecifier"); }
#line 1371 "parser.tab.c" // lalr1.cc:870
    break;

  case 129:
#line 423 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[0].value.nodeList); (yystack_[0].value.nodeList)->prepend(*(yystack_[1].value.node)); }
#line 1377 "parser.tab.c" // lalr1.cc:870
    break;

  case 130:
#line 424 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::SpecifierQualifierList(*(yystack_[0].value.node), "typeQualifier"); }
#line 1383 "parser.tab.c" // lalr1.cc:870
    break;

  case 131:
#line 428 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::StructDeclaratorList(*(yystack_[0].value.node)); }
#line 1389 "parser.tab.c" // lalr1.cc:870
    break;

  case 132:
#line 429 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[2].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 1395 "parser.tab.c" // lalr1.cc:870
    break;

  case 133:
#line 433 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1401 "parser.tab.c" // lalr1.cc:870
    break;

  case 134:
#line 434 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StructDeclarator(*(yystack_[0].value.node), "constantExpression"); }
#line 1407 "parser.tab.c" // lalr1.cc:870
    break;

  case 135:
#line 435 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::StructDeclarator(*(yystack_[2].value.node), *(yystack_[0].value.node), "full"); }
#line 1413 "parser.tab.c" // lalr1.cc:870
    break;

  case 136:
#line 439 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::EnumSpecifier(*(yystack_[1].value.nodeList), "anonymous0"); }
#line 1419 "parser.tab.c" // lalr1.cc:870
    break;

  case 137:
#line 440 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::EnumSpecifier(*(new forec::ast::PrimaryExpression(*(yystack_[3].value.str), yystack_[3].location.begin.line, "identifier")), *(yystack_[1].value.nodeList), "definition0"); }
#line 1425 "parser.tab.c" // lalr1.cc:870
    break;

  case 138:
#line 441 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::EnumSpecifier(*(yystack_[2].value.nodeList), "anonymous1"); }
#line 1431 "parser.tab.c" // lalr1.cc:870
    break;

  case 139:
#line 442 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::EnumSpecifier(*(new forec::ast::PrimaryExpression(*(yystack_[4].value.str), yystack_[4].location.begin.line, "identifier")), *(yystack_[2].value.nodeList), "definition1"); }
#line 1437 "parser.tab.c" // lalr1.cc:870
    break;

  case 140:
#line 443 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::EnumSpecifier(*(new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier")), "declaration"); }
#line 1443 "parser.tab.c" // lalr1.cc:870
    break;

  case 141:
#line 447 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::EnumeratorList(*(yystack_[0].value.node)); }
#line 1449 "parser.tab.c" // lalr1.cc:870
    break;

  case 142:
#line 448 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[2].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 1455 "parser.tab.c" // lalr1.cc:870
    break;

  case 143:
#line 452 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier"); }
#line 1461 "parser.tab.c" // lalr1.cc:870
    break;

  case 144:
#line 453 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Enumerator(*(new forec::ast::PrimaryExpression(*(yystack_[2].value.str), yystack_[2].location.begin.line, "identifier")), *(yystack_[0].value.node)); }
#line 1467 "parser.tab.c" // lalr1.cc:870
    break;

  case 145:
#line 457 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeQualifier("const"); }
#line 1473 "parser.tab.c" // lalr1.cc:870
    break;

  case 146:
#line 458 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeQualifier("restrict"); }
#line 1479 "parser.tab.c" // lalr1.cc:870
    break;

  case 147:
#line 459 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeQualifier("volatile"); }
#line 1485 "parser.tab.c" // lalr1.cc:870
    break;

  case 148:
#line 460 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeQualifier("input"); }
#line 1491 "parser.tab.c" // lalr1.cc:870
    break;

  case 149:
#line 461 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeQualifier("output"); }
#line 1497 "parser.tab.c" // lalr1.cc:870
    break;

  case 150:
#line 462 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeQualifier("shared"); }
#line 1503 "parser.tab.c" // lalr1.cc:870
    break;

  case 151:
#line 466 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::CombineSpecifier(*(yystack_[0].value.str)); }
#line 1509 "parser.tab.c" // lalr1.cc:870
    break;

  case 152:
#line 470 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::FunctionSpecifier("inline"); }
#line 1515 "parser.tab.c" // lalr1.cc:870
    break;

  case 153:
#line 477 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Declarator(*(yystack_[1].value.node), *(yystack_[0].value.node)); }
#line 1521 "parser.tab.c" // lalr1.cc:870
    break;

  case 154:
#line 478 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1527 "parser.tab.c" // lalr1.cc:870
    break;

  case 155:
#line 483 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier")), "identifier"); }
#line 1533 "parser.tab.c" // lalr1.cc:870
    break;

  case 156:
#line 484 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[1].value.node), "cast"); }
#line 1539 "parser.tab.c" // lalr1.cc:870
    break;

  case 157:
#line 485 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[4].value.node), *(yystack_[2].value.nodeList), *(yystack_[1].value.node), "array0"); }
#line 1545 "parser.tab.c" // lalr1.cc:870
    break;

  case 158:
#line 486 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[3].value.node), *(yystack_[1].value.nodeList), "array1"); }
#line 1551 "parser.tab.c" // lalr1.cc:870
    break;

  case 159:
#line 487 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[3].value.node), *(yystack_[1].value.node), "array2"); }
#line 1557 "parser.tab.c" // lalr1.cc:870
    break;

  case 160:
#line 488 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[5].value.node), *(yystack_[2].value.nodeList), *(yystack_[1].value.node), "array3"); }
#line 1563 "parser.tab.c" // lalr1.cc:870
    break;

  case 161:
#line 489 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[5].value.node), *(yystack_[3].value.nodeList), *(yystack_[1].value.node), "array4"); }
#line 1569 "parser.tab.c" // lalr1.cc:870
    break;

  case 162:
#line 490 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[4].value.node), *(yystack_[2].value.nodeList), "array5"); }
#line 1575 "parser.tab.c" // lalr1.cc:870
    break;

  case 163:
#line 491 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[3].value.node), "array6"); }
#line 1581 "parser.tab.c" // lalr1.cc:870
    break;

  case 164:
#line 492 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[2].value.node), "array7"); }
#line 1587 "parser.tab.c" // lalr1.cc:870
    break;

  case 165:
#line 493 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[3].value.node), *(yystack_[1].value.node), "function0"); }
#line 1593 "parser.tab.c" // lalr1.cc:870
    break;

  case 166:
#line 494 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[3].value.node), *(yystack_[1].value.nodeList), "function1"); }
#line 1599 "parser.tab.c" // lalr1.cc:870
    break;

  case 167:
#line 495 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectDeclarator(*(yystack_[2].value.node), "function2"); }
#line 1605 "parser.tab.c" // lalr1.cc:870
    break;

  case 168:
#line 499 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Pointer("asterisk"); }
#line 1611 "parser.tab.c" // lalr1.cc:870
    break;

  case 169:
#line 500 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Pointer(*(yystack_[0].value.nodeList), "typeQualifier"); }
#line 1617 "parser.tab.c" // lalr1.cc:870
    break;

  case 170:
#line 501 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Pointer(*(yystack_[0].value.node), "pointer"); }
#line 1623 "parser.tab.c" // lalr1.cc:870
    break;

  case 171:
#line 502 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Pointer(*(yystack_[1].value.nodeList), *(yystack_[0].value.node), "typeQualifierPointer"); }
#line 1629 "parser.tab.c" // lalr1.cc:870
    break;

  case 172:
#line 506 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::TypeQualifierList(*(yystack_[0].value.node)); }
#line 1635 "parser.tab.c" // lalr1.cc:870
    break;

  case 173:
#line 507 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[1].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 1641 "parser.tab.c" // lalr1.cc:870
    break;

  case 174:
#line 512 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.nodeList); }
#line 1647 "parser.tab.c" // lalr1.cc:870
    break;

  case 175:
#line 513 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::ParameterTypeList(*(yystack_[2].value.nodeList), "unbounded"); }
#line 1653 "parser.tab.c" // lalr1.cc:870
    break;

  case 176:
#line 517 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::ParameterList(*(yystack_[0].value.node)); }
#line 1659 "parser.tab.c" // lalr1.cc:870
    break;

  case 177:
#line 518 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[2].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 1665 "parser.tab.c" // lalr1.cc:870
    break;

  case 178:
#line 522 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::ParameterDeclaration(*(yystack_[1].value.nodeList), *(yystack_[0].value.node)); }
#line 1671 "parser.tab.c" // lalr1.cc:870
    break;

  case 179:
#line 523 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::ParameterDeclaration(*(yystack_[1].value.nodeList), *(yystack_[0].value.node)); }
#line 1677 "parser.tab.c" // lalr1.cc:870
    break;

  case 180:
#line 524 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.nodeList); }
#line 1683 "parser.tab.c" // lalr1.cc:870
    break;

  case 181:
#line 528 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::IdentifierList(*(new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier"))); }
#line 1689 "parser.tab.c" // lalr1.cc:870
    break;

  case 182:
#line 529 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[2].value.nodeList); (yylhs.value.nodeList)->append(*(new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier"))); }
#line 1695 "parser.tab.c" // lalr1.cc:870
    break;

  case 183:
#line 533 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeName(*(yystack_[0].value.nodeList)); }
#line 1701 "parser.tab.c" // lalr1.cc:870
    break;

  case 184:
#line 534 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::TypeName(*(yystack_[1].value.nodeList), *(yystack_[0].value.node)); }
#line 1707 "parser.tab.c" // lalr1.cc:870
    break;

  case 185:
#line 538 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1713 "parser.tab.c" // lalr1.cc:870
    break;

  case 186:
#line 539 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1719 "parser.tab.c" // lalr1.cc:870
    break;

  case 187:
#line 540 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AbstractDeclarator(*(yystack_[1].value.node), *(yystack_[0].value.node)); }
#line 1725 "parser.tab.c" // lalr1.cc:870
    break;

  case 188:
#line 544 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator(*(yystack_[1].value.node), "cast"); }
#line 1731 "parser.tab.c" // lalr1.cc:870
    break;

  case 189:
#line 545 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator("index0"); }
#line 1737 "parser.tab.c" // lalr1.cc:870
    break;

  case 190:
#line 546 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator(*(yystack_[1].value.node), "index1"); }
#line 1743 "parser.tab.c" // lalr1.cc:870
    break;

  case 191:
#line 547 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator(*(yystack_[2].value.node), "array0"); }
#line 1749 "parser.tab.c" // lalr1.cc:870
    break;

  case 192:
#line 548 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator(*(yystack_[3].value.node), *(yystack_[1].value.node), "array1"); }
#line 1755 "parser.tab.c" // lalr1.cc:870
    break;

  case 193:
#line 549 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator("array2"); }
#line 1761 "parser.tab.c" // lalr1.cc:870
    break;

  case 194:
#line 550 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator(*(yystack_[3].value.node), "index2"); }
#line 1767 "parser.tab.c" // lalr1.cc:870
    break;

  case 195:
#line 551 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator("function0"); }
#line 1773 "parser.tab.c" // lalr1.cc:870
    break;

  case 196:
#line 552 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator(*(yystack_[1].value.node), "function1"); }
#line 1779 "parser.tab.c" // lalr1.cc:870
    break;

  case 197:
#line 553 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator(*(yystack_[2].value.node), "function2"); }
#line 1785 "parser.tab.c" // lalr1.cc:870
    break;

  case 198:
#line 554 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::DirectAbstractDeclarator(*(yystack_[3].value.node), *(yystack_[1].value.node), "function3"); }
#line 1791 "parser.tab.c" // lalr1.cc:870
    break;

  case 199:
#line 558 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1797 "parser.tab.c" // lalr1.cc:870
    break;

  case 200:
#line 559 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Initializer(*(yystack_[1].value.node), "initializerList0"); }
#line 1803 "parser.tab.c" // lalr1.cc:870
    break;

  case 201:
#line 560 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Initializer(*(yystack_[2].value.node), "initializerList1"); }
#line 1809 "parser.tab.c" // lalr1.cc:870
    break;

  case 202:
#line 564 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1815 "parser.tab.c" // lalr1.cc:870
    break;

  case 203:
#line 565 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::InitializerList(*(yystack_[1].value.node), *(yystack_[0].value.node), "designation"); }
#line 1821 "parser.tab.c" // lalr1.cc:870
    break;

  case 204:
#line 566 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::InitializerList(*(yystack_[2].value.node), *(yystack_[0].value.node), "initializer"); }
#line 1827 "parser.tab.c" // lalr1.cc:870
    break;

  case 205:
#line 567 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::InitializerList(*(yystack_[3].value.node), *(yystack_[1].value.node), *(yystack_[0].value.node), "designationInitalizer"); }
#line 1833 "parser.tab.c" // lalr1.cc:870
    break;

  case 206:
#line 571 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Designation(*(yystack_[1].value.nodeList)); }
#line 1839 "parser.tab.c" // lalr1.cc:870
    break;

  case 207:
#line 575 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::DesignatorList(*(yystack_[0].value.node)); }
#line 1845 "parser.tab.c" // lalr1.cc:870
    break;

  case 208:
#line 576 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[1].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 1851 "parser.tab.c" // lalr1.cc:870
    break;

  case 209:
#line 580 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Designator(*(yystack_[1].value.node), "index"); }
#line 1857 "parser.tab.c" // lalr1.cc:870
    break;

  case 210:
#line 581 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::Designator(*(new forec::ast::PrimaryExpression(*(yystack_[0].value.str), yystack_[0].location.begin.line, "identifier")), "member"); }
#line 1863 "parser.tab.c" // lalr1.cc:870
    break;

  case 211:
#line 585 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1869 "parser.tab.c" // lalr1.cc:870
    break;

  case 212:
#line 586 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1875 "parser.tab.c" // lalr1.cc:870
    break;

  case 213:
#line 587 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1881 "parser.tab.c" // lalr1.cc:870
    break;

  case 214:
#line 588 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1887 "parser.tab.c" // lalr1.cc:870
    break;

  case 215:
#line 589 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1893 "parser.tab.c" // lalr1.cc:870
    break;

  case 216:
#line 590 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1899 "parser.tab.c" // lalr1.cc:870
    break;

  case 217:
#line 591 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1905 "parser.tab.c" // lalr1.cc:870
    break;

  case 218:
#line 592 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1911 "parser.tab.c" // lalr1.cc:870
    break;

  case 219:
#line 593 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1917 "parser.tab.c" // lalr1.cc:870
    break;

  case 220:
#line 597 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::LabeledStatement(*(new forec::ast::PrimaryExpression(*(yystack_[2].value.str), yystack_[2].location.begin.line, "identifier")), *(yystack_[0].value.node), "label"); }
#line 1923 "parser.tab.c" // lalr1.cc:870
    break;

  case 221:
#line 598 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::LabeledStatement(*(yystack_[2].value.node), *(yystack_[0].value.node), "case"); }
#line 1929 "parser.tab.c" // lalr1.cc:870
    break;

  case 222:
#line 599 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::LabeledStatement(*(yystack_[0].value.node), "default"); }
#line 1935 "parser.tab.c" // lalr1.cc:870
    break;

  case 223:
#line 603 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::CompoundStatement(); }
#line 1941 "parser.tab.c" // lalr1.cc:870
    break;

  case 224:
#line 604 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::CompoundStatement(*(yystack_[1].value.nodeList)); }
#line 1947 "parser.tab.c" // lalr1.cc:870
    break;

  case 225:
#line 608 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::BlockItemList(*(yystack_[0].value.node)); }
#line 1953 "parser.tab.c" // lalr1.cc:870
    break;

  case 226:
#line 609 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[1].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 1959 "parser.tab.c" // lalr1.cc:870
    break;

  case 227:
#line 613 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1965 "parser.tab.c" // lalr1.cc:870
    break;

  case 228:
#line 614 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1971 "parser.tab.c" // lalr1.cc:870
    break;

  case 229:
#line 615 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1977 "parser.tab.c" // lalr1.cc:870
    break;

  case 230:
#line 619 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::ExpressionStatement(); }
#line 1983 "parser.tab.c" // lalr1.cc:870
    break;

  case 231:
#line 620 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::ExpressionStatement(*(yystack_[1].value.nodeList)); }
#line 1989 "parser.tab.c" // lalr1.cc:870
    break;

  case 232:
#line 624 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::SelectionStatement(*(yystack_[2].value.nodeList), *(yystack_[0].value.node), "if"); }
#line 1995 "parser.tab.c" // lalr1.cc:870
    break;

  case 233:
#line 625 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::SelectionStatement(*(yystack_[4].value.nodeList), *(yystack_[2].value.node), *(yystack_[0].value.node), "ifElse"); }
#line 2001 "parser.tab.c" // lalr1.cc:870
    break;

  case 234:
#line 626 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::SelectionStatement(*(yystack_[2].value.nodeList), *(yystack_[0].value.node), "switch"); }
#line 2007 "parser.tab.c" // lalr1.cc:870
    break;

  case 235:
#line 630 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[4].location.begin.line, *(yystack_[2].value.nodeList), *(yystack_[0].value.node), "while"); }
#line 2013 "parser.tab.c" // lalr1.cc:870
    break;

  case 236:
#line 631 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[6].location.begin.line, *(yystack_[5].value.node), *(yystack_[2].value.nodeList), "doWhile"); }
#line 2019 "parser.tab.c" // lalr1.cc:870
    break;

  case 237:
#line 632 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[5].location.begin.line, *(yystack_[3].value.node), *(yystack_[2].value.node), *(yystack_[0].value.node), "for0"); }
#line 2025 "parser.tab.c" // lalr1.cc:870
    break;

  case 238:
#line 633 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[6].location.begin.line, *(yystack_[4].value.node), *(yystack_[3].value.node), *(yystack_[2].value.nodeList), *(yystack_[0].value.node), "for1"); }
#line 2031 "parser.tab.c" // lalr1.cc:870
    break;

  case 239:
#line 634 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[5].location.begin.line, *(yystack_[3].value.node), *(yystack_[2].value.node), *(yystack_[0].value.node), "for2"); }
#line 2037 "parser.tab.c" // lalr1.cc:870
    break;

  case 240:
#line 635 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[6].location.begin.line, *(yystack_[4].value.node), *(yystack_[3].value.node), *(yystack_[2].value.nodeList), *(yystack_[0].value.node), "for3"); }
#line 2043 "parser.tab.c" // lalr1.cc:870
    break;

  case 241:
#line 636 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[8].location.begin.line, *(yystack_[6].value.nodeList), *(yystack_[3].value.str), *(yystack_[1].value.str), *(yystack_[0].value.node), "while"); }
#line 2049 "parser.tab.c" // lalr1.cc:870
    break;

  case 242:
#line 637 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[10].location.begin.line, *(yystack_[9].value.node), *(yystack_[6].value.nodeList), *(yystack_[3].value.str), *(yystack_[1].value.str), "doWhile"); }
#line 2055 "parser.tab.c" // lalr1.cc:870
    break;

  case 243:
#line 638 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[9].location.begin.line, *(yystack_[7].value.node), *(yystack_[6].value.node), *(yystack_[3].value.str), *(yystack_[1].value.str), *(yystack_[0].value.node), "for0"); }
#line 2061 "parser.tab.c" // lalr1.cc:870
    break;

  case 244:
#line 639 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[10].location.begin.line, *(yystack_[8].value.node), *(yystack_[7].value.node), *(yystack_[6].value.nodeList), *(yystack_[3].value.str), *(yystack_[1].value.str), *(yystack_[0].value.node), "for1"); }
#line 2067 "parser.tab.c" // lalr1.cc:870
    break;

  case 245:
#line 640 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[9].location.begin.line, *(yystack_[7].value.node), *(yystack_[6].value.node), *(yystack_[3].value.str), *(yystack_[1].value.str), *(yystack_[0].value.node), "for2"); }
#line 2073 "parser.tab.c" // lalr1.cc:870
    break;

  case 246:
#line 641 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::IterationStatement(yystack_[10].location.begin.line, *(yystack_[8].value.node), *(yystack_[7].value.node), *(yystack_[6].value.nodeList), *(yystack_[3].value.str), *(yystack_[1].value.str), *(yystack_[0].value.node), "for3"); }
#line 2079 "parser.tab.c" // lalr1.cc:870
    break;

  case 247:
#line 646 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::JumpStatement(*(new forec::ast::PrimaryExpression(*(yystack_[1].value.str), yystack_[1].location.begin.line, "identifier")), "goto"); }
#line 2085 "parser.tab.c" // lalr1.cc:870
    break;

  case 248:
#line 647 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::JumpStatement("continue"); }
#line 2091 "parser.tab.c" // lalr1.cc:870
    break;

  case 249:
#line 648 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::JumpStatement("break"); }
#line 2097 "parser.tab.c" // lalr1.cc:870
    break;

  case 250:
#line 649 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::JumpStatement("return"); }
#line 2103 "parser.tab.c" // lalr1.cc:870
    break;

  case 251:
#line 650 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::JumpStatement(*(yystack_[1].value.nodeList), "returnExpression"); }
#line 2109 "parser.tab.c" // lalr1.cc:870
    break;

  case 252:
#line 654 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::PauseStatement(); }
#line 2115 "parser.tab.c" // lalr1.cc:870
    break;

  case 253:
#line 658 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::ParStatement(*(yystack_[2].value.nodeList)); }
#line 2121 "parser.tab.c" // lalr1.cc:870
    break;

  case 254:
#line 662 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AbortStatement(*(yystack_[5].value.node), *(yystack_[2].value.nodeList), "weakNonImmediate"); }
#line 2127 "parser.tab.c" // lalr1.cc:870
    break;

  case 255:
#line 663 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AbortStatement(*(yystack_[5].value.node), *(yystack_[2].value.nodeList), "strongNonImmediate"); }
#line 2133 "parser.tab.c" // lalr1.cc:870
    break;

  case 256:
#line 664 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AbortStatement(*(yystack_[6].value.node), *(yystack_[2].value.nodeList), "weakImmediate"); }
#line 2139 "parser.tab.c" // lalr1.cc:870
    break;

  case 257:
#line 665 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::AbortStatement(*(yystack_[6].value.node), *(yystack_[2].value.nodeList), "strongImmediate"); }
#line 2145 "parser.tab.c" // lalr1.cc:870
    break;

  case 258:
#line 669 "parser.y" // lalr1.cc:870
    { rootNode.append(*(yystack_[0].value.node)); }
#line 2151 "parser.tab.c" // lalr1.cc:870
    break;

  case 259:
#line 670 "parser.y" // lalr1.cc:870
    { rootNode.append(*(yystack_[0].value.node)); }
#line 2157 "parser.tab.c" // lalr1.cc:870
    break;

  case 260:
#line 674 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2163 "parser.tab.c" // lalr1.cc:870
    break;

  case 261:
#line 675 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2169 "parser.tab.c" // lalr1.cc:870
    break;

  case 262:
#line 676 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2175 "parser.tab.c" // lalr1.cc:870
    break;

  case 263:
#line 677 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 2181 "parser.tab.c" // lalr1.cc:870
    break;

  case 264:
#line 681 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::FunctionDefinition(*(yystack_[3].value.nodeList), *(yystack_[2].value.node), *(yystack_[1].value.nodeList), *(yystack_[0].value.node)); }
#line 2187 "parser.tab.c" // lalr1.cc:870
    break;

  case 265:
#line 682 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::FunctionDefinition(*(yystack_[2].value.nodeList), *(yystack_[1].value.node), *(yystack_[0].value.node)); }
#line 2193 "parser.tab.c" // lalr1.cc:870
    break;

  case 266:
#line 686 "parser.y" // lalr1.cc:870
    { (yylhs.value.node) = new forec::ast::ThreadDefinition(*(yystack_[1].value.node), *(yystack_[0].value.node)); }
#line 2199 "parser.tab.c" // lalr1.cc:870
    break;

  case 267:
#line 690 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = new forec::ast::DeclarationList(*(yystack_[0].value.node)); }
#line 2205 "parser.tab.c" // lalr1.cc:870
    break;

  case 268:
#line 691 "parser.y" // lalr1.cc:870
    { (yylhs.value.nodeList) = (yystack_[1].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 2211 "parser.tab.c" // lalr1.cc:870
    break;


#line 2215 "parser.tab.c" // lalr1.cc:870
            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
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

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
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
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

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
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short Parser::yypact_ninf_ = -337;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
    1832,  -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,
    -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,
    -337,  -337,  -337,  -337,  -337,  -337,  -337,    43,  -337,  -337,
    -337,    68,  -337,  -337,    10,  2300,  2300,  -337,    53,  -337,
    2300,  2300,  1723,  -337,  -337,  -337,    45,    41,  -337,    68,
     263,   -29,  -337,   -18,   -20,    20,  -337,   -26,  1884,  -337,
    -337,    67,   862,  -337,  -337,  -337,  -337,    41,   -51,    92,
    -337,    16,  -337,  -337,   263,    68,  -337,   -10,   370,  1356,
    -337,  -337,  1775,  1166,   -20,  -337,    68,  -337,    10,  -337,
    2137,   862,   862,  2020,  -337,    21,   862,   206,  1508,  -337,
      29,  -337,  -337,  -337,  -337,   -13,   167,    86,  -337,  -337,
    1528,  1589,  1589,  -337,  -337,  1508,   128,    79,   116,   184,
     998,   194,   277,   193,   199,   577,   211,   238,   252,   244,
    1113,  -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,
    -337,   196,   237,  1508,  -337,    94,    65,   292,    72,   309,
     257,   240,   243,   337,    23,  -337,  -337,    38,  -337,  -337,
    -337,  -337,   466,  -337,  -337,  -337,  -337,  -337,  -337,  -337,
    -337,  -337,  1285,  -337,   286,  -337,  -337,    64,   274,   270,
    -337,    89,   266,  -337,   276,   278,  1209,  -337,  -337,  2075,
    -337,  -337,  -337,  1508,    71,  -337,   265,  -337,  -337,    50,
    -337,  -337,  -337,  -337,  -337,  -337,   998,  1113,  -337,  1113,
    -337,  -337,   273,   998,  1508,  1508,  1508,   319,   945,   275,
    -337,  -337,  -337,    74,  -337,   379,   244,   305,    99,    83,
     300,   382,  -337,  -337,  1379,  1508,   383,  -337,  -337,  -337,
    -337,  -337,  -337,  -337,  -337,  -337,  -337,  -337,  1508,  -337,
    1508,  1508,  1508,  1508,  1508,  1508,  1508,  1508,  1508,  1508,
    1508,  1508,  1508,  1508,  1508,  1508,  1508,  1508,  1508,  1508,
    -337,  -337,  -337,  1508,   384,  -337,   250,  1356,   -27,  -337,
    -337,  1658,  1399,  -337,    69,  -337,    14,  -337,  2255,  -337,
     385,  1242,  -337,  -337,  1508,  -337,   303,   304,  -337,  -337,
      21,  -337,  1508,  -337,  -337,   307,   308,   998,  -337,   110,
     118,   122,   310,  1041,  1041,  -337,  -337,   150,   316,    12,
    -337,  1962,   126,  -337,  1413,  -337,  -337,   151,  -337,   204,
    -337,  -337,  -337,  -337,  -337,    94,    94,    65,    65,   292,
     292,   292,   292,    72,    72,   309,   257,   240,   243,   337,
      -8,  -337,   311,  -337,  -337,   744,  -337,  -337,  -337,  -337,
     312,   339,  -337,   343,   352,    14,  2198,  1432,  -337,  -337,
    -337,   353,   360,  -337,  -337,  -337,  -337,   362,   362,  -337,
     998,   998,   560,  1508,  1475,  1494,   289,    51,   365,  1508,
    1285,  -337,  -337,  1508,  -337,  1508,  -337,  -337,  -337,  1356,
    -337,  -337,  -337,  -337,  -337,   367,  -337,   366,   368,  -337,
    -337,   396,  -337,   452,  -337,   155,   636,   158,   712,   159,
    -337,   374,  1508,  1508,   160,   254,  -337,  -337,  -337,  -337,
    -337,  -337,   998,   371,   220,   456,  -337,   788,   469,  -337,
     864,  1508,   162,   181,   373,  -337,  1262,  -337,   473,  -337,
     476,   375,   477,  -337,   376,   480,  -337,   188,   380,   381,
    -337,  -337,   998,   378,   484,   386,   485,   412,   419,  -337,
    -337,  -337,   486,   998,   487,   998,   488,  -337,   428,  -337,
     998,  -337,   998,  -337,  -337,  -337
  };

  const unsigned short
  Parser::yydefact_[] =
  {
       0,     2,     3,   118,    99,   100,   101,   102,   103,   152,
     146,   105,   106,   107,   108,   111,   112,   109,   110,   145,
     147,   104,   113,   114,   115,   122,   123,     0,   150,   148,
     149,     0,   260,   263,     0,    85,    87,   116,     0,   117,
      89,    91,     0,   258,   261,   262,   140,     0,   155,     0,
     168,     0,    93,    95,   154,     0,    82,     0,    95,    86,
      88,   121,     0,    90,    92,     1,   259,     0,   143,     0,
     141,     0,   172,   170,   169,     0,    84,     0,     0,     0,
      96,   266,     0,     0,   153,    83,     0,   267,     0,   265,
       0,     0,   128,     0,   124,     0,   130,     0,     0,   136,
       0,   156,   173,   171,    94,    95,     0,     4,     5,     6,
       0,     0,     0,     7,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   223,    28,    29,    30,    31,    32,    33,   230,   229,
      10,    22,    34,     0,    36,    40,    43,    46,    51,    54,
      56,    58,    60,    62,    64,    66,    79,     0,   227,   228,
     211,   212,     0,   225,   213,   214,   215,   216,   217,   218,
     219,     4,     0,   199,    97,   181,   167,   180,     0,   174,
     176,     0,     0,   164,    29,     0,     0,   268,   264,     0,
     127,   120,   125,     0,     0,   131,   133,   129,   137,     0,
      34,    81,   144,   138,   142,   151,     0,     0,    26,     0,
      23,    24,     0,     0,     0,     0,     0,     0,     0,     0,
     248,   249,   250,     0,   252,     0,     0,     0,     0,   183,
       0,     0,    16,    17,     0,     0,     0,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    68,     0,    25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     231,   224,   226,     0,     0,   202,     0,     0,     0,   207,
      98,     0,     0,   178,   185,   179,   186,   165,     0,   166,
       0,     0,   163,   159,     0,   158,    29,     0,   119,   134,
       0,   126,     0,   139,   220,     0,     0,     0,   222,     0,
       0,     0,     0,     0,     0,   247,   251,     0,     0,     0,
       9,     0,   185,   184,     0,    15,    12,     0,    20,     0,
      14,    67,    37,    38,    39,    41,    42,    44,    45,    49,
      50,    47,    48,    52,    53,    55,    57,    59,    61,    63,
       0,    80,     0,   210,   200,     0,   203,   206,   208,   195,
       0,     0,   189,    29,     0,   187,     0,     0,   175,   177,
     182,     0,     0,   162,   157,   132,   135,    27,     0,   221,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    13,     0,    11,     0,   209,   201,   204,     0,
     196,   188,   193,   190,   197,     0,   191,    29,     0,   160,
     161,   232,   234,     0,   235,     0,     0,     0,     0,     0,
     253,     0,     0,     0,     0,     0,    21,    65,   205,   198,
     194,   192,     0,     0,     0,     0,   239,     0,     0,   237,
       0,     0,     0,     0,     0,    18,     0,   233,     0,   236,
       0,     0,     0,   240,     0,     0,   238,     0,     0,     0,
     255,    19,     0,     0,     0,     0,     0,     0,     0,   254,
     257,   241,     0,     0,     0,     0,     0,   256,     0,   245,
       0,   243,     0,   242,   246,   244
  };

  const short
  Parser::yypgoto_[] =
  {
    -337,   -50,  -337,  -337,  -337,   -34,  -337,  -129,    95,    98,
      58,    97,   281,   282,   272,   283,   285,  -337,   -93,   -79,
    -337,   -90,  -102,   -31,     3,    -5,   475,  -337,    46,  -337,
    -337,   457,   -57,   -59,  -337,   253,  -337,   491,   -88,   -42,
     395,  -337,   -25,   -44,   -43,   -66,   -80,  -337,   267,   329,
      80,  -154,  -254,   -78,   182,  -336,  -337,   295,  -110,  -337,
     -37,  -337,   413,  -200,  -337,  -337,  -337,  -337,  -337,  -337,
    -337,   534,  -337,  -337,  -337
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,    32,   140,   141,   327,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     248,   157,   202,    33,    88,    51,    52,    35,    36,    37,
      38,    93,    94,    95,   194,   195,    39,    69,    70,    40,
      80,    41,   105,    54,    55,    74,   360,   179,   180,   181,
     230,   361,   286,   275,   276,   277,   278,   279,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
      42,    43,    44,    45,    90
  };

  const unsigned short
  Parser::yytable_[] =
  {
     173,   174,   178,    34,   185,   201,    53,    73,    72,    58,
     217,    84,   204,   212,   249,    48,    81,   186,   314,   399,
      96,    89,   201,   285,    71,    48,    48,    87,   139,    57,
     365,   103,   102,   190,    68,   223,   192,   197,    59,    60,
     228,    72,   267,    63,    64,    34,    68,   158,    46,    96,
      96,    96,    77,   188,    96,    68,    98,    77,    61,   187,
     273,   106,   274,    75,   200,    82,    75,    83,   365,    48,
     196,   229,    78,    48,    48,   323,   208,   210,   211,    76,
     357,   200,    85,    57,   269,   177,   257,   258,    96,    79,
     388,   299,   227,   173,    79,    49,   304,   389,   395,   366,
     201,   367,   101,   308,    50,    49,    49,   297,    92,   200,
     399,   204,   139,   384,   385,    50,   291,   228,    56,   228,
     203,   332,   333,   334,   309,   310,   311,   193,   268,   421,
     269,   158,   192,    47,   284,    67,   422,    92,    92,    92,
      72,   303,    92,    62,   102,   329,   270,    96,   229,   281,
     229,   282,   283,    49,   281,   328,   282,    91,    50,   200,
     253,   254,    50,   300,   214,    96,   269,    96,   321,   331,
     282,   352,   205,   259,   260,   289,    92,    50,   350,   301,
     201,   290,   316,    99,   100,   320,   322,   313,   250,   318,
     351,   269,   206,   251,   252,   391,   380,   379,   173,   356,
     376,   215,   269,   364,   381,   231,   232,   233,   382,   201,
     269,   321,   371,   282,   269,   372,   200,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   200,   200,   200,   200,
     200,   200,   200,   200,   213,    92,   386,   392,   284,   200,
      84,   434,   290,   393,   437,   440,   444,   269,   458,   102,
     269,   269,   269,    92,   269,    92,    71,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   459,   200,   216,
     411,   412,   414,   269,   468,   196,   173,   398,   322,   218,
     269,   234,   219,   235,   177,   236,   405,   305,   408,   306,
     200,   177,   394,   415,   417,   419,   269,   198,   199,   424,
      10,   220,   427,    10,   255,   256,   436,   221,   439,    19,
      20,   173,    19,    20,   426,   339,   340,   341,   342,   224,
     173,   428,   447,   225,   177,   261,   262,   453,   449,   450,
     456,   226,   442,   443,    78,    28,    29,    30,    28,    29,
      30,   354,   355,   264,   247,   445,   446,   265,   335,   336,
     263,   457,   471,   337,   338,   266,    77,    50,   343,   344,
     287,   200,   288,   479,   292,   481,   293,   173,   398,   177,
     484,   302,   485,     1,     2,   107,   108,   109,   110,   307,
     111,   112,   312,   315,   175,   319,   324,   325,   330,   353,
     370,   373,   374,   377,   378,   383,   387,   420,   400,   396,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,   401,   113,   114,   115,   116,
     117,   402,   118,   119,   120,   121,   122,   123,   124,   125,
     403,   409,    28,    29,    30,   126,   127,   128,   410,   129,
     423,    86,   390,   429,   430,   130,   431,   432,   433,   441,
      78,   131,   451,   132,   133,   134,   135,   136,   137,     1,
       2,   107,   108,   109,   110,   454,   111,   112,   138,   462,
     448,   460,   463,   465,   464,   466,   467,   472,   469,   470,
     473,   475,   478,   480,   482,   474,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,   476,   113,   114,   115,   116,   117,   477,   118,   119,
     120,   121,   122,   123,   124,   125,   483,   347,    28,    29,
      30,   126,   127,   128,   345,   129,   346,    86,   189,   348,
     104,   130,   349,   375,   317,   369,    78,   271,    97,   132,
     133,   134,   135,   136,   137,   107,   108,   109,   110,   280,
     111,   112,   425,   358,   138,   272,    66,     0,     0,     0,
       0,     0,   171,   108,   109,   110,     0,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,     0,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,   113,   114,   126,   127,   128,     0,   129,
       0,   107,   108,   109,   110,   130,   111,   112,     0,     0,
      78,     0,     0,   132,   133,   134,   135,   136,   137,     0,
       0,     0,   130,     0,     0,     0,     0,     0,   138,   413,
     132,   133,   134,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   222,     0,     0,     0,     0,
       0,     0,   113,   114,   115,   116,   117,     0,   118,   119,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
       0,   126,   127,   128,     0,   129,     0,   107,   108,   109,
     110,   130,   111,   112,     0,     0,    78,     0,     0,   132,
     133,   134,   135,   136,   137,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   435,     0,     0,     0,   171,
     108,   109,   110,     0,   111,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   114,
     115,   116,   117,     0,   118,   119,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,     0,   126,   127,   128,
       0,   129,     0,   107,   108,   109,   110,   130,   111,   112,
     113,   114,    78,     0,     0,   132,   133,   134,   135,   136,
     137,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,   438,     0,     0,     0,     0,     0,     0,     0,   130,
       0,   273,     0,   274,   172,   397,     0,   132,   133,   134,
     135,   136,   137,     0,   113,   114,   115,   116,   117,     0,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,   126,   127,   128,     0,   129,     0,   107,
     108,   109,   110,   130,   111,   112,     0,     0,    78,     0,
       0,   132,   133,   134,   135,   136,   137,     0,     0,     0,
       0,     0,     3,     0,     0,     0,   138,   452,     0,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,     0,     0,     0,
     113,   114,   115,   116,   117,     0,   118,   119,   120,   121,
     122,   123,   124,   125,    28,    29,    30,     0,     0,   126,
     127,   128,     0,   129,     0,     0,     0,     0,     0,   130,
     171,   108,   109,   110,    78,   111,   112,   132,   133,   134,
     135,   136,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   138,   455,     0,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
       0,   113,   114,   107,   108,   109,   110,     0,   111,   112,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
       0,     0,     0,     0,     0,     0,    86,     0,     0,     0,
     130,     0,     0,     0,     0,     0,     0,     0,   132,   133,
     134,   135,   136,   137,     0,     0,   171,   108,   109,   110,
       0,   111,   112,   138,   113,   114,   115,   116,   117,     0,
     118,   119,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,     0,   126,   127,   128,     0,   129,     0,     0,
       0,     0,     0,   130,     0,     0,     0,     0,    78,     0,
       0,   132,   133,   134,   135,   136,   137,   113,   114,     0,
       0,     0,     0,     0,     0,     0,   138,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   171,   108,
     109,   110,     0,   111,   112,     0,   130,     0,     0,     0,
       0,     0,     0,     0,   132,   133,   134,   135,   136,   137,
       0,     0,     0,     3,     0,     0,     0,     0,     0,   138,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,     0,   113,
     114,   171,   108,   109,   110,     0,   111,   112,     0,     0,
       0,     0,     0,     0,     0,    28,    29,    30,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   130,   182,
       0,     0,     0,    10,     0,     0,   132,   133,   134,   135,
     136,   137,    19,    20,   171,   108,   109,   110,     0,   111,
     112,     0,   113,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    29,
      30,     0,   294,     0,     0,     0,    10,   171,   108,   109,
     110,   130,   111,   112,   183,    19,    20,     0,     0,   132,
     184,   134,   135,   136,   137,   113,   114,   171,   108,   109,
     110,     0,   111,   112,     0,     0,     0,     0,     0,    10,
       0,    28,    29,    30,     0,     0,     0,     0,    19,    20,
     171,   108,   109,   110,   130,   111,   112,   295,   113,   114,
       0,     0,   132,   296,   134,   135,   136,   137,     0,     0,
       0,     0,     0,     0,    28,    29,    30,     0,   113,   114,
       0,     0,     0,     0,     0,     0,     0,   130,     0,     0,
       0,     0,     0,     0,     0,   132,   133,   134,   135,   136,
     137,   113,   114,     0,     0,     0,     0,   130,     0,   273,
       0,   274,   172,   461,     0,   132,   133,   134,   135,   136,
     137,   171,   108,   109,   110,     0,   111,   112,     0,     0,
     130,     0,   273,     0,   274,   172,     0,     0,   132,   133,
     134,   135,   136,   137,   171,   108,   109,   110,     0,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   171,   108,   109,   110,     0,   111,
     112,     0,   113,   114,     0,     0,     0,     0,   171,   108,
     109,   110,     0,   111,   112,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,   114,   171,   108,   109,
     110,   130,   111,   112,     0,     0,   172,     0,     0,   132,
     133,   134,   135,   136,   137,   113,   114,     0,     0,     0,
       0,     0,     0,     0,   130,   326,     0,     0,     0,   113,
     114,     0,   132,   133,   134,   135,   136,   137,     0,     0,
     171,   108,   109,   110,   130,   111,   112,   362,   113,   114,
       0,     0,   132,   363,   134,   135,   136,   137,   130,   171,
     108,   109,   110,   390,   111,   112,   132,   133,   134,   135,
     136,   137,     0,   171,   108,   109,   110,   130,   111,   112,
     406,     0,     0,     0,     0,   132,   407,   134,   135,   136,
     137,   113,   114,   171,   108,   109,   110,     0,   111,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,   114,     0,     0,     0,     0,     0,     0,     0,     0,
     130,   416,     0,     0,   113,   114,     0,     0,   132,   133,
     134,   135,   136,   137,     0,     0,     0,     0,     0,   130,
     418,     0,     0,     0,   113,   114,     0,   132,   133,   134,
     135,   136,   137,   130,   171,   108,   109,   110,     0,   111,
     112,   132,   133,   134,   135,   136,   137,     0,     0,     0,
       0,     0,     0,   207,     0,     0,     0,     0,     0,     0,
       0,   132,   133,   134,   135,   136,   137,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   209,     0,     0,     0,     0,     0,
       0,     0,   132,   133,   134,   135,   136,   137,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    65,     0,     0,     1,     2,     0,     0,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   281,   359,   282,     0,     0,     0,     0,
       0,     0,    50,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,     0,     0,
     175,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,    29,    30,     0,     0,
       0,     0,     0,     0,    31,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
       0,     0,     0,     0,     0,     1,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   176,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    29,    30,     0,     0,     0,
       0,     0,     0,    31,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    77,     0,    28,    29,    30,     0,
       0,     0,     0,     0,     0,    86,     0,     0,     0,     0,
       0,     0,     0,     0,    78,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    79,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,    29,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   321,   359,   282,
       3,     0,     0,     0,     0,     0,    50,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    29,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     3,     0,     0,     0,     0,
       0,   191,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   298,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      29,    30,     0,     0,     0,     0,     0,     0,    86,     0,
       0,     0,     0,     0,     0,     0,     0,    78,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      28,    29,    30,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   404,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
     368,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,    29,    30,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    29,    30
  };

  const short
  Parser::yycheck_[] =
  {
      79,    79,    82,     0,    83,    98,    31,    50,    50,    34,
     120,    55,   100,   115,   143,     5,    53,    83,   218,   355,
      62,    58,   115,   177,    49,     5,     5,    58,    78,    34,
     284,    74,    74,    92,     5,   125,    93,    96,    35,    36,
     130,    83,    19,    40,    41,    42,     5,    78,     5,    91,
      92,    93,    70,    90,    96,     5,   107,    70,     5,    90,
      87,    71,    89,    92,    98,    85,    92,    87,   322,     5,
      95,   130,    90,     5,     5,   229,   110,   111,   112,   108,
     107,   115,   108,    88,    92,    82,    14,    15,   130,   107,
      78,   193,   129,   172,   107,    85,   206,    85,   106,    85,
     193,    87,    86,   213,    94,    85,    85,   186,    62,   143,
     446,   199,   162,   313,   314,    94,   182,   207,   108,   209,
      91,   250,   251,   252,   214,   215,   216,   106,   105,    78,
      92,   162,   189,    90,   177,    90,    85,    91,    92,    93,
     182,    91,    96,    90,   186,   235,   108,   189,   207,    85,
     209,    87,   177,    85,    85,   234,    87,    90,    94,   193,
      95,    96,    94,    92,    85,   207,    92,   209,    85,   248,
      87,   273,     5,   101,   102,    86,   130,    94,   268,   108,
     273,    92,   108,    91,    92,    86,   229,   218,    94,   226,
     269,    92,   106,    99,   100,   324,    86,   307,   277,   277,
     302,    85,    92,   282,    86,     9,    10,    11,    86,   302,
      92,    85,   291,    87,    92,   294,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   106,   189,    86,    86,   281,   273,
     284,    86,    92,    92,    86,    86,    86,    92,    86,   291,
      92,    92,    92,   207,    92,   209,   281,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    86,   302,    85,
     380,   381,   382,    92,    86,   300,   355,   355,   321,    85,
      92,    85,     5,    87,   281,    89,   366,   207,   367,   209,
     324,   288,    88,   383,   384,   385,    92,    91,    92,   389,
      37,   108,   395,    37,    12,    13,   416,   108,   418,    46,
      47,   390,    46,    47,   393,   257,   258,   259,   260,   108,
     399,   399,   432,    85,   321,    16,    17,   437,   108,   109,
     440,    79,   422,   423,    90,    72,    73,    74,    72,    73,
      74,    91,    92,   103,   107,    91,    92,   104,   253,   254,
      93,   441,   462,   255,   256,    18,    70,    94,   261,   262,
      86,   395,    92,   473,    88,   475,    88,   446,   446,   366,
     480,   106,   482,     3,     4,     5,     6,     7,     8,   106,
      10,    11,    63,   108,     5,    80,    86,     5,     5,     5,
       5,    88,    88,    86,    86,    85,    80,   108,    86,    88,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    86,    56,    57,    58,    59,
      60,    88,    62,    63,    64,    65,    66,    67,    68,    69,
      88,    88,    72,    73,    74,    75,    76,    77,    88,    79,
      85,    81,    90,    86,    88,    85,    88,    61,     6,    85,
      90,    91,     6,    93,    94,    95,    96,    97,    98,     3,
       4,     5,     6,     7,     8,     6,    10,    11,   108,     6,
     109,   108,     6,     6,   109,   109,     6,   109,   108,   108,
       6,     6,     6,     6,     6,   109,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,   109,    56,    57,    58,    59,    60,   108,    62,    63,
      64,    65,    66,    67,    68,    69,   108,   265,    72,    73,
      74,    75,    76,    77,   263,    79,   264,    81,    91,   266,
      75,    85,   267,   300,   225,   288,    90,    91,    67,    93,
      94,    95,    96,    97,    98,     5,     6,     7,     8,   174,
      10,    11,   390,   278,   108,   162,    42,    -1,    -1,    -1,
      -1,    -1,     5,     6,     7,     8,    -1,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    -1,    62,    63,    64,    65,    66,    67,    68,    69,
      -1,    -1,    -1,    56,    57,    75,    76,    77,    -1,    79,
      -1,     5,     6,     7,     8,    85,    10,    11,    -1,    -1,
      90,    -1,    -1,    93,    94,    95,    96,    97,    98,    -1,
      -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,   108,   109,
      93,    94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    -1,    62,    63,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    -1,    79,    -1,     5,     6,     7,
       8,    85,    10,    11,    -1,    -1,    90,    -1,    -1,    93,
      94,    95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,   109,    -1,    -1,    -1,     5,
       6,     7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    -1,    62,    63,    64,    65,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      -1,    79,    -1,     5,     6,     7,     8,    85,    10,    11,
      56,    57,    90,    -1,    -1,    93,    94,    95,    96,    97,
      98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      -1,    87,    -1,    89,    90,    91,    -1,    93,    94,    95,
      96,    97,    98,    -1,    56,    57,    58,    59,    60,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    -1,    79,    -1,     5,
       6,     7,     8,    85,    10,    11,    -1,    -1,    90,    -1,
      -1,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,   108,   109,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    -1,    -1,
      56,    57,    58,    59,    60,    -1,    62,    63,    64,    65,
      66,    67,    68,    69,    72,    73,    74,    -1,    -1,    75,
      76,    77,    -1,    79,    -1,    -1,    -1,    -1,    -1,    85,
       5,     6,     7,     8,    90,    10,    11,    93,    94,    95,
      96,    97,    98,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    56,    57,     5,     6,     7,     8,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      85,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,
      95,    96,    97,    98,    -1,    -1,     5,     6,     7,     8,
      -1,    10,    11,   108,    56,    57,    58,    59,    60,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    -1,    79,    -1,    -1,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    90,    -1,
      -1,    93,    94,    95,    96,    97,    98,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     5,     6,
       7,     8,    -1,    10,    11,    -1,    85,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    94,    95,    96,    97,    98,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,   108,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    56,
      57,     5,     6,     7,     8,    -1,    10,    11,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    33,
      -1,    -1,    -1,    37,    -1,    -1,    93,    94,    95,    96,
      97,    98,    46,    47,     5,     6,     7,     8,    -1,    10,
      11,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    -1,    33,    -1,    -1,    -1,    37,     5,     6,     7,
       8,    85,    10,    11,    88,    46,    47,    -1,    -1,    93,
      94,    95,    96,    97,    98,    56,    57,     5,     6,     7,
       8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    72,    73,    74,    -1,    -1,    -1,    -1,    46,    47,
       5,     6,     7,     8,    85,    10,    11,    88,    56,    57,
      -1,    -1,    93,    94,    95,    96,    97,    98,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    94,    95,    96,    97,
      98,    56,    57,    -1,    -1,    -1,    -1,    85,    -1,    87,
      -1,    89,    90,    91,    -1,    93,    94,    95,    96,    97,
      98,     5,     6,     7,     8,    -1,    10,    11,    -1,    -1,
      85,    -1,    87,    -1,    89,    90,    -1,    -1,    93,    94,
      95,    96,    97,    98,     5,     6,     7,     8,    -1,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     5,     6,     7,     8,    -1,    10,
      11,    -1,    56,    57,    -1,    -1,    -1,    -1,     5,     6,
       7,     8,    -1,    10,    11,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,     5,     6,     7,
       8,    85,    10,    11,    -1,    -1,    90,    -1,    -1,    93,
      94,    95,    96,    97,    98,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    86,    -1,    -1,    -1,    56,
      57,    -1,    93,    94,    95,    96,    97,    98,    -1,    -1,
       5,     6,     7,     8,    85,    10,    11,    88,    56,    57,
      -1,    -1,    93,    94,    95,    96,    97,    98,    85,     5,
       6,     7,     8,    90,    10,    11,    93,    94,    95,    96,
      97,    98,    -1,     5,     6,     7,     8,    85,    10,    11,
      88,    -1,    -1,    -1,    -1,    93,    94,    95,    96,    97,
      98,    56,    57,     5,     6,     7,     8,    -1,    10,    11,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    56,    57,    -1,    -1,    93,    94,
      95,    96,    97,    98,    -1,    -1,    -1,    -1,    -1,    85,
      86,    -1,    -1,    -1,    56,    57,    -1,    93,    94,    95,
      96,    97,    98,    85,     5,     6,     7,     8,    -1,    10,
      11,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    93,    94,    95,    96,    97,    98,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    85,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    94,    95,    96,    97,    98,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     0,    -1,    -1,     3,     4,    -1,    -1,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    -1,
       5,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,     3,     4,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   107,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,    86,    87,
      30,    -1,    -1,    -1,    -1,    -1,    94,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    91,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    91,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,     4,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    72,    73,
      74,    81,   111,   133,   134,   137,   138,   139,   140,   146,
     149,   151,   180,   181,   182,   183,     5,    90,     5,    85,
      94,   135,   136,   152,   153,   154,   108,   135,   152,   134,
     134,     5,    90,   134,   134,     0,   181,    90,     5,   147,
     148,   152,   149,   154,   155,    92,   108,    70,    90,   107,
     150,   170,    85,    87,   153,   108,    81,   133,   134,   170,
     184,    90,   138,   141,   142,   143,   149,   147,   107,    91,
      92,    86,   149,   154,   136,   152,    71,     5,     6,     7,
       8,    10,    11,    56,    57,    58,    59,    60,    62,    63,
      64,    65,    66,    67,    68,    69,    75,    76,    77,    79,
      85,    91,    93,    94,    95,    96,    97,    98,   108,   111,
     112,   113,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   131,   133,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,     5,    90,   129,   163,     5,    86,   134,   156,   157,
     158,   159,    33,    88,    94,   129,   155,   133,   170,   141,
     143,    91,   142,   106,   144,   145,   152,   143,    91,    92,
     115,   128,   132,    91,   148,     5,   106,    85,   115,    85,
     115,   115,   132,   106,    85,    85,    85,   168,    85,     5,
     108,   108,   108,   131,   108,    85,    79,   170,   131,   143,
     160,     9,    10,    11,    85,    87,    89,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,   107,   130,   117,
      94,    99,   100,    95,    96,    12,    13,    14,    15,   101,
     102,    16,    17,    93,   103,   104,    18,    19,   105,    92,
     108,    91,   172,    87,    89,   163,   164,   165,   166,   167,
     150,    85,    87,   152,   154,   161,   162,    86,    92,    86,
      92,   155,    88,    88,    33,    88,    94,   129,    91,   132,
      92,   108,   106,    91,   168,   160,   160,   106,   168,   131,
     131,   131,    63,   133,   173,   108,   108,   159,   170,    80,
      86,    85,   154,   161,    86,     5,    86,   114,   129,   131,
       5,   129,   117,   117,   117,   118,   118,   119,   119,   120,
     120,   120,   120,   121,   121,   122,   123,   124,   125,   126,
     131,   129,   132,     5,    91,    92,   163,   107,   167,    86,
     156,   161,    88,    94,   129,   162,    85,    87,    55,   158,
       5,   129,   129,    88,    88,   145,   132,    86,    86,   168,
      86,    86,    86,    85,   173,   173,    86,    80,    78,    85,
      90,   117,    86,    92,    88,   106,    88,    91,   163,   165,
      86,    86,    88,    88,    86,   156,    88,    94,   129,    88,
      88,   168,   168,   109,   168,   131,    86,   131,    86,   131,
     108,    78,    85,    85,   131,   164,   129,   128,   163,    86,
      88,    88,    61,     6,    86,   109,   168,    86,   109,   168,
      86,    85,   131,   131,    86,    91,    92,   168,   109,   108,
     109,     6,   109,   168,     6,   109,   168,   131,    86,    86,
     108,    91,     6,     6,   109,     6,   109,     6,    86,   108,
     108,   168,   109,     6,   109,     6,   109,   108,     6,   168,
       6,   168,     6,   108,   168,   168
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,   110,   111,   111,   112,   112,   112,   112,   112,   112,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     114,   114,   115,   115,   115,   115,   115,   115,   116,   116,
     116,   116,   116,   116,   117,   117,   118,   118,   118,   118,
     119,   119,   119,   120,   120,   120,   121,   121,   121,   121,
     121,   122,   122,   122,   123,   123,   124,   124,   125,   125,
     126,   126,   127,   127,   128,   128,   129,   129,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   131,
     131,   132,   133,   133,   133,   134,   134,   134,   134,   134,
     134,   134,   134,   135,   135,   136,   136,   136,   136,   137,
     137,   137,   137,   137,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   139,
     139,   139,   140,   140,   141,   141,   142,   143,   143,   143,
     143,   144,   144,   145,   145,   145,   146,   146,   146,   146,
     146,   147,   147,   148,   148,   149,   149,   149,   149,   149,
     149,   150,   151,   152,   152,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   154,   154,
     154,   154,   155,   155,   156,   156,   157,   157,   158,   158,
     158,   159,   159,   160,   160,   161,   161,   161,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   163,
     163,   163,   164,   164,   164,   164,   165,   166,   166,   167,
     167,   168,   168,   168,   168,   168,   168,   168,   168,   168,
     169,   169,   169,   170,   170,   171,   171,   172,   172,   172,
     173,   173,   174,   174,   174,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   176,   176,   176,
     176,   176,   177,   178,   179,   179,   179,   179,   180,   180,
     181,   181,   181,   181,   182,   182,   183,   184,   184
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     4,     3,     4,     3,     3,     2,     2,     6,     7,
       1,     3,     1,     2,     2,     2,     2,     4,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     3,     3,     1,     2,     1,     2,     1,
       2,     1,     2,     1,     3,     1,     2,     3,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     5,
       4,     2,     1,     1,     1,     2,     3,     2,     1,     2,
       1,     1,     3,     1,     2,     3,     4,     5,     5,     6,
       2,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     1,     2,     1,     1,     3,     5,     4,     4,
       6,     6,     5,     4,     3,     4,     4,     3,     1,     2,
       2,     3,     1,     2,     1,     3,     1,     3,     2,     2,
       1,     1,     3,     1,     2,     1,     1,     2,     3,     2,
       3,     3,     4,     3,     4,     2,     3,     3,     4,     1,
       3,     4,     1,     2,     3,     4,     2,     1,     2,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     3,     2,     3,     1,     2,     1,     1,     1,
       1,     2,     5,     7,     5,     5,     7,     6,     7,     6,
       7,     9,    11,    10,    11,    10,    11,     3,     2,     2,
       2,     3,     2,     5,     8,     7,     9,     8,     1,     2,
       1,     1,     1,     1,     4,     3,     3,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "INCLUDE", "DEFINE", "IDENTIFIER",
  "CONSTANT", "STRING_LITERAL", "SIZEOF", "PTR_OP", "INC_OP", "DEC_OP",
  "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN",
  "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN",
  "OR_ASSIGN", "TYPE_NAME", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "INLINE", "RESTRICT", "CHAR", "SHORT", "INT", "LONG",
  "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE", "CONST", "VOLATILE", "VOID",
  "BOOL", "COMPLEX", "IMAGINARY", "STRUCT", "UNION", "ENUM", "ELLIPSIS",
  "TRUE", "FALSE", "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE",
  "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "COMBINE", "WITH",
  "SHARED", "INPUT", "OUTPUT", "PAUSE", "PAR", "WEAK", "IMMEDIATE",
  "ABORT", "WHEN", "THREAD", "CS_NONE", "CS_START", "CS_END", "'('", "')'",
  "'['", "']'", "'.'", "'{'", "'}'", "','", "'&'", "'*'", "'+'", "'-'",
  "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "':'",
  "'='", "';'", "'#'", "$accept", "preprocessor_directives",
  "primary_expression", "postfix_expression", "argument_expression_list",
  "unary_expression", "unary_operator", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "combine_specifier", "function_specifier",
  "declarator", "direct_declarator", "pointer", "type_qualifier_list",
  "parameter_type_list", "parameter_list", "parameter_declaration",
  "identifier_list", "type_name", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "designation", "designator_list", "designator", "statement",
  "labeled_statement", "compound_statement", "block_item_list",
  "block_item", "expression_statement", "selection_statement",
  "iteration_statement", "jump_statement", "pause_statement",
  "par_statement", "abort_statement", "translation_unit",
  "external_declaration", "function_definition", "thread_definition",
  "declaration_list", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short
  Parser::yyrline_[] =
  {
       0,   196,   196,   197,   201,   202,   203,   204,   205,   206,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     223,   224,   228,   229,   230,   231,   232,   233,   237,   238,
     239,   240,   241,   242,   246,   247,   251,   252,   253,   254,
     258,   259,   260,   264,   265,   266,   270,   271,   272,   273,
     274,   278,   279,   280,   284,   285,   289,   290,   294,   295,
     299,   300,   304,   305,   309,   310,   314,   315,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   333,
     334,   338,   346,   347,   348,   352,   353,   354,   355,   356,
     357,   358,   359,   363,   364,   368,   369,   370,   371,   375,
     376,   377,   378,   379,   383,   384,   385,   386,   387,   388,
     389,   390,   391,   392,   393,   394,   395,   396,   397,   401,
     402,   403,   407,   408,   412,   413,   417,   421,   422,   423,
     424,   428,   429,   433,   434,   435,   439,   440,   441,   442,
     443,   447,   448,   452,   453,   457,   458,   459,   460,   461,
     462,   466,   470,   477,   478,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   495,   499,   500,
     501,   502,   506,   507,   512,   513,   517,   518,   522,   523,
     524,   528,   529,   533,   534,   538,   539,   540,   544,   545,
     546,   547,   548,   549,   550,   551,   552,   553,   554,   558,
     559,   560,   564,   565,   566,   567,   571,   575,   576,   580,
     581,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     597,   598,   599,   603,   604,   608,   609,   613,   614,   615,
     619,   620,   624,   625,   626,   630,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   641,   646,   647,   648,
     649,   650,   654,   658,   662,   663,   664,   665,   669,   670,
     674,   675,   676,   677,   681,   682,   686,   690,   691
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    98,     2,   109,     2,   100,    93,     2,
      85,    86,    94,    95,    92,    96,    89,    99,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   106,   108,
     101,   107,   102,   105,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    87,     2,    88,   103,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    90,   104,    91,    97,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
    };
    const unsigned user_token_number_max_ = 339;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 12 "parser.y" // lalr1.cc:1181
} } // forec::loader
#line 3383 "parser.tab.c" // lalr1.cc:1181
#line 695 "parser.y" // lalr1.cc:1182


// Now that we have the Parser declared, we can declare the Scanner and implement
// the yylex function
#include "Scanner.hpp"
static int yylex(forec::loader::Parser::semantic_type * yylval, forec::loader::Parser::location_type * yylloc, forec::loader::Scanner &scanner) {
	return scanner.yylex(yylval, yylloc);
}

