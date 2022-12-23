// $ANTLR 3.1.2 C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g 2014-09-02 19:10:01

import java.util.Set;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.ArrayList;


import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;

import org.antlr.runtime.tree.*;

/** ANSI C ANTLR v3 grammar
  
Translated from Jutta Degener's 1995 ANSI C yacc grammar by Terence Parr
July 2006.  The lexical rules were taken from the Java grammar.

Jutta says: "In 1985, Jeff Lee published his Yacc grammar (which
is accompanied by a matching Lex specification) for the April 30, 1985 draft
version of the ANSI C standard.  Tom Stockfisch reposted it to net.sources in
1987; that original, as mentioned in the answer to question 17.25 of the
comp.lang.c FAQ, can be ftp'ed from ftp.uu.net,
   file usenet/net.sources/ansi.c.grammar.Z.
I intend to keep this version as close to the current C Standard grammar as
possible; please let me know if you discover discrepancies. Jutta Degener, 1995"

Generally speaking, you need symbol table info to parse C; typedefs
define types and then IDENTIFIERS are either types or plain IDs.  I'm doing
the min necessary here tracking only type names.  This is a good example 
of the global scope (called Symbols).  Every rule that declares its usage
of Symbols pushes a new copy on the stack effectively creating a new
symbol scope.  Also note rule declaration declares a rule scope that
lets any invoked rule see isTypedef boolean.  It's much easier than
passing that info down as parameters.  Very clean.  Rule
direct_declarator can then easily determine whether the IDENTIFIER
should be declared as a type name.

I have only tested this on a single file, though it is 3500 lines.

This grammar requires ANTLR v3.0.1 or higher.

Terence Parr
July 2006
*/
public class PretCParser extends Parser {
    public static final String[] tokenNames = new String[] {
        "<invalid>", "<EOR>", "<DOWN>", "<UP>", "ID_TOK", "SOURCE_TOK", "FUNCTION_TOK", "GLOBAL_DECLARATION_TOK", "DECLARATION_TOK", "TYPE_DECLARATION_TOK", "LABELED_STATMENT_TOK", "EXPRESSION_STATMENT_TOK", "SELECTION_STATMENT_TOK", "ITERATION_STATEMENT_TOK", "JUMP_STATMENT_TOK", "SCOPE_TOK", "EMPTY_TOK", "END_TOK", "ABORT_TOK", "PREPROC_TOK", "PRET_DEF_TOK", "IDENTIFIER", "DECIMAL_LITERAL", "LINE_COMMAND", "HEX_LITERAL", "OCTAL_LITERAL", "CHARACTER_LITERAL", "STRING_LITERAL", "FLOATING_POINT_LITERAL", "LETTER", "EscapeSequence", "HexDigit", "IntegerTypeSuffix", "Exponent", "FloatTypeSuffix", "OctalEscape", "UnicodeEscape", "WS", "COMMENT", "LINE_COMMENT", "'PRETDEF'", "';'", "'ReactiveInput'", "'ReactiveOutput'", "'='", "','", "'#range'", "'to'", "'thread'", "'('", "'void'", "')'", "'typedef'", "'extern'", "'static'", "'auto'", "'register'", "'unsigned'", "'signed'", "'char'", "'short'", "'int'", "'long'", "'float'", "'double'", "'{'", "'}'", "'struct'", "'union'", "':'", "'enum'", "'const'", "'volatile'", "'['", "']'", "'*'", "'...'", "'+'", "'-'", "'/'", "'%'", "'++'", "'--'", "'sizeof'", "'.'", "'->'", "'&'", "'~'", "'!'", "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", "'>>='", "'&='", "'^='", "'|='", "'?'", "'||'", "'&&'", "'|'", "'^'", "'=='", "'!='", "'<'", "'>'", "'<='", "'>='", "'<<'", "'>>'", "'EOT'", "'case'", "'default'", "'sabort'", "'when'", "'abort'", "'wabort'", "'PAR'", "'if'", "'else'", "'switch'", "'while'", "'do'", "'for'", "'goto'", "'continue'", "'break'", "'return'"
    };
    public static final int ITERATION_STATEMENT_TOK=13;
    public static final int FloatTypeSuffix=34;
    public static final int PRET_DEF_TOK=20;
    public static final int LETTER=29;
    public static final int EMPTY_TOK=16;
    public static final int EOF=-1;
    public static final int T__93=93;
    public static final int T__94=94;
    public static final int T__91=91;
    public static final int PREPROC_TOK=19;
    public static final int T__92=92;
    public static final int STRING_LITERAL=27;
    public static final int EXPRESSION_STATMENT_TOK=11;
    public static final int T__90=90;
    public static final int FLOATING_POINT_LITERAL=28;
    public static final int COMMENT=38;
    public static final int T__99=99;
    public static final int T__98=98;
    public static final int T__97=97;
    public static final int T__96=96;
    public static final int T__95=95;
    public static final int T__80=80;
    public static final int T__81=81;
    public static final int T__82=82;
    public static final int T__83=83;
    public static final int LINE_COMMENT=39;
    public static final int IntegerTypeSuffix=32;
    public static final int SOURCE_TOK=5;
    public static final int CHARACTER_LITERAL=26;
    public static final int JUMP_STATMENT_TOK=14;
    public static final int T__85=85;
    public static final int T__84=84;
    public static final int T__87=87;
    public static final int T__86=86;
    public static final int T__89=89;
    public static final int T__88=88;
    public static final int ID_TOK=4;
    public static final int T__126=126;
    public static final int T__125=125;
    public static final int T__128=128;
    public static final int T__127=127;
    public static final int WS=37;
    public static final int T__71=71;
    public static final int T__129=129;
    public static final int T__72=72;
    public static final int T__70=70;
    public static final int TYPE_DECLARATION_TOK=9;
    public static final int LINE_COMMAND=23;
    public static final int END_TOK=17;
    public static final int T__76=76;
    public static final int T__75=75;
    public static final int SCOPE_TOK=15;
    public static final int T__74=74;
    public static final int EscapeSequence=30;
    public static final int DECIMAL_LITERAL=22;
    public static final int T__73=73;
    public static final int T__79=79;
    public static final int T__78=78;
    public static final int T__77=77;
    public static final int T__68=68;
    public static final int T__69=69;
    public static final int T__66=66;
    public static final int T__67=67;
    public static final int T__64=64;
    public static final int T__65=65;
    public static final int T__62=62;
    public static final int T__63=63;
    public static final int T__118=118;
    public static final int T__119=119;
    public static final int T__116=116;
    public static final int T__117=117;
    public static final int T__114=114;
    public static final int T__115=115;
    public static final int T__124=124;
    public static final int T__123=123;
    public static final int Exponent=33;
    public static final int T__122=122;
    public static final int FUNCTION_TOK=6;
    public static final int T__121=121;
    public static final int T__120=120;
    public static final int T__61=61;
    public static final int T__60=60;
    public static final int HexDigit=31;
    public static final int T__55=55;
    public static final int T__56=56;
    public static final int T__57=57;
    public static final int T__58=58;
    public static final int T__51=51;
    public static final int T__52=52;
    public static final int T__53=53;
    public static final int T__54=54;
    public static final int T__107=107;
    public static final int T__108=108;
    public static final int T__109=109;
    public static final int IDENTIFIER=21;
    public static final int T__59=59;
    public static final int T__103=103;
    public static final int T__104=104;
    public static final int T__105=105;
    public static final int T__106=106;
    public static final int T__111=111;
    public static final int T__110=110;
    public static final int ABORT_TOK=18;
    public static final int T__113=113;
    public static final int T__112=112;
    public static final int HEX_LITERAL=24;
    public static final int T__50=50;
    public static final int T__42=42;
    public static final int T__43=43;
    public static final int T__40=40;
    public static final int T__41=41;
    public static final int T__46=46;
    public static final int T__47=47;
    public static final int T__44=44;
    public static final int T__45=45;
    public static final int T__48=48;
    public static final int T__49=49;
    public static final int DECLARATION_TOK=8;
    public static final int OCTAL_LITERAL=25;
    public static final int LABELED_STATMENT_TOK=10;
    public static final int T__102=102;
    public static final int T__101=101;
    public static final int T__100=100;
    public static final int SELECTION_STATMENT_TOK=12;
    public static final int GLOBAL_DECLARATION_TOK=7;
    public static final int UnicodeEscape=36;
    public static final int OctalEscape=35;

    // delegates
    // delegators

    protected static class is_scope {
        boolean typeDef;
        boolean declaration;
    }
    protected Stack is_stack = new Stack();
    protected static class Symbols_scope {
        Set types;
        // only track types in order to get parser working;
    }
    protected Stack Symbols_stack = new Stack();
    protected static class nodes_scope {
        StatementNode node;
    }
    protected Stack nodes_stack = new Stack();
    protected static class scopeNodes_scope {
        ScopeNode node;
    }
    protected Stack scopeNodes_stack = new Stack();
    protected static class isFromFunction_scope {
        boolean data;
    }
    protected Stack isFromFunction_stack = new Stack();


        public PretCParser(TokenStream input) {
            this(input, new RecognizerSharedState());
        }
        public PretCParser(TokenStream input, RecognizerSharedState state) {
            super(input, state);
            this.state.ruleMemo = new HashMap[263+1];
             
             
        }
        
    protected TreeAdaptor adaptor = new CommonTreeAdaptor();

    public void setTreeAdaptor(TreeAdaptor adaptor) {
        this.adaptor = adaptor;
    }
    public TreeAdaptor getTreeAdaptor() {
        return adaptor;
    }

    public String[] getTokenNames() { return PretCParser.tokenNames; }
    public String getGrammarFileName() { return "C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g"; }



    	boolean addtype = true;
    	long idCount = 1; //id 0 reserved
    	long uniqueThdInstantID = 1;
    	String sourceTemp = "";
    	long scopeCount = -1;
    	long currentScope = -1;
    	long scopeFuncCount = 0; //scope = 0 funcScope = 0 = global
    	String constantExprTempIdentifier = "";
    	Hashtable<Long,ScopeNode> scopeList = new Hashtable<Long,ScopeNode>();
    	String preType = "";
    	String preVarSpecifiers ="";
    	String preMax = "";
    	String preMin = "";
    	long typeDefStuctIDGen = 0;
    	ArrayList<String> PRETdefinedtable = new ArrayList<String>();
    	/*ArrayList weakAbortTemp = new ArrayList<Long>();
    	ArrayList strongAbortTemp = new ArrayList<Long>();
    	ArrayList hierWeakAbortTemp = new ArrayList<Long>();
    	ArrayList hierStrongAbortTemp = new ArrayList<Long>();*/
    	
    	Hashtable nodesTable= new Hashtable();// hash table of StatementNode test;
    	int debug = 0;
    	boolean isTypeName(String name) {
    		for (int i = Symbols_stack.size()-1; i>=0; i--) {
    			Symbols_scope scope = (Symbols_scope)Symbols_stack.get(i);
    			if ( scope.types.contains(name) ) {
    				return true;
    			}
    		}
    		return false;
    	}
    	/*void errorExit(int line,String code) {
    		System.out.println("Error type at line "+line);
    		System.out.println(code);
    		System.exit(0);
    	}*/
    	/* error reporting codes*/
    	/*http://www.antlr.org/wiki/display/ANTLR3/Migrating+from+ANTLR+2+to+ANTLR+3*/
    	/*book error handeling*/
    	boolean errorReported = false;
    	protected void mismatch(IntStream input, int ttype, BitSet follow)
    		throws RecognitionException
    	{
    		System.out.println("aaaaa "+input);
    		throw new MismatchedTokenException(ttype, input);
    		
    	}
    	
    	public Object recoverFromMismatchedSet(IntStream input, RecognitionException e,BitSet follow)
    		throws RecognitionException
    	{
    		System.out.println("bbbbb "+input);
    		throw e;
    	}

    	public String getErrorMessage(RecognitionException e, String[] tokenNames) {
    		return "cccccc";
    	}



    public static class translation_unit_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "translation_unit"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:193:1: translation_unit : ( external_declaration )+ ;
    public final PretCParser.translation_unit_return translation_unit() throws RecognitionException {
        Symbols_stack.push(new Symbols_scope());
        scopeNodes_stack.push(new scopeNodes_scope());

        PretCParser.translation_unit_return retval = new PretCParser.translation_unit_return();
        retval.start = input.LT(1);
        int translation_unit_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.external_declaration_return external_declaration1 = null;




          ((Symbols_scope)Symbols_stack.peek()).types = new HashSet();
          
          scopeCount = 0;
          currentScope = 0;
          ((scopeNodes_scope)scopeNodes_stack.peek()).node = new ScopeNode(currentScope);

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 1) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:211:2: ( ( external_declaration )+ )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:211:4: ( external_declaration )+
            {
            root_0 = (CommonTree)adaptor.nil();

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:211:4: ( external_declaration )+
            int cnt1=0;
            loop1:
            do {
                int alt1=2;
                alt1 = dfa1.predict(input);
                switch (alt1) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: external_declaration
            	    {
            	    pushFollow(FOLLOW_external_declaration_in_translation_unit251);
            	    external_declaration1=external_declaration();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, external_declaration1.getTree());

            	    }
            	    break;

            	default :
            	    if ( cnt1 >= 1 ) break loop1;
            	    if (state.backtracking>0) {state.failed=true; return retval;}
                        EarlyExitException eee =
                            new EarlyExitException(1, input);
                        throw eee;
                }
                cnt1++;
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {

              	scopeList.put(currentScope, ((scopeNodes_scope)scopeNodes_stack.peek()).node);
              	//System.out.println("--------------------------------");
              	//System.out.println(nodesTable);
              	//System.out.println("--------------------------------");
              	//System.out.println(scopeList);
              	//System.out.println("--------------------------------");
              	//System.out.println(input);

            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 1, translation_unit_StartIndex); }
            Symbols_stack.pop();
            scopeNodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "translation_unit"

    public static class external_declaration_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "external_declaration"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:214:1: external_declaration options {k=1; } : ( ( ( declaration_specifiers )? declarator ( declaration )* '{' )=> function_definition | declaration -> ^( GLOBAL_DECLARATION_TOK declaration ) | 'PRETDEF' IDENTIFIER ';' -> PRET_DEF_TOK | 'ReactiveInput' declaration_specifiers reactive_declarator ';' -> ^( 'ReactiveInput' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | 'ReactiveOutput' declaration_specifiers reactive_declarator ';' -> ^( 'ReactiveOutput' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | thread_definition );
    public final PretCParser.external_declaration_return external_declaration() throws RecognitionException {
        nodes_stack.push(new nodes_scope());

        PretCParser.external_declaration_return retval = new PretCParser.external_declaration_return();
        retval.start = input.LT(1);
        int external_declaration_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal4=null;
        Token IDENTIFIER5=null;
        Token char_literal6=null;
        Token string_literal7=null;
        Token char_literal10=null;
        Token string_literal11=null;
        Token char_literal14=null;
        PretCParser.function_definition_return function_definition2 = null;

        PretCParser.declaration_return declaration3 = null;

        PretCParser.declaration_specifiers_return declaration_specifiers8 = null;

        PretCParser.reactive_declarator_return reactive_declarator9 = null;

        PretCParser.declaration_specifiers_return declaration_specifiers12 = null;

        PretCParser.reactive_declarator_return reactive_declarator13 = null;

        PretCParser.thread_definition_return thread_definition15 = null;


        CommonTree string_literal4_tree=null;
        CommonTree IDENTIFIER5_tree=null;
        CommonTree char_literal6_tree=null;
        CommonTree string_literal7_tree=null;
        CommonTree char_literal10_tree=null;
        CommonTree string_literal11_tree=null;
        CommonTree char_literal14_tree=null;
        RewriteRuleTokenStream stream_43=new RewriteRuleTokenStream(adaptor,"token 43");
        RewriteRuleTokenStream stream_42=new RewriteRuleTokenStream(adaptor,"token 42");
        RewriteRuleTokenStream stream_41=new RewriteRuleTokenStream(adaptor,"token 41");
        RewriteRuleTokenStream stream_40=new RewriteRuleTokenStream(adaptor,"token 40");
        RewriteRuleTokenStream stream_IDENTIFIER=new RewriteRuleTokenStream(adaptor,"token IDENTIFIER");
        RewriteRuleSubtreeStream stream_declaration_specifiers=new RewriteRuleSubtreeStream(adaptor,"rule declaration_specifiers");
        RewriteRuleSubtreeStream stream_declaration=new RewriteRuleSubtreeStream(adaptor,"rule declaration");
        RewriteRuleSubtreeStream stream_reactive_declarator=new RewriteRuleSubtreeStream(adaptor,"rule reactive_declarator");

          ((nodes_scope)nodes_stack.peek()).node = new StatementNode();
          long ID=-1;
          long lineNo = input.LT(1).getLine();

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 2) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:239:2: ( ( ( declaration_specifiers )? declarator ( declaration )* '{' )=> function_definition | declaration -> ^( GLOBAL_DECLARATION_TOK declaration ) | 'PRETDEF' IDENTIFIER ';' -> PRET_DEF_TOK | 'ReactiveInput' declaration_specifiers reactive_declarator ';' -> ^( 'ReactiveInput' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | 'ReactiveOutput' declaration_specifiers reactive_declarator ';' -> ^( 'ReactiveOutput' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | thread_definition )
            int alt2=6;
            alt2 = dfa2.predict(input);
            switch (alt2) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:239:4: ( ( declaration_specifiers )? declarator ( declaration )* '{' )=> function_definition
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_function_definition_in_external_declaration305);
                    function_definition2=function_definition();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, function_definition2.getTree());

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:240:4: declaration
                    {
                    pushFollow(FOLLOW_declaration_in_external_declaration312);
                    declaration3=declaration();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_declaration.add(declaration3.getTree());


                    // AST REWRITE
                    // elements: declaration
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 240:16: -> ^( GLOBAL_DECLARATION_TOK declaration )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:240:19: ^( GLOBAL_DECLARATION_TOK declaration )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(GLOBAL_DECLARATION_TOK, "GLOBAL_DECLARATION_TOK"), root_1);

                        adaptor.addChild(root_1, stream_declaration.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:241:4: 'PRETDEF' IDENTIFIER ';'
                    {
                    string_literal4=(Token)match(input,40,FOLLOW_40_in_external_declaration327); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_40.add(string_literal4);

                    IDENTIFIER5=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_external_declaration329); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_IDENTIFIER.add(IDENTIFIER5);

                    char_literal6=(Token)match(input,41,FOLLOW_41_in_external_declaration331); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal6);

                    if ( state.backtracking==0 ) {
                      PRETdefinedtable.add((IDENTIFIER5!=null?IDENTIFIER5.getText():null));
                    }


                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 241:73: -> PRET_DEF_TOK
                    {
                        adaptor.addChild(root_0, (CommonTree)adaptor.create(PRET_DEF_TOK, "PRET_DEF_TOK"));

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 4 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:243:4: 'ReactiveInput' declaration_specifiers reactive_declarator ';'
                    {
                    string_literal7=(Token)match(input,42,FOLLOW_42_in_external_declaration346); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_42.add(string_literal7);

                    pushFollow(FOLLOW_declaration_specifiers_in_external_declaration348);
                    declaration_specifiers8=declaration_specifiers();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_declaration_specifiers.add(declaration_specifiers8.getTree());
                    pushFollow(FOLLOW_reactive_declarator_in_external_declaration350);
                    reactive_declarator9=reactive_declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_reactive_declarator.add(reactive_declarator9.getTree());
                    char_literal10=(Token)match(input,41,FOLLOW_41_in_external_declaration352); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal10);

                    if ( state.backtracking==0 ) {

                      			sourceTemp =  "//Reactive Input\n ";
                      			sourceTemp += (declaration_specifiers8!=null?input.toString(declaration_specifiers8.start,declaration_specifiers8.stop):null)+" "+(reactive_declarator9!=null?input.toString(reactive_declarator9.start,reactive_declarator9.stop):null) ;
                      			sourceTemp += ";\n";
                      			
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			if (isFromFunction_stack.size() > 0) { //within function scope
                      				((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			}else{
                      				((nodes_scope)nodes_stack.peek()).node.funcScopeID=0; //global
                      			}
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.type="ReactiveInput";
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: 42
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 265:4: -> ^( 'ReactiveInput' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:265:6: ^( 'ReactiveInput' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot(stream_42.nextNode(), root_1);

                        adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+ID));
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 5 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:266:4: 'ReactiveOutput' declaration_specifiers reactive_declarator ';'
                    {
                    string_literal11=(Token)match(input,43,FOLLOW_43_in_external_declaration372); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_43.add(string_literal11);

                    pushFollow(FOLLOW_declaration_specifiers_in_external_declaration374);
                    declaration_specifiers12=declaration_specifiers();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_declaration_specifiers.add(declaration_specifiers12.getTree());
                    pushFollow(FOLLOW_reactive_declarator_in_external_declaration376);
                    reactive_declarator13=reactive_declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_reactive_declarator.add(reactive_declarator13.getTree());
                    char_literal14=(Token)match(input,41,FOLLOW_41_in_external_declaration378); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal14);

                    if ( state.backtracking==0 ) {

                      			sourceTemp =  "//Reactive Output\n";
                      			sourceTemp += (declaration_specifiers12!=null?input.toString(declaration_specifiers12.start,declaration_specifiers12.stop):null)+" "+(reactive_declarator13!=null?input.toString(reactive_declarator13.start,reactive_declarator13.stop):null) ;
                      			sourceTemp += ";\n";
                      			
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			if (isFromFunction_stack.size() > 0) { //within function scope
                      				((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			}else{
                      				((nodes_scope)nodes_stack.peek()).node.funcScopeID=0; //global
                      			}
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.type="ReactiveOutput";
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: 43
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 288:4: -> ^( 'ReactiveOutput' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:288:6: ^( 'ReactiveOutput' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot(stream_43.nextNode(), root_1);

                        adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+ID));
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 6 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:289:4: thread_definition
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_thread_definition_in_external_declaration397);
                    thread_definition15=thread_definition();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, thread_definition15.getTree());

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 2, external_declaration_StartIndex); }
            nodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "external_declaration"

    public static class reactive_declarator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "reactive_declarator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:292:1: reactive_declarator : (d1= declarator ( '=' initializer )? ( range_declarator )? ) ( ',' d2= declarator ( '=' initializer )? ( range_declarator )? )* ;
    public final PretCParser.reactive_declarator_return reactive_declarator() throws RecognitionException {
        PretCParser.reactive_declarator_return retval = new PretCParser.reactive_declarator_return();
        retval.start = input.LT(1);
        int reactive_declarator_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal16=null;
        Token char_literal19=null;
        Token char_literal20=null;
        PretCParser.declarator_return d1 = null;

        PretCParser.declarator_return d2 = null;

        PretCParser.initializer_return initializer17 = null;

        PretCParser.range_declarator_return range_declarator18 = null;

        PretCParser.initializer_return initializer21 = null;

        PretCParser.range_declarator_return range_declarator22 = null;


        CommonTree char_literal16_tree=null;
        CommonTree char_literal19_tree=null;
        CommonTree char_literal20_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 3) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:2: ( (d1= declarator ( '=' initializer )? ( range_declarator )? ) ( ',' d2= declarator ( '=' initializer )? ( range_declarator )? )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:4: (d1= declarator ( '=' initializer )? ( range_declarator )? ) ( ',' d2= declarator ( '=' initializer )? ( range_declarator )? )*
            {
            root_0 = (CommonTree)adaptor.nil();

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:4: (d1= declarator ( '=' initializer )? ( range_declarator )? )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:5: d1= declarator ( '=' initializer )? ( range_declarator )?
            {
            pushFollow(FOLLOW_declarator_in_reactive_declarator412);
            d1=declarator();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, d1.getTree());
            if ( state.backtracking==0 ) {
              ((nodes_scope)nodes_stack.peek()).node.name.add((d1!=null?input.toString(d1.start,d1.stop):null));((scopeNodes_scope)scopeNodes_stack.peek()).node.variableMapPut((d1!=null?input.toString(d1.start,d1.stop):null),((nodes_scope)nodes_stack.peek()).node);
            }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:110: ( '=' initializer )?
            int alt3=2;
            int LA3_0 = input.LA(1);

            if ( (LA3_0==44) ) {
                alt3=1;
            }
            switch (alt3) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:111: '=' initializer
                    {
                    char_literal16=(Token)match(input,44,FOLLOW_44_in_reactive_declarator417); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal16_tree = (CommonTree)adaptor.create(char_literal16);
                    adaptor.addChild(root_0, char_literal16_tree);
                    }
                    pushFollow(FOLLOW_initializer_in_reactive_declarator419);
                    initializer17=initializer();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, initializer17.getTree());

                    }
                    break;

            }

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:129: ( range_declarator )?
            int alt4=2;
            int LA4_0 = input.LA(1);

            if ( (LA4_0==46) ) {
                alt4=1;
            }
            switch (alt4) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: range_declarator
                    {
                    pushFollow(FOLLOW_range_declarator_in_reactive_declarator423);
                    range_declarator18=range_declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, range_declarator18.getTree());

                    }
                    break;

            }


            }

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:148: ( ',' d2= declarator ( '=' initializer )? ( range_declarator )? )*
            loop7:
            do {
                int alt7=2;
                int LA7_0 = input.LA(1);

                if ( (LA7_0==45) ) {
                    alt7=1;
                }


                switch (alt7) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:149: ',' d2= declarator ( '=' initializer )? ( range_declarator )?
            	    {
            	    char_literal19=(Token)match(input,45,FOLLOW_45_in_reactive_declarator428); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal19_tree = (CommonTree)adaptor.create(char_literal19);
            	    adaptor.addChild(root_0, char_literal19_tree);
            	    }
            	    if ( state.backtracking==0 ) {
            	      ((nodes_scope)nodes_stack.peek()).node.constantStatement.add(new ArrayList<String>());
            	    }
            	    pushFollow(FOLLOW_declarator_in_reactive_declarator434);
            	    d2=declarator();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, d2.getTree());
            	    if ( state.backtracking==0 ) {
            	      ((nodes_scope)nodes_stack.peek()).node.declaredType.add(preType);((nodes_scope)nodes_stack.peek()).node.varSpecifiers.add(preVarSpecifiers);((nodes_scope)nodes_stack.peek()).node.name.add((d2!=null?input.toString(d2.start,d2.stop):null));((scopeNodes_scope)scopeNodes_stack.peek()).node.variableMapPut((d2!=null?input.toString(d2.start,d2.stop):null),((nodes_scope)nodes_stack.peek()).node);
            	    }
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:409: ( '=' initializer )?
            	    int alt5=2;
            	    int LA5_0 = input.LA(1);

            	    if ( (LA5_0==44) ) {
            	        alt5=1;
            	    }
            	    switch (alt5) {
            	        case 1 :
            	            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:410: '=' initializer
            	            {
            	            char_literal20=(Token)match(input,44,FOLLOW_44_in_reactive_declarator439); if (state.failed) return retval;
            	            if ( state.backtracking==0 ) {
            	            char_literal20_tree = (CommonTree)adaptor.create(char_literal20);
            	            adaptor.addChild(root_0, char_literal20_tree);
            	            }
            	            pushFollow(FOLLOW_initializer_in_reactive_declarator441);
            	            initializer21=initializer();

            	            state._fsp--;
            	            if (state.failed) return retval;
            	            if ( state.backtracking==0 ) adaptor.addChild(root_0, initializer21.getTree());

            	            }
            	            break;

            	    }

            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:293:428: ( range_declarator )?
            	    int alt6=2;
            	    int LA6_0 = input.LA(1);

            	    if ( (LA6_0==46) ) {
            	        alt6=1;
            	    }
            	    switch (alt6) {
            	        case 1 :
            	            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: range_declarator
            	            {
            	            pushFollow(FOLLOW_range_declarator_in_reactive_declarator445);
            	            range_declarator22=range_declarator();

            	            state._fsp--;
            	            if (state.failed) return retval;
            	            if ( state.backtracking==0 ) adaptor.addChild(root_0, range_declarator22.getTree());

            	            }
            	            break;

            	    }


            	    }
            	    break;

            	default :
            	    break loop7;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 3, reactive_declarator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "reactive_declarator"

    public static class range_declarator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "range_declarator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:295:1: range_declarator : '#range' min= DECIMAL_LITERAL 'to' max= DECIMAL_LITERAL ;
    public final PretCParser.range_declarator_return range_declarator() throws RecognitionException {
        PretCParser.range_declarator_return retval = new PretCParser.range_declarator_return();
        retval.start = input.LT(1);
        int range_declarator_StartIndex = input.index();
        CommonTree root_0 = null;

        Token min=null;
        Token max=null;
        Token string_literal23=null;
        Token string_literal24=null;

        CommonTree min_tree=null;
        CommonTree max_tree=null;
        CommonTree string_literal23_tree=null;
        CommonTree string_literal24_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 4) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:296:2: ( '#range' min= DECIMAL_LITERAL 'to' max= DECIMAL_LITERAL )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:296:5: '#range' min= DECIMAL_LITERAL 'to' max= DECIMAL_LITERAL
            {
            root_0 = (CommonTree)adaptor.nil();

            string_literal23=(Token)match(input,46,FOLLOW_46_in_range_declarator459); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            string_literal23_tree = (CommonTree)adaptor.create(string_literal23);
            adaptor.addChild(root_0, string_literal23_tree);
            }
            min=(Token)match(input,DECIMAL_LITERAL,FOLLOW_DECIMAL_LITERAL_in_range_declarator463); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            min_tree = (CommonTree)adaptor.create(min);
            adaptor.addChild(root_0, min_tree);
            }
            string_literal24=(Token)match(input,47,FOLLOW_47_in_range_declarator465); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            string_literal24_tree = (CommonTree)adaptor.create(string_literal24);
            adaptor.addChild(root_0, string_literal24_tree);
            }
            max=(Token)match(input,DECIMAL_LITERAL,FOLLOW_DECIMAL_LITERAL_in_range_declarator469); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            max_tree = (CommonTree)adaptor.create(max);
            adaptor.addChild(root_0, max_tree);
            }
            if ( state.backtracking==0 ) {

              			//System.out.println("ddddddddddddddddd "+((nodes_scope)nodes_stack.peek()).node.functionParameter);
              			//System.out.println("fffffffffffffffff "+((nodes_scope)nodes_stack.peek()).node.name);
              			int numberOfProcessedVariables = ((nodes_scope)nodes_stack.peek()).node.name.size();
              			if (((nodes_scope)nodes_stack.peek()).node.functionParameter.size() > 0) {
              				//minus 1 has function has already processed the name before processing the range
              				//hwere name on variable declare doesnt do that
              				numberOfProcessedVariables = ((nodes_scope)nodes_stack.peek()).node.functionParameter.size()-1;
              			}
              			while(numberOfProcessedVariables > ((nodes_scope)nodes_stack.peek()).node.minValue.size()) {
              				((nodes_scope)nodes_stack.peek()).node.minValue.add("UNDEFINED");
              				((nodes_scope)nodes_stack.peek()).node.maxValue.add("UNDEFINED");
              			}
              			((nodes_scope)nodes_stack.peek()).node.minValue.add((min!=null?min.getText():null));
              			((nodes_scope)nodes_stack.peek()).node.maxValue.add((max!=null?max.getText():null));
              			
              		
            }

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 4, range_declarator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "range_declarator"

    public static class thread_definition_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "thread_definition"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:315:1: thread_definition : 'thread' IDENTIFIER '(' ( 'void' )? ')' scope_statement -> ^( 'thread' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] scope_statement ) ;
    public final PretCParser.thread_definition_return thread_definition() throws RecognitionException {
        nodes_stack.push(new nodes_scope());

        PretCParser.thread_definition_return retval = new PretCParser.thread_definition_return();
        retval.start = input.LT(1);
        int thread_definition_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal25=null;
        Token IDENTIFIER26=null;
        Token char_literal27=null;
        Token string_literal28=null;
        Token char_literal29=null;
        PretCParser.scope_statement_return scope_statement30 = null;


        CommonTree string_literal25_tree=null;
        CommonTree IDENTIFIER26_tree=null;
        CommonTree char_literal27_tree=null;
        CommonTree string_literal28_tree=null;
        CommonTree char_literal29_tree=null;
        RewriteRuleTokenStream stream_49=new RewriteRuleTokenStream(adaptor,"token 49");
        RewriteRuleTokenStream stream_48=new RewriteRuleTokenStream(adaptor,"token 48");
        RewriteRuleTokenStream stream_51=new RewriteRuleTokenStream(adaptor,"token 51");
        RewriteRuleTokenStream stream_IDENTIFIER=new RewriteRuleTokenStream(adaptor,"token IDENTIFIER");
        RewriteRuleTokenStream stream_50=new RewriteRuleTokenStream(adaptor,"token 50");
        RewriteRuleSubtreeStream stream_scope_statement=new RewriteRuleSubtreeStream(adaptor,"rule scope_statement");

          ((nodes_scope)nodes_stack.peek()).node = new StatementNode();
          long ID=-1;
          long lineNo = input.LT(1).getLine();
          scopeFuncCount++; //thread is a type of function

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 5) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:323:2: ( 'thread' IDENTIFIER '(' ( 'void' )? ')' scope_statement -> ^( 'thread' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] scope_statement ) )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:323:4: 'thread' IDENTIFIER '(' ( 'void' )? ')' scope_statement
            {
            string_literal25=(Token)match(input,48,FOLLOW_48_in_thread_definition494); if (state.failed) return retval; 
            if ( state.backtracking==0 ) stream_48.add(string_literal25);

            IDENTIFIER26=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_thread_definition496); if (state.failed) return retval; 
            if ( state.backtracking==0 ) stream_IDENTIFIER.add(IDENTIFIER26);

            char_literal27=(Token)match(input,49,FOLLOW_49_in_thread_definition498); if (state.failed) return retval; 
            if ( state.backtracking==0 ) stream_49.add(char_literal27);

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:323:28: ( 'void' )?
            int alt8=2;
            int LA8_0 = input.LA(1);

            if ( (LA8_0==50) ) {
                alt8=1;
            }
            switch (alt8) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: 'void'
                    {
                    string_literal28=(Token)match(input,50,FOLLOW_50_in_thread_definition500); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_50.add(string_literal28);


                    }
                    break;

            }

            char_literal29=(Token)match(input,51,FOLLOW_51_in_thread_definition503); if (state.failed) return retval; 
            if ( state.backtracking==0 ) stream_51.add(char_literal29);

            pushFollow(FOLLOW_scope_statement_in_thread_definition505);
            scope_statement30=scope_statement();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) stream_scope_statement.add(scope_statement30.getTree());
            if ( state.backtracking==0 ) {

              			sourceTemp = "thread "+(IDENTIFIER26!=null?IDENTIFIER26.getText():null)+"(void)";
              			ID = idCount++;
              			((nodes_scope)nodes_stack.peek()).node.ID=ID;
              			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
              			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
              			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
              			((nodes_scope)nodes_stack.peek()).node.type="thread";
              			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
              			((nodes_scope)nodes_stack.peek()).node.name.add((IDENTIFIER26!=null?IDENTIFIER26.getText():null).trim()); //added trim to remove white space causing error
              			
              			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
              			if (debug > 0) {
              				System.out.println(nodesTable.get(ID));
              			}
              		
            }


            // AST REWRITE
            // elements: scope_statement, 48
            // token labels: 
            // rule labels: retval
            // token list labels: 
            // rule list labels: 
            // wildcard labels: 
            if ( state.backtracking==0 ) {
            retval.tree = root_0;
            RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

            root_0 = (CommonTree)adaptor.nil();
            // 339:5: -> ^( 'thread' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] scope_statement )
            {
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:339:9: ^( 'thread' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] scope_statement )
                {
                CommonTree root_1 = (CommonTree)adaptor.nil();
                root_1 = (CommonTree)adaptor.becomeRoot(stream_48.nextNode(), root_1);

                adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+ID));
                adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));
                adaptor.addChild(root_1, stream_scope_statement.nextTree());

                adaptor.addChild(root_0, root_1);
                }

            }

            retval.tree = root_0;}
            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 5, thread_definition_StartIndex); }
            nodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "thread_definition"

    public static class function_definition_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "function_definition"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:342:1: function_definition : ( declaration_specifiers )? declarator ( ( declaration )+ scope_statement | scope_statement ) -> ^( FUNCTION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ( declaration )* scope_statement ) ;
    public final PretCParser.function_definition_return function_definition() throws RecognitionException {
        Symbols_stack.push(new Symbols_scope());
        nodes_stack.push(new nodes_scope());
        is_stack.push(new is_scope());
        isFromFunction_stack.push(new isFromFunction_scope());
        scopeNodes_stack.push(new scopeNodes_scope());

        PretCParser.function_definition_return retval = new PretCParser.function_definition_return();
        retval.start = input.LT(1);
        int function_definition_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.declaration_specifiers_return declaration_specifiers31 = null;

        PretCParser.declarator_return declarator32 = null;

        PretCParser.declaration_return declaration33 = null;

        PretCParser.scope_statement_return scope_statement34 = null;

        PretCParser.scope_statement_return scope_statement35 = null;


        RewriteRuleSubtreeStream stream_declaration_specifiers=new RewriteRuleSubtreeStream(adaptor,"rule declaration_specifiers");
        RewriteRuleSubtreeStream stream_declarator=new RewriteRuleSubtreeStream(adaptor,"rule declarator");
        RewriteRuleSubtreeStream stream_declaration=new RewriteRuleSubtreeStream(adaptor,"rule declaration");
        RewriteRuleSubtreeStream stream_scope_statement=new RewriteRuleSubtreeStream(adaptor,"rule scope_statement");

          ((Symbols_scope)Symbols_stack.peek()).types = new HashSet();
          ((nodes_scope)nodes_stack.peek()).node = new StatementNode();
          ((isFromFunction_scope)isFromFunction_stack.peek()).data = new Boolean(true);
          long ID=-1;
          long lineNo = input.LT(1).getLine();
          scopeFuncCount++; 
          long previousScope = currentScope;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 6) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:360:2: ( ( declaration_specifiers )? declarator ( ( declaration )+ scope_statement | scope_statement ) -> ^( FUNCTION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ( declaration )* scope_statement ) )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:360:4: ( declaration_specifiers )? declarator ( ( declaration )+ scope_statement | scope_statement )
            {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:360:4: ( declaration_specifiers )?
            int alt9=2;
            alt9 = dfa9.predict(input);
            switch (alt9) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: declaration_specifiers
                    {
                    pushFollow(FOLLOW_declaration_specifiers_in_function_definition561);
                    declaration_specifiers31=declaration_specifiers();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_declaration_specifiers.add(declaration_specifiers31.getTree());

                    }
                    break;

            }

            if ( state.backtracking==0 ) {

              			((isFromFunction_scope)isFromFunction_stack.peek()).data = false;
              			currentScope = ++scopeCount;
              			((scopeNodes_scope)scopeNodes_stack.peek()).node = new ScopeNode(currentScope);
              		  	((scopeNodes_scope)scopeNodes_stack.peek()).node.parentID = previousScope;
              		
            }
            pushFollow(FOLLOW_declarator_in_function_definition573);
            declarator32=declarator();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) stream_declarator.add(declarator32.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:368:3: ( ( declaration )+ scope_statement | scope_statement )
            int alt11=2;
            alt11 = dfa11.predict(input);
            switch (alt11) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:368:5: ( declaration )+ scope_statement
                    {
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:368:5: ( declaration )+
                    int cnt10=0;
                    loop10:
                    do {
                        int alt10=2;
                        alt10 = dfa10.predict(input);
                        switch (alt10) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: declaration
                    	    {
                    	    pushFollow(FOLLOW_declaration_in_function_definition582);
                    	    declaration33=declaration();

                    	    state._fsp--;
                    	    if (state.failed) return retval;
                    	    if ( state.backtracking==0 ) stream_declaration.add(declaration33.getTree());

                    	    }
                    	    break;

                    	default :
                    	    if ( cnt10 >= 1 ) break loop10;
                    	    if (state.backtracking>0) {state.failed=true; return retval;}
                                EarlyExitException eee =
                                    new EarlyExitException(10, input);
                                throw eee;
                        }
                        cnt10++;
                    } while (true);

                    pushFollow(FOLLOW_scope_statement_in_function_definition585);
                    scope_statement34=scope_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_scope_statement.add(scope_statement34.getTree());

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:369:5: scope_statement
                    {
                    pushFollow(FOLLOW_scope_statement_in_function_definition595);
                    scope_statement35=scope_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_scope_statement.add(scope_statement35.getTree());

                    }
                    break;

            }

            if ( state.backtracking==0 ) {

              			sourceTemp = "";
              			if ((declaration_specifiers31!=null?input.toString(declaration_specifiers31.start,declaration_specifiers31.stop):null) != null) {
              				sourceTemp +=  (declaration_specifiers31!=null?input.toString(declaration_specifiers31.start,declaration_specifiers31.stop):null);
              			}
              			sourceTemp +=  " " + (declarator32!=null?input.toString(declarator32.start,declarator32.stop):null);
              			ID = idCount++;
              			((nodes_scope)nodes_stack.peek()).node.ID=ID;
              			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
              			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
              			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
              			String function_name = ((declarator32!=null?input.toString(declarator32.start,declarator32.stop):null)).replaceFirst("[(].*","").trim(); //add trim on name
              			//System.out.println("........................."+function_name);
              			((nodes_scope)nodes_stack.peek()).node.type="function";
              			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
              			//((nodes_scope)nodes_stack.peek()).node.name.add((declarator32!=null?input.toString(declarator32.start,declarator32.stop):null));
              			((nodes_scope)nodes_stack.peek()).node.name.add(function_name);
              			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
              			if (debug > 0) {
              				System.out.println(nodesTable.get(ID));
              			}
              		
            }


            // AST REWRITE
            // elements: scope_statement, declaration
            // token labels: 
            // rule labels: retval
            // token list labels: 
            // rule list labels: 
            // wildcard labels: 
            if ( state.backtracking==0 ) {
            retval.tree = root_0;
            RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

            root_0 = (CommonTree)adaptor.nil();
            // 393:3: -> ^( FUNCTION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ( declaration )* scope_statement )
            {
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:393:7: ^( FUNCTION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ( declaration )* scope_statement )
                {
                CommonTree root_1 = (CommonTree)adaptor.nil();
                root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(FUNCTION_TOK, "FUNCTION_TOK"), root_1);

                adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+ID));
                adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:393:60: ( declaration )*
                while ( stream_declaration.hasNext() ) {
                    adaptor.addChild(root_1, stream_declaration.nextTree());

                }
                stream_declaration.reset();
                adaptor.addChild(root_1, stream_scope_statement.nextTree());

                adaptor.addChild(root_0, root_1);
                }

            }

            retval.tree = root_0;}
            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {

                ((isFromFunction_scope)isFromFunction_stack.peek()).data = false;
                
                scopeList.put(currentScope,((scopeNodes_scope)scopeNodes_stack.peek()).node);
                currentScope = previousScope;

            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 6, function_definition_StartIndex); }
            Symbols_stack.pop();
            nodes_stack.pop();
            is_stack.pop();
            isFromFunction_stack.pop();
            scopeNodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "function_definition"

    public static class declaration_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "declaration"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:397:1: declaration : ( 'typedef' ( declaration_specifiers )? init_declarator_list ';' -> ^( TYPE_DECLARATION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | declaration_specifiers ( init_declarator_list )? ';' -> ^( DECLARATION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | LINE_COMMAND -> PREPROC_TOK[$LINE_COMMAND.text] );
    public final PretCParser.declaration_return declaration() throws RecognitionException {
        is_stack.push(new is_scope());
        nodes_stack.push(new nodes_scope());

        PretCParser.declaration_return retval = new PretCParser.declaration_return();
        retval.start = input.LT(1);
        int declaration_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal36=null;
        Token char_literal39=null;
        Token char_literal42=null;
        Token LINE_COMMAND43=null;
        PretCParser.declaration_specifiers_return declaration_specifiers37 = null;

        PretCParser.init_declarator_list_return init_declarator_list38 = null;

        PretCParser.declaration_specifiers_return declaration_specifiers40 = null;

        PretCParser.init_declarator_list_return init_declarator_list41 = null;


        CommonTree string_literal36_tree=null;
        CommonTree char_literal39_tree=null;
        CommonTree char_literal42_tree=null;
        CommonTree LINE_COMMAND43_tree=null;
        RewriteRuleTokenStream stream_41=new RewriteRuleTokenStream(adaptor,"token 41");
        RewriteRuleTokenStream stream_52=new RewriteRuleTokenStream(adaptor,"token 52");
        RewriteRuleTokenStream stream_LINE_COMMAND=new RewriteRuleTokenStream(adaptor,"token LINE_COMMAND");
        RewriteRuleSubtreeStream stream_declaration_specifiers=new RewriteRuleSubtreeStream(adaptor,"rule declaration_specifiers");
        RewriteRuleSubtreeStream stream_init_declarator_list=new RewriteRuleSubtreeStream(adaptor,"rule init_declarator_list");

          ((is_scope)is_stack.peek()).typeDef = false;
          ((is_scope)is_stack.peek()).declaration = true;
          ((nodes_scope)nodes_stack.peek()).node = new StatementNode();
          long ID=-1;
          long lineNo = input.LT(1).getLine();
          boolean gotName = false;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 7) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:410:2: ( 'typedef' ( declaration_specifiers )? init_declarator_list ';' -> ^( TYPE_DECLARATION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | declaration_specifiers ( init_declarator_list )? ';' -> ^( DECLARATION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | LINE_COMMAND -> PREPROC_TOK[$LINE_COMMAND.text] )
            int alt14=3;
            alt14 = dfa14.predict(input);
            switch (alt14) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:410:4: 'typedef' ( declaration_specifiers )? init_declarator_list ';'
                    {
                    string_literal36=(Token)match(input,52,FOLLOW_52_in_declaration663); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_52.add(string_literal36);

                    if ( state.backtracking==0 ) {
                      ((nodes_scope)nodes_stack.peek()).node.type="typedef";
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:410:45: ( declaration_specifiers )?
                    int alt12=2;
                    alt12 = dfa12.predict(input);
                    switch (alt12) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: declaration_specifiers
                            {
                            pushFollow(FOLLOW_declaration_specifiers_in_declaration667);
                            declaration_specifiers37=declaration_specifiers();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) stream_declaration_specifiers.add(declaration_specifiers37.getTree());

                            }
                            break;

                    }

                    if ( state.backtracking==0 ) {
                      ((is_scope)is_stack.peek()).typeDef =true;
                    }
                    pushFollow(FOLLOW_init_declarator_list_in_declaration675);
                    init_declarator_list38=init_declarator_list();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_init_declarator_list.add(init_declarator_list38.getTree());
                    char_literal39=(Token)match(input,41,FOLLOW_41_in_declaration677); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal39);

                    if ( state.backtracking==0 ) {

                      	  		sourceTemp = "typedef ";
                      	  		if ((declaration_specifiers37!=null?input.toString(declaration_specifiers37.start,declaration_specifiers37.stop):null) != null) {
                      	  			sourceTemp += (declaration_specifiers37!=null?input.toString(declaration_specifiers37.start,declaration_specifiers37.stop):null) +" ";
                      	  		}
                      	  		sourceTemp += (init_declarator_list38!=null?input.toString(init_declarator_list38.start,init_declarator_list38.stop):null) +";";
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			if (isFromFunction_stack.size() > 0) { //within function scope
                      				((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			}else{
                      				((nodes_scope)nodes_stack.peek()).node.funcScopeID=0; //global
                      			}
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 434:5: -> ^( TYPE_DECLARATION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:434:7: ^( TYPE_DECLARATION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(TYPE_DECLARATION_TOK, "TYPE_DECLARATION_TOK"), root_1);

                        adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+ID));
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:436:4: declaration_specifiers ( init_declarator_list )? ';'
                    {
                    pushFollow(FOLLOW_declaration_specifiers_in_declaration706);
                    declaration_specifiers40=declaration_specifiers();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_declaration_specifiers.add(declaration_specifiers40.getTree());
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:436:27: ( init_declarator_list )?
                    int alt13=2;
                    int LA13_0 = input.LA(1);

                    if ( (LA13_0==IDENTIFIER||LA13_0==49||LA13_0==75) ) {
                        alt13=1;
                    }
                    switch (alt13) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:436:28: init_declarator_list
                            {
                            pushFollow(FOLLOW_init_declarator_list_in_declaration709);
                            init_declarator_list41=init_declarator_list();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) stream_init_declarator_list.add(init_declarator_list41.getTree());
                            if ( state.backtracking==0 ) {
                              gotName=true;
                            }

                            }
                            break;

                    }

                    char_literal42=(Token)match(input,41,FOLLOW_41_in_declaration715); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal42);

                    if ( state.backtracking==0 ) {

                      			if (gotName == false) {
                      				((nodes_scope)nodes_stack.peek()).node.name.add(""); 
                      			}
                      			sourceTemp =  "";
                      			sourceTemp += (declaration_specifiers40!=null?input.toString(declaration_specifiers40.start,declaration_specifiers40.stop):null) ;
                      			if ((init_declarator_list41!=null?input.toString(init_declarator_list41.start,init_declarator_list41.stop):null) != null) {
                      				sourceTemp += " " + (init_declarator_list41!=null?input.toString(init_declarator_list41.start,init_declarator_list41.stop):null);
                      			}
                      			sourceTemp += ";";
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			if (isFromFunction_stack.size() > 0) { //within function scope
                      				((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			}else{
                      				((nodes_scope)nodes_stack.peek()).node.funcScopeID=0; //global
                      			}
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.type="declare";
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 464:3: -> ^( DECLARATION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:464:5: ^( DECLARATION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(DECLARATION_TOK, "DECLARATION_TOK"), root_1);

                        adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+ID));
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:465:4: LINE_COMMAND
                    {
                    LINE_COMMAND43=(Token)match(input,LINE_COMMAND,FOLLOW_LINE_COMMAND_in_declaration738); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_LINE_COMMAND.add(LINE_COMMAND43);



                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 465:17: -> PREPROC_TOK[$LINE_COMMAND.text]
                    {
                        adaptor.addChild(root_0, (CommonTree)adaptor.create(PREPROC_TOK, (LINE_COMMAND43!=null?LINE_COMMAND43.getText():null)));

                    }

                    retval.tree = root_0;}
                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {

                ((is_scope)is_stack.peek()).declaration = false;

            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 7, declaration_StartIndex); }
            is_stack.pop();
            nodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "declaration"

    public static class declaration_specifiers_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "declaration_specifiers"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:468:1: declaration_specifiers : ( storage_class_specifier | type_qualifier )* type_specifier ;
    public final PretCParser.declaration_specifiers_return declaration_specifiers() throws RecognitionException {
        PretCParser.declaration_specifiers_return retval = new PretCParser.declaration_specifiers_return();
        retval.start = input.LT(1);
        int declaration_specifiers_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.storage_class_specifier_return storage_class_specifier44 = null;

        PretCParser.type_qualifier_return type_qualifier45 = null;

        PretCParser.type_specifier_return type_specifier46 = null;




        	String specifiers = "";

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 8) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:476:2: ( ( storage_class_specifier | type_qualifier )* type_specifier )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:476:6: ( storage_class_specifier | type_qualifier )* type_specifier
            {
            root_0 = (CommonTree)adaptor.nil();

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:476:6: ( storage_class_specifier | type_qualifier )*
            loop15:
            do {
                int alt15=3;
                alt15 = dfa15.predict(input);
                switch (alt15) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:476:10: storage_class_specifier
            	    {
            	    pushFollow(FOLLOW_storage_class_specifier_in_declaration_specifiers768);
            	    storage_class_specifier44=storage_class_specifier();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, storage_class_specifier44.getTree());
            	    if ( state.backtracking==0 ) {
            	      specifiers+=(storage_class_specifier44!=null?input.toString(storage_class_specifier44.start,storage_class_specifier44.stop):null)+" ";
            	    }

            	    }
            	    break;
            	case 2 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:477:14: type_qualifier
            	    {
            	    pushFollow(FOLLOW_type_qualifier_in_declaration_specifiers785);
            	    type_qualifier45=type_qualifier();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, type_qualifier45.getTree());
            	    if ( state.backtracking==0 ) {
            	      specifiers+=(type_qualifier45!=null?input.toString(type_qualifier45.start,type_qualifier45.stop):null)+" ";
            	    }

            	    }
            	    break;

            	default :
            	    break loop15;
                }
            } while (true);

            pushFollow(FOLLOW_type_specifier_in_declaration_specifiers818);
            type_specifier46=type_specifier();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, type_specifier46.getTree());
            if ( state.backtracking==0 ) {
              specifiers+=(type_specifier46!=null?input.toString(type_specifier46.start,type_specifier46.stop):null)+" ";
            }
            if ( state.backtracking==0 ) {

                      	if (addtype) {
                      		((nodes_scope)nodes_stack.peek()).node.varSpecifiers.add(specifiers);
                      		preVarSpecifiers = specifiers; 
                      	}
                      	
                      
            }

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 8, declaration_specifiers_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "declaration_specifiers"

    public static class init_declarator_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "init_declarator_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:492:1: init_declarator_list : init_declarator ( ',' init_declarator )* ;
    public final PretCParser.init_declarator_list_return init_declarator_list() throws RecognitionException {
        PretCParser.init_declarator_list_return retval = new PretCParser.init_declarator_list_return();
        retval.start = input.LT(1);
        int init_declarator_list_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal48=null;
        PretCParser.init_declarator_return init_declarator47 = null;

        PretCParser.init_declarator_return init_declarator49 = null;


        CommonTree char_literal48_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 9) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:493:2: ( init_declarator ( ',' init_declarator )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:493:4: init_declarator ( ',' init_declarator )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_init_declarator_in_init_declarator_list866);
            init_declarator47=init_declarator();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, init_declarator47.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:493:20: ( ',' init_declarator )*
            loop16:
            do {
                int alt16=2;
                int LA16_0 = input.LA(1);

                if ( (LA16_0==45) ) {
                    alt16=1;
                }


                switch (alt16) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:493:21: ',' init_declarator
            	    {
            	    char_literal48=(Token)match(input,45,FOLLOW_45_in_init_declarator_list869); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal48_tree = (CommonTree)adaptor.create(char_literal48);
            	    adaptor.addChild(root_0, char_literal48_tree);
            	    }
            	    if ( state.backtracking==0 ) {
            	      ((nodes_scope)nodes_stack.peek()).node.constantStatement.add(new ArrayList<String>());
            	    }
            	    pushFollow(FOLLOW_init_declarator_in_init_declarator_list872);
            	    init_declarator49=init_declarator();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, init_declarator49.getTree());
            	    if ( state.backtracking==0 ) {
            	      ((nodes_scope)nodes_stack.peek()).node.declaredType.add(preType);((nodes_scope)nodes_stack.peek()).node.varSpecifiers.add(preVarSpecifiers);
            	    }

            	    }
            	    break;

            	default :
            	    break loop16;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 9, init_declarator_list_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "init_declarator_list"

    public static class init_declarator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "init_declarator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:496:1: init_declarator : declarator ( '=' initializer )? ( range_declarator )? ;
    public final PretCParser.init_declarator_return init_declarator() throws RecognitionException {
        PretCParser.init_declarator_return retval = new PretCParser.init_declarator_return();
        retval.start = input.LT(1);
        int init_declarator_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal51=null;
        PretCParser.declarator_return declarator50 = null;

        PretCParser.initializer_return initializer52 = null;

        PretCParser.range_declarator_return range_declarator53 = null;


        CommonTree char_literal51_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 10) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:497:2: ( declarator ( '=' initializer )? ( range_declarator )? )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:497:4: declarator ( '=' initializer )? ( range_declarator )?
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_declarator_in_init_declarator889);
            declarator50=declarator();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, declarator50.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:497:15: ( '=' initializer )?
            int alt17=2;
            int LA17_0 = input.LA(1);

            if ( (LA17_0==44) ) {
                alt17=1;
            }
            switch (alt17) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:497:16: '=' initializer
                    {
                    char_literal51=(Token)match(input,44,FOLLOW_44_in_init_declarator892); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal51_tree = (CommonTree)adaptor.create(char_literal51);
                    adaptor.addChild(root_0, char_literal51_tree);
                    }
                    pushFollow(FOLLOW_initializer_in_init_declarator894);
                    initializer52=initializer();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, initializer52.getTree());

                    }
                    break;

            }

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:497:35: ( range_declarator )?
            int alt18=2;
            int LA18_0 = input.LA(1);

            if ( (LA18_0==46) ) {
                alt18=1;
            }
            switch (alt18) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: range_declarator
                    {
                    pushFollow(FOLLOW_range_declarator_in_init_declarator899);
                    range_declarator53=range_declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, range_declarator53.getTree());

                    }
                    break;

            }

            if ( state.backtracking==0 ) {

              			//System.out.println("sssssssss "+(declarator50!=null?input.toString(declarator50.start,declarator50.stop):null));
              			((nodes_scope)nodes_stack.peek()).node.name.add((declarator50!=null?input.toString(declarator50.start,declarator50.stop):null));	
              			if (((nodes_scope)nodes_stack.peek()).node.type.equals("typedef")==false) {
              				((scopeNodes_scope)scopeNodes_stack.peek()).node.variableMapPut((declarator50!=null?input.toString(declarator50.start,declarator50.stop):null),((nodes_scope)nodes_stack.peek()).node);
              			}
              			
              			/*if (((nodes_scope)nodes_stack.peek()).node.constantStatement.size() < ((nodes_scope)nodes_stack.peek()).node.name.size()) {
              				((nodes_scope)nodes_stack.peek()).node.constantStatement.add("UNDEFINED");//undefined var
              			}*/
              			//((nodes_scope)nodes_stack.peek()).node.constantStatement.add((initializer52!=null?input.toString(initializer52.start,initializer52.stop):null));
              		
            }

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 10, init_declarator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "init_declarator"

    public static class storage_class_specifier_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "storage_class_specifier"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:512:1: storage_class_specifier : ( 'extern' | 'static' | 'auto' | 'register' );
    public final PretCParser.storage_class_specifier_return storage_class_specifier() throws RecognitionException {
        PretCParser.storage_class_specifier_return retval = new PretCParser.storage_class_specifier_return();
        retval.start = input.LT(1);
        int storage_class_specifier_StartIndex = input.index();
        CommonTree root_0 = null;

        Token set54=null;

        CommonTree set54_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 11) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:513:2: ( 'extern' | 'static' | 'auto' | 'register' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
            {
            root_0 = (CommonTree)adaptor.nil();

            set54=(Token)input.LT(1);
            if ( (input.LA(1)>=53 && input.LA(1)<=56) ) {
                input.consume();
                if ( state.backtracking==0 ) adaptor.addChild(root_0, (CommonTree)adaptor.create(set54));
                state.errorRecovery=false;state.failed=false;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                MismatchedSetException mse = new MismatchedSetException(null,input);
                throw mse;
            }


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 11, storage_class_specifier_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "storage_class_specifier"

    public static class type_specifier_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "type_specifier"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:519:1: type_specifier : ( 'void' | ( 'unsigned' | 'signed' )? 'char' | ( 'unsigned' | 'signed' )? 'short' | ( 'unsigned' | 'signed' )? 'int' | ( 'unsigned' | 'signed' )? 'long' 'long' | ( 'unsigned' | 'signed' )? 'long' | 'float' | 'double' | struct_or_union_specifier | enum_specifier | type_id | declared_id );
    public final PretCParser.type_specifier_return type_specifier() throws RecognitionException {
        PretCParser.type_specifier_return retval = new PretCParser.type_specifier_return();
        retval.start = input.LT(1);
        int type_specifier_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal55=null;
        Token string_literal56=null;
        Token string_literal57=null;
        Token string_literal58=null;
        Token string_literal59=null;
        Token string_literal60=null;
        Token string_literal61=null;
        Token string_literal62=null;
        Token string_literal63=null;
        Token string_literal64=null;
        Token string_literal65=null;
        Token string_literal66=null;
        Token string_literal67=null;
        Token string_literal68=null;
        Token string_literal69=null;
        Token string_literal70=null;
        Token string_literal71=null;
        Token string_literal72=null;
        Token string_literal73=null;
        PretCParser.struct_or_union_specifier_return struct_or_union_specifier74 = null;

        PretCParser.enum_specifier_return enum_specifier75 = null;

        PretCParser.type_id_return type_id76 = null;

        PretCParser.declared_id_return declared_id77 = null;


        CommonTree string_literal55_tree=null;
        CommonTree string_literal56_tree=null;
        CommonTree string_literal57_tree=null;
        CommonTree string_literal58_tree=null;
        CommonTree string_literal59_tree=null;
        CommonTree string_literal60_tree=null;
        CommonTree string_literal61_tree=null;
        CommonTree string_literal62_tree=null;
        CommonTree string_literal63_tree=null;
        CommonTree string_literal64_tree=null;
        CommonTree string_literal65_tree=null;
        CommonTree string_literal66_tree=null;
        CommonTree string_literal67_tree=null;
        CommonTree string_literal68_tree=null;
        CommonTree string_literal69_tree=null;
        CommonTree string_literal70_tree=null;
        CommonTree string_literal71_tree=null;
        CommonTree string_literal72_tree=null;
        CommonTree string_literal73_tree=null;


        	String typeTemp = "";

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 12) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:538:2: ( 'void' | ( 'unsigned' | 'signed' )? 'char' | ( 'unsigned' | 'signed' )? 'short' | ( 'unsigned' | 'signed' )? 'int' | ( 'unsigned' | 'signed' )? 'long' 'long' | ( 'unsigned' | 'signed' )? 'long' | 'float' | 'double' | struct_or_union_specifier | enum_specifier | type_id | declared_id )
            int alt24=12;
            alt24 = dfa24.predict(input);
            switch (alt24) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:538:4: 'void'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal55=(Token)match(input,50,FOLLOW_50_in_type_specifier951); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal55_tree = (CommonTree)adaptor.create(string_literal55);
                    adaptor.addChild(root_0, string_literal55_tree);
                    }
                    if ( state.backtracking==0 ) {
                      typeTemp ="void";
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:539:4: ( 'unsigned' | 'signed' )? 'char'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:539:4: ( 'unsigned' | 'signed' )?
                    int alt19=3;
                    int LA19_0 = input.LA(1);

                    if ( (LA19_0==57) ) {
                        alt19=1;
                    }
                    else if ( (LA19_0==58) ) {
                        alt19=2;
                    }
                    switch (alt19) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:539:5: 'unsigned'
                            {
                            string_literal56=(Token)match(input,57,FOLLOW_57_in_type_specifier968); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            string_literal56_tree = (CommonTree)adaptor.create(string_literal56);
                            adaptor.addChild(root_0, string_literal56_tree);
                            }
                            if ( state.backtracking==0 ) {
                              typeTemp="unsigned";
                            }

                            }
                            break;
                        case 2 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:539:39: 'signed'
                            {
                            string_literal57=(Token)match(input,58,FOLLOW_58_in_type_specifier972); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            string_literal57_tree = (CommonTree)adaptor.create(string_literal57);
                            adaptor.addChild(root_0, string_literal57_tree);
                            }
                            if ( state.backtracking==0 ) {
                              typeTemp="signed";
                            }

                            }
                            break;

                    }

                    string_literal58=(Token)match(input,59,FOLLOW_59_in_type_specifier977); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal58_tree = (CommonTree)adaptor.create(string_literal58);
                    adaptor.addChild(root_0, string_literal58_tree);
                    }
                    if ( state.backtracking==0 ) {
                      typeTemp +=" char";
                    }

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:540:4: ( 'unsigned' | 'signed' )? 'short'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:540:4: ( 'unsigned' | 'signed' )?
                    int alt20=3;
                    int LA20_0 = input.LA(1);

                    if ( (LA20_0==57) ) {
                        alt20=1;
                    }
                    else if ( (LA20_0==58) ) {
                        alt20=2;
                    }
                    switch (alt20) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:540:5: 'unsigned'
                            {
                            string_literal59=(Token)match(input,57,FOLLOW_57_in_type_specifier985); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            string_literal59_tree = (CommonTree)adaptor.create(string_literal59);
                            adaptor.addChild(root_0, string_literal59_tree);
                            }
                            if ( state.backtracking==0 ) {
                              typeTemp="unsigned";
                            }

                            }
                            break;
                        case 2 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:540:39: 'signed'
                            {
                            string_literal60=(Token)match(input,58,FOLLOW_58_in_type_specifier989); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            string_literal60_tree = (CommonTree)adaptor.create(string_literal60);
                            adaptor.addChild(root_0, string_literal60_tree);
                            }
                            if ( state.backtracking==0 ) {
                              typeTemp="signed";
                            }

                            }
                            break;

                    }

                    string_literal61=(Token)match(input,60,FOLLOW_60_in_type_specifier994); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal61_tree = (CommonTree)adaptor.create(string_literal61);
                    adaptor.addChild(root_0, string_literal61_tree);
                    }
                    if ( state.backtracking==0 ) {
                      typeTemp +=" short";
                    }

                    }
                    break;
                case 4 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:541:4: ( 'unsigned' | 'signed' )? 'int'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:541:4: ( 'unsigned' | 'signed' )?
                    int alt21=3;
                    int LA21_0 = input.LA(1);

                    if ( (LA21_0==57) ) {
                        alt21=1;
                    }
                    else if ( (LA21_0==58) ) {
                        alt21=2;
                    }
                    switch (alt21) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:541:5: 'unsigned'
                            {
                            string_literal62=(Token)match(input,57,FOLLOW_57_in_type_specifier1002); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            string_literal62_tree = (CommonTree)adaptor.create(string_literal62);
                            adaptor.addChild(root_0, string_literal62_tree);
                            }
                            if ( state.backtracking==0 ) {
                              typeTemp="unsigned";
                            }

                            }
                            break;
                        case 2 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:541:39: 'signed'
                            {
                            string_literal63=(Token)match(input,58,FOLLOW_58_in_type_specifier1006); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            string_literal63_tree = (CommonTree)adaptor.create(string_literal63);
                            adaptor.addChild(root_0, string_literal63_tree);
                            }
                            if ( state.backtracking==0 ) {
                              typeTemp="signed";
                            }

                            }
                            break;

                    }

                    string_literal64=(Token)match(input,61,FOLLOW_61_in_type_specifier1011); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal64_tree = (CommonTree)adaptor.create(string_literal64);
                    adaptor.addChild(root_0, string_literal64_tree);
                    }
                    if ( state.backtracking==0 ) {
                      typeTemp +=" int";
                    }

                    }
                    break;
                case 5 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:542:4: ( 'unsigned' | 'signed' )? 'long' 'long'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:542:4: ( 'unsigned' | 'signed' )?
                    int alt22=3;
                    int LA22_0 = input.LA(1);

                    if ( (LA22_0==57) ) {
                        alt22=1;
                    }
                    else if ( (LA22_0==58) ) {
                        alt22=2;
                    }
                    switch (alt22) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:542:5: 'unsigned'
                            {
                            string_literal65=(Token)match(input,57,FOLLOW_57_in_type_specifier1020); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            string_literal65_tree = (CommonTree)adaptor.create(string_literal65);
                            adaptor.addChild(root_0, string_literal65_tree);
                            }
                            if ( state.backtracking==0 ) {
                              typeTemp="unsigned";
                            }

                            }
                            break;
                        case 2 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:542:39: 'signed'
                            {
                            string_literal66=(Token)match(input,58,FOLLOW_58_in_type_specifier1024); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            string_literal66_tree = (CommonTree)adaptor.create(string_literal66);
                            adaptor.addChild(root_0, string_literal66_tree);
                            }
                            if ( state.backtracking==0 ) {
                              typeTemp="signed";
                            }

                            }
                            break;

                    }

                    string_literal67=(Token)match(input,62,FOLLOW_62_in_type_specifier1029); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal67_tree = (CommonTree)adaptor.create(string_literal67);
                    adaptor.addChild(root_0, string_literal67_tree);
                    }
                    string_literal68=(Token)match(input,62,FOLLOW_62_in_type_specifier1031); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal68_tree = (CommonTree)adaptor.create(string_literal68);
                    adaptor.addChild(root_0, string_literal68_tree);
                    }
                    if ( state.backtracking==0 ) {
                      typeTemp +=" long long";
                    }

                    }
                    break;
                case 6 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:543:4: ( 'unsigned' | 'signed' )? 'long'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:543:4: ( 'unsigned' | 'signed' )?
                    int alt23=3;
                    int LA23_0 = input.LA(1);

                    if ( (LA23_0==57) ) {
                        alt23=1;
                    }
                    else if ( (LA23_0==58) ) {
                        alt23=2;
                    }
                    switch (alt23) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:543:5: 'unsigned'
                            {
                            string_literal69=(Token)match(input,57,FOLLOW_57_in_type_specifier1039); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            string_literal69_tree = (CommonTree)adaptor.create(string_literal69);
                            adaptor.addChild(root_0, string_literal69_tree);
                            }
                            if ( state.backtracking==0 ) {
                              typeTemp="unsigned";
                            }

                            }
                            break;
                        case 2 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:543:39: 'signed'
                            {
                            string_literal70=(Token)match(input,58,FOLLOW_58_in_type_specifier1043); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            string_literal70_tree = (CommonTree)adaptor.create(string_literal70);
                            adaptor.addChild(root_0, string_literal70_tree);
                            }
                            if ( state.backtracking==0 ) {
                              typeTemp="signed";
                            }

                            }
                            break;

                    }

                    string_literal71=(Token)match(input,62,FOLLOW_62_in_type_specifier1048); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal71_tree = (CommonTree)adaptor.create(string_literal71);
                    adaptor.addChild(root_0, string_literal71_tree);
                    }
                    if ( state.backtracking==0 ) {
                      typeTemp +=" long";
                    }

                    }
                    break;
                case 7 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:544:4: 'float'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal72=(Token)match(input,63,FOLLOW_63_in_type_specifier1055); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal72_tree = (CommonTree)adaptor.create(string_literal72);
                    adaptor.addChild(root_0, string_literal72_tree);
                    }
                    if ( state.backtracking==0 ) {
                      typeTemp ="float";
                    }

                    }
                    break;
                case 8 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:545:4: 'double'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal73=(Token)match(input,64,FOLLOW_64_in_type_specifier1070); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal73_tree = (CommonTree)adaptor.create(string_literal73);
                    adaptor.addChild(root_0, string_literal73_tree);
                    }
                    if ( state.backtracking==0 ) {
                      typeTemp ="double";
                    }

                    }
                    break;
                case 9 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:548:4: struct_or_union_specifier
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_struct_or_union_specifier_in_type_specifier1089);
                    struct_or_union_specifier74=struct_or_union_specifier();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, struct_or_union_specifier74.getTree());
                    if ( state.backtracking==0 ) {

                      						typeTemp = (struct_or_union_specifier74!=null?struct_or_union_specifier74.typeTemp:null);
                      						//declared stuctures
                      						//(struct_or_union_specifier74!=null?struct_or_union_specifier74.n:null).sourceNode = ((nodes_scope)nodes_stack.peek()).node;
                      						((nodes_scope)nodes_stack.peek()).node.addScopedVaraibles((struct_or_union_specifier74!=null?struct_or_union_specifier74.n:null));
                      						
                      						(struct_or_union_specifier74!=null?struct_or_union_specifier74.n:null).structTypeName = (struct_or_union_specifier74!=null?struct_or_union_specifier74.structTypeName:null);
                      						if ((struct_or_union_specifier74!=null?struct_or_union_specifier74.n:null).name.size()>0) { //has things inside struct
                      							//System.out.println((struct_or_union_specifier74!=null?struct_or_union_specifier74.n:null).name+" sdfadsghgas ash "+ (struct_or_union_specifier74!=null?struct_or_union_specifier74.structTypeName:null) + " "+((nodes_scope)nodes_stack.peek()).node);
                      							if ((struct_or_union_specifier74!=null?struct_or_union_specifier74.structTypeName:null) == null) {  
                      								//if (((nodes_scope)nodes_stack.peek()).node.type.equals("typedef")) {
                      								//	System.out.println(((nodes_scope)nodes_stack.peek()).node.name.get(0));
                      								////	((scopeNodes_scope)scopeNodes_stack.peek()).node.listOfStruct.put(((nodes_scope)nodes_stack.peek()).node.name.get(0),((nodes_scope)nodes_stack.peek()).node);
                      								//	(struct_or_union_specifier74!=null?struct_or_union_specifier74.n:null).structTypeName = ((nodes_scope)nodes_stack.peek()).node.name.get(0);
                      								//	
                      								//}else{
                      									long ID = typeDefStuctIDGen++;
                      									((scopeNodes_scope)scopeNodes_stack.peek()).node.listOfStruct.put("_gen_struct_"+(ID),((nodes_scope)nodes_stack.peek()).node);
                      									(struct_or_union_specifier74!=null?struct_or_union_specifier74.n:null).structTypeName = "_gen_struct_"+ID;
                      								//}
                      							}else{
                      								((scopeNodes_scope)scopeNodes_stack.peek()).node.listOfStruct.put((struct_or_union_specifier74!=null?struct_or_union_specifier74.structTypeName:null),((nodes_scope)nodes_stack.peek()).node);
                      							}
                      							//System.out.println("ddddddddddddddddddd" + ((nodes_scope)nodes_stack.peek()).node);
                      						}
                      					
                    }

                    }
                    break;
                case 10 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:574:4: enum_specifier
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_enum_specifier_in_type_specifier1096);
                    enum_specifier75=enum_specifier();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, enum_specifier75.getTree());
                    if ( state.backtracking==0 ) {
                      typeTemp ="enum";
                    }

                    }
                    break;
                case 11 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:575:4: type_id
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_type_id_in_type_specifier1105);
                    type_id76=type_id();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, type_id76.getTree());
                    if ( state.backtracking==0 ) {
                      typeTemp =(type_id76!=null?input.toString(type_id76.start,type_id76.stop):null);
                    }

                    }
                    break;
                case 12 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:576:4: declared_id
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_declared_id_in_type_specifier1116);
                    declared_id77=declared_id();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, declared_id77.getTree());
                    if ( state.backtracking==0 ) {
                      typeTemp =(declared_id77!=null?input.toString(declared_id77.start,declared_id77.stop):null);
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {

              	if (typeTemp.equals("") == false) {
              		if (isFromFunction_stack.size() > 0 && ((isFromFunction_scope)isFromFunction_stack.peek()).data == true) {
              			((nodes_scope)nodes_stack.peek()).node.returnType=typeTemp;
              		}else{
              			        
                      		if (addtype) {
                      			preType = typeTemp.replaceAll(" ","");
              				((nodes_scope)nodes_stack.peek()).node.declaredType.add(preType);
              				
              			}
              			
              		}	
              	}

            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 12, type_specifier_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "type_specifier"

    public static class type_id_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "type_id"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:579:1: type_id : {...}? IDENTIFIER ;
    public final PretCParser.type_id_return type_id() throws RecognitionException {
        PretCParser.type_id_return retval = new PretCParser.type_id_return();
        retval.start = input.LT(1);
        int type_id_StartIndex = input.index();
        CommonTree root_0 = null;

        Token IDENTIFIER78=null;

        CommonTree IDENTIFIER78_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 13) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:580:5: ({...}? IDENTIFIER )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:580:9: {...}? IDENTIFIER
            {
            root_0 = (CommonTree)adaptor.nil();

            if ( !((isTypeName(input.LT(1).getText()))) ) {
                if (state.backtracking>0) {state.failed=true; return retval;}
                throw new FailedPredicateException(input, "type_id", "isTypeName(input.LT(1).getText())");
            }
            IDENTIFIER78=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_type_id1137); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            IDENTIFIER78_tree = (CommonTree)adaptor.create(IDENTIFIER78);
            adaptor.addChild(root_0, IDENTIFIER78_tree);
            }

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 13, type_id_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "type_id"

    public static class declared_id_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "declared_id"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:584:1: declared_id : {...}? IDENTIFIER ;
    public final PretCParser.declared_id_return declared_id() throws RecognitionException {
        PretCParser.declared_id_return retval = new PretCParser.declared_id_return();
        retval.start = input.LT(1);
        int declared_id_StartIndex = input.index();
        CommonTree root_0 = null;

        Token IDENTIFIER79=null;

        CommonTree IDENTIFIER79_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 14) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:585:5: ({...}? IDENTIFIER )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:585:9: {...}? IDENTIFIER
            {
            root_0 = (CommonTree)adaptor.nil();

            if ( !((PRETdefinedtable.contains(input.LT(1).getText()))) ) {
                if (state.backtracking>0) {state.failed=true; return retval;}
                throw new FailedPredicateException(input, "declared_id", "PRETdefinedtable.contains(input.LT(1).getText())");
            }
            IDENTIFIER79=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_declared_id1164); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            IDENTIFIER79_tree = (CommonTree)adaptor.create(IDENTIFIER79);
            adaptor.addChild(root_0, IDENTIFIER79_tree);
            }

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 14, declared_id_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "declared_id"

    public static class struct_or_union_specifier_return extends ParserRuleReturnScope {
        public String typeTemp;
        public StatementNode n;
        public String structTypeName;
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "struct_or_union_specifier"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:589:1: struct_or_union_specifier returns [String typeTemp, StatementNode n, String structTypeName] options {k=3; } : ( struct_or_union ( IDENTIFIER )? '{' struct_declaration_list '}' | struct_or_union IDENTIFIER );
    public final PretCParser.struct_or_union_specifier_return struct_or_union_specifier() throws RecognitionException {
        Symbols_stack.push(new Symbols_scope());
        nodes_stack.push(new nodes_scope());

        PretCParser.struct_or_union_specifier_return retval = new PretCParser.struct_or_union_specifier_return();
        retval.start = input.LT(1);
        int struct_or_union_specifier_StartIndex = input.index();
        CommonTree root_0 = null;

        Token IDENTIFIER81=null;
        Token char_literal82=null;
        Token char_literal84=null;
        Token IDENTIFIER86=null;
        PretCParser.struct_or_union_return struct_or_union80 = null;

        PretCParser.struct_declaration_list_return struct_declaration_list83 = null;

        PretCParser.struct_or_union_return struct_or_union85 = null;


        CommonTree IDENTIFIER81_tree=null;
        CommonTree char_literal82_tree=null;
        CommonTree char_literal84_tree=null;
        CommonTree IDENTIFIER86_tree=null;


          retval.n =  new StatementNode();
          retval.n.type = "scopedVaraibles";	
          ((nodes_scope)nodes_stack.peek()).node = retval.n;
          ((Symbols_scope)Symbols_stack.peek()).types = new HashSet();
          retval.typeTemp = "";
          

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 15) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:600:2: ( struct_or_union ( IDENTIFIER )? '{' struct_declaration_list '}' | struct_or_union IDENTIFIER )
            int alt26=2;
            alt26 = dfa26.predict(input);
            switch (alt26) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:600:4: struct_or_union ( IDENTIFIER )? '{' struct_declaration_list '}'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_struct_or_union_in_struct_or_union_specifier1209);
                    struct_or_union80=struct_or_union();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, struct_or_union80.getTree());
                    if ( state.backtracking==0 ) {
                      retval.typeTemp = (struct_or_union80!=null?struct_or_union80.typeTemp:null);
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:600:61: ( IDENTIFIER )?
                    int alt25=2;
                    int LA25_0 = input.LA(1);

                    if ( (LA25_0==IDENTIFIER) ) {
                        alt25=1;
                    }
                    switch (alt25) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:600:62: IDENTIFIER
                            {
                            IDENTIFIER81=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_struct_or_union_specifier1214); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            IDENTIFIER81_tree = (CommonTree)adaptor.create(IDENTIFIER81);
                            adaptor.addChild(root_0, IDENTIFIER81_tree);
                            }
                            if ( state.backtracking==0 ) {
                              retval.structTypeName = (IDENTIFIER81!=null?IDENTIFIER81.getText():null);
                            }

                            }
                            break;

                    }

                    char_literal82=(Token)match(input,65,FOLLOW_65_in_struct_or_union_specifier1219); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal82_tree = (CommonTree)adaptor.create(char_literal82);
                    adaptor.addChild(root_0, char_literal82_tree);
                    }
                    pushFollow(FOLLOW_struct_declaration_list_in_struct_or_union_specifier1221);
                    struct_declaration_list83=struct_declaration_list();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, struct_declaration_list83.getTree());
                    char_literal84=(Token)match(input,66,FOLLOW_66_in_struct_or_union_specifier1223); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal84_tree = (CommonTree)adaptor.create(char_literal84);
                    adaptor.addChild(root_0, char_literal84_tree);
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:601:4: struct_or_union IDENTIFIER
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_struct_or_union_in_struct_or_union_specifier1228);
                    struct_or_union85=struct_or_union();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, struct_or_union85.getTree());
                    if ( state.backtracking==0 ) {
                      retval.typeTemp = (struct_or_union85!=null?struct_or_union85.typeTemp:null);
                    }
                    IDENTIFIER86=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_struct_or_union_specifier1232); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    IDENTIFIER86_tree = (CommonTree)adaptor.create(IDENTIFIER86);
                    adaptor.addChild(root_0, IDENTIFIER86_tree);
                    }
                    if ( state.backtracking==0 ) {
                      retval.structTypeName = (IDENTIFIER86!=null?IDENTIFIER86.getText():null);
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 15, struct_or_union_specifier_StartIndex); }
            Symbols_stack.pop();
            nodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "struct_or_union_specifier"

    public static class struct_or_union_return extends ParserRuleReturnScope {
        public String typeTemp;
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "struct_or_union"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:604:1: struct_or_union returns [String typeTemp] : ( 'struct' | 'union' );
    public final PretCParser.struct_or_union_return struct_or_union() throws RecognitionException {
        PretCParser.struct_or_union_return retval = new PretCParser.struct_or_union_return();
        retval.start = input.LT(1);
        int struct_or_union_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal87=null;
        Token string_literal88=null;

        CommonTree string_literal87_tree=null;
        CommonTree string_literal88_tree=null;


        	retval.typeTemp = "";

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 16) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:617:2: ( 'struct' | 'union' )
            int alt27=2;
            int LA27_0 = input.LA(1);

            if ( (LA27_0==67) ) {
                alt27=1;
            }
            else if ( (LA27_0==68) ) {
                alt27=2;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 27, 0, input);

                throw nvae;
            }
            switch (alt27) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:617:4: 'struct'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal87=(Token)match(input,67,FOLLOW_67_in_struct_or_union1253); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal87_tree = (CommonTree)adaptor.create(string_literal87);
                    adaptor.addChild(root_0, string_literal87_tree);
                    }
                    if ( state.backtracking==0 ) {
                      retval.typeTemp ="struct";
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:618:4: 'union'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal88=(Token)match(input,68,FOLLOW_68_in_struct_or_union1260); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal88_tree = (CommonTree)adaptor.create(string_literal88);
                    adaptor.addChild(root_0, string_literal88_tree);
                    }
                    if ( state.backtracking==0 ) {
                      retval.typeTemp ="union";
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 16, struct_or_union_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "struct_or_union"

    public static class struct_declaration_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "struct_declaration_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:621:1: struct_declaration_list : struct_declaration ( struct_declaration )* ;
    public final PretCParser.struct_declaration_list_return struct_declaration_list() throws RecognitionException {
        scopeNodes_stack.push(new scopeNodes_scope());

        PretCParser.struct_declaration_list_return retval = new PretCParser.struct_declaration_list_return();
        retval.start = input.LT(1);
        int struct_declaration_list_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.struct_declaration_return struct_declaration89 = null;

        PretCParser.struct_declaration_return struct_declaration90 = null;




          long previousScope = currentScope;
          //dont put in init , init can prograss more than once when findingin which is right


        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 17) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:634:2: ( struct_declaration ( struct_declaration )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:634:4: struct_declaration ( struct_declaration )*
            {
            root_0 = (CommonTree)adaptor.nil();

            if ( state.backtracking==0 ) {
                
              		currentScope = ++scopeCount;
              		((scopeNodes_scope)scopeNodes_stack.peek()).node = new ScopeNode(currentScope);
              		((scopeNodes_scope)scopeNodes_stack.peek()).node.parentID = previousScope;
              	  
            }
            pushFollow(FOLLOW_struct_declaration_in_struct_declaration_list1291);
            struct_declaration89=struct_declaration();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, struct_declaration89.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:638:25: ( struct_declaration )*
            loop28:
            do {
                int alt28=2;
                alt28 = dfa28.predict(input);
                switch (alt28) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:638:26: struct_declaration
            	    {
            	    if ( state.backtracking==0 ) {
            	      ((nodes_scope)nodes_stack.peek()).node.constantStatement.add(new ArrayList<String>());
            	    }
            	    pushFollow(FOLLOW_struct_declaration_in_struct_declaration_list1296);
            	    struct_declaration90=struct_declaration();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, struct_declaration90.getTree());

            	    }
            	    break;

            	default :
            	    break loop28;
                }
            } while (true);

            if ( state.backtracking==0 ) {

              	 	((nodes_scope)nodes_stack.peek()).node.scopeID = currentScope;
              	  
            }

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {

                scopeList.put(currentScope,((scopeNodes_scope)scopeNodes_stack.peek()).node);
               // System.out.println("A"+currentScope);
                currentScope = previousScope;
                

            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 17, struct_declaration_list_StartIndex); }
            scopeNodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "struct_declaration_list"

    public static class struct_declaration_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "struct_declaration"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:644:1: struct_declaration : specifier_qualifier_list ( struct_declarator_list )? ';' ;
    public final PretCParser.struct_declaration_return struct_declaration() throws RecognitionException {
        PretCParser.struct_declaration_return retval = new PretCParser.struct_declaration_return();
        retval.start = input.LT(1);
        int struct_declaration_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal93=null;
        PretCParser.specifier_qualifier_list_return specifier_qualifier_list91 = null;

        PretCParser.struct_declarator_list_return struct_declarator_list92 = null;


        CommonTree char_literal93_tree=null;


        	boolean hasName = false;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 18) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:648:2: ( specifier_qualifier_list ( struct_declarator_list )? ';' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:648:4: specifier_qualifier_list ( struct_declarator_list )? ';'
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_specifier_qualifier_list_in_struct_declaration1318);
            specifier_qualifier_list91=specifier_qualifier_list();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, specifier_qualifier_list91.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:648:29: ( struct_declarator_list )?
            int alt29=2;
            int LA29_0 = input.LA(1);

            if ( (LA29_0==IDENTIFIER||LA29_0==49||LA29_0==69||LA29_0==75) ) {
                alt29=1;
            }
            switch (alt29) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:648:30: struct_declarator_list
                    {
                    pushFollow(FOLLOW_struct_declarator_list_in_struct_declaration1321);
                    struct_declarator_list92=struct_declarator_list();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, struct_declarator_list92.getTree());
                    if ( state.backtracking==0 ) {
                      hasName = true;
                    }

                    }
                    break;

            }

            char_literal93=(Token)match(input,41,FOLLOW_41_in_struct_declaration1325); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal93_tree = (CommonTree)adaptor.create(char_literal93);
            adaptor.addChild(root_0, char_literal93_tree);
            }
            if ( state.backtracking==0 ) {

              		if (hasName == false) {
              			((nodes_scope)nodes_stack.peek()).node.name.add("");	
              		}
              	
            }

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 18, struct_declaration_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "struct_declaration"

    public static class specifier_qualifier_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "specifier_qualifier_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:656:1: specifier_qualifier_list : ( type_qualifier | type_specifier )+ ;
    public final PretCParser.specifier_qualifier_list_return specifier_qualifier_list() throws RecognitionException {
        PretCParser.specifier_qualifier_list_return retval = new PretCParser.specifier_qualifier_list_return();
        retval.start = input.LT(1);
        int specifier_qualifier_list_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.type_qualifier_return type_qualifier94 = null;

        PretCParser.type_specifier_return type_specifier95 = null;




        	String specifiers = "";

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 19) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:660:2: ( ( type_qualifier | type_specifier )+ )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:660:4: ( type_qualifier | type_specifier )+
            {
            root_0 = (CommonTree)adaptor.nil();

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:660:4: ( type_qualifier | type_specifier )+
            int cnt30=0;
            loop30:
            do {
                int alt30=3;
                alt30 = dfa30.predict(input);
                switch (alt30) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:660:6: type_qualifier
            	    {
            	    pushFollow(FOLLOW_type_qualifier_in_specifier_qualifier_list1346);
            	    type_qualifier94=type_qualifier();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, type_qualifier94.getTree());
            	    if ( state.backtracking==0 ) {
            	      specifiers+=(type_qualifier94!=null?input.toString(type_qualifier94.start,type_qualifier94.stop):null);
            	    }

            	    }
            	    break;
            	case 2 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:660:59: type_specifier
            	    {
            	    pushFollow(FOLLOW_type_specifier_in_specifier_qualifier_list1352);
            	    type_specifier95=type_specifier();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, type_specifier95.getTree());
            	    if ( state.backtracking==0 ) {
            	      specifiers+=(type_specifier95!=null?input.toString(type_specifier95.start,type_specifier95.stop):null);
            	    }

            	    }
            	    break;

            	default :
            	    if ( cnt30 >= 1 ) break loop30;
            	    if (state.backtracking>0) {state.failed=true; return retval;}
                        EarlyExitException eee =
                            new EarlyExitException(30, input);
                        throw eee;
                }
                cnt30++;
            } while (true);

            if ( state.backtracking==0 ) {
              ((nodes_scope)nodes_stack.peek()).node.varSpecifiers.add(specifiers);preVarSpecifiers = specifiers; 
            }

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 19, specifier_qualifier_list_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "specifier_qualifier_list"

    public static class struct_declarator_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "struct_declarator_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:664:1: struct_declarator_list : struct_declarator ( ',' struct_declarator )* ;
    public final PretCParser.struct_declarator_list_return struct_declarator_list() throws RecognitionException {
        PretCParser.struct_declarator_list_return retval = new PretCParser.struct_declarator_list_return();
        retval.start = input.LT(1);
        int struct_declarator_list_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal97=null;
        PretCParser.struct_declarator_return struct_declarator96 = null;

        PretCParser.struct_declarator_return struct_declarator98 = null;


        CommonTree char_literal97_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 20) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:665:2: ( struct_declarator ( ',' struct_declarator )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:665:4: struct_declarator ( ',' struct_declarator )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_struct_declarator_in_struct_declarator_list1371);
            struct_declarator96=struct_declarator();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, struct_declarator96.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:665:22: ( ',' struct_declarator )*
            loop31:
            do {
                int alt31=2;
                int LA31_0 = input.LA(1);

                if ( (LA31_0==45) ) {
                    alt31=1;
                }


                switch (alt31) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:665:23: ',' struct_declarator
            	    {
            	    char_literal97=(Token)match(input,45,FOLLOW_45_in_struct_declarator_list1374); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal97_tree = (CommonTree)adaptor.create(char_literal97);
            	    adaptor.addChild(root_0, char_literal97_tree);
            	    }
            	    if ( state.backtracking==0 ) {
            	      ((nodes_scope)nodes_stack.peek()).node.constantStatement.add(new ArrayList<String>());
            	    }
            	    pushFollow(FOLLOW_struct_declarator_in_struct_declarator_list1379);
            	    struct_declarator98=struct_declarator();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, struct_declarator98.getTree());
            	    if ( state.backtracking==0 ) {
            	      ((nodes_scope)nodes_stack.peek()).node.declaredType.add(preType);((nodes_scope)nodes_stack.peek()).node.varSpecifiers.add(preVarSpecifiers);
            	    }

            	    }
            	    break;

            	default :
            	    break loop31;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 20, struct_declarator_list_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "struct_declarator_list"

    public static class struct_declarator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "struct_declarator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:668:1: struct_declarator : ( declarator ( ':' constant_expression )? ( range_declarator )? | ':' constant_expression );
    public final PretCParser.struct_declarator_return struct_declarator() throws RecognitionException {
        PretCParser.struct_declarator_return retval = new PretCParser.struct_declarator_return();
        retval.start = input.LT(1);
        int struct_declarator_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal100=null;
        Token char_literal103=null;
        PretCParser.declarator_return declarator99 = null;

        PretCParser.constant_expression_return constant_expression101 = null;

        PretCParser.range_declarator_return range_declarator102 = null;

        PretCParser.constant_expression_return constant_expression104 = null;


        CommonTree char_literal100_tree=null;
        CommonTree char_literal103_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 21) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:669:2: ( declarator ( ':' constant_expression )? ( range_declarator )? | ':' constant_expression )
            int alt34=2;
            int LA34_0 = input.LA(1);

            if ( (LA34_0==IDENTIFIER||LA34_0==49||LA34_0==75) ) {
                alt34=1;
            }
            else if ( (LA34_0==69) ) {
                alt34=2;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 34, 0, input);

                throw nvae;
            }
            switch (alt34) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:669:4: declarator ( ':' constant_expression )? ( range_declarator )?
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_declarator_in_struct_declarator1394);
                    declarator99=declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, declarator99.getTree());
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:669:15: ( ':' constant_expression )?
                    int alt32=2;
                    int LA32_0 = input.LA(1);

                    if ( (LA32_0==69) ) {
                        alt32=1;
                    }
                    switch (alt32) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:669:16: ':' constant_expression
                            {
                            char_literal100=(Token)match(input,69,FOLLOW_69_in_struct_declarator1397); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            char_literal100_tree = (CommonTree)adaptor.create(char_literal100);
                            adaptor.addChild(root_0, char_literal100_tree);
                            }
                            pushFollow(FOLLOW_constant_expression_in_struct_declarator1399);
                            constant_expression101=constant_expression();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) adaptor.addChild(root_0, constant_expression101.getTree());

                            }
                            break;

                    }

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:669:43: ( range_declarator )?
                    int alt33=2;
                    int LA33_0 = input.LA(1);

                    if ( (LA33_0==46) ) {
                        alt33=1;
                    }
                    switch (alt33) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: range_declarator
                            {
                            pushFollow(FOLLOW_range_declarator_in_struct_declarator1404);
                            range_declarator102=range_declarator();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) adaptor.addChild(root_0, range_declarator102.getTree());

                            }
                            break;

                    }

                    if ( state.backtracking==0 ) {

                      			//System.out.println("ddddddddddd"+(declarator99!=null?input.toString(declarator99.start,declarator99.stop):null));
                      			((nodes_scope)nodes_stack.peek()).node.name.add((declarator99!=null?input.toString(declarator99.start,declarator99.stop):null)); 
                      			((scopeNodes_scope)scopeNodes_stack.peek()).node.variableMapPut((declarator99!=null?input.toString(declarator99.start,declarator99.stop):null),((nodes_scope)nodes_stack.peek()).node);
                      			if ((constant_expression101!=null?input.toString(constant_expression101.start,constant_expression101.stop):null) != null) {
                      				((nodes_scope)nodes_stack.peek()).node.constantStatement.get(((nodes_scope)nodes_stack.peek()).node.constantStatement.size()-1).add((constant_expression101!=null?input.toString(constant_expression101.start,constant_expression101.stop):null));
                      			}/*else{
                      				((nodes_scope)nodes_stack.peek()).node.constantStatement.add("UNDEFINED");
                      			}*/
                      			
                      			//((nodes_scope)nodes_stack.peek()).node.constantStatement.add((constant_expression101!=null?input.toString(constant_expression101.start,constant_expression101.stop):null));
                      		
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:682:4: ':' constant_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal103=(Token)match(input,69,FOLLOW_69_in_struct_declarator1415); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal103_tree = (CommonTree)adaptor.create(char_literal103);
                    adaptor.addChild(root_0, char_literal103_tree);
                    }
                    pushFollow(FOLLOW_constant_expression_in_struct_declarator1417);
                    constant_expression104=constant_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, constant_expression104.getTree());

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 21, struct_declarator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "struct_declarator"

    public static class enum_specifier_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "enum_specifier"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:685:1: enum_specifier options {k=3; } : ( 'enum' '{' enumerator_list '}' | 'enum' IDENTIFIER '{' enumerator_list '}' | 'enum' IDENTIFIER );
    public final PretCParser.enum_specifier_return enum_specifier() throws RecognitionException {
        PretCParser.enum_specifier_return retval = new PretCParser.enum_specifier_return();
        retval.start = input.LT(1);
        int enum_specifier_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal105=null;
        Token char_literal106=null;
        Token char_literal108=null;
        Token string_literal109=null;
        Token IDENTIFIER110=null;
        Token char_literal111=null;
        Token char_literal113=null;
        Token string_literal114=null;
        Token IDENTIFIER115=null;
        PretCParser.enumerator_list_return enumerator_list107 = null;

        PretCParser.enumerator_list_return enumerator_list112 = null;


        CommonTree string_literal105_tree=null;
        CommonTree char_literal106_tree=null;
        CommonTree char_literal108_tree=null;
        CommonTree string_literal109_tree=null;
        CommonTree IDENTIFIER110_tree=null;
        CommonTree char_literal111_tree=null;
        CommonTree char_literal113_tree=null;
        CommonTree string_literal114_tree=null;
        CommonTree IDENTIFIER115_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 22) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:687:2: ( 'enum' '{' enumerator_list '}' | 'enum' IDENTIFIER '{' enumerator_list '}' | 'enum' IDENTIFIER )
            int alt35=3;
            alt35 = dfa35.predict(input);
            switch (alt35) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:687:4: 'enum' '{' enumerator_list '}'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal105=(Token)match(input,70,FOLLOW_70_in_enum_specifier1436); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal105_tree = (CommonTree)adaptor.create(string_literal105);
                    adaptor.addChild(root_0, string_literal105_tree);
                    }
                    char_literal106=(Token)match(input,65,FOLLOW_65_in_enum_specifier1438); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal106_tree = (CommonTree)adaptor.create(char_literal106);
                    adaptor.addChild(root_0, char_literal106_tree);
                    }
                    pushFollow(FOLLOW_enumerator_list_in_enum_specifier1440);
                    enumerator_list107=enumerator_list();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, enumerator_list107.getTree());
                    char_literal108=(Token)match(input,66,FOLLOW_66_in_enum_specifier1442); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal108_tree = (CommonTree)adaptor.create(char_literal108);
                    adaptor.addChild(root_0, char_literal108_tree);
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:688:4: 'enum' IDENTIFIER '{' enumerator_list '}'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal109=(Token)match(input,70,FOLLOW_70_in_enum_specifier1448); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal109_tree = (CommonTree)adaptor.create(string_literal109);
                    adaptor.addChild(root_0, string_literal109_tree);
                    }
                    IDENTIFIER110=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_enum_specifier1450); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    IDENTIFIER110_tree = (CommonTree)adaptor.create(IDENTIFIER110);
                    adaptor.addChild(root_0, IDENTIFIER110_tree);
                    }
                    char_literal111=(Token)match(input,65,FOLLOW_65_in_enum_specifier1452); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal111_tree = (CommonTree)adaptor.create(char_literal111);
                    adaptor.addChild(root_0, char_literal111_tree);
                    }
                    pushFollow(FOLLOW_enumerator_list_in_enum_specifier1454);
                    enumerator_list112=enumerator_list();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, enumerator_list112.getTree());
                    char_literal113=(Token)match(input,66,FOLLOW_66_in_enum_specifier1456); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal113_tree = (CommonTree)adaptor.create(char_literal113);
                    adaptor.addChild(root_0, char_literal113_tree);
                    }

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:689:4: 'enum' IDENTIFIER
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal114=(Token)match(input,70,FOLLOW_70_in_enum_specifier1461); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal114_tree = (CommonTree)adaptor.create(string_literal114);
                    adaptor.addChild(root_0, string_literal114_tree);
                    }
                    IDENTIFIER115=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_enum_specifier1463); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    IDENTIFIER115_tree = (CommonTree)adaptor.create(IDENTIFIER115);
                    adaptor.addChild(root_0, IDENTIFIER115_tree);
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 22, enum_specifier_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "enum_specifier"

    public static class enumerator_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "enumerator_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:692:1: enumerator_list : enumerator ( ',' enumerator )* ;
    public final PretCParser.enumerator_list_return enumerator_list() throws RecognitionException {
        PretCParser.enumerator_list_return retval = new PretCParser.enumerator_list_return();
        retval.start = input.LT(1);
        int enumerator_list_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal117=null;
        PretCParser.enumerator_return enumerator116 = null;

        PretCParser.enumerator_return enumerator118 = null;


        CommonTree char_literal117_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 23) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:693:2: ( enumerator ( ',' enumerator )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:693:4: enumerator ( ',' enumerator )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_enumerator_in_enumerator_list1474);
            enumerator116=enumerator();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, enumerator116.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:693:15: ( ',' enumerator )*
            loop36:
            do {
                int alt36=2;
                int LA36_0 = input.LA(1);

                if ( (LA36_0==45) ) {
                    alt36=1;
                }


                switch (alt36) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:693:16: ',' enumerator
            	    {
            	    char_literal117=(Token)match(input,45,FOLLOW_45_in_enumerator_list1477); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal117_tree = (CommonTree)adaptor.create(char_literal117);
            	    adaptor.addChild(root_0, char_literal117_tree);
            	    }
            	    pushFollow(FOLLOW_enumerator_in_enumerator_list1479);
            	    enumerator118=enumerator();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, enumerator118.getTree());

            	    }
            	    break;

            	default :
            	    break loop36;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 23, enumerator_list_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "enumerator_list"

    public static class enumerator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "enumerator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:696:1: enumerator : IDENTIFIER ( '=' constant_expression )? ;
    public final PretCParser.enumerator_return enumerator() throws RecognitionException {
        PretCParser.enumerator_return retval = new PretCParser.enumerator_return();
        retval.start = input.LT(1);
        int enumerator_StartIndex = input.index();
        CommonTree root_0 = null;

        Token IDENTIFIER119=null;
        Token char_literal120=null;
        PretCParser.constant_expression_return constant_expression121 = null;


        CommonTree IDENTIFIER119_tree=null;
        CommonTree char_literal120_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 24) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:697:2: ( IDENTIFIER ( '=' constant_expression )? )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:697:4: IDENTIFIER ( '=' constant_expression )?
            {
            root_0 = (CommonTree)adaptor.nil();

            IDENTIFIER119=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_enumerator1492); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            IDENTIFIER119_tree = (CommonTree)adaptor.create(IDENTIFIER119);
            adaptor.addChild(root_0, IDENTIFIER119_tree);
            }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:697:15: ( '=' constant_expression )?
            int alt37=2;
            int LA37_0 = input.LA(1);

            if ( (LA37_0==44) ) {
                alt37=1;
            }
            switch (alt37) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:697:16: '=' constant_expression
                    {
                    char_literal120=(Token)match(input,44,FOLLOW_44_in_enumerator1495); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal120_tree = (CommonTree)adaptor.create(char_literal120);
                    adaptor.addChild(root_0, char_literal120_tree);
                    }
                    pushFollow(FOLLOW_constant_expression_in_enumerator1497);
                    constant_expression121=constant_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, constant_expression121.getTree());

                    }
                    break;

            }


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 24, enumerator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "enumerator"

    public static class type_qualifier_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "type_qualifier"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:700:1: type_qualifier : ( 'const' | 'volatile' );
    public final PretCParser.type_qualifier_return type_qualifier() throws RecognitionException {
        PretCParser.type_qualifier_return retval = new PretCParser.type_qualifier_return();
        retval.start = input.LT(1);
        int type_qualifier_StartIndex = input.index();
        CommonTree root_0 = null;

        Token set122=null;

        CommonTree set122_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 25) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:701:2: ( 'const' | 'volatile' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
            {
            root_0 = (CommonTree)adaptor.nil();

            set122=(Token)input.LT(1);
            if ( (input.LA(1)>=71 && input.LA(1)<=72) ) {
                input.consume();
                if ( state.backtracking==0 ) adaptor.addChild(root_0, (CommonTree)adaptor.create(set122));
                state.errorRecovery=false;state.failed=false;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                MismatchedSetException mse = new MismatchedSetException(null,input);
                throw mse;
            }


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 25, type_qualifier_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "type_qualifier"

    public static class declarator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "declarator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:705:1: declarator : ( ( pointer )? direct_declarator | pointer );
    public final PretCParser.declarator_return declarator() throws RecognitionException {
        PretCParser.declarator_return retval = new PretCParser.declarator_return();
        retval.start = input.LT(1);
        int declarator_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.pointer_return pointer123 = null;

        PretCParser.direct_declarator_return direct_declarator124 = null;

        PretCParser.pointer_return pointer125 = null;



        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 26) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:706:2: ( ( pointer )? direct_declarator | pointer )
            int alt39=2;
            alt39 = dfa39.predict(input);
            switch (alt39) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:706:4: ( pointer )? direct_declarator
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:706:4: ( pointer )?
                    int alt38=2;
                    int LA38_0 = input.LA(1);

                    if ( (LA38_0==75) ) {
                        alt38=1;
                    }
                    switch (alt38) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: pointer
                            {
                            pushFollow(FOLLOW_pointer_in_declarator1526);
                            pointer123=pointer();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) adaptor.addChild(root_0, pointer123.getTree());

                            }
                            break;

                    }

                    pushFollow(FOLLOW_direct_declarator_in_declarator1529);
                    direct_declarator124=direct_declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, direct_declarator124.getTree());

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:707:4: pointer
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_pointer_in_declarator1534);
                    pointer125=pointer();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, pointer125.getTree());

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 26, declarator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "declarator"

    public static class direct_declarator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "direct_declarator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:710:1: direct_declarator : ( IDENTIFIER ( declarator_suffix )* -> ( declarator_suffix )* | '(' declarator ')' ( declarator_suffix )* -> '(' declarator ')' ( declarator_suffix )* );
    public final PretCParser.direct_declarator_return direct_declarator() throws RecognitionException {
        PretCParser.direct_declarator_return retval = new PretCParser.direct_declarator_return();
        retval.start = input.LT(1);
        int direct_declarator_StartIndex = input.index();
        CommonTree root_0 = null;

        Token IDENTIFIER126=null;
        Token char_literal128=null;
        Token char_literal130=null;
        PretCParser.declarator_suffix_return declarator_suffix127 = null;

        PretCParser.declarator_return declarator129 = null;

        PretCParser.declarator_suffix_return declarator_suffix131 = null;


        CommonTree IDENTIFIER126_tree=null;
        CommonTree char_literal128_tree=null;
        CommonTree char_literal130_tree=null;
        RewriteRuleTokenStream stream_49=new RewriteRuleTokenStream(adaptor,"token 49");
        RewriteRuleTokenStream stream_51=new RewriteRuleTokenStream(adaptor,"token 51");
        RewriteRuleTokenStream stream_IDENTIFIER=new RewriteRuleTokenStream(adaptor,"token IDENTIFIER");
        RewriteRuleSubtreeStream stream_declarator=new RewriteRuleSubtreeStream(adaptor,"rule declarator");
        RewriteRuleSubtreeStream stream_declarator_suffix=new RewriteRuleSubtreeStream(adaptor,"rule declarator_suffix");
        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 27) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:711:2: ( IDENTIFIER ( declarator_suffix )* -> ( declarator_suffix )* | '(' declarator ')' ( declarator_suffix )* -> '(' declarator ')' ( declarator_suffix )* )
            int alt42=2;
            int LA42_0 = input.LA(1);

            if ( (LA42_0==IDENTIFIER) ) {
                alt42=1;
            }
            else if ( (LA42_0==49) ) {
                alt42=2;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 42, 0, input);

                throw nvae;
            }
            switch (alt42) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:711:7: IDENTIFIER ( declarator_suffix )*
                    {
                    IDENTIFIER126=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_direct_declarator1548); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_IDENTIFIER.add(IDENTIFIER126);

                    if ( state.backtracking==0 ) {

                      			if (is_stack.size()>0&&((is_scope)is_stack.peek()).typeDef) {
                      				((Symbols_scope)Symbols_stack.peek()).types.add((IDENTIFIER126!=null?IDENTIFIER126.getText():null));
                      				((scopeNodes_scope)scopeNodes_stack.peek()).node.listOfTypeDef.put((IDENTIFIER126!=null?IDENTIFIER126.getText():null),((nodes_scope)nodes_stack.peek()).node);
                      				System.out.println("define type "+(IDENTIFIER126!=null?IDENTIFIER126.getText():null));
                      			}
                      			
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:719:4: ( declarator_suffix )*
                    loop40:
                    do {
                        int alt40=2;
                        alt40 = dfa40.predict(input);
                        switch (alt40) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: declarator_suffix
                    	    {
                    	    pushFollow(FOLLOW_declarator_suffix_in_direct_declarator1559);
                    	    declarator_suffix127=declarator_suffix();

                    	    state._fsp--;
                    	    if (state.failed) return retval;
                    	    if ( state.backtracking==0 ) stream_declarator_suffix.add(declarator_suffix127.getTree());

                    	    }
                    	    break;

                    	default :
                    	    break loop40;
                        }
                    } while (true);



                    // AST REWRITE
                    // elements: declarator_suffix
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 720:4: -> ( declarator_suffix )*
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:720:7: ( declarator_suffix )*
                        while ( stream_declarator_suffix.hasNext() ) {
                            adaptor.addChild(root_0, stream_declarator_suffix.nextTree());

                        }
                        stream_declarator_suffix.reset();

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:722:3: '(' declarator ')' ( declarator_suffix )*
                    {
                    char_literal128=(Token)match(input,49,FOLLOW_49_in_direct_declarator1578); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_49.add(char_literal128);

                    pushFollow(FOLLOW_declarator_in_direct_declarator1580);
                    declarator129=declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_declarator.add(declarator129.getTree());
                    char_literal130=(Token)match(input,51,FOLLOW_51_in_direct_declarator1582); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_51.add(char_literal130);

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:722:22: ( declarator_suffix )*
                    loop41:
                    do {
                        int alt41=2;
                        alt41 = dfa41.predict(input);
                        switch (alt41) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: declarator_suffix
                    	    {
                    	    pushFollow(FOLLOW_declarator_suffix_in_direct_declarator1584);
                    	    declarator_suffix131=declarator_suffix();

                    	    state._fsp--;
                    	    if (state.failed) return retval;
                    	    if ( state.backtracking==0 ) stream_declarator_suffix.add(declarator_suffix131.getTree());

                    	    }
                    	    break;

                    	default :
                    	    break loop41;
                        }
                    } while (true);



                    // AST REWRITE
                    // elements: 49, declarator_suffix, declarator, 51
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 722:41: -> '(' declarator ')' ( declarator_suffix )*
                    {
                        adaptor.addChild(root_0, stream_49.nextNode());
                        adaptor.addChild(root_0, stream_declarator.nextTree());
                        adaptor.addChild(root_0, stream_51.nextNode());
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:722:63: ( declarator_suffix )*
                        while ( stream_declarator_suffix.hasNext() ) {
                            adaptor.addChild(root_0, stream_declarator_suffix.nextTree());

                        }
                        stream_declarator_suffix.reset();

                    }

                    retval.tree = root_0;}
                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 27, direct_declarator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "direct_declarator"

    public static class declarator_suffix_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "declarator_suffix"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:725:1: declarator_suffix : ( '[' constant_expression ']' | '[' ']' | '(' parameter_type_list ')' | '(' identifier_list ')' | '(' ')' );
    public final PretCParser.declarator_suffix_return declarator_suffix() throws RecognitionException {
        PretCParser.declarator_suffix_return retval = new PretCParser.declarator_suffix_return();
        retval.start = input.LT(1);
        int declarator_suffix_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal132=null;
        Token char_literal134=null;
        Token char_literal135=null;
        Token char_literal136=null;
        Token char_literal137=null;
        Token char_literal139=null;
        Token char_literal140=null;
        Token char_literal142=null;
        Token char_literal143=null;
        Token char_literal144=null;
        PretCParser.constant_expression_return constant_expression133 = null;

        PretCParser.parameter_type_list_return parameter_type_list138 = null;

        PretCParser.identifier_list_return identifier_list141 = null;


        CommonTree char_literal132_tree=null;
        CommonTree char_literal134_tree=null;
        CommonTree char_literal135_tree=null;
        CommonTree char_literal136_tree=null;
        CommonTree char_literal137_tree=null;
        CommonTree char_literal139_tree=null;
        CommonTree char_literal140_tree=null;
        CommonTree char_literal142_tree=null;
        CommonTree char_literal143_tree=null;
        CommonTree char_literal144_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 28) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:726:2: ( '[' constant_expression ']' | '[' ']' | '(' parameter_type_list ')' | '(' identifier_list ')' | '(' ')' )
            int alt43=5;
            alt43 = dfa43.predict(input);
            switch (alt43) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:726:6: '[' constant_expression ']'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal132=(Token)match(input,73,FOLLOW_73_in_declarator_suffix1609); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal132_tree = (CommonTree)adaptor.create(char_literal132);
                    adaptor.addChild(root_0, char_literal132_tree);
                    }
                    pushFollow(FOLLOW_constant_expression_in_declarator_suffix1611);
                    constant_expression133=constant_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, constant_expression133.getTree());
                    char_literal134=(Token)match(input,74,FOLLOW_74_in_declarator_suffix1613); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal134_tree = (CommonTree)adaptor.create(char_literal134);
                    adaptor.addChild(root_0, char_literal134_tree);
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:727:9: '[' ']'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal135=(Token)match(input,73,FOLLOW_73_in_declarator_suffix1623); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal135_tree = (CommonTree)adaptor.create(char_literal135);
                    adaptor.addChild(root_0, char_literal135_tree);
                    }
                    char_literal136=(Token)match(input,74,FOLLOW_74_in_declarator_suffix1625); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal136_tree = (CommonTree)adaptor.create(char_literal136);
                    adaptor.addChild(root_0, char_literal136_tree);
                    }

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:728:9: '(' parameter_type_list ')'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal137=(Token)match(input,49,FOLLOW_49_in_declarator_suffix1635); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal137_tree = (CommonTree)adaptor.create(char_literal137);
                    adaptor.addChild(root_0, char_literal137_tree);
                    }
                    pushFollow(FOLLOW_parameter_type_list_in_declarator_suffix1637);
                    parameter_type_list138=parameter_type_list();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, parameter_type_list138.getTree());
                    char_literal139=(Token)match(input,51,FOLLOW_51_in_declarator_suffix1639); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal139_tree = (CommonTree)adaptor.create(char_literal139);
                    adaptor.addChild(root_0, char_literal139_tree);
                    }

                    }
                    break;
                case 4 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:729:9: '(' identifier_list ')'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal140=(Token)match(input,49,FOLLOW_49_in_declarator_suffix1649); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal140_tree = (CommonTree)adaptor.create(char_literal140);
                    adaptor.addChild(root_0, char_literal140_tree);
                    }
                    pushFollow(FOLLOW_identifier_list_in_declarator_suffix1651);
                    identifier_list141=identifier_list();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, identifier_list141.getTree());
                    char_literal142=(Token)match(input,51,FOLLOW_51_in_declarator_suffix1653); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal142_tree = (CommonTree)adaptor.create(char_literal142);
                    adaptor.addChild(root_0, char_literal142_tree);
                    }

                    }
                    break;
                case 5 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:730:9: '(' ')'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal143=(Token)match(input,49,FOLLOW_49_in_declarator_suffix1663); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal143_tree = (CommonTree)adaptor.create(char_literal143);
                    adaptor.addChild(root_0, char_literal143_tree);
                    }
                    char_literal144=(Token)match(input,51,FOLLOW_51_in_declarator_suffix1665); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal144_tree = (CommonTree)adaptor.create(char_literal144);
                    adaptor.addChild(root_0, char_literal144_tree);
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 28, declarator_suffix_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "declarator_suffix"

    public static class pointer_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "pointer"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:733:1: pointer : ( '*' ( type_qualifier )+ ( pointer )? | '*' pointer | '*' );
    public final PretCParser.pointer_return pointer() throws RecognitionException {
        PretCParser.pointer_return retval = new PretCParser.pointer_return();
        retval.start = input.LT(1);
        int pointer_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal145=null;
        Token char_literal148=null;
        Token char_literal150=null;
        PretCParser.type_qualifier_return type_qualifier146 = null;

        PretCParser.pointer_return pointer147 = null;

        PretCParser.pointer_return pointer149 = null;


        CommonTree char_literal145_tree=null;
        CommonTree char_literal148_tree=null;
        CommonTree char_literal150_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 29) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:2: ( '*' ( type_qualifier )+ ( pointer )? | '*' pointer | '*' )
            int alt46=3;
            alt46 = dfa46.predict(input);
            switch (alt46) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:4: '*' ( type_qualifier )+ ( pointer )?
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal145=(Token)match(input,75,FOLLOW_75_in_pointer1676); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal145_tree = (CommonTree)adaptor.create(char_literal145);
                    adaptor.addChild(root_0, char_literal145_tree);
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:8: ( type_qualifier )+
                    int cnt44=0;
                    loop44:
                    do {
                        int alt44=2;
                        alt44 = dfa44.predict(input);
                        switch (alt44) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: type_qualifier
                    	    {
                    	    pushFollow(FOLLOW_type_qualifier_in_pointer1678);
                    	    type_qualifier146=type_qualifier();

                    	    state._fsp--;
                    	    if (state.failed) return retval;
                    	    if ( state.backtracking==0 ) adaptor.addChild(root_0, type_qualifier146.getTree());

                    	    }
                    	    break;

                    	default :
                    	    if ( cnt44 >= 1 ) break loop44;
                    	    if (state.backtracking>0) {state.failed=true; return retval;}
                                EarlyExitException eee =
                                    new EarlyExitException(44, input);
                                throw eee;
                        }
                        cnt44++;
                    } while (true);

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:24: ( pointer )?
                    int alt45=2;
                    alt45 = dfa45.predict(input);
                    switch (alt45) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: pointer
                            {
                            pushFollow(FOLLOW_pointer_in_pointer1681);
                            pointer147=pointer();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) adaptor.addChild(root_0, pointer147.getTree());

                            }
                            break;

                    }


                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:735:4: '*' pointer
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal148=(Token)match(input,75,FOLLOW_75_in_pointer1687); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal148_tree = (CommonTree)adaptor.create(char_literal148);
                    adaptor.addChild(root_0, char_literal148_tree);
                    }
                    pushFollow(FOLLOW_pointer_in_pointer1689);
                    pointer149=pointer();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, pointer149.getTree());

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:736:4: '*'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal150=(Token)match(input,75,FOLLOW_75_in_pointer1694); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal150_tree = (CommonTree)adaptor.create(char_literal150);
                    adaptor.addChild(root_0, char_literal150_tree);
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 29, pointer_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "pointer"

    public static class parameter_type_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "parameter_type_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:739:1: parameter_type_list : parameter_list ( ',' '...' )? ;
    public final PretCParser.parameter_type_list_return parameter_type_list() throws RecognitionException {
        PretCParser.parameter_type_list_return retval = new PretCParser.parameter_type_list_return();
        retval.start = input.LT(1);
        int parameter_type_list_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal152=null;
        Token string_literal153=null;
        PretCParser.parameter_list_return parameter_list151 = null;


        CommonTree char_literal152_tree=null;
        CommonTree string_literal153_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 30) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:740:2: ( parameter_list ( ',' '...' )? )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:740:4: parameter_list ( ',' '...' )?
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_parameter_list_in_parameter_type_list1705);
            parameter_list151=parameter_list();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, parameter_list151.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:740:19: ( ',' '...' )?
            int alt47=2;
            int LA47_0 = input.LA(1);

            if ( (LA47_0==45) ) {
                alt47=1;
            }
            switch (alt47) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:740:20: ',' '...'
                    {
                    char_literal152=(Token)match(input,45,FOLLOW_45_in_parameter_type_list1708); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal152_tree = (CommonTree)adaptor.create(char_literal152);
                    adaptor.addChild(root_0, char_literal152_tree);
                    }
                    string_literal153=(Token)match(input,76,FOLLOW_76_in_parameter_type_list1710); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal153_tree = (CommonTree)adaptor.create(string_literal153);
                    adaptor.addChild(root_0, string_literal153_tree);
                    }

                    }
                    break;

            }


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 30, parameter_type_list_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "parameter_type_list"

    public static class parameter_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "parameter_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:743:1: parameter_list : p1= parameter_declaration ( ',' p2= parameter_declaration )* ;
    public final PretCParser.parameter_list_return parameter_list() throws RecognitionException {
        PretCParser.parameter_list_return retval = new PretCParser.parameter_list_return();
        retval.start = input.LT(1);
        int parameter_list_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal154=null;
        PretCParser.parameter_declaration_return p1 = null;

        PretCParser.parameter_declaration_return p2 = null;


        CommonTree char_literal154_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 31) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:744:2: (p1= parameter_declaration ( ',' p2= parameter_declaration )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:744:4: p1= parameter_declaration ( ',' p2= parameter_declaration )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_parameter_declaration_in_parameter_list1726);
            p1=parameter_declaration();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, p1.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:748:3: ( ',' p2= parameter_declaration )*
            loop48:
            do {
                int alt48=2;
                alt48 = dfa48.predict(input);
                switch (alt48) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:748:4: ',' p2= parameter_declaration
            	    {
            	    char_literal154=(Token)match(input,45,FOLLOW_45_in_parameter_list1736); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal154_tree = (CommonTree)adaptor.create(char_literal154);
            	    adaptor.addChild(root_0, char_literal154_tree);
            	    }
            	    pushFollow(FOLLOW_parameter_declaration_in_parameter_list1740);
            	    p2=parameter_declaration();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, p2.getTree());

            	    }
            	    break;

            	default :
            	    break loop48;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 31, parameter_list_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "parameter_list"

    public static class parameter_declaration_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "parameter_declaration"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:756:1: parameter_declaration : declaration_specifiers ( declarator | abstract_declarator )* ( range_declarator )? -> declaration_specifiers ( declarator )* ( abstract_declarator )* ;
    public final PretCParser.parameter_declaration_return parameter_declaration() throws RecognitionException {
        PretCParser.parameter_declaration_return retval = new PretCParser.parameter_declaration_return();
        retval.start = input.LT(1);
        int parameter_declaration_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.declaration_specifiers_return declaration_specifiers155 = null;

        PretCParser.declarator_return declarator156 = null;

        PretCParser.abstract_declarator_return abstract_declarator157 = null;

        PretCParser.range_declarator_return range_declarator158 = null;


        RewriteRuleSubtreeStream stream_declaration_specifiers=new RewriteRuleSubtreeStream(adaptor,"rule declaration_specifiers");
        RewriteRuleSubtreeStream stream_declarator=new RewriteRuleSubtreeStream(adaptor,"rule declarator");
        RewriteRuleSubtreeStream stream_abstract_declarator=new RewriteRuleSubtreeStream(adaptor,"rule abstract_declarator");
        RewriteRuleSubtreeStream stream_range_declarator=new RewriteRuleSubtreeStream(adaptor,"rule range_declarator");

        	//boolean hasDecl = false;
        	addtype = true;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 32) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:764:2: ( declaration_specifiers ( declarator | abstract_declarator )* ( range_declarator )? -> declaration_specifiers ( declarator )* ( abstract_declarator )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:764:4: declaration_specifiers ( declarator | abstract_declarator )* ( range_declarator )?
            {
            if ( state.backtracking==0 ) {

              		if (is_stack.size()>0&&((is_scope)is_stack.peek()).declaration) {
              			addtype = false;	    		
              		}
              	  
            }
            pushFollow(FOLLOW_declaration_specifiers_in_parameter_declaration1781);
            declaration_specifiers155=declaration_specifiers();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) stream_declaration_specifiers.add(declaration_specifiers155.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:771:5: ( declarator | abstract_declarator )*
            loop49:
            do {
                int alt49=3;
                alt49 = dfa49.predict(input);
                switch (alt49) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:771:6: declarator
            	    {
            	    pushFollow(FOLLOW_declarator_in_parameter_declaration1792);
            	    declarator156=declarator();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) stream_declarator.add(declarator156.getTree());
            	    if ( state.backtracking==0 ) {

            	      					    		if (is_stack.size()>0&&((is_scope)is_stack.peek()).declaration) {
            	      					    		
            	      					    		}else{
            	          	    
            	      								((nodes_scope)nodes_stack.peek()).node.functionParameter.add((declarator156!=null?input.toString(declarator156.start,declarator156.stop):null));
            	      								((scopeNodes_scope)scopeNodes_stack.peek()).node.variableMapPut((declarator156!=null?input.toString(declarator156.start,declarator156.stop):null),((nodes_scope)nodes_stack.peek()).node);
            	      							}
            	      							//hasDecl = true;
            	      						
            	    }

            	    }
            	    break;
            	case 2 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:781:6: abstract_declarator
            	    {
            	    pushFollow(FOLLOW_abstract_declarator_in_parameter_declaration1802);
            	    abstract_declarator157=abstract_declarator();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) stream_abstract_declarator.add(abstract_declarator157.getTree());
            	    if ( state.backtracking==0 ) {
            	      System.out.println("\nAbstractor not handled contact developer\n");
            	      						
            	      						
            	    }

            	    }
            	    break;

            	default :
            	    break loop49;
                }
            } while (true);

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:786:5: ( range_declarator )?
            int alt50=2;
            int LA50_0 = input.LA(1);

            if ( (LA50_0==46) ) {
                alt50=1;
            }
            switch (alt50) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: range_declarator
                    {
                    pushFollow(FOLLOW_range_declarator_in_parameter_declaration1823);
                    range_declarator158=range_declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_range_declarator.add(range_declarator158.getTree());

                    }
                    break;

            }

            if ( state.backtracking==0 ) {

              							/*if (hasDecl == false) {
              								((nodes_scope)nodes_stack.peek()).node.functionParameter.add("");
              								
              							}*/
              						
            }


            // AST REWRITE
            // elements: abstract_declarator, declaration_specifiers, declarator
            // token labels: 
            // rule labels: retval
            // token list labels: 
            // rule list labels: 
            // wildcard labels: 
            if ( state.backtracking==0 ) {
            retval.tree = root_0;
            RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

            root_0 = (CommonTree)adaptor.nil();
            // 794:5: -> declaration_specifiers ( declarator )* ( abstract_declarator )*
            {
                adaptor.addChild(root_0, stream_declaration_specifiers.nextTree());
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:794:31: ( declarator )*
                while ( stream_declarator.hasNext() ) {
                    adaptor.addChild(root_0, stream_declarator.nextTree());

                }
                stream_declarator.reset();
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:794:43: ( abstract_declarator )*
                while ( stream_abstract_declarator.hasNext() ) {
                    adaptor.addChild(root_0, stream_abstract_declarator.nextTree());

                }
                stream_abstract_declarator.reset();

            }

            retval.tree = root_0;}
            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {

              	addtype = true;

            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 32, parameter_declaration_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "parameter_declaration"

    public static class identifier_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "identifier_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:798:1: identifier_list : IDENTIFIER ( ',' IDENTIFIER )* ;
    public final PretCParser.identifier_list_return identifier_list() throws RecognitionException {
        PretCParser.identifier_list_return retval = new PretCParser.identifier_list_return();
        retval.start = input.LT(1);
        int identifier_list_StartIndex = input.index();
        CommonTree root_0 = null;

        Token IDENTIFIER159=null;
        Token char_literal160=null;
        Token IDENTIFIER161=null;

        CommonTree IDENTIFIER159_tree=null;
        CommonTree char_literal160_tree=null;
        CommonTree IDENTIFIER161_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 33) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:799:2: ( IDENTIFIER ( ',' IDENTIFIER )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:799:4: IDENTIFIER ( ',' IDENTIFIER )*
            {
            root_0 = (CommonTree)adaptor.nil();

            IDENTIFIER159=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_identifier_list1868); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            IDENTIFIER159_tree = (CommonTree)adaptor.create(IDENTIFIER159);
            adaptor.addChild(root_0, IDENTIFIER159_tree);
            }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:799:15: ( ',' IDENTIFIER )*
            loop51:
            do {
                int alt51=2;
                int LA51_0 = input.LA(1);

                if ( (LA51_0==45) ) {
                    alt51=1;
                }


                switch (alt51) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:799:16: ',' IDENTIFIER
            	    {
            	    char_literal160=(Token)match(input,45,FOLLOW_45_in_identifier_list1871); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal160_tree = (CommonTree)adaptor.create(char_literal160);
            	    adaptor.addChild(root_0, char_literal160_tree);
            	    }
            	    IDENTIFIER161=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_identifier_list1873); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    IDENTIFIER161_tree = (CommonTree)adaptor.create(IDENTIFIER161);
            	    adaptor.addChild(root_0, IDENTIFIER161_tree);
            	    }

            	    }
            	    break;

            	default :
            	    break loop51;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 33, identifier_list_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "identifier_list"

    public static class type_name_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "type_name"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:802:1: type_name : specifier_qualifier_list ( abstract_declarator )? ;
    public final PretCParser.type_name_return type_name() throws RecognitionException {
        PretCParser.type_name_return retval = new PretCParser.type_name_return();
        retval.start = input.LT(1);
        int type_name_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.specifier_qualifier_list_return specifier_qualifier_list162 = null;

        PretCParser.abstract_declarator_return abstract_declarator163 = null;



        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 34) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:803:2: ( specifier_qualifier_list ( abstract_declarator )? )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:803:4: specifier_qualifier_list ( abstract_declarator )?
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_specifier_qualifier_list_in_type_name1886);
            specifier_qualifier_list162=specifier_qualifier_list();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, specifier_qualifier_list162.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:803:29: ( abstract_declarator )?
            int alt52=2;
            int LA52_0 = input.LA(1);

            if ( (LA52_0==49||LA52_0==73||LA52_0==75) ) {
                alt52=1;
            }
            switch (alt52) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: abstract_declarator
                    {
                    pushFollow(FOLLOW_abstract_declarator_in_type_name1888);
                    abstract_declarator163=abstract_declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, abstract_declarator163.getTree());

                    }
                    break;

            }


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 34, type_name_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "type_name"

    public static class abstract_declarator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "abstract_declarator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:806:1: abstract_declarator : ( pointer ( direct_abstract_declarator )? | direct_abstract_declarator );
    public final PretCParser.abstract_declarator_return abstract_declarator() throws RecognitionException {
        PretCParser.abstract_declarator_return retval = new PretCParser.abstract_declarator_return();
        retval.start = input.LT(1);
        int abstract_declarator_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.pointer_return pointer164 = null;

        PretCParser.direct_abstract_declarator_return direct_abstract_declarator165 = null;

        PretCParser.direct_abstract_declarator_return direct_abstract_declarator166 = null;



        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 35) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:807:2: ( pointer ( direct_abstract_declarator )? | direct_abstract_declarator )
            int alt54=2;
            int LA54_0 = input.LA(1);

            if ( (LA54_0==75) ) {
                alt54=1;
            }
            else if ( (LA54_0==49||LA54_0==73) ) {
                alt54=2;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 54, 0, input);

                throw nvae;
            }
            switch (alt54) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:807:4: pointer ( direct_abstract_declarator )?
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_pointer_in_abstract_declarator1900);
                    pointer164=pointer();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, pointer164.getTree());
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:807:12: ( direct_abstract_declarator )?
                    int alt53=2;
                    alt53 = dfa53.predict(input);
                    switch (alt53) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: direct_abstract_declarator
                            {
                            pushFollow(FOLLOW_direct_abstract_declarator_in_abstract_declarator1902);
                            direct_abstract_declarator165=direct_abstract_declarator();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) adaptor.addChild(root_0, direct_abstract_declarator165.getTree());

                            }
                            break;

                    }


                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:808:4: direct_abstract_declarator
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_direct_abstract_declarator_in_abstract_declarator1908);
                    direct_abstract_declarator166=direct_abstract_declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, direct_abstract_declarator166.getTree());

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 35, abstract_declarator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "abstract_declarator"

    public static class direct_abstract_declarator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "direct_abstract_declarator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:811:1: direct_abstract_declarator : ( '(' abstract_declarator ')' | abstract_declarator_suffix ) ( abstract_declarator_suffix )* ;
    public final PretCParser.direct_abstract_declarator_return direct_abstract_declarator() throws RecognitionException {
        PretCParser.direct_abstract_declarator_return retval = new PretCParser.direct_abstract_declarator_return();
        retval.start = input.LT(1);
        int direct_abstract_declarator_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal167=null;
        Token char_literal169=null;
        PretCParser.abstract_declarator_return abstract_declarator168 = null;

        PretCParser.abstract_declarator_suffix_return abstract_declarator_suffix170 = null;

        PretCParser.abstract_declarator_suffix_return abstract_declarator_suffix171 = null;


        CommonTree char_literal167_tree=null;
        CommonTree char_literal169_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 36) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:812:2: ( ( '(' abstract_declarator ')' | abstract_declarator_suffix ) ( abstract_declarator_suffix )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:812:4: ( '(' abstract_declarator ')' | abstract_declarator_suffix ) ( abstract_declarator_suffix )*
            {
            root_0 = (CommonTree)adaptor.nil();

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:812:4: ( '(' abstract_declarator ')' | abstract_declarator_suffix )
            int alt55=2;
            alt55 = dfa55.predict(input);
            switch (alt55) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:812:6: '(' abstract_declarator ')'
                    {
                    char_literal167=(Token)match(input,49,FOLLOW_49_in_direct_abstract_declarator1921); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal167_tree = (CommonTree)adaptor.create(char_literal167);
                    adaptor.addChild(root_0, char_literal167_tree);
                    }
                    pushFollow(FOLLOW_abstract_declarator_in_direct_abstract_declarator1923);
                    abstract_declarator168=abstract_declarator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, abstract_declarator168.getTree());
                    char_literal169=(Token)match(input,51,FOLLOW_51_in_direct_abstract_declarator1925); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal169_tree = (CommonTree)adaptor.create(char_literal169);
                    adaptor.addChild(root_0, char_literal169_tree);
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:812:36: abstract_declarator_suffix
                    {
                    pushFollow(FOLLOW_abstract_declarator_suffix_in_direct_abstract_declarator1929);
                    abstract_declarator_suffix170=abstract_declarator_suffix();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, abstract_declarator_suffix170.getTree());

                    }
                    break;

            }

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:812:65: ( abstract_declarator_suffix )*
            loop56:
            do {
                int alt56=2;
                alt56 = dfa56.predict(input);
                switch (alt56) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: abstract_declarator_suffix
            	    {
            	    pushFollow(FOLLOW_abstract_declarator_suffix_in_direct_abstract_declarator1933);
            	    abstract_declarator_suffix171=abstract_declarator_suffix();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, abstract_declarator_suffix171.getTree());

            	    }
            	    break;

            	default :
            	    break loop56;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 36, direct_abstract_declarator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "direct_abstract_declarator"

    public static class abstract_declarator_suffix_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "abstract_declarator_suffix"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:815:1: abstract_declarator_suffix : ( '[' ']' | '[' constant_expression ']' | '(' ')' | '(' parameter_type_list ')' );
    public final PretCParser.abstract_declarator_suffix_return abstract_declarator_suffix() throws RecognitionException {
        PretCParser.abstract_declarator_suffix_return retval = new PretCParser.abstract_declarator_suffix_return();
        retval.start = input.LT(1);
        int abstract_declarator_suffix_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal172=null;
        Token char_literal173=null;
        Token char_literal174=null;
        Token char_literal176=null;
        Token char_literal177=null;
        Token char_literal178=null;
        Token char_literal179=null;
        Token char_literal181=null;
        PretCParser.constant_expression_return constant_expression175 = null;

        PretCParser.parameter_type_list_return parameter_type_list180 = null;


        CommonTree char_literal172_tree=null;
        CommonTree char_literal173_tree=null;
        CommonTree char_literal174_tree=null;
        CommonTree char_literal176_tree=null;
        CommonTree char_literal177_tree=null;
        CommonTree char_literal178_tree=null;
        CommonTree char_literal179_tree=null;
        CommonTree char_literal181_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 37) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:816:2: ( '[' ']' | '[' constant_expression ']' | '(' ')' | '(' parameter_type_list ')' )
            int alt57=4;
            alt57 = dfa57.predict(input);
            switch (alt57) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:816:4: '[' ']'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal172=(Token)match(input,73,FOLLOW_73_in_abstract_declarator_suffix1945); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal172_tree = (CommonTree)adaptor.create(char_literal172);
                    adaptor.addChild(root_0, char_literal172_tree);
                    }
                    char_literal173=(Token)match(input,74,FOLLOW_74_in_abstract_declarator_suffix1947); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal173_tree = (CommonTree)adaptor.create(char_literal173);
                    adaptor.addChild(root_0, char_literal173_tree);
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:817:4: '[' constant_expression ']'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal174=(Token)match(input,73,FOLLOW_73_in_abstract_declarator_suffix1952); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal174_tree = (CommonTree)adaptor.create(char_literal174);
                    adaptor.addChild(root_0, char_literal174_tree);
                    }
                    pushFollow(FOLLOW_constant_expression_in_abstract_declarator_suffix1954);
                    constant_expression175=constant_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, constant_expression175.getTree());
                    char_literal176=(Token)match(input,74,FOLLOW_74_in_abstract_declarator_suffix1956); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal176_tree = (CommonTree)adaptor.create(char_literal176);
                    adaptor.addChild(root_0, char_literal176_tree);
                    }

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:818:4: '(' ')'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal177=(Token)match(input,49,FOLLOW_49_in_abstract_declarator_suffix1961); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal177_tree = (CommonTree)adaptor.create(char_literal177);
                    adaptor.addChild(root_0, char_literal177_tree);
                    }
                    char_literal178=(Token)match(input,51,FOLLOW_51_in_abstract_declarator_suffix1963); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal178_tree = (CommonTree)adaptor.create(char_literal178);
                    adaptor.addChild(root_0, char_literal178_tree);
                    }

                    }
                    break;
                case 4 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:819:4: '(' parameter_type_list ')'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal179=(Token)match(input,49,FOLLOW_49_in_abstract_declarator_suffix1968); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal179_tree = (CommonTree)adaptor.create(char_literal179);
                    adaptor.addChild(root_0, char_literal179_tree);
                    }
                    pushFollow(FOLLOW_parameter_type_list_in_abstract_declarator_suffix1970);
                    parameter_type_list180=parameter_type_list();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, parameter_type_list180.getTree());
                    char_literal181=(Token)match(input,51,FOLLOW_51_in_abstract_declarator_suffix1972); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal181_tree = (CommonTree)adaptor.create(char_literal181);
                    adaptor.addChild(root_0, char_literal181_tree);
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 37, abstract_declarator_suffix_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "abstract_declarator_suffix"

    public static class initializer_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "initializer"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:822:1: initializer : ( assignment_expression | '{' initializer_list ( ',' )? '}' );
    public final PretCParser.initializer_return initializer() throws RecognitionException {
        PretCParser.initializer_return retval = new PretCParser.initializer_return();
        retval.start = input.LT(1);
        int initializer_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal183=null;
        Token char_literal185=null;
        Token char_literal186=null;
        PretCParser.assignment_expression_return assignment_expression182 = null;

        PretCParser.initializer_list_return initializer_list184 = null;


        CommonTree char_literal183_tree=null;
        CommonTree char_literal185_tree=null;
        CommonTree char_literal186_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 38) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:823:2: ( assignment_expression | '{' initializer_list ( ',' )? '}' )
            int alt59=2;
            int LA59_0 = input.LA(1);

            if ( ((LA59_0>=IDENTIFIER && LA59_0<=DECIMAL_LITERAL)||(LA59_0>=HEX_LITERAL && LA59_0<=FLOATING_POINT_LITERAL)||LA59_0==49||LA59_0==75||(LA59_0>=77 && LA59_0<=78)||(LA59_0>=81 && LA59_0<=83)||(LA59_0>=86 && LA59_0<=88)) ) {
                alt59=1;
            }
            else if ( (LA59_0==65) ) {
                alt59=2;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 59, 0, input);

                throw nvae;
            }
            switch (alt59) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:823:4: assignment_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_assignment_expression_in_initializer1984);
                    assignment_expression182=assignment_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, assignment_expression182.getTree());

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:824:4: '{' initializer_list ( ',' )? '}'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal183=(Token)match(input,65,FOLLOW_65_in_initializer1989); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal183_tree = (CommonTree)adaptor.create(char_literal183);
                    adaptor.addChild(root_0, char_literal183_tree);
                    }
                    pushFollow(FOLLOW_initializer_list_in_initializer1991);
                    initializer_list184=initializer_list();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, initializer_list184.getTree());
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:824:25: ( ',' )?
                    int alt58=2;
                    int LA58_0 = input.LA(1);

                    if ( (LA58_0==45) ) {
                        alt58=1;
                    }
                    switch (alt58) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: ','
                            {
                            char_literal185=(Token)match(input,45,FOLLOW_45_in_initializer1993); if (state.failed) return retval;
                            if ( state.backtracking==0 ) {
                            char_literal185_tree = (CommonTree)adaptor.create(char_literal185);
                            adaptor.addChild(root_0, char_literal185_tree);
                            }

                            }
                            break;

                    }

                    char_literal186=(Token)match(input,66,FOLLOW_66_in_initializer1996); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal186_tree = (CommonTree)adaptor.create(char_literal186);
                    adaptor.addChild(root_0, char_literal186_tree);
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 38, initializer_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "initializer"

    public static class initializer_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "initializer_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:827:1: initializer_list : initializer ( ',' initializer )* ;
    public final PretCParser.initializer_list_return initializer_list() throws RecognitionException {
        PretCParser.initializer_list_return retval = new PretCParser.initializer_list_return();
        retval.start = input.LT(1);
        int initializer_list_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal188=null;
        PretCParser.initializer_return initializer187 = null;

        PretCParser.initializer_return initializer189 = null;


        CommonTree char_literal188_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 39) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:828:2: ( initializer ( ',' initializer )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:828:4: initializer ( ',' initializer )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_initializer_in_initializer_list2007);
            initializer187=initializer();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, initializer187.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:828:16: ( ',' initializer )*
            loop60:
            do {
                int alt60=2;
                alt60 = dfa60.predict(input);
                switch (alt60) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:828:17: ',' initializer
            	    {
            	    char_literal188=(Token)match(input,45,FOLLOW_45_in_initializer_list2010); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal188_tree = (CommonTree)adaptor.create(char_literal188);
            	    adaptor.addChild(root_0, char_literal188_tree);
            	    }
            	    pushFollow(FOLLOW_initializer_in_initializer_list2012);
            	    initializer189=initializer();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, initializer189.getTree());

            	    }
            	    break;

            	default :
            	    break loop60;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 39, initializer_list_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "initializer_list"

    public static class argument_expression_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "argument_expression_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:833:1: argument_expression_list : assignment_expression ( ',' assignment_expression )* ;
    public final PretCParser.argument_expression_list_return argument_expression_list() throws RecognitionException {
        PretCParser.argument_expression_list_return retval = new PretCParser.argument_expression_list_return();
        retval.start = input.LT(1);
        int argument_expression_list_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal191=null;
        PretCParser.assignment_expression_return assignment_expression190 = null;

        PretCParser.assignment_expression_return assignment_expression192 = null;


        CommonTree char_literal191_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 40) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:834:2: ( assignment_expression ( ',' assignment_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:834:6: assignment_expression ( ',' assignment_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_assignment_expression_in_argument_expression_list2029);
            assignment_expression190=assignment_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, assignment_expression190.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:834:28: ( ',' assignment_expression )*
            loop61:
            do {
                int alt61=2;
                int LA61_0 = input.LA(1);

                if ( (LA61_0==45) ) {
                    alt61=1;
                }


                switch (alt61) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:834:29: ',' assignment_expression
            	    {
            	    char_literal191=(Token)match(input,45,FOLLOW_45_in_argument_expression_list2032); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal191_tree = (CommonTree)adaptor.create(char_literal191);
            	    adaptor.addChild(root_0, char_literal191_tree);
            	    }
            	    pushFollow(FOLLOW_assignment_expression_in_argument_expression_list2034);
            	    assignment_expression192=assignment_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, assignment_expression192.getTree());

            	    }
            	    break;

            	default :
            	    break loop61;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 40, argument_expression_list_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "argument_expression_list"

    public static class additive_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "additive_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:837:1: additive_expression : ( multiplicative_expression ) ( '+' multiplicative_expression | '-' multiplicative_expression )* ;
    public final PretCParser.additive_expression_return additive_expression() throws RecognitionException {
        PretCParser.additive_expression_return retval = new PretCParser.additive_expression_return();
        retval.start = input.LT(1);
        int additive_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal194=null;
        Token char_literal196=null;
        PretCParser.multiplicative_expression_return multiplicative_expression193 = null;

        PretCParser.multiplicative_expression_return multiplicative_expression195 = null;

        PretCParser.multiplicative_expression_return multiplicative_expression197 = null;


        CommonTree char_literal194_tree=null;
        CommonTree char_literal196_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 41) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:838:2: ( ( multiplicative_expression ) ( '+' multiplicative_expression | '-' multiplicative_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:838:4: ( multiplicative_expression ) ( '+' multiplicative_expression | '-' multiplicative_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:838:4: ( multiplicative_expression )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:838:5: multiplicative_expression
            {
            pushFollow(FOLLOW_multiplicative_expression_in_additive_expression2048);
            multiplicative_expression193=multiplicative_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, multiplicative_expression193.getTree());

            }

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:838:32: ( '+' multiplicative_expression | '-' multiplicative_expression )*
            loop62:
            do {
                int alt62=3;
                alt62 = dfa62.predict(input);
                switch (alt62) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:838:33: '+' multiplicative_expression
            	    {
            	    char_literal194=(Token)match(input,77,FOLLOW_77_in_additive_expression2052); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal194_tree = (CommonTree)adaptor.create(char_literal194);
            	    adaptor.addChild(root_0, char_literal194_tree);
            	    }
            	    pushFollow(FOLLOW_multiplicative_expression_in_additive_expression2054);
            	    multiplicative_expression195=multiplicative_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, multiplicative_expression195.getTree());

            	    }
            	    break;
            	case 2 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:838:65: '-' multiplicative_expression
            	    {
            	    char_literal196=(Token)match(input,78,FOLLOW_78_in_additive_expression2058); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal196_tree = (CommonTree)adaptor.create(char_literal196);
            	    adaptor.addChild(root_0, char_literal196_tree);
            	    }
            	    pushFollow(FOLLOW_multiplicative_expression_in_additive_expression2060);
            	    multiplicative_expression197=multiplicative_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, multiplicative_expression197.getTree());

            	    }
            	    break;

            	default :
            	    break loop62;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 41, additive_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "additive_expression"

    public static class multiplicative_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "multiplicative_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:841:1: multiplicative_expression : ( cast_expression ) ( '*' cast_expression | '/' cast_expression | '%' cast_expression )* ;
    public final PretCParser.multiplicative_expression_return multiplicative_expression() throws RecognitionException {
        PretCParser.multiplicative_expression_return retval = new PretCParser.multiplicative_expression_return();
        retval.start = input.LT(1);
        int multiplicative_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal199=null;
        Token char_literal201=null;
        Token char_literal203=null;
        PretCParser.cast_expression_return cast_expression198 = null;

        PretCParser.cast_expression_return cast_expression200 = null;

        PretCParser.cast_expression_return cast_expression202 = null;

        PretCParser.cast_expression_return cast_expression204 = null;


        CommonTree char_literal199_tree=null;
        CommonTree char_literal201_tree=null;
        CommonTree char_literal203_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 42) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:842:2: ( ( cast_expression ) ( '*' cast_expression | '/' cast_expression | '%' cast_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:842:4: ( cast_expression ) ( '*' cast_expression | '/' cast_expression | '%' cast_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:842:4: ( cast_expression )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:842:5: cast_expression
            {
            pushFollow(FOLLOW_cast_expression_in_multiplicative_expression2074);
            cast_expression198=cast_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, cast_expression198.getTree());

            }

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:842:22: ( '*' cast_expression | '/' cast_expression | '%' cast_expression )*
            loop63:
            do {
                int alt63=4;
                alt63 = dfa63.predict(input);
                switch (alt63) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:842:23: '*' cast_expression
            	    {
            	    char_literal199=(Token)match(input,75,FOLLOW_75_in_multiplicative_expression2078); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal199_tree = (CommonTree)adaptor.create(char_literal199);
            	    adaptor.addChild(root_0, char_literal199_tree);
            	    }
            	    pushFollow(FOLLOW_cast_expression_in_multiplicative_expression2080);
            	    cast_expression200=cast_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, cast_expression200.getTree());

            	    }
            	    break;
            	case 2 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:842:45: '/' cast_expression
            	    {
            	    char_literal201=(Token)match(input,79,FOLLOW_79_in_multiplicative_expression2084); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal201_tree = (CommonTree)adaptor.create(char_literal201);
            	    adaptor.addChild(root_0, char_literal201_tree);
            	    }
            	    pushFollow(FOLLOW_cast_expression_in_multiplicative_expression2086);
            	    cast_expression202=cast_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, cast_expression202.getTree());

            	    }
            	    break;
            	case 3 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:842:67: '%' cast_expression
            	    {
            	    char_literal203=(Token)match(input,80,FOLLOW_80_in_multiplicative_expression2090); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal203_tree = (CommonTree)adaptor.create(char_literal203);
            	    adaptor.addChild(root_0, char_literal203_tree);
            	    }
            	    pushFollow(FOLLOW_cast_expression_in_multiplicative_expression2092);
            	    cast_expression204=cast_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, cast_expression204.getTree());

            	    }
            	    break;

            	default :
            	    break loop63;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 42, multiplicative_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "multiplicative_expression"

    public static class cast_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "cast_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:845:1: cast_expression : ( '(' type_name ')' cast_expression | unary_expression );
    public final PretCParser.cast_expression_return cast_expression() throws RecognitionException {
        PretCParser.cast_expression_return retval = new PretCParser.cast_expression_return();
        retval.start = input.LT(1);
        int cast_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal205=null;
        Token char_literal207=null;
        PretCParser.type_name_return type_name206 = null;

        PretCParser.cast_expression_return cast_expression208 = null;

        PretCParser.unary_expression_return unary_expression209 = null;


        CommonTree char_literal205_tree=null;
        CommonTree char_literal207_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 43) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:846:2: ( '(' type_name ')' cast_expression | unary_expression )
            int alt64=2;
            alt64 = dfa64.predict(input);
            switch (alt64) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:846:4: '(' type_name ')' cast_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal205=(Token)match(input,49,FOLLOW_49_in_cast_expression2105); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal205_tree = (CommonTree)adaptor.create(char_literal205);
                    adaptor.addChild(root_0, char_literal205_tree);
                    }
                    pushFollow(FOLLOW_type_name_in_cast_expression2107);
                    type_name206=type_name();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, type_name206.getTree());
                    char_literal207=(Token)match(input,51,FOLLOW_51_in_cast_expression2109); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal207_tree = (CommonTree)adaptor.create(char_literal207);
                    adaptor.addChild(root_0, char_literal207_tree);
                    }
                    pushFollow(FOLLOW_cast_expression_in_cast_expression2111);
                    cast_expression208=cast_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, cast_expression208.getTree());

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:847:4: unary_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_unary_expression_in_cast_expression2116);
                    unary_expression209=unary_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, unary_expression209.getTree());

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 43, cast_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "cast_expression"

    public static class unary_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "unary_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:850:1: unary_expression : ( postfix_expression | '++' unary_expression | '--' unary_expression | unary_operator cast_expression | 'sizeof' unary_expression | 'sizeof' '(' type_name ')' );
    public final PretCParser.unary_expression_return unary_expression() throws RecognitionException {
        PretCParser.unary_expression_return retval = new PretCParser.unary_expression_return();
        retval.start = input.LT(1);
        int unary_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal211=null;
        Token string_literal213=null;
        Token string_literal217=null;
        Token string_literal219=null;
        Token char_literal220=null;
        Token char_literal222=null;
        PretCParser.postfix_expression_return postfix_expression210 = null;

        PretCParser.unary_expression_return unary_expression212 = null;

        PretCParser.unary_expression_return unary_expression214 = null;

        PretCParser.unary_operator_return unary_operator215 = null;

        PretCParser.cast_expression_return cast_expression216 = null;

        PretCParser.unary_expression_return unary_expression218 = null;

        PretCParser.type_name_return type_name221 = null;


        CommonTree string_literal211_tree=null;
        CommonTree string_literal213_tree=null;
        CommonTree string_literal217_tree=null;
        CommonTree string_literal219_tree=null;
        CommonTree char_literal220_tree=null;
        CommonTree char_literal222_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 44) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:851:2: ( postfix_expression | '++' unary_expression | '--' unary_expression | unary_operator cast_expression | 'sizeof' unary_expression | 'sizeof' '(' type_name ')' )
            int alt65=6;
            alt65 = dfa65.predict(input);
            switch (alt65) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:851:4: postfix_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_postfix_expression_in_unary_expression2127);
                    postfix_expression210=postfix_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, postfix_expression210.getTree());

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:852:4: '++' unary_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal211=(Token)match(input,81,FOLLOW_81_in_unary_expression2132); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal211_tree = (CommonTree)adaptor.create(string_literal211);
                    adaptor.addChild(root_0, string_literal211_tree);
                    }
                    pushFollow(FOLLOW_unary_expression_in_unary_expression2134);
                    unary_expression212=unary_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, unary_expression212.getTree());
                    if ( state.backtracking==0 ) {

                      			((nodes_scope)nodes_stack.peek()).node.assignedVars.add("++"+constantExprTempIdentifier);
                      		
                    }

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:856:4: '--' unary_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal213=(Token)match(input,82,FOLLOW_82_in_unary_expression2143); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal213_tree = (CommonTree)adaptor.create(string_literal213);
                    adaptor.addChild(root_0, string_literal213_tree);
                    }
                    pushFollow(FOLLOW_unary_expression_in_unary_expression2145);
                    unary_expression214=unary_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, unary_expression214.getTree());
                    if ( state.backtracking==0 ) {

                      			((nodes_scope)nodes_stack.peek()).node.assignedVars.add("--"+constantExprTempIdentifier);
                      		
                    }

                    }
                    break;
                case 4 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:860:4: unary_operator cast_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_unary_operator_in_unary_expression2154);
                    unary_operator215=unary_operator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, unary_operator215.getTree());
                    pushFollow(FOLLOW_cast_expression_in_unary_expression2156);
                    cast_expression216=cast_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, cast_expression216.getTree());

                    }
                    break;
                case 5 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:861:4: 'sizeof' unary_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal217=(Token)match(input,83,FOLLOW_83_in_unary_expression2161); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal217_tree = (CommonTree)adaptor.create(string_literal217);
                    adaptor.addChild(root_0, string_literal217_tree);
                    }
                    pushFollow(FOLLOW_unary_expression_in_unary_expression2163);
                    unary_expression218=unary_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, unary_expression218.getTree());

                    }
                    break;
                case 6 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:862:4: 'sizeof' '(' type_name ')'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal219=(Token)match(input,83,FOLLOW_83_in_unary_expression2168); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal219_tree = (CommonTree)adaptor.create(string_literal219);
                    adaptor.addChild(root_0, string_literal219_tree);
                    }
                    char_literal220=(Token)match(input,49,FOLLOW_49_in_unary_expression2170); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal220_tree = (CommonTree)adaptor.create(char_literal220);
                    adaptor.addChild(root_0, char_literal220_tree);
                    }
                    pushFollow(FOLLOW_type_name_in_unary_expression2172);
                    type_name221=type_name();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, type_name221.getTree());
                    char_literal222=(Token)match(input,51,FOLLOW_51_in_unary_expression2174); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal222_tree = (CommonTree)adaptor.create(char_literal222);
                    adaptor.addChild(root_0, char_literal222_tree);
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 44, unary_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "unary_expression"

    public static class postfix_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "postfix_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:865:1: postfix_expression : primary_expression ( '[' expression ']' | '(' ')' | '(' argument_expression_list ')' | '.' i1= IDENTIFIER | '->' i2= IDENTIFIER | '++' | '--' )* ;
    public final PretCParser.postfix_expression_return postfix_expression() throws RecognitionException {
        PretCParser.postfix_expression_return retval = new PretCParser.postfix_expression_return();
        retval.start = input.LT(1);
        int postfix_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token i1=null;
        Token i2=null;
        Token char_literal224=null;
        Token char_literal226=null;
        Token char_literal227=null;
        Token char_literal228=null;
        Token char_literal229=null;
        Token char_literal231=null;
        Token char_literal232=null;
        Token string_literal233=null;
        Token string_literal234=null;
        Token string_literal235=null;
        PretCParser.primary_expression_return primary_expression223 = null;

        PretCParser.expression_return expression225 = null;

        PretCParser.argument_expression_list_return argument_expression_list230 = null;


        CommonTree i1_tree=null;
        CommonTree i2_tree=null;
        CommonTree char_literal224_tree=null;
        CommonTree char_literal226_tree=null;
        CommonTree char_literal227_tree=null;
        CommonTree char_literal228_tree=null;
        CommonTree char_literal229_tree=null;
        CommonTree char_literal231_tree=null;
        CommonTree char_literal232_tree=null;
        CommonTree string_literal233_tree=null;
        CommonTree string_literal234_tree=null;
        CommonTree string_literal235_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 45) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:866:2: ( primary_expression ( '[' expression ']' | '(' ')' | '(' argument_expression_list ')' | '.' i1= IDENTIFIER | '->' i2= IDENTIFIER | '++' | '--' )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:866:6: primary_expression ( '[' expression ']' | '(' ')' | '(' argument_expression_list ')' | '.' i1= IDENTIFIER | '->' i2= IDENTIFIER | '++' | '--' )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_primary_expression_in_postfix_expression2187);
            primary_expression223=primary_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, primary_expression223.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:867:9: ( '[' expression ']' | '(' ')' | '(' argument_expression_list ')' | '.' i1= IDENTIFIER | '->' i2= IDENTIFIER | '++' | '--' )*
            loop66:
            do {
                int alt66=8;
                alt66 = dfa66.predict(input);
                switch (alt66) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:867:13: '[' expression ']'
            	    {
            	    char_literal224=(Token)match(input,73,FOLLOW_73_in_postfix_expression2201); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal224_tree = (CommonTree)adaptor.create(char_literal224);
            	    adaptor.addChild(root_0, char_literal224_tree);
            	    }
            	    pushFollow(FOLLOW_expression_in_postfix_expression2203);
            	    expression225=expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, expression225.getTree());
            	    char_literal226=(Token)match(input,74,FOLLOW_74_in_postfix_expression2205); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal226_tree = (CommonTree)adaptor.create(char_literal226);
            	    adaptor.addChild(root_0, char_literal226_tree);
            	    }

            	    }
            	    break;
            	case 2 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:868:13: '(' ')'
            	    {
            	    char_literal227=(Token)match(input,49,FOLLOW_49_in_postfix_expression2219); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal227_tree = (CommonTree)adaptor.create(char_literal227);
            	    adaptor.addChild(root_0, char_literal227_tree);
            	    }
            	    char_literal228=(Token)match(input,51,FOLLOW_51_in_postfix_expression2221); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal228_tree = (CommonTree)adaptor.create(char_literal228);
            	    adaptor.addChild(root_0, char_literal228_tree);
            	    }

            	    }
            	    break;
            	case 3 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:869:13: '(' argument_expression_list ')'
            	    {
            	    char_literal229=(Token)match(input,49,FOLLOW_49_in_postfix_expression2235); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal229_tree = (CommonTree)adaptor.create(char_literal229);
            	    adaptor.addChild(root_0, char_literal229_tree);
            	    }
            	    pushFollow(FOLLOW_argument_expression_list_in_postfix_expression2237);
            	    argument_expression_list230=argument_expression_list();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, argument_expression_list230.getTree());
            	    char_literal231=(Token)match(input,51,FOLLOW_51_in_postfix_expression2239); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal231_tree = (CommonTree)adaptor.create(char_literal231);
            	    adaptor.addChild(root_0, char_literal231_tree);
            	    }

            	    }
            	    break;
            	case 4 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:870:13: '.' i1= IDENTIFIER
            	    {
            	    char_literal232=(Token)match(input,84,FOLLOW_84_in_postfix_expression2253); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal232_tree = (CommonTree)adaptor.create(char_literal232);
            	    adaptor.addChild(root_0, char_literal232_tree);
            	    }
            	    i1=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_postfix_expression2257); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    i1_tree = (CommonTree)adaptor.create(i1);
            	    adaptor.addChild(root_0, i1_tree);
            	    }
            	    if ( state.backtracking==0 ) {
            	      constantExprTempIdentifier+="."+(i1!=null?i1.getText():null);
            	    }

            	    }
            	    break;
            	case 5 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:871:13: '->' i2= IDENTIFIER
            	    {
            	    string_literal233=(Token)match(input,85,FOLLOW_85_in_postfix_expression2273); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    string_literal233_tree = (CommonTree)adaptor.create(string_literal233);
            	    adaptor.addChild(root_0, string_literal233_tree);
            	    }
            	    i2=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_postfix_expression2277); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    i2_tree = (CommonTree)adaptor.create(i2);
            	    adaptor.addChild(root_0, i2_tree);
            	    }
            	    if ( state.backtracking==0 ) {
            	      constantExprTempIdentifier+="->"+(i2!=null?i2.getText():null);
            	    }

            	    }
            	    break;
            	case 6 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:872:13: '++'
            	    {
            	    string_literal234=(Token)match(input,81,FOLLOW_81_in_postfix_expression2293); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    string_literal234_tree = (CommonTree)adaptor.create(string_literal234);
            	    adaptor.addChild(root_0, string_literal234_tree);
            	    }
            	    if ( state.backtracking==0 ) {
            	      ((nodes_scope)nodes_stack.peek()).node.assignedVars.add(constantExprTempIdentifier+"++");
            	    }

            	    }
            	    break;
            	case 7 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:873:13: '--'
            	    {
            	    string_literal235=(Token)match(input,82,FOLLOW_82_in_postfix_expression2310); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    string_literal235_tree = (CommonTree)adaptor.create(string_literal235);
            	    adaptor.addChild(root_0, string_literal235_tree);
            	    }
            	    if ( state.backtracking==0 ) {
            	      ((nodes_scope)nodes_stack.peek()).node.assignedVars.add(constantExprTempIdentifier+"--");
            	    }

            	    }
            	    break;

            	default :
            	    break loop66;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 45, postfix_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "postfix_expression"

    public static class unary_operator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "unary_operator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:877:1: unary_operator : ( '&' | '*' | '+' | '-' | '~' | '!' );
    public final PretCParser.unary_operator_return unary_operator() throws RecognitionException {
        PretCParser.unary_operator_return retval = new PretCParser.unary_operator_return();
        retval.start = input.LT(1);
        int unary_operator_StartIndex = input.index();
        CommonTree root_0 = null;

        Token set236=null;

        CommonTree set236_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 46) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:878:2: ( '&' | '*' | '+' | '-' | '~' | '!' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
            {
            root_0 = (CommonTree)adaptor.nil();

            set236=(Token)input.LT(1);
            if ( input.LA(1)==75||(input.LA(1)>=77 && input.LA(1)<=78)||(input.LA(1)>=86 && input.LA(1)<=88) ) {
                input.consume();
                if ( state.backtracking==0 ) adaptor.addChild(root_0, (CommonTree)adaptor.create(set236));
                state.errorRecovery=false;state.failed=false;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                MismatchedSetException mse = new MismatchedSetException(null,input);
                throw mse;
            }


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 46, unary_operator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "unary_operator"

    public static class primary_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "primary_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:886:1: primary_expression : ( IDENTIFIER | constant | '(' expression ')' );
    public final PretCParser.primary_expression_return primary_expression() throws RecognitionException {
        PretCParser.primary_expression_return retval = new PretCParser.primary_expression_return();
        retval.start = input.LT(1);
        int primary_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token IDENTIFIER237=null;
        Token char_literal239=null;
        Token char_literal241=null;
        PretCParser.constant_return constant238 = null;

        PretCParser.expression_return expression240 = null;


        CommonTree IDENTIFIER237_tree=null;
        CommonTree char_literal239_tree=null;
        CommonTree char_literal241_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 47) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:887:2: ( IDENTIFIER | constant | '(' expression ')' )
            int alt67=3;
            switch ( input.LA(1) ) {
            case IDENTIFIER:
                {
                alt67=1;
                }
                break;
            case DECIMAL_LITERAL:
            case HEX_LITERAL:
            case OCTAL_LITERAL:
            case CHARACTER_LITERAL:
            case STRING_LITERAL:
            case FLOATING_POINT_LITERAL:
                {
                alt67=2;
                }
                break;
            case 49:
                {
                alt67=3;
                }
                break;
            default:
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 67, 0, input);

                throw nvae;
            }

            switch (alt67) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:887:4: IDENTIFIER
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    IDENTIFIER237=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_primary_expression2371); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    IDENTIFIER237_tree = (CommonTree)adaptor.create(IDENTIFIER237);
                    adaptor.addChild(root_0, IDENTIFIER237_tree);
                    }
                    if ( state.backtracking==0 ) {
                      constantExprTempIdentifier=(IDENTIFIER237!=null?IDENTIFIER237.getText():null);
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:888:4: constant
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_constant_in_primary_expression2378);
                    constant238=constant();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, constant238.getTree());

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:889:4: '(' expression ')'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal239=(Token)match(input,49,FOLLOW_49_in_primary_expression2383); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal239_tree = (CommonTree)adaptor.create(char_literal239);
                    adaptor.addChild(root_0, char_literal239_tree);
                    }
                    pushFollow(FOLLOW_expression_in_primary_expression2385);
                    expression240=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, expression240.getTree());
                    char_literal241=(Token)match(input,51,FOLLOW_51_in_primary_expression2387); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal241_tree = (CommonTree)adaptor.create(char_literal241);
                    adaptor.addChild(root_0, char_literal241_tree);
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 47, primary_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "primary_expression"

    public static class constant_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "constant"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:892:1: constant : ( HEX_LITERAL | OCTAL_LITERAL | DECIMAL_LITERAL | CHARACTER_LITERAL | STRING_LITERAL | FLOATING_POINT_LITERAL );
    public final PretCParser.constant_return constant() throws RecognitionException {
        PretCParser.constant_return retval = new PretCParser.constant_return();
        retval.start = input.LT(1);
        int constant_StartIndex = input.index();
        CommonTree root_0 = null;

        Token set242=null;

        CommonTree set242_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 48) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:893:5: ( HEX_LITERAL | OCTAL_LITERAL | DECIMAL_LITERAL | CHARACTER_LITERAL | STRING_LITERAL | FLOATING_POINT_LITERAL )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
            {
            root_0 = (CommonTree)adaptor.nil();

            set242=(Token)input.LT(1);
            if ( input.LA(1)==DECIMAL_LITERAL||(input.LA(1)>=HEX_LITERAL && input.LA(1)<=FLOATING_POINT_LITERAL) ) {
                input.consume();
                if ( state.backtracking==0 ) adaptor.addChild(root_0, (CommonTree)adaptor.create(set242));
                state.errorRecovery=false;state.failed=false;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                MismatchedSetException mse = new MismatchedSetException(null,input);
                throw mse;
            }


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 48, constant_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "constant"

    public static class expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:903:1: expression : a1= assignment_expression ( ',' a2= assignment_expression )* ;
    public final PretCParser.expression_return expression() throws RecognitionException {
        PretCParser.expression_return retval = new PretCParser.expression_return();
        retval.start = input.LT(1);
        int expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal243=null;
        PretCParser.assignment_expression_return a1 = null;

        PretCParser.assignment_expression_return a2 = null;


        CommonTree char_literal243_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 49) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:904:2: (a1= assignment_expression ( ',' a2= assignment_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:904:4: a1= assignment_expression ( ',' a2= assignment_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_assignment_expression_in_expression2466);
            a1=assignment_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, a1.getTree());
            if ( state.backtracking==0 ) {
              ((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add((a1!=null?input.toString(a1.start,a1.stop):null));
            }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:904:82: ( ',' a2= assignment_expression )*
            loop68:
            do {
                int alt68=2;
                int LA68_0 = input.LA(1);

                if ( (LA68_0==45) ) {
                    alt68=1;
                }


                switch (alt68) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:904:83: ',' a2= assignment_expression
            	    {
            	    char_literal243=(Token)match(input,45,FOLLOW_45_in_expression2471); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal243_tree = (CommonTree)adaptor.create(char_literal243);
            	    adaptor.addChild(root_0, char_literal243_tree);
            	    }
            	    pushFollow(FOLLOW_assignment_expression_in_expression2476);
            	    a2=assignment_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, a2.getTree());
            	    if ( state.backtracking==0 ) {
            	      ((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add((a2!=null?input.toString(a2.start,a2.stop):null));
            	    }

            	    }
            	    break;

            	default :
            	    break loop68;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 49, expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "expression"

    public static class constant_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "constant_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:907:1: constant_expression : conditional_expression ;
    public final PretCParser.constant_expression_return constant_expression() throws RecognitionException {
        PretCParser.constant_expression_return retval = new PretCParser.constant_expression_return();
        retval.start = input.LT(1);
        int constant_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.conditional_expression_return conditional_expression244 = null;



        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 50) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:908:2: ( conditional_expression )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:908:4: conditional_expression
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_conditional_expression_in_constant_expression2490);
            conditional_expression244=conditional_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, conditional_expression244.getTree());

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 50, constant_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "constant_expression"

    public static class assignment_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "assignment_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:911:1: assignment_expression : ( lvalue assignment_operator assignment_expression | constant_expression );
    public final PretCParser.assignment_expression_return assignment_expression() throws RecognitionException {
        PretCParser.assignment_expression_return retval = new PretCParser.assignment_expression_return();
        retval.start = input.LT(1);
        int assignment_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.lvalue_return lvalue245 = null;

        PretCParser.assignment_operator_return assignment_operator246 = null;

        PretCParser.assignment_expression_return assignment_expression247 = null;

        PretCParser.constant_expression_return constant_expression248 = null;



        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 51) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:912:2: ( lvalue assignment_operator assignment_expression | constant_expression )
            int alt69=2;
            alt69 = dfa69.predict(input);
            switch (alt69) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:912:4: lvalue assignment_operator assignment_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_lvalue_in_assignment_expression2503);
                    lvalue245=lvalue();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, lvalue245.getTree());
                    pushFollow(FOLLOW_assignment_operator_in_assignment_expression2505);
                    assignment_operator246=assignment_operator();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, assignment_operator246.getTree());
                    pushFollow(FOLLOW_assignment_expression_in_assignment_expression2507);
                    assignment_expression247=assignment_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, assignment_expression247.getTree());
                    if ( state.backtracking==0 ) {

                      			((nodes_scope)nodes_stack.peek()).node.assignedVars.add((lvalue245!=null?input.toString(lvalue245.start,lvalue245.stop):null));
                      			
                      		
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:917:4: constant_expression
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_constant_expression_in_assignment_expression2516);
                    constant_expression248=constant_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, constant_expression248.getTree());
                    if ( state.backtracking==0 ) {

                      			((nodes_scope)nodes_stack.peek()).node.constantStatement.get(((nodes_scope)nodes_stack.peek()).node.constantStatement.size()-1).add((constant_expression248!=null?input.toString(constant_expression248.start,constant_expression248.stop):null));
                      		
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 51, assignment_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "assignment_expression"

    public static class lvalue_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "lvalue"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:923:1: lvalue : unary_expression ;
    public final PretCParser.lvalue_return lvalue() throws RecognitionException {
        PretCParser.lvalue_return retval = new PretCParser.lvalue_return();
        retval.start = input.LT(1);
        int lvalue_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.unary_expression_return unary_expression249 = null;



        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 52) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:924:2: ( unary_expression )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:924:4: unary_expression
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_unary_expression_in_lvalue2532);
            unary_expression249=unary_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, unary_expression249.getTree());

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 52, lvalue_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "lvalue"

    public static class assignment_operator_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "assignment_operator"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:927:1: assignment_operator : ( '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '>>=' | '&=' | '^=' | '|=' );
    public final PretCParser.assignment_operator_return assignment_operator() throws RecognitionException {
        PretCParser.assignment_operator_return retval = new PretCParser.assignment_operator_return();
        retval.start = input.LT(1);
        int assignment_operator_StartIndex = input.index();
        CommonTree root_0 = null;

        Token set250=null;

        CommonTree set250_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 53) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:928:2: ( '=' | '*=' | '/=' | '%=' | '+=' | '-=' | '<<=' | '>>=' | '&=' | '^=' | '|=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
            {
            root_0 = (CommonTree)adaptor.nil();

            set250=(Token)input.LT(1);
            if ( input.LA(1)==44||(input.LA(1)>=89 && input.LA(1)<=98) ) {
                input.consume();
                if ( state.backtracking==0 ) adaptor.addChild(root_0, (CommonTree)adaptor.create(set250));
                state.errorRecovery=false;state.failed=false;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                MismatchedSetException mse = new MismatchedSetException(null,input);
                throw mse;
            }


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 53, assignment_operator_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "assignment_operator"

    public static class conditional_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "conditional_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:941:1: conditional_expression : logical_or_expression ( '?' expression ':' conditional_expression )? ;
    public final PretCParser.conditional_expression_return conditional_expression() throws RecognitionException {
        PretCParser.conditional_expression_return retval = new PretCParser.conditional_expression_return();
        retval.start = input.LT(1);
        int conditional_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal252=null;
        Token char_literal254=null;
        PretCParser.logical_or_expression_return logical_or_expression251 = null;

        PretCParser.expression_return expression253 = null;

        PretCParser.conditional_expression_return conditional_expression255 = null;


        CommonTree char_literal252_tree=null;
        CommonTree char_literal254_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 54) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:942:2: ( logical_or_expression ( '?' expression ':' conditional_expression )? )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:942:4: logical_or_expression ( '?' expression ':' conditional_expression )?
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_logical_or_expression_in_conditional_expression2604);
            logical_or_expression251=logical_or_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, logical_or_expression251.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:942:26: ( '?' expression ':' conditional_expression )?
            int alt70=2;
            alt70 = dfa70.predict(input);
            switch (alt70) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:942:27: '?' expression ':' conditional_expression
                    {
                    char_literal252=(Token)match(input,99,FOLLOW_99_in_conditional_expression2607); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal252_tree = (CommonTree)adaptor.create(char_literal252);
                    adaptor.addChild(root_0, char_literal252_tree);
                    }
                    pushFollow(FOLLOW_expression_in_conditional_expression2609);
                    expression253=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, expression253.getTree());
                    char_literal254=(Token)match(input,69,FOLLOW_69_in_conditional_expression2611); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal254_tree = (CommonTree)adaptor.create(char_literal254);
                    adaptor.addChild(root_0, char_literal254_tree);
                    }
                    pushFollow(FOLLOW_conditional_expression_in_conditional_expression2613);
                    conditional_expression255=conditional_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, conditional_expression255.getTree());

                    }
                    break;

            }


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 54, conditional_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "conditional_expression"

    public static class logical_or_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "logical_or_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:945:1: logical_or_expression : logical_and_expression ( '||' logical_and_expression )* ;
    public final PretCParser.logical_or_expression_return logical_or_expression() throws RecognitionException {
        PretCParser.logical_or_expression_return retval = new PretCParser.logical_or_expression_return();
        retval.start = input.LT(1);
        int logical_or_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal257=null;
        PretCParser.logical_and_expression_return logical_and_expression256 = null;

        PretCParser.logical_and_expression_return logical_and_expression258 = null;


        CommonTree string_literal257_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 55) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:946:2: ( logical_and_expression ( '||' logical_and_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:946:4: logical_and_expression ( '||' logical_and_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_logical_and_expression_in_logical_or_expression2626);
            logical_and_expression256=logical_and_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, logical_and_expression256.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:946:27: ( '||' logical_and_expression )*
            loop71:
            do {
                int alt71=2;
                alt71 = dfa71.predict(input);
                switch (alt71) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:946:28: '||' logical_and_expression
            	    {
            	    string_literal257=(Token)match(input,100,FOLLOW_100_in_logical_or_expression2629); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    string_literal257_tree = (CommonTree)adaptor.create(string_literal257);
            	    adaptor.addChild(root_0, string_literal257_tree);
            	    }
            	    pushFollow(FOLLOW_logical_and_expression_in_logical_or_expression2631);
            	    logical_and_expression258=logical_and_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, logical_and_expression258.getTree());

            	    }
            	    break;

            	default :
            	    break loop71;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 55, logical_or_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "logical_or_expression"

    public static class logical_and_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "logical_and_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:949:1: logical_and_expression : inclusive_or_expression ( '&&' inclusive_or_expression )* ;
    public final PretCParser.logical_and_expression_return logical_and_expression() throws RecognitionException {
        PretCParser.logical_and_expression_return retval = new PretCParser.logical_and_expression_return();
        retval.start = input.LT(1);
        int logical_and_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal260=null;
        PretCParser.inclusive_or_expression_return inclusive_or_expression259 = null;

        PretCParser.inclusive_or_expression_return inclusive_or_expression261 = null;


        CommonTree string_literal260_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 56) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:950:2: ( inclusive_or_expression ( '&&' inclusive_or_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:950:4: inclusive_or_expression ( '&&' inclusive_or_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_inclusive_or_expression_in_logical_and_expression2644);
            inclusive_or_expression259=inclusive_or_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, inclusive_or_expression259.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:950:28: ( '&&' inclusive_or_expression )*
            loop72:
            do {
                int alt72=2;
                alt72 = dfa72.predict(input);
                switch (alt72) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:950:29: '&&' inclusive_or_expression
            	    {
            	    string_literal260=(Token)match(input,101,FOLLOW_101_in_logical_and_expression2647); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    string_literal260_tree = (CommonTree)adaptor.create(string_literal260);
            	    adaptor.addChild(root_0, string_literal260_tree);
            	    }
            	    pushFollow(FOLLOW_inclusive_or_expression_in_logical_and_expression2649);
            	    inclusive_or_expression261=inclusive_or_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, inclusive_or_expression261.getTree());

            	    }
            	    break;

            	default :
            	    break loop72;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 56, logical_and_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "logical_and_expression"

    public static class inclusive_or_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "inclusive_or_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:953:1: inclusive_or_expression : exclusive_or_expression ( '|' exclusive_or_expression )* ;
    public final PretCParser.inclusive_or_expression_return inclusive_or_expression() throws RecognitionException {
        PretCParser.inclusive_or_expression_return retval = new PretCParser.inclusive_or_expression_return();
        retval.start = input.LT(1);
        int inclusive_or_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal263=null;
        PretCParser.exclusive_or_expression_return exclusive_or_expression262 = null;

        PretCParser.exclusive_or_expression_return exclusive_or_expression264 = null;


        CommonTree char_literal263_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 57) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:954:2: ( exclusive_or_expression ( '|' exclusive_or_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:954:4: exclusive_or_expression ( '|' exclusive_or_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_exclusive_or_expression_in_inclusive_or_expression2662);
            exclusive_or_expression262=exclusive_or_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, exclusive_or_expression262.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:954:28: ( '|' exclusive_or_expression )*
            loop73:
            do {
                int alt73=2;
                alt73 = dfa73.predict(input);
                switch (alt73) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:954:29: '|' exclusive_or_expression
            	    {
            	    char_literal263=(Token)match(input,102,FOLLOW_102_in_inclusive_or_expression2665); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal263_tree = (CommonTree)adaptor.create(char_literal263);
            	    adaptor.addChild(root_0, char_literal263_tree);
            	    }
            	    pushFollow(FOLLOW_exclusive_or_expression_in_inclusive_or_expression2667);
            	    exclusive_or_expression264=exclusive_or_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, exclusive_or_expression264.getTree());

            	    }
            	    break;

            	default :
            	    break loop73;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 57, inclusive_or_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "inclusive_or_expression"

    public static class exclusive_or_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "exclusive_or_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:957:1: exclusive_or_expression : and_expression ( '^' and_expression )* ;
    public final PretCParser.exclusive_or_expression_return exclusive_or_expression() throws RecognitionException {
        PretCParser.exclusive_or_expression_return retval = new PretCParser.exclusive_or_expression_return();
        retval.start = input.LT(1);
        int exclusive_or_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal266=null;
        PretCParser.and_expression_return and_expression265 = null;

        PretCParser.and_expression_return and_expression267 = null;


        CommonTree char_literal266_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 58) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:958:2: ( and_expression ( '^' and_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:958:4: and_expression ( '^' and_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_and_expression_in_exclusive_or_expression2680);
            and_expression265=and_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, and_expression265.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:958:19: ( '^' and_expression )*
            loop74:
            do {
                int alt74=2;
                alt74 = dfa74.predict(input);
                switch (alt74) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:958:20: '^' and_expression
            	    {
            	    char_literal266=(Token)match(input,103,FOLLOW_103_in_exclusive_or_expression2683); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal266_tree = (CommonTree)adaptor.create(char_literal266);
            	    adaptor.addChild(root_0, char_literal266_tree);
            	    }
            	    pushFollow(FOLLOW_and_expression_in_exclusive_or_expression2685);
            	    and_expression267=and_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, and_expression267.getTree());

            	    }
            	    break;

            	default :
            	    break loop74;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 58, exclusive_or_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "exclusive_or_expression"

    public static class and_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "and_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:961:1: and_expression : equality_expression ( '&' equality_expression )* ;
    public final PretCParser.and_expression_return and_expression() throws RecognitionException {
        PretCParser.and_expression_return retval = new PretCParser.and_expression_return();
        retval.start = input.LT(1);
        int and_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal269=null;
        PretCParser.equality_expression_return equality_expression268 = null;

        PretCParser.equality_expression_return equality_expression270 = null;


        CommonTree char_literal269_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 59) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:962:2: ( equality_expression ( '&' equality_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:962:4: equality_expression ( '&' equality_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_equality_expression_in_and_expression2698);
            equality_expression268=equality_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, equality_expression268.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:962:24: ( '&' equality_expression )*
            loop75:
            do {
                int alt75=2;
                alt75 = dfa75.predict(input);
                switch (alt75) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:962:25: '&' equality_expression
            	    {
            	    char_literal269=(Token)match(input,86,FOLLOW_86_in_and_expression2701); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal269_tree = (CommonTree)adaptor.create(char_literal269);
            	    adaptor.addChild(root_0, char_literal269_tree);
            	    }
            	    pushFollow(FOLLOW_equality_expression_in_and_expression2703);
            	    equality_expression270=equality_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, equality_expression270.getTree());

            	    }
            	    break;

            	default :
            	    break loop75;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 59, and_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "and_expression"

    public static class equality_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "equality_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:964:1: equality_expression : relational_expression ( ( '==' | '!=' ) relational_expression )* ;
    public final PretCParser.equality_expression_return equality_expression() throws RecognitionException {
        PretCParser.equality_expression_return retval = new PretCParser.equality_expression_return();
        retval.start = input.LT(1);
        int equality_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token set272=null;
        PretCParser.relational_expression_return relational_expression271 = null;

        PretCParser.relational_expression_return relational_expression273 = null;


        CommonTree set272_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 60) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:965:2: ( relational_expression ( ( '==' | '!=' ) relational_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:965:4: relational_expression ( ( '==' | '!=' ) relational_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_relational_expression_in_equality_expression2715);
            relational_expression271=relational_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, relational_expression271.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:965:26: ( ( '==' | '!=' ) relational_expression )*
            loop76:
            do {
                int alt76=2;
                alt76 = dfa76.predict(input);
                switch (alt76) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:965:27: ( '==' | '!=' ) relational_expression
            	    {
            	    set272=(Token)input.LT(1);
            	    if ( (input.LA(1)>=104 && input.LA(1)<=105) ) {
            	        input.consume();
            	        if ( state.backtracking==0 ) adaptor.addChild(root_0, (CommonTree)adaptor.create(set272));
            	        state.errorRecovery=false;state.failed=false;
            	    }
            	    else {
            	        if (state.backtracking>0) {state.failed=true; return retval;}
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        throw mse;
            	    }

            	    pushFollow(FOLLOW_relational_expression_in_equality_expression2724);
            	    relational_expression273=relational_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, relational_expression273.getTree());

            	    }
            	    break;

            	default :
            	    break loop76;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 60, equality_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "equality_expression"

    public static class relational_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "relational_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:968:1: relational_expression : shift_expression ( ( '<' | '>' | '<=' | '>=' ) shift_expression )* ;
    public final PretCParser.relational_expression_return relational_expression() throws RecognitionException {
        PretCParser.relational_expression_return retval = new PretCParser.relational_expression_return();
        retval.start = input.LT(1);
        int relational_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token set275=null;
        PretCParser.shift_expression_return shift_expression274 = null;

        PretCParser.shift_expression_return shift_expression276 = null;


        CommonTree set275_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 61) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:969:2: ( shift_expression ( ( '<' | '>' | '<=' | '>=' ) shift_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:969:4: shift_expression ( ( '<' | '>' | '<=' | '>=' ) shift_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_shift_expression_in_relational_expression2737);
            shift_expression274=shift_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, shift_expression274.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:969:21: ( ( '<' | '>' | '<=' | '>=' ) shift_expression )*
            loop77:
            do {
                int alt77=2;
                alt77 = dfa77.predict(input);
                switch (alt77) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:969:22: ( '<' | '>' | '<=' | '>=' ) shift_expression
            	    {
            	    set275=(Token)input.LT(1);
            	    if ( (input.LA(1)>=106 && input.LA(1)<=109) ) {
            	        input.consume();
            	        if ( state.backtracking==0 ) adaptor.addChild(root_0, (CommonTree)adaptor.create(set275));
            	        state.errorRecovery=false;state.failed=false;
            	    }
            	    else {
            	        if (state.backtracking>0) {state.failed=true; return retval;}
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        throw mse;
            	    }

            	    pushFollow(FOLLOW_shift_expression_in_relational_expression2750);
            	    shift_expression276=shift_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, shift_expression276.getTree());

            	    }
            	    break;

            	default :
            	    break loop77;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 61, relational_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "relational_expression"

    public static class shift_expression_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "shift_expression"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:972:1: shift_expression : additive_expression ( ( '<<' | '>>' ) additive_expression )* ;
    public final PretCParser.shift_expression_return shift_expression() throws RecognitionException {
        PretCParser.shift_expression_return retval = new PretCParser.shift_expression_return();
        retval.start = input.LT(1);
        int shift_expression_StartIndex = input.index();
        CommonTree root_0 = null;

        Token set278=null;
        PretCParser.additive_expression_return additive_expression277 = null;

        PretCParser.additive_expression_return additive_expression279 = null;


        CommonTree set278_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 62) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:973:2: ( additive_expression ( ( '<<' | '>>' ) additive_expression )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:973:4: additive_expression ( ( '<<' | '>>' ) additive_expression )*
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_additive_expression_in_shift_expression2766);
            additive_expression277=additive_expression();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, additive_expression277.getTree());
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:973:24: ( ( '<<' | '>>' ) additive_expression )*
            loop78:
            do {
                int alt78=2;
                alt78 = dfa78.predict(input);
                switch (alt78) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:973:25: ( '<<' | '>>' ) additive_expression
            	    {
            	    set278=(Token)input.LT(1);
            	    if ( (input.LA(1)>=110 && input.LA(1)<=111) ) {
            	        input.consume();
            	        if ( state.backtracking==0 ) adaptor.addChild(root_0, (CommonTree)adaptor.create(set278));
            	        state.errorRecovery=false;state.failed=false;
            	    }
            	    else {
            	        if (state.backtracking>0) {state.failed=true; return retval;}
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        throw mse;
            	    }

            	    pushFollow(FOLLOW_additive_expression_in_shift_expression2775);
            	    additive_expression279=additive_expression();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, additive_expression279.getTree());

            	    }
            	    break;

            	default :
            	    break loop78;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 62, shift_expression_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "shift_expression"

    public static class statement_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:978:1: statement : ( labeled_statement -> ^( LABELED_STATMENT_TOK ID_TOK[\"\"+(ID)] labeled_statement ) | expression_statement | selection_statement | iteration_statement | jump_statement -> ^( JUMP_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$jump_statement.text] ) | parallel_statement | 'EOT' ';' -> ^( 'EOT' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) | preemption_statment | scope_statement );
    public final PretCParser.statement_return statement() throws RecognitionException {
        nodes_stack.push(new nodes_scope());

        PretCParser.statement_return retval = new PretCParser.statement_return();
        retval.start = input.LT(1);
        int statement_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal286=null;
        Token char_literal287=null;
        PretCParser.labeled_statement_return labeled_statement280 = null;

        PretCParser.expression_statement_return expression_statement281 = null;

        PretCParser.selection_statement_return selection_statement282 = null;

        PretCParser.iteration_statement_return iteration_statement283 = null;

        PretCParser.jump_statement_return jump_statement284 = null;

        PretCParser.parallel_statement_return parallel_statement285 = null;

        PretCParser.preemption_statment_return preemption_statment288 = null;

        PretCParser.scope_statement_return scope_statement289 = null;


        CommonTree string_literal286_tree=null;
        CommonTree char_literal287_tree=null;
        RewriteRuleTokenStream stream_112=new RewriteRuleTokenStream(adaptor,"token 112");
        RewriteRuleTokenStream stream_41=new RewriteRuleTokenStream(adaptor,"token 41");
        RewriteRuleSubtreeStream stream_labeled_statement=new RewriteRuleSubtreeStream(adaptor,"rule labeled_statement");
        RewriteRuleSubtreeStream stream_jump_statement=new RewriteRuleSubtreeStream(adaptor,"rule jump_statement");

          ((nodes_scope)nodes_stack.peek()).node = new StatementNode();
          long ID=-1;
          long lineNo = input.LT(1).getLine();

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 63) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:985:2: ( labeled_statement -> ^( LABELED_STATMENT_TOK ID_TOK[\"\"+(ID)] labeled_statement ) | expression_statement | selection_statement | iteration_statement | jump_statement -> ^( JUMP_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$jump_statement.text] ) | parallel_statement | 'EOT' ';' -> ^( 'EOT' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) | preemption_statment | scope_statement )
            int alt79=9;
            alt79 = dfa79.predict(input);
            switch (alt79) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:985:4: labeled_statement
                    {
                    pushFollow(FOLLOW_labeled_statement_in_statement2800);
                    labeled_statement280=labeled_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_labeled_statement.add(labeled_statement280.getTree());
                    if ( state.backtracking==0 ) {

                      			//sourceTemp = (labeled_statement280!=null?input.toString(labeled_statement280.start,labeled_statement280.stop):null);
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			//((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: labeled_statement
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 998:5: -> ^( LABELED_STATMENT_TOK ID_TOK[\"\"+(ID)] labeled_statement )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:998:8: ^( LABELED_STATMENT_TOK ID_TOK[\"\"+(ID)] labeled_statement )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(LABELED_STATMENT_TOK, "LABELED_STATMENT_TOK"), root_1);

                        adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_1, stream_labeled_statement.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1000:4: expression_statement
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_expression_statement_in_statement2823);
                    expression_statement281=expression_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, expression_statement281.getTree());

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1001:4: selection_statement
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_selection_statement_in_statement2829);
                    selection_statement282=selection_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, selection_statement282.getTree());

                    }
                    break;
                case 4 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1002:4: iteration_statement
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_iteration_statement_in_statement2835);
                    iteration_statement283=iteration_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, iteration_statement283.getTree());

                    }
                    break;
                case 5 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1003:4: jump_statement
                    {
                    pushFollow(FOLLOW_jump_statement_in_statement2841);
                    jump_statement284=jump_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_jump_statement.add(jump_statement284.getTree());
                    if ( state.backtracking==0 ) {

                      			sourceTemp = (jump_statement284!=null?input.toString(jump_statement284.start,jump_statement284.stop):null);
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1016:5: -> ^( JUMP_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$jump_statement.text] )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1016:8: ^( JUMP_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$jump_statement.text] )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(JUMP_STATMENT_TOK, "JUMP_STATMENT_TOK"), root_1);

                        adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, (jump_statement284!=null?input.toString(jump_statement284.start,jump_statement284.stop):null)));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 6 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1017:4: parallel_statement
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_parallel_statement_in_statement2864);
                    parallel_statement285=parallel_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, parallel_statement285.getTree());

                    }
                    break;
                case 7 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1018:4: 'EOT' ';'
                    {
                    string_literal286=(Token)match(input,112,FOLLOW_112_in_statement2870); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_112.add(string_literal286);

                    char_literal287=(Token)match(input,41,FOLLOW_41_in_statement2872); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal287);

                    if ( state.backtracking==0 ) {

                      			sourceTemp = "EOT;";
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			((nodes_scope)nodes_stack.peek()).node.type="EOT";	
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: 112
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1032:5: -> ^( 'EOT' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1032:8: ^( 'EOT' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot(stream_112.nextNode(), root_1);

                        adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 8 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1033:4: preemption_statment
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_preemption_statment_in_statement2894);
                    preemption_statment288=preemption_statment();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, preemption_statment288.getTree());

                    }
                    break;
                case 9 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1034:4: scope_statement
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_scope_statement_in_statement2899);
                    scope_statement289=scope_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, scope_statement289.getTree());

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 63, statement_StartIndex); }
            nodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "statement"

    public static class labeled_statement_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "labeled_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1037:1: labeled_statement : ( IDENTIFIER ':' -> SOURCE_TOK[$IDENTIFIER.text+\":\"] | 'case' constant_expression ':' -> SOURCE_TOK[\"case \"+$constant_expression.text+\":\"] | 'default' ':' -> SOURCE_TOK[\"default:\"] );
    public final PretCParser.labeled_statement_return labeled_statement() throws RecognitionException {
        PretCParser.labeled_statement_return retval = new PretCParser.labeled_statement_return();
        retval.start = input.LT(1);
        int labeled_statement_StartIndex = input.index();
        CommonTree root_0 = null;

        Token IDENTIFIER290=null;
        Token char_literal291=null;
        Token string_literal292=null;
        Token char_literal294=null;
        Token string_literal295=null;
        Token char_literal296=null;
        PretCParser.constant_expression_return constant_expression293 = null;


        CommonTree IDENTIFIER290_tree=null;
        CommonTree char_literal291_tree=null;
        CommonTree string_literal292_tree=null;
        CommonTree char_literal294_tree=null;
        CommonTree string_literal295_tree=null;
        CommonTree char_literal296_tree=null;
        RewriteRuleTokenStream stream_114=new RewriteRuleTokenStream(adaptor,"token 114");
        RewriteRuleTokenStream stream_69=new RewriteRuleTokenStream(adaptor,"token 69");
        RewriteRuleTokenStream stream_113=new RewriteRuleTokenStream(adaptor,"token 113");
        RewriteRuleTokenStream stream_IDENTIFIER=new RewriteRuleTokenStream(adaptor,"token IDENTIFIER");
        RewriteRuleSubtreeStream stream_constant_expression=new RewriteRuleSubtreeStream(adaptor,"rule constant_expression");
        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 64) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1038:2: ( IDENTIFIER ':' -> SOURCE_TOK[$IDENTIFIER.text+\":\"] | 'case' constant_expression ':' -> SOURCE_TOK[\"case \"+$constant_expression.text+\":\"] | 'default' ':' -> SOURCE_TOK[\"default:\"] )
            int alt80=3;
            switch ( input.LA(1) ) {
            case IDENTIFIER:
                {
                alt80=1;
                }
                break;
            case 113:
                {
                alt80=2;
                }
                break;
            case 114:
                {
                alt80=3;
                }
                break;
            default:
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 80, 0, input);

                throw nvae;
            }

            switch (alt80) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1038:4: IDENTIFIER ':'
                    {
                    IDENTIFIER290=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_labeled_statement2910); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_IDENTIFIER.add(IDENTIFIER290);

                    char_literal291=(Token)match(input,69,FOLLOW_69_in_labeled_statement2912); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_69.add(char_literal291);

                    if ( state.backtracking==0 ) {

                      			sourceTemp = (IDENTIFIER290!=null?IDENTIFIER290.getText():null)+":";
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			((nodes_scope)nodes_stack.peek()).node.name.add((IDENTIFIER290!=null?IDENTIFIER290.getText():null));
                      			((nodes_scope)nodes_stack.peek()).node.type="label";	
                      		
                    }


                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1045:3: -> SOURCE_TOK[$IDENTIFIER.text+\":\"]
                    {
                        adaptor.addChild(root_0, (CommonTree)adaptor.create(SOURCE_TOK, (IDENTIFIER290!=null?IDENTIFIER290.getText():null)+":"));

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1046:4: 'case' constant_expression ':'
                    {
                    string_literal292=(Token)match(input,113,FOLLOW_113_in_labeled_statement2932); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_113.add(string_literal292);

                    pushFollow(FOLLOW_constant_expression_in_labeled_statement2934);
                    constant_expression293=constant_expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_constant_expression.add(constant_expression293.getTree());
                    char_literal294=(Token)match(input,69,FOLLOW_69_in_labeled_statement2936); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_69.add(char_literal294);

                    if ( state.backtracking==0 ) {

                      			sourceTemp = "case "+(constant_expression293!=null?input.toString(constant_expression293.start,constant_expression293.stop):null)+":";
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			((nodes_scope)nodes_stack.peek()).node.type="case";	
                      			//((nodes_scope)nodes_stack.peek()).node.constantStatement.add((constant_expression293!=null?input.toString(constant_expression293.start,constant_expression293.stop):null));
                      		
                    }


                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1053:3: -> SOURCE_TOK[\"case \"+$constant_expression.text+\":\"]
                    {
                        adaptor.addChild(root_0, (CommonTree)adaptor.create(SOURCE_TOK, "case "+(constant_expression293!=null?input.toString(constant_expression293.start,constant_expression293.stop):null)+":"));

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1054:4: 'default' ':'
                    {
                    string_literal295=(Token)match(input,114,FOLLOW_114_in_labeled_statement2957); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_114.add(string_literal295);

                    char_literal296=(Token)match(input,69,FOLLOW_69_in_labeled_statement2959); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_69.add(char_literal296);

                    if ( state.backtracking==0 ) {

                      			sourceTemp = "default:";
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			((nodes_scope)nodes_stack.peek()).node.type="default";	
                      			//((nodes_scope)nodes_stack.peek()).node.constantStatement.add($constant_expression.text);
                      		
                    }


                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1061:3: -> SOURCE_TOK[\"default:\"]
                    {
                        adaptor.addChild(root_0, (CommonTree)adaptor.create(SOURCE_TOK, "default:"));

                    }

                    retval.tree = root_0;}
                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 64, labeled_statement_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "labeled_statement"

    public static class scope_statement_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "scope_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1064:1: scope_statement : ( '{' '}' -> ^( SCOPE_TOK EMPTY_TOK END_TOK ) | '{' compound_statement '}' -> ^( SCOPE_TOK compound_statement END_TOK ) );
    public final PretCParser.scope_statement_return scope_statement() throws RecognitionException {
        scopeNodes_stack.push(new scopeNodes_scope());

        PretCParser.scope_statement_return retval = new PretCParser.scope_statement_return();
        retval.start = input.LT(1);
        int scope_statement_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal297=null;
        Token char_literal298=null;
        Token char_literal299=null;
        Token char_literal301=null;
        PretCParser.compound_statement_return compound_statement300 = null;


        CommonTree char_literal297_tree=null;
        CommonTree char_literal298_tree=null;
        CommonTree char_literal299_tree=null;
        CommonTree char_literal301_tree=null;
        RewriteRuleTokenStream stream_66=new RewriteRuleTokenStream(adaptor,"token 66");
        RewriteRuleTokenStream stream_65=new RewriteRuleTokenStream(adaptor,"token 65");
        RewriteRuleSubtreeStream stream_compound_statement=new RewriteRuleSubtreeStream(adaptor,"rule compound_statement");

          long previousScope = currentScope;
          //dont put in init , init can prograss more than once when findingin which is right


        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 65) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1078:2: ( '{' '}' -> ^( SCOPE_TOK EMPTY_TOK END_TOK ) | '{' compound_statement '}' -> ^( SCOPE_TOK compound_statement END_TOK ) )
            int alt81=2;
            alt81 = dfa81.predict(input);
            switch (alt81) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1078:4: '{' '}'
                    {
                    char_literal297=(Token)match(input,65,FOLLOW_65_in_scope_statement3001); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_65.add(char_literal297);

                    if ( state.backtracking==0 ) {

                      		  currentScope = ++scopeCount;
                      		  ((scopeNodes_scope)scopeNodes_stack.peek()).node = new ScopeNode(currentScope);
                      		  ((scopeNodes_scope)scopeNodes_stack.peek()).node.parentID = previousScope;
                      		 // System.out.println(currentScope);
                      		
                    }
                    char_literal298=(Token)match(input,66,FOLLOW_66_in_scope_statement3011); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_66.add(char_literal298);



                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1085:8: -> ^( SCOPE_TOK EMPTY_TOK END_TOK )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1085:11: ^( SCOPE_TOK EMPTY_TOK END_TOK )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(SCOPE_TOK, "SCOPE_TOK"), root_1);

                        adaptor.addChild(root_1, (CommonTree)adaptor.create(EMPTY_TOK, "EMPTY_TOK"));
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(END_TOK, "END_TOK"));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1086:4: '{' compound_statement '}'
                    {
                    char_literal299=(Token)match(input,65,FOLLOW_65_in_scope_statement3027); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_65.add(char_literal299);

                    if ( state.backtracking==0 ) {

                      		  currentScope = ++scopeCount;
                      		  ((scopeNodes_scope)scopeNodes_stack.peek()).node = new ScopeNode(currentScope);
                      		  ((scopeNodes_scope)scopeNodes_stack.peek()).node.parentID = previousScope;
                      		//  System.out.println(currentScope);
                      		
                    }
                    pushFollow(FOLLOW_compound_statement_in_scope_statement3038);
                    compound_statement300=compound_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_compound_statement.add(compound_statement300.getTree());
                    char_literal301=(Token)match(input,66,FOLLOW_66_in_scope_statement3040); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_66.add(char_literal301);



                    // AST REWRITE
                    // elements: compound_statement
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1093:28: -> ^( SCOPE_TOK compound_statement END_TOK )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1093:31: ^( SCOPE_TOK compound_statement END_TOK )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(SCOPE_TOK, "SCOPE_TOK"), root_1);

                        adaptor.addChild(root_1, stream_compound_statement.nextTree());
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(END_TOK, "END_TOK"));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {

                scopeList.put(currentScope,((scopeNodes_scope)scopeNodes_stack.peek()).node);
               // System.out.println("A"+currentScope);
                currentScope = previousScope;
                

            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 65, scope_statement_StartIndex); }
            scopeNodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "scope_statement"

    public static class condition_statement_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "condition_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1095:1: condition_statement : ( ( '{' ( compound_statement )? '}' )=> scope_statement | ( declaration | statement ) -> ^( SCOPE_TOK ( declaration )? ( statement )? END_TOK ) );
    public final PretCParser.condition_statement_return condition_statement() throws RecognitionException {
        scopeNodes_stack.push(new scopeNodes_scope());

        PretCParser.condition_statement_return retval = new PretCParser.condition_statement_return();
        retval.start = input.LT(1);
        int condition_statement_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.scope_statement_return scope_statement302 = null;

        PretCParser.declaration_return declaration303 = null;

        PretCParser.statement_return statement304 = null;


        RewriteRuleSubtreeStream stream_statement=new RewriteRuleSubtreeStream(adaptor,"rule statement");
        RewriteRuleSubtreeStream stream_declaration=new RewriteRuleSubtreeStream(adaptor,"rule declaration");

          long previousScope = currentScope;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 66) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1100:2: ( ( '{' ( compound_statement )? '}' )=> scope_statement | ( declaration | statement ) -> ^( SCOPE_TOK ( declaration )? ( statement )? END_TOK ) )
            int alt83=2;
            alt83 = dfa83.predict(input);
            switch (alt83) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1100:4: ( '{' ( compound_statement )? '}' )=> scope_statement
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_scope_statement_in_condition_statement3084);
                    scope_statement302=scope_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, scope_statement302.getTree());

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1101:4: ( declaration | statement )
                    {
                    if ( state.backtracking==0 ) {
                      currentScope = ++scopeCount; ((scopeNodes_scope)scopeNodes_stack.peek()).node = new ScopeNode(currentScope);((scopeNodes_scope)scopeNodes_stack.peek()).node.parentID = previousScope;
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1101:126: ( declaration | statement )
                    int alt82=2;
                    alt82 = dfa82.predict(input);
                    switch (alt82) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1101:127: declaration
                            {
                            pushFollow(FOLLOW_declaration_in_condition_statement3091);
                            declaration303=declaration();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) stream_declaration.add(declaration303.getTree());

                            }
                            break;
                        case 2 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1101:139: statement
                            {
                            pushFollow(FOLLOW_statement_in_condition_statement3093);
                            statement304=statement();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) stream_statement.add(statement304.getTree());

                            }
                            break;

                    }

                    if ( state.backtracking==0 ) {
                      scopeList.put(currentScope,((scopeNodes_scope)scopeNodes_stack.peek()).node);currentScope = previousScope;
                    }


                    // AST REWRITE
                    // elements: declaration, statement
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1101:229: -> ^( SCOPE_TOK ( declaration )? ( statement )? END_TOK )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1101:232: ^( SCOPE_TOK ( declaration )? ( statement )? END_TOK )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(SCOPE_TOK, "SCOPE_TOK"), root_1);

                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1101:244: ( declaration )?
                        if ( stream_declaration.hasNext() ) {
                            adaptor.addChild(root_1, stream_declaration.nextTree());

                        }
                        stream_declaration.reset();
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1101:257: ( statement )?
                        if ( stream_statement.hasNext() ) {
                            adaptor.addChild(root_1, stream_statement.nextTree());

                        }
                        stream_statement.reset();
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(END_TOK, "END_TOK"));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 66, condition_statement_StartIndex); }
            scopeNodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "condition_statement"

    public static class compound_statement_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "compound_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1104:1: compound_statement : ( declaration | statement_list )* ;
    public final PretCParser.compound_statement_return compound_statement() throws RecognitionException {
        Symbols_stack.push(new Symbols_scope());

        PretCParser.compound_statement_return retval = new PretCParser.compound_statement_return();
        retval.start = input.LT(1);
        int compound_statement_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.declaration_return declaration305 = null;

        PretCParser.statement_list_return statement_list306 = null;




          ((Symbols_scope)Symbols_stack.peek()).types = new HashSet();

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 67) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1109:2: ( ( declaration | statement_list )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1109:4: ( declaration | statement_list )*
            {
            root_0 = (CommonTree)adaptor.nil();

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1109:4: ( declaration | statement_list )*
            loop84:
            do {
                int alt84=3;
                alt84 = dfa84.predict(input);
                switch (alt84) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1109:5: declaration
            	    {
            	    pushFollow(FOLLOW_declaration_in_compound_statement3139);
            	    declaration305=declaration();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, declaration305.getTree());

            	    }
            	    break;
            	case 2 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1109:17: statement_list
            	    {
            	    pushFollow(FOLLOW_statement_list_in_compound_statement3141);
            	    statement_list306=statement_list();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, statement_list306.getTree());

            	    }
            	    break;

            	default :
            	    break loop84;
                }
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 67, compound_statement_StartIndex); }
            Symbols_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "compound_statement"

    public static class statement_list_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "statement_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1112:1: statement_list : ( statement )+ ;
    public final PretCParser.statement_list_return statement_list() throws RecognitionException {
        PretCParser.statement_list_return retval = new PretCParser.statement_list_return();
        retval.start = input.LT(1);
        int statement_list_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCParser.statement_return statement307 = null;



        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 68) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1113:2: ( ( statement )+ )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1113:4: ( statement )+
            {
            root_0 = (CommonTree)adaptor.nil();

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1113:4: ( statement )+
            int cnt85=0;
            loop85:
            do {
                int alt85=2;
                alt85 = dfa85.predict(input);
                switch (alt85) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: statement
            	    {
            	    pushFollow(FOLLOW_statement_in_statement_list3156);
            	    statement307=statement();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, statement307.getTree());

            	    }
            	    break;

            	default :
            	    if ( cnt85 >= 1 ) break loop85;
            	    if (state.backtracking>0) {state.failed=true; return retval;}
                        EarlyExitException eee =
                            new EarlyExitException(85, input);
                        throw eee;
                }
                cnt85++;
            } while (true);


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 68, statement_list_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "statement_list"

    public static class preemption_statment_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "preemption_statment"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1117:1: preemption_statment : ( 'sabort' condition_statement 'when' '(' expression ')' ';' -> ^( ABORT_TOK ^( 'sabort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement ) | 'abort' condition_statement 'when' '(' expression ')' ';' -> ^( ABORT_TOK ^( 'abort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement ) | 'wabort' condition_statement 'when' '(' expression ')' ';' -> ^( ABORT_TOK ^( 'wabort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement ) );
    public final PretCParser.preemption_statment_return preemption_statment() throws RecognitionException {
        PretCParser.preemption_statment_return retval = new PretCParser.preemption_statment_return();
        retval.start = input.LT(1);
        int preemption_statment_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal308=null;
        Token string_literal310=null;
        Token char_literal311=null;
        Token char_literal313=null;
        Token char_literal314=null;
        Token string_literal315=null;
        Token string_literal317=null;
        Token char_literal318=null;
        Token char_literal320=null;
        Token char_literal321=null;
        Token string_literal322=null;
        Token string_literal324=null;
        Token char_literal325=null;
        Token char_literal327=null;
        Token char_literal328=null;
        PretCParser.condition_statement_return condition_statement309 = null;

        PretCParser.expression_return expression312 = null;

        PretCParser.condition_statement_return condition_statement316 = null;

        PretCParser.expression_return expression319 = null;

        PretCParser.condition_statement_return condition_statement323 = null;

        PretCParser.expression_return expression326 = null;


        CommonTree string_literal308_tree=null;
        CommonTree string_literal310_tree=null;
        CommonTree char_literal311_tree=null;
        CommonTree char_literal313_tree=null;
        CommonTree char_literal314_tree=null;
        CommonTree string_literal315_tree=null;
        CommonTree string_literal317_tree=null;
        CommonTree char_literal318_tree=null;
        CommonTree char_literal320_tree=null;
        CommonTree char_literal321_tree=null;
        CommonTree string_literal322_tree=null;
        CommonTree string_literal324_tree=null;
        CommonTree char_literal325_tree=null;
        CommonTree char_literal327_tree=null;
        CommonTree char_literal328_tree=null;
        RewriteRuleTokenStream stream_49=new RewriteRuleTokenStream(adaptor,"token 49");
        RewriteRuleTokenStream stream_116=new RewriteRuleTokenStream(adaptor,"token 116");
        RewriteRuleTokenStream stream_117=new RewriteRuleTokenStream(adaptor,"token 117");
        RewriteRuleTokenStream stream_115=new RewriteRuleTokenStream(adaptor,"token 115");
        RewriteRuleTokenStream stream_41=new RewriteRuleTokenStream(adaptor,"token 41");
        RewriteRuleTokenStream stream_51=new RewriteRuleTokenStream(adaptor,"token 51");
        RewriteRuleTokenStream stream_118=new RewriteRuleTokenStream(adaptor,"token 118");
        RewriteRuleSubtreeStream stream_condition_statement=new RewriteRuleSubtreeStream(adaptor,"rule condition_statement");
        RewriteRuleSubtreeStream stream_expression=new RewriteRuleSubtreeStream(adaptor,"rule expression");

         
        	long ID=-1; 
        	long lineNo = input.LT(1).getLine();

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 69) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1123:2: ( 'sabort' condition_statement 'when' '(' expression ')' ';' -> ^( ABORT_TOK ^( 'sabort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement ) | 'abort' condition_statement 'when' '(' expression ')' ';' -> ^( ABORT_TOK ^( 'abort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement ) | 'wabort' condition_statement 'when' '(' expression ')' ';' -> ^( ABORT_TOK ^( 'wabort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement ) )
            int alt86=3;
            switch ( input.LA(1) ) {
            case 115:
                {
                alt86=1;
                }
                break;
            case 117:
                {
                alt86=2;
                }
                break;
            case 118:
                {
                alt86=3;
                }
                break;
            default:
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 86, 0, input);

                throw nvae;
            }

            switch (alt86) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1123:4: 'sabort' condition_statement 'when' '(' expression ')' ';'
                    {
                    string_literal308=(Token)match(input,115,FOLLOW_115_in_preemption_statment3174); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_115.add(string_literal308);

                    if ( state.backtracking==0 ) {

                      			
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.type="strongAbort";				

                      		
                    }
                    pushFollow(FOLLOW_condition_statement_in_preemption_statment3180);
                    condition_statement309=condition_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_condition_statement.add(condition_statement309.getTree());
                    string_literal310=(Token)match(input,116,FOLLOW_116_in_preemption_statment3182); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_116.add(string_literal310);

                    char_literal311=(Token)match(input,49,FOLLOW_49_in_preemption_statment3184); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_49.add(char_literal311);

                    pushFollow(FOLLOW_expression_in_preemption_statment3186);
                    expression312=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_expression.add(expression312.getTree());
                    char_literal313=(Token)match(input,51,FOLLOW_51_in_preemption_statment3188); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_51.add(char_literal313);

                    char_literal314=(Token)match(input,41,FOLLOW_41_in_preemption_statment3190); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal314);

                    if ( state.backtracking==0 ) {

                      			sourceTemp = "strong abort{...} when("+(expression312!=null?input.toString(expression312.start,expression312.stop):null)+");" ;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = (expression312!=null?input.toString(expression312.start,expression312.stop):null);
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: condition_statement, 115
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1143:3: -> ^( ABORT_TOK ^( 'sabort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1143:7: ^( ABORT_TOK ^( 'sabort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(ABORT_TOK, "ABORT_TOK"), root_1);

                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1143:19: ^( 'sabort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] )
                        {
                        CommonTree root_2 = (CommonTree)adaptor.nil();
                        root_2 = (CommonTree)adaptor.becomeRoot(stream_115.nextNode(), root_2);

                        adaptor.addChild(root_2, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_2, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));

                        adaptor.addChild(root_1, root_2);
                        }
                        adaptor.addChild(root_1, stream_condition_statement.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1144:4: 'abort' condition_statement 'when' '(' expression ')' ';'
                    {
                    string_literal315=(Token)match(input,117,FOLLOW_117_in_preemption_statment3222); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_117.add(string_literal315);

                    if ( state.backtracking==0 ) {

                      			
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.type="strongAbort";				

                      		
                    }
                    pushFollow(FOLLOW_condition_statement_in_preemption_statment3228);
                    condition_statement316=condition_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_condition_statement.add(condition_statement316.getTree());
                    string_literal317=(Token)match(input,116,FOLLOW_116_in_preemption_statment3230); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_116.add(string_literal317);

                    char_literal318=(Token)match(input,49,FOLLOW_49_in_preemption_statment3232); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_49.add(char_literal318);

                    pushFollow(FOLLOW_expression_in_preemption_statment3234);
                    expression319=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_expression.add(expression319.getTree());
                    char_literal320=(Token)match(input,51,FOLLOW_51_in_preemption_statment3236); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_51.add(char_literal320);

                    char_literal321=(Token)match(input,41,FOLLOW_41_in_preemption_statment3238); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal321);

                    if ( state.backtracking==0 ) {

                      			sourceTemp = "strong abort{...} when("+(expression319!=null?input.toString(expression319.start,expression319.stop):null)+");" ;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = (expression319!=null?input.toString(expression319.start,expression319.stop):null);
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: 117, condition_statement
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1164:3: -> ^( ABORT_TOK ^( 'abort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1164:7: ^( ABORT_TOK ^( 'abort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(ABORT_TOK, "ABORT_TOK"), root_1);

                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1164:19: ^( 'abort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] )
                        {
                        CommonTree root_2 = (CommonTree)adaptor.nil();
                        root_2 = (CommonTree)adaptor.becomeRoot(stream_117.nextNode(), root_2);

                        adaptor.addChild(root_2, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_2, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));

                        adaptor.addChild(root_1, root_2);
                        }
                        adaptor.addChild(root_1, stream_condition_statement.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1165:4: 'wabort' condition_statement 'when' '(' expression ')' ';'
                    {
                    string_literal322=(Token)match(input,118,FOLLOW_118_in_preemption_statment3270); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_118.add(string_literal322);

                    if ( state.backtracking==0 ) {

                      			
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			
                      			
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.type="weakAbort";	

                      		
                    }
                    pushFollow(FOLLOW_condition_statement_in_preemption_statment3277);
                    condition_statement323=condition_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_condition_statement.add(condition_statement323.getTree());
                    string_literal324=(Token)match(input,116,FOLLOW_116_in_preemption_statment3279); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_116.add(string_literal324);

                    char_literal325=(Token)match(input,49,FOLLOW_49_in_preemption_statment3281); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_49.add(char_literal325);

                    pushFollow(FOLLOW_expression_in_preemption_statment3283);
                    expression326=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_expression.add(expression326.getTree());
                    char_literal327=(Token)match(input,51,FOLLOW_51_in_preemption_statment3285); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_51.add(char_literal327);

                    char_literal328=(Token)match(input,41,FOLLOW_41_in_preemption_statment3287); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal328);

                    if ( state.backtracking==0 ) {
                      	
                      			sourceTemp = "weak abort{...} when("+(expression326!=null?input.toString(expression326.start,expression326.stop):null)+");" ;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = (expression326!=null?input.toString(expression326.start,expression326.stop):null);
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: condition_statement, 118
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1186:3: -> ^( ABORT_TOK ^( 'wabort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1186:7: ^( ABORT_TOK ^( 'wabort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) condition_statement )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(ABORT_TOK, "ABORT_TOK"), root_1);

                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1186:19: ^( 'wabort' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] )
                        {
                        CommonTree root_2 = (CommonTree)adaptor.nil();
                        root_2 = (CommonTree)adaptor.becomeRoot(stream_118.nextNode(), root_2);

                        adaptor.addChild(root_2, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_2, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));

                        adaptor.addChild(root_1, root_2);
                        }
                        adaptor.addChild(root_1, stream_condition_statement.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 69, preemption_statment_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "preemption_statment"

    public static class parallel_statement_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "parallel_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1189:1: parallel_statement : 'PAR' '(' ( (i1= IDENTIFIER ) | ( 'void' ) ) ( ( ( ',' i2= IDENTIFIER )+ ) | ( ',' 'void' ) ) ')' ';' -> ^( 'PAR' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) ;
    public final PretCParser.parallel_statement_return parallel_statement() throws RecognitionException {
        PretCParser.parallel_statement_return retval = new PretCParser.parallel_statement_return();
        retval.start = input.LT(1);
        int parallel_statement_StartIndex = input.index();
        CommonTree root_0 = null;

        Token i1=null;
        Token i2=null;
        Token string_literal329=null;
        Token char_literal330=null;
        Token string_literal331=null;
        Token char_literal332=null;
        Token char_literal333=null;
        Token string_literal334=null;
        Token char_literal335=null;
        Token char_literal336=null;

        CommonTree i1_tree=null;
        CommonTree i2_tree=null;
        CommonTree string_literal329_tree=null;
        CommonTree char_literal330_tree=null;
        CommonTree string_literal331_tree=null;
        CommonTree char_literal332_tree=null;
        CommonTree char_literal333_tree=null;
        CommonTree string_literal334_tree=null;
        CommonTree char_literal335_tree=null;
        CommonTree char_literal336_tree=null;
        RewriteRuleTokenStream stream_49=new RewriteRuleTokenStream(adaptor,"token 49");
        RewriteRuleTokenStream stream_45=new RewriteRuleTokenStream(adaptor,"token 45");
        RewriteRuleTokenStream stream_41=new RewriteRuleTokenStream(adaptor,"token 41");
        RewriteRuleTokenStream stream_51=new RewriteRuleTokenStream(adaptor,"token 51");
        RewriteRuleTokenStream stream_IDENTIFIER=new RewriteRuleTokenStream(adaptor,"token IDENTIFIER");
        RewriteRuleTokenStream stream_50=new RewriteRuleTokenStream(adaptor,"token 50");
        RewriteRuleTokenStream stream_119=new RewriteRuleTokenStream(adaptor,"token 119");


        	sourceTemp = "PAR("; 
        	long ID=-1;
        	long lineNo = input.LT(1).getLine();

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 70) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1195:2: ( 'PAR' '(' ( (i1= IDENTIFIER ) | ( 'void' ) ) ( ( ( ',' i2= IDENTIFIER )+ ) | ( ',' 'void' ) ) ')' ';' -> ^( 'PAR' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1195:4: 'PAR' '(' ( (i1= IDENTIFIER ) | ( 'void' ) ) ( ( ( ',' i2= IDENTIFIER )+ ) | ( ',' 'void' ) ) ')' ';'
            {
            string_literal329=(Token)match(input,119,FOLLOW_119_in_parallel_statement3331); if (state.failed) return retval; 
            if ( state.backtracking==0 ) stream_119.add(string_literal329);

            char_literal330=(Token)match(input,49,FOLLOW_49_in_parallel_statement3333); if (state.failed) return retval; 
            if ( state.backtracking==0 ) stream_49.add(char_literal330);

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1195:14: ( (i1= IDENTIFIER ) | ( 'void' ) )
            int alt87=2;
            int LA87_0 = input.LA(1);

            if ( (LA87_0==IDENTIFIER) ) {
                alt87=1;
            }
            else if ( (LA87_0==50) ) {
                alt87=2;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 87, 0, input);

                throw nvae;
            }
            switch (alt87) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1196:5: (i1= IDENTIFIER )
                    {
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1196:5: (i1= IDENTIFIER )
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1196:6: i1= IDENTIFIER
                    {
                    i1=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_parallel_statement3344); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_IDENTIFIER.add(i1);

                    if ( state.backtracking==0 ) {
                      sourceTemp+=(i1!=null?i1.getText():null);((nodes_scope)nodes_stack.peek()).node.name.add((i1!=null?i1.getText():null));((nodes_scope)nodes_stack.peek()).node.thdInsID.add(uniqueThdInstantID++);
                    }

                    }


                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1198:5: ( 'void' )
                    {
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1198:5: ( 'void' )
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1198:6: 'void'
                    {
                    string_literal331=(Token)match(input,50,FOLLOW_50_in_parallel_statement3360); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_50.add(string_literal331);

                    if ( state.backtracking==0 ) {
                      sourceTemp+="void";
                    }

                    }


                    }
                    break;

            }

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1201:5: ( ( ( ',' i2= IDENTIFIER )+ ) | ( ',' 'void' ) )
            int alt89=2;
            int LA89_0 = input.LA(1);

            if ( (LA89_0==45) ) {
                int LA89_1 = input.LA(2);

                if ( (LA89_1==IDENTIFIER) ) {
                    alt89=1;
                }
                else if ( (LA89_1==50) ) {
                    alt89=2;
                }
                else {
                    if (state.backtracking>0) {state.failed=true; return retval;}
                    NoViableAltException nvae =
                        new NoViableAltException("", 89, 1, input);

                    throw nvae;
                }
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 89, 0, input);

                throw nvae;
            }
            switch (alt89) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1203:5: ( ( ',' i2= IDENTIFIER )+ )
                    {
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1203:5: ( ( ',' i2= IDENTIFIER )+ )
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1204:5: ( ',' i2= IDENTIFIER )+
                    {
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1204:5: ( ',' i2= IDENTIFIER )+
                    int cnt88=0;
                    loop88:
                    do {
                        int alt88=2;
                        int LA88_0 = input.LA(1);

                        if ( (LA88_0==45) ) {
                            alt88=1;
                        }


                        switch (alt88) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1204:6: ',' i2= IDENTIFIER
                    	    {
                    	    char_literal332=(Token)match(input,45,FOLLOW_45_in_parallel_statement3398); if (state.failed) return retval; 
                    	    if ( state.backtracking==0 ) stream_45.add(char_literal332);

                    	    i2=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_parallel_statement3402); if (state.failed) return retval; 
                    	    if ( state.backtracking==0 ) stream_IDENTIFIER.add(i2);

                    	    if ( state.backtracking==0 ) {
                    	      sourceTemp+=','+(i2!=null?i2.getText():null);((nodes_scope)nodes_stack.peek()).node.name.add((i2!=null?i2.getText():null));((nodes_scope)nodes_stack.peek()).node.thdInsID.add(uniqueThdInstantID++);
                    	    }

                    	    }
                    	    break;

                    	default :
                    	    if ( cnt88 >= 1 ) break loop88;
                    	    if (state.backtracking>0) {state.failed=true; return retval;}
                                EarlyExitException eee =
                                    new EarlyExitException(88, input);
                                throw eee;
                        }
                        cnt88++;
                    } while (true);


                    }


                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1207:5: ( ',' 'void' )
                    {
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1207:5: ( ',' 'void' )
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1207:6: ',' 'void'
                    {
                    char_literal333=(Token)match(input,45,FOLLOW_45_in_parallel_statement3425); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_45.add(char_literal333);

                    string_literal334=(Token)match(input,50,FOLLOW_50_in_parallel_statement3427); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_50.add(string_literal334);

                    if ( state.backtracking==0 ) {
                      sourceTemp+=",void";
                    }

                    }


                    }
                    break;

            }

            char_literal335=(Token)match(input,51,FOLLOW_51_in_parallel_statement3442); if (state.failed) return retval; 
            if ( state.backtracking==0 ) stream_51.add(char_literal335);

            char_literal336=(Token)match(input,41,FOLLOW_41_in_parallel_statement3444); if (state.failed) return retval; 
            if ( state.backtracking==0 ) stream_41.add(char_literal336);

            if ( state.backtracking==0 ) {

              			

              				
              			sourceTemp += ");";
              			ID = idCount++;
              			((nodes_scope)nodes_stack.peek()).node.ID=ID;
              			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
              			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
              			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
              			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
              			((nodes_scope)nodes_stack.peek()).node.type="PAR";	
              			//((nodes_scope)nodes_stack.peek()).node.constantStatement.add(";");
              			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
              			if (debug > 0) {
              				System.out.println(nodesTable.get(ID));
              			}
              			
              		
              		
            }


            // AST REWRITE
            // elements: 119
            // token labels: 
            // rule labels: retval
            // token list labels: 
            // rule list labels: 
            // wildcard labels: 
            if ( state.backtracking==0 ) {
            retval.tree = root_0;
            RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

            root_0 = (CommonTree)adaptor.nil();
            // 1230:3: -> ^( 'PAR' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] )
            {
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1230:6: ^( 'PAR' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] )
                {
                CommonTree root_1 = (CommonTree)adaptor.nil();
                root_1 = (CommonTree)adaptor.becomeRoot(stream_119.nextNode(), root_1);

                adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, sourceTemp));

                adaptor.addChild(root_0, root_1);
                }

            }

            retval.tree = root_0;}
            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 70, parallel_statement_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "parallel_statement"

    public static class expression_statement_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "expression_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1233:1: expression_statement : ( ';' -> ^( EXPRESSION_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$expression_statement.text] ) | expression ';' -> ^( EXPRESSION_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$expression_statement.text] ) );
    public final PretCParser.expression_statement_return expression_statement() throws RecognitionException {
        nodes_stack.push(new nodes_scope());

        PretCParser.expression_statement_return retval = new PretCParser.expression_statement_return();
        retval.start = input.LT(1);
        int expression_statement_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal337=null;
        Token char_literal339=null;
        PretCParser.expression_return expression338 = null;


        CommonTree char_literal337_tree=null;
        CommonTree char_literal339_tree=null;
        RewriteRuleTokenStream stream_41=new RewriteRuleTokenStream(adaptor,"token 41");
        RewriteRuleSubtreeStream stream_expression=new RewriteRuleSubtreeStream(adaptor,"rule expression");

          ((nodes_scope)nodes_stack.peek()).node = new StatementNode();
          long ID=-1;
          long lineNo = input.LT(1).getLine();

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 71) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1240:2: ( ';' -> ^( EXPRESSION_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$expression_statement.text] ) | expression ';' -> ^( EXPRESSION_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$expression_statement.text] ) )
            int alt90=2;
            int LA90_0 = input.LA(1);

            if ( (LA90_0==41) ) {
                alt90=1;
            }
            else if ( ((LA90_0>=IDENTIFIER && LA90_0<=DECIMAL_LITERAL)||(LA90_0>=HEX_LITERAL && LA90_0<=FLOATING_POINT_LITERAL)||LA90_0==49||LA90_0==75||(LA90_0>=77 && LA90_0<=78)||(LA90_0>=81 && LA90_0<=83)||(LA90_0>=86 && LA90_0<=88)) ) {
                alt90=2;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 90, 0, input);

                throw nvae;
            }
            switch (alt90) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1240:4: ';'
                    {
                    char_literal337=(Token)match(input,41,FOLLOW_41_in_expression_statement3485); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal337);

                    if ( state.backtracking==0 ) {

                      		sourceTemp = "";
                      		ID = idCount++;
                      		((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      		((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      		((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      		((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      		((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      		((nodes_scope)nodes_stack.peek()).node.type="expression";	
                      		((nodes_scope)nodes_stack.peek()).node.constantStatement.get(((nodes_scope)nodes_stack.peek()).node.constantStatement.size()-1).add(";");
                      		nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      		if (debug > 0) {
                      			System.out.println(nodesTable.get(ID));
                      		}
                      	
                    }


                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1255:4: -> ^( EXPRESSION_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$expression_statement.text] )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1255:7: ^( EXPRESSION_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$expression_statement.text] )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(EXPRESSION_STATMENT_TOK, "EXPRESSION_STATMENT_TOK"), root_1);

                        adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, input.toString(retval.start,input.LT(-1))));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1257:3: expression ';'
                    {
                    pushFollow(FOLLOW_expression_in_expression_statement3509);
                    expression338=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_expression.add(expression338.getTree());
                    char_literal339=(Token)match(input,41,FOLLOW_41_in_expression_statement3511); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal339);

                    if ( state.backtracking==0 ) {

                      		sourceTemp = (expression338!=null?input.toString(expression338.start,expression338.stop):null)+";";
                      		ID = idCount++;
                      		((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      		((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      		((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      		((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      		((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      		((nodes_scope)nodes_stack.peek()).node.type="expression";
                      		nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      		if (debug > 0) {
                      			System.out.println(nodesTable.get(ID));
                      		}
                      	
                    }


                    // AST REWRITE
                    // elements: 
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1271:4: -> ^( EXPRESSION_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$expression_statement.text] )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1271:7: ^( EXPRESSION_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$expression_statement.text] )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(EXPRESSION_STATMENT_TOK, "EXPRESSION_STATMENT_TOK"), root_1);

                        adaptor.addChild(root_1, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_1, (CommonTree)adaptor.create(SOURCE_TOK, input.toString(retval.start,input.LT(-1))));

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 71, expression_statement_StartIndex); }
            nodes_stack.pop();

        }
        return retval;
    }
    // $ANTLR end "expression_statement"

    public static class selection_statement_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "selection_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1274:1: selection_statement : ( 'if' '(' expression ')' s1= condition_statement ( options {k=1; backtrack=false; } : 'else' s2= condition_statement )? -> ^( SELECTION_STATMENT_TOK ^( 'if' ID_TOK[\"\"+(ifID)] SOURCE_TOK[\"if(\"+$expression.text+\")\"] ) $s1 ( ^( 'else' ID_TOK[\"\"+(elseID)] SOURCE_TOK[\"else\"] ) $s2)? ) | 'switch' '(' expression ')' condition_statement -> ^( SELECTION_STATMENT_TOK ^( 'switch' ID_TOK[\"\"+(ID)] SOURCE_TOK[\"switch(\"+$expression.text+\")\"] ) condition_statement ) );
    public final PretCParser.selection_statement_return selection_statement() throws RecognitionException {
        PretCParser.selection_statement_return retval = new PretCParser.selection_statement_return();
        retval.start = input.LT(1);
        int selection_statement_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal340=null;
        Token char_literal341=null;
        Token char_literal343=null;
        Token string_literal344=null;
        Token string_literal345=null;
        Token char_literal346=null;
        Token char_literal348=null;
        PretCParser.condition_statement_return s1 = null;

        PretCParser.condition_statement_return s2 = null;

        PretCParser.expression_return expression342 = null;

        PretCParser.expression_return expression347 = null;

        PretCParser.condition_statement_return condition_statement349 = null;


        CommonTree string_literal340_tree=null;
        CommonTree char_literal341_tree=null;
        CommonTree char_literal343_tree=null;
        CommonTree string_literal344_tree=null;
        CommonTree string_literal345_tree=null;
        CommonTree char_literal346_tree=null;
        CommonTree char_literal348_tree=null;
        RewriteRuleTokenStream stream_49=new RewriteRuleTokenStream(adaptor,"token 49");
        RewriteRuleTokenStream stream_121=new RewriteRuleTokenStream(adaptor,"token 121");
        RewriteRuleTokenStream stream_122=new RewriteRuleTokenStream(adaptor,"token 122");
        RewriteRuleTokenStream stream_51=new RewriteRuleTokenStream(adaptor,"token 51");
        RewriteRuleTokenStream stream_120=new RewriteRuleTokenStream(adaptor,"token 120");
        RewriteRuleSubtreeStream stream_expression=new RewriteRuleSubtreeStream(adaptor,"rule expression");
        RewriteRuleSubtreeStream stream_condition_statement=new RewriteRuleSubtreeStream(adaptor,"rule condition_statement");

        	long ID=-1;
        	long lineNo = input.LT(1).getLine();
        	long ifID = 0;
        	long elseID = 0;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 72) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1284:2: ( 'if' '(' expression ')' s1= condition_statement ( options {k=1; backtrack=false; } : 'else' s2= condition_statement )? -> ^( SELECTION_STATMENT_TOK ^( 'if' ID_TOK[\"\"+(ifID)] SOURCE_TOK[\"if(\"+$expression.text+\")\"] ) $s1 ( ^( 'else' ID_TOK[\"\"+(elseID)] SOURCE_TOK[\"else\"] ) $s2)? ) | 'switch' '(' expression ')' condition_statement -> ^( SELECTION_STATMENT_TOK ^( 'switch' ID_TOK[\"\"+(ID)] SOURCE_TOK[\"switch(\"+$expression.text+\")\"] ) condition_statement ) )
            int alt92=2;
            int LA92_0 = input.LA(1);

            if ( (LA92_0==120) ) {
                alt92=1;
            }
            else if ( (LA92_0==122) ) {
                alt92=2;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 92, 0, input);

                throw nvae;
            }
            switch (alt92) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1284:4: 'if' '(' expression ')' s1= condition_statement ( options {k=1; backtrack=false; } : 'else' s2= condition_statement )?
                    {
                    string_literal340=(Token)match(input,120,FOLLOW_120_in_selection_statement3547); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_120.add(string_literal340);

                    char_literal341=(Token)match(input,49,FOLLOW_49_in_selection_statement3549); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_49.add(char_literal341);

                    pushFollow(FOLLOW_expression_in_selection_statement3551);
                    expression342=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_expression.add(expression342.getTree());
                    char_literal343=(Token)match(input,51,FOLLOW_51_in_selection_statement3553); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_51.add(char_literal343);

                    if ( state.backtracking==0 ) {

                      			sourceTemp = "if("+(expression342!=null?input.toString(expression342.start,expression342.stop):null)+")" ;
                      			ID = idCount++;
                      			ifID = ID;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			((nodes_scope)nodes_stack.peek()).node.type="if";	
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      			//reset node for else
                      			((nodes_scope)nodes_stack.peek()).node = new StatementNode();
                      			ID=-1;
                      			lineNo = input.LT(1).getLine();
                      			
                      		
                    }
                    pushFollow(FOLLOW_condition_statement_in_selection_statement3572);
                    s1=condition_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_condition_statement.add(s1.getTree());
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1309:5: ( options {k=1; backtrack=false; } : 'else' s2= condition_statement )?
                    int alt91=2;
                    int LA91_0 = input.LA(1);

                    if ( (LA91_0==121) ) {
                        int LA91_2 = input.LA(2);

                        if ( (true) ) {
                            alt91=1;
                        }
                    }
                    switch (alt91) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1309:38: 'else' s2= condition_statement
                            {
                            string_literal344=(Token)match(input,121,FOLLOW_121_in_selection_statement3594); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_121.add(string_literal344);

                            if ( state.backtracking==0 ) {

                              			sourceTemp = "else" ;
                              			ID = idCount++;
                              			elseID = ID;
                              			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                              			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                              			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                              			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                              			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                              			((nodes_scope)nodes_stack.peek()).node.type="else";	
                              			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                              			if (debug > 0) {
                              				System.out.println(nodesTable.get(ID));
                              			}
                              		
                            }
                            pushFollow(FOLLOW_condition_statement_in_selection_statement3618);
                            s2=condition_statement();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) stream_condition_statement.add(s2.getTree());

                            }
                            break;

                    }



                    // AST REWRITE
                    // elements: s2, 121, 120, s1
                    // token labels: 
                    // rule labels: retval, s2, s1
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);
                    RewriteRuleSubtreeStream stream_s2=new RewriteRuleSubtreeStream(adaptor,"rule s2",s2!=null?s2.tree:null);
                    RewriteRuleSubtreeStream stream_s1=new RewriteRuleSubtreeStream(adaptor,"rule s1",s1!=null?s1.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1329:5: -> ^( SELECTION_STATMENT_TOK ^( 'if' ID_TOK[\"\"+(ifID)] SOURCE_TOK[\"if(\"+$expression.text+\")\"] ) $s1 ( ^( 'else' ID_TOK[\"\"+(elseID)] SOURCE_TOK[\"else\"] ) $s2)? )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1329:9: ^( SELECTION_STATMENT_TOK ^( 'if' ID_TOK[\"\"+(ifID)] SOURCE_TOK[\"if(\"+$expression.text+\")\"] ) $s1 ( ^( 'else' ID_TOK[\"\"+(elseID)] SOURCE_TOK[\"else\"] ) $s2)? )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(SELECTION_STATMENT_TOK, "SELECTION_STATMENT_TOK"), root_1);

                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1329:34: ^( 'if' ID_TOK[\"\"+(ifID)] SOURCE_TOK[\"if(\"+$expression.text+\")\"] )
                        {
                        CommonTree root_2 = (CommonTree)adaptor.nil();
                        root_2 = (CommonTree)adaptor.becomeRoot(stream_120.nextNode(), root_2);

                        adaptor.addChild(root_2, (CommonTree)adaptor.create(ID_TOK, ""+(ifID)));
                        adaptor.addChild(root_2, (CommonTree)adaptor.create(SOURCE_TOK, "if("+(expression342!=null?input.toString(expression342.start,expression342.stop):null)+")"));

                        adaptor.addChild(root_1, root_2);
                        }
                        adaptor.addChild(root_1, stream_s1.nextTree());
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1329:103: ( ^( 'else' ID_TOK[\"\"+(elseID)] SOURCE_TOK[\"else\"] ) $s2)?
                        if ( stream_s2.hasNext()||stream_121.hasNext() ) {
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1329:104: ^( 'else' ID_TOK[\"\"+(elseID)] SOURCE_TOK[\"else\"] )
                            {
                            CommonTree root_2 = (CommonTree)adaptor.nil();
                            root_2 = (CommonTree)adaptor.becomeRoot(stream_121.nextNode(), root_2);

                            adaptor.addChild(root_2, (CommonTree)adaptor.create(ID_TOK, ""+(elseID)));
                            adaptor.addChild(root_2, (CommonTree)adaptor.create(SOURCE_TOK, "else"));

                            adaptor.addChild(root_1, root_2);
                            }
                            adaptor.addChild(root_1, stream_s2.nextTree());

                        }
                        stream_s2.reset();
                        stream_121.reset();

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1333:4: 'switch' '(' expression ')' condition_statement
                    {
                    string_literal345=(Token)match(input,122,FOLLOW_122_in_selection_statement3687); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_122.add(string_literal345);

                    char_literal346=(Token)match(input,49,FOLLOW_49_in_selection_statement3689); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_49.add(char_literal346);

                    pushFollow(FOLLOW_expression_in_selection_statement3691);
                    expression347=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_expression.add(expression347.getTree());
                    char_literal348=(Token)match(input,51,FOLLOW_51_in_selection_statement3693); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_51.add(char_literal348);

                    if ( state.backtracking==0 ) {

                      			sourceTemp = "switch("+(expression347!=null?input.toString(expression347.start,expression347.stop):null)+")" ;
                      			ID = idCount++;
                      			elseID = ID;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			((nodes_scope)nodes_stack.peek()).node.type="switch";	
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }
                    pushFollow(FOLLOW_condition_statement_in_selection_statement3712);
                    condition_statement349=condition_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_condition_statement.add(condition_statement349.getTree());


                    // AST REWRITE
                    // elements: 122, condition_statement
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1352:6: -> ^( SELECTION_STATMENT_TOK ^( 'switch' ID_TOK[\"\"+(ID)] SOURCE_TOK[\"switch(\"+$expression.text+\")\"] ) condition_statement )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1352:9: ^( SELECTION_STATMENT_TOK ^( 'switch' ID_TOK[\"\"+(ID)] SOURCE_TOK[\"switch(\"+$expression.text+\")\"] ) condition_statement )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(SELECTION_STATMENT_TOK, "SELECTION_STATMENT_TOK"), root_1);

                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1352:34: ^( 'switch' ID_TOK[\"\"+(ID)] SOURCE_TOK[\"switch(\"+$expression.text+\")\"] )
                        {
                        CommonTree root_2 = (CommonTree)adaptor.nil();
                        root_2 = (CommonTree)adaptor.becomeRoot(stream_122.nextNode(), root_2);

                        adaptor.addChild(root_2, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_2, (CommonTree)adaptor.create(SOURCE_TOK, "switch("+(expression347!=null?input.toString(expression347.start,expression347.stop):null)+")"));

                        adaptor.addChild(root_1, root_2);
                        }
                        adaptor.addChild(root_1, stream_condition_statement.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {

              	

            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 72, selection_statement_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "selection_statement"

    public static class iteration_statement_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "iteration_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1355:1: iteration_statement : ( 'while' '(' expression ')' ( ':' DECIMAL_LITERAL )? condition_statement -> ^( ITERATION_STATEMENT_TOK ^( 'while' ID_TOK[\"\"+(ID)] SOURCE_TOK[\"while(\"+$expression.text+\")\"] ) condition_statement ) | 'do' ( ':' DECIMAL_LITERAL )? condition_statement 'while' '(' expression ')' ';' -> ^( ITERATION_STATEMENT_TOK ^( 'do' 'while' ID_TOK[\"\"+(ID)] SOURCE_TOK[ \"while(\"+$expression.text+\")\"] ) condition_statement ) | 'for' '(' (s1= expression )? ';' (s2= expression )? ';' (s3= expression )? ')' ( ':' DECIMAL_LITERAL )? condition_statement -> ^( ITERATION_STATEMENT_TOK ^( 'for' ID_TOK[\"\"+(ID)] SOURCE_TOK[localSourceTemp] ) condition_statement ) );
    public final PretCParser.iteration_statement_return iteration_statement() throws RecognitionException {
        PretCParser.iteration_statement_return retval = new PretCParser.iteration_statement_return();
        retval.start = input.LT(1);
        int iteration_statement_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal350=null;
        Token char_literal351=null;
        Token char_literal353=null;
        Token char_literal354=null;
        Token DECIMAL_LITERAL355=null;
        Token string_literal357=null;
        Token char_literal358=null;
        Token DECIMAL_LITERAL359=null;
        Token string_literal361=null;
        Token char_literal362=null;
        Token char_literal364=null;
        Token char_literal365=null;
        Token string_literal366=null;
        Token char_literal367=null;
        Token char_literal368=null;
        Token char_literal369=null;
        Token char_literal370=null;
        Token char_literal371=null;
        Token DECIMAL_LITERAL372=null;
        PretCParser.expression_return s1 = null;

        PretCParser.expression_return s2 = null;

        PretCParser.expression_return s3 = null;

        PretCParser.expression_return expression352 = null;

        PretCParser.condition_statement_return condition_statement356 = null;

        PretCParser.condition_statement_return condition_statement360 = null;

        PretCParser.expression_return expression363 = null;

        PretCParser.condition_statement_return condition_statement373 = null;


        CommonTree string_literal350_tree=null;
        CommonTree char_literal351_tree=null;
        CommonTree char_literal353_tree=null;
        CommonTree char_literal354_tree=null;
        CommonTree DECIMAL_LITERAL355_tree=null;
        CommonTree string_literal357_tree=null;
        CommonTree char_literal358_tree=null;
        CommonTree DECIMAL_LITERAL359_tree=null;
        CommonTree string_literal361_tree=null;
        CommonTree char_literal362_tree=null;
        CommonTree char_literal364_tree=null;
        CommonTree char_literal365_tree=null;
        CommonTree string_literal366_tree=null;
        CommonTree char_literal367_tree=null;
        CommonTree char_literal368_tree=null;
        CommonTree char_literal369_tree=null;
        CommonTree char_literal370_tree=null;
        CommonTree char_literal371_tree=null;
        CommonTree DECIMAL_LITERAL372_tree=null;
        RewriteRuleTokenStream stream_125=new RewriteRuleTokenStream(adaptor,"token 125");
        RewriteRuleTokenStream stream_49=new RewriteRuleTokenStream(adaptor,"token 49");
        RewriteRuleTokenStream stream_69=new RewriteRuleTokenStream(adaptor,"token 69");
        RewriteRuleTokenStream stream_41=new RewriteRuleTokenStream(adaptor,"token 41");
        RewriteRuleTokenStream stream_123=new RewriteRuleTokenStream(adaptor,"token 123");
        RewriteRuleTokenStream stream_124=new RewriteRuleTokenStream(adaptor,"token 124");
        RewriteRuleTokenStream stream_51=new RewriteRuleTokenStream(adaptor,"token 51");
        RewriteRuleTokenStream stream_DECIMAL_LITERAL=new RewriteRuleTokenStream(adaptor,"token DECIMAL_LITERAL");
        RewriteRuleSubtreeStream stream_expression=new RewriteRuleSubtreeStream(adaptor,"rule expression");
        RewriteRuleSubtreeStream stream_condition_statement=new RewriteRuleSubtreeStream(adaptor,"rule condition_statement");

        	long ID=-1;
        	long lineNo = input.LT(1).getLine();
        	String localSourceTemp = "";

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 73) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1363:2: ( 'while' '(' expression ')' ( ':' DECIMAL_LITERAL )? condition_statement -> ^( ITERATION_STATEMENT_TOK ^( 'while' ID_TOK[\"\"+(ID)] SOURCE_TOK[\"while(\"+$expression.text+\")\"] ) condition_statement ) | 'do' ( ':' DECIMAL_LITERAL )? condition_statement 'while' '(' expression ')' ';' -> ^( ITERATION_STATEMENT_TOK ^( 'do' 'while' ID_TOK[\"\"+(ID)] SOURCE_TOK[ \"while(\"+$expression.text+\")\"] ) condition_statement ) | 'for' '(' (s1= expression )? ';' (s2= expression )? ';' (s3= expression )? ')' ( ':' DECIMAL_LITERAL )? condition_statement -> ^( ITERATION_STATEMENT_TOK ^( 'for' ID_TOK[\"\"+(ID)] SOURCE_TOK[localSourceTemp] ) condition_statement ) )
            int alt99=3;
            switch ( input.LA(1) ) {
            case 123:
                {
                alt99=1;
                }
                break;
            case 124:
                {
                alt99=2;
                }
                break;
            case 125:
                {
                alt99=3;
                }
                break;
            default:
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 99, 0, input);

                throw nvae;
            }

            switch (alt99) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1363:4: 'while' '(' expression ')' ( ':' DECIMAL_LITERAL )? condition_statement
                    {
                    string_literal350=(Token)match(input,123,FOLLOW_123_in_iteration_statement3756); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_123.add(string_literal350);

                    char_literal351=(Token)match(input,49,FOLLOW_49_in_iteration_statement3758); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_49.add(char_literal351);

                    pushFollow(FOLLOW_expression_in_iteration_statement3760);
                    expression352=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_expression.add(expression352.getTree());
                    char_literal353=(Token)match(input,51,FOLLOW_51_in_iteration_statement3762); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_51.add(char_literal353);

                    if ( state.backtracking==0 ) {

                      			sourceTemp = "while("+(expression352!=null?input.toString(expression352.start,expression352.stop):null)+")" ;
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			((nodes_scope)nodes_stack.peek()).node.type="while";	
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1378:3: ( ':' DECIMAL_LITERAL )?
                    int alt93=2;
                    alt93 = dfa93.predict(input);
                    switch (alt93) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1378:4: ':' DECIMAL_LITERAL
                            {
                            char_literal354=(Token)match(input,69,FOLLOW_69_in_iteration_statement3771); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_69.add(char_literal354);

                            DECIMAL_LITERAL355=(Token)match(input,DECIMAL_LITERAL,FOLLOW_DECIMAL_LITERAL_in_iteration_statement3773); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_DECIMAL_LITERAL.add(DECIMAL_LITERAL355);

                            if ( state.backtracking==0 ) {
                              ((nodes_scope)nodes_stack.peek()).node.loopBound=(DECIMAL_LITERAL355!=null?DECIMAL_LITERAL355.getText():null);
                            }

                            }
                            break;

                    }

                    pushFollow(FOLLOW_condition_statement_in_iteration_statement3785);
                    condition_statement356=condition_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_condition_statement.add(condition_statement356.getTree());


                    // AST REWRITE
                    // elements: 123, condition_statement
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1381:3: -> ^( ITERATION_STATEMENT_TOK ^( 'while' ID_TOK[\"\"+(ID)] SOURCE_TOK[\"while(\"+$expression.text+\")\"] ) condition_statement )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1381:6: ^( ITERATION_STATEMENT_TOK ^( 'while' ID_TOK[\"\"+(ID)] SOURCE_TOK[\"while(\"+$expression.text+\")\"] ) condition_statement )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(ITERATION_STATEMENT_TOK, "ITERATION_STATEMENT_TOK"), root_1);

                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1381:32: ^( 'while' ID_TOK[\"\"+(ID)] SOURCE_TOK[\"while(\"+$expression.text+\")\"] )
                        {
                        CommonTree root_2 = (CommonTree)adaptor.nil();
                        root_2 = (CommonTree)adaptor.becomeRoot(stream_123.nextNode(), root_2);

                        adaptor.addChild(root_2, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_2, (CommonTree)adaptor.create(SOURCE_TOK, "while("+(expression352!=null?input.toString(expression352.start,expression352.stop):null)+")"));

                        adaptor.addChild(root_1, root_2);
                        }
                        adaptor.addChild(root_1, stream_condition_statement.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1383:4: 'do' ( ':' DECIMAL_LITERAL )? condition_statement 'while' '(' expression ')' ';'
                    {
                    string_literal357=(Token)match(input,124,FOLLOW_124_in_iteration_statement3815); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_124.add(string_literal357);

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1383:9: ( ':' DECIMAL_LITERAL )?
                    int alt94=2;
                    alt94 = dfa94.predict(input);
                    switch (alt94) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1383:10: ':' DECIMAL_LITERAL
                            {
                            char_literal358=(Token)match(input,69,FOLLOW_69_in_iteration_statement3818); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_69.add(char_literal358);

                            DECIMAL_LITERAL359=(Token)match(input,DECIMAL_LITERAL,FOLLOW_DECIMAL_LITERAL_in_iteration_statement3820); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_DECIMAL_LITERAL.add(DECIMAL_LITERAL359);

                            if ( state.backtracking==0 ) {
                              ((nodes_scope)nodes_stack.peek()).node.loopBound=(DECIMAL_LITERAL359!=null?DECIMAL_LITERAL359.getText():null);
                            }

                            }
                            break;

                    }

                    pushFollow(FOLLOW_condition_statement_in_iteration_statement3832);
                    condition_statement360=condition_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_condition_statement.add(condition_statement360.getTree());
                    string_literal361=(Token)match(input,123,FOLLOW_123_in_iteration_statement3834); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_123.add(string_literal361);

                    char_literal362=(Token)match(input,49,FOLLOW_49_in_iteration_statement3836); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_49.add(char_literal362);

                    pushFollow(FOLLOW_expression_in_iteration_statement3838);
                    expression363=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_expression.add(expression363.getTree());
                    char_literal364=(Token)match(input,51,FOLLOW_51_in_iteration_statement3840); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_51.add(char_literal364);

                    char_literal365=(Token)match(input,41,FOLLOW_41_in_iteration_statement3842); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal365);

                    if ( state.backtracking==0 ) {

                      			sourceTemp = "while("+(expression363!=null?input.toString(expression363.start,expression363.stop):null)+");" ;
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			((nodes_scope)nodes_stack.peek()).node.type="dowhile";	
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			}
                      		
                    }


                    // AST REWRITE
                    // elements: 123, condition_statement, 124
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1400:3: -> ^( ITERATION_STATEMENT_TOK ^( 'do' 'while' ID_TOK[\"\"+(ID)] SOURCE_TOK[ \"while(\"+$expression.text+\")\"] ) condition_statement )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1400:7: ^( ITERATION_STATEMENT_TOK ^( 'do' 'while' ID_TOK[\"\"+(ID)] SOURCE_TOK[ \"while(\"+$expression.text+\")\"] ) condition_statement )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(ITERATION_STATEMENT_TOK, "ITERATION_STATEMENT_TOK"), root_1);

                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1400:33: ^( 'do' 'while' ID_TOK[\"\"+(ID)] SOURCE_TOK[ \"while(\"+$expression.text+\")\"] )
                        {
                        CommonTree root_2 = (CommonTree)adaptor.nil();
                        root_2 = (CommonTree)adaptor.becomeRoot(stream_124.nextNode(), root_2);

                        adaptor.addChild(root_2, stream_123.nextNode());
                        adaptor.addChild(root_2, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_2, (CommonTree)adaptor.create(SOURCE_TOK, "while("+(expression363!=null?input.toString(expression363.start,expression363.stop):null)+")"));

                        adaptor.addChild(root_1, root_2);
                        }
                        adaptor.addChild(root_1, stream_condition_statement.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1401:3: 'for' '(' (s1= expression )? ';' (s2= expression )? ';' (s3= expression )? ')' ( ':' DECIMAL_LITERAL )? condition_statement
                    {
                    string_literal366=(Token)match(input,125,FOLLOW_125_in_iteration_statement3875); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_125.add(string_literal366);

                    char_literal367=(Token)match(input,49,FOLLOW_49_in_iteration_statement3877); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_49.add(char_literal367);

                    if ( state.backtracking==0 ) {
                      localSourceTemp="for(";
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1401:39: (s1= expression )?
                    int alt95=2;
                    int LA95_0 = input.LA(1);

                    if ( ((LA95_0>=IDENTIFIER && LA95_0<=DECIMAL_LITERAL)||(LA95_0>=HEX_LITERAL && LA95_0<=FLOATING_POINT_LITERAL)||LA95_0==49||LA95_0==75||(LA95_0>=77 && LA95_0<=78)||(LA95_0>=81 && LA95_0<=83)||(LA95_0>=86 && LA95_0<=88)) ) {
                        alt95=1;
                    }
                    switch (alt95) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1401:40: s1= expression
                            {
                            pushFollow(FOLLOW_expression_in_iteration_statement3884);
                            s1=expression();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) stream_expression.add(s1.getTree());
                            if ( state.backtracking==0 ) {
                              localSourceTemp+=(s1!=null?input.toString(s1.start,s1.stop):null);
                            }

                            }
                            break;

                    }

                    char_literal368=(Token)match(input,41,FOLLOW_41_in_iteration_statement3893); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal368);

                    if ( state.backtracking==0 ) {
                      localSourceTemp+=";";
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1402:32: (s2= expression )?
                    int alt96=2;
                    int LA96_0 = input.LA(1);

                    if ( ((LA96_0>=IDENTIFIER && LA96_0<=DECIMAL_LITERAL)||(LA96_0>=HEX_LITERAL && LA96_0<=FLOATING_POINT_LITERAL)||LA96_0==49||LA96_0==75||(LA96_0>=77 && LA96_0<=78)||(LA96_0>=81 && LA96_0<=83)||(LA96_0>=86 && LA96_0<=88)) ) {
                        alt96=1;
                    }
                    switch (alt96) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1403:12: s2= expression
                            {
                            if ( state.backtracking==0 ) {

                              												if (((nodes_scope)nodes_stack.peek()).node.assignmentExpression.size()==0) {
                              													((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add("");
                              												}
                              											
                            }
                            pushFollow(FOLLOW_expression_in_iteration_statement3913);
                            s2=expression();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) stream_expression.add(s2.getTree());
                            if ( state.backtracking==0 ) {
                              localSourceTemp+=(s2!=null?input.toString(s2.start,s2.stop):null);
                            }

                            }
                            break;

                    }

                    char_literal369=(Token)match(input,41,FOLLOW_41_in_iteration_statement3923); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_41.add(char_literal369);

                    if ( state.backtracking==0 ) {
                      localSourceTemp+=";";
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1408:32: (s3= expression )?
                    int alt97=2;
                    int LA97_0 = input.LA(1);

                    if ( ((LA97_0>=IDENTIFIER && LA97_0<=DECIMAL_LITERAL)||(LA97_0>=HEX_LITERAL && LA97_0<=FLOATING_POINT_LITERAL)||LA97_0==49||LA97_0==75||(LA97_0>=77 && LA97_0<=78)||(LA97_0>=81 && LA97_0<=83)||(LA97_0>=86 && LA97_0<=88)) ) {
                        alt97=1;
                    }
                    switch (alt97) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1409:12: s3= expression
                            {
                            if ( state.backtracking==0 ) {

                              												if (((nodes_scope)nodes_stack.peek()).node.assignmentExpression.size()==0) {
                              													((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add("");
                              													((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add("");
                              												}else if (((nodes_scope)nodes_stack.peek()).node.assignmentExpression.size()==1) {
                              													((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add("");
                              												}
                              											
                            }
                            pushFollow(FOLLOW_expression_in_iteration_statement3955);
                            s3=expression();

                            state._fsp--;
                            if (state.failed) return retval;
                            if ( state.backtracking==0 ) stream_expression.add(s3.getTree());
                            if ( state.backtracking==0 ) {
                              localSourceTemp+=(s3!=null?input.toString(s3.start,s3.stop):null);
                            }

                            }
                            break;

                    }

                    char_literal370=(Token)match(input,51,FOLLOW_51_in_iteration_statement3964); if (state.failed) return retval; 
                    if ( state.backtracking==0 ) stream_51.add(char_literal370);

                    if ( state.backtracking==0 ) {

                      				localSourceTemp+=")";
                      												if (((nodes_scope)nodes_stack.peek()).node.assignmentExpression.size()==0) {
                      													((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add("");
                      													((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add("");
                      													((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add("");
                      												}else if (((nodes_scope)nodes_stack.peek()).node.assignmentExpression.size()==1) {
                      													((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add("");
                      													((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add("");
                      												}else if (((nodes_scope)nodes_stack.peek()).node.assignmentExpression.size()==2) {
                      													((nodes_scope)nodes_stack.peek()).node.assignmentExpression.add("");
                      												}
                      			
                      			
                      			
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1435:4: ( ':' DECIMAL_LITERAL )?
                    int alt98=2;
                    alt98 = dfa98.predict(input);
                    switch (alt98) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1435:5: ':' DECIMAL_LITERAL
                            {
                            char_literal371=(Token)match(input,69,FOLLOW_69_in_iteration_statement3981); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_69.add(char_literal371);

                            DECIMAL_LITERAL372=(Token)match(input,DECIMAL_LITERAL,FOLLOW_DECIMAL_LITERAL_in_iteration_statement3983); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_DECIMAL_LITERAL.add(DECIMAL_LITERAL372);

                            if ( state.backtracking==0 ) {
                              ((nodes_scope)nodes_stack.peek()).node.loopBound=(DECIMAL_LITERAL372!=null?DECIMAL_LITERAL372.getText():null);
                            }

                            }
                            break;

                    }

                    if ( state.backtracking==0 ) {

                      			sourceTemp = localSourceTemp;
                      			ID = idCount++;
                      			((nodes_scope)nodes_stack.peek()).node.ID=ID;
                      			((nodes_scope)nodes_stack.peek()).node.line= lineNo;
                      			((nodes_scope)nodes_stack.peek()).node.funcScopeID=scopeFuncCount;
                      			((nodes_scope)nodes_stack.peek()).node.scopeID=currentScope;
                      			((nodes_scope)nodes_stack.peek()).node.sourceCode = sourceTemp;
                      			((nodes_scope)nodes_stack.peek()).node.type="for";	
                      			nodesTable.put(ID,((nodes_scope)nodes_stack.peek()).node);
                      			if (debug > 0) {
                      				System.out.println(nodesTable.get(ID));
                      			} 
                      		
                    }
                    pushFollow(FOLLOW_condition_statement_in_iteration_statement3999);
                    condition_statement373=condition_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_condition_statement.add(condition_statement373.getTree());


                    // AST REWRITE
                    // elements: 125, condition_statement
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 1453:24: -> ^( ITERATION_STATEMENT_TOK ^( 'for' ID_TOK[\"\"+(ID)] SOURCE_TOK[localSourceTemp] ) condition_statement )
                    {
                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1453:27: ^( ITERATION_STATEMENT_TOK ^( 'for' ID_TOK[\"\"+(ID)] SOURCE_TOK[localSourceTemp] ) condition_statement )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(ITERATION_STATEMENT_TOK, "ITERATION_STATEMENT_TOK"), root_1);

                        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1453:53: ^( 'for' ID_TOK[\"\"+(ID)] SOURCE_TOK[localSourceTemp] )
                        {
                        CommonTree root_2 = (CommonTree)adaptor.nil();
                        root_2 = (CommonTree)adaptor.becomeRoot(stream_125.nextNode(), root_2);

                        adaptor.addChild(root_2, (CommonTree)adaptor.create(ID_TOK, ""+(ID)));
                        adaptor.addChild(root_2, (CommonTree)adaptor.create(SOURCE_TOK, localSourceTemp));

                        adaptor.addChild(root_1, root_2);
                        }
                        adaptor.addChild(root_1, stream_condition_statement.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {


            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 73, iteration_statement_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "iteration_statement"

    public static class jump_statement_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "jump_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1456:1: jump_statement : ( 'goto' IDENTIFIER ';' | 'continue' ';' | 'break' ';' | 'return' ';' | 'return' expression ';' );
    public final PretCParser.jump_statement_return jump_statement() throws RecognitionException {
        PretCParser.jump_statement_return retval = new PretCParser.jump_statement_return();
        retval.start = input.LT(1);
        int jump_statement_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal374=null;
        Token IDENTIFIER375=null;
        Token char_literal376=null;
        Token string_literal377=null;
        Token char_literal378=null;
        Token string_literal379=null;
        Token char_literal380=null;
        Token string_literal381=null;
        Token char_literal382=null;
        Token string_literal383=null;
        Token char_literal385=null;
        PretCParser.expression_return expression384 = null;


        CommonTree string_literal374_tree=null;
        CommonTree IDENTIFIER375_tree=null;
        CommonTree char_literal376_tree=null;
        CommonTree string_literal377_tree=null;
        CommonTree char_literal378_tree=null;
        CommonTree string_literal379_tree=null;
        CommonTree char_literal380_tree=null;
        CommonTree string_literal381_tree=null;
        CommonTree char_literal382_tree=null;
        CommonTree string_literal383_tree=null;
        CommonTree char_literal385_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 74) ) { return retval; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1457:2: ( 'goto' IDENTIFIER ';' | 'continue' ';' | 'break' ';' | 'return' ';' | 'return' expression ';' )
            int alt100=5;
            alt100 = dfa100.predict(input);
            switch (alt100) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1457:4: 'goto' IDENTIFIER ';'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal374=(Token)match(input,126,FOLLOW_126_in_jump_statement4029); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal374_tree = (CommonTree)adaptor.create(string_literal374);
                    adaptor.addChild(root_0, string_literal374_tree);
                    }
                    IDENTIFIER375=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_jump_statement4031); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    IDENTIFIER375_tree = (CommonTree)adaptor.create(IDENTIFIER375);
                    adaptor.addChild(root_0, IDENTIFIER375_tree);
                    }
                    char_literal376=(Token)match(input,41,FOLLOW_41_in_jump_statement4033); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal376_tree = (CommonTree)adaptor.create(char_literal376);
                    adaptor.addChild(root_0, char_literal376_tree);
                    }
                    if ( state.backtracking==0 ) {

                      			((nodes_scope)nodes_stack.peek()).node.name.add((IDENTIFIER375!=null?IDENTIFIER375.getText():null));
                      			((nodes_scope)nodes_stack.peek()).node.type="goto";	
                      		
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1462:4: 'continue' ';'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal377=(Token)match(input,127,FOLLOW_127_in_jump_statement4043); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal377_tree = (CommonTree)adaptor.create(string_literal377);
                    adaptor.addChild(root_0, string_literal377_tree);
                    }
                    char_literal378=(Token)match(input,41,FOLLOW_41_in_jump_statement4045); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal378_tree = (CommonTree)adaptor.create(char_literal378);
                    adaptor.addChild(root_0, char_literal378_tree);
                    }
                    if ( state.backtracking==0 ) {

                      			((nodes_scope)nodes_stack.peek()).node.type="continue";	
                      		
                    }

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1466:4: 'break' ';'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal379=(Token)match(input,128,FOLLOW_128_in_jump_statement4054); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal379_tree = (CommonTree)adaptor.create(string_literal379);
                    adaptor.addChild(root_0, string_literal379_tree);
                    }
                    char_literal380=(Token)match(input,41,FOLLOW_41_in_jump_statement4056); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal380_tree = (CommonTree)adaptor.create(char_literal380);
                    adaptor.addChild(root_0, char_literal380_tree);
                    }
                    if ( state.backtracking==0 ) {

                      			((nodes_scope)nodes_stack.peek()).node.type="break";	
                      		
                    }

                    }
                    break;
                case 4 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1470:4: 'return' ';'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal381=(Token)match(input,129,FOLLOW_129_in_jump_statement4065); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal381_tree = (CommonTree)adaptor.create(string_literal381);
                    adaptor.addChild(root_0, string_literal381_tree);
                    }
                    char_literal382=(Token)match(input,41,FOLLOW_41_in_jump_statement4067); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal382_tree = (CommonTree)adaptor.create(char_literal382);
                    adaptor.addChild(root_0, char_literal382_tree);
                    }
                    if ( state.backtracking==0 ) {

                      			((nodes_scope)nodes_stack.peek()).node.type="return";	
                      		
                    }

                    }
                    break;
                case 5 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1474:4: 'return' expression ';'
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    string_literal383=(Token)match(input,129,FOLLOW_129_in_jump_statement4076); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    string_literal383_tree = (CommonTree)adaptor.create(string_literal383);
                    adaptor.addChild(root_0, string_literal383_tree);
                    }
                    pushFollow(FOLLOW_expression_in_jump_statement4078);
                    expression384=expression();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, expression384.getTree());
                    char_literal385=(Token)match(input,41,FOLLOW_41_in_jump_statement4080); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal385_tree = (CommonTree)adaptor.create(char_literal385);
                    adaptor.addChild(root_0, char_literal385_tree);
                    }
                    if ( state.backtracking==0 ) {

                      			((nodes_scope)nodes_stack.peek()).node.constantStatement.get(((nodes_scope)nodes_stack.peek()).node.constantStatement.size()-1).add((expression384!=null?input.toString(expression384.start,expression384.stop):null));
                      			((nodes_scope)nodes_stack.peek()).node.type="return2";	
                      		
                    }

                    }
                    break;

            }
            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
        }

        	catch (RecognitionException e) {
        	    if (errorReported == false) {
        			System.out.println("Error on \""+input.LT(1).getText()+"\"");
        			System.out.println("Line: "+input.LT(1).getLine());
        			errorReported = true;
        		}
        	    throw e;
        	}  
        finally {
            if ( state.backtracking>0 ) { memoize(input, 74, jump_statement_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "jump_statement"

    // $ANTLR start synpred2_PretC
    public final void synpred2_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:239:6: ( declaration_specifiers )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:239:6: declaration_specifiers
        {
        pushFollow(FOLLOW_declaration_specifiers_in_synpred2_PretC292);
        declaration_specifiers();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred2_PretC

    // $ANTLR start synpred4_PretC
    public final void synpred4_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:239:4: ( ( declaration_specifiers )? declarator ( declaration )* '{' )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:239:6: ( declaration_specifiers )? declarator ( declaration )* '{'
        {
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:239:6: ( declaration_specifiers )?
        int alt101=2;
        alt101 = dfa101.predict(input);
        switch (alt101) {
            case 1 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: declaration_specifiers
                {
                pushFollow(FOLLOW_declaration_specifiers_in_synpred4_PretC292);
                declaration_specifiers();

                state._fsp--;
                if (state.failed) return ;

                }
                break;

        }

        pushFollow(FOLLOW_declarator_in_synpred4_PretC295);
        declarator();

        state._fsp--;
        if (state.failed) return ;
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:239:41: ( declaration )*
        loop102:
        do {
            int alt102=2;
            alt102 = dfa102.predict(input);
            switch (alt102) {
        	case 1 :
        	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: declaration
        	    {
        	    pushFollow(FOLLOW_declaration_in_synpred4_PretC297);
        	    declaration();

        	    state._fsp--;
        	    if (state.failed) return ;

        	    }
        	    break;

        	default :
        	    break loop102;
            }
        } while (true);

        match(input,65,FOLLOW_65_in_synpred4_PretC300); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred4_PretC

    // $ANTLR start synpred5_PretC
    public final void synpred5_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:240:4: ( declaration )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:240:4: declaration
        {
        pushFollow(FOLLOW_declaration_in_synpred5_PretC312);
        declaration();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred5_PretC

    // $ANTLR start synpred15_PretC
    public final void synpred15_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:360:4: ( declaration_specifiers )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:360:4: declaration_specifiers
        {
        pushFollow(FOLLOW_declaration_specifiers_in_synpred15_PretC561);
        declaration_specifiers();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred15_PretC

    // $ANTLR start synpred18_PretC
    public final void synpred18_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:410:45: ( declaration_specifiers )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:410:45: declaration_specifiers
        {
        pushFollow(FOLLOW_declaration_specifiers_in_synpred18_PretC667);
        declaration_specifiers();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred18_PretC

    // $ANTLR start synpred42_PretC
    public final void synpred42_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:542:4: ( ( 'unsigned' | 'signed' )? 'long' 'long' )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:542:4: ( 'unsigned' | 'signed' )? 'long' 'long'
        {
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:542:4: ( 'unsigned' | 'signed' )?
        int alt111=2;
        int LA111_0 = input.LA(1);

        if ( ((LA111_0>=57 && LA111_0<=58)) ) {
            alt111=1;
        }
        switch (alt111) {
            case 1 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
                {
                if ( (input.LA(1)>=57 && input.LA(1)<=58) ) {
                    input.consume();
                    state.errorRecovery=false;state.failed=false;
                }
                else {
                    if (state.backtracking>0) {state.failed=true; return ;}
                    MismatchedSetException mse = new MismatchedSetException(null,input);
                    throw mse;
                }


                }
                break;

        }

        match(input,62,FOLLOW_62_in_synpred42_PretC1029); if (state.failed) return ;
        match(input,62,FOLLOW_62_in_synpred42_PretC1031); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred42_PretC

    // $ANTLR start synpred45_PretC
    public final void synpred45_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:543:4: ( ( 'unsigned' | 'signed' )? 'long' )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:543:4: ( 'unsigned' | 'signed' )? 'long'
        {
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:543:4: ( 'unsigned' | 'signed' )?
        int alt112=2;
        int LA112_0 = input.LA(1);

        if ( ((LA112_0>=57 && LA112_0<=58)) ) {
            alt112=1;
        }
        switch (alt112) {
            case 1 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
                {
                if ( (input.LA(1)>=57 && input.LA(1)<=58) ) {
                    input.consume();
                    state.errorRecovery=false;state.failed=false;
                }
                else {
                    if (state.backtracking>0) {state.failed=true; return ;}
                    MismatchedSetException mse = new MismatchedSetException(null,input);
                    throw mse;
                }


                }
                break;

        }

        match(input,62,FOLLOW_62_in_synpred45_PretC1048); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred45_PretC

    // $ANTLR start synpred50_PretC
    public final void synpred50_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:575:4: ( type_id )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:575:4: type_id
        {
        pushFollow(FOLLOW_type_id_in_synpred50_PretC1105);
        type_id();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred50_PretC

    // $ANTLR start synpred57_PretC
    public final void synpred57_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:660:59: ( type_specifier )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:660:59: type_specifier
        {
        pushFollow(FOLLOW_type_specifier_in_synpred57_PretC1352);
        type_specifier();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred57_PretC

    // $ANTLR start synpred68_PretC
    public final void synpred68_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:706:4: ( ( pointer )? direct_declarator )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:706:4: ( pointer )? direct_declarator
        {
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:706:4: ( pointer )?
        int alt116=2;
        int LA116_0 = input.LA(1);

        if ( (LA116_0==75) ) {
            alt116=1;
        }
        switch (alt116) {
            case 1 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: pointer
                {
                pushFollow(FOLLOW_pointer_in_synpred68_PretC1526);
                pointer();

                state._fsp--;
                if (state.failed) return ;

                }
                break;

        }

        pushFollow(FOLLOW_direct_declarator_in_synpred68_PretC1529);
        direct_declarator();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred68_PretC

    // $ANTLR start synpred69_PretC
    public final void synpred69_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:719:4: ( declarator_suffix )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:719:4: declarator_suffix
        {
        pushFollow(FOLLOW_declarator_suffix_in_synpred69_PretC1559);
        declarator_suffix();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred69_PretC

    // $ANTLR start synpred71_PretC
    public final void synpred71_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:722:22: ( declarator_suffix )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:722:22: declarator_suffix
        {
        pushFollow(FOLLOW_declarator_suffix_in_synpred71_PretC1584);
        declarator_suffix();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred71_PretC

    // $ANTLR start synpred74_PretC
    public final void synpred74_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:728:9: ( '(' parameter_type_list ')' )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:728:9: '(' parameter_type_list ')'
        {
        match(input,49,FOLLOW_49_in_synpred74_PretC1635); if (state.failed) return ;
        pushFollow(FOLLOW_parameter_type_list_in_synpred74_PretC1637);
        parameter_type_list();

        state._fsp--;
        if (state.failed) return ;
        match(input,51,FOLLOW_51_in_synpred74_PretC1639); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred74_PretC

    // $ANTLR start synpred75_PretC
    public final void synpred75_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:729:9: ( '(' identifier_list ')' )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:729:9: '(' identifier_list ')'
        {
        match(input,49,FOLLOW_49_in_synpred75_PretC1649); if (state.failed) return ;
        pushFollow(FOLLOW_identifier_list_in_synpred75_PretC1651);
        identifier_list();

        state._fsp--;
        if (state.failed) return ;
        match(input,51,FOLLOW_51_in_synpred75_PretC1653); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred75_PretC

    // $ANTLR start synpred76_PretC
    public final void synpred76_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:8: ( type_qualifier )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:8: type_qualifier
        {
        pushFollow(FOLLOW_type_qualifier_in_synpred76_PretC1678);
        type_qualifier();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred76_PretC

    // $ANTLR start synpred77_PretC
    public final void synpred77_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:24: ( pointer )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:24: pointer
        {
        pushFollow(FOLLOW_pointer_in_synpred77_PretC1681);
        pointer();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred77_PretC

    // $ANTLR start synpred78_PretC
    public final void synpred78_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:4: ( '*' ( type_qualifier )+ ( pointer )? )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:4: '*' ( type_qualifier )+ ( pointer )?
        {
        match(input,75,FOLLOW_75_in_synpred78_PretC1676); if (state.failed) return ;
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:8: ( type_qualifier )+
        int cnt118=0;
        loop118:
        do {
            int alt118=2;
            int LA118_0 = input.LA(1);

            if ( ((LA118_0>=71 && LA118_0<=72)) ) {
                alt118=1;
            }


            switch (alt118) {
        	case 1 :
        	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: type_qualifier
        	    {
        	    pushFollow(FOLLOW_type_qualifier_in_synpred78_PretC1678);
        	    type_qualifier();

        	    state._fsp--;
        	    if (state.failed) return ;

        	    }
        	    break;

        	default :
        	    if ( cnt118 >= 1 ) break loop118;
        	    if (state.backtracking>0) {state.failed=true; return ;}
                    EarlyExitException eee =
                        new EarlyExitException(118, input);
                    throw eee;
            }
            cnt118++;
        } while (true);

        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:734:24: ( pointer )?
        int alt119=2;
        int LA119_0 = input.LA(1);

        if ( (LA119_0==75) ) {
            alt119=1;
        }
        switch (alt119) {
            case 1 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: pointer
                {
                pushFollow(FOLLOW_pointer_in_synpred78_PretC1681);
                pointer();

                state._fsp--;
                if (state.failed) return ;

                }
                break;

        }


        }
    }
    // $ANTLR end synpred78_PretC

    // $ANTLR start synpred79_PretC
    public final void synpred79_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:735:4: ( '*' pointer )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:735:4: '*' pointer
        {
        match(input,75,FOLLOW_75_in_synpred79_PretC1687); if (state.failed) return ;
        pushFollow(FOLLOW_pointer_in_synpred79_PretC1689);
        pointer();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred79_PretC

    // $ANTLR start synpred82_PretC
    public final void synpred82_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:771:6: ( declarator )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:771:6: declarator
        {
        pushFollow(FOLLOW_declarator_in_synpred82_PretC1792);
        declarator();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred82_PretC

    // $ANTLR start synpred83_PretC
    public final void synpred83_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:781:6: ( abstract_declarator )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:781:6: abstract_declarator
        {
        pushFollow(FOLLOW_abstract_declarator_in_synpred83_PretC1802);
        abstract_declarator();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred83_PretC

    // $ANTLR start synpred87_PretC
    public final void synpred87_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:807:12: ( direct_abstract_declarator )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:807:12: direct_abstract_declarator
        {
        pushFollow(FOLLOW_direct_abstract_declarator_in_synpred87_PretC1902);
        direct_abstract_declarator();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred87_PretC

    // $ANTLR start synpred90_PretC
    public final void synpred90_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:812:65: ( abstract_declarator_suffix )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:812:65: abstract_declarator_suffix
        {
        pushFollow(FOLLOW_abstract_declarator_suffix_in_synpred90_PretC1933);
        abstract_declarator_suffix();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred90_PretC

    // $ANTLR start synpred103_PretC
    public final void synpred103_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:846:4: ( '(' type_name ')' cast_expression )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:846:4: '(' type_name ')' cast_expression
        {
        match(input,49,FOLLOW_49_in_synpred103_PretC2105); if (state.failed) return ;
        pushFollow(FOLLOW_type_name_in_synpred103_PretC2107);
        type_name();

        state._fsp--;
        if (state.failed) return ;
        match(input,51,FOLLOW_51_in_synpred103_PretC2109); if (state.failed) return ;
        pushFollow(FOLLOW_cast_expression_in_synpred103_PretC2111);
        cast_expression();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred103_PretC

    // $ANTLR start synpred108_PretC
    public final void synpred108_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:861:4: ( 'sizeof' unary_expression )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:861:4: 'sizeof' unary_expression
        {
        match(input,83,FOLLOW_83_in_synpred108_PretC2161); if (state.failed) return ;
        pushFollow(FOLLOW_unary_expression_in_synpred108_PretC2163);
        unary_expression();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred108_PretC

    // $ANTLR start synpred129_PretC
    public final void synpred129_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:912:4: ( lvalue assignment_operator assignment_expression )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:912:4: lvalue assignment_operator assignment_expression
        {
        pushFollow(FOLLOW_lvalue_in_synpred129_PretC2503);
        lvalue();

        state._fsp--;
        if (state.failed) return ;
        pushFollow(FOLLOW_assignment_operator_in_synpred129_PretC2505);
        assignment_operator();

        state._fsp--;
        if (state.failed) return ;
        pushFollow(FOLLOW_assignment_expression_in_synpred129_PretC2507);
        assignment_expression();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred129_PretC

    // $ANTLR start synpred164_PretC
    public final void synpred164_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1078:4: ( '{' '}' )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1078:4: '{' '}'
        {
        match(input,65,FOLLOW_65_in_synpred164_PretC3001); if (state.failed) return ;
        match(input,66,FOLLOW_66_in_synpred164_PretC3011); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred164_PretC

    // $ANTLR start synpred165_PretC
    public final void synpred165_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1100:9: ( compound_statement )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1100:9: compound_statement
        {
        pushFollow(FOLLOW_compound_statement_in_synpred165_PretC3077);
        compound_statement();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred165_PretC

    // $ANTLR start synpred166_PretC
    public final void synpred166_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1100:4: ( '{' ( compound_statement )? '}' )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1100:5: '{' ( compound_statement )? '}'
        {
        match(input,65,FOLLOW_65_in_synpred166_PretC3075); if (state.failed) return ;
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1100:9: ( compound_statement )?
        int alt121=2;
        alt121 = dfa121.predict(input);
        switch (alt121) {
            case 1 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:0:0: compound_statement
                {
                pushFollow(FOLLOW_compound_statement_in_synpred166_PretC3077);
                compound_statement();

                state._fsp--;
                if (state.failed) return ;

                }
                break;

        }

        match(input,66,FOLLOW_66_in_synpred166_PretC3080); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred166_PretC

    // $ANTLR start synpred167_PretC
    public final void synpred167_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1101:127: ( declaration )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1101:127: declaration
        {
        pushFollow(FOLLOW_declaration_in_synpred167_PretC3091);
        declaration();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred167_PretC

    // $ANTLR start synpred168_PretC
    public final void synpred168_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1109:5: ( declaration )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1109:5: declaration
        {
        pushFollow(FOLLOW_declaration_in_synpred168_PretC3139);
        declaration();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred168_PretC

    // $ANTLR start synpred169_PretC
    public final void synpred169_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1109:17: ( statement_list )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1109:17: statement_list
        {
        pushFollow(FOLLOW_statement_list_in_synpred169_PretC3141);
        statement_list();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred169_PretC

    // $ANTLR start synpred170_PretC
    public final void synpred170_PretC_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1113:4: ( statement )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1113:4: statement
        {
        pushFollow(FOLLOW_statement_in_synpred170_PretC3156);
        statement();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred170_PretC

    // Delegated rules

    public final boolean synpred167_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred167_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred83_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred83_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred69_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred69_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred108_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred108_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred71_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred71_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred76_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred76_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred166_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred166_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred18_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred18_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred168_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred168_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred2_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred2_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred57_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred57_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred42_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred42_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred82_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred82_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred5_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred5_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred4_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred4_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred87_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred87_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred79_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred79_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred103_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred103_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred170_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred170_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred164_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred164_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred77_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred77_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred169_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred169_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred68_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred68_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred165_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred165_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred15_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred15_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred75_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred75_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred74_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred74_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred45_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred45_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred50_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred50_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred90_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred90_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred129_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred129_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred78_PretC() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred78_PretC_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }


    protected DFA1 dfa1 = new DFA1(this);
    protected DFA2 dfa2 = new DFA2(this);
    protected DFA9 dfa9 = new DFA9(this);
    protected DFA11 dfa11 = new DFA11(this);
    protected DFA10 dfa10 = new DFA10(this);
    protected DFA14 dfa14 = new DFA14(this);
    protected DFA12 dfa12 = new DFA12(this);
    protected DFA15 dfa15 = new DFA15(this);
    protected DFA24 dfa24 = new DFA24(this);
    protected DFA26 dfa26 = new DFA26(this);
    protected DFA28 dfa28 = new DFA28(this);
    protected DFA30 dfa30 = new DFA30(this);
    protected DFA35 dfa35 = new DFA35(this);
    protected DFA39 dfa39 = new DFA39(this);
    protected DFA40 dfa40 = new DFA40(this);
    protected DFA41 dfa41 = new DFA41(this);
    protected DFA43 dfa43 = new DFA43(this);
    protected DFA46 dfa46 = new DFA46(this);
    protected DFA44 dfa44 = new DFA44(this);
    protected DFA45 dfa45 = new DFA45(this);
    protected DFA48 dfa48 = new DFA48(this);
    protected DFA49 dfa49 = new DFA49(this);
    protected DFA53 dfa53 = new DFA53(this);
    protected DFA55 dfa55 = new DFA55(this);
    protected DFA56 dfa56 = new DFA56(this);
    protected DFA57 dfa57 = new DFA57(this);
    protected DFA60 dfa60 = new DFA60(this);
    protected DFA62 dfa62 = new DFA62(this);
    protected DFA63 dfa63 = new DFA63(this);
    protected DFA64 dfa64 = new DFA64(this);
    protected DFA65 dfa65 = new DFA65(this);
    protected DFA66 dfa66 = new DFA66(this);
    protected DFA69 dfa69 = new DFA69(this);
    protected DFA70 dfa70 = new DFA70(this);
    protected DFA71 dfa71 = new DFA71(this);
    protected DFA72 dfa72 = new DFA72(this);
    protected DFA73 dfa73 = new DFA73(this);
    protected DFA74 dfa74 = new DFA74(this);
    protected DFA75 dfa75 = new DFA75(this);
    protected DFA76 dfa76 = new DFA76(this);
    protected DFA77 dfa77 = new DFA77(this);
    protected DFA78 dfa78 = new DFA78(this);
    protected DFA79 dfa79 = new DFA79(this);
    protected DFA81 dfa81 = new DFA81(this);
    protected DFA83 dfa83 = new DFA83(this);
    protected DFA82 dfa82 = new DFA82(this);
    protected DFA84 dfa84 = new DFA84(this);
    protected DFA85 dfa85 = new DFA85(this);
    protected DFA93 dfa93 = new DFA93(this);
    protected DFA94 dfa94 = new DFA94(this);
    protected DFA98 dfa98 = new DFA98(this);
    protected DFA100 dfa100 = new DFA100(this);
    protected DFA101 dfa101 = new DFA101(this);
    protected DFA102 dfa102 = new DFA102(this);
    protected DFA121 dfa121 = new DFA121(this);
    static final String DFA1_eotS =
        "\31\uffff";
    static final String DFA1_eofS =
        "\1\1\30\uffff";
    static final String DFA1_minS =
        "\1\25\30\uffff";
    static final String DFA1_maxS =
        "\1\113\30\uffff";
    static final String DFA1_acceptS =
        "\1\uffff\1\2\1\1\26\uffff";
    static final String DFA1_specialS =
        "\31\uffff}>";
    static final String[] DFA1_transitionS = {
            "\1\2\1\uffff\1\2\20\uffff\1\2\1\uffff\2\2\4\uffff\3\2\1\uffff"+
            "\15\2\2\uffff\2\2\1\uffff\3\2\2\uffff\1\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA1_eot = DFA.unpackEncodedString(DFA1_eotS);
    static final short[] DFA1_eof = DFA.unpackEncodedString(DFA1_eofS);
    static final char[] DFA1_min = DFA.unpackEncodedStringToUnsignedChars(DFA1_minS);
    static final char[] DFA1_max = DFA.unpackEncodedStringToUnsignedChars(DFA1_maxS);
    static final short[] DFA1_accept = DFA.unpackEncodedString(DFA1_acceptS);
    static final short[] DFA1_special = DFA.unpackEncodedString(DFA1_specialS);
    static final short[][] DFA1_transition;

    static {
        int numStates = DFA1_transitionS.length;
        DFA1_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA1_transition[i] = DFA.unpackEncodedString(DFA1_transitionS[i]);
        }
    }

    class DFA1 extends DFA {

        public DFA1(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 1;
            this.eot = DFA1_eot;
            this.eof = DFA1_eof;
            this.min = DFA1_min;
            this.max = DFA1_max;
            this.accept = DFA1_accept;
            this.special = DFA1_special;
            this.transition = DFA1_transition;
        }
        public String getDescription() {
            return "()+ loopback of 211:4: ( external_declaration )+";
        }
    }
    static final String DFA2_eotS =
        "\30\uffff";
    static final String DFA2_eofS =
        "\30\uffff";
    static final String DFA2_minS =
        "\1\25\17\0\10\uffff";
    static final String DFA2_maxS =
        "\1\113\17\0\10\uffff";
    static final String DFA2_acceptS =
        "\20\uffff\2\1\1\2\1\uffff\1\3\1\4\1\5\1\6";
    static final String DFA2_specialS =
        "\1\0\1\1\1\2\1\3\1\4\1\5\1\6\1\7\1\10\1\11\1\12\1\13\1\14\1\15"+
        "\1\16\1\17\10\uffff}>";
    static final String[] DFA2_transitionS = {
            "\1\17\1\uffff\1\22\20\uffff\1\24\1\uffff\1\25\1\26\4\uffff"+
            "\1\27\1\21\1\3\1\uffff\1\22\4\1\1\4\1\5\1\6\1\7\1\10\1\11\1"+
            "\12\1\13\2\uffff\1\14\1\15\1\uffff\1\16\2\2\2\uffff\1\20",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA2_eot = DFA.unpackEncodedString(DFA2_eotS);
    static final short[] DFA2_eof = DFA.unpackEncodedString(DFA2_eofS);
    static final char[] DFA2_min = DFA.unpackEncodedStringToUnsignedChars(DFA2_minS);
    static final char[] DFA2_max = DFA.unpackEncodedStringToUnsignedChars(DFA2_maxS);
    static final short[] DFA2_accept = DFA.unpackEncodedString(DFA2_acceptS);
    static final short[] DFA2_special = DFA.unpackEncodedString(DFA2_specialS);
    static final short[][] DFA2_transition;

    static {
        int numStates = DFA2_transitionS.length;
        DFA2_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA2_transition[i] = DFA.unpackEncodedString(DFA2_transitionS[i]);
        }
    }

    class DFA2 extends DFA {

        public DFA2(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 2;
            this.eot = DFA2_eot;
            this.eof = DFA2_eof;
            this.min = DFA2_min;
            this.max = DFA2_max;
            this.accept = DFA2_accept;
            this.special = DFA2_special;
            this.transition = DFA2_transition;
        }
        public String getDescription() {
            return "214:1: external_declaration options {k=1; } : ( ( ( declaration_specifiers )? declarator ( declaration )* '{' )=> function_definition | declaration -> ^( GLOBAL_DECLARATION_TOK declaration ) | 'PRETDEF' IDENTIFIER ';' -> PRET_DEF_TOK | 'ReactiveInput' declaration_specifiers reactive_declarator ';' -> ^( 'ReactiveInput' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | 'ReactiveOutput' declaration_specifiers reactive_declarator ';' -> ^( 'ReactiveOutput' ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | thread_definition );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA2_0 = input.LA(1);

                         
                        int index2_0 = input.index();
                        input.rewind();
                        s = -1;
                        if ( ((LA2_0>=53 && LA2_0<=56)) ) {s = 1;}

                        else if ( ((LA2_0>=71 && LA2_0<=72)) ) {s = 2;}

                        else if ( (LA2_0==50) ) {s = 3;}

                        else if ( (LA2_0==57) ) {s = 4;}

                        else if ( (LA2_0==58) ) {s = 5;}

                        else if ( (LA2_0==59) ) {s = 6;}

                        else if ( (LA2_0==60) ) {s = 7;}

                        else if ( (LA2_0==61) ) {s = 8;}

                        else if ( (LA2_0==62) ) {s = 9;}

                        else if ( (LA2_0==63) ) {s = 10;}

                        else if ( (LA2_0==64) ) {s = 11;}

                        else if ( (LA2_0==67) ) {s = 12;}

                        else if ( (LA2_0==68) ) {s = 13;}

                        else if ( (LA2_0==70) ) {s = 14;}

                        else if ( (LA2_0==IDENTIFIER) ) {s = 15;}

                        else if ( (LA2_0==75) && (synpred4_PretC())) {s = 16;}

                        else if ( (LA2_0==49) && (synpred4_PretC())) {s = 17;}

                        else if ( (LA2_0==LINE_COMMAND||LA2_0==52) ) {s = 18;}

                        else if ( (LA2_0==40) ) {s = 20;}

                        else if ( (LA2_0==42) ) {s = 21;}

                        else if ( (LA2_0==43) ) {s = 22;}

                        else if ( (LA2_0==48) ) {s = 23;}

                         
                        input.seek(index2_0);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA2_1 = input.LA(1);

                         
                        int index2_1 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_1);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA2_2 = input.LA(1);

                         
                        int index2_2 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_2);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA2_3 = input.LA(1);

                         
                        int index2_3 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_3);
                        if ( s>=0 ) return s;
                        break;
                    case 4 : 
                        int LA2_4 = input.LA(1);

                         
                        int index2_4 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_4);
                        if ( s>=0 ) return s;
                        break;
                    case 5 : 
                        int LA2_5 = input.LA(1);

                         
                        int index2_5 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_5);
                        if ( s>=0 ) return s;
                        break;
                    case 6 : 
                        int LA2_6 = input.LA(1);

                         
                        int index2_6 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_6);
                        if ( s>=0 ) return s;
                        break;
                    case 7 : 
                        int LA2_7 = input.LA(1);

                         
                        int index2_7 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_7);
                        if ( s>=0 ) return s;
                        break;
                    case 8 : 
                        int LA2_8 = input.LA(1);

                         
                        int index2_8 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_8);
                        if ( s>=0 ) return s;
                        break;
                    case 9 : 
                        int LA2_9 = input.LA(1);

                         
                        int index2_9 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_9);
                        if ( s>=0 ) return s;
                        break;
                    case 10 : 
                        int LA2_10 = input.LA(1);

                         
                        int index2_10 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_10);
                        if ( s>=0 ) return s;
                        break;
                    case 11 : 
                        int LA2_11 = input.LA(1);

                         
                        int index2_11 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_11);
                        if ( s>=0 ) return s;
                        break;
                    case 12 : 
                        int LA2_12 = input.LA(1);

                         
                        int index2_12 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_12);
                        if ( s>=0 ) return s;
                        break;
                    case 13 : 
                        int LA2_13 = input.LA(1);

                         
                        int index2_13 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_13);
                        if ( s>=0 ) return s;
                        break;
                    case 14 : 
                        int LA2_14 = input.LA(1);

                         
                        int index2_14 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretC()) ) {s = 17;}

                        else if ( (synpred5_PretC()) ) {s = 18;}

                         
                        input.seek(index2_14);
                        if ( s>=0 ) return s;
                        break;
                    case 15 : 
                        int LA2_15 = input.LA(1);

                         
                        int index2_15 = input.index();
                        input.rewind();
                        s = -1;
                        if ( ((synpred4_PretC()||(synpred4_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText())))||(synpred4_PretC()&&(isTypeName(input.LT(1).getText()))))) ) {s = 17;}

                        else if ( (((synpred5_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred5_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 18;}

                         
                        input.seek(index2_15);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 2, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA9_eotS =
        "\47\uffff";
    static final String DFA9_eofS =
        "\47\uffff";
    static final String DFA9_minS =
        "\1\25\16\uffff\1\25\3\uffff\2\0\22\uffff";
    static final String DFA9_maxS =
        "\1\113\16\uffff\1\113\3\uffff\2\0\22\uffff";
    static final String DFA9_acceptS =
        "\1\uffff\1\1\16\uffff\1\2\26\uffff";
    static final String DFA9_specialS =
        "\23\uffff\1\0\1\1\22\uffff}>";
    static final String[] DFA9_transitionS = {
            "\1\17\33\uffff\1\20\1\1\2\uffff\14\1\2\uffff\2\1\1\uffff\3"+
            "\1\2\uffff\1\20",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\23\1\uffff\1\20\31\uffff\1\24\1\20\1\uffff\16\20\1\uffff"+
            "\2\20\1\uffff\4\20\1\uffff\1\1",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA9_eot = DFA.unpackEncodedString(DFA9_eotS);
    static final short[] DFA9_eof = DFA.unpackEncodedString(DFA9_eofS);
    static final char[] DFA9_min = DFA.unpackEncodedStringToUnsignedChars(DFA9_minS);
    static final char[] DFA9_max = DFA.unpackEncodedStringToUnsignedChars(DFA9_maxS);
    static final short[] DFA9_accept = DFA.unpackEncodedString(DFA9_acceptS);
    static final short[] DFA9_special = DFA.unpackEncodedString(DFA9_specialS);
    static final short[][] DFA9_transition;

    static {
        int numStates = DFA9_transitionS.length;
        DFA9_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA9_transition[i] = DFA.unpackEncodedString(DFA9_transitionS[i]);
        }
    }

    class DFA9 extends DFA {

        public DFA9(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 9;
            this.eot = DFA9_eot;
            this.eof = DFA9_eof;
            this.min = DFA9_min;
            this.max = DFA9_max;
            this.accept = DFA9_accept;
            this.special = DFA9_special;
            this.transition = DFA9_transition;
        }
        public String getDescription() {
            return "360:4: ( declaration_specifiers )?";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA9_19 = input.LA(1);

                         
                        int index9_19 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred15_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText())))||(synpred15_PretC()&&(isTypeName(input.LT(1).getText()))))) ) {s = 1;}

                        else if ( (true) ) {s = 16;}

                         
                        input.seek(index9_19);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA9_20 = input.LA(1);

                         
                        int index9_20 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred15_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText())))||(synpred15_PretC()&&(isTypeName(input.LT(1).getText()))))) ) {s = 1;}

                        else if ( (true) ) {s = 16;}

                         
                        input.seek(index9_20);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 9, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA11_eotS =
        "\23\uffff";
    static final String DFA11_eofS =
        "\23\uffff";
    static final String DFA11_minS =
        "\1\25\22\uffff";
    static final String DFA11_maxS =
        "\1\110\22\uffff";
    static final String DFA11_acceptS =
        "\1\uffff\1\1\20\uffff\1\2";
    static final String DFA11_specialS =
        "\23\uffff}>";
    static final String[] DFA11_transitionS = {
            "\1\1\1\uffff\1\1\32\uffff\1\1\1\uffff\15\1\1\22\1\uffff\2\1"+
            "\1\uffff\3\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA11_eot = DFA.unpackEncodedString(DFA11_eotS);
    static final short[] DFA11_eof = DFA.unpackEncodedString(DFA11_eofS);
    static final char[] DFA11_min = DFA.unpackEncodedStringToUnsignedChars(DFA11_minS);
    static final char[] DFA11_max = DFA.unpackEncodedStringToUnsignedChars(DFA11_maxS);
    static final short[] DFA11_accept = DFA.unpackEncodedString(DFA11_acceptS);
    static final short[] DFA11_special = DFA.unpackEncodedString(DFA11_specialS);
    static final short[][] DFA11_transition;

    static {
        int numStates = DFA11_transitionS.length;
        DFA11_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA11_transition[i] = DFA.unpackEncodedString(DFA11_transitionS[i]);
        }
    }

    class DFA11 extends DFA {

        public DFA11(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 11;
            this.eot = DFA11_eot;
            this.eof = DFA11_eof;
            this.min = DFA11_min;
            this.max = DFA11_max;
            this.accept = DFA11_accept;
            this.special = DFA11_special;
            this.transition = DFA11_transition;
        }
        public String getDescription() {
            return "368:3: ( ( declaration )+ scope_statement | scope_statement )";
        }
    }
    static final String DFA10_eotS =
        "\23\uffff";
    static final String DFA10_eofS =
        "\23\uffff";
    static final String DFA10_minS =
        "\1\25\22\uffff";
    static final String DFA10_maxS =
        "\1\110\22\uffff";
    static final String DFA10_acceptS =
        "\1\uffff\1\2\1\1\20\uffff";
    static final String DFA10_specialS =
        "\23\uffff}>";
    static final String[] DFA10_transitionS = {
            "\1\2\1\uffff\1\2\32\uffff\1\2\1\uffff\15\2\1\1\1\uffff\2\2"+
            "\1\uffff\3\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA10_eot = DFA.unpackEncodedString(DFA10_eotS);
    static final short[] DFA10_eof = DFA.unpackEncodedString(DFA10_eofS);
    static final char[] DFA10_min = DFA.unpackEncodedStringToUnsignedChars(DFA10_minS);
    static final char[] DFA10_max = DFA.unpackEncodedStringToUnsignedChars(DFA10_maxS);
    static final short[] DFA10_accept = DFA.unpackEncodedString(DFA10_acceptS);
    static final short[] DFA10_special = DFA.unpackEncodedString(DFA10_specialS);
    static final short[][] DFA10_transition;

    static {
        int numStates = DFA10_transitionS.length;
        DFA10_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA10_transition[i] = DFA.unpackEncodedString(DFA10_transitionS[i]);
        }
    }

    class DFA10 extends DFA {

        public DFA10(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 10;
            this.eot = DFA10_eot;
            this.eof = DFA10_eof;
            this.min = DFA10_min;
            this.max = DFA10_max;
            this.accept = DFA10_accept;
            this.special = DFA10_special;
            this.transition = DFA10_transition;
        }
        public String getDescription() {
            return "()+ loopback of 368:5: ( declaration )+";
        }
    }
    static final String DFA14_eotS =
        "\22\uffff";
    static final String DFA14_eofS =
        "\22\uffff";
    static final String DFA14_minS =
        "\1\25\21\uffff";
    static final String DFA14_maxS =
        "\1\110\21\uffff";
    static final String DFA14_acceptS =
        "\1\uffff\1\1\1\2\16\uffff\1\3";
    static final String DFA14_specialS =
        "\22\uffff}>";
    static final String[] DFA14_transitionS = {
            "\1\2\1\uffff\1\21\32\uffff\1\2\1\uffff\1\1\14\2\2\uffff\2\2"+
            "\1\uffff\3\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA14_eot = DFA.unpackEncodedString(DFA14_eotS);
    static final short[] DFA14_eof = DFA.unpackEncodedString(DFA14_eofS);
    static final char[] DFA14_min = DFA.unpackEncodedStringToUnsignedChars(DFA14_minS);
    static final char[] DFA14_max = DFA.unpackEncodedStringToUnsignedChars(DFA14_maxS);
    static final short[] DFA14_accept = DFA.unpackEncodedString(DFA14_acceptS);
    static final short[] DFA14_special = DFA.unpackEncodedString(DFA14_specialS);
    static final short[][] DFA14_transition;

    static {
        int numStates = DFA14_transitionS.length;
        DFA14_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA14_transition[i] = DFA.unpackEncodedString(DFA14_transitionS[i]);
        }
    }

    class DFA14 extends DFA {

        public DFA14(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 14;
            this.eot = DFA14_eot;
            this.eof = DFA14_eof;
            this.min = DFA14_min;
            this.max = DFA14_max;
            this.accept = DFA14_accept;
            this.special = DFA14_special;
            this.transition = DFA14_transition;
        }
        public String getDescription() {
            return "397:1: declaration : ( 'typedef' ( declaration_specifiers )? init_declarator_list ';' -> ^( TYPE_DECLARATION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | declaration_specifiers ( init_declarator_list )? ';' -> ^( DECLARATION_TOK ID_TOK[\"\"+ID] SOURCE_TOK[sourceTemp] ) | LINE_COMMAND -> PREPROC_TOK[$LINE_COMMAND.text] );";
        }
    }
    static final String DFA12_eotS =
        "\32\uffff";
    static final String DFA12_eofS =
        "\32\uffff";
    static final String DFA12_minS =
        "\1\25\16\uffff\1\25\4\uffff\1\0\5\uffff";
    static final String DFA12_maxS =
        "\1\113\16\uffff\1\113\4\uffff\1\0\5\uffff";
    static final String DFA12_acceptS =
        "\1\uffff\1\1\16\uffff\1\2\11\uffff";
    static final String DFA12_specialS =
        "\24\uffff\1\0\5\uffff}>";
    static final String[] DFA12_transitionS = {
            "\1\17\33\uffff\1\20\1\1\2\uffff\14\1\2\uffff\2\1\1\uffff\3"+
            "\1\2\uffff\1\20",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\1\23\uffff\1\20\2\uffff\3\20\2\uffff\1\24\27\uffff\1\20"+
            "\1\uffff\1\1",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA12_eot = DFA.unpackEncodedString(DFA12_eotS);
    static final short[] DFA12_eof = DFA.unpackEncodedString(DFA12_eofS);
    static final char[] DFA12_min = DFA.unpackEncodedStringToUnsignedChars(DFA12_minS);
    static final char[] DFA12_max = DFA.unpackEncodedStringToUnsignedChars(DFA12_maxS);
    static final short[] DFA12_accept = DFA.unpackEncodedString(DFA12_acceptS);
    static final short[] DFA12_special = DFA.unpackEncodedString(DFA12_specialS);
    static final short[][] DFA12_transition;

    static {
        int numStates = DFA12_transitionS.length;
        DFA12_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA12_transition[i] = DFA.unpackEncodedString(DFA12_transitionS[i]);
        }
    }

    class DFA12 extends DFA {

        public DFA12(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 12;
            this.eot = DFA12_eot;
            this.eof = DFA12_eof;
            this.min = DFA12_min;
            this.max = DFA12_max;
            this.accept = DFA12_accept;
            this.special = DFA12_special;
            this.transition = DFA12_transition;
        }
        public String getDescription() {
            return "410:45: ( declaration_specifiers )?";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA12_20 = input.LA(1);

                         
                        int index12_20 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred18_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred18_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 1;}

                        else if ( (true) ) {s = 16;}

                         
                        input.seek(index12_20);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 12, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA15_eotS =
        "\20\uffff";
    static final String DFA15_eofS =
        "\20\uffff";
    static final String DFA15_minS =
        "\1\25\17\uffff";
    static final String DFA15_maxS =
        "\1\110\17\uffff";
    static final String DFA15_acceptS =
        "\1\uffff\1\3\14\uffff\1\1\1\2";
    static final String DFA15_specialS =
        "\20\uffff}>";
    static final String[] DFA15_transitionS = {
            "\1\1\34\uffff\1\1\2\uffff\4\16\10\1\2\uffff\2\1\1\uffff\1\1"+
            "\2\17",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA15_eot = DFA.unpackEncodedString(DFA15_eotS);
    static final short[] DFA15_eof = DFA.unpackEncodedString(DFA15_eofS);
    static final char[] DFA15_min = DFA.unpackEncodedStringToUnsignedChars(DFA15_minS);
    static final char[] DFA15_max = DFA.unpackEncodedStringToUnsignedChars(DFA15_maxS);
    static final short[] DFA15_accept = DFA.unpackEncodedString(DFA15_acceptS);
    static final short[] DFA15_special = DFA.unpackEncodedString(DFA15_specialS);
    static final short[][] DFA15_transition;

    static {
        int numStates = DFA15_transitionS.length;
        DFA15_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA15_transition[i] = DFA.unpackEncodedString(DFA15_transitionS[i]);
        }
    }

    class DFA15 extends DFA {

        public DFA15(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 15;
            this.eot = DFA15_eot;
            this.eof = DFA15_eof;
            this.min = DFA15_min;
            this.max = DFA15_max;
            this.accept = DFA15_accept;
            this.special = DFA15_special;
            this.transition = DFA15_transition;
        }
        public String getDescription() {
            return "()* loopback of 476:6: ( storage_class_specifier | type_qualifier )*";
        }
    }
    static final String DFA24_eotS =
        "\107\uffff";
    static final String DFA24_eofS =
        "\7\uffff\1\27\77\uffff";
    static final String DFA24_minS =
        "\1\25\1\uffff\2\73\3\uffff\1\25\5\uffff\2\0\4\uffff\1\0\2\uffff"+
        "\1\0\60\uffff";
    static final String DFA24_maxS =
        "\1\106\1\uffff\2\76\3\uffff\1\113\5\uffff\2\0\4\uffff\1\0\2\uffff"+
        "\1\0\60\uffff";
    static final String DFA24_acceptS =
        "\1\uffff\1\1\2\uffff\1\2\1\3\1\4\1\uffff\1\7\1\10\1\11\1\uffff"+
        "\1\12\12\uffff\1\6\54\uffff\1\13\1\14\1\5";
    static final String DFA24_specialS =
        "\15\uffff\1\0\1\1\4\uffff\1\2\2\uffff\1\3\60\uffff}>";
    static final String[] DFA24_transitionS = {
            "\1\15\34\uffff\1\1\6\uffff\1\2\1\3\1\4\1\5\1\6\1\7\1\10\1\11"+
            "\2\uffff\2\12\1\uffff\1\14",
            "",
            "\1\4\1\5\1\6\1\16",
            "\1\4\1\5\1\6\1\23",
            "",
            "",
            "",
            "\1\27\23\uffff\1\27\3\uffff\2\27\2\uffff\3\27\5\uffff\5\27"+
            "\1\26\2\27\2\uffff\7\27\1\uffff\1\27",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA24_eot = DFA.unpackEncodedString(DFA24_eotS);
    static final short[] DFA24_eof = DFA.unpackEncodedString(DFA24_eofS);
    static final char[] DFA24_min = DFA.unpackEncodedStringToUnsignedChars(DFA24_minS);
    static final char[] DFA24_max = DFA.unpackEncodedStringToUnsignedChars(DFA24_maxS);
    static final short[] DFA24_accept = DFA.unpackEncodedString(DFA24_acceptS);
    static final short[] DFA24_special = DFA.unpackEncodedString(DFA24_specialS);
    static final short[][] DFA24_transition;

    static {
        int numStates = DFA24_transitionS.length;
        DFA24_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA24_transition[i] = DFA.unpackEncodedString(DFA24_transitionS[i]);
        }
    }

    class DFA24 extends DFA {

        public DFA24(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 24;
            this.eot = DFA24_eot;
            this.eof = DFA24_eof;
            this.min = DFA24_min;
            this.max = DFA24_max;
            this.accept = DFA24_accept;
            this.special = DFA24_special;
            this.transition = DFA24_transition;
        }
        public String getDescription() {
            return "519:1: type_specifier : ( 'void' | ( 'unsigned' | 'signed' )? 'char' | ( 'unsigned' | 'signed' )? 'short' | ( 'unsigned' | 'signed' )? 'int' | ( 'unsigned' | 'signed' )? 'long' 'long' | ( 'unsigned' | 'signed' )? 'long' | 'float' | 'double' | struct_or_union_specifier | enum_specifier | type_id | declared_id );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA24_13 = input.LA(1);

                         
                        int index24_13 = input.index();
                        input.rewind();
                        s = -1;
                        if ( ((synpred50_PretC()&&(isTypeName(input.LT(1).getText())))) ) {s = 68;}

                        else if ( ((PRETdefinedtable.contains(input.LT(1).getText()))) ) {s = 69;}

                         
                        input.seek(index24_13);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA24_14 = input.LA(1);

                         
                        int index24_14 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred42_PretC()) ) {s = 70;}

                        else if ( (synpred45_PretC()) ) {s = 23;}

                         
                        input.seek(index24_14);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA24_19 = input.LA(1);

                         
                        int index24_19 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred42_PretC()) ) {s = 70;}

                        else if ( (synpred45_PretC()) ) {s = 23;}

                         
                        input.seek(index24_19);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA24_22 = input.LA(1);

                         
                        int index24_22 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred42_PretC()) ) {s = 70;}

                        else if ( (synpred45_PretC()) ) {s = 23;}

                         
                        input.seek(index24_22);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 24, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA26_eotS =
        "\67\uffff";
    static final String DFA26_eofS =
        "\3\uffff\1\10\1\uffff\1\10\61\uffff";
    static final String DFA26_minS =
        "\1\103\3\25\1\uffff\1\25\61\uffff";
    static final String DFA26_maxS =
        "\1\104\2\101\1\113\1\uffff\1\113\61\uffff";
    static final String DFA26_acceptS =
        "\4\uffff\1\1\3\uffff\1\2\56\uffff";
    static final String DFA26_specialS =
        "\67\uffff}>";
    static final String[] DFA26_transitionS = {
            "\1\1\1\2",
            "\1\3\53\uffff\1\4",
            "\1\5\53\uffff\1\4",
            "\1\10\23\uffff\1\10\3\uffff\2\10\2\uffff\3\10\5\uffff\10\10"+
            "\1\4\1\uffff\7\10\1\uffff\1\10",
            "",
            "\1\10\23\uffff\1\10\3\uffff\2\10\2\uffff\3\10\5\uffff\10\10"+
            "\1\4\1\uffff\7\10\1\uffff\1\10",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA26_eot = DFA.unpackEncodedString(DFA26_eotS);
    static final short[] DFA26_eof = DFA.unpackEncodedString(DFA26_eofS);
    static final char[] DFA26_min = DFA.unpackEncodedStringToUnsignedChars(DFA26_minS);
    static final char[] DFA26_max = DFA.unpackEncodedStringToUnsignedChars(DFA26_maxS);
    static final short[] DFA26_accept = DFA.unpackEncodedString(DFA26_acceptS);
    static final short[] DFA26_special = DFA.unpackEncodedString(DFA26_specialS);
    static final short[][] DFA26_transition;

    static {
        int numStates = DFA26_transitionS.length;
        DFA26_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA26_transition[i] = DFA.unpackEncodedString(DFA26_transitionS[i]);
        }
    }

    class DFA26 extends DFA {

        public DFA26(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 26;
            this.eot = DFA26_eot;
            this.eof = DFA26_eof;
            this.min = DFA26_min;
            this.max = DFA26_max;
            this.accept = DFA26_accept;
            this.special = DFA26_special;
            this.transition = DFA26_transition;
        }
        public String getDescription() {
            return "589:1: struct_or_union_specifier returns [String typeTemp, StatementNode n, String structTypeName] options {k=3; } : ( struct_or_union ( IDENTIFIER )? '{' struct_declaration_list '}' | struct_or_union IDENTIFIER );";
        }
    }
    static final String DFA28_eotS =
        "\20\uffff";
    static final String DFA28_eofS =
        "\20\uffff";
    static final String DFA28_minS =
        "\1\25\17\uffff";
    static final String DFA28_maxS =
        "\1\110\17\uffff";
    static final String DFA28_acceptS =
        "\1\uffff\1\2\1\1\15\uffff";
    static final String DFA28_specialS =
        "\20\uffff}>";
    static final String[] DFA28_transitionS = {
            "\1\2\34\uffff\1\2\6\uffff\10\2\1\uffff\1\1\2\2\1\uffff\3\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA28_eot = DFA.unpackEncodedString(DFA28_eotS);
    static final short[] DFA28_eof = DFA.unpackEncodedString(DFA28_eofS);
    static final char[] DFA28_min = DFA.unpackEncodedStringToUnsignedChars(DFA28_minS);
    static final char[] DFA28_max = DFA.unpackEncodedStringToUnsignedChars(DFA28_maxS);
    static final short[] DFA28_accept = DFA.unpackEncodedString(DFA28_acceptS);
    static final short[] DFA28_special = DFA.unpackEncodedString(DFA28_specialS);
    static final short[][] DFA28_transition;

    static {
        int numStates = DFA28_transitionS.length;
        DFA28_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA28_transition[i] = DFA.unpackEncodedString(DFA28_transitionS[i]);
        }
    }

    class DFA28 extends DFA {

        public DFA28(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 28;
            this.eot = DFA28_eot;
            this.eof = DFA28_eof;
            this.min = DFA28_min;
            this.max = DFA28_max;
            this.accept = DFA28_accept;
            this.special = DFA28_special;
            this.transition = DFA28_transition;
        }
        public String getDescription() {
            return "()* loopback of 638:25: ( struct_declaration )*";
        }
    }
    static final String DFA30_eotS =
        "\53\uffff";
    static final String DFA30_eofS =
        "\53\uffff";
    static final String DFA30_minS =
        "\1\25\1\uffff\1\0\50\uffff";
    static final String DFA30_maxS =
        "\1\113\1\uffff\1\0\50\uffff";
    static final String DFA30_acceptS =
        "\1\uffff\1\3\6\uffff\1\1\1\2\41\uffff";
    static final String DFA30_specialS =
        "\2\uffff\1\0\50\uffff}>";
    static final String[] DFA30_transitionS = {
            "\1\2\23\uffff\1\1\7\uffff\1\1\1\11\1\1\5\uffff\10\11\2\uffff"+
            "\2\11\1\1\1\11\2\10\1\1\1\uffff\1\1",
            "",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA30_eot = DFA.unpackEncodedString(DFA30_eotS);
    static final short[] DFA30_eof = DFA.unpackEncodedString(DFA30_eofS);
    static final char[] DFA30_min = DFA.unpackEncodedStringToUnsignedChars(DFA30_minS);
    static final char[] DFA30_max = DFA.unpackEncodedStringToUnsignedChars(DFA30_maxS);
    static final short[] DFA30_accept = DFA.unpackEncodedString(DFA30_acceptS);
    static final short[] DFA30_special = DFA.unpackEncodedString(DFA30_specialS);
    static final short[][] DFA30_transition;

    static {
        int numStates = DFA30_transitionS.length;
        DFA30_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA30_transition[i] = DFA.unpackEncodedString(DFA30_transitionS[i]);
        }
    }

    class DFA30 extends DFA {

        public DFA30(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 30;
            this.eot = DFA30_eot;
            this.eof = DFA30_eof;
            this.min = DFA30_min;
            this.max = DFA30_max;
            this.accept = DFA30_accept;
            this.special = DFA30_special;
            this.transition = DFA30_transition;
        }
        public String getDescription() {
            return "()+ loopback of 660:4: ( type_qualifier | type_specifier )+";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA30_2 = input.LA(1);

                         
                        int index30_2 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred57_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred57_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 9;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index30_2);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 30, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA35_eotS =
        "\34\uffff";
    static final String DFA35_eofS =
        "\3\uffff\1\5\30\uffff";
    static final String DFA35_minS =
        "\1\106\1\25\1\uffff\1\25\30\uffff";
    static final String DFA35_maxS =
        "\1\106\1\101\1\uffff\1\113\30\uffff";
    static final String DFA35_acceptS =
        "\2\uffff\1\1\1\uffff\1\2\1\3\26\uffff";
    static final String DFA35_specialS =
        "\34\uffff}>";
    static final String[] DFA35_transitionS = {
            "\1\1",
            "\1\3\53\uffff\1\2",
            "",
            "\1\5\23\uffff\1\5\3\uffff\2\5\2\uffff\3\5\5\uffff\10\5\1\4"+
            "\1\uffff\7\5\1\uffff\1\5",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA35_eot = DFA.unpackEncodedString(DFA35_eotS);
    static final short[] DFA35_eof = DFA.unpackEncodedString(DFA35_eofS);
    static final char[] DFA35_min = DFA.unpackEncodedStringToUnsignedChars(DFA35_minS);
    static final char[] DFA35_max = DFA.unpackEncodedStringToUnsignedChars(DFA35_maxS);
    static final short[] DFA35_accept = DFA.unpackEncodedString(DFA35_acceptS);
    static final short[] DFA35_special = DFA.unpackEncodedString(DFA35_specialS);
    static final short[][] DFA35_transition;

    static {
        int numStates = DFA35_transitionS.length;
        DFA35_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA35_transition[i] = DFA.unpackEncodedString(DFA35_transitionS[i]);
        }
    }

    class DFA35 extends DFA {

        public DFA35(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 35;
            this.eot = DFA35_eot;
            this.eof = DFA35_eof;
            this.min = DFA35_min;
            this.max = DFA35_max;
            this.accept = DFA35_accept;
            this.special = DFA35_special;
            this.transition = DFA35_transition;
        }
        public String getDescription() {
            return "685:1: enum_specifier options {k=3; } : ( 'enum' '{' enumerator_list '}' | 'enum' IDENTIFIER '{' enumerator_list '}' | 'enum' IDENTIFIER );";
        }
    }
    static final String DFA39_eotS =
        "\41\uffff";
    static final String DFA39_eofS =
        "\41\uffff";
    static final String DFA39_minS =
        "\1\25\1\0\37\uffff";
    static final String DFA39_maxS =
        "\1\113\1\0\37\uffff";
    static final String DFA39_acceptS =
        "\2\uffff\1\1\35\uffff\1\2";
    static final String DFA39_specialS =
        "\1\uffff\1\0\37\uffff}>";
    static final String[] DFA39_transitionS = {
            "\1\2\33\uffff\1\2\31\uffff\1\1",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA39_eot = DFA.unpackEncodedString(DFA39_eotS);
    static final short[] DFA39_eof = DFA.unpackEncodedString(DFA39_eofS);
    static final char[] DFA39_min = DFA.unpackEncodedStringToUnsignedChars(DFA39_minS);
    static final char[] DFA39_max = DFA.unpackEncodedStringToUnsignedChars(DFA39_maxS);
    static final short[] DFA39_accept = DFA.unpackEncodedString(DFA39_acceptS);
    static final short[] DFA39_special = DFA.unpackEncodedString(DFA39_specialS);
    static final short[][] DFA39_transition;

    static {
        int numStates = DFA39_transitionS.length;
        DFA39_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA39_transition[i] = DFA.unpackEncodedString(DFA39_transitionS[i]);
        }
    }

    class DFA39 extends DFA {

        public DFA39(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 39;
            this.eot = DFA39_eot;
            this.eof = DFA39_eof;
            this.min = DFA39_min;
            this.max = DFA39_max;
            this.accept = DFA39_accept;
            this.special = DFA39_special;
            this.transition = DFA39_transition;
        }
        public String getDescription() {
            return "705:1: declarator : ( ( pointer )? direct_declarator | pointer );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA39_1 = input.LA(1);

                         
                        int index39_1 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred68_PretC()) ) {s = 2;}

                        else if ( (true) ) {s = 32;}

                         
                        input.seek(index39_1);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 39, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA40_eotS =
        "\71\uffff";
    static final String DFA40_eofS =
        "\1\1\70\uffff";
    static final String DFA40_minS =
        "\1\25\32\uffff\2\25\20\0\3\uffff\10\0\1\uffff";
    static final String DFA40_maxS =
        "\1\113\32\uffff\1\113\1\130\20\0\3\uffff\10\0\1\uffff";
    static final String DFA40_acceptS =
        "\1\uffff\1\2\66\uffff\1\1";
    static final String DFA40_specialS =
        "\35\uffff\1\0\1\1\1\2\1\3\1\4\1\5\1\6\1\7\1\10\1\11\1\12\1\13\1"+
        "\14\1\15\1\16\1\17\3\uffff\1\20\1\21\1\22\1\23\1\24\1\25\1\26\1"+
        "\27\1\uffff}>";
    static final String[] DFA40_transitionS = {
            "\1\1\1\uffff\1\1\21\uffff\1\1\2\uffff\3\1\2\uffff\1\33\20\1"+
            "\1\uffff\6\1\1\34\1\uffff\1\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\54\33\uffff\1\1\1\40\1\35\1\uffff\4\36\1\41\1\42\1\43\1"+
            "\44\1\45\1\46\1\47\1\50\2\uffff\1\51\1\52\1\uffff\1\53\2\37"+
            "\1\1\1\uffff\1\1",
            "\1\62\1\63\1\uffff\5\63\24\uffff\1\61\30\uffff\1\60\1\66\1"+
            "\uffff\2\66\2\uffff\1\64\1\65\1\67\2\uffff\3\66",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            ""
    };

    static final short[] DFA40_eot = DFA.unpackEncodedString(DFA40_eotS);
    static final short[] DFA40_eof = DFA.unpackEncodedString(DFA40_eofS);
    static final char[] DFA40_min = DFA.unpackEncodedStringToUnsignedChars(DFA40_minS);
    static final char[] DFA40_max = DFA.unpackEncodedStringToUnsignedChars(DFA40_maxS);
    static final short[] DFA40_accept = DFA.unpackEncodedString(DFA40_acceptS);
    static final short[] DFA40_special = DFA.unpackEncodedString(DFA40_specialS);
    static final short[][] DFA40_transition;

    static {
        int numStates = DFA40_transitionS.length;
        DFA40_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA40_transition[i] = DFA.unpackEncodedString(DFA40_transitionS[i]);
        }
    }

    class DFA40 extends DFA {

        public DFA40(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 40;
            this.eot = DFA40_eot;
            this.eof = DFA40_eof;
            this.min = DFA40_min;
            this.max = DFA40_max;
            this.accept = DFA40_accept;
            this.special = DFA40_special;
            this.transition = DFA40_transition;
        }
        public String getDescription() {
            return "()* loopback of 719:4: ( declarator_suffix )*";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA40_29 = input.LA(1);

                         
                        int index40_29 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_29);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA40_30 = input.LA(1);

                         
                        int index40_30 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_30);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA40_31 = input.LA(1);

                         
                        int index40_31 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_31);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA40_32 = input.LA(1);

                         
                        int index40_32 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_32);
                        if ( s>=0 ) return s;
                        break;
                    case 4 : 
                        int LA40_33 = input.LA(1);

                         
                        int index40_33 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_33);
                        if ( s>=0 ) return s;
                        break;
                    case 5 : 
                        int LA40_34 = input.LA(1);

                         
                        int index40_34 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_34);
                        if ( s>=0 ) return s;
                        break;
                    case 6 : 
                        int LA40_35 = input.LA(1);

                         
                        int index40_35 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_35);
                        if ( s>=0 ) return s;
                        break;
                    case 7 : 
                        int LA40_36 = input.LA(1);

                         
                        int index40_36 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_36);
                        if ( s>=0 ) return s;
                        break;
                    case 8 : 
                        int LA40_37 = input.LA(1);

                         
                        int index40_37 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_37);
                        if ( s>=0 ) return s;
                        break;
                    case 9 : 
                        int LA40_38 = input.LA(1);

                         
                        int index40_38 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_38);
                        if ( s>=0 ) return s;
                        break;
                    case 10 : 
                        int LA40_39 = input.LA(1);

                         
                        int index40_39 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_39);
                        if ( s>=0 ) return s;
                        break;
                    case 11 : 
                        int LA40_40 = input.LA(1);

                         
                        int index40_40 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_40);
                        if ( s>=0 ) return s;
                        break;
                    case 12 : 
                        int LA40_41 = input.LA(1);

                         
                        int index40_41 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_41);
                        if ( s>=0 ) return s;
                        break;
                    case 13 : 
                        int LA40_42 = input.LA(1);

                         
                        int index40_42 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_42);
                        if ( s>=0 ) return s;
                        break;
                    case 14 : 
                        int LA40_43 = input.LA(1);

                         
                        int index40_43 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_43);
                        if ( s>=0 ) return s;
                        break;
                    case 15 : 
                        int LA40_44 = input.LA(1);

                         
                        int index40_44 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_44);
                        if ( s>=0 ) return s;
                        break;
                    case 16 : 
                        int LA40_48 = input.LA(1);

                         
                        int index40_48 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_48);
                        if ( s>=0 ) return s;
                        break;
                    case 17 : 
                        int LA40_49 = input.LA(1);

                         
                        int index40_49 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_49);
                        if ( s>=0 ) return s;
                        break;
                    case 18 : 
                        int LA40_50 = input.LA(1);

                         
                        int index40_50 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_50);
                        if ( s>=0 ) return s;
                        break;
                    case 19 : 
                        int LA40_51 = input.LA(1);

                         
                        int index40_51 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_51);
                        if ( s>=0 ) return s;
                        break;
                    case 20 : 
                        int LA40_52 = input.LA(1);

                         
                        int index40_52 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_52);
                        if ( s>=0 ) return s;
                        break;
                    case 21 : 
                        int LA40_53 = input.LA(1);

                         
                        int index40_53 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_53);
                        if ( s>=0 ) return s;
                        break;
                    case 22 : 
                        int LA40_54 = input.LA(1);

                         
                        int index40_54 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_54);
                        if ( s>=0 ) return s;
                        break;
                    case 23 : 
                        int LA40_55 = input.LA(1);

                         
                        int index40_55 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred69_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index40_55);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 40, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA41_eotS =
        "\71\uffff";
    static final String DFA41_eofS =
        "\1\1\70\uffff";
    static final String DFA41_minS =
        "\1\25\32\uffff\2\25\20\0\3\uffff\10\0\1\uffff";
    static final String DFA41_maxS =
        "\1\113\32\uffff\1\113\1\130\20\0\3\uffff\10\0\1\uffff";
    static final String DFA41_acceptS =
        "\1\uffff\1\2\66\uffff\1\1";
    static final String DFA41_specialS =
        "\35\uffff\1\0\1\1\1\2\1\3\1\4\1\5\1\6\1\7\1\10\1\11\1\12\1\13\1"+
        "\14\1\15\1\16\1\17\3\uffff\1\20\1\21\1\22\1\23\1\24\1\25\1\26\1"+
        "\27\1\uffff}>";
    static final String[] DFA41_transitionS = {
            "\1\1\1\uffff\1\1\21\uffff\1\1\2\uffff\3\1\2\uffff\1\33\20\1"+
            "\1\uffff\6\1\1\34\1\uffff\1\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\54\33\uffff\1\1\1\40\1\35\1\uffff\4\36\1\41\1\42\1\43\1"+
            "\44\1\45\1\46\1\47\1\50\2\uffff\1\51\1\52\1\uffff\1\53\2\37"+
            "\1\1\1\uffff\1\1",
            "\1\62\1\63\1\uffff\5\63\24\uffff\1\61\30\uffff\1\60\1\66\1"+
            "\uffff\2\66\2\uffff\1\64\1\65\1\67\2\uffff\3\66",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            ""
    };

    static final short[] DFA41_eot = DFA.unpackEncodedString(DFA41_eotS);
    static final short[] DFA41_eof = DFA.unpackEncodedString(DFA41_eofS);
    static final char[] DFA41_min = DFA.unpackEncodedStringToUnsignedChars(DFA41_minS);
    static final char[] DFA41_max = DFA.unpackEncodedStringToUnsignedChars(DFA41_maxS);
    static final short[] DFA41_accept = DFA.unpackEncodedString(DFA41_acceptS);
    static final short[] DFA41_special = DFA.unpackEncodedString(DFA41_specialS);
    static final short[][] DFA41_transition;

    static {
        int numStates = DFA41_transitionS.length;
        DFA41_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA41_transition[i] = DFA.unpackEncodedString(DFA41_transitionS[i]);
        }
    }

    class DFA41 extends DFA {

        public DFA41(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 41;
            this.eot = DFA41_eot;
            this.eof = DFA41_eof;
            this.min = DFA41_min;
            this.max = DFA41_max;
            this.accept = DFA41_accept;
            this.special = DFA41_special;
            this.transition = DFA41_transition;
        }
        public String getDescription() {
            return "()* loopback of 722:22: ( declarator_suffix )*";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA41_29 = input.LA(1);

                         
                        int index41_29 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_29);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA41_30 = input.LA(1);

                         
                        int index41_30 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_30);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA41_31 = input.LA(1);

                         
                        int index41_31 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_31);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA41_32 = input.LA(1);

                         
                        int index41_32 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_32);
                        if ( s>=0 ) return s;
                        break;
                    case 4 : 
                        int LA41_33 = input.LA(1);

                         
                        int index41_33 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_33);
                        if ( s>=0 ) return s;
                        break;
                    case 5 : 
                        int LA41_34 = input.LA(1);

                         
                        int index41_34 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_34);
                        if ( s>=0 ) return s;
                        break;
                    case 6 : 
                        int LA41_35 = input.LA(1);

                         
                        int index41_35 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_35);
                        if ( s>=0 ) return s;
                        break;
                    case 7 : 
                        int LA41_36 = input.LA(1);

                         
                        int index41_36 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_36);
                        if ( s>=0 ) return s;
                        break;
                    case 8 : 
                        int LA41_37 = input.LA(1);

                         
                        int index41_37 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_37);
                        if ( s>=0 ) return s;
                        break;
                    case 9 : 
                        int LA41_38 = input.LA(1);

                         
                        int index41_38 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_38);
                        if ( s>=0 ) return s;
                        break;
                    case 10 : 
                        int LA41_39 = input.LA(1);

                         
                        int index41_39 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_39);
                        if ( s>=0 ) return s;
                        break;
                    case 11 : 
                        int LA41_40 = input.LA(1);

                         
                        int index41_40 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_40);
                        if ( s>=0 ) return s;
                        break;
                    case 12 : 
                        int LA41_41 = input.LA(1);

                         
                        int index41_41 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_41);
                        if ( s>=0 ) return s;
                        break;
                    case 13 : 
                        int LA41_42 = input.LA(1);

                         
                        int index41_42 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_42);
                        if ( s>=0 ) return s;
                        break;
                    case 14 : 
                        int LA41_43 = input.LA(1);

                         
                        int index41_43 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_43);
                        if ( s>=0 ) return s;
                        break;
                    case 15 : 
                        int LA41_44 = input.LA(1);

                         
                        int index41_44 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_44);
                        if ( s>=0 ) return s;
                        break;
                    case 16 : 
                        int LA41_48 = input.LA(1);

                         
                        int index41_48 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_48);
                        if ( s>=0 ) return s;
                        break;
                    case 17 : 
                        int LA41_49 = input.LA(1);

                         
                        int index41_49 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_49);
                        if ( s>=0 ) return s;
                        break;
                    case 18 : 
                        int LA41_50 = input.LA(1);

                         
                        int index41_50 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_50);
                        if ( s>=0 ) return s;
                        break;
                    case 19 : 
                        int LA41_51 = input.LA(1);

                         
                        int index41_51 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_51);
                        if ( s>=0 ) return s;
                        break;
                    case 20 : 
                        int LA41_52 = input.LA(1);

                         
                        int index41_52 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_52);
                        if ( s>=0 ) return s;
                        break;
                    case 21 : 
                        int LA41_53 = input.LA(1);

                         
                        int index41_53 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_53);
                        if ( s>=0 ) return s;
                        break;
                    case 22 : 
                        int LA41_54 = input.LA(1);

                         
                        int index41_54 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_54);
                        if ( s>=0 ) return s;
                        break;
                    case 23 : 
                        int LA41_55 = input.LA(1);

                         
                        int index41_55 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred71_PretC()) ) {s = 56;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index41_55);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 41, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA43_eotS =
        "\34\uffff";
    static final String DFA43_eofS =
        "\34\uffff";
    static final String DFA43_minS =
        "\1\61\2\25\11\uffff\1\0\17\uffff";
    static final String DFA43_maxS =
        "\1\111\1\130\1\110\11\uffff\1\0\17\uffff";
    static final String DFA43_acceptS =
        "\3\uffff\1\2\1\1\6\uffff\1\5\1\uffff\1\3\15\uffff\1\4";
    static final String DFA43_specialS =
        "\14\uffff\1\0\17\uffff}>";
    static final String[] DFA43_transitionS = {
            "\1\2\27\uffff\1\1",
            "\2\4\1\uffff\5\4\24\uffff\1\4\30\uffff\1\3\1\4\1\uffff\2\4"+
            "\2\uffff\3\4\2\uffff\3\4",
            "\1\14\34\uffff\1\15\1\13\1\uffff\14\15\2\uffff\2\15\1\uffff"+
            "\3\15",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA43_eot = DFA.unpackEncodedString(DFA43_eotS);
    static final short[] DFA43_eof = DFA.unpackEncodedString(DFA43_eofS);
    static final char[] DFA43_min = DFA.unpackEncodedStringToUnsignedChars(DFA43_minS);
    static final char[] DFA43_max = DFA.unpackEncodedStringToUnsignedChars(DFA43_maxS);
    static final short[] DFA43_accept = DFA.unpackEncodedString(DFA43_acceptS);
    static final short[] DFA43_special = DFA.unpackEncodedString(DFA43_specialS);
    static final short[][] DFA43_transition;

    static {
        int numStates = DFA43_transitionS.length;
        DFA43_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA43_transition[i] = DFA.unpackEncodedString(DFA43_transitionS[i]);
        }
    }

    class DFA43 extends DFA {

        public DFA43(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 43;
            this.eot = DFA43_eot;
            this.eof = DFA43_eof;
            this.min = DFA43_min;
            this.max = DFA43_max;
            this.accept = DFA43_accept;
            this.special = DFA43_special;
            this.transition = DFA43_transition;
        }
        public String getDescription() {
            return "725:1: declarator_suffix : ( '[' constant_expression ']' | '[' ']' | '(' parameter_type_list ')' | '(' identifier_list ')' | '(' ')' );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA43_12 = input.LA(1);

                         
                        int index43_12 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred74_PretC()) ) {s = 13;}

                        else if ( (synpred75_PretC()) ) {s = 27;}

                         
                        input.seek(index43_12);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 43, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA46_eotS =
        "\40\uffff";
    static final String DFA46_eofS =
        "\1\uffff\1\2\36\uffff";
    static final String DFA46_minS =
        "\1\113\1\25\10\uffff\1\0\21\uffff\1\0\3\uffff";
    static final String DFA46_maxS =
        "\2\113\10\uffff\1\0\21\uffff\1\0\3\uffff";
    static final String DFA46_acceptS =
        "\2\uffff\1\3\33\uffff\1\1\1\2";
    static final String DFA46_specialS =
        "\12\uffff\1\0\21\uffff\1\1\3\uffff}>";
    static final String[] DFA46_transitionS = {
            "\1\1",
            "\1\2\1\uffff\1\2\21\uffff\1\2\2\uffff\3\2\2\uffff\21\2\1\uffff"+
            "\4\2\2\12\1\2\1\uffff\1\34",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "",
            ""
    };

    static final short[] DFA46_eot = DFA.unpackEncodedString(DFA46_eotS);
    static final short[] DFA46_eof = DFA.unpackEncodedString(DFA46_eofS);
    static final char[] DFA46_min = DFA.unpackEncodedStringToUnsignedChars(DFA46_minS);
    static final char[] DFA46_max = DFA.unpackEncodedStringToUnsignedChars(DFA46_maxS);
    static final short[] DFA46_accept = DFA.unpackEncodedString(DFA46_acceptS);
    static final short[] DFA46_special = DFA.unpackEncodedString(DFA46_specialS);
    static final short[][] DFA46_transition;

    static {
        int numStates = DFA46_transitionS.length;
        DFA46_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA46_transition[i] = DFA.unpackEncodedString(DFA46_transitionS[i]);
        }
    }

    class DFA46 extends DFA {

        public DFA46(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 46;
            this.eot = DFA46_eot;
            this.eof = DFA46_eof;
            this.min = DFA46_min;
            this.max = DFA46_max;
            this.accept = DFA46_accept;
            this.special = DFA46_special;
            this.transition = DFA46_transition;
        }
        public String getDescription() {
            return "733:1: pointer : ( '*' ( type_qualifier )+ ( pointer )? | '*' pointer | '*' );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA46_10 = input.LA(1);

                         
                        int index46_10 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred78_PretC()) ) {s = 30;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index46_10);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA46_28 = input.LA(1);

                         
                        int index46_28 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred79_PretC()) ) {s = 31;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index46_28);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 46, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA44_eotS =
        "\72\uffff";
    static final String DFA44_eofS =
        "\1\1\71\uffff";
    static final String DFA44_minS =
        "\1\25\11\uffff\1\0\57\uffff";
    static final String DFA44_maxS =
        "\1\113\11\uffff\1\0\57\uffff";
    static final String DFA44_acceptS =
        "\1\uffff\1\2\67\uffff\1\1";
    static final String DFA44_specialS =
        "\12\uffff\1\0\57\uffff}>";
    static final String[] DFA44_transitionS = {
            "\1\1\1\uffff\1\1\21\uffff\1\1\2\uffff\3\1\2\uffff\21\1\1\uffff"+
            "\4\1\2\12\1\1\1\uffff\1\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA44_eot = DFA.unpackEncodedString(DFA44_eotS);
    static final short[] DFA44_eof = DFA.unpackEncodedString(DFA44_eofS);
    static final char[] DFA44_min = DFA.unpackEncodedStringToUnsignedChars(DFA44_minS);
    static final char[] DFA44_max = DFA.unpackEncodedStringToUnsignedChars(DFA44_maxS);
    static final short[] DFA44_accept = DFA.unpackEncodedString(DFA44_acceptS);
    static final short[] DFA44_special = DFA.unpackEncodedString(DFA44_specialS);
    static final short[][] DFA44_transition;

    static {
        int numStates = DFA44_transitionS.length;
        DFA44_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA44_transition[i] = DFA.unpackEncodedString(DFA44_transitionS[i]);
        }
    }

    class DFA44 extends DFA {

        public DFA44(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 44;
            this.eot = DFA44_eot;
            this.eof = DFA44_eof;
            this.min = DFA44_min;
            this.max = DFA44_max;
            this.accept = DFA44_accept;
            this.special = DFA44_special;
            this.transition = DFA44_transition;
        }
        public String getDescription() {
            return "()+ loopback of 734:8: ( type_qualifier )+";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA44_10 = input.LA(1);

                         
                        int index44_10 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred76_PretC()) ) {s = 57;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index44_10);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 44, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA45_eotS =
        "\72\uffff";
    static final String DFA45_eofS =
        "\1\2\71\uffff";
    static final String DFA45_minS =
        "\1\25\1\0\70\uffff";
    static final String DFA45_maxS =
        "\1\113\1\0\70\uffff";
    static final String DFA45_acceptS =
        "\2\uffff\1\2\66\uffff\1\1";
    static final String DFA45_specialS =
        "\1\uffff\1\0\70\uffff}>";
    static final String[] DFA45_transitionS = {
            "\1\2\1\uffff\1\2\21\uffff\1\2\2\uffff\3\2\2\uffff\21\2\1\uffff"+
            "\7\2\1\uffff\1\1",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA45_eot = DFA.unpackEncodedString(DFA45_eotS);
    static final short[] DFA45_eof = DFA.unpackEncodedString(DFA45_eofS);
    static final char[] DFA45_min = DFA.unpackEncodedStringToUnsignedChars(DFA45_minS);
    static final char[] DFA45_max = DFA.unpackEncodedStringToUnsignedChars(DFA45_maxS);
    static final short[] DFA45_accept = DFA.unpackEncodedString(DFA45_acceptS);
    static final short[] DFA45_special = DFA.unpackEncodedString(DFA45_specialS);
    static final short[][] DFA45_transition;

    static {
        int numStates = DFA45_transitionS.length;
        DFA45_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA45_transition[i] = DFA.unpackEncodedString(DFA45_transitionS[i]);
        }
    }

    class DFA45 extends DFA {

        public DFA45(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 45;
            this.eot = DFA45_eot;
            this.eof = DFA45_eof;
            this.min = DFA45_min;
            this.max = DFA45_max;
            this.accept = DFA45_accept;
            this.special = DFA45_special;
            this.transition = DFA45_transition;
        }
        public String getDescription() {
            return "734:24: ( pointer )?";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA45_1 = input.LA(1);

                         
                        int index45_1 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred77_PretC()) ) {s = 57;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index45_1);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 45, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA48_eotS =
        "\23\uffff";
    static final String DFA48_eofS =
        "\23\uffff";
    static final String DFA48_minS =
        "\1\55\1\25\21\uffff";
    static final String DFA48_maxS =
        "\1\63\1\114\21\uffff";
    static final String DFA48_acceptS =
        "\2\uffff\1\2\1\uffff\1\1\16\uffff";
    static final String DFA48_specialS =
        "\23\uffff}>";
    static final String[] DFA48_transitionS = {
            "\1\1\5\uffff\1\2",
            "\1\4\34\uffff\1\4\2\uffff\14\4\2\uffff\2\4\1\uffff\3\4\3\uffff"+
            "\1\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA48_eot = DFA.unpackEncodedString(DFA48_eotS);
    static final short[] DFA48_eof = DFA.unpackEncodedString(DFA48_eofS);
    static final char[] DFA48_min = DFA.unpackEncodedStringToUnsignedChars(DFA48_minS);
    static final char[] DFA48_max = DFA.unpackEncodedStringToUnsignedChars(DFA48_maxS);
    static final short[] DFA48_accept = DFA.unpackEncodedString(DFA48_acceptS);
    static final short[] DFA48_special = DFA.unpackEncodedString(DFA48_specialS);
    static final short[][] DFA48_transition;

    static {
        int numStates = DFA48_transitionS.length;
        DFA48_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA48_transition[i] = DFA.unpackEncodedString(DFA48_transitionS[i]);
        }
    }

    class DFA48 extends DFA {

        public DFA48(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 48;
            this.eot = DFA48_eot;
            this.eof = DFA48_eof;
            this.min = DFA48_min;
            this.max = DFA48_max;
            this.accept = DFA48_accept;
            this.special = DFA48_special;
            this.transition = DFA48_transition;
        }
        public String getDescription() {
            return "()* loopback of 748:3: ( ',' p2= parameter_declaration )*";
        }
    }
    static final String DFA49_eotS =
        "\45\uffff";
    static final String DFA49_eofS =
        "\1\1\44\uffff";
    static final String DFA49_minS =
        "\1\25\4\uffff\1\0\1\uffff\1\25\31\uffff\3\0\1\uffff";
    static final String DFA49_maxS =
        "\1\113\4\uffff\1\0\1\uffff\1\113\31\uffff\3\0\1\uffff";
    static final String DFA49_acceptS =
        "\1\uffff\1\3\4\uffff\1\1\1\uffff\1\2\34\uffff";
    static final String DFA49_specialS =
        "\5\uffff\1\0\33\uffff\1\1\1\2\1\3\1\uffff}>";
    static final String[] DFA49_transitionS = {
            "\1\6\27\uffff\2\1\2\uffff\1\7\1\uffff\1\1\25\uffff\1\10\1\uffff"+
            "\1\5",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "\1\41\33\uffff\1\43\2\10\1\uffff\14\10\2\uffff\2\10\1\uffff"+
            "\4\10\1\uffff\1\42",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            ""
    };

    static final short[] DFA49_eot = DFA.unpackEncodedString(DFA49_eotS);
    static final short[] DFA49_eof = DFA.unpackEncodedString(DFA49_eofS);
    static final char[] DFA49_min = DFA.unpackEncodedStringToUnsignedChars(DFA49_minS);
    static final char[] DFA49_max = DFA.unpackEncodedStringToUnsignedChars(DFA49_maxS);
    static final short[] DFA49_accept = DFA.unpackEncodedString(DFA49_acceptS);
    static final short[] DFA49_special = DFA.unpackEncodedString(DFA49_specialS);
    static final short[][] DFA49_transition;

    static {
        int numStates = DFA49_transitionS.length;
        DFA49_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA49_transition[i] = DFA.unpackEncodedString(DFA49_transitionS[i]);
        }
    }

    class DFA49 extends DFA {

        public DFA49(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 49;
            this.eot = DFA49_eot;
            this.eof = DFA49_eof;
            this.min = DFA49_min;
            this.max = DFA49_max;
            this.accept = DFA49_accept;
            this.special = DFA49_special;
            this.transition = DFA49_transition;
        }
        public String getDescription() {
            return "()* loopback of 771:5: ( declarator | abstract_declarator )*";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA49_5 = input.LA(1);

                         
                        int index49_5 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred82_PretC()) ) {s = 6;}

                        else if ( (synpred83_PretC()) ) {s = 8;}

                         
                        input.seek(index49_5);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA49_33 = input.LA(1);

                         
                        int index49_33 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred82_PretC()) ) {s = 6;}

                        else if ( (synpred83_PretC()) ) {s = 8;}

                         
                        input.seek(index49_33);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA49_34 = input.LA(1);

                         
                        int index49_34 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred82_PretC()) ) {s = 6;}

                        else if ( (synpred83_PretC()) ) {s = 8;}

                         
                        input.seek(index49_34);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA49_35 = input.LA(1);

                         
                        int index49_35 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred82_PretC()) ) {s = 6;}

                        else if ( (synpred83_PretC()) ) {s = 8;}

                         
                        input.seek(index49_35);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 49, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA53_eotS =
        "\45\uffff";
    static final String DFA53_eofS =
        "\1\3\44\uffff";
    static final String DFA53_minS =
        "\3\25\6\uffff\33\0\1\uffff";
    static final String DFA53_maxS =
        "\2\113\1\130\6\uffff\33\0\1\uffff";
    static final String DFA53_acceptS =
        "\3\uffff\1\2\40\uffff\1\1";
    static final String DFA53_specialS =
        "\11\uffff\1\0\1\1\1\2\1\3\1\4\1\5\1\6\1\7\1\10\1\11\1\12\1\13\1"+
        "\14\1\15\1\16\1\17\1\20\1\21\1\22\1\23\1\24\1\25\1\26\1\27\1\30"+
        "\1\31\1\32\1\uffff}>";
    static final String[] DFA53_transitionS = {
            "\1\3\27\uffff\2\3\2\uffff\1\1\1\uffff\1\3\25\uffff\1\2\1\uffff"+
            "\1\3",
            "\1\30\33\uffff\1\32\1\14\1\11\1\uffff\4\12\1\15\1\16\1\17"+
            "\1\20\1\21\1\22\1\23\1\24\2\uffff\1\25\1\26\1\uffff\1\27\2\13"+
            "\1\33\1\uffff\1\31",
            "\1\36\1\37\1\uffff\5\37\24\uffff\1\35\30\uffff\1\34\1\42\1"+
            "\uffff\2\42\2\uffff\1\40\1\41\1\43\2\uffff\3\42",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            ""
    };

    static final short[] DFA53_eot = DFA.unpackEncodedString(DFA53_eotS);
    static final short[] DFA53_eof = DFA.unpackEncodedString(DFA53_eofS);
    static final char[] DFA53_min = DFA.unpackEncodedStringToUnsignedChars(DFA53_minS);
    static final char[] DFA53_max = DFA.unpackEncodedStringToUnsignedChars(DFA53_maxS);
    static final short[] DFA53_accept = DFA.unpackEncodedString(DFA53_acceptS);
    static final short[] DFA53_special = DFA.unpackEncodedString(DFA53_specialS);
    static final short[][] DFA53_transition;

    static {
        int numStates = DFA53_transitionS.length;
        DFA53_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA53_transition[i] = DFA.unpackEncodedString(DFA53_transitionS[i]);
        }
    }

    class DFA53 extends DFA {

        public DFA53(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 53;
            this.eot = DFA53_eot;
            this.eof = DFA53_eof;
            this.min = DFA53_min;
            this.max = DFA53_max;
            this.accept = DFA53_accept;
            this.special = DFA53_special;
            this.transition = DFA53_transition;
        }
        public String getDescription() {
            return "807:12: ( direct_abstract_declarator )?";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA53_9 = input.LA(1);

                         
                        int index53_9 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_9);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA53_10 = input.LA(1);

                         
                        int index53_10 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_10);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA53_11 = input.LA(1);

                         
                        int index53_11 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_11);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA53_12 = input.LA(1);

                         
                        int index53_12 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_12);
                        if ( s>=0 ) return s;
                        break;
                    case 4 : 
                        int LA53_13 = input.LA(1);

                         
                        int index53_13 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_13);
                        if ( s>=0 ) return s;
                        break;
                    case 5 : 
                        int LA53_14 = input.LA(1);

                         
                        int index53_14 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_14);
                        if ( s>=0 ) return s;
                        break;
                    case 6 : 
                        int LA53_15 = input.LA(1);

                         
                        int index53_15 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_15);
                        if ( s>=0 ) return s;
                        break;
                    case 7 : 
                        int LA53_16 = input.LA(1);

                         
                        int index53_16 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_16);
                        if ( s>=0 ) return s;
                        break;
                    case 8 : 
                        int LA53_17 = input.LA(1);

                         
                        int index53_17 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_17);
                        if ( s>=0 ) return s;
                        break;
                    case 9 : 
                        int LA53_18 = input.LA(1);

                         
                        int index53_18 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_18);
                        if ( s>=0 ) return s;
                        break;
                    case 10 : 
                        int LA53_19 = input.LA(1);

                         
                        int index53_19 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_19);
                        if ( s>=0 ) return s;
                        break;
                    case 11 : 
                        int LA53_20 = input.LA(1);

                         
                        int index53_20 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_20);
                        if ( s>=0 ) return s;
                        break;
                    case 12 : 
                        int LA53_21 = input.LA(1);

                         
                        int index53_21 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_21);
                        if ( s>=0 ) return s;
                        break;
                    case 13 : 
                        int LA53_22 = input.LA(1);

                         
                        int index53_22 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_22);
                        if ( s>=0 ) return s;
                        break;
                    case 14 : 
                        int LA53_23 = input.LA(1);

                         
                        int index53_23 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_23);
                        if ( s>=0 ) return s;
                        break;
                    case 15 : 
                        int LA53_24 = input.LA(1);

                         
                        int index53_24 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_24);
                        if ( s>=0 ) return s;
                        break;
                    case 16 : 
                        int LA53_25 = input.LA(1);

                         
                        int index53_25 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_25);
                        if ( s>=0 ) return s;
                        break;
                    case 17 : 
                        int LA53_26 = input.LA(1);

                         
                        int index53_26 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_26);
                        if ( s>=0 ) return s;
                        break;
                    case 18 : 
                        int LA53_27 = input.LA(1);

                         
                        int index53_27 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_27);
                        if ( s>=0 ) return s;
                        break;
                    case 19 : 
                        int LA53_28 = input.LA(1);

                         
                        int index53_28 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_28);
                        if ( s>=0 ) return s;
                        break;
                    case 20 : 
                        int LA53_29 = input.LA(1);

                         
                        int index53_29 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_29);
                        if ( s>=0 ) return s;
                        break;
                    case 21 : 
                        int LA53_30 = input.LA(1);

                         
                        int index53_30 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_30);
                        if ( s>=0 ) return s;
                        break;
                    case 22 : 
                        int LA53_31 = input.LA(1);

                         
                        int index53_31 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_31);
                        if ( s>=0 ) return s;
                        break;
                    case 23 : 
                        int LA53_32 = input.LA(1);

                         
                        int index53_32 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_32);
                        if ( s>=0 ) return s;
                        break;
                    case 24 : 
                        int LA53_33 = input.LA(1);

                         
                        int index53_33 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_33);
                        if ( s>=0 ) return s;
                        break;
                    case 25 : 
                        int LA53_34 = input.LA(1);

                         
                        int index53_34 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_34);
                        if ( s>=0 ) return s;
                        break;
                    case 26 : 
                        int LA53_35 = input.LA(1);

                         
                        int index53_35 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred87_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 3;}

                         
                        input.seek(index53_35);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 53, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA55_eotS =
        "\26\uffff";
    static final String DFA55_eofS =
        "\26\uffff";
    static final String DFA55_minS =
        "\1\61\1\25\24\uffff";
    static final String DFA55_maxS =
        "\1\111\1\113\24\uffff";
    static final String DFA55_acceptS =
        "\2\uffff\1\2\1\uffff\1\1\21\uffff";
    static final String DFA55_specialS =
        "\26\uffff}>";
    static final String[] DFA55_transitionS = {
            "\1\1\27\uffff\1\2",
            "\1\2\33\uffff\1\4\2\2\1\uffff\14\2\2\uffff\2\2\1\uffff\3\2"+
            "\1\4\1\uffff\1\4",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA55_eot = DFA.unpackEncodedString(DFA55_eotS);
    static final short[] DFA55_eof = DFA.unpackEncodedString(DFA55_eofS);
    static final char[] DFA55_min = DFA.unpackEncodedStringToUnsignedChars(DFA55_minS);
    static final char[] DFA55_max = DFA.unpackEncodedStringToUnsignedChars(DFA55_maxS);
    static final short[] DFA55_accept = DFA.unpackEncodedString(DFA55_acceptS);
    static final short[] DFA55_special = DFA.unpackEncodedString(DFA55_specialS);
    static final short[][] DFA55_transition;

    static {
        int numStates = DFA55_transitionS.length;
        DFA55_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA55_transition[i] = DFA.unpackEncodedString(DFA55_transitionS[i]);
        }
    }

    class DFA55 extends DFA {

        public DFA55(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 55;
            this.eot = DFA55_eot;
            this.eof = DFA55_eof;
            this.min = DFA55_min;
            this.max = DFA55_max;
            this.accept = DFA55_accept;
            this.special = DFA55_special;
            this.transition = DFA55_transition;
        }
        public String getDescription() {
            return "812:4: ( '(' abstract_declarator ')' | abstract_declarator_suffix )";
        }
    }
    static final String DFA56_eotS =
        "\45\uffff";
    static final String DFA56_eofS =
        "\1\1\44\uffff";
    static final String DFA56_minS =
        "\1\25\6\uffff\2\25\20\0\3\uffff\10\0\1\uffff";
    static final String DFA56_maxS =
        "\1\113\6\uffff\1\113\1\130\20\0\3\uffff\10\0\1\uffff";
    static final String DFA56_acceptS =
        "\1\uffff\1\2\42\uffff\1\1";
    static final String DFA56_specialS =
        "\11\uffff\1\0\1\1\1\2\1\3\1\4\1\5\1\6\1\7\1\10\1\11\1\12\1\13\1"+
        "\14\1\15\1\16\1\17\3\uffff\1\20\1\21\1\22\1\23\1\24\1\25\1\26\1"+
        "\27\1\uffff}>";
    static final String[] DFA56_transitionS = {
            "\1\1\27\uffff\2\1\2\uffff\1\7\1\uffff\1\1\25\uffff\1\10\1\uffff"+
            "\1\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\30\33\uffff\1\1\1\14\1\11\1\uffff\4\12\1\15\1\16\1\17\1"+
            "\20\1\21\1\22\1\23\1\24\2\uffff\1\25\1\26\1\uffff\1\27\2\13"+
            "\1\1\1\uffff\1\1",
            "\1\36\1\37\1\uffff\5\37\24\uffff\1\35\30\uffff\1\34\1\42\1"+
            "\uffff\2\42\2\uffff\1\40\1\41\1\43\2\uffff\3\42",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            ""
    };

    static final short[] DFA56_eot = DFA.unpackEncodedString(DFA56_eotS);
    static final short[] DFA56_eof = DFA.unpackEncodedString(DFA56_eofS);
    static final char[] DFA56_min = DFA.unpackEncodedStringToUnsignedChars(DFA56_minS);
    static final char[] DFA56_max = DFA.unpackEncodedStringToUnsignedChars(DFA56_maxS);
    static final short[] DFA56_accept = DFA.unpackEncodedString(DFA56_acceptS);
    static final short[] DFA56_special = DFA.unpackEncodedString(DFA56_specialS);
    static final short[][] DFA56_transition;

    static {
        int numStates = DFA56_transitionS.length;
        DFA56_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA56_transition[i] = DFA.unpackEncodedString(DFA56_transitionS[i]);
        }
    }

    class DFA56 extends DFA {

        public DFA56(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 56;
            this.eot = DFA56_eot;
            this.eof = DFA56_eof;
            this.min = DFA56_min;
            this.max = DFA56_max;
            this.accept = DFA56_accept;
            this.special = DFA56_special;
            this.transition = DFA56_transition;
        }
        public String getDescription() {
            return "()* loopback of 812:65: ( abstract_declarator_suffix )*";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA56_9 = input.LA(1);

                         
                        int index56_9 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_9);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA56_10 = input.LA(1);

                         
                        int index56_10 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_10);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA56_11 = input.LA(1);

                         
                        int index56_11 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_11);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA56_12 = input.LA(1);

                         
                        int index56_12 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_12);
                        if ( s>=0 ) return s;
                        break;
                    case 4 : 
                        int LA56_13 = input.LA(1);

                         
                        int index56_13 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_13);
                        if ( s>=0 ) return s;
                        break;
                    case 5 : 
                        int LA56_14 = input.LA(1);

                         
                        int index56_14 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_14);
                        if ( s>=0 ) return s;
                        break;
                    case 6 : 
                        int LA56_15 = input.LA(1);

                         
                        int index56_15 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_15);
                        if ( s>=0 ) return s;
                        break;
                    case 7 : 
                        int LA56_16 = input.LA(1);

                         
                        int index56_16 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_16);
                        if ( s>=0 ) return s;
                        break;
                    case 8 : 
                        int LA56_17 = input.LA(1);

                         
                        int index56_17 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_17);
                        if ( s>=0 ) return s;
                        break;
                    case 9 : 
                        int LA56_18 = input.LA(1);

                         
                        int index56_18 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_18);
                        if ( s>=0 ) return s;
                        break;
                    case 10 : 
                        int LA56_19 = input.LA(1);

                         
                        int index56_19 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_19);
                        if ( s>=0 ) return s;
                        break;
                    case 11 : 
                        int LA56_20 = input.LA(1);

                         
                        int index56_20 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_20);
                        if ( s>=0 ) return s;
                        break;
                    case 12 : 
                        int LA56_21 = input.LA(1);

                         
                        int index56_21 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_21);
                        if ( s>=0 ) return s;
                        break;
                    case 13 : 
                        int LA56_22 = input.LA(1);

                         
                        int index56_22 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_22);
                        if ( s>=0 ) return s;
                        break;
                    case 14 : 
                        int LA56_23 = input.LA(1);

                         
                        int index56_23 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_23);
                        if ( s>=0 ) return s;
                        break;
                    case 15 : 
                        int LA56_24 = input.LA(1);

                         
                        int index56_24 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_24);
                        if ( s>=0 ) return s;
                        break;
                    case 16 : 
                        int LA56_28 = input.LA(1);

                         
                        int index56_28 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_28);
                        if ( s>=0 ) return s;
                        break;
                    case 17 : 
                        int LA56_29 = input.LA(1);

                         
                        int index56_29 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_29);
                        if ( s>=0 ) return s;
                        break;
                    case 18 : 
                        int LA56_30 = input.LA(1);

                         
                        int index56_30 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_30);
                        if ( s>=0 ) return s;
                        break;
                    case 19 : 
                        int LA56_31 = input.LA(1);

                         
                        int index56_31 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_31);
                        if ( s>=0 ) return s;
                        break;
                    case 20 : 
                        int LA56_32 = input.LA(1);

                         
                        int index56_32 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_32);
                        if ( s>=0 ) return s;
                        break;
                    case 21 : 
                        int LA56_33 = input.LA(1);

                         
                        int index56_33 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_33);
                        if ( s>=0 ) return s;
                        break;
                    case 22 : 
                        int LA56_34 = input.LA(1);

                         
                        int index56_34 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_34);
                        if ( s>=0 ) return s;
                        break;
                    case 23 : 
                        int LA56_35 = input.LA(1);

                         
                        int index56_35 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred90_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index56_35);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 56, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA57_eotS =
        "\33\uffff";
    static final String DFA57_eofS =
        "\33\uffff";
    static final String DFA57_minS =
        "\1\61\2\25\30\uffff";
    static final String DFA57_maxS =
        "\1\111\1\130\1\110\30\uffff";
    static final String DFA57_acceptS =
        "\3\uffff\1\1\1\2\6\uffff\1\3\1\4\16\uffff";
    static final String DFA57_specialS =
        "\33\uffff}>";
    static final String[] DFA57_transitionS = {
            "\1\2\27\uffff\1\1",
            "\2\4\1\uffff\5\4\24\uffff\1\4\30\uffff\1\3\1\4\1\uffff\2\4"+
            "\2\uffff\3\4\2\uffff\3\4",
            "\1\14\34\uffff\1\14\1\13\1\uffff\14\14\2\uffff\2\14\1\uffff"+
            "\3\14",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA57_eot = DFA.unpackEncodedString(DFA57_eotS);
    static final short[] DFA57_eof = DFA.unpackEncodedString(DFA57_eofS);
    static final char[] DFA57_min = DFA.unpackEncodedStringToUnsignedChars(DFA57_minS);
    static final char[] DFA57_max = DFA.unpackEncodedStringToUnsignedChars(DFA57_maxS);
    static final short[] DFA57_accept = DFA.unpackEncodedString(DFA57_acceptS);
    static final short[] DFA57_special = DFA.unpackEncodedString(DFA57_specialS);
    static final short[][] DFA57_transition;

    static {
        int numStates = DFA57_transitionS.length;
        DFA57_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA57_transition[i] = DFA.unpackEncodedString(DFA57_transitionS[i]);
        }
    }

    class DFA57 extends DFA {

        public DFA57(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 57;
            this.eot = DFA57_eot;
            this.eof = DFA57_eof;
            this.min = DFA57_min;
            this.max = DFA57_max;
            this.accept = DFA57_accept;
            this.special = DFA57_special;
            this.transition = DFA57_transition;
        }
        public String getDescription() {
            return "815:1: abstract_declarator_suffix : ( '[' ']' | '[' constant_expression ']' | '(' ')' | '(' parameter_type_list ')' );";
        }
    }
    static final String DFA60_eotS =
        "\14\uffff";
    static final String DFA60_eofS =
        "\14\uffff";
    static final String DFA60_minS =
        "\1\55\1\25\12\uffff";
    static final String DFA60_maxS =
        "\1\102\1\130\12\uffff";
    static final String DFA60_acceptS =
        "\2\uffff\1\2\1\1\10\uffff";
    static final String DFA60_specialS =
        "\14\uffff}>";
    static final String[] DFA60_transitionS = {
            "\1\1\24\uffff\1\2",
            "\2\3\1\uffff\5\3\24\uffff\1\3\17\uffff\1\3\1\2\10\uffff\1"+
            "\3\1\uffff\2\3\2\uffff\3\3\2\uffff\3\3",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA60_eot = DFA.unpackEncodedString(DFA60_eotS);
    static final short[] DFA60_eof = DFA.unpackEncodedString(DFA60_eofS);
    static final char[] DFA60_min = DFA.unpackEncodedStringToUnsignedChars(DFA60_minS);
    static final char[] DFA60_max = DFA.unpackEncodedStringToUnsignedChars(DFA60_maxS);
    static final short[] DFA60_accept = DFA.unpackEncodedString(DFA60_acceptS);
    static final short[] DFA60_special = DFA.unpackEncodedString(DFA60_specialS);
    static final short[][] DFA60_transition;

    static {
        int numStates = DFA60_transitionS.length;
        DFA60_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA60_transition[i] = DFA.unpackEncodedString(DFA60_transitionS[i]);
        }
    }

    class DFA60 extends DFA {

        public DFA60(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 60;
            this.eot = DFA60_eot;
            this.eof = DFA60_eof;
            this.min = DFA60_min;
            this.max = DFA60_max;
            this.accept = DFA60_accept;
            this.special = DFA60_special;
            this.transition = DFA60_transition;
        }
        public String getDescription() {
            return "()* loopback of 828:16: ( ',' initializer )*";
        }
    }
    static final String DFA62_eotS =
        "\24\uffff";
    static final String DFA62_eofS =
        "\1\1\23\uffff";
    static final String DFA62_minS =
        "\1\51\23\uffff";
    static final String DFA62_maxS =
        "\1\157\23\uffff";
    static final String DFA62_acceptS =
        "\1\uffff\1\3\20\uffff\1\1\1\2";
    static final String DFA62_specialS =
        "\24\uffff}>";
    static final String[] DFA62_transitionS = {
            "\1\1\3\uffff\2\1\4\uffff\1\1\16\uffff\1\1\2\uffff\1\1\4\uffff"+
            "\1\1\2\uffff\1\22\1\23\7\uffff\1\1\14\uffff\15\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA62_eot = DFA.unpackEncodedString(DFA62_eotS);
    static final short[] DFA62_eof = DFA.unpackEncodedString(DFA62_eofS);
    static final char[] DFA62_min = DFA.unpackEncodedStringToUnsignedChars(DFA62_minS);
    static final char[] DFA62_max = DFA.unpackEncodedStringToUnsignedChars(DFA62_maxS);
    static final short[] DFA62_accept = DFA.unpackEncodedString(DFA62_acceptS);
    static final short[] DFA62_special = DFA.unpackEncodedString(DFA62_specialS);
    static final short[][] DFA62_transition;

    static {
        int numStates = DFA62_transitionS.length;
        DFA62_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA62_transition[i] = DFA.unpackEncodedString(DFA62_transitionS[i]);
        }
    }

    class DFA62 extends DFA {

        public DFA62(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 62;
            this.eot = DFA62_eot;
            this.eof = DFA62_eof;
            this.min = DFA62_min;
            this.max = DFA62_max;
            this.accept = DFA62_accept;
            this.special = DFA62_special;
            this.transition = DFA62_transition;
        }
        public String getDescription() {
            return "()* loopback of 838:32: ( '+' multiplicative_expression | '-' multiplicative_expression )*";
        }
    }
    static final String DFA63_eotS =
        "\27\uffff";
    static final String DFA63_eofS =
        "\1\1\26\uffff";
    static final String DFA63_minS =
        "\1\51\26\uffff";
    static final String DFA63_maxS =
        "\1\157\26\uffff";
    static final String DFA63_acceptS =
        "\1\uffff\1\4\22\uffff\1\1\1\2\1\3";
    static final String DFA63_specialS =
        "\27\uffff}>";
    static final String[] DFA63_transitionS = {
            "\1\1\3\uffff\2\1\4\uffff\1\1\16\uffff\1\1\2\uffff\1\1\4\uffff"+
            "\1\1\1\24\1\uffff\2\1\1\25\1\26\5\uffff\1\1\14\uffff\15\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA63_eot = DFA.unpackEncodedString(DFA63_eotS);
    static final short[] DFA63_eof = DFA.unpackEncodedString(DFA63_eofS);
    static final char[] DFA63_min = DFA.unpackEncodedStringToUnsignedChars(DFA63_minS);
    static final char[] DFA63_max = DFA.unpackEncodedStringToUnsignedChars(DFA63_maxS);
    static final short[] DFA63_accept = DFA.unpackEncodedString(DFA63_acceptS);
    static final short[] DFA63_special = DFA.unpackEncodedString(DFA63_specialS);
    static final short[][] DFA63_transition;

    static {
        int numStates = DFA63_transitionS.length;
        DFA63_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA63_transition[i] = DFA.unpackEncodedString(DFA63_transitionS[i]);
        }
    }

    class DFA63 extends DFA {

        public DFA63(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 63;
            this.eot = DFA63_eot;
            this.eof = DFA63_eof;
            this.min = DFA63_min;
            this.max = DFA63_max;
            this.accept = DFA63_accept;
            this.special = DFA63_special;
            this.transition = DFA63_transition;
        }
        public String getDescription() {
            return "()* loopback of 842:22: ( '*' cast_expression | '/' cast_expression | '%' cast_expression )*";
        }
    }
    static final String DFA64_eotS =
        "\34\uffff";
    static final String DFA64_eofS =
        "\34\uffff";
    static final String DFA64_minS =
        "\2\25\23\uffff\1\0\6\uffff";
    static final String DFA64_maxS =
        "\2\130\23\uffff\1\0\6\uffff";
    static final String DFA64_acceptS =
        "\2\uffff\1\2\5\uffff\1\1\23\uffff";
    static final String DFA64_specialS =
        "\25\uffff\1\0\6\uffff}>";
    static final String[] DFA64_transitionS = {
            "\2\2\1\uffff\5\2\24\uffff\1\1\31\uffff\1\2\1\uffff\2\2\2\uffff"+
            "\3\2\2\uffff\3\2",
            "\1\25\1\2\1\uffff\5\2\24\uffff\1\2\1\10\6\uffff\10\10\2\uffff"+
            "\2\10\1\uffff\3\10\2\uffff\1\2\1\uffff\2\2\2\uffff\3\2\2\uffff"+
            "\3\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA64_eot = DFA.unpackEncodedString(DFA64_eotS);
    static final short[] DFA64_eof = DFA.unpackEncodedString(DFA64_eofS);
    static final char[] DFA64_min = DFA.unpackEncodedStringToUnsignedChars(DFA64_minS);
    static final char[] DFA64_max = DFA.unpackEncodedStringToUnsignedChars(DFA64_maxS);
    static final short[] DFA64_accept = DFA.unpackEncodedString(DFA64_acceptS);
    static final short[] DFA64_special = DFA.unpackEncodedString(DFA64_specialS);
    static final short[][] DFA64_transition;

    static {
        int numStates = DFA64_transitionS.length;
        DFA64_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA64_transition[i] = DFA.unpackEncodedString(DFA64_transitionS[i]);
        }
    }

    class DFA64 extends DFA {

        public DFA64(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 64;
            this.eot = DFA64_eot;
            this.eof = DFA64_eof;
            this.min = DFA64_min;
            this.max = DFA64_max;
            this.accept = DFA64_accept;
            this.special = DFA64_special;
            this.transition = DFA64_transition;
        }
        public String getDescription() {
            return "845:1: cast_expression : ( '(' type_name ')' cast_expression | unary_expression );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA64_21 = input.LA(1);

                         
                        int index64_21 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred103_PretC()) ) {s = 8;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index64_21);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 64, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA65_eotS =
        "\20\uffff";
    static final String DFA65_eofS =
        "\20\uffff";
    static final String DFA65_minS =
        "\1\25\6\uffff\1\25\1\0\7\uffff";
    static final String DFA65_maxS =
        "\1\130\6\uffff\1\130\1\0\7\uffff";
    static final String DFA65_acceptS =
        "\1\uffff\1\1\2\uffff\1\2\1\3\1\4\2\uffff\1\5\5\uffff\1\6";
    static final String DFA65_specialS =
        "\10\uffff\1\0\7\uffff}>";
    static final String[] DFA65_transitionS = {
            "\2\1\1\uffff\5\1\24\uffff\1\1\31\uffff\1\6\1\uffff\2\6\2\uffff"+
            "\1\4\1\5\1\7\2\uffff\3\6",
            "",
            "",
            "",
            "",
            "",
            "",
            "\2\11\1\uffff\5\11\24\uffff\1\10\31\uffff\1\11\1\uffff\2\11"+
            "\2\uffff\3\11\2\uffff\3\11",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA65_eot = DFA.unpackEncodedString(DFA65_eotS);
    static final short[] DFA65_eof = DFA.unpackEncodedString(DFA65_eofS);
    static final char[] DFA65_min = DFA.unpackEncodedStringToUnsignedChars(DFA65_minS);
    static final char[] DFA65_max = DFA.unpackEncodedStringToUnsignedChars(DFA65_maxS);
    static final short[] DFA65_accept = DFA.unpackEncodedString(DFA65_acceptS);
    static final short[] DFA65_special = DFA.unpackEncodedString(DFA65_specialS);
    static final short[][] DFA65_transition;

    static {
        int numStates = DFA65_transitionS.length;
        DFA65_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA65_transition[i] = DFA.unpackEncodedString(DFA65_transitionS[i]);
        }
    }

    class DFA65 extends DFA {

        public DFA65(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 65;
            this.eot = DFA65_eot;
            this.eof = DFA65_eof;
            this.min = DFA65_min;
            this.max = DFA65_max;
            this.accept = DFA65_accept;
            this.special = DFA65_special;
            this.transition = DFA65_transition;
        }
        public String getDescription() {
            return "850:1: unary_expression : ( postfix_expression | '++' unary_expression | '--' unary_expression | unary_operator cast_expression | 'sizeof' unary_expression | 'sizeof' '(' type_name ')' );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA65_8 = input.LA(1);

                         
                        int index65_8 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred108_PretC()) ) {s = 9;}

                        else if ( (true) ) {s = 15;}

                         
                        input.seek(index65_8);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 65, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA66_eotS =
        "\46\uffff";
    static final String DFA66_eofS =
        "\1\1\45\uffff";
    static final String DFA66_minS =
        "\1\51\30\uffff\1\25\14\uffff";
    static final String DFA66_maxS =
        "\1\157\30\uffff\1\130\14\uffff";
    static final String DFA66_acceptS =
        "\1\uffff\1\10\26\uffff\1\1\1\uffff\1\4\1\5\1\6\1\7\1\2\1\3\6\uffff";
    static final String DFA66_specialS =
        "\46\uffff}>";
    static final String[] DFA66_transitionS = {
            "\1\1\2\uffff\3\1\2\uffff\1\31\1\uffff\1\1\16\uffff\1\1\2\uffff"+
            "\1\1\3\uffff\1\30\2\1\1\uffff\4\1\1\34\1\35\1\uffff\1\32\1\33"+
            "\1\1\2\uffff\27\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\2\37\1\uffff\5\37\24\uffff\1\37\1\uffff\1\36\27\uffff\1\37"+
            "\1\uffff\2\37\2\uffff\3\37\2\uffff\3\37",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA66_eot = DFA.unpackEncodedString(DFA66_eotS);
    static final short[] DFA66_eof = DFA.unpackEncodedString(DFA66_eofS);
    static final char[] DFA66_min = DFA.unpackEncodedStringToUnsignedChars(DFA66_minS);
    static final char[] DFA66_max = DFA.unpackEncodedStringToUnsignedChars(DFA66_maxS);
    static final short[] DFA66_accept = DFA.unpackEncodedString(DFA66_acceptS);
    static final short[] DFA66_special = DFA.unpackEncodedString(DFA66_specialS);
    static final short[][] DFA66_transition;

    static {
        int numStates = DFA66_transitionS.length;
        DFA66_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA66_transition[i] = DFA.unpackEncodedString(DFA66_transitionS[i]);
        }
    }

    class DFA66 extends DFA {

        public DFA66(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 66;
            this.eot = DFA66_eot;
            this.eof = DFA66_eof;
            this.min = DFA66_min;
            this.max = DFA66_max;
            this.accept = DFA66_accept;
            this.special = DFA66_special;
            this.transition = DFA66_transition;
        }
        public String getDescription() {
            return "()* loopback of 867:9: ( '[' expression ']' | '(' ')' | '(' argument_expression_list ')' | '.' i1= IDENTIFIER | '->' i2= IDENTIFIER | '++' | '--' )*";
        }
    }
    static final String DFA69_eotS =
        "\162\uffff";
    static final String DFA69_eofS =
        "\1\uffff\2\16\157\uffff";
    static final String DFA69_minS =
        "\1\25\2\51\5\25\6\0\27\uffff\6\0\27\uffff\7\0\15\uffff\34\0";
    static final String DFA69_maxS =
        "\1\130\2\157\5\130\6\0\27\uffff\6\0\27\uffff\7\0\15\uffff\34\0";
    static final String DFA69_acceptS =
        "\16\uffff\1\2\25\uffff\1\1\115\uffff";
    static final String DFA69_specialS =
        "\10\uffff\1\0\1\1\1\2\1\3\1\4\1\5\27\uffff\1\6\1\7\1\10\1\11\1"+
        "\12\1\13\27\uffff\1\14\1\15\1\16\1\17\1\20\1\21\1\22\15\uffff\1"+
        "\23\1\24\1\25\1\26\1\27\1\30\1\31\1\32\1\33\1\34\1\35\1\36\1\37"+
        "\1\40\1\41\1\42\1\43\1\44\1\45\1\46\1\47\1\50\1\51\1\52\1\53\1\54"+
        "\1\55\1\56}>";
    static final String[] DFA69_transitionS = {
            "\1\1\1\2\1\uffff\5\2\24\uffff\1\3\31\uffff\1\6\1\uffff\2\6"+
            "\2\uffff\1\4\1\5\1\7\2\uffff\3\6",
            "\1\16\2\uffff\1\44\2\16\2\uffff\1\11\1\uffff\1\16\16\uffff"+
            "\1\16\2\uffff\1\16\3\uffff\1\10\2\16\1\uffff\4\16\1\14\1\15"+
            "\1\uffff\1\12\1\13\1\16\2\uffff\12\44\15\16",
            "\1\16\2\uffff\1\44\2\16\2\uffff\1\46\1\uffff\1\16\16\uffff"+
            "\1\16\2\uffff\1\16\3\uffff\1\45\2\16\1\uffff\4\16\1\51\1\52"+
            "\1\uffff\1\47\1\50\1\16\2\uffff\12\44\15\16",
            "\1\102\1\103\1\uffff\5\103\24\uffff\1\104\1\16\6\uffff\10"+
            "\16\2\uffff\2\16\1\uffff\3\16\2\uffff\1\107\1\uffff\2\107\2"+
            "\uffff\1\105\1\106\1\110\2\uffff\3\107",
            "\1\126\1\127\1\uffff\5\127\24\uffff\1\130\31\uffff\1\133\1"+
            "\uffff\2\133\2\uffff\1\131\1\132\1\134\2\uffff\3\133",
            "\1\135\1\136\1\uffff\5\136\24\uffff\1\137\31\uffff\1\142\1"+
            "\uffff\2\142\2\uffff\1\140\1\141\1\143\2\uffff\3\142",
            "\1\145\1\146\1\uffff\5\146\24\uffff\1\144\31\uffff\1\151\1"+
            "\uffff\2\151\2\uffff\1\147\1\150\1\152\2\uffff\3\151",
            "\1\154\1\155\1\uffff\5\155\24\uffff\1\153\31\uffff\1\160\1"+
            "\uffff\2\160\2\uffff\1\156\1\157\1\161\2\uffff\3\160",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff"
    };

    static final short[] DFA69_eot = DFA.unpackEncodedString(DFA69_eotS);
    static final short[] DFA69_eof = DFA.unpackEncodedString(DFA69_eofS);
    static final char[] DFA69_min = DFA.unpackEncodedStringToUnsignedChars(DFA69_minS);
    static final char[] DFA69_max = DFA.unpackEncodedStringToUnsignedChars(DFA69_maxS);
    static final short[] DFA69_accept = DFA.unpackEncodedString(DFA69_acceptS);
    static final short[] DFA69_special = DFA.unpackEncodedString(DFA69_specialS);
    static final short[][] DFA69_transition;

    static {
        int numStates = DFA69_transitionS.length;
        DFA69_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA69_transition[i] = DFA.unpackEncodedString(DFA69_transitionS[i]);
        }
    }

    class DFA69 extends DFA {

        public DFA69(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 69;
            this.eot = DFA69_eot;
            this.eof = DFA69_eof;
            this.min = DFA69_min;
            this.max = DFA69_max;
            this.accept = DFA69_accept;
            this.special = DFA69_special;
            this.transition = DFA69_transition;
        }
        public String getDescription() {
            return "911:1: assignment_expression : ( lvalue assignment_operator assignment_expression | constant_expression );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA69_8 = input.LA(1);

                         
                        int index69_8 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_8);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA69_9 = input.LA(1);

                         
                        int index69_9 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_9);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA69_10 = input.LA(1);

                         
                        int index69_10 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_10);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA69_11 = input.LA(1);

                         
                        int index69_11 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_11);
                        if ( s>=0 ) return s;
                        break;
                    case 4 : 
                        int LA69_12 = input.LA(1);

                         
                        int index69_12 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_12);
                        if ( s>=0 ) return s;
                        break;
                    case 5 : 
                        int LA69_13 = input.LA(1);

                         
                        int index69_13 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_13);
                        if ( s>=0 ) return s;
                        break;
                    case 6 : 
                        int LA69_37 = input.LA(1);

                         
                        int index69_37 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_37);
                        if ( s>=0 ) return s;
                        break;
                    case 7 : 
                        int LA69_38 = input.LA(1);

                         
                        int index69_38 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_38);
                        if ( s>=0 ) return s;
                        break;
                    case 8 : 
                        int LA69_39 = input.LA(1);

                         
                        int index69_39 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_39);
                        if ( s>=0 ) return s;
                        break;
                    case 9 : 
                        int LA69_40 = input.LA(1);

                         
                        int index69_40 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_40);
                        if ( s>=0 ) return s;
                        break;
                    case 10 : 
                        int LA69_41 = input.LA(1);

                         
                        int index69_41 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_41);
                        if ( s>=0 ) return s;
                        break;
                    case 11 : 
                        int LA69_42 = input.LA(1);

                         
                        int index69_42 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_42);
                        if ( s>=0 ) return s;
                        break;
                    case 12 : 
                        int LA69_66 = input.LA(1);

                         
                        int index69_66 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_66);
                        if ( s>=0 ) return s;
                        break;
                    case 13 : 
                        int LA69_67 = input.LA(1);

                         
                        int index69_67 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_67);
                        if ( s>=0 ) return s;
                        break;
                    case 14 : 
                        int LA69_68 = input.LA(1);

                         
                        int index69_68 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_68);
                        if ( s>=0 ) return s;
                        break;
                    case 15 : 
                        int LA69_69 = input.LA(1);

                         
                        int index69_69 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_69);
                        if ( s>=0 ) return s;
                        break;
                    case 16 : 
                        int LA69_70 = input.LA(1);

                         
                        int index69_70 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_70);
                        if ( s>=0 ) return s;
                        break;
                    case 17 : 
                        int LA69_71 = input.LA(1);

                         
                        int index69_71 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_71);
                        if ( s>=0 ) return s;
                        break;
                    case 18 : 
                        int LA69_72 = input.LA(1);

                         
                        int index69_72 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_72);
                        if ( s>=0 ) return s;
                        break;
                    case 19 : 
                        int LA69_86 = input.LA(1);

                         
                        int index69_86 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_86);
                        if ( s>=0 ) return s;
                        break;
                    case 20 : 
                        int LA69_87 = input.LA(1);

                         
                        int index69_87 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_87);
                        if ( s>=0 ) return s;
                        break;
                    case 21 : 
                        int LA69_88 = input.LA(1);

                         
                        int index69_88 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_88);
                        if ( s>=0 ) return s;
                        break;
                    case 22 : 
                        int LA69_89 = input.LA(1);

                         
                        int index69_89 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_89);
                        if ( s>=0 ) return s;
                        break;
                    case 23 : 
                        int LA69_90 = input.LA(1);

                         
                        int index69_90 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_90);
                        if ( s>=0 ) return s;
                        break;
                    case 24 : 
                        int LA69_91 = input.LA(1);

                         
                        int index69_91 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_91);
                        if ( s>=0 ) return s;
                        break;
                    case 25 : 
                        int LA69_92 = input.LA(1);

                         
                        int index69_92 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_92);
                        if ( s>=0 ) return s;
                        break;
                    case 26 : 
                        int LA69_93 = input.LA(1);

                         
                        int index69_93 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_93);
                        if ( s>=0 ) return s;
                        break;
                    case 27 : 
                        int LA69_94 = input.LA(1);

                         
                        int index69_94 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_94);
                        if ( s>=0 ) return s;
                        break;
                    case 28 : 
                        int LA69_95 = input.LA(1);

                         
                        int index69_95 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_95);
                        if ( s>=0 ) return s;
                        break;
                    case 29 : 
                        int LA69_96 = input.LA(1);

                         
                        int index69_96 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_96);
                        if ( s>=0 ) return s;
                        break;
                    case 30 : 
                        int LA69_97 = input.LA(1);

                         
                        int index69_97 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_97);
                        if ( s>=0 ) return s;
                        break;
                    case 31 : 
                        int LA69_98 = input.LA(1);

                         
                        int index69_98 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_98);
                        if ( s>=0 ) return s;
                        break;
                    case 32 : 
                        int LA69_99 = input.LA(1);

                         
                        int index69_99 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_99);
                        if ( s>=0 ) return s;
                        break;
                    case 33 : 
                        int LA69_100 = input.LA(1);

                         
                        int index69_100 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_100);
                        if ( s>=0 ) return s;
                        break;
                    case 34 : 
                        int LA69_101 = input.LA(1);

                         
                        int index69_101 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_101);
                        if ( s>=0 ) return s;
                        break;
                    case 35 : 
                        int LA69_102 = input.LA(1);

                         
                        int index69_102 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_102);
                        if ( s>=0 ) return s;
                        break;
                    case 36 : 
                        int LA69_103 = input.LA(1);

                         
                        int index69_103 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_103);
                        if ( s>=0 ) return s;
                        break;
                    case 37 : 
                        int LA69_104 = input.LA(1);

                         
                        int index69_104 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_104);
                        if ( s>=0 ) return s;
                        break;
                    case 38 : 
                        int LA69_105 = input.LA(1);

                         
                        int index69_105 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_105);
                        if ( s>=0 ) return s;
                        break;
                    case 39 : 
                        int LA69_106 = input.LA(1);

                         
                        int index69_106 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_106);
                        if ( s>=0 ) return s;
                        break;
                    case 40 : 
                        int LA69_107 = input.LA(1);

                         
                        int index69_107 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_107);
                        if ( s>=0 ) return s;
                        break;
                    case 41 : 
                        int LA69_108 = input.LA(1);

                         
                        int index69_108 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_108);
                        if ( s>=0 ) return s;
                        break;
                    case 42 : 
                        int LA69_109 = input.LA(1);

                         
                        int index69_109 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_109);
                        if ( s>=0 ) return s;
                        break;
                    case 43 : 
                        int LA69_110 = input.LA(1);

                         
                        int index69_110 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_110);
                        if ( s>=0 ) return s;
                        break;
                    case 44 : 
                        int LA69_111 = input.LA(1);

                         
                        int index69_111 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_111);
                        if ( s>=0 ) return s;
                        break;
                    case 45 : 
                        int LA69_112 = input.LA(1);

                         
                        int index69_112 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_112);
                        if ( s>=0 ) return s;
                        break;
                    case 46 : 
                        int LA69_113 = input.LA(1);

                         
                        int index69_113 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred129_PretC()) ) {s = 36;}

                        else if ( (true) ) {s = 14;}

                         
                        input.seek(index69_113);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 69, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA70_eotS =
        "\12\uffff";
    static final String DFA70_eofS =
        "\1\2\11\uffff";
    static final String DFA70_minS =
        "\1\51\11\uffff";
    static final String DFA70_maxS =
        "\1\143\11\uffff";
    static final String DFA70_acceptS =
        "\1\uffff\1\1\1\2\7\uffff";
    static final String DFA70_specialS =
        "\12\uffff}>";
    static final String[] DFA70_transitionS = {
            "\1\2\3\uffff\2\2\4\uffff\1\2\16\uffff\1\2\2\uffff\1\2\4\uffff"+
            "\1\2\30\uffff\1\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA70_eot = DFA.unpackEncodedString(DFA70_eotS);
    static final short[] DFA70_eof = DFA.unpackEncodedString(DFA70_eofS);
    static final char[] DFA70_min = DFA.unpackEncodedStringToUnsignedChars(DFA70_minS);
    static final char[] DFA70_max = DFA.unpackEncodedStringToUnsignedChars(DFA70_maxS);
    static final short[] DFA70_accept = DFA.unpackEncodedString(DFA70_acceptS);
    static final short[] DFA70_special = DFA.unpackEncodedString(DFA70_specialS);
    static final short[][] DFA70_transition;

    static {
        int numStates = DFA70_transitionS.length;
        DFA70_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA70_transition[i] = DFA.unpackEncodedString(DFA70_transitionS[i]);
        }
    }

    class DFA70 extends DFA {

        public DFA70(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 70;
            this.eot = DFA70_eot;
            this.eof = DFA70_eof;
            this.min = DFA70_min;
            this.max = DFA70_max;
            this.accept = DFA70_accept;
            this.special = DFA70_special;
            this.transition = DFA70_transition;
        }
        public String getDescription() {
            return "942:26: ( '?' expression ':' conditional_expression )?";
        }
    }
    static final String DFA71_eotS =
        "\13\uffff";
    static final String DFA71_eofS =
        "\1\1\12\uffff";
    static final String DFA71_minS =
        "\1\51\12\uffff";
    static final String DFA71_maxS =
        "\1\144\12\uffff";
    static final String DFA71_acceptS =
        "\1\uffff\1\2\10\uffff\1\1";
    static final String DFA71_specialS =
        "\13\uffff}>";
    static final String[] DFA71_transitionS = {
            "\1\1\3\uffff\2\1\4\uffff\1\1\16\uffff\1\1\2\uffff\1\1\4\uffff"+
            "\1\1\30\uffff\1\1\1\12",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA71_eot = DFA.unpackEncodedString(DFA71_eotS);
    static final short[] DFA71_eof = DFA.unpackEncodedString(DFA71_eofS);
    static final char[] DFA71_min = DFA.unpackEncodedStringToUnsignedChars(DFA71_minS);
    static final char[] DFA71_max = DFA.unpackEncodedStringToUnsignedChars(DFA71_maxS);
    static final short[] DFA71_accept = DFA.unpackEncodedString(DFA71_acceptS);
    static final short[] DFA71_special = DFA.unpackEncodedString(DFA71_specialS);
    static final short[][] DFA71_transition;

    static {
        int numStates = DFA71_transitionS.length;
        DFA71_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA71_transition[i] = DFA.unpackEncodedString(DFA71_transitionS[i]);
        }
    }

    class DFA71 extends DFA {

        public DFA71(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 71;
            this.eot = DFA71_eot;
            this.eof = DFA71_eof;
            this.min = DFA71_min;
            this.max = DFA71_max;
            this.accept = DFA71_accept;
            this.special = DFA71_special;
            this.transition = DFA71_transition;
        }
        public String getDescription() {
            return "()* loopback of 946:27: ( '||' logical_and_expression )*";
        }
    }
    static final String DFA72_eotS =
        "\14\uffff";
    static final String DFA72_eofS =
        "\1\1\13\uffff";
    static final String DFA72_minS =
        "\1\51\13\uffff";
    static final String DFA72_maxS =
        "\1\145\13\uffff";
    static final String DFA72_acceptS =
        "\1\uffff\1\2\11\uffff\1\1";
    static final String DFA72_specialS =
        "\14\uffff}>";
    static final String[] DFA72_transitionS = {
            "\1\1\3\uffff\2\1\4\uffff\1\1\16\uffff\1\1\2\uffff\1\1\4\uffff"+
            "\1\1\30\uffff\2\1\1\13",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA72_eot = DFA.unpackEncodedString(DFA72_eotS);
    static final short[] DFA72_eof = DFA.unpackEncodedString(DFA72_eofS);
    static final char[] DFA72_min = DFA.unpackEncodedStringToUnsignedChars(DFA72_minS);
    static final char[] DFA72_max = DFA.unpackEncodedStringToUnsignedChars(DFA72_maxS);
    static final short[] DFA72_accept = DFA.unpackEncodedString(DFA72_acceptS);
    static final short[] DFA72_special = DFA.unpackEncodedString(DFA72_specialS);
    static final short[][] DFA72_transition;

    static {
        int numStates = DFA72_transitionS.length;
        DFA72_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA72_transition[i] = DFA.unpackEncodedString(DFA72_transitionS[i]);
        }
    }

    class DFA72 extends DFA {

        public DFA72(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 72;
            this.eot = DFA72_eot;
            this.eof = DFA72_eof;
            this.min = DFA72_min;
            this.max = DFA72_max;
            this.accept = DFA72_accept;
            this.special = DFA72_special;
            this.transition = DFA72_transition;
        }
        public String getDescription() {
            return "()* loopback of 950:28: ( '&&' inclusive_or_expression )*";
        }
    }
    static final String DFA73_eotS =
        "\15\uffff";
    static final String DFA73_eofS =
        "\1\1\14\uffff";
    static final String DFA73_minS =
        "\1\51\14\uffff";
    static final String DFA73_maxS =
        "\1\146\14\uffff";
    static final String DFA73_acceptS =
        "\1\uffff\1\2\12\uffff\1\1";
    static final String DFA73_specialS =
        "\15\uffff}>";
    static final String[] DFA73_transitionS = {
            "\1\1\3\uffff\2\1\4\uffff\1\1\16\uffff\1\1\2\uffff\1\1\4\uffff"+
            "\1\1\30\uffff\3\1\1\14",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA73_eot = DFA.unpackEncodedString(DFA73_eotS);
    static final short[] DFA73_eof = DFA.unpackEncodedString(DFA73_eofS);
    static final char[] DFA73_min = DFA.unpackEncodedStringToUnsignedChars(DFA73_minS);
    static final char[] DFA73_max = DFA.unpackEncodedStringToUnsignedChars(DFA73_maxS);
    static final short[] DFA73_accept = DFA.unpackEncodedString(DFA73_acceptS);
    static final short[] DFA73_special = DFA.unpackEncodedString(DFA73_specialS);
    static final short[][] DFA73_transition;

    static {
        int numStates = DFA73_transitionS.length;
        DFA73_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA73_transition[i] = DFA.unpackEncodedString(DFA73_transitionS[i]);
        }
    }

    class DFA73 extends DFA {

        public DFA73(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 73;
            this.eot = DFA73_eot;
            this.eof = DFA73_eof;
            this.min = DFA73_min;
            this.max = DFA73_max;
            this.accept = DFA73_accept;
            this.special = DFA73_special;
            this.transition = DFA73_transition;
        }
        public String getDescription() {
            return "()* loopback of 954:28: ( '|' exclusive_or_expression )*";
        }
    }
    static final String DFA74_eotS =
        "\16\uffff";
    static final String DFA74_eofS =
        "\1\1\15\uffff";
    static final String DFA74_minS =
        "\1\51\15\uffff";
    static final String DFA74_maxS =
        "\1\147\15\uffff";
    static final String DFA74_acceptS =
        "\1\uffff\1\2\13\uffff\1\1";
    static final String DFA74_specialS =
        "\16\uffff}>";
    static final String[] DFA74_transitionS = {
            "\1\1\3\uffff\2\1\4\uffff\1\1\16\uffff\1\1\2\uffff\1\1\4\uffff"+
            "\1\1\30\uffff\4\1\1\15",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA74_eot = DFA.unpackEncodedString(DFA74_eotS);
    static final short[] DFA74_eof = DFA.unpackEncodedString(DFA74_eofS);
    static final char[] DFA74_min = DFA.unpackEncodedStringToUnsignedChars(DFA74_minS);
    static final char[] DFA74_max = DFA.unpackEncodedStringToUnsignedChars(DFA74_maxS);
    static final short[] DFA74_accept = DFA.unpackEncodedString(DFA74_acceptS);
    static final short[] DFA74_special = DFA.unpackEncodedString(DFA74_specialS);
    static final short[][] DFA74_transition;

    static {
        int numStates = DFA74_transitionS.length;
        DFA74_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA74_transition[i] = DFA.unpackEncodedString(DFA74_transitionS[i]);
        }
    }

    class DFA74 extends DFA {

        public DFA74(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 74;
            this.eot = DFA74_eot;
            this.eof = DFA74_eof;
            this.min = DFA74_min;
            this.max = DFA74_max;
            this.accept = DFA74_accept;
            this.special = DFA74_special;
            this.transition = DFA74_transition;
        }
        public String getDescription() {
            return "()* loopback of 958:19: ( '^' and_expression )*";
        }
    }
    static final String DFA75_eotS =
        "\17\uffff";
    static final String DFA75_eofS =
        "\1\1\16\uffff";
    static final String DFA75_minS =
        "\1\51\16\uffff";
    static final String DFA75_maxS =
        "\1\147\16\uffff";
    static final String DFA75_acceptS =
        "\1\uffff\1\2\14\uffff\1\1";
    static final String DFA75_specialS =
        "\17\uffff}>";
    static final String[] DFA75_transitionS = {
            "\1\1\3\uffff\2\1\4\uffff\1\1\16\uffff\1\1\2\uffff\1\1\4\uffff"+
            "\1\1\13\uffff\1\16\14\uffff\5\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA75_eot = DFA.unpackEncodedString(DFA75_eotS);
    static final short[] DFA75_eof = DFA.unpackEncodedString(DFA75_eofS);
    static final char[] DFA75_min = DFA.unpackEncodedStringToUnsignedChars(DFA75_minS);
    static final char[] DFA75_max = DFA.unpackEncodedStringToUnsignedChars(DFA75_maxS);
    static final short[] DFA75_accept = DFA.unpackEncodedString(DFA75_acceptS);
    static final short[] DFA75_special = DFA.unpackEncodedString(DFA75_specialS);
    static final short[][] DFA75_transition;

    static {
        int numStates = DFA75_transitionS.length;
        DFA75_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA75_transition[i] = DFA.unpackEncodedString(DFA75_transitionS[i]);
        }
    }

    class DFA75 extends DFA {

        public DFA75(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 75;
            this.eot = DFA75_eot;
            this.eof = DFA75_eof;
            this.min = DFA75_min;
            this.max = DFA75_max;
            this.accept = DFA75_accept;
            this.special = DFA75_special;
            this.transition = DFA75_transition;
        }
        public String getDescription() {
            return "()* loopback of 962:24: ( '&' equality_expression )*";
        }
    }
    static final String DFA76_eotS =
        "\20\uffff";
    static final String DFA76_eofS =
        "\1\1\17\uffff";
    static final String DFA76_minS =
        "\1\51\17\uffff";
    static final String DFA76_maxS =
        "\1\151\17\uffff";
    static final String DFA76_acceptS =
        "\1\uffff\1\2\15\uffff\1\1";
    static final String DFA76_specialS =
        "\20\uffff}>";
    static final String[] DFA76_transitionS = {
            "\1\1\3\uffff\2\1\4\uffff\1\1\16\uffff\1\1\2\uffff\1\1\4\uffff"+
            "\1\1\13\uffff\1\1\14\uffff\5\1\2\17",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA76_eot = DFA.unpackEncodedString(DFA76_eotS);
    static final short[] DFA76_eof = DFA.unpackEncodedString(DFA76_eofS);
    static final char[] DFA76_min = DFA.unpackEncodedStringToUnsignedChars(DFA76_minS);
    static final char[] DFA76_max = DFA.unpackEncodedStringToUnsignedChars(DFA76_maxS);
    static final short[] DFA76_accept = DFA.unpackEncodedString(DFA76_acceptS);
    static final short[] DFA76_special = DFA.unpackEncodedString(DFA76_specialS);
    static final short[][] DFA76_transition;

    static {
        int numStates = DFA76_transitionS.length;
        DFA76_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA76_transition[i] = DFA.unpackEncodedString(DFA76_transitionS[i]);
        }
    }

    class DFA76 extends DFA {

        public DFA76(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 76;
            this.eot = DFA76_eot;
            this.eof = DFA76_eof;
            this.min = DFA76_min;
            this.max = DFA76_max;
            this.accept = DFA76_accept;
            this.special = DFA76_special;
            this.transition = DFA76_transition;
        }
        public String getDescription() {
            return "()* loopback of 965:26: ( ( '==' | '!=' ) relational_expression )*";
        }
    }
    static final String DFA77_eotS =
        "\21\uffff";
    static final String DFA77_eofS =
        "\1\1\20\uffff";
    static final String DFA77_minS =
        "\1\51\20\uffff";
    static final String DFA77_maxS =
        "\1\155\20\uffff";
    static final String DFA77_acceptS =
        "\1\uffff\1\2\16\uffff\1\1";
    static final String DFA77_specialS =
        "\21\uffff}>";
    static final String[] DFA77_transitionS = {
            "\1\1\3\uffff\2\1\4\uffff\1\1\16\uffff\1\1\2\uffff\1\1\4\uffff"+
            "\1\1\13\uffff\1\1\14\uffff\7\1\4\20",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA77_eot = DFA.unpackEncodedString(DFA77_eotS);
    static final short[] DFA77_eof = DFA.unpackEncodedString(DFA77_eofS);
    static final char[] DFA77_min = DFA.unpackEncodedStringToUnsignedChars(DFA77_minS);
    static final char[] DFA77_max = DFA.unpackEncodedStringToUnsignedChars(DFA77_maxS);
    static final short[] DFA77_accept = DFA.unpackEncodedString(DFA77_acceptS);
    static final short[] DFA77_special = DFA.unpackEncodedString(DFA77_specialS);
    static final short[][] DFA77_transition;

    static {
        int numStates = DFA77_transitionS.length;
        DFA77_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA77_transition[i] = DFA.unpackEncodedString(DFA77_transitionS[i]);
        }
    }

    class DFA77 extends DFA {

        public DFA77(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 77;
            this.eot = DFA77_eot;
            this.eof = DFA77_eof;
            this.min = DFA77_min;
            this.max = DFA77_max;
            this.accept = DFA77_accept;
            this.special = DFA77_special;
            this.transition = DFA77_transition;
        }
        public String getDescription() {
            return "()* loopback of 969:21: ( ( '<' | '>' | '<=' | '>=' ) shift_expression )*";
        }
    }
    static final String DFA78_eotS =
        "\22\uffff";
    static final String DFA78_eofS =
        "\1\1\21\uffff";
    static final String DFA78_minS =
        "\1\51\21\uffff";
    static final String DFA78_maxS =
        "\1\157\21\uffff";
    static final String DFA78_acceptS =
        "\1\uffff\1\2\17\uffff\1\1";
    static final String DFA78_specialS =
        "\22\uffff}>";
    static final String[] DFA78_transitionS = {
            "\1\1\3\uffff\2\1\4\uffff\1\1\16\uffff\1\1\2\uffff\1\1\4\uffff"+
            "\1\1\13\uffff\1\1\14\uffff\13\1\2\21",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA78_eot = DFA.unpackEncodedString(DFA78_eotS);
    static final short[] DFA78_eof = DFA.unpackEncodedString(DFA78_eofS);
    static final char[] DFA78_min = DFA.unpackEncodedStringToUnsignedChars(DFA78_minS);
    static final char[] DFA78_max = DFA.unpackEncodedStringToUnsignedChars(DFA78_maxS);
    static final short[] DFA78_accept = DFA.unpackEncodedString(DFA78_acceptS);
    static final short[] DFA78_special = DFA.unpackEncodedString(DFA78_specialS);
    static final short[][] DFA78_transition;

    static {
        int numStates = DFA78_transitionS.length;
        DFA78_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA78_transition[i] = DFA.unpackEncodedString(DFA78_transitionS[i]);
        }
    }

    class DFA78 extends DFA {

        public DFA78(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 78;
            this.eot = DFA78_eot;
            this.eof = DFA78_eof;
            this.min = DFA78_min;
            this.max = DFA78_max;
            this.accept = DFA78_accept;
            this.special = DFA78_special;
            this.transition = DFA78_transition;
        }
        public String getDescription() {
            return "()* loopback of 973:24: ( ( '<<' | '>>' ) additive_expression )*";
        }
    }
    static final String DFA79_eotS =
        "\62\uffff";
    static final String DFA79_eofS =
        "\62\uffff";
    static final String DFA79_minS =
        "\1\25\1\51\60\uffff";
    static final String DFA79_maxS =
        "\1\u0081\1\157\60\uffff";
    static final String DFA79_acceptS =
        "\2\uffff\1\1\1\uffff\1\2\6\uffff\1\3\1\uffff\1\4\2\uffff\1\5\3"+
        "\uffff\1\6\1\7\1\10\2\uffff\1\11\30\uffff";
    static final String DFA79_specialS =
        "\62\uffff}>";
    static final String[] DFA79_transitionS = {
            "\1\1\1\4\1\uffff\5\4\14\uffff\1\4\7\uffff\1\4\17\uffff\1\31"+
            "\11\uffff\1\4\1\uffff\2\4\2\uffff\3\4\2\uffff\3\4\27\uffff\1"+
            "\25\2\2\1\26\1\uffff\2\26\1\24\1\13\1\uffff\1\13\3\15\4\20",
            "\1\4\2\uffff\2\4\3\uffff\1\4\23\uffff\1\2\3\uffff\1\4\1\uffff"+
            "\1\4\1\uffff\6\4\1\uffff\3\4\2\uffff\27\4",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA79_eot = DFA.unpackEncodedString(DFA79_eotS);
    static final short[] DFA79_eof = DFA.unpackEncodedString(DFA79_eofS);
    static final char[] DFA79_min = DFA.unpackEncodedStringToUnsignedChars(DFA79_minS);
    static final char[] DFA79_max = DFA.unpackEncodedStringToUnsignedChars(DFA79_maxS);
    static final short[] DFA79_accept = DFA.unpackEncodedString(DFA79_acceptS);
    static final short[] DFA79_special = DFA.unpackEncodedString(DFA79_specialS);
    static final short[][] DFA79_transition;

    static {
        int numStates = DFA79_transitionS.length;
        DFA79_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA79_transition[i] = DFA.unpackEncodedString(DFA79_transitionS[i]);
        }
    }

    class DFA79 extends DFA {

        public DFA79(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 79;
            this.eot = DFA79_eot;
            this.eof = DFA79_eof;
            this.min = DFA79_min;
            this.max = DFA79_max;
            this.accept = DFA79_accept;
            this.special = DFA79_special;
            this.transition = DFA79_transition;
        }
        public String getDescription() {
            return "978:1: statement : ( labeled_statement -> ^( LABELED_STATMENT_TOK ID_TOK[\"\"+(ID)] labeled_statement ) | expression_statement | selection_statement | iteration_statement | jump_statement -> ^( JUMP_STATMENT_TOK ID_TOK[\"\"+(ID)] SOURCE_TOK[$jump_statement.text] ) | parallel_statement | 'EOT' ';' -> ^( 'EOT' ID_TOK[\"\"+(ID)] SOURCE_TOK[sourceTemp] ) | preemption_statment | scope_statement );";
        }
    }
    static final String DFA81_eotS =
        "\55\uffff";
    static final String DFA81_eofS =
        "\55\uffff";
    static final String DFA81_minS =
        "\1\101\1\25\51\uffff\1\0\1\uffff";
    static final String DFA81_maxS =
        "\1\101\1\u0081\51\uffff\1\0\1\uffff";
    static final String DFA81_acceptS =
        "\2\uffff\1\2\51\uffff\1\1";
    static final String DFA81_specialS =
        "\53\uffff\1\0\1\uffff}>";
    static final String[] DFA81_transitionS = {
            "\1\1",
            "\10\2\14\uffff\1\2\7\uffff\2\2\1\uffff\16\2\1\53\2\2\1\uffff"+
            "\3\2\2\uffff\1\2\1\uffff\2\2\2\uffff\3\2\2\uffff\3\2\27\uffff"+
            "\4\2\1\uffff\4\2\1\uffff\10\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            ""
    };

    static final short[] DFA81_eot = DFA.unpackEncodedString(DFA81_eotS);
    static final short[] DFA81_eof = DFA.unpackEncodedString(DFA81_eofS);
    static final char[] DFA81_min = DFA.unpackEncodedStringToUnsignedChars(DFA81_minS);
    static final char[] DFA81_max = DFA.unpackEncodedStringToUnsignedChars(DFA81_maxS);
    static final short[] DFA81_accept = DFA.unpackEncodedString(DFA81_acceptS);
    static final short[] DFA81_special = DFA.unpackEncodedString(DFA81_specialS);
    static final short[][] DFA81_transition;

    static {
        int numStates = DFA81_transitionS.length;
        DFA81_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA81_transition[i] = DFA.unpackEncodedString(DFA81_transitionS[i]);
        }
    }

    class DFA81 extends DFA {

        public DFA81(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 81;
            this.eot = DFA81_eot;
            this.eof = DFA81_eof;
            this.min = DFA81_min;
            this.max = DFA81_max;
            this.accept = DFA81_accept;
            this.special = DFA81_special;
            this.transition = DFA81_transition;
        }
        public String getDescription() {
            return "1064:1: scope_statement : ( '{' '}' -> ^( SCOPE_TOK EMPTY_TOK END_TOK ) | '{' compound_statement '}' -> ^( SCOPE_TOK compound_statement END_TOK ) );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA81_43 = input.LA(1);

                         
                        int index81_43 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred164_PretC()) ) {s = 44;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index81_43);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 81, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA83_eotS =
        "\125\uffff";
    static final String DFA83_eofS =
        "\125\uffff";
    static final String DFA83_minS =
        "\2\25\50\uffff\52\0\1\uffff";
    static final String DFA83_maxS =
        "\2\u0081\50\uffff\52\0\1\uffff";
    static final String DFA83_acceptS =
        "\2\uffff\1\2\121\uffff\1\1";
    static final String DFA83_specialS =
        "\52\uffff\1\0\1\1\1\2\1\3\1\4\1\5\1\6\1\7\1\10\1\11\1\12\1\13\1"+
        "\14\1\15\1\16\1\17\1\20\1\21\1\22\1\23\1\24\1\25\1\26\1\27\1\30"+
        "\1\31\1\32\1\33\1\34\1\35\1\36\1\37\1\40\1\41\1\42\1\43\1\44\1\45"+
        "\1\46\1\47\1\50\1\51\1\uffff}>";
    static final String[] DFA83_transitionS = {
            "\10\2\14\uffff\1\2\7\uffff\2\2\1\uffff\15\2\1\1\1\uffff\2\2"+
            "\1\uffff\3\2\2\uffff\1\2\1\uffff\2\2\2\uffff\3\2\2\uffff\3\2"+
            "\27\uffff\4\2\1\uffff\4\2\1\uffff\10\2",
            "\1\72\1\77\1\73\5\77\14\uffff\1\76\7\uffff\1\100\1\56\1\uffff"+
            "\1\53\4\54\1\57\1\60\1\61\1\62\1\63\1\64\1\65\1\66\1\123\1\52"+
            "\1\67\1\70\1\uffff\1\71\2\55\2\uffff\1\103\1\uffff\2\103\2\uffff"+
            "\1\101\1\102\1\104\2\uffff\3\103\27\uffff\1\117\1\74\1\75\1"+
            "\120\1\uffff\1\121\1\122\1\116\1\105\1\uffff\1\106\1\107\1\110"+
            "\1\111\1\112\1\113\1\114\1\115",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            ""
    };

    static final short[] DFA83_eot = DFA.unpackEncodedString(DFA83_eotS);
    static final short[] DFA83_eof = DFA.unpackEncodedString(DFA83_eofS);
    static final char[] DFA83_min = DFA.unpackEncodedStringToUnsignedChars(DFA83_minS);
    static final char[] DFA83_max = DFA.unpackEncodedStringToUnsignedChars(DFA83_maxS);
    static final short[] DFA83_accept = DFA.unpackEncodedString(DFA83_acceptS);
    static final short[] DFA83_special = DFA.unpackEncodedString(DFA83_specialS);
    static final short[][] DFA83_transition;

    static {
        int numStates = DFA83_transitionS.length;
        DFA83_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA83_transition[i] = DFA.unpackEncodedString(DFA83_transitionS[i]);
        }
    }

    class DFA83 extends DFA {

        public DFA83(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 83;
            this.eot = DFA83_eot;
            this.eof = DFA83_eof;
            this.min = DFA83_min;
            this.max = DFA83_max;
            this.accept = DFA83_accept;
            this.special = DFA83_special;
            this.transition = DFA83_transition;
        }
        public String getDescription() {
            return "1095:1: condition_statement : ( ( '{' ( compound_statement )? '}' )=> scope_statement | ( declaration | statement ) -> ^( SCOPE_TOK ( declaration )? ( statement )? END_TOK ) );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA83_42 = input.LA(1);

                         
                        int index83_42 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_42);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA83_43 = input.LA(1);

                         
                        int index83_43 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_43);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA83_44 = input.LA(1);

                         
                        int index83_44 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_44);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA83_45 = input.LA(1);

                         
                        int index83_45 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_45);
                        if ( s>=0 ) return s;
                        break;
                    case 4 : 
                        int LA83_46 = input.LA(1);

                         
                        int index83_46 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_46);
                        if ( s>=0 ) return s;
                        break;
                    case 5 : 
                        int LA83_47 = input.LA(1);

                         
                        int index83_47 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_47);
                        if ( s>=0 ) return s;
                        break;
                    case 6 : 
                        int LA83_48 = input.LA(1);

                         
                        int index83_48 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_48);
                        if ( s>=0 ) return s;
                        break;
                    case 7 : 
                        int LA83_49 = input.LA(1);

                         
                        int index83_49 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_49);
                        if ( s>=0 ) return s;
                        break;
                    case 8 : 
                        int LA83_50 = input.LA(1);

                         
                        int index83_50 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_50);
                        if ( s>=0 ) return s;
                        break;
                    case 9 : 
                        int LA83_51 = input.LA(1);

                         
                        int index83_51 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_51);
                        if ( s>=0 ) return s;
                        break;
                    case 10 : 
                        int LA83_52 = input.LA(1);

                         
                        int index83_52 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_52);
                        if ( s>=0 ) return s;
                        break;
                    case 11 : 
                        int LA83_53 = input.LA(1);

                         
                        int index83_53 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_53);
                        if ( s>=0 ) return s;
                        break;
                    case 12 : 
                        int LA83_54 = input.LA(1);

                         
                        int index83_54 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_54);
                        if ( s>=0 ) return s;
                        break;
                    case 13 : 
                        int LA83_55 = input.LA(1);

                         
                        int index83_55 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_55);
                        if ( s>=0 ) return s;
                        break;
                    case 14 : 
                        int LA83_56 = input.LA(1);

                         
                        int index83_56 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_56);
                        if ( s>=0 ) return s;
                        break;
                    case 15 : 
                        int LA83_57 = input.LA(1);

                         
                        int index83_57 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_57);
                        if ( s>=0 ) return s;
                        break;
                    case 16 : 
                        int LA83_58 = input.LA(1);

                         
                        int index83_58 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_58);
                        if ( s>=0 ) return s;
                        break;
                    case 17 : 
                        int LA83_59 = input.LA(1);

                         
                        int index83_59 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_59);
                        if ( s>=0 ) return s;
                        break;
                    case 18 : 
                        int LA83_60 = input.LA(1);

                         
                        int index83_60 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_60);
                        if ( s>=0 ) return s;
                        break;
                    case 19 : 
                        int LA83_61 = input.LA(1);

                         
                        int index83_61 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_61);
                        if ( s>=0 ) return s;
                        break;
                    case 20 : 
                        int LA83_62 = input.LA(1);

                         
                        int index83_62 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_62);
                        if ( s>=0 ) return s;
                        break;
                    case 21 : 
                        int LA83_63 = input.LA(1);

                         
                        int index83_63 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_63);
                        if ( s>=0 ) return s;
                        break;
                    case 22 : 
                        int LA83_64 = input.LA(1);

                         
                        int index83_64 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_64);
                        if ( s>=0 ) return s;
                        break;
                    case 23 : 
                        int LA83_65 = input.LA(1);

                         
                        int index83_65 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_65);
                        if ( s>=0 ) return s;
                        break;
                    case 24 : 
                        int LA83_66 = input.LA(1);

                         
                        int index83_66 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_66);
                        if ( s>=0 ) return s;
                        break;
                    case 25 : 
                        int LA83_67 = input.LA(1);

                         
                        int index83_67 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_67);
                        if ( s>=0 ) return s;
                        break;
                    case 26 : 
                        int LA83_68 = input.LA(1);

                         
                        int index83_68 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_68);
                        if ( s>=0 ) return s;
                        break;
                    case 27 : 
                        int LA83_69 = input.LA(1);

                         
                        int index83_69 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_69);
                        if ( s>=0 ) return s;
                        break;
                    case 28 : 
                        int LA83_70 = input.LA(1);

                         
                        int index83_70 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_70);
                        if ( s>=0 ) return s;
                        break;
                    case 29 : 
                        int LA83_71 = input.LA(1);

                         
                        int index83_71 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_71);
                        if ( s>=0 ) return s;
                        break;
                    case 30 : 
                        int LA83_72 = input.LA(1);

                         
                        int index83_72 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_72);
                        if ( s>=0 ) return s;
                        break;
                    case 31 : 
                        int LA83_73 = input.LA(1);

                         
                        int index83_73 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_73);
                        if ( s>=0 ) return s;
                        break;
                    case 32 : 
                        int LA83_74 = input.LA(1);

                         
                        int index83_74 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_74);
                        if ( s>=0 ) return s;
                        break;
                    case 33 : 
                        int LA83_75 = input.LA(1);

                         
                        int index83_75 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_75);
                        if ( s>=0 ) return s;
                        break;
                    case 34 : 
                        int LA83_76 = input.LA(1);

                         
                        int index83_76 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_76);
                        if ( s>=0 ) return s;
                        break;
                    case 35 : 
                        int LA83_77 = input.LA(1);

                         
                        int index83_77 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_77);
                        if ( s>=0 ) return s;
                        break;
                    case 36 : 
                        int LA83_78 = input.LA(1);

                         
                        int index83_78 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_78);
                        if ( s>=0 ) return s;
                        break;
                    case 37 : 
                        int LA83_79 = input.LA(1);

                         
                        int index83_79 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_79);
                        if ( s>=0 ) return s;
                        break;
                    case 38 : 
                        int LA83_80 = input.LA(1);

                         
                        int index83_80 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_80);
                        if ( s>=0 ) return s;
                        break;
                    case 39 : 
                        int LA83_81 = input.LA(1);

                         
                        int index83_81 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_81);
                        if ( s>=0 ) return s;
                        break;
                    case 40 : 
                        int LA83_82 = input.LA(1);

                         
                        int index83_82 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_82);
                        if ( s>=0 ) return s;
                        break;
                    case 41 : 
                        int LA83_83 = input.LA(1);

                         
                        int index83_83 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred166_PretC()) ) {s = 84;}

                        else if ( (true) ) {s = 2;}

                         
                        input.seek(index83_83);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 83, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA82_eotS =
        "\103\uffff";
    static final String DFA82_eofS =
        "\103\uffff";
    static final String DFA82_minS =
        "\1\25\17\uffff\1\25\32\uffff\1\0\1\uffff\2\0\24\uffff";
    static final String DFA82_maxS =
        "\1\u0081\17\uffff\1\157\32\uffff\1\0\1\uffff\2\0\24\uffff";
    static final String DFA82_acceptS =
        "\1\uffff\1\1\20\uffff\1\2\60\uffff";
    static final String DFA82_specialS =
        "\53\uffff\1\0\1\uffff\1\1\1\2\24\uffff}>";
    static final String[] DFA82_transitionS = {
            "\1\20\1\22\1\1\5\22\14\uffff\1\22\7\uffff\1\22\1\1\1\uffff"+
            "\15\1\1\22\1\uffff\2\1\1\uffff\3\1\2\uffff\1\22\1\uffff\2\22"+
            "\2\uffff\3\22\2\uffff\3\22\27\uffff\4\22\1\uffff\4\22\1\uffff"+
            "\10\22",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\1\23\uffff\1\56\2\uffff\2\22\3\uffff\1\55\23\uffff\1\22"+
            "\3\uffff\1\22\1\uffff\1\53\1\uffff\6\22\1\uffff\3\22\2\uffff"+
            "\27\22",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA82_eot = DFA.unpackEncodedString(DFA82_eotS);
    static final short[] DFA82_eof = DFA.unpackEncodedString(DFA82_eofS);
    static final char[] DFA82_min = DFA.unpackEncodedStringToUnsignedChars(DFA82_minS);
    static final char[] DFA82_max = DFA.unpackEncodedStringToUnsignedChars(DFA82_maxS);
    static final short[] DFA82_accept = DFA.unpackEncodedString(DFA82_acceptS);
    static final short[] DFA82_special = DFA.unpackEncodedString(DFA82_specialS);
    static final short[][] DFA82_transition;

    static {
        int numStates = DFA82_transitionS.length;
        DFA82_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA82_transition[i] = DFA.unpackEncodedString(DFA82_transitionS[i]);
        }
    }

    class DFA82 extends DFA {

        public DFA82(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 82;
            this.eot = DFA82_eot;
            this.eof = DFA82_eof;
            this.min = DFA82_min;
            this.max = DFA82_max;
            this.accept = DFA82_accept;
            this.special = DFA82_special;
            this.transition = DFA82_transition;
        }
        public String getDescription() {
            return "1101:126: ( declaration | statement )";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA82_43 = input.LA(1);

                         
                        int index82_43 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred167_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred167_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 1;}

                        else if ( (true) ) {s = 18;}

                         
                        input.seek(index82_43);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA82_45 = input.LA(1);

                         
                        int index82_45 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred167_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred167_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 1;}

                        else if ( (true) ) {s = 18;}

                         
                        input.seek(index82_45);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA82_46 = input.LA(1);

                         
                        int index82_46 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred167_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred167_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 1;}

                        else if ( (true) ) {s = 18;}

                         
                        input.seek(index82_46);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 82, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA84_eotS =
        "\105\uffff";
    static final String DFA84_eofS =
        "\1\1\104\uffff";
    static final String DFA84_minS =
        "\1\25\21\uffff\1\25\33\uffff\1\0\5\uffff\1\0\1\uffff\1\0\16\uffff";
    static final String DFA84_maxS =
        "\1\u0081\21\uffff\1\157\33\uffff\1\0\5\uffff\1\0\1\uffff\1\0\16"+
        "\uffff";
    static final String DFA84_acceptS =
        "\1\uffff\1\3\1\uffff\1\1\20\uffff\1\2\60\uffff";
    static final String DFA84_specialS =
        "\56\uffff\1\0\5\uffff\1\1\1\uffff\1\2\16\uffff}>";
    static final String[] DFA84_transitionS = {
            "\1\22\1\24\1\3\5\24\14\uffff\1\24\7\uffff\1\24\1\3\1\uffff"+
            "\15\3\1\24\1\1\2\3\1\uffff\3\3\2\uffff\1\24\1\uffff\2\24\2\uffff"+
            "\3\24\2\uffff\3\24\27\uffff\4\24\1\uffff\4\24\1\uffff\10\24",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\3\23\uffff\1\66\2\uffff\2\24\3\uffff\1\56\23\uffff\1\24"+
            "\3\uffff\1\24\1\uffff\1\64\1\uffff\6\24\1\uffff\3\24\2\uffff"+
            "\27\24",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA84_eot = DFA.unpackEncodedString(DFA84_eotS);
    static final short[] DFA84_eof = DFA.unpackEncodedString(DFA84_eofS);
    static final char[] DFA84_min = DFA.unpackEncodedStringToUnsignedChars(DFA84_minS);
    static final char[] DFA84_max = DFA.unpackEncodedStringToUnsignedChars(DFA84_maxS);
    static final short[] DFA84_accept = DFA.unpackEncodedString(DFA84_acceptS);
    static final short[] DFA84_special = DFA.unpackEncodedString(DFA84_specialS);
    static final short[][] DFA84_transition;

    static {
        int numStates = DFA84_transitionS.length;
        DFA84_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA84_transition[i] = DFA.unpackEncodedString(DFA84_transitionS[i]);
        }
    }

    class DFA84 extends DFA {

        public DFA84(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 84;
            this.eot = DFA84_eot;
            this.eof = DFA84_eof;
            this.min = DFA84_min;
            this.max = DFA84_max;
            this.accept = DFA84_accept;
            this.special = DFA84_special;
            this.transition = DFA84_transition;
        }
        public String getDescription() {
            return "()* loopback of 1109:4: ( declaration | statement_list )*";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA84_46 = input.LA(1);

                         
                        int index84_46 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred168_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred168_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 3;}

                        else if ( (synpred169_PretC()) ) {s = 20;}

                         
                        input.seek(index84_46);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA84_52 = input.LA(1);

                         
                        int index84_52 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred168_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred168_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 3;}

                        else if ( (synpred169_PretC()) ) {s = 20;}

                         
                        input.seek(index84_52);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA84_54 = input.LA(1);

                         
                        int index84_54 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred168_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred168_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 3;}

                        else if ( (synpred169_PretC()) ) {s = 20;}

                         
                        input.seek(index84_54);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 84, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA85_eotS =
        "\u01a0\uffff";
    static final String DFA85_eofS =
        "\1\1\u019f\uffff";
    static final String DFA85_minS =
        "\1\25\21\uffff\1\0\1\uffff\30\0\u0174\uffff";
    static final String DFA85_maxS =
        "\1\u0081\21\uffff\1\0\1\uffff\30\0\u0174\uffff";
    static final String DFA85_acceptS =
        "\1\uffff\1\2\103\uffff\1\1\u015a\uffff";
    static final String DFA85_specialS =
        "\22\uffff\1\0\1\uffff\1\1\1\2\1\3\1\4\1\5\1\6\1\7\1\10\1\11\1\12"+
        "\1\13\1\14\1\15\1\16\1\17\1\20\1\21\1\22\1\23\1\24\1\25\1\26\1\27"+
        "\1\30\u0174\uffff}>";
    static final String[] DFA85_transitionS = {
            "\1\22\1\27\1\1\5\27\14\uffff\1\26\7\uffff\1\30\1\1\1\uffff"+
            "\15\1\1\53\3\1\1\uffff\3\1\2\uffff\1\33\1\uffff\2\33\2\uffff"+
            "\1\31\1\32\1\34\2\uffff\3\33\27\uffff\1\47\1\24\1\25\1\50\1"+
            "\uffff\1\51\1\52\1\46\1\35\1\uffff\1\36\1\37\1\40\1\41\1\42"+
            "\1\43\1\44\1\45",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA85_eot = DFA.unpackEncodedString(DFA85_eotS);
    static final short[] DFA85_eof = DFA.unpackEncodedString(DFA85_eofS);
    static final char[] DFA85_min = DFA.unpackEncodedStringToUnsignedChars(DFA85_minS);
    static final char[] DFA85_max = DFA.unpackEncodedStringToUnsignedChars(DFA85_maxS);
    static final short[] DFA85_accept = DFA.unpackEncodedString(DFA85_acceptS);
    static final short[] DFA85_special = DFA.unpackEncodedString(DFA85_specialS);
    static final short[][] DFA85_transition;

    static {
        int numStates = DFA85_transitionS.length;
        DFA85_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA85_transition[i] = DFA.unpackEncodedString(DFA85_transitionS[i]);
        }
    }

    class DFA85 extends DFA {

        public DFA85(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 85;
            this.eot = DFA85_eot;
            this.eof = DFA85_eof;
            this.min = DFA85_min;
            this.max = DFA85_max;
            this.accept = DFA85_accept;
            this.special = DFA85_special;
            this.transition = DFA85_transition;
        }
        public String getDescription() {
            return "()+ loopback of 1113:4: ( statement )+";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA85_18 = input.LA(1);

                         
                        int index85_18 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_18);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA85_20 = input.LA(1);

                         
                        int index85_20 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_20);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA85_21 = input.LA(1);

                         
                        int index85_21 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_21);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA85_22 = input.LA(1);

                         
                        int index85_22 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_22);
                        if ( s>=0 ) return s;
                        break;
                    case 4 : 
                        int LA85_23 = input.LA(1);

                         
                        int index85_23 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_23);
                        if ( s>=0 ) return s;
                        break;
                    case 5 : 
                        int LA85_24 = input.LA(1);

                         
                        int index85_24 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_24);
                        if ( s>=0 ) return s;
                        break;
                    case 6 : 
                        int LA85_25 = input.LA(1);

                         
                        int index85_25 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_25);
                        if ( s>=0 ) return s;
                        break;
                    case 7 : 
                        int LA85_26 = input.LA(1);

                         
                        int index85_26 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_26);
                        if ( s>=0 ) return s;
                        break;
                    case 8 : 
                        int LA85_27 = input.LA(1);

                         
                        int index85_27 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_27);
                        if ( s>=0 ) return s;
                        break;
                    case 9 : 
                        int LA85_28 = input.LA(1);

                         
                        int index85_28 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_28);
                        if ( s>=0 ) return s;
                        break;
                    case 10 : 
                        int LA85_29 = input.LA(1);

                         
                        int index85_29 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_29);
                        if ( s>=0 ) return s;
                        break;
                    case 11 : 
                        int LA85_30 = input.LA(1);

                         
                        int index85_30 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_30);
                        if ( s>=0 ) return s;
                        break;
                    case 12 : 
                        int LA85_31 = input.LA(1);

                         
                        int index85_31 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_31);
                        if ( s>=0 ) return s;
                        break;
                    case 13 : 
                        int LA85_32 = input.LA(1);

                         
                        int index85_32 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_32);
                        if ( s>=0 ) return s;
                        break;
                    case 14 : 
                        int LA85_33 = input.LA(1);

                         
                        int index85_33 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_33);
                        if ( s>=0 ) return s;
                        break;
                    case 15 : 
                        int LA85_34 = input.LA(1);

                         
                        int index85_34 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_34);
                        if ( s>=0 ) return s;
                        break;
                    case 16 : 
                        int LA85_35 = input.LA(1);

                         
                        int index85_35 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_35);
                        if ( s>=0 ) return s;
                        break;
                    case 17 : 
                        int LA85_36 = input.LA(1);

                         
                        int index85_36 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_36);
                        if ( s>=0 ) return s;
                        break;
                    case 18 : 
                        int LA85_37 = input.LA(1);

                         
                        int index85_37 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_37);
                        if ( s>=0 ) return s;
                        break;
                    case 19 : 
                        int LA85_38 = input.LA(1);

                         
                        int index85_38 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_38);
                        if ( s>=0 ) return s;
                        break;
                    case 20 : 
                        int LA85_39 = input.LA(1);

                         
                        int index85_39 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_39);
                        if ( s>=0 ) return s;
                        break;
                    case 21 : 
                        int LA85_40 = input.LA(1);

                         
                        int index85_40 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_40);
                        if ( s>=0 ) return s;
                        break;
                    case 22 : 
                        int LA85_41 = input.LA(1);

                         
                        int index85_41 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_41);
                        if ( s>=0 ) return s;
                        break;
                    case 23 : 
                        int LA85_42 = input.LA(1);

                         
                        int index85_42 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_42);
                        if ( s>=0 ) return s;
                        break;
                    case 24 : 
                        int LA85_43 = input.LA(1);

                         
                        int index85_43 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred170_PretC()) ) {s = 69;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index85_43);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 85, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA93_eotS =
        "\53\uffff";
    static final String DFA93_eofS =
        "\53\uffff";
    static final String DFA93_minS =
        "\1\25\52\uffff";
    static final String DFA93_maxS =
        "\1\u0081\52\uffff";
    static final String DFA93_acceptS =
        "\1\uffff\1\1\1\2\50\uffff";
    static final String DFA93_specialS =
        "\53\uffff}>";
    static final String[] DFA93_transitionS = {
            "\10\2\14\uffff\1\2\7\uffff\2\2\1\uffff\16\2\1\uffff\2\2\1\1"+
            "\3\2\2\uffff\1\2\1\uffff\2\2\2\uffff\3\2\2\uffff\3\2\27\uffff"+
            "\4\2\1\uffff\4\2\1\uffff\10\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA93_eot = DFA.unpackEncodedString(DFA93_eotS);
    static final short[] DFA93_eof = DFA.unpackEncodedString(DFA93_eofS);
    static final char[] DFA93_min = DFA.unpackEncodedStringToUnsignedChars(DFA93_minS);
    static final char[] DFA93_max = DFA.unpackEncodedStringToUnsignedChars(DFA93_maxS);
    static final short[] DFA93_accept = DFA.unpackEncodedString(DFA93_acceptS);
    static final short[] DFA93_special = DFA.unpackEncodedString(DFA93_specialS);
    static final short[][] DFA93_transition;

    static {
        int numStates = DFA93_transitionS.length;
        DFA93_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA93_transition[i] = DFA.unpackEncodedString(DFA93_transitionS[i]);
        }
    }

    class DFA93 extends DFA {

        public DFA93(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 93;
            this.eot = DFA93_eot;
            this.eof = DFA93_eof;
            this.min = DFA93_min;
            this.max = DFA93_max;
            this.accept = DFA93_accept;
            this.special = DFA93_special;
            this.transition = DFA93_transition;
        }
        public String getDescription() {
            return "1378:3: ( ':' DECIMAL_LITERAL )?";
        }
    }
    static final String DFA94_eotS =
        "\53\uffff";
    static final String DFA94_eofS =
        "\53\uffff";
    static final String DFA94_minS =
        "\1\25\52\uffff";
    static final String DFA94_maxS =
        "\1\u0081\52\uffff";
    static final String DFA94_acceptS =
        "\1\uffff\1\1\1\2\50\uffff";
    static final String DFA94_specialS =
        "\53\uffff}>";
    static final String[] DFA94_transitionS = {
            "\10\2\14\uffff\1\2\7\uffff\2\2\1\uffff\16\2\1\uffff\2\2\1\1"+
            "\3\2\2\uffff\1\2\1\uffff\2\2\2\uffff\3\2\2\uffff\3\2\27\uffff"+
            "\4\2\1\uffff\4\2\1\uffff\10\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA94_eot = DFA.unpackEncodedString(DFA94_eotS);
    static final short[] DFA94_eof = DFA.unpackEncodedString(DFA94_eofS);
    static final char[] DFA94_min = DFA.unpackEncodedStringToUnsignedChars(DFA94_minS);
    static final char[] DFA94_max = DFA.unpackEncodedStringToUnsignedChars(DFA94_maxS);
    static final short[] DFA94_accept = DFA.unpackEncodedString(DFA94_acceptS);
    static final short[] DFA94_special = DFA.unpackEncodedString(DFA94_specialS);
    static final short[][] DFA94_transition;

    static {
        int numStates = DFA94_transitionS.length;
        DFA94_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA94_transition[i] = DFA.unpackEncodedString(DFA94_transitionS[i]);
        }
    }

    class DFA94 extends DFA {

        public DFA94(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 94;
            this.eot = DFA94_eot;
            this.eof = DFA94_eof;
            this.min = DFA94_min;
            this.max = DFA94_max;
            this.accept = DFA94_accept;
            this.special = DFA94_special;
            this.transition = DFA94_transition;
        }
        public String getDescription() {
            return "1383:9: ( ':' DECIMAL_LITERAL )?";
        }
    }
    static final String DFA98_eotS =
        "\53\uffff";
    static final String DFA98_eofS =
        "\53\uffff";
    static final String DFA98_minS =
        "\1\25\52\uffff";
    static final String DFA98_maxS =
        "\1\u0081\52\uffff";
    static final String DFA98_acceptS =
        "\1\uffff\1\1\1\2\50\uffff";
    static final String DFA98_specialS =
        "\53\uffff}>";
    static final String[] DFA98_transitionS = {
            "\10\2\14\uffff\1\2\7\uffff\2\2\1\uffff\16\2\1\uffff\2\2\1\1"+
            "\3\2\2\uffff\1\2\1\uffff\2\2\2\uffff\3\2\2\uffff\3\2\27\uffff"+
            "\4\2\1\uffff\4\2\1\uffff\10\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA98_eot = DFA.unpackEncodedString(DFA98_eotS);
    static final short[] DFA98_eof = DFA.unpackEncodedString(DFA98_eofS);
    static final char[] DFA98_min = DFA.unpackEncodedStringToUnsignedChars(DFA98_minS);
    static final char[] DFA98_max = DFA.unpackEncodedStringToUnsignedChars(DFA98_maxS);
    static final short[] DFA98_accept = DFA.unpackEncodedString(DFA98_acceptS);
    static final short[] DFA98_special = DFA.unpackEncodedString(DFA98_specialS);
    static final short[][] DFA98_transition;

    static {
        int numStates = DFA98_transitionS.length;
        DFA98_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA98_transition[i] = DFA.unpackEncodedString(DFA98_transitionS[i]);
        }
    }

    class DFA98 extends DFA {

        public DFA98(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 98;
            this.eot = DFA98_eot;
            this.eof = DFA98_eof;
            this.min = DFA98_min;
            this.max = DFA98_max;
            this.accept = DFA98_accept;
            this.special = DFA98_special;
            this.transition = DFA98_transition;
        }
        public String getDescription() {
            return "1435:4: ( ':' DECIMAL_LITERAL )?";
        }
    }
    static final String DFA100_eotS =
        "\15\uffff";
    static final String DFA100_eofS =
        "\15\uffff";
    static final String DFA100_minS =
        "\1\176\3\uffff\1\25\10\uffff";
    static final String DFA100_maxS =
        "\1\u0081\3\uffff\1\130\10\uffff";
    static final String DFA100_acceptS =
        "\1\uffff\1\1\1\2\1\3\1\uffff\1\4\1\5\6\uffff";
    static final String DFA100_specialS =
        "\15\uffff}>";
    static final String[] DFA100_transitionS = {
            "\1\1\1\2\1\3\1\4",
            "",
            "",
            "",
            "\2\6\1\uffff\5\6\14\uffff\1\5\7\uffff\1\6\31\uffff\1\6\1\uffff"+
            "\2\6\2\uffff\3\6\2\uffff\3\6",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA100_eot = DFA.unpackEncodedString(DFA100_eotS);
    static final short[] DFA100_eof = DFA.unpackEncodedString(DFA100_eofS);
    static final char[] DFA100_min = DFA.unpackEncodedStringToUnsignedChars(DFA100_minS);
    static final char[] DFA100_max = DFA.unpackEncodedStringToUnsignedChars(DFA100_maxS);
    static final short[] DFA100_accept = DFA.unpackEncodedString(DFA100_acceptS);
    static final short[] DFA100_special = DFA.unpackEncodedString(DFA100_specialS);
    static final short[][] DFA100_transition;

    static {
        int numStates = DFA100_transitionS.length;
        DFA100_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA100_transition[i] = DFA.unpackEncodedString(DFA100_transitionS[i]);
        }
    }

    class DFA100 extends DFA {

        public DFA100(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 100;
            this.eot = DFA100_eot;
            this.eof = DFA100_eof;
            this.min = DFA100_min;
            this.max = DFA100_max;
            this.accept = DFA100_accept;
            this.special = DFA100_special;
            this.transition = DFA100_transition;
        }
        public String getDescription() {
            return "1456:1: jump_statement : ( 'goto' IDENTIFIER ';' | 'continue' ';' | 'break' ';' | 'return' ';' | 'return' expression ';' );";
        }
    }
    static final String DFA101_eotS =
        "\47\uffff";
    static final String DFA101_eofS =
        "\47\uffff";
    static final String DFA101_minS =
        "\1\25\16\uffff\1\25\3\uffff\2\0\22\uffff";
    static final String DFA101_maxS =
        "\1\113\16\uffff\1\113\3\uffff\2\0\22\uffff";
    static final String DFA101_acceptS =
        "\1\uffff\1\1\16\uffff\1\2\26\uffff";
    static final String DFA101_specialS =
        "\23\uffff\1\0\1\1\22\uffff}>";
    static final String[] DFA101_transitionS = {
            "\1\17\33\uffff\1\20\1\1\2\uffff\14\1\2\uffff\2\1\1\uffff\3"+
            "\1\2\uffff\1\20",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\23\1\uffff\1\20\31\uffff\1\24\1\20\1\uffff\16\20\1\uffff"+
            "\2\20\1\uffff\4\20\1\uffff\1\1",
            "",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA101_eot = DFA.unpackEncodedString(DFA101_eotS);
    static final short[] DFA101_eof = DFA.unpackEncodedString(DFA101_eofS);
    static final char[] DFA101_min = DFA.unpackEncodedStringToUnsignedChars(DFA101_minS);
    static final char[] DFA101_max = DFA.unpackEncodedStringToUnsignedChars(DFA101_maxS);
    static final short[] DFA101_accept = DFA.unpackEncodedString(DFA101_acceptS);
    static final short[] DFA101_special = DFA.unpackEncodedString(DFA101_specialS);
    static final short[][] DFA101_transition;

    static {
        int numStates = DFA101_transitionS.length;
        DFA101_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA101_transition[i] = DFA.unpackEncodedString(DFA101_transitionS[i]);
        }
    }

    class DFA101 extends DFA {

        public DFA101(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 101;
            this.eot = DFA101_eot;
            this.eof = DFA101_eof;
            this.min = DFA101_min;
            this.max = DFA101_max;
            this.accept = DFA101_accept;
            this.special = DFA101_special;
            this.transition = DFA101_transition;
        }
        public String getDescription() {
            return "239:6: ( declaration_specifiers )?";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA101_19 = input.LA(1);

                         
                        int index101_19 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred2_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred2_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 1;}

                        else if ( (true) ) {s = 16;}

                         
                        input.seek(index101_19);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA101_20 = input.LA(1);

                         
                        int index101_20 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (((synpred2_PretC()&&(isTypeName(input.LT(1).getText())))||(synpred2_PretC()&&(PRETdefinedtable.contains(input.LT(1).getText()))))) ) {s = 1;}

                        else if ( (true) ) {s = 16;}

                         
                        input.seek(index101_20);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 101, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA102_eotS =
        "\23\uffff";
    static final String DFA102_eofS =
        "\23\uffff";
    static final String DFA102_minS =
        "\1\25\22\uffff";
    static final String DFA102_maxS =
        "\1\110\22\uffff";
    static final String DFA102_acceptS =
        "\1\uffff\1\2\1\1\20\uffff";
    static final String DFA102_specialS =
        "\23\uffff}>";
    static final String[] DFA102_transitionS = {
            "\1\2\1\uffff\1\2\32\uffff\1\2\1\uffff\15\2\1\1\1\uffff\2\2"+
            "\1\uffff\3\2",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA102_eot = DFA.unpackEncodedString(DFA102_eotS);
    static final short[] DFA102_eof = DFA.unpackEncodedString(DFA102_eofS);
    static final char[] DFA102_min = DFA.unpackEncodedStringToUnsignedChars(DFA102_minS);
    static final char[] DFA102_max = DFA.unpackEncodedStringToUnsignedChars(DFA102_maxS);
    static final short[] DFA102_accept = DFA.unpackEncodedString(DFA102_acceptS);
    static final short[] DFA102_special = DFA.unpackEncodedString(DFA102_specialS);
    static final short[][] DFA102_transition;

    static {
        int numStates = DFA102_transitionS.length;
        DFA102_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA102_transition[i] = DFA.unpackEncodedString(DFA102_transitionS[i]);
        }
    }

    class DFA102 extends DFA {

        public DFA102(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 102;
            this.eot = DFA102_eot;
            this.eof = DFA102_eof;
            this.min = DFA102_min;
            this.max = DFA102_max;
            this.accept = DFA102_accept;
            this.special = DFA102_special;
            this.transition = DFA102_transition;
        }
        public String getDescription() {
            return "()* loopback of 239:41: ( declaration )*";
        }
    }
    static final String DFA121_eotS =
        "\55\uffff";
    static final String DFA121_eofS =
        "\55\uffff";
    static final String DFA121_minS =
        "\1\25\51\uffff\1\0\2\uffff";
    static final String DFA121_maxS =
        "\1\u0081\51\uffff\1\0\2\uffff";
    static final String DFA121_acceptS =
        "\1\uffff\1\1\52\uffff\1\2";
    static final String DFA121_specialS =
        "\52\uffff\1\0\2\uffff}>";
    static final String[] DFA121_transitionS = {
            "\10\1\14\uffff\1\1\7\uffff\2\1\1\uffff\16\1\1\52\2\1\1\uffff"+
            "\3\1\2\uffff\1\1\1\uffff\2\1\2\uffff\3\1\2\uffff\3\1\27\uffff"+
            "\4\1\1\uffff\4\1\1\uffff\10\1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            ""
    };

    static final short[] DFA121_eot = DFA.unpackEncodedString(DFA121_eotS);
    static final short[] DFA121_eof = DFA.unpackEncodedString(DFA121_eofS);
    static final char[] DFA121_min = DFA.unpackEncodedStringToUnsignedChars(DFA121_minS);
    static final char[] DFA121_max = DFA.unpackEncodedStringToUnsignedChars(DFA121_maxS);
    static final short[] DFA121_accept = DFA.unpackEncodedString(DFA121_acceptS);
    static final short[] DFA121_special = DFA.unpackEncodedString(DFA121_specialS);
    static final short[][] DFA121_transition;

    static {
        int numStates = DFA121_transitionS.length;
        DFA121_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA121_transition[i] = DFA.unpackEncodedString(DFA121_transitionS[i]);
        }
    }

    class DFA121 extends DFA {

        public DFA121(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 121;
            this.eot = DFA121_eot;
            this.eof = DFA121_eof;
            this.min = DFA121_min;
            this.max = DFA121_max;
            this.accept = DFA121_accept;
            this.special = DFA121_special;
            this.transition = DFA121_transition;
        }
        public String getDescription() {
            return "1100:9: ( compound_statement )?";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA121_42 = input.LA(1);

                         
                        int index121_42 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred165_PretC()) ) {s = 1;}

                        else if ( (true) ) {s = 44;}

                         
                        input.seek(index121_42);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 121, _s, input);
            error(nvae);
            throw nvae;
        }
    }
 

    public static final BitSet FOLLOW_external_declaration_in_translation_unit251 = new BitSet(new long[]{0xFFF70D0000A00002L,0x00000000000009D9L});
    public static final BitSet FOLLOW_function_definition_in_external_declaration305 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_in_external_declaration312 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_40_in_external_declaration327 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_external_declaration329 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_external_declaration331 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_42_in_external_declaration346 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_declaration_specifiers_in_external_declaration348 = new BitSet(new long[]{0xFFE6000000200000L,0x00000000000009D9L});
    public static final BitSet FOLLOW_reactive_declarator_in_external_declaration350 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_external_declaration352 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_43_in_external_declaration372 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_declaration_specifiers_in_external_declaration374 = new BitSet(new long[]{0xFFE6000000200000L,0x00000000000009D9L});
    public static final BitSet FOLLOW_reactive_declarator_in_external_declaration376 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_external_declaration378 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_thread_definition_in_external_declaration397 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declarator_in_reactive_declarator412 = new BitSet(new long[]{0x0000700000000002L});
    public static final BitSet FOLLOW_44_in_reactive_declarator417 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6802L});
    public static final BitSet FOLLOW_initializer_in_reactive_declarator419 = new BitSet(new long[]{0x0000600000000002L});
    public static final BitSet FOLLOW_range_declarator_in_reactive_declarator423 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_45_in_reactive_declarator428 = new BitSet(new long[]{0xFFE6000000200000L,0x00000000000009D9L});
    public static final BitSet FOLLOW_declarator_in_reactive_declarator434 = new BitSet(new long[]{0x0000700000000002L});
    public static final BitSet FOLLOW_44_in_reactive_declarator439 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6802L});
    public static final BitSet FOLLOW_initializer_in_reactive_declarator441 = new BitSet(new long[]{0x0000600000000002L});
    public static final BitSet FOLLOW_range_declarator_in_reactive_declarator445 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_46_in_range_declarator459 = new BitSet(new long[]{0x0000000000400000L});
    public static final BitSet FOLLOW_DECIMAL_LITERAL_in_range_declarator463 = new BitSet(new long[]{0x0000800000000000L});
    public static final BitSet FOLLOW_47_in_range_declarator465 = new BitSet(new long[]{0x0000000000400000L});
    public static final BitSet FOLLOW_DECIMAL_LITERAL_in_range_declarator469 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_48_in_thread_definition494 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_thread_definition496 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_thread_definition498 = new BitSet(new long[]{0x000C000000000000L});
    public static final BitSet FOLLOW_50_in_thread_definition500 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_thread_definition503 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000002L});
    public static final BitSet FOLLOW_scope_statement_in_thread_definition505 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_specifiers_in_function_definition561 = new BitSet(new long[]{0xFFE6000000200000L,0x00000000000009D9L});
    public static final BitSet FOLLOW_declarator_in_function_definition573 = new BitSet(new long[]{0xFFF4000000A00000L,0x00000000000001DBL});
    public static final BitSet FOLLOW_declaration_in_function_definition582 = new BitSet(new long[]{0xFFF4000000A00000L,0x00000000000001DBL});
    public static final BitSet FOLLOW_scope_statement_in_function_definition585 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_scope_statement_in_function_definition595 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_52_in_declaration663 = new BitSet(new long[]{0xFFE6000000200000L,0x00000000000009D9L});
    public static final BitSet FOLLOW_declaration_specifiers_in_declaration667 = new BitSet(new long[]{0xFFE6000000200000L,0x00000000000009D9L});
    public static final BitSet FOLLOW_init_declarator_list_in_declaration675 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_declaration677 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_specifiers_in_declaration706 = new BitSet(new long[]{0xFFE6020000200000L,0x00000000000009D9L});
    public static final BitSet FOLLOW_init_declarator_list_in_declaration709 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_declaration715 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_LINE_COMMAND_in_declaration738 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_storage_class_specifier_in_declaration_specifiers768 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_type_qualifier_in_declaration_specifiers785 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_type_specifier_in_declaration_specifiers818 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_init_declarator_in_init_declarator_list866 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_45_in_init_declarator_list869 = new BitSet(new long[]{0xFFE6000000200000L,0x00000000000009D9L});
    public static final BitSet FOLLOW_init_declarator_in_init_declarator_list872 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_declarator_in_init_declarator889 = new BitSet(new long[]{0x0000500000000002L});
    public static final BitSet FOLLOW_44_in_init_declarator892 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6802L});
    public static final BitSet FOLLOW_initializer_in_init_declarator894 = new BitSet(new long[]{0x0000400000000002L});
    public static final BitSet FOLLOW_range_declarator_in_init_declarator899 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_storage_class_specifier0 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_50_in_type_specifier951 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_57_in_type_specifier968 = new BitSet(new long[]{0x0800000000000000L});
    public static final BitSet FOLLOW_58_in_type_specifier972 = new BitSet(new long[]{0x0800000000000000L});
    public static final BitSet FOLLOW_59_in_type_specifier977 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_57_in_type_specifier985 = new BitSet(new long[]{0x1000000000000000L});
    public static final BitSet FOLLOW_58_in_type_specifier989 = new BitSet(new long[]{0x1000000000000000L});
    public static final BitSet FOLLOW_60_in_type_specifier994 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_57_in_type_specifier1002 = new BitSet(new long[]{0x2000000000000000L});
    public static final BitSet FOLLOW_58_in_type_specifier1006 = new BitSet(new long[]{0x2000000000000000L});
    public static final BitSet FOLLOW_61_in_type_specifier1011 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_57_in_type_specifier1020 = new BitSet(new long[]{0x4000000000000000L});
    public static final BitSet FOLLOW_58_in_type_specifier1024 = new BitSet(new long[]{0x4000000000000000L});
    public static final BitSet FOLLOW_62_in_type_specifier1029 = new BitSet(new long[]{0x4000000000000000L});
    public static final BitSet FOLLOW_62_in_type_specifier1031 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_57_in_type_specifier1039 = new BitSet(new long[]{0x4000000000000000L});
    public static final BitSet FOLLOW_58_in_type_specifier1043 = new BitSet(new long[]{0x4000000000000000L});
    public static final BitSet FOLLOW_62_in_type_specifier1048 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_63_in_type_specifier1055 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_64_in_type_specifier1070 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_struct_or_union_specifier_in_type_specifier1089 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_enum_specifier_in_type_specifier1096 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_type_id_in_type_specifier1105 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declared_id_in_type_specifier1116 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_IDENTIFIER_in_type_id1137 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_IDENTIFIER_in_declared_id1164 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_struct_or_union_in_struct_or_union_specifier1209 = new BitSet(new long[]{0x0000000000200000L,0x0000000000000002L});
    public static final BitSet FOLLOW_IDENTIFIER_in_struct_or_union_specifier1214 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000002L});
    public static final BitSet FOLLOW_65_in_struct_or_union_specifier1219 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_struct_declaration_list_in_struct_or_union_specifier1221 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000004L});
    public static final BitSet FOLLOW_66_in_struct_or_union_specifier1223 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_struct_or_union_in_struct_or_union_specifier1228 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_struct_or_union_specifier1232 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_67_in_struct_or_union1253 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_68_in_struct_or_union1260 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_struct_declaration_in_struct_declaration_list1291 = new BitSet(new long[]{0xFFE4000000200002L,0x00000000000001D9L});
    public static final BitSet FOLLOW_struct_declaration_in_struct_declaration_list1296 = new BitSet(new long[]{0xFFE4000000200002L,0x00000000000001D9L});
    public static final BitSet FOLLOW_specifier_qualifier_list_in_struct_declaration1318 = new BitSet(new long[]{0xFFE6020000200000L,0x00000000000009F9L});
    public static final BitSet FOLLOW_struct_declarator_list_in_struct_declaration1321 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_struct_declaration1325 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_type_qualifier_in_specifier_qualifier_list1346 = new BitSet(new long[]{0xFFE4000000200002L,0x00000000000001D9L});
    public static final BitSet FOLLOW_type_specifier_in_specifier_qualifier_list1352 = new BitSet(new long[]{0xFFE4000000200002L,0x00000000000001D9L});
    public static final BitSet FOLLOW_struct_declarator_in_struct_declarator_list1371 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_45_in_struct_declarator_list1374 = new BitSet(new long[]{0xFFE6000000200000L,0x00000000000009F9L});
    public static final BitSet FOLLOW_struct_declarator_in_struct_declarator_list1379 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_declarator_in_struct_declarator1394 = new BitSet(new long[]{0x0000400000000002L,0x0000000000000020L});
    public static final BitSet FOLLOW_69_in_struct_declarator1397 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_constant_expression_in_struct_declarator1399 = new BitSet(new long[]{0x0000400000000002L});
    public static final BitSet FOLLOW_range_declarator_in_struct_declarator1404 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_69_in_struct_declarator1415 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_constant_expression_in_struct_declarator1417 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_70_in_enum_specifier1436 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000002L});
    public static final BitSet FOLLOW_65_in_enum_specifier1438 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_enumerator_list_in_enum_specifier1440 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000004L});
    public static final BitSet FOLLOW_66_in_enum_specifier1442 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_70_in_enum_specifier1448 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_enum_specifier1450 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000002L});
    public static final BitSet FOLLOW_65_in_enum_specifier1452 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_enumerator_list_in_enum_specifier1454 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000004L});
    public static final BitSet FOLLOW_66_in_enum_specifier1456 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_70_in_enum_specifier1461 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_enum_specifier1463 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_enumerator_in_enumerator_list1474 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_45_in_enumerator_list1477 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_enumerator_in_enumerator_list1479 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_IDENTIFIER_in_enumerator1492 = new BitSet(new long[]{0x0000100000000002L});
    public static final BitSet FOLLOW_44_in_enumerator1495 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_constant_expression_in_enumerator1497 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_type_qualifier0 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_pointer_in_declarator1526 = new BitSet(new long[]{0x0002000000200000L,0x0000000000000800L});
    public static final BitSet FOLLOW_direct_declarator_in_declarator1529 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_pointer_in_declarator1534 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_IDENTIFIER_in_direct_declarator1548 = new BitSet(new long[]{0x0002000000000002L,0x0000000000000200L});
    public static final BitSet FOLLOW_declarator_suffix_in_direct_declarator1559 = new BitSet(new long[]{0x0002000000000002L,0x0000000000000200L});
    public static final BitSet FOLLOW_49_in_direct_declarator1578 = new BitSet(new long[]{0xFFE6000000200000L,0x00000000000009D9L});
    public static final BitSet FOLLOW_declarator_in_direct_declarator1580 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_direct_declarator1582 = new BitSet(new long[]{0x0002000000000002L,0x0000000000000200L});
    public static final BitSet FOLLOW_declarator_suffix_in_direct_declarator1584 = new BitSet(new long[]{0x0002000000000002L,0x0000000000000200L});
    public static final BitSet FOLLOW_73_in_declarator_suffix1609 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_constant_expression_in_declarator_suffix1611 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000400L});
    public static final BitSet FOLLOW_74_in_declarator_suffix1613 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_73_in_declarator_suffix1623 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000400L});
    public static final BitSet FOLLOW_74_in_declarator_suffix1625 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_49_in_declarator_suffix1635 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_parameter_type_list_in_declarator_suffix1637 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_declarator_suffix1639 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_49_in_declarator_suffix1649 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_identifier_list_in_declarator_suffix1651 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_declarator_suffix1653 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_49_in_declarator_suffix1663 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_declarator_suffix1665 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_75_in_pointer1676 = new BitSet(new long[]{0x01E0000000000000L,0x0000000000000180L});
    public static final BitSet FOLLOW_type_qualifier_in_pointer1678 = new BitSet(new long[]{0x01E0000000000002L,0x0000000000000980L});
    public static final BitSet FOLLOW_pointer_in_pointer1681 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_75_in_pointer1687 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000800L});
    public static final BitSet FOLLOW_pointer_in_pointer1689 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_75_in_pointer1694 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_parameter_list_in_parameter_type_list1705 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_45_in_parameter_type_list1708 = new BitSet(new long[]{0x0000000000000000L,0x0000000000001000L});
    public static final BitSet FOLLOW_76_in_parameter_type_list1710 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_parameter_declaration_in_parameter_list1726 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_45_in_parameter_list1736 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_parameter_declaration_in_parameter_list1740 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_declaration_specifiers_in_parameter_declaration1781 = new BitSet(new long[]{0xFFE6400000200002L,0x0000000000000BD9L});
    public static final BitSet FOLLOW_declarator_in_parameter_declaration1792 = new BitSet(new long[]{0xFFE6400000200002L,0x0000000000000BD9L});
    public static final BitSet FOLLOW_abstract_declarator_in_parameter_declaration1802 = new BitSet(new long[]{0xFFE6400000200002L,0x0000000000000BD9L});
    public static final BitSet FOLLOW_range_declarator_in_parameter_declaration1823 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_IDENTIFIER_in_identifier_list1868 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_45_in_identifier_list1871 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_identifier_list1873 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_specifier_qualifier_list_in_type_name1886 = new BitSet(new long[]{0xFFE6000000200002L,0x0000000000000BD9L});
    public static final BitSet FOLLOW_abstract_declarator_in_type_name1888 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_pointer_in_abstract_declarator1900 = new BitSet(new long[]{0xFFE6000000200002L,0x0000000000000BD9L});
    public static final BitSet FOLLOW_direct_abstract_declarator_in_abstract_declarator1902 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_direct_abstract_declarator_in_abstract_declarator1908 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_49_in_direct_abstract_declarator1921 = new BitSet(new long[]{0xFFE6000000200000L,0x0000000000000BD9L});
    public static final BitSet FOLLOW_abstract_declarator_in_direct_abstract_declarator1923 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_direct_abstract_declarator1925 = new BitSet(new long[]{0xFFE6000000200002L,0x0000000000000BD9L});
    public static final BitSet FOLLOW_abstract_declarator_suffix_in_direct_abstract_declarator1929 = new BitSet(new long[]{0xFFE6000000200002L,0x0000000000000BD9L});
    public static final BitSet FOLLOW_abstract_declarator_suffix_in_direct_abstract_declarator1933 = new BitSet(new long[]{0xFFE6000000200002L,0x0000000000000BD9L});
    public static final BitSet FOLLOW_73_in_abstract_declarator_suffix1945 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000400L});
    public static final BitSet FOLLOW_74_in_abstract_declarator_suffix1947 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_73_in_abstract_declarator_suffix1952 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_constant_expression_in_abstract_declarator_suffix1954 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000400L});
    public static final BitSet FOLLOW_74_in_abstract_declarator_suffix1956 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_49_in_abstract_declarator_suffix1961 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_abstract_declarator_suffix1963 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_49_in_abstract_declarator_suffix1968 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_parameter_type_list_in_abstract_declarator_suffix1970 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_abstract_declarator_suffix1972 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_assignment_expression_in_initializer1984 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_65_in_initializer1989 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6802L});
    public static final BitSet FOLLOW_initializer_list_in_initializer1991 = new BitSet(new long[]{0x0000200000000000L,0x0000000000000004L});
    public static final BitSet FOLLOW_45_in_initializer1993 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000004L});
    public static final BitSet FOLLOW_66_in_initializer1996 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_initializer_in_initializer_list2007 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_45_in_initializer_list2010 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6802L});
    public static final BitSet FOLLOW_initializer_in_initializer_list2012 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_assignment_expression_in_argument_expression_list2029 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_45_in_argument_expression_list2032 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_assignment_expression_in_argument_expression_list2034 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_multiplicative_expression_in_additive_expression2048 = new BitSet(new long[]{0x0000000000000002L,0x0000000000006000L});
    public static final BitSet FOLLOW_77_in_additive_expression2052 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_multiplicative_expression_in_additive_expression2054 = new BitSet(new long[]{0x0000000000000002L,0x0000000000006000L});
    public static final BitSet FOLLOW_78_in_additive_expression2058 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_multiplicative_expression_in_additive_expression2060 = new BitSet(new long[]{0x0000000000000002L,0x0000000000006000L});
    public static final BitSet FOLLOW_cast_expression_in_multiplicative_expression2074 = new BitSet(new long[]{0x0000000000000002L,0x0000000000018800L});
    public static final BitSet FOLLOW_75_in_multiplicative_expression2078 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_cast_expression_in_multiplicative_expression2080 = new BitSet(new long[]{0x0000000000000002L,0x0000000000018800L});
    public static final BitSet FOLLOW_79_in_multiplicative_expression2084 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_cast_expression_in_multiplicative_expression2086 = new BitSet(new long[]{0x0000000000000002L,0x0000000000018800L});
    public static final BitSet FOLLOW_80_in_multiplicative_expression2090 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_cast_expression_in_multiplicative_expression2092 = new BitSet(new long[]{0x0000000000000002L,0x0000000000018800L});
    public static final BitSet FOLLOW_49_in_cast_expression2105 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_type_name_in_cast_expression2107 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_cast_expression2109 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_cast_expression_in_cast_expression2111 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_unary_expression_in_cast_expression2116 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_postfix_expression_in_unary_expression2127 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_81_in_unary_expression2132 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_unary_expression_in_unary_expression2134 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_82_in_unary_expression2143 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_unary_expression_in_unary_expression2145 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_unary_operator_in_unary_expression2154 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_cast_expression_in_unary_expression2156 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_83_in_unary_expression2161 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_unary_expression_in_unary_expression2163 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_83_in_unary_expression2168 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_unary_expression2170 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_type_name_in_unary_expression2172 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_unary_expression2174 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_primary_expression_in_postfix_expression2187 = new BitSet(new long[]{0x0002000000000002L,0x0000000000360200L});
    public static final BitSet FOLLOW_73_in_postfix_expression2201 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_postfix_expression2203 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000400L});
    public static final BitSet FOLLOW_74_in_postfix_expression2205 = new BitSet(new long[]{0x0002000000000002L,0x0000000000360200L});
    public static final BitSet FOLLOW_49_in_postfix_expression2219 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_postfix_expression2221 = new BitSet(new long[]{0x0002000000000002L,0x0000000000360200L});
    public static final BitSet FOLLOW_49_in_postfix_expression2235 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_argument_expression_list_in_postfix_expression2237 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_postfix_expression2239 = new BitSet(new long[]{0x0002000000000002L,0x0000000000360200L});
    public static final BitSet FOLLOW_84_in_postfix_expression2253 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_postfix_expression2257 = new BitSet(new long[]{0x0002000000000002L,0x0000000000360200L});
    public static final BitSet FOLLOW_85_in_postfix_expression2273 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_postfix_expression2277 = new BitSet(new long[]{0x0002000000000002L,0x0000000000360200L});
    public static final BitSet FOLLOW_81_in_postfix_expression2293 = new BitSet(new long[]{0x0002000000000002L,0x0000000000360200L});
    public static final BitSet FOLLOW_82_in_postfix_expression2310 = new BitSet(new long[]{0x0002000000000002L,0x0000000000360200L});
    public static final BitSet FOLLOW_set_in_unary_operator0 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_IDENTIFIER_in_primary_expression2371 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_constant_in_primary_expression2378 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_49_in_primary_expression2383 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_primary_expression2385 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_primary_expression2387 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_constant0 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_assignment_expression_in_expression2466 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_45_in_expression2471 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_assignment_expression_in_expression2476 = new BitSet(new long[]{0x0000200000000002L});
    public static final BitSet FOLLOW_conditional_expression_in_constant_expression2490 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_lvalue_in_assignment_expression2503 = new BitSet(new long[]{0x0000100000000000L,0x00000007FE000000L});
    public static final BitSet FOLLOW_assignment_operator_in_assignment_expression2505 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_assignment_expression_in_assignment_expression2507 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_constant_expression_in_assignment_expression2516 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_unary_expression_in_lvalue2532 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_assignment_operator0 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_logical_or_expression_in_conditional_expression2604 = new BitSet(new long[]{0x0000000000000002L,0x0000000800000000L});
    public static final BitSet FOLLOW_99_in_conditional_expression2607 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_conditional_expression2609 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000020L});
    public static final BitSet FOLLOW_69_in_conditional_expression2611 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_conditional_expression_in_conditional_expression2613 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_logical_and_expression_in_logical_or_expression2626 = new BitSet(new long[]{0x0000000000000002L,0x0000001000000000L});
    public static final BitSet FOLLOW_100_in_logical_or_expression2629 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_logical_and_expression_in_logical_or_expression2631 = new BitSet(new long[]{0x0000000000000002L,0x0000001000000000L});
    public static final BitSet FOLLOW_inclusive_or_expression_in_logical_and_expression2644 = new BitSet(new long[]{0x0000000000000002L,0x0000002000000000L});
    public static final BitSet FOLLOW_101_in_logical_and_expression2647 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_inclusive_or_expression_in_logical_and_expression2649 = new BitSet(new long[]{0x0000000000000002L,0x0000002000000000L});
    public static final BitSet FOLLOW_exclusive_or_expression_in_inclusive_or_expression2662 = new BitSet(new long[]{0x0000000000000002L,0x0000004000000000L});
    public static final BitSet FOLLOW_102_in_inclusive_or_expression2665 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_exclusive_or_expression_in_inclusive_or_expression2667 = new BitSet(new long[]{0x0000000000000002L,0x0000004000000000L});
    public static final BitSet FOLLOW_and_expression_in_exclusive_or_expression2680 = new BitSet(new long[]{0x0000000000000002L,0x0000008000000000L});
    public static final BitSet FOLLOW_103_in_exclusive_or_expression2683 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_and_expression_in_exclusive_or_expression2685 = new BitSet(new long[]{0x0000000000000002L,0x0000008000000000L});
    public static final BitSet FOLLOW_equality_expression_in_and_expression2698 = new BitSet(new long[]{0x0000000000000002L,0x0000000000400000L});
    public static final BitSet FOLLOW_86_in_and_expression2701 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_equality_expression_in_and_expression2703 = new BitSet(new long[]{0x0000000000000002L,0x0000000000400000L});
    public static final BitSet FOLLOW_relational_expression_in_equality_expression2715 = new BitSet(new long[]{0x0000000000000002L,0x0000030000000000L});
    public static final BitSet FOLLOW_set_in_equality_expression2718 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_relational_expression_in_equality_expression2724 = new BitSet(new long[]{0x0000000000000002L,0x0000030000000000L});
    public static final BitSet FOLLOW_shift_expression_in_relational_expression2737 = new BitSet(new long[]{0x0000000000000002L,0x00003C0000000000L});
    public static final BitSet FOLLOW_set_in_relational_expression2740 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_shift_expression_in_relational_expression2750 = new BitSet(new long[]{0x0000000000000002L,0x00003C0000000000L});
    public static final BitSet FOLLOW_additive_expression_in_shift_expression2766 = new BitSet(new long[]{0x0000000000000002L,0x0000C00000000000L});
    public static final BitSet FOLLOW_set_in_shift_expression2769 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_additive_expression_in_shift_expression2775 = new BitSet(new long[]{0x0000000000000002L,0x0000C00000000000L});
    public static final BitSet FOLLOW_labeled_statement_in_statement2800 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_expression_statement_in_statement2823 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_selection_statement_in_statement2829 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_iteration_statement_in_statement2835 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_jump_statement_in_statement2841 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_parallel_statement_in_statement2864 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_112_in_statement2870 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_statement2872 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_preemption_statment_in_statement2894 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_scope_statement_in_statement2899 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_IDENTIFIER_in_labeled_statement2910 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000020L});
    public static final BitSet FOLLOW_69_in_labeled_statement2912 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_113_in_labeled_statement2932 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_constant_expression_in_labeled_statement2934 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000020L});
    public static final BitSet FOLLOW_69_in_labeled_statement2936 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_114_in_labeled_statement2957 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000020L});
    public static final BitSet FOLLOW_69_in_labeled_statement2959 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_65_in_scope_statement3001 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000004L});
    public static final BitSet FOLLOW_66_in_scope_statement3011 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_65_in_scope_statement3027 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DFL,0x0000000000000003L});
    public static final BitSet FOLLOW_compound_statement_in_scope_statement3038 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000004L});
    public static final BitSet FOLLOW_66_in_scope_statement3040 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_scope_statement_in_condition_statement3084 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_in_condition_statement3091 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_statement_in_condition_statement3093 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_in_compound_statement3139 = new BitSet(new long[]{0xFFF602001FE00002L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_statement_list_in_compound_statement3141 = new BitSet(new long[]{0xFFF602001FE00002L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_statement_in_statement_list3156 = new BitSet(new long[]{0xFFF602001FE00002L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_115_in_preemption_statment3174 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_condition_statement_in_preemption_statment3180 = new BitSet(new long[]{0x0000000000000000L,0x0010000000000000L});
    public static final BitSet FOLLOW_116_in_preemption_statment3182 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_preemption_statment3184 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_preemption_statment3186 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_preemption_statment3188 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_preemption_statment3190 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_117_in_preemption_statment3222 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_condition_statement_in_preemption_statment3228 = new BitSet(new long[]{0x0000000000000000L,0x0010000000000000L});
    public static final BitSet FOLLOW_116_in_preemption_statment3230 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_preemption_statment3232 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_preemption_statment3234 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_preemption_statment3236 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_preemption_statment3238 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_118_in_preemption_statment3270 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_condition_statement_in_preemption_statment3277 = new BitSet(new long[]{0x0000000000000000L,0x0010000000000000L});
    public static final BitSet FOLLOW_116_in_preemption_statment3279 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_preemption_statment3281 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_preemption_statment3283 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_preemption_statment3285 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_preemption_statment3287 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_119_in_parallel_statement3331 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_parallel_statement3333 = new BitSet(new long[]{0x0004000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_parallel_statement3344 = new BitSet(new long[]{0x0000200000000000L});
    public static final BitSet FOLLOW_50_in_parallel_statement3360 = new BitSet(new long[]{0x0000200000000000L});
    public static final BitSet FOLLOW_45_in_parallel_statement3398 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_parallel_statement3402 = new BitSet(new long[]{0x0008200000000000L});
    public static final BitSet FOLLOW_45_in_parallel_statement3425 = new BitSet(new long[]{0x0004000000000000L});
    public static final BitSet FOLLOW_50_in_parallel_statement3427 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_parallel_statement3442 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_parallel_statement3444 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_41_in_expression_statement3485 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_expression_in_expression_statement3509 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_expression_statement3511 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_120_in_selection_statement3547 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_selection_statement3549 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_selection_statement3551 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_selection_statement3553 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_condition_statement_in_selection_statement3572 = new BitSet(new long[]{0x0000000000000002L,0x0200000000000000L});
    public static final BitSet FOLLOW_121_in_selection_statement3594 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_condition_statement_in_selection_statement3618 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_122_in_selection_statement3687 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_selection_statement3689 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_selection_statement3691 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_selection_statement3693 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_condition_statement_in_selection_statement3712 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_123_in_iteration_statement3756 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_iteration_statement3758 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_iteration_statement3760 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_iteration_statement3762 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69FBL,0x0000000000000003L});
    public static final BitSet FOLLOW_69_in_iteration_statement3771 = new BitSet(new long[]{0x0000000000400000L});
    public static final BitSet FOLLOW_DECIMAL_LITERAL_in_iteration_statement3773 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_condition_statement_in_iteration_statement3785 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_124_in_iteration_statement3815 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69FBL,0x0000000000000003L});
    public static final BitSet FOLLOW_69_in_iteration_statement3818 = new BitSet(new long[]{0x0000000000400000L});
    public static final BitSet FOLLOW_DECIMAL_LITERAL_in_iteration_statement3820 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_condition_statement_in_iteration_statement3832 = new BitSet(new long[]{0x0000000000000000L,0x0800000000000000L});
    public static final BitSet FOLLOW_123_in_iteration_statement3834 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_iteration_statement3836 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_iteration_statement3838 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_iteration_statement3840 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_iteration_statement3842 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_125_in_iteration_statement3875 = new BitSet(new long[]{0x0002000000000000L});
    public static final BitSet FOLLOW_49_in_iteration_statement3877 = new BitSet(new long[]{0x000202001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_iteration_statement3884 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_iteration_statement3893 = new BitSet(new long[]{0x000202001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_iteration_statement3913 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_iteration_statement3923 = new BitSet(new long[]{0x000A00001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_iteration_statement3955 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_iteration_statement3964 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69FBL,0x0000000000000003L});
    public static final BitSet FOLLOW_69_in_iteration_statement3981 = new BitSet(new long[]{0x0000000000400000L});
    public static final BitSet FOLLOW_DECIMAL_LITERAL_in_iteration_statement3983 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DBL,0x0000000000000003L});
    public static final BitSet FOLLOW_condition_statement_in_iteration_statement3999 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_126_in_jump_statement4029 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_IDENTIFIER_in_jump_statement4031 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_jump_statement4033 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_127_in_jump_statement4043 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_jump_statement4045 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_128_in_jump_statement4054 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_jump_statement4056 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_129_in_jump_statement4065 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_jump_statement4067 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_129_in_jump_statement4076 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_expression_in_jump_statement4078 = new BitSet(new long[]{0x0000020000000000L});
    public static final BitSet FOLLOW_41_in_jump_statement4080 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_specifiers_in_synpred2_PretC292 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_specifiers_in_synpred4_PretC292 = new BitSet(new long[]{0xFFE6000000200000L,0x00000000000009D9L});
    public static final BitSet FOLLOW_declarator_in_synpred4_PretC295 = new BitSet(new long[]{0xFFF4000000A00000L,0x00000000000001DBL});
    public static final BitSet FOLLOW_declaration_in_synpred4_PretC297 = new BitSet(new long[]{0xFFF4000000A00000L,0x00000000000001DBL});
    public static final BitSet FOLLOW_65_in_synpred4_PretC300 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_in_synpred5_PretC312 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_specifiers_in_synpred15_PretC561 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_specifiers_in_synpred18_PretC667 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_synpred42_PretC1019 = new BitSet(new long[]{0x4000000000000000L});
    public static final BitSet FOLLOW_62_in_synpred42_PretC1029 = new BitSet(new long[]{0x4000000000000000L});
    public static final BitSet FOLLOW_62_in_synpred42_PretC1031 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_synpred45_PretC1038 = new BitSet(new long[]{0x4000000000000000L});
    public static final BitSet FOLLOW_62_in_synpred45_PretC1048 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_type_id_in_synpred50_PretC1105 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_type_specifier_in_synpred57_PretC1352 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_pointer_in_synpred68_PretC1526 = new BitSet(new long[]{0x0002000000200000L,0x0000000000000800L});
    public static final BitSet FOLLOW_direct_declarator_in_synpred68_PretC1529 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declarator_suffix_in_synpred69_PretC1559 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declarator_suffix_in_synpred71_PretC1584 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_49_in_synpred74_PretC1635 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_parameter_type_list_in_synpred74_PretC1637 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_synpred74_PretC1639 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_49_in_synpred75_PretC1649 = new BitSet(new long[]{0x0000000000200000L});
    public static final BitSet FOLLOW_identifier_list_in_synpred75_PretC1651 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_synpred75_PretC1653 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_type_qualifier_in_synpred76_PretC1678 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_pointer_in_synpred77_PretC1681 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_75_in_synpred78_PretC1676 = new BitSet(new long[]{0x01E0000000000000L,0x0000000000000180L});
    public static final BitSet FOLLOW_type_qualifier_in_synpred78_PretC1678 = new BitSet(new long[]{0x01E0000000000002L,0x0000000000000980L});
    public static final BitSet FOLLOW_pointer_in_synpred78_PretC1681 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_75_in_synpred79_PretC1687 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000800L});
    public static final BitSet FOLLOW_pointer_in_synpred79_PretC1689 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declarator_in_synpred82_PretC1792 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_abstract_declarator_in_synpred83_PretC1802 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_direct_abstract_declarator_in_synpred87_PretC1902 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_abstract_declarator_suffix_in_synpred90_PretC1933 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_49_in_synpred103_PretC2105 = new BitSet(new long[]{0xFFE4000000200000L,0x00000000000001D9L});
    public static final BitSet FOLLOW_type_name_in_synpred103_PretC2107 = new BitSet(new long[]{0x0008000000000000L});
    public static final BitSet FOLLOW_51_in_synpred103_PretC2109 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_cast_expression_in_synpred103_PretC2111 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_83_in_synpred108_PretC2161 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_unary_expression_in_synpred108_PretC2163 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_lvalue_in_synpred129_PretC2503 = new BitSet(new long[]{0x0000100000000000L,0x00000007FE000000L});
    public static final BitSet FOLLOW_assignment_operator_in_synpred129_PretC2505 = new BitSet(new long[]{0x000200001F600000L,0x0000000001CE6800L});
    public static final BitSet FOLLOW_assignment_expression_in_synpred129_PretC2507 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_65_in_synpred164_PretC3001 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000004L});
    public static final BitSet FOLLOW_66_in_synpred164_PretC3011 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_compound_statement_in_synpred165_PretC3077 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_65_in_synpred166_PretC3075 = new BitSet(new long[]{0xFFF602001FE00000L,0xFDEF000001CE69DFL,0x0000000000000003L});
    public static final BitSet FOLLOW_compound_statement_in_synpred166_PretC3077 = new BitSet(new long[]{0x0000000000000000L,0x0000000000000004L});
    public static final BitSet FOLLOW_66_in_synpred166_PretC3080 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_in_synpred167_PretC3091 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_declaration_in_synpred168_PretC3139 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_statement_list_in_synpred169_PretC3141 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_statement_in_synpred170_PretC3156 = new BitSet(new long[]{0x0000000000000002L});

}