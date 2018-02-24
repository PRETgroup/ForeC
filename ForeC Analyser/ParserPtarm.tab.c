// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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

// Take the name prefix into account.
#define yylex   ptarmlex

// First part of user declarations.

#line 39 "ParserPtarm.tab.c" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "ParserPtarm.tab.h"

// User implementation prologue.

#line 53 "ParserPtarm.tab.c" // lalr1.cc:412
// Unqualified %code blocks.
#line 55 "ParserPtarm.y" // lalr1.cc:413

	// Prototype for the yylex function
	static int yylex(forec::loader::ParserPtarm::semantic_type * yylval, forec::loader::ParserPtarm::location_type * yylloc, forec::loader::ScannerPtarm &scanner);

#line 60 "ParserPtarm.tab.c" // lalr1.cc:413


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
#if PTARMDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
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

#else // !PTARMDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !PTARMDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "ParserPtarm.y" // lalr1.cc:479
namespace forec { namespace loader {
#line 146 "ParserPtarm.tab.c" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  ParserPtarm::yytnamerr_ (const char *yystr)
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
  ParserPtarm::ParserPtarm (forec::loader::ScannerPtarm &scanner_yyarg, forec::cfg::Node &rootNode_yyarg)
    :
#if PTARMDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      rootNode (rootNode_yyarg)
  {}

  ParserPtarm::~ParserPtarm ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  ParserPtarm::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  ParserPtarm::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  ParserPtarm::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  ParserPtarm::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  ParserPtarm::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  ParserPtarm::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  ParserPtarm::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  ParserPtarm::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  ParserPtarm::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  ParserPtarm::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  ParserPtarm::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  ParserPtarm::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  ParserPtarm::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  ParserPtarm::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  ParserPtarm::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  ParserPtarm::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  ParserPtarm::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  ParserPtarm::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  ParserPtarm::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  ParserPtarm::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  ParserPtarm::symbol_number_type
  ParserPtarm::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  ParserPtarm::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  ParserPtarm::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  ParserPtarm::stack_symbol_type&
  ParserPtarm::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  ParserPtarm::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if PTARMDEBUG
  template <typename Base>
  void
  ParserPtarm::yy_print_ (std::ostream& yyo,
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

  inline
  void
  ParserPtarm::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  ParserPtarm::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  ParserPtarm::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if PTARMDEBUG
  std::ostream&
  ParserPtarm::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ParserPtarm::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ParserPtarm::debug_level_type
  ParserPtarm::debug_level () const
  {
    return yydebug_;
  }

  void
  ParserPtarm::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PTARMDEBUG

  inline ParserPtarm::state_type
  ParserPtarm::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  ParserPtarm::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  ParserPtarm::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  ParserPtarm::parse ()
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

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
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, scanner));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
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
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 114 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Operand(*(yystack_[0].value.str), "generalRegister"); }
#line 627 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 3:
#line 115 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Operand(*(yystack_[0].value.str), "specialRegister"); }
#line 633 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 4:
#line 116 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Operand(*(yystack_[0].value.str), "coprocessorRegister"); }
#line 639 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 5:
#line 117 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Operand(*(yystack_[0].value.str), "constant"); }
#line 645 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 6:
#line 118 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Operand(*(yystack_[0].value.str), "shiftedOperand"); }
#line 651 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 7:
#line 119 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Operand(*(yystack_[1].value.node), "address1"); }
#line 657 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 8:
#line 120 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Operand(*(yystack_[3].value.node), *(yystack_[1].value.node), "address2"); }
#line 663 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 9:
#line 124 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.nodeList) = new forec::cfg::OperandList(*(yystack_[0].value.node)); }
#line 669 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 10:
#line 125 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.nodeList) = new forec::cfg::OperandList(*(yystack_[1].value.node)); }
#line 675 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 11:
#line 126 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.nodeList) = new forec::cfg::OperandList(*(yystack_[1].value.node)); }
#line 681 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 12:
#line 127 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.nodeList) = new forec::cfg::OperandList(*(yystack_[1].value.nodeList), "registerList"); }
#line 687 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 13:
#line 128 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.nodeList) = (yystack_[2].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 693 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 14:
#line 129 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.nodeList) = (yystack_[3].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[1].value.node)); }
#line 699 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 15:
#line 130 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.nodeList) = (yystack_[3].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[1].value.node)); }
#line 705 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 16:
#line 131 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.nodeList) = (yystack_[4].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[1].value.node)); }
#line 711 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 17:
#line 135 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "branchConditional"); }
#line 717 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 18:
#line 136 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "branchUnconditional"); }
#line 723 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 19:
#line 137 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "interrupt"); }
#line 729 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 20:
#line 138 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "logic"); }
#line 735 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 21:
#line 139 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "arithmeticInteger"); }
#line 741 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 22:
#line 140 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "read"); }
#line 747 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 23:
#line 141 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "store"); }
#line 753 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 24:
#line 142 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "move"); }
#line 759 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 25:
#line 143 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "coprocessor"); }
#line 765 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 26:
#line 144 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "data"); }
#line 771 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 27:
#line 148 "ParserPtarm.y" // lalr1.cc:859
    { /* Do nothing */ }
