// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

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
#define yylex   microBlazelex

// First part of user declarations.

#line 39 "ParserMicroBlaze.tab.c" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "ParserMicroBlaze.tab.h"

// User implementation prologue.

#line 53 "ParserMicroBlaze.tab.c" // lalr1.cc:407
// Unqualified %code blocks.
#line 55 "ParserMicroBlaze.y" // lalr1.cc:408

	// Prototype for the yylex function
	static int yylex(forec::loader::ParserMicroBlaze::semantic_type * yylval, forec::loader::ParserMicroBlaze::location_type * yylloc, forec::loader::ScannerMicroBlaze &scanner);

#line 60 "ParserMicroBlaze.tab.c" // lalr1.cc:408


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
#if MICROBLAZEDEBUG

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

#else // !MICROBLAZEDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !MICROBLAZEDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 13 "ParserMicroBlaze.y" // lalr1.cc:474
namespace forec { namespace loader {
#line 146 "ParserMicroBlaze.tab.c" // lalr1.cc:474

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  ParserMicroBlaze::yytnamerr_ (const char *yystr)
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
  ParserMicroBlaze::ParserMicroBlaze (forec::loader::ScannerMicroBlaze &scanner_yyarg, forec::cfg::Node &rootNode_yyarg)
    :
#if MICROBLAZEDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      rootNode (rootNode_yyarg)
  {}

  ParserMicroBlaze::~ParserMicroBlaze ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  ParserMicroBlaze::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  ParserMicroBlaze::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  ParserMicroBlaze::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  ParserMicroBlaze::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  ParserMicroBlaze::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  ParserMicroBlaze::basic_symbol<Base>::~basic_symbol ()
  {
  }

  template <typename Base>
  inline
  void
  ParserMicroBlaze::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  ParserMicroBlaze::by_type::by_type ()
     : type (empty)
  {}

  inline
  ParserMicroBlaze::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  ParserMicroBlaze::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  ParserMicroBlaze::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
  ParserMicroBlaze::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  ParserMicroBlaze::by_state::by_state ()
    : state (empty)
  {}

  inline
  ParserMicroBlaze::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  ParserMicroBlaze::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
  ParserMicroBlaze::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  ParserMicroBlaze::symbol_number_type
  ParserMicroBlaze::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
  ParserMicroBlaze::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  ParserMicroBlaze::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty;
  }

  inline
  ParserMicroBlaze::stack_symbol_type&
  ParserMicroBlaze::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  ParserMicroBlaze::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if MICROBLAZEDEBUG
  template <typename Base>
  void
  ParserMicroBlaze::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  ParserMicroBlaze::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  ParserMicroBlaze::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  ParserMicroBlaze::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if MICROBLAZEDEBUG
  std::ostream&
  ParserMicroBlaze::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  ParserMicroBlaze::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  ParserMicroBlaze::debug_level_type
  ParserMicroBlaze::debug_level () const
  {
    return yydebug_;
  }

  void
  ParserMicroBlaze::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // MICROBLAZEDEBUG

  inline ParserMicroBlaze::state_type
  ParserMicroBlaze::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  ParserMicroBlaze::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  ParserMicroBlaze::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  ParserMicroBlaze::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

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
    if (yyempty)
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
        yyempty = false;
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

    // Discard the token being shifted.
    yyempty = true;

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
#line 113 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Operand(*(yystack_[0].value.str), "generalRegister"); }
#line 596 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 3:
#line 114 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Operand(*(yystack_[0].value.str), "specialRegister"); }
#line 602 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 4:
#line 115 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Operand(*(yystack_[0].value.str), "constant"); }
#line 608 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 5:
#line 119 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.nodeList) = new forec::cfg::OperandList(*(yystack_[0].value.node)); }
#line 614 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 6:
#line 120 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.nodeList) = (yystack_[2].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 620 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 7:
#line 124 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "branchConditional"); }
#line 626 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 8:
#line 125 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "branchConditionalWithDelay"); }
#line 632 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 9:
#line 126 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "branchUnconditional"); }
#line 638 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 10:
#line 127 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "branchUnconditionalWithDelay"); }
#line 644 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 11:
#line 128 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "break"); }
#line 650 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 12:
#line 129 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "return"); }
#line 656 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 13:
#line 130 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "logic"); }
#line 662 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 14:
#line 131 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "arithmeticInteger"); }
#line 668 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 15:
#line 132 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "arithmeticFloat"); }
#line 674 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 16:
#line 133 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "read"); }
#line 680 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 17:
#line 134 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "store"); }
#line 686 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 18:
#line 135 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "move"); }
#line 692 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 19:
#line 136 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyInstruction(*(yystack_[0].value.str), "memory"); }
#line 698 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 20:
#line 140 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyLine(*(yystack_[4].value.str), *(yystack_[2].value.str), *(yystack_[1].value.node), *(yystack_[0].value.nodeList)); }
#line 704 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 21:
#line 141 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyLine(*(yystack_[5].value.str), *(yystack_[3].value.str), *(yystack_[2].value.node), *(yystack_[1].value.nodeList), *(yystack_[0].value.str)); }
#line 710 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 22:
#line 142 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AssemblyLine(*(yystack_[8].value.str), *(yystack_[6].value.str), *(yystack_[5].value.node), *(yystack_[4].value.nodeList), *(yystack_[3].value.str), *(yystack_[1].value.str)); }
#line 716 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 23:
#line 146 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Label(*(yystack_[4].value.str), *(yystack_[2].value.str)); }
#line 722 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 24:
#line 150 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::CSourceLine(*(yystack_[0].value.str)); }
#line 728 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 25:
#line 151 "ParserMicroBlaze.y" // lalr1.cc:847
    { if ((yystack_[1].value.str)->compare("80000001") != 0) {	/* Special MicroBlaze instruction to terminate the simulation. */
											unsigned int pcValue;
											std::istringstream pc(*(yystack_[3].value.str));
											pc >> std::hex >> pcValue;
											std::ostringstream error;
											error << "Parser Error at program counter 0x" << std::hex << pcValue << ": Missing asm instruction" << std::endl;
											throw error.str();
										  }; (yylhs.value.node) = new forec::cfg::CSourceLine("80000001 r0, r0, r0"); 
										}
#line 742 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 26:
#line 163 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::IterationBound(*(yystack_[0].value.str)); }
#line 748 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 27:
#line 167 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 754 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 28:
#line 168 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 760 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 29:
#line 169 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 766 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 30:
#line 175 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AbortStatement(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "statement"); }
#line 772 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 31:
#line 179 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::AbortStatement(*(yystack_[0].value.str), "scopeEnd"); }
#line 778 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 32:
#line 183 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::ParStatement(*(yystack_[2].value.str), *(yystack_[1].value.nodeList)); }
#line 784 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 33:
#line 187 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::PauseStatement(*(yystack_[2].value.str), *(yystack_[1].value.nodeList)); }
#line 790 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 34:
#line 191 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 796 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 35:
#line 192 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 802 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 36:
#line 193 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 808 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 37:
#line 194 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 814 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 38:
#line 200 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "counter");}
#line 820 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 39:
#line 201 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "boot");}
#line 826 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 40:
#line 202 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "reactionStart");}
#line 832 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 41:
#line 203 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "reactionEnd");}
#line 838 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 42:
#line 204 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "parHandler");}
#line 844 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 43:
#line 205 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "abortHandler");}
#line 850 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 44:
#line 206 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "threadRemove");}
#line 856 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 45:
#line 207 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Scheduler(*(yystack_[2].value.str), *(yystack_[1].value.nodeList), "iterationEnd");}
#line 862 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 46:
#line 213 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 868 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 47:
#line 214 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 874 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 48:
#line 215 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 880 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 49:
#line 219 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.nodeList) = new forec::cfg::Body(*(yystack_[0].value.node)); }
#line 886 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 50:
#line 220 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.nodeList) = (yystack_[1].value.nodeList); (yylhs.value.nodeList)->append(*(yystack_[0].value.node)); }
#line 892 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 51:
#line 226 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = new forec::cfg::Thread(*(yystack_[2].value.str), *(yystack_[1].value.nodeList));}
#line 898 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 52:
#line 231 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 904 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 53:
#line 232 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 910 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 54:
#line 233 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 916 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 55:
#line 234 "ParserMicroBlaze.y" // lalr1.cc:847
    { (yylhs.value.node) = (yystack_[0].value.node); }
#line 922 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 56:
#line 238 "ParserMicroBlaze.y" // lalr1.cc:847
    { rootNode.append(*(yystack_[0].value.node)); }
#line 928 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;