#line 777 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 28:
#line 152 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyLine(*(yystack_[4].value.str), *(yystack_[2].value.str), *(yystack_[1].value.node), *(yystack_[0].value.nodeList)); }
#line 783 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 29:
#line 153 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyLine(*(yystack_[4].value.str), *(yystack_[2].value.str), *(yystack_[1].value.node), *(new forec::cfg::OperandList(*(new forec::cfg::Operand(""))))); }
#line 789 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 30:
#line 154 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyLine(*(yystack_[5].value.str), *(yystack_[3].value.str), *(yystack_[2].value.node), *(yystack_[1].value.nodeList)); }
#line 795 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 31:
#line 155 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyLine(*(yystack_[7].value.str), *(yystack_[5].value.str), *(yystack_[4].value.node), *(yystack_[3].value.nodeList), "; " + ((forec::cfg::Operand *)(((forec::cfg::OperandList *)(yystack_[3].value.nodeList))->getOperands()[0]))->getValue(), *(yystack_[1].value.str)); }
#line 801 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 32:
#line 156 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyLine(*(yystack_[5].value.str), *(yystack_[3].value.str), *(yystack_[2].value.node), *(yystack_[1].value.nodeList), *(yystack_[0].value.str)); }
#line 807 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 33:
#line 157 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AssemblyLine(*(yystack_[8].value.str), *(yystack_[6].value.str), *(yystack_[5].value.node), *(yystack_[4].value.nodeList), *(yystack_[3].value.str), *(yystack_[1].value.str)); }
#line 813 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 34:
#line 161 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Label(*(yystack_[4].value.str), *(yystack_[2].value.str)); }
#line 819 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 35:
#line 165 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::CSourceLine(*(yystack_[0].value.str)); }
#line 825 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 36:
#line 169 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::IterationBound(*(yystack_[0].value.str)); }
#line 831 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 37:
#line 173 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 837 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 38:
#line 174 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 843 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 39:
#line 175 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 849 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 40:
#line 181 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AbortStatement(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "statement"); }
#line 855 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 41:
#line 185 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::AbortStatement(*(yystack_[0].value.str), "scopeEnd"); }
#line 861 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 42:
#line 189 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::ParStatement(*(yystack_[2].value.str), *(yystack_[1].value.nodeList)); }
#line 867 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 43:
#line 193 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::PauseStatement(*(yystack_[2].value.str), *(yystack_[1].value.nodeList)); }
#line 873 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 44:
#line 197 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 879 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 45:
#line 198 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 885 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 46:
#line 199 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 891 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 47:
#line 200 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 897 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 48:
#line 206 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "counter");}
#line 903 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 49:
#line 207 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "boot");}
#line 909 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 50:
#line 208 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "reactionStart");}
#line 915 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 51:
#line 209 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "reactionEnd");}
#line 921 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 52:
#line 210 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "parHandler");}
#line 927 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 53:
#line 211 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "abortHandler");}
#line 933 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 54:
#line 212 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "threadRemove");}
#line 939 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 55:
#line 213 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "iterationEnd");}
#line 945 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 56:
#line 219 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 951 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 57:
#line 220 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 957 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 58:
#line 221 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 963 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 59:
#line 225 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.nodeList) = new forec::cfg::Body(*(yystack_[0].value.node)); }
#line 969 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 60:
#line 226 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.nodeList) = (yystack_[1].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 975 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 61:
#line 232 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = new forec::cfg::Thread(*(yystack_[2].value.str), *(yystack_[1].value.nodeList));}
#line 981 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 62:
#line 237 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 987 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 63:
#line 238 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 993 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 64:
#line 239 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 999 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 65:
#line 240 "ParserPtarm.y" // lalr1.cc:859
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 1005 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 66:
#line 244 "ParserPtarm.y" // lalr1.cc:859
    { rootNode.append(*(yystack_[0].value.node)); }