  case 57:
#line 239 "ParserMicroBlaze.y" // lalr1.cc:847
    { rootNode.append(*(yystack_[0].value.node)); }
#line 934 "ParserMicroBlaze.tab.c" // lalr1.cc:847
    break;


#line 938 "ParserMicroBlaze.tab.c" // lalr1.cc:847
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
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
    if (!yyempty)
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
        if (!yyempty)
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
  ParserMicroBlaze::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  ParserMicroBlaze::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
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
       - The only way there can be no lookahead present (in yytoken) is
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
    if (yytoken != yyempty_)
      {
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


  const signed char ParserMicroBlaze::yypact_ninf_ = -48;

  const signed char ParserMicroBlaze::yytable_ninf_ = -1;

  const short int
  ParserMicroBlaze::yypact_[] =
  {
      42,   -31,   -48,   348,   348,   348,   348,   348,   348,   348,
     348,   -48,   348,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,     0,    -2,   -16,   -36,   348,   348,   -48,   348,   -48,
     -48,   -48,   -48,   -48,   -48,   -48,   -48,    71,    98,   123,
     148,   173,   198,   223,   248,    27,   -48,   -48,   392,   -28,
     273,   298,   323,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,   -48,
     -23,    13,   -29,   -48,   -48,   -48,    13,    -6,   -48,   -48,
     -24,    14,   -15,   -48
  };

  const unsigned char
  ParserMicroBlaze::yydefact_[] =
  {
       0,     0,    24,     0,     0,     0,     0,     0,     0,     0,
       0,    26,     0,    27,    52,    28,    29,    53,    55,    54,
      56,     0,     0,     0,     0,     0,     0,    31,     0,    46,
      35,    36,    37,    34,    47,    48,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,    57,     0,     0,
       0,     0,     0,    38,    50,    39,    40,    41,    42,    43,
      44,    45,    51,     2,     3,     4,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,     5,
      25,     0,     0,    32,    30,    33,     0,    20,    23,     6,
      21,     0,     0,    22
  };

  const short int
  ParserMicroBlaze::yypgoto_[] =
  {
     -48,   -47,   -40,   -48,   -48,   -48,   -48,   -48,     2,   -48,
     -48,   -48,   -48,   -48,     4,   376,     3,   -48,    24,   -48
  };

  const signed char
  ParserMicroBlaze::yydefgoto_[] =
  {
      -1,    79,    80,    81,    13,    14,    15,    16,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    19,    20,    21
  };

  const unsigned char
  ParserMicroBlaze::yytable_[] =
  {
      46,    90,    17,    48,    18,    49,     1,    38,    39,    40,
      41,    42,    43,    44,    22,    45,    63,    64,    65,    22,
      23,    88,     2,    17,    82,    18,    86,    91,    50,    51,
       3,    52,     4,    24,     5,    92,     6,    93,     7,    89,
       8,    87,     9,    86,    10,    47,    11,    12,     1,     2,
      25,     0,    26,     0,    27,    28,     0,     3,     0,     4,
       0,     5,     0,     6,     2,     7,     0,     8,     0,     9,
       0,    10,     3,    11,     4,    62,     5,    24,     6,     0,
       7,     0,     8,     0,     9,     0,    10,     0,    11,    12,
       0,     0,     0,     2,    25,     0,    26,     0,    27,    28,
       0,     3,    53,     4,    24,     5,     0,     6,     0,     7,
       0,     8,     0,     9,     0,    10,     0,    11,     0,     0,
       2,    25,     0,    26,     0,    27,    28,     0,     3,    24,
       4,    55,     5,     0,     6,     0,     7,     0,     8,     0,
       9,     0,    10,     0,    11,     2,    25,     0,    26,     0,
      27,    28,     0,     3,    24,     4,     0,     5,    56,     6,
       0,     7,     0,     8,     0,     9,     0,    10,     0,    11,
       2,    25,     0,    26,     0,    27,    28,     0,     3,    24,
       4,     0,     5,     0,     6,    57,     7,     0,     8,     0,
       9,     0,    10,     0,    11,     2,    25,     0,    26,     0,
      27,    28,     0,     3,    24,     4,     0,     5,     0,     6,
       0,     7,    58,     8,     0,     9,     0,    10,     0,    11,
       2,    25,     0,    26,     0,    27,    28,     0,     3,    24,
       4,     0,     5,     0,     6,     0,     7,     0,     8,    59,
       9,     0,    10,     0,    11,     2,    25,     0,    26,     0,
      27,    28,     0,     3,    24,     4,     0,     5,     0,     6,
       0,     7,     0,     8,     0,     9,    60,    10,     0,    11,
       2,    25,     0,    26,     0,    27,    28,     0,     3,    24,
       4,     0,     5,     0,     6,     0,     7,     0,     8,     0,
       9,     0,    10,    61,    11,     2,    25,    83,    26,     0,
      27,    28,     0,     3,    24,     4,     0,     5,     0,     6,
       0,     7,     0,     8,     0,     9,     0,    10,     0,    11,
       2,    25,     0,    26,    84,    27,    28,     0,     3,    24,
       4,     0,     5,     0,     6,     0,     7,     0,     8,     0,
       9,     0,    10,     0,    11,     2,    25,     0,    26,     0,
      27,    28,    85,     3,    24,     4,     0,     5,     0,     6,
       0,     7,     0,     8,     0,     9,     0,    10,     0,    11,
       2,    25,     0,    26,     0,    27,    28,     0,     3,     0,
       4,     0,     5,     0,     6,     0,     7,     0,     8,     0,
       9,     0,    10,     0,    11,    63,    64,    65,     0,     0,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    54,    54,    54,    54,    54,    54,    54,
      54,    54,     0,     0,     0,     0,    54,    54,    54
  };

  const signed char
  ParserMicroBlaze::yycheck_[] =
  {
       0,     7,     0,     5,     0,    21,     6,     4,     5,     6,
       7,     8,     9,    10,    50,    12,     3,     4,     5,    50,
      51,    50,    22,    21,    52,    21,    49,    51,    25,    26,
      30,    28,    32,     6,    34,    21,    36,    52,    38,    86,
      40,    81,    42,    49,    44,    21,    46,    47,     6,    22,
      23,    -1,    25,    -1,    27,    28,    -1,    30,    -1,    32,
      -1,    34,    -1,    36,    22,    38,    -1,    40,    -1,    42,
      -1,    44,    30,    46,    32,    48,    34,     6,    36,    -1,
      38,    -1,    40,    -1,    42,    -1,    44,    -1,    46,    47,
      -1,    -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,
      -1,    30,    31,    32,     6,    34,    -1,    36,    -1,    38,
      -1,    40,    -1,    42,    -1,    44,    -1,    46,    -1,    -1,
      22,    23,    -1,    25,    -1,    27,    28,    -1,    30,     6,
      32,    33,    34,    -1,    36,    -1,    38,    -1,    40,    -1,
      42,    -1,    44,    -1,    46,    22,    23,    -1,    25,    -1,
      27,    28,    -1,    30,     6,    32,    -1,    34,    35,    36,
      -1,    38,    -1,    40,    -1,    42,    -1,    44,    -1,    46,
      22,    23,    -1,    25,    -1,    27,    28,    -1,    30,     6,
      32,    -1,    34,    -1,    36,    37,    38,    -1,    40,    -1,
      42,    -1,    44,    -1,    46,    22,    23,    -1,    25,    -1,
      27,    28,    -1,    30,     6,    32,    -1,    34,    -1,    36,
      -1,    38,    39,    40,    -1,    42,    -1,    44,    -1,    46,
      22,    23,    -1,    25,    -1,    27,    28,    -1,    30,     6,
      32,    -1,    34,    -1,    36,    -1,    38,    -1,    40,    41,
      42,    -1,    44,    -1,    46,    22,    23,    -1,    25,    -1,
      27,    28,    -1,    30,     6,    32,    -1,    34,    -1,    36,
      -1,    38,    -1,    40,    -1,    42,    43,    44,    -1,    46,
      22,    23,    -1,    25,    -1,    27,    28,    -1,    30,     6,
      32,    -1,    34,    -1,    36,    -1,    38,    -1,    40,    -1,
      42,    -1,    44,    45,    46,    22,    23,    24,    25,    -1,
      27,    28,    -1,    30,     6,    32,    -1,    34,    -1,    36,
      -1,    38,    -1,    40,    -1,    42,    -1,    44,    -1,    46,
      22,    23,    -1,    25,    26,    27,    28,    -1,    30,     6,
      32,    -1,    34,    -1,    36,    -1,    38,    -1,    40,    -1,
      42,    -1,    44,    -1,    46,    22,    23,    -1,    25,    -1,
      27,    28,    29,    30,     6,    32,    -1,    34,    -1,    36,
      -1,    38,    -1,    40,    -1,    42,    -1,    44,    -1,    46,
      22,    23,    -1,    25,    -1,    27,    28,    -1,    30,    -1,
      32,    -1,    34,    -1,    36,    -1,    38,    -1,    40,    -1,
      42,    -1,    44,    -1,    46,     3,     4,     5,    -1,    -1,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    50,    51,    52
  };

  const unsigned char
  ParserMicroBlaze::yystos_[] =
  {
       0,     6,    22,    30,    32,    34,    36,    38,    40,    42,
      44,    46,    47,    57,    58,    59,    60,    61,    67,    70,
      71,    72,    50,    51,     6,    23,    25,    27,    28,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    69,    69,
      69,    69,    69,    69,    69,    69,     0,    71,     5,    21,
      69,    69,    69,    31,    68,    33,    35,    37,    39,    41,
      43,    45,    48,     3,     4,     5,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    54,
      55,    56,    52,    24,    26,    29,    49,    55,    50,    54,
       7,    51,    21,    52
  };

  const unsigned char
  ParserMicroBlaze::yyr1_[] =
  {
       0,    53,    54,    54,    54,    55,    55,    56,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    57,    57,    58,    59,    59,    60,    61,    61,    61,
      62,    63,    64,    65,    66,    66,    66,    66,    67,    67,
      67,    67,    67,    67,    67,    67,    68,    68,    68,    69,
      69,    70,    71,    71,    71,    71,    72,    72
  };

  const unsigned char
  ParserMicroBlaze::yyr2_[] =
  {
       0,     2,     1,     1,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     6,     9,     5,     1,     4,     1,     1,     1,     1,
       3,     1,     3,     3,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     1,     1,
       2,     3,     1,     1,     1,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const ParserMicroBlaze::yytname_[] =
  {
  "$end", "error", "$undefined", "REGISTERS_GENERAL", "REGISTERS_SPECIAL",
  "CONSTANT", "PC", "PC_1", "BRANCH_CONDITIONAL",
  "BRANCH_CONDITIONAL_WITH_DELAY", "BRANCH_UNCONDITIONAL",
  "BRANCH_UNCONDITIONAL_WITH_DELAY", "BREAK", "RETURN", "LOGIC",
  "ARITHMETIC_INTEGER", "ARITHMETIC_FLOAT", "READ", "STORE", "MOVE",
  "MEMORY", "LABEL", "C_SOURCE", "FOREC_STATEMENT_PAR_START",
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
  "FOREC_THREAD_START", "FOREC_THREAD_END", "','", "':'", "'<'", "'>'",
  "$accept", "operand", "operand_list", "assembly_instruction",
  "assembly_line", "label", "c_source_line", "iteration_bound",
  "mixed_source", "abort_statement", "abort_scope_end", "par_statement",
  "pause_statement", "forec_statement", "forec_scheduler", "body_item",
  "body", "thread", "fragment", "translation_unit", YY_NULLPTR
  };

#if MICROBLAZEDEBUG
  const unsigned char
  ParserMicroBlaze::yyrline_[] =
  {
       0,   113,   113,   114,   115,   119,   120,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     140,   141,   142,   146,   150,   151,   163,   167,   168,   169,
     175,   179,   183,   187,   191,   192,   193,   194,   200,   201,
     202,   203,   204,   205,   206,   207,   213,   214,   215,   219,
     220,   226,   231,   232,   233,   234,   238,   239
  };

  // Print the state stack on the debug stream.
  void
  ParserMicroBlaze::yystack_print_ ()
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
  ParserMicroBlaze::yy_reduce_print_ (int yyrule)
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
#endif // MICROBLAZEDEBUG

  // Symbol number corresponding to token number t.
  inline
  ParserMicroBlaze::token_number_type
  ParserMicroBlaze::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    49,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    50,     2,
      51,     2,    52,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48
    };
    const unsigned int user_token_number_max_ = 303;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

#line 13 "ParserMicroBlaze.y" // lalr1.cc:1155
} } // forec::loader
#line 1505 "ParserMicroBlaze.tab.c" // lalr1.cc:1155
#line 242 "ParserMicroBlaze.y" // lalr1.cc:1156



// Now that we have the Parser declared, we can declare the Scanner and implement
// the yylex function
#include "ScannerMicroBlaze.hpp"
static int yylex(forec::loader::ParserMicroBlaze::semantic_type * yylval, forec::loader::ParserMicroBlaze::location_type * yylloc, forec::loader::ScannerMicroBlaze &scanner) {
	return scanner.yylex(yylval);
}