#line 1011 "ParserPtarm.tab.c" // lalr1.cc:859
    break;

  case 67:
#line 245 "ParserPtarm.y" // lalr1.cc:859
    { rootNode.append(*(yystack_[0].value.node)); }
#line 1017 "ParserPtarm.tab.c" // lalr1.cc:859
    break;


#line 1021 "ParserPtarm.tab.c" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
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
    yyerror_range[1].location = yystack_[yylen - 1].location;
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
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  ParserPtarm::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  ParserPtarm::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const signed char ParserPtarm::yypact_ninf_ = -65;

  const signed char ParserPtarm::yytable_ninf_ = -1;

  const short int
  ParserPtarm::yypact_[] =
  {
      83,    -5,   -65,   347,   347,   347,   347,   347,   347,   347,
     347,   -65,   347,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,    35,    -1,    -8,   -21,   347,   347,   -65,   347,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   111,   131,   151,
     171,   191,   211,   233,   257,    63,   -65,   -65,   399,     1,
     283,   305,   325,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,    -3,    11,   -65,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,    17,     3,    19,   351,     8,   -65,   -65,
     355,    -6,   399,   -65,   -65,    14,     9,    58,   -65,   -65,
      17,   -65,     3,    60,    17,   367,    22,    37,   -16,    24,
      34,   -65,   -65,   -65,   -65,   -65,   -65,   -65
  };

  const unsigned char
  ParserPtarm::yydefact_[] =
  {
       0,     0,    35,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,    37,    62,    38,    39,    63,    65,    64,
      66,     0,     0,     0,     0,     0,     0,    41,     0,    56,
      45,    46,    47,    44,    57,    58,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    67,     0,     0,
       0,     0,     0,    48,    60,    49,    50,    51,    52,    53,
      54,    55,    61,    17,    18,    19,    20,    21,    25,    22,
      23,    24,    26,     0,     0,    42,    40,    43,     2,     3,
       4,     5,     6,     0,     0,     0,     9,    28,    29,    34,
       0,     0,     0,    10,    11,    32,     0,     0,    30,     7,
       0,    12,     0,     0,     0,    13,     0,     0,     0,     0,
       0,    14,    15,    31,     8,    27,    33,    16
  };

  const short int
  ParserPtarm::yypgoto_[] =
  {
     -65,   -64,   -42,     5,     6,   -65,   -65,   -65,   -65,    18,
     -65,   -65,   -65,   -65,   -65,    38,   356,    21,   -65,    74,
     -65
  };

  const signed char
  ParserPtarm::yydefgoto_[] =
  {
      -1,    86,    87,    73,    88,    13,    14,    15,    16,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    19,    20,
      21
  };

  const unsigned char
  ParserPtarm::yytable_[] =
  {
      78,    79,    80,    81,    82,    48,    78,    79,    80,    81,
      82,    49,    78,    79,    80,    81,    82,    95,    17,    90,
      78,    79,    80,    81,    82,    38,    39,    40,    41,    42,
      43,    44,   105,    45,    96,    46,   107,    22,    18,    17,
     110,   115,    91,     1,    96,    83,    50,    51,   101,    52,
      84,    83,    85,    22,    23,     2,    84,    83,    96,    18,
     108,    74,   104,    85,     3,    83,     4,    97,     5,    89,
       6,    24,     7,   103,     8,    92,     9,   106,    10,   109,
      11,    12,   113,     2,   116,    25,   114,    26,   117,    27,
      28,     1,     3,    98,     4,    47,     5,   102,     6,     0,
       7,     0,     8,     2,     9,     0,    10,     0,    11,     0,
      62,     0,     3,     0,     4,     0,     5,     0,     6,    24,
       7,     0,     8,     0,     9,     0,    10,     0,    11,    12,
       0,     2,     0,    25,     0,    26,     0,    27,    28,    24,
       3,    53,     4,     0,     5,     0,     6,     0,     7,     0,
       8,     2,     9,    25,    10,    26,    11,    27,    28,    24,
       3,     0,     4,    55,     5,     0,     6,     0,     7,     0,
       8,     2,     9,    25,    10,    26,    11,    27,    28,    24,
       3,     0,     4,     0,     5,    56,     6,     0,     7,     0,
       8,     2,     9,    25,    10,    26,    11,    27,    28,    24,
       3,     0,     4,     0,     5,     0,     6,    57,     7,     0,
       8,     2,     9,    25,    10,    26,    11,    27,    28,    24,
       3,     0,     4,     0,     5,     0,     6,     0,     7,    58,
       8,     2,     9,    25,    10,    26,    11,    27,    28,     0,
       3,    24,     4,     0,     5,     0,     6,     0,     7,     0,
       8,    59,     9,     2,    10,    25,    11,    26,     0,    27,
      28,     0,     3,     0,     4,    24,     5,     0,     6,     0,
       7,     0,     8,     0,     9,    60,    10,     2,    11,    25,
       0,    26,     0,    27,    28,     0,     3,     0,     4,     0,
       5,    24,     6,     0,     7,     0,     8,     0,     9,     0,
      10,    61,    11,     2,     0,    25,    75,    26,     0,    27,
      28,     0,     3,    24,     4,     0,     5,     0,     6,     0,
       7,     0,     8,     0,     9,     2,    10,    25,    11,    26,
      76,    27,    28,    24,     3,     0,     4,     0,     5,     0,
       6,     0,     7,     0,     8,     2,     9,    25,    10,    26,
      11,    27,    28,    77,     3,    24,     4,     0,     5,     0,
       6,     0,     7,     0,     8,     0,     9,     2,    10,    25,
      11,    26,     0,    27,    28,     0,     3,     0,     4,     0,
       5,     0,     6,     0,     7,     0,     8,     0,     9,     0,
      10,     0,    11,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    93,    94,    99,   100,    54,    54,    54,    63,
      64,    65,    66,    67,    68,    69,    70,    71,   111,   112,
      72
  };

  const signed char
  ParserPtarm::yycheck_[] =
  {
       3,     4,     5,     6,     7,     6,     3,     4,     5,     6,
       7,    19,     3,     4,     5,     6,     7,     9,     0,    83,
       3,     4,     5,     6,     7,     4,     5,     6,     7,     8,
       9,    10,    96,    12,    50,     0,   100,    58,     0,    21,
     104,    57,    84,     8,    50,    48,    25,    26,    54,    28,
      53,    48,    55,    58,    59,    20,    53,    48,    50,    21,
     102,    60,    53,    55,    29,    48,    31,    59,    33,    58,
      35,     8,    37,    59,    39,    56,    41,    19,    43,    19,
      45,    46,    60,    20,    60,    22,    49,    24,    54,    26,
      27,     8,    29,    87,    31,    21,    33,    92,    35,    -1,
      37,    -1,    39,    20,    41,    -1,    43,    -1,    45,    -1,
      47,    -1,    29,    -1,    31,    -1,    33,    -1,    35,     8,
      37,    -1,    39,    -1,    41,    -1,    43,    -1,    45,    46,
      -1,    20,    -1,    22,    -1,    24,    -1,    26,    27,     8,
      29,    30,    31,    -1,    33,    -1,    35,    -1,    37,    -1,
      39,    20,    41,    22,    43,    24,    45,    26,    27,     8,
      29,    -1,    31,    32,    33,    -1,    35,    -1,    37,    -1,
      39,    20,    41,    22,    43,    24,    45,    26,    27,     8,
      29,    -1,    31,    -1,    33,    34,    35,    -1,    37,    -1,
      39,    20,    41,    22,    43,    24,    45,    26,    27,     8,
      29,    -1,    31,    -1,    33,    -1,    35,    36,    37,    -1,
      39,    20,    41,    22,    43,    24,    45,    26,    27,     8,
      29,    -1,    31,    -1,    33,    -1,    35,    -1,    37,    38,
      39,    20,    41,    22,    43,    24,    45,    26,    27,    -1,
      29,     8,    31,    -1,    33,    -1,    35,    -1,    37,    -1,
      39,    40,    41,    20,    43,    22,    45,    24,    -1,    26,
      27,    -1,    29,    -1,    31,     8,    33,    -1,    35,    -1,
      37,    -1,    39,    -1,    41,    42,    43,    20,    45,    22,
      -1,    24,    -1,    26,    27,    -1,    29,    -1,    31,    -1,
      33,     8,    35,    -1,    37,    -1,    39,    -1,    41,    -1,
      43,    44,    45,    20,    -1,    22,    23,    24,    -1,    26,
      27,    -1,    29,     8,    31,    -1,    33,    -1,    35,    -1,
      37,    -1,    39,    -1,    41,    20,    43,    22,    45,    24,
      25,    26,    27,     8,    29,    -1,    31,    -1,    33,    -1,
      35,    -1,    37,    -1,    39,    20,    41,    22,    43,    24,
      45,    26,    27,    28,    29,     8,    31,    -1,    33,    -1,
      35,    -1,    37,    -1,    39,    -1,    41,    20,    43,    22,
      45,    24,    -1,    26,    27,    -1,    29,    -1,    31,    -1,
      33,    -1,    35,    -1,    37,    -1,    39,    -1,    41,    -1,
      43,    -1,    45,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    51,    52,    49,    50,    50,    51,    52,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    51,    52,
      21
  };

  const unsigned char
  ParserPtarm::yystos_[] =
  {
       0,     8,    20,    29,    31,    33,    35,    37,    39,    41,
      43,    45,    46,    66,    67,    68,    69,    70,    76,    79,
      80,    81,    58,    59,     8,    22,    24,    26,    27,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    78,    78,
      78,    78,    78,    78,    78,    78,     0,    80,     6,    19,
      78,    78,    78,    30,    77,    32,    34,    36,    38,    40,
      42,    44,    47,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    21,    64,    60,    23,    25,    28,     3,     4,
       5,     6,     7,    48,    53,    55,    62,    63,    65,    58,
      62,    63,    56,    51,    52,     9,    50,    59,    65,    49,
      50,    54,    64,    59,    53,    62,    19,    62,    63,    19,
      62,    51,    52,    60,    49,    57,    60,    54
  };

  const unsigned char
  ParserPtarm::yyr1_[] =
  {
       0,    61,    62,    62,    62,    62,    62,    62,    62,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    65,    66,    66,
      66,    66,    66,    66,    67,    68,    69,    70,    70,    70,
      71,    72,    73,    74,    75,    75,    75,    75,    76,    76,
      76,    76,    76,    76,    76,    76,    77,    77,    77,    78,
      78,    79,    80,    80,    80,    80,    81,    81
  };

  const unsigned char
  ParserPtarm::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     1,     3,     5,     1,
       2,     2,     3,     3,     4,     4,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     5,     5,     5,
       6,     8,     6,     9,     5,     1,     1,     1,     1,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       2,     3,     1,     1,     1,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const ParserPtarm::yytname_[] =
  {
  "$end", "error", "$undefined", "REGISTERS_GENERAL", "REGISTERS_SPECIAL",
  "COPROCESSOR_REGISTERS", "CONSTANT", "SHIFTED_OPERAND", "PC", "PC_1",
  "BRANCH_CONDITIONAL", "BRANCH_UNCONDITIONAL", "INTERRUPT", "LOGIC",
  "ARITHMETIC_INTEGER", "COPROCESSOR", "READ", "STORE", "MOVE", "LABEL",
  "C_SOURCE", "DATA", "FOREC_STATEMENT_PAR_START",
  "FOREC_STATEMENT_PAR_END", "FOREC_STATEMENT_ABORT_START",
  "FOREC_STATEMENT_ABORT_END", "FOREC_STATEMENT_ABORT_SCOPE_END",
  "FOREC_STATEMENT_PAUSE_START", "FOREC_STATEMENT_PAUSE_END",
  "FOREC_SCHEDULER_COUNTER_START", "FOREC_SCHEDULER_COUNTER_END",
  "FOREC_SCHEDULER_BOOT_START", "FOREC_SCHEDULER_BOOT_END",
  "FOREC_SCHEDULER_REACTION_START_START",
  "FOREC_SCHEDULER_REACTION_START_END",
  "FOREC_SCHEDULER_REACTION_END_START", "FOREC_SCHEDULER_REACTION_END_END",
  "FOREC_SCHEDULER_PAR_HANDLER_START", "FOREC_SCHEDULER_PAR_HANDLER_END",
  "FOREC_SCHEDULER_ABORT_HANDLER_START",
  "FOREC_SCHEDULER_ABORT_HANDLER_END",
  "FOREC_SCHEDULER_THREAD_REMOVE_START",
  "FOREC_SCHEDULER_THREAD_REMOVE_END",
  "FOREC_SCHEDULER_ITERATION_END_START",
  "FOREC_SCHEDULER_ITERATION_END_END", "FOREC_ITERATION_BOUND",
  "FOREC_THREAD_START", "FOREC_THREAD_END", "'['", "']'", "','", "'!'",
  "'^'", "'{'", "'}'", "';'", "'('", "')'", "':'", "'<'", "'>'", "$accept",
  "operand", "operand_list", "assembly_instruction", "alt_assembly_line",
  "assembly_line", "label", "c_source_line", "iteration_bound",
  "mixed_source", "abort_statement", "abort_scope_end", "par_statement",
  "pause_statement", "forec_statement", "forec_scheduler", "body_item",
  "body", "thread", "fragment", "translation_unit", YY_NULLPTR
  };

#if PTARMDEBUG
  const unsigned char
  ParserPtarm::yyrline_[] =
  {
       0,   114,   114,   115,   116,   117,   118,   119,   120,   124,
     125,   126,   127,   128,   129,   130,   131,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   148,   152,   153,
     154,   155,   156,   157,   161,   165,   169,   173,   174,   175,
     181,   185,   189,   193,   197,   198,   199,   200,   206,   207,
     208,   209,   210,   211,   212,   213,   219,   220,   221,   225,
     226,   232,   237,   238,   239,   240,   244,   245
  };

  // Print the state stack on the debug stream.
  void
  ParserPtarm::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  ParserPtarm::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // PTARMDEBUG

  // Symbol number corresponding to token number t.
  inline
  ParserPtarm::token_number_type
  ParserPtarm::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    51,     2,     2,     2,     2,     2,     2,
      56,    57,     2,     2,    50,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    58,    55,
      59,     2,    60,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    48,     2,    49,    52,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    53,     2,    54,     2,     2,     2,     2,
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
      45,    46,    47
    };
    const unsigned int user_token_number_max_ = 302;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 13 "ParserPtarm.y" // lalr1.cc:1167
} } // forec::loader
#line 1599 "ParserPtarm.tab.c" // lalr1.cc:1167
#line 248 "ParserPtarm.y" // lalr1.cc:1168



// Now that we have the Parser declared, we can declare the Scanner and implement
// the yylex function
#include "ScannerPtarm.hpp"
static int yylex(forec::loader::ParserPtarm::semantic_type * yylval, forec::loader::ParserPtarm::location_type * yylloc, forec::loader::ScannerPtarm &scanner) {
	return scanner.yylex(yylval);
}

