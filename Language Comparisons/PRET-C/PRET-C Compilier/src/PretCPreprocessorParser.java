// $ANTLR 3.1.2 D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g 2011-11-24 17:30:00

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

public class PretCPreprocessorParser extends Parser {
    public static final String[] tokenNames = new String[] {
        "<invalid>", "<EOR>", "<DOWN>", "<UP>", "TOK", "THD_TOK", "SCP_TOK", "FUN_TOK", "IDENTIFIER", "WILDCARD", "LETTER", "WS", "COMMENT", "LINE_COMMENT", "'{'", "'}'", "'thread'", "'('", "'void'", "')'", "';'", "':'", "','", "'PAR'"
    };
    public static final int FUN_TOK=7;
    public static final int LINE_COMMENT=13;
    public static final int LETTER=10;
    public static final int T__23=23;
    public static final int T__22=22;
    public static final int T__21=21;
    public static final int T__20=20;
    public static final int EOF=-1;
    public static final int THD_TOK=5;
    public static final int T__19=19;
    public static final int WS=11;
    public static final int T__16=16;
    public static final int T__15=15;
    public static final int T__18=18;
    public static final int T__17=17;
    public static final int T__14=14;
    public static final int IDENTIFIER=8;
    public static final int WILDCARD=9;
    public static final int SCP_TOK=6;
    public static final int COMMENT=12;
    public static final int TOK=4;

    // delegates
    // delegators


        public PretCPreprocessorParser(TokenStream input) {
            this(input, new RecognizerSharedState());
        }
        public PretCPreprocessorParser(TokenStream input, RecognizerSharedState state) {
            super(input, state);
            this.state.ruleMemo = new HashMap[32+1];
             
             
        }
        
    protected TreeAdaptor adaptor = new CommonTreeAdaptor();

    public void setTreeAdaptor(TreeAdaptor adaptor) {
        this.adaptor = adaptor;
    }
    public TreeAdaptor getTreeAdaptor() {
        return adaptor;
    }

    public String[] getTokenNames() { return PretCPreprocessorParser.tokenNames; }
    public String getGrammarFileName() { return "D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g"; }


    	Hashtable threads = new Hashtable();
    	ArrayList pars = new ArrayList<String>();
    	Hashtable occurence = new Hashtable();
    	Hashtable occurenceThdCopy = new Hashtable();
    	ArrayList<String> printedThreads = new ArrayList<String>();
    	String source = "";
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
    		return "ERROR "+tokenNames[0] +" END ERROR";
    	}



    public static class translation_unit_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "translation_unit"
    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:70:1: translation_unit : ( ( external_declaration )+ ) ;
    public final PretCPreprocessorParser.translation_unit_return translation_unit() throws RecognitionException {
        PretCPreprocessorParser.translation_unit_return retval = new PretCPreprocessorParser.translation_unit_return();
        retval.start = input.LT(1);
        int translation_unit_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCPreprocessorParser.external_declaration_return external_declaration1 = null;




        	System.out.println("Parse once-------------------------------------------------------------------");
        	occurenceThdCopy = (Hashtable)occurence.clone();

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 1) ) { return retval; }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:83:2: ( ( ( external_declaration )+ ) )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:83:4: ( ( external_declaration )+ )
            {
            root_0 = (CommonTree)adaptor.nil();

            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:83:4: ( ( external_declaration )+ )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:83:5: ( external_declaration )+
            {
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:83:5: ( external_declaration )+
            int cnt1=0;
            loop1:
            do {
                int alt1=2;
                int LA1_0 = input.LA(1);

                if ( ((LA1_0>=IDENTIFIER && LA1_0<=WILDCARD)||LA1_0==14||(LA1_0>=16 && LA1_0<=23)) ) {
                    alt1=1;
                }


                switch (alt1) {
            	case 1 :
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:0:0: external_declaration
            	    {
            	    pushFollow(FOLLOW_external_declaration_in_translation_unit116);
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


            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {

              	//System.out.println(source);
              	//System.out.println("****************************************************************************");
              	//System.out.println("THREADS: = " + threads);
              	//System.out.println("****************************************************************************");
              	//System.out.println(pars);
              	//System.out.println("----------------------------------------------------------------------------");

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
        }
        return retval;
    }
    // $ANTLR end "translation_unit"

    public static class external_declaration_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "external_declaration"
    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:86:1: external_declaration : ( scope_definition -> ^( SCP_TOK scope_definition ) | line | thread_definition -> ^( THD_TOK thread_definition ) );
    public final PretCPreprocessorParser.external_declaration_return external_declaration() throws RecognitionException {
        PretCPreprocessorParser.external_declaration_return retval = new PretCPreprocessorParser.external_declaration_return();
        retval.start = input.LT(1);
        int external_declaration_StartIndex = input.index();
        CommonTree root_0 = null;

        PretCPreprocessorParser.scope_definition_return scope_definition2 = null;

        PretCPreprocessorParser.line_return line3 = null;

        PretCPreprocessorParser.thread_definition_return thread_definition4 = null;


        RewriteRuleSubtreeStream stream_scope_definition=new RewriteRuleSubtreeStream(adaptor,"rule scope_definition");
        RewriteRuleSubtreeStream stream_thread_definition=new RewriteRuleSubtreeStream(adaptor,"rule thread_definition");

        	String code = "";

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 2) ) { return retval; }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:97:2: ( scope_definition -> ^( SCP_TOK scope_definition ) | line | thread_definition -> ^( THD_TOK thread_definition ) )
            int alt2=3;
            alt2 = dfa2.predict(input);
            switch (alt2) {
                case 1 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:97:4: scope_definition
                    {
                    pushFollow(FOLLOW_scope_definition_in_external_declaration139);
                    scope_definition2=scope_definition();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_scope_definition.add(scope_definition2.getTree());
                    if ( state.backtracking==0 ) {
                      code += (scope_definition2!=null?scope_definition2.code:null);
                    }


                    // AST REWRITE
                    // elements: scope_definition
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 97:55: -> ^( SCP_TOK scope_definition )
                    {
                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:97:58: ^( SCP_TOK scope_definition )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(SCP_TOK, "SCP_TOK"), root_1);

                        adaptor.addChild(root_1, stream_scope_definition.nextTree());

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 2 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:98:4: line
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_line_in_external_declaration154);
                    line3=line();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, line3.getTree());
                    if ( state.backtracking==0 ) {

                      			code += (line3!=null?line3.code:null);
                      		
                    }

                    }
                    break;
                case 3 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:102:4: thread_definition
                    {
                    pushFollow(FOLLOW_thread_definition_in_external_declaration164);
                    thread_definition4=thread_definition();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_thread_definition.add(thread_definition4.getTree());


                    // AST REWRITE
                    // elements: thread_definition
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 102:22: -> ^( THD_TOK thread_definition )
                    {
                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:102:25: ^( THD_TOK thread_definition )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(THD_TOK, "THD_TOK"), root_1);

                        adaptor.addChild(root_1, stream_thread_definition.nextTree());

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

              	if (code.equals("")==false) { 
              		//System.out.println(code);
              		source+=code;
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
            if ( state.backtracking>0 ) { memoize(input, 2, external_declaration_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "external_declaration"

    public static class scope_definition_return extends ParserRuleReturnScope {
        public String code;
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "scope_definition"
    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:108:1: scope_definition returns [String code] : wildcard_rule '{' ( ( line ) | (fn= scope_definition ) )* '}' ;
    public final PretCPreprocessorParser.scope_definition_return scope_definition() throws RecognitionException {
        PretCPreprocessorParser.scope_definition_return retval = new PretCPreprocessorParser.scope_definition_return();
        retval.start = input.LT(1);
        int scope_definition_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal6=null;
        Token char_literal8=null;
        PretCPreprocessorParser.scope_definition_return fn = null;

        PretCPreprocessorParser.wildcard_rule_return wildcard_rule5 = null;

        PretCPreprocessorParser.line_return line7 = null;


        CommonTree char_literal6_tree=null;
        CommonTree char_literal8_tree=null;


        	retval.code = "";

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 3) ) { return retval; }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:116:2: ( wildcard_rule '{' ( ( line ) | (fn= scope_definition ) )* '}' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:116:4: wildcard_rule '{' ( ( line ) | (fn= scope_definition ) )* '}'
            {
            root_0 = (CommonTree)adaptor.nil();

            pushFollow(FOLLOW_wildcard_rule_in_scope_definition205);
            wildcard_rule5=wildcard_rule();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, wildcard_rule5.getTree());
            char_literal6=(Token)match(input,14,FOLLOW_14_in_scope_definition207); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal6_tree = (CommonTree)adaptor.create(char_literal6);
            adaptor.addChild(root_0, char_literal6_tree);
            }
            if ( state.backtracking==0 ) {
               
              			retval.code += (wildcard_rule5!=null?input.toString(wildcard_rule5.start,wildcard_rule5.stop):null)+"{\n";
              		
            }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:120:3: ( ( line ) | (fn= scope_definition ) )*
            loop3:
            do {
                int alt3=3;
                alt3 = dfa3.predict(input);
                switch (alt3) {
            	case 1 :
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:121:4: ( line )
            	    {
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:121:4: ( line )
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:122:5: line
            	    {
            	    pushFollow(FOLLOW_line_in_scope_definition228);
            	    line7=line();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, line7.getTree());
            	    if ( state.backtracking==0 ) {

            	      					retval.code +=(line7!=null?line7.code:null)+"\n";
            	      				
            	    }

            	    }


            	    }
            	    break;
            	case 2 :
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:128:4: (fn= scope_definition )
            	    {
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:128:4: (fn= scope_definition )
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:129:5: fn= scope_definition
            	    {
            	    pushFollow(FOLLOW_scope_definition_in_scope_definition258);
            	    fn=scope_definition();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, fn.getTree());
            	    if ( state.backtracking==0 ) {

            	      					retval.code +=(fn!=null?fn.code:null)+"\n";
            	      				
            	    }

            	    }


            	    }
            	    break;

            	default :
            	    break loop3;
                }
            } while (true);

            char_literal8=(Token)match(input,15,FOLLOW_15_in_scope_definition279); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal8_tree = (CommonTree)adaptor.create(char_literal8);
            adaptor.addChild(root_0, char_literal8_tree);
            }
            if ( state.backtracking==0 ) {

              			retval.code += "}\n";
              		
            }

            }

            retval.stop = input.LT(-1);

            if ( state.backtracking==0 ) {

            retval.tree = (CommonTree)adaptor.rulePostProcessing(root_0);
            adaptor.setTokenBoundaries(retval.tree, retval.start, retval.stop);
            }
            if ( state.backtracking==0 ) {

              	//System.out.println(code);
              	//retval.code+"\n";

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
            if ( state.backtracking>0 ) { memoize(input, 3, scope_definition_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "scope_definition"

    public static class thread_definition_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "thread_definition"
    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:141:1: thread_definition : 'thread' IDENTIFIER '(' 'void' ')' '{' ( ( line ) | ( scope_definition ) )* '}' ;
    public final PretCPreprocessorParser.thread_definition_return thread_definition() throws RecognitionException {
        PretCPreprocessorParser.thread_definition_return retval = new PretCPreprocessorParser.thread_definition_return();
        retval.start = input.LT(1);
        int thread_definition_StartIndex = input.index();
        CommonTree root_0 = null;

        Token string_literal9=null;
        Token IDENTIFIER10=null;
        Token char_literal11=null;
        Token string_literal12=null;
        Token char_literal13=null;
        Token char_literal14=null;
        Token char_literal17=null;
        PretCPreprocessorParser.line_return line15 = null;

        PretCPreprocessorParser.scope_definition_return scope_definition16 = null;


        CommonTree string_literal9_tree=null;
        CommonTree IDENTIFIER10_tree=null;
        CommonTree char_literal11_tree=null;
        CommonTree string_literal12_tree=null;
        CommonTree char_literal13_tree=null;
        CommonTree char_literal14_tree=null;
        CommonTree char_literal17_tree=null;


        	String code = "";
        	String id = "";
        	String lines = "";

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 4) ) { return retval; }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:147:2: ( 'thread' IDENTIFIER '(' 'void' ')' '{' ( ( line ) | ( scope_definition ) )* '}' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:147:5: 'thread' IDENTIFIER '(' 'void' ')' '{' ( ( line ) | ( scope_definition ) )* '}'
            {
            root_0 = (CommonTree)adaptor.nil();

            string_literal9=(Token)match(input,16,FOLLOW_16_in_thread_definition301); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            string_literal9_tree = (CommonTree)adaptor.create(string_literal9);
            adaptor.addChild(root_0, string_literal9_tree);
            }
            IDENTIFIER10=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_thread_definition303); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            IDENTIFIER10_tree = (CommonTree)adaptor.create(IDENTIFIER10);
            adaptor.addChild(root_0, IDENTIFIER10_tree);
            }
            char_literal11=(Token)match(input,17,FOLLOW_17_in_thread_definition305); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal11_tree = (CommonTree)adaptor.create(char_literal11);
            adaptor.addChild(root_0, char_literal11_tree);
            }
            string_literal12=(Token)match(input,18,FOLLOW_18_in_thread_definition307); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            string_literal12_tree = (CommonTree)adaptor.create(string_literal12);
            adaptor.addChild(root_0, string_literal12_tree);
            }
            char_literal13=(Token)match(input,19,FOLLOW_19_in_thread_definition309); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal13_tree = (CommonTree)adaptor.create(char_literal13);
            adaptor.addChild(root_0, char_literal13_tree);
            }
            char_literal14=(Token)match(input,14,FOLLOW_14_in_thread_definition311); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal14_tree = (CommonTree)adaptor.create(char_literal14);
            adaptor.addChild(root_0, char_literal14_tree);
            }
            if ( state.backtracking==0 ) {

              			code += "thread "+(IDENTIFIER10!=null?IDENTIFIER10.getText():null)+"(void) {\n";
              			id = (IDENTIFIER10!=null?IDENTIFIER10.getText():null);
              		
            }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:152:3: ( ( line ) | ( scope_definition ) )*
            loop4:
            do {
                int alt4=3;
                alt4 = dfa4.predict(input);
                switch (alt4) {
            	case 1 :
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:153:4: ( line )
            	    {
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:153:4: ( line )
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:154:5: line
            	    {
            	    pushFollow(FOLLOW_line_in_thread_definition332);
            	    line15=line();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, line15.getTree());
            	    if ( state.backtracking==0 ) {

            	      					code +=(line15!=null?line15.code:null)+"\n";
            	      					lines +=(line15!=null?line15.code:null)+"\n";
            	      				
            	    }

            	    }


            	    }
            	    break;
            	case 2 :
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:161:4: ( scope_definition )
            	    {
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:161:4: ( scope_definition )
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:162:5: scope_definition
            	    {
            	    pushFollow(FOLLOW_scope_definition_in_thread_definition359);
            	    scope_definition16=scope_definition();

            	    state._fsp--;
            	    if (state.failed) return retval;
            	    if ( state.backtracking==0 ) adaptor.addChild(root_0, scope_definition16.getTree());
            	    if ( state.backtracking==0 ) {

            	      					code +=(scope_definition16!=null?scope_definition16.code:null)+"\n";
            	      					lines +=(scope_definition16!=null?scope_definition16.code:null)+"\n";
            	      				
            	    }

            	    }


            	    }
            	    break;

            	default :
            	    break loop4;
                }
            } while (true);

            char_literal17=(Token)match(input,15,FOLLOW_15_in_thread_definition377); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal17_tree = (CommonTree)adaptor.create(char_literal17);
            adaptor.addChild(root_0, char_literal17_tree);
            }
            if ( state.backtracking==0 ) {

              			code += "}\n";
              			if (printedThreads.contains(id) == false) {
              				printedThreads.add(id);
              				threads.put(id,code);
              				source+=code+"\n";
              			}
              		
            }
            if ( state.backtracking==0 ) {

              			if (occurenceThdCopy.isEmpty() == false && occurenceThdCopy.get(id) != null) {
              				int count = (Integer)occurenceThdCopy.get(id);
              			
              				while (count > 1){
              					code = "";
              					code += "thread "+id+"_PRET_"+count+"(void) {\n";
              					code += lines;
              					code += "}\n";
              					if (printedThreads.contains(id+"_PRET_"+count) == false) {
              						printedThreads.add(id+"_PRET_"+count);
              						threads.put(id+"_PRET_"+count,code);
              						source+=code+"\n";
              					}
              					count--;
              					
              				}
              				occurenceThdCopy.put(id,count);
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
            if ( state.backtracking>0 ) { memoize(input, 4, thread_definition_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "thread_definition"

    public static class line_return extends ParserRuleReturnScope {
        public String code;
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "line"
    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:200:1: line returns [String code] : ( parallel_statement | wildcard_rule ( ( ';' ) | ( ':' ) ) -> ^( TOK ( wildcard_rule )? ( ';' )? ( ':' )? ) | wildcard_rule array_declare ( ( ';' ) | ( ':' ) ) -> ^( TOK ( wildcard_rule )? ( array_declare )? ( ';' )? ( ':' )? ) );
    public final PretCPreprocessorParser.line_return line() throws RecognitionException {
        PretCPreprocessorParser.line_return retval = new PretCPreprocessorParser.line_return();
        retval.start = input.LT(1);
        int line_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal20=null;
        Token char_literal21=null;
        Token char_literal24=null;
        Token char_literal25=null;
        PretCPreprocessorParser.parallel_statement_return parallel_statement18 = null;

        PretCPreprocessorParser.wildcard_rule_return wildcard_rule19 = null;

        PretCPreprocessorParser.wildcard_rule_return wildcard_rule22 = null;

        PretCPreprocessorParser.array_declare_return array_declare23 = null;


        CommonTree char_literal20_tree=null;
        CommonTree char_literal21_tree=null;
        CommonTree char_literal24_tree=null;
        CommonTree char_literal25_tree=null;
        RewriteRuleTokenStream stream_21=new RewriteRuleTokenStream(adaptor,"token 21");
        RewriteRuleTokenStream stream_20=new RewriteRuleTokenStream(adaptor,"token 20");
        RewriteRuleSubtreeStream stream_wildcard_rule=new RewriteRuleSubtreeStream(adaptor,"rule wildcard_rule");
        RewriteRuleSubtreeStream stream_array_declare=new RewriteRuleSubtreeStream(adaptor,"rule array_declare");
        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 5) ) { return retval; }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:201:2: ( parallel_statement | wildcard_rule ( ( ';' ) | ( ':' ) ) -> ^( TOK ( wildcard_rule )? ( ';' )? ( ':' )? ) | wildcard_rule array_declare ( ( ';' ) | ( ':' ) ) -> ^( TOK ( wildcard_rule )? ( array_declare )? ( ';' )? ( ':' )? ) )
            int alt7=3;
            alt7 = dfa7.predict(input);
            switch (alt7) {
                case 1 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:201:4: parallel_statement
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_parallel_statement_in_line405);
                    parallel_statement18=parallel_statement();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, parallel_statement18.getTree());
                    if ( state.backtracking==0 ) {
                      retval.code = (parallel_statement18!=null?parallel_statement18.code:null)+"\n";
                    }

                    }
                    break;
                case 2 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:202:4: wildcard_rule ( ( ';' ) | ( ':' ) )
                    {
                    pushFollow(FOLLOW_wildcard_rule_in_line412);
                    wildcard_rule19=wildcard_rule();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_wildcard_rule.add(wildcard_rule19.getTree());
                    if ( state.backtracking==0 ) {
                      	
                      			retval.code = "";
                      			if ((wildcard_rule19!=null?input.toString(wildcard_rule19.start,wildcard_rule19.stop):null) != null) {
                      				retval.code = (wildcard_rule19!=null?input.toString(wildcard_rule19.start,wildcard_rule19.stop):null);
                      			} 
                      			
                      		 
                    }
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:211:4: ( ( ';' ) | ( ':' ) )
                    int alt5=2;
                    int LA5_0 = input.LA(1);

                    if ( (LA5_0==20) ) {
                        alt5=1;
                    }
                    else if ( (LA5_0==21) ) {
                        alt5=2;
                    }
                    else {
                        if (state.backtracking>0) {state.failed=true; return retval;}
                        NoViableAltException nvae =
                            new NoViableAltException("", 5, 0, input);

                        throw nvae;
                    }
                    switch (alt5) {
                        case 1 :
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:212:5: ( ';' )
                            {
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:212:5: ( ';' )
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:212:6: ';'
                            {
                            char_literal20=(Token)match(input,20,FOLLOW_20_in_line434); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_20.add(char_literal20);

                            if ( state.backtracking==0 ) {

                              			 	retval.code +=";"+"\n";
                              			 
                            }

                            }


                            }
                            break;
                        case 2 :
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:218:5: ( ':' )
                            {
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:218:5: ( ':' )
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:218:6: ':'
                            {
                            char_literal21=(Token)match(input,21,FOLLOW_21_in_line458); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_21.add(char_literal21);

                            if ( state.backtracking==0 ) {

                              			 	retval.code +=":"+"\n";
                              			 
                            }

                            }


                            }
                            break;

                    }



                    // AST REWRITE
                    // elements: wildcard_rule, 20, 21
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 226:4: -> ^( TOK ( wildcard_rule )? ( ';' )? ( ':' )? )
                    {
                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:226:7: ^( TOK ( wildcard_rule )? ( ';' )? ( ':' )? )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(TOK, "TOK"), root_1);

                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:226:13: ( wildcard_rule )?
                        if ( stream_wildcard_rule.hasNext() ) {
                            adaptor.addChild(root_1, stream_wildcard_rule.nextTree());

                        }
                        stream_wildcard_rule.reset();
                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:226:28: ( ';' )?
                        if ( stream_20.hasNext() ) {
                            adaptor.addChild(root_1, stream_20.nextNode());

                        }
                        stream_20.reset();
                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:226:33: ( ':' )?
                        if ( stream_21.hasNext() ) {
                            adaptor.addChild(root_1, stream_21.nextNode());

                        }
                        stream_21.reset();

                        adaptor.addChild(root_0, root_1);
                        }

                    }

                    retval.tree = root_0;}
                    }
                    break;
                case 3 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:227:4: wildcard_rule array_declare ( ( ';' ) | ( ':' ) )
                    {
                    pushFollow(FOLLOW_wildcard_rule_in_line506);
                    wildcard_rule22=wildcard_rule();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_wildcard_rule.add(wildcard_rule22.getTree());
                    pushFollow(FOLLOW_array_declare_in_line508);
                    array_declare23=array_declare();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) stream_array_declare.add(array_declare23.getTree());
                    if ( state.backtracking==0 ) {
                      	
                      			retval.code = "";
                      			if ((array_declare23!=null?input.toString(array_declare23.start,array_declare23.stop):null) != null) {
                      				retval.code = (wildcard_rule22!=null?input.toString(wildcard_rule22.start,wildcard_rule22.stop):null) + (array_declare23!=null?input.toString(array_declare23.start,array_declare23.stop):null);
                      			} 
                      			
                      		 
                    }
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:236:4: ( ( ';' ) | ( ':' ) )
                    int alt6=2;
                    int LA6_0 = input.LA(1);

                    if ( (LA6_0==20) ) {
                        alt6=1;
                    }
                    else if ( (LA6_0==21) ) {
                        alt6=2;
                    }
                    else {
                        if (state.backtracking>0) {state.failed=true; return retval;}
                        NoViableAltException nvae =
                            new NoViableAltException("", 6, 0, input);

                        throw nvae;
                    }
                    switch (alt6) {
                        case 1 :
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:237:5: ( ';' )
                            {
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:237:5: ( ';' )
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:237:6: ';'
                            {
                            char_literal24=(Token)match(input,20,FOLLOW_20_in_line530); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_20.add(char_literal24);

                            if ( state.backtracking==0 ) {

                              			 	retval.code +=";"+"\n";
                              			 
                            }

                            }


                            }
                            break;
                        case 2 :
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:243:5: ( ':' )
                            {
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:243:5: ( ':' )
                            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:243:6: ':'
                            {
                            char_literal25=(Token)match(input,21,FOLLOW_21_in_line554); if (state.failed) return retval; 
                            if ( state.backtracking==0 ) stream_21.add(char_literal25);

                            if ( state.backtracking==0 ) {

                              			 	retval.code +=":"+"\n";
                              			 
                            }

                            }


                            }
                            break;

                    }



                    // AST REWRITE
                    // elements: 20, wildcard_rule, 21, array_declare
                    // token labels: 
                    // rule labels: retval
                    // token list labels: 
                    // rule list labels: 
                    // wildcard labels: 
                    if ( state.backtracking==0 ) {
                    retval.tree = root_0;
                    RewriteRuleSubtreeStream stream_retval=new RewriteRuleSubtreeStream(adaptor,"rule retval",retval!=null?retval.tree:null);

                    root_0 = (CommonTree)adaptor.nil();
                    // 249:4: -> ^( TOK ( wildcard_rule )? ( array_declare )? ( ';' )? ( ':' )? )
                    {
                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:249:7: ^( TOK ( wildcard_rule )? ( array_declare )? ( ';' )? ( ':' )? )
                        {
                        CommonTree root_1 = (CommonTree)adaptor.nil();
                        root_1 = (CommonTree)adaptor.becomeRoot((CommonTree)adaptor.create(TOK, "TOK"), root_1);

                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:249:13: ( wildcard_rule )?
                        if ( stream_wildcard_rule.hasNext() ) {
                            adaptor.addChild(root_1, stream_wildcard_rule.nextTree());

                        }
                        stream_wildcard_rule.reset();
                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:249:28: ( array_declare )?
                        if ( stream_array_declare.hasNext() ) {
                            adaptor.addChild(root_1, stream_array_declare.nextTree());

                        }
                        stream_array_declare.reset();
                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:249:43: ( ';' )?
                        if ( stream_20.hasNext() ) {
                            adaptor.addChild(root_1, stream_20.nextNode());

                        }
                        stream_20.reset();
                        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:249:48: ( ':' )?
                        if ( stream_21.hasNext() ) {
                            adaptor.addChild(root_1, stream_21.nextNode());

                        }
                        stream_21.reset();

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
            if ( state.backtracking>0 ) { memoize(input, 5, line_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "line"

    public static class array_declare_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "array_declare"
    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:253:1: array_declare : '{' array_elements '}' ;
    public final PretCPreprocessorParser.array_declare_return array_declare() throws RecognitionException {
        PretCPreprocessorParser.array_declare_return retval = new PretCPreprocessorParser.array_declare_return();
        retval.start = input.LT(1);
        int array_declare_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal26=null;
        Token char_literal28=null;
        PretCPreprocessorParser.array_elements_return array_elements27 = null;


        CommonTree char_literal26_tree=null;
        CommonTree char_literal28_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 6) ) { return retval; }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:254:2: ( '{' array_elements '}' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:254:4: '{' array_elements '}'
            {
            root_0 = (CommonTree)adaptor.nil();

            char_literal26=(Token)match(input,14,FOLLOW_14_in_array_declare608); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal26_tree = (CommonTree)adaptor.create(char_literal26);
            adaptor.addChild(root_0, char_literal26_tree);
            }
            pushFollow(FOLLOW_array_elements_in_array_declare610);
            array_elements27=array_elements();

            state._fsp--;
            if (state.failed) return retval;
            if ( state.backtracking==0 ) adaptor.addChild(root_0, array_elements27.getTree());
            char_literal28=(Token)match(input,15,FOLLOW_15_in_array_declare612); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal28_tree = (CommonTree)adaptor.create(char_literal28);
            adaptor.addChild(root_0, char_literal28_tree);
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
            if ( state.backtracking>0 ) { memoize(input, 6, array_declare_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "array_declare"

    public static class array_elements_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "array_elements"
    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:257:1: array_elements : ( array_declare ( ',' array_declare )* | '{' wildcard_rule '}' ( ',' '{' wildcard_rule '}' )* );
    public final PretCPreprocessorParser.array_elements_return array_elements() throws RecognitionException {
        PretCPreprocessorParser.array_elements_return retval = new PretCPreprocessorParser.array_elements_return();
        retval.start = input.LT(1);
        int array_elements_StartIndex = input.index();
        CommonTree root_0 = null;

        Token char_literal30=null;
        Token char_literal32=null;
        Token char_literal34=null;
        Token char_literal35=null;
        Token char_literal36=null;
        Token char_literal38=null;
        PretCPreprocessorParser.array_declare_return array_declare29 = null;

        PretCPreprocessorParser.array_declare_return array_declare31 = null;

        PretCPreprocessorParser.wildcard_rule_return wildcard_rule33 = null;

        PretCPreprocessorParser.wildcard_rule_return wildcard_rule37 = null;


        CommonTree char_literal30_tree=null;
        CommonTree char_literal32_tree=null;
        CommonTree char_literal34_tree=null;
        CommonTree char_literal35_tree=null;
        CommonTree char_literal36_tree=null;
        CommonTree char_literal38_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 7) ) { return retval; }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:258:2: ( array_declare ( ',' array_declare )* | '{' wildcard_rule '}' ( ',' '{' wildcard_rule '}' )* )
            int alt10=2;
            int LA10_0 = input.LA(1);

            if ( (LA10_0==14) ) {
                int LA10_1 = input.LA(2);

                if ( ((LA10_1>=IDENTIFIER && LA10_1<=WILDCARD)||LA10_1==15||(LA10_1>=17 && LA10_1<=19)||LA10_1==22) ) {
                    alt10=2;
                }
                else if ( (LA10_1==14) ) {
                    alt10=1;
                }
                else {
                    if (state.backtracking>0) {state.failed=true; return retval;}
                    NoViableAltException nvae =
                        new NoViableAltException("", 10, 1, input);

                    throw nvae;
                }
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 10, 0, input);

                throw nvae;
            }
            switch (alt10) {
                case 1 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:258:4: array_declare ( ',' array_declare )*
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    pushFollow(FOLLOW_array_declare_in_array_elements627);
                    array_declare29=array_declare();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, array_declare29.getTree());
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:258:18: ( ',' array_declare )*
                    loop8:
                    do {
                        int alt8=2;
                        int LA8_0 = input.LA(1);

                        if ( (LA8_0==22) ) {
                            alt8=1;
                        }


                        switch (alt8) {
                    	case 1 :
                    	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:258:19: ',' array_declare
                    	    {
                    	    char_literal30=(Token)match(input,22,FOLLOW_22_in_array_elements630); if (state.failed) return retval;
                    	    if ( state.backtracking==0 ) {
                    	    char_literal30_tree = (CommonTree)adaptor.create(char_literal30);
                    	    adaptor.addChild(root_0, char_literal30_tree);
                    	    }
                    	    pushFollow(FOLLOW_array_declare_in_array_elements632);
                    	    array_declare31=array_declare();

                    	    state._fsp--;
                    	    if (state.failed) return retval;
                    	    if ( state.backtracking==0 ) adaptor.addChild(root_0, array_declare31.getTree());

                    	    }
                    	    break;

                    	default :
                    	    break loop8;
                        }
                    } while (true);


                    }
                    break;
                case 2 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:259:4: '{' wildcard_rule '}' ( ',' '{' wildcard_rule '}' )*
                    {
                    root_0 = (CommonTree)adaptor.nil();

                    char_literal32=(Token)match(input,14,FOLLOW_14_in_array_elements639); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal32_tree = (CommonTree)adaptor.create(char_literal32);
                    adaptor.addChild(root_0, char_literal32_tree);
                    }
                    pushFollow(FOLLOW_wildcard_rule_in_array_elements641);
                    wildcard_rule33=wildcard_rule();

                    state._fsp--;
                    if (state.failed) return retval;
                    if ( state.backtracking==0 ) adaptor.addChild(root_0, wildcard_rule33.getTree());
                    char_literal34=(Token)match(input,15,FOLLOW_15_in_array_elements643); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    char_literal34_tree = (CommonTree)adaptor.create(char_literal34);
                    adaptor.addChild(root_0, char_literal34_tree);
                    }
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:259:26: ( ',' '{' wildcard_rule '}' )*
                    loop9:
                    do {
                        int alt9=2;
                        int LA9_0 = input.LA(1);

                        if ( (LA9_0==22) ) {
                            alt9=1;
                        }


                        switch (alt9) {
                    	case 1 :
                    	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:259:27: ',' '{' wildcard_rule '}'
                    	    {
                    	    char_literal35=(Token)match(input,22,FOLLOW_22_in_array_elements646); if (state.failed) return retval;
                    	    if ( state.backtracking==0 ) {
                    	    char_literal35_tree = (CommonTree)adaptor.create(char_literal35);
                    	    adaptor.addChild(root_0, char_literal35_tree);
                    	    }
                    	    char_literal36=(Token)match(input,14,FOLLOW_14_in_array_elements648); if (state.failed) return retval;
                    	    if ( state.backtracking==0 ) {
                    	    char_literal36_tree = (CommonTree)adaptor.create(char_literal36);
                    	    adaptor.addChild(root_0, char_literal36_tree);
                    	    }
                    	    pushFollow(FOLLOW_wildcard_rule_in_array_elements650);
                    	    wildcard_rule37=wildcard_rule();

                    	    state._fsp--;
                    	    if (state.failed) return retval;
                    	    if ( state.backtracking==0 ) adaptor.addChild(root_0, wildcard_rule37.getTree());
                    	    char_literal38=(Token)match(input,15,FOLLOW_15_in_array_elements652); if (state.failed) return retval;
                    	    if ( state.backtracking==0 ) {
                    	    char_literal38_tree = (CommonTree)adaptor.create(char_literal38);
                    	    adaptor.addChild(root_0, char_literal38_tree);
                    	    }

                    	    }
                    	    break;

                    	default :
                    	    break loop9;
                        }
                    } while (true);


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
            if ( state.backtracking>0 ) { memoize(input, 7, array_elements_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "array_elements"

    public static class parallel_statement_return extends ParserRuleReturnScope {
        public String code;
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "parallel_statement"
    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:262:1: parallel_statement returns [String code] : 'PAR' '(' (i1= IDENTIFIER | i1= 'void' ) ( ',' (i2= IDENTIFIER | i2= 'void' ) )+ ')' ';' ;
    public final PretCPreprocessorParser.parallel_statement_return parallel_statement() throws RecognitionException {
        PretCPreprocessorParser.parallel_statement_return retval = new PretCPreprocessorParser.parallel_statement_return();
        retval.start = input.LT(1);
        int parallel_statement_StartIndex = input.index();
        CommonTree root_0 = null;

        Token i1=null;
        Token i2=null;
        Token string_literal39=null;
        Token char_literal40=null;
        Token char_literal41=null;
        Token char_literal42=null;
        Token char_literal43=null;

        CommonTree i1_tree=null;
        CommonTree i2_tree=null;
        CommonTree string_literal39_tree=null;
        CommonTree char_literal40_tree=null;
        CommonTree char_literal41_tree=null;
        CommonTree char_literal42_tree=null;
        CommonTree char_literal43_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 8) ) { return retval; }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:263:2: ( 'PAR' '(' (i1= IDENTIFIER | i1= 'void' ) ( ',' (i2= IDENTIFIER | i2= 'void' ) )+ ')' ';' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:263:4: 'PAR' '(' (i1= IDENTIFIER | i1= 'void' ) ( ',' (i2= IDENTIFIER | i2= 'void' ) )+ ')' ';'
            {
            root_0 = (CommonTree)adaptor.nil();

            string_literal39=(Token)match(input,23,FOLLOW_23_in_parallel_statement671); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            string_literal39_tree = (CommonTree)adaptor.create(string_literal39);
            adaptor.addChild(root_0, string_literal39_tree);
            }
            char_literal40=(Token)match(input,17,FOLLOW_17_in_parallel_statement673); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal40_tree = (CommonTree)adaptor.create(char_literal40);
            adaptor.addChild(root_0, char_literal40_tree);
            }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:263:14: (i1= IDENTIFIER | i1= 'void' )
            int alt11=2;
            int LA11_0 = input.LA(1);

            if ( (LA11_0==IDENTIFIER) ) {
                alt11=1;
            }
            else if ( (LA11_0==18) ) {
                alt11=2;
            }
            else {
                if (state.backtracking>0) {state.failed=true; return retval;}
                NoViableAltException nvae =
                    new NoViableAltException("", 11, 0, input);

                throw nvae;
            }
            switch (alt11) {
                case 1 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:263:15: i1= IDENTIFIER
                    {
                    i1=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_parallel_statement678); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    i1_tree = (CommonTree)adaptor.create(i1);
                    adaptor.addChild(root_0, i1_tree);
                    }

                    }
                    break;
                case 2 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:263:29: i1= 'void'
                    {
                    i1=(Token)match(input,18,FOLLOW_18_in_parallel_statement682); if (state.failed) return retval;
                    if ( state.backtracking==0 ) {
                    i1_tree = (CommonTree)adaptor.create(i1);
                    adaptor.addChild(root_0, i1_tree);
                    }

                    }
                    break;

            }

            if ( state.backtracking==0 ) {

              			retval.code = "PAR(";
              		
              			if (occurence.isEmpty() == false) {
              				int count = (Integer)occurence.get((i1!=null?i1.getText():null));
              				if (count > 1){
              					retval.code +=(i1!=null?i1.getText():null)+"_PRET_"+count;
              					pars.add((i1!=null?i1.getText():null)+"_PRET_"+count);
              					count--;
              					occurence.put((i1!=null?i1.getText():null),count);
              				}else{
              					retval.code +=(i1!=null?i1.getText():null);
              					pars.add((i1!=null?i1.getText():null));
              				}
              			}else{
              				retval.code +=(i1!=null?i1.getText():null);
              				pars.add((i1!=null?i1.getText():null));
              			}
              		
            }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:282:5: ( ',' (i2= IDENTIFIER | i2= 'void' ) )+
            int cnt13=0;
            loop13:
            do {
                int alt13=2;
                int LA13_0 = input.LA(1);

                if ( (LA13_0==22) ) {
                    alt13=1;
                }


                switch (alt13) {
            	case 1 :
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:282:6: ',' (i2= IDENTIFIER | i2= 'void' )
            	    {
            	    char_literal41=(Token)match(input,22,FOLLOW_22_in_parallel_statement690); if (state.failed) return retval;
            	    if ( state.backtracking==0 ) {
            	    char_literal41_tree = (CommonTree)adaptor.create(char_literal41);
            	    adaptor.addChild(root_0, char_literal41_tree);
            	    }
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:282:10: (i2= IDENTIFIER | i2= 'void' )
            	    int alt12=2;
            	    int LA12_0 = input.LA(1);

            	    if ( (LA12_0==IDENTIFIER) ) {
            	        alt12=1;
            	    }
            	    else if ( (LA12_0==18) ) {
            	        alt12=2;
            	    }
            	    else {
            	        if (state.backtracking>0) {state.failed=true; return retval;}
            	        NoViableAltException nvae =
            	            new NoViableAltException("", 12, 0, input);

            	        throw nvae;
            	    }
            	    switch (alt12) {
            	        case 1 :
            	            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:282:11: i2= IDENTIFIER
            	            {
            	            i2=(Token)match(input,IDENTIFIER,FOLLOW_IDENTIFIER_in_parallel_statement695); if (state.failed) return retval;
            	            if ( state.backtracking==0 ) {
            	            i2_tree = (CommonTree)adaptor.create(i2);
            	            adaptor.addChild(root_0, i2_tree);
            	            }

            	            }
            	            break;
            	        case 2 :
            	            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:282:25: i2= 'void'
            	            {
            	            i2=(Token)match(input,18,FOLLOW_18_in_parallel_statement699); if (state.failed) return retval;
            	            if ( state.backtracking==0 ) {
            	            i2_tree = (CommonTree)adaptor.create(i2);
            	            adaptor.addChild(root_0, i2_tree);
            	            }

            	            }
            	            break;

            	    }

            	    if ( state.backtracking==0 ) {

            	      			//retval.code += ","+(i2!=null?i2.getText():null);
            	      			//pars.add((i2!=null?i2.getText():null));
            	      		
            	      			if (occurence.isEmpty() == false) {
            	      				int count = (Integer)occurence.get((i2!=null?i2.getText():null));
            	      				if (count > 1){
            	      					retval.code +=","+(i2!=null?i2.getText():null)+"_PRET_"+count;
            	      					pars.add((i2!=null?i2.getText():null)+"_PRET_"+count);
            	      					count--;
            	      					occurence.put((i2!=null?i2.getText():null),count);
            	      				}else{
            	      					retval.code +=","+(i2!=null?i2.getText():null);
            	      					pars.add((i2!=null?i2.getText():null));
            	      				}
            	      			}else{
            	      				retval.code +=","+(i2!=null?i2.getText():null);
            	      				pars.add((i2!=null?i2.getText():null));
            	      			}
            	      		
            	    }

            	    }
            	    break;

            	default :
            	    if ( cnt13 >= 1 ) break loop13;
            	    if (state.backtracking>0) {state.failed=true; return retval;}
                        EarlyExitException eee =
                            new EarlyExitException(13, input);
                        throw eee;
                }
                cnt13++;
            } while (true);

            char_literal42=(Token)match(input,19,FOLLOW_19_in_parallel_statement711); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal42_tree = (CommonTree)adaptor.create(char_literal42);
            adaptor.addChild(root_0, char_literal42_tree);
            }
            char_literal43=(Token)match(input,20,FOLLOW_20_in_parallel_statement713); if (state.failed) return retval;
            if ( state.backtracking==0 ) {
            char_literal43_tree = (CommonTree)adaptor.create(char_literal43);
            adaptor.addChild(root_0, char_literal43_tree);
            }
            if ( state.backtracking==0 ) {

              			retval.code += ");";
              		
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
            if ( state.backtracking>0 ) { memoize(input, 8, parallel_statement_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "parallel_statement"

    public static class wildcard_rule_return extends ParserRuleReturnScope {
        CommonTree tree;
        public Object getTree() { return tree; }
    };

    // $ANTLR start "wildcard_rule"
    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:310:1: wildcard_rule : ( options {greedy=false; } : ( WILDCARD | IDENTIFIER | '(' | ')' | 'void' | ',' ) )* ;
    public final PretCPreprocessorParser.wildcard_rule_return wildcard_rule() throws RecognitionException {
        PretCPreprocessorParser.wildcard_rule_return retval = new PretCPreprocessorParser.wildcard_rule_return();
        retval.start = input.LT(1);
        int wildcard_rule_StartIndex = input.index();
        CommonTree root_0 = null;

        Token set44=null;

        CommonTree set44_tree=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 9) ) { return retval; }
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:311:2: ( ( options {greedy=false; } : ( WILDCARD | IDENTIFIER | '(' | ')' | 'void' | ',' ) )* )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:311:4: ( options {greedy=false; } : ( WILDCARD | IDENTIFIER | '(' | ')' | 'void' | ',' ) )*
            {
            root_0 = (CommonTree)adaptor.nil();

            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:311:4: ( options {greedy=false; } : ( WILDCARD | IDENTIFIER | '(' | ')' | 'void' | ',' ) )*
            loop14:
            do {
                int alt14=2;
                int LA14_0 = input.LA(1);

                if ( ((LA14_0>=14 && LA14_0<=15)||(LA14_0>=20 && LA14_0<=21)) ) {
                    alt14=2;
                }
                else if ( ((LA14_0>=IDENTIFIER && LA14_0<=WILDCARD)||(LA14_0>=17 && LA14_0<=19)||LA14_0==22) ) {
                    alt14=1;
                }


                switch (alt14) {
            	case 1 :
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:311:32: ( WILDCARD | IDENTIFIER | '(' | ')' | 'void' | ',' )
            	    {
            	    set44=(Token)input.LT(1);
            	    if ( (input.LA(1)>=IDENTIFIER && input.LA(1)<=WILDCARD)||(input.LA(1)>=17 && input.LA(1)<=19)||input.LA(1)==22 ) {
            	        input.consume();
            	        if ( state.backtracking==0 ) adaptor.addChild(root_0, (CommonTree)adaptor.create(set44));
            	        state.errorRecovery=false;state.failed=false;
            	    }
            	    else {
            	        if (state.backtracking>0) {state.failed=true; return retval;}
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        throw mse;
            	    }


            	    }
            	    break;

            	default :
            	    break loop14;
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
            if ( state.backtracking>0 ) { memoize(input, 9, wildcard_rule_StartIndex); }
        }
        return retval;
    }
    // $ANTLR end "wildcard_rule"

    // $ANTLR start synpred2_PretCPreprocessor
    public final void synpred2_PretCPreprocessor_fragment() throws RecognitionException {   
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:97:4: ( scope_definition )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:97:4: scope_definition
        {
        pushFollow(FOLLOW_scope_definition_in_synpred2_PretCPreprocessor139);
        scope_definition();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred2_PretCPreprocessor

    // $ANTLR start synpred3_PretCPreprocessor
    public final void synpred3_PretCPreprocessor_fragment() throws RecognitionException {   
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:98:4: ( line )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:98:4: line
        {
        pushFollow(FOLLOW_line_in_synpred3_PretCPreprocessor154);
        line();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred3_PretCPreprocessor

    // $ANTLR start synpred4_PretCPreprocessor
    public final void synpred4_PretCPreprocessor_fragment() throws RecognitionException {   
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:121:4: ( ( line ) )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:121:4: ( line )
        {
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:121:4: ( line )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:122:5: line
        {
        pushFollow(FOLLOW_line_in_synpred4_PretCPreprocessor228);
        line();

        state._fsp--;
        if (state.failed) return ;

        }


        }
    }
    // $ANTLR end synpred4_PretCPreprocessor

    // $ANTLR start synpred5_PretCPreprocessor
    public final void synpred5_PretCPreprocessor_fragment() throws RecognitionException {   
        PretCPreprocessorParser.scope_definition_return fn = null;


        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:128:4: ( (fn= scope_definition ) )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:128:4: (fn= scope_definition )
        {
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:128:4: (fn= scope_definition )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:129:5: fn= scope_definition
        {
        pushFollow(FOLLOW_scope_definition_in_synpred5_PretCPreprocessor258);
        fn=scope_definition();

        state._fsp--;
        if (state.failed) return ;

        }


        }
    }
    // $ANTLR end synpred5_PretCPreprocessor

    // $ANTLR start synpred6_PretCPreprocessor
    public final void synpred6_PretCPreprocessor_fragment() throws RecognitionException {   
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:153:4: ( ( line ) )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:153:4: ( line )
        {
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:153:4: ( line )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:154:5: line
        {
        pushFollow(FOLLOW_line_in_synpred6_PretCPreprocessor332);
        line();

        state._fsp--;
        if (state.failed) return ;

        }


        }
    }
    // $ANTLR end synpred6_PretCPreprocessor

    // $ANTLR start synpred7_PretCPreprocessor
    public final void synpred7_PretCPreprocessor_fragment() throws RecognitionException {   
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:161:4: ( ( scope_definition ) )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:161:4: ( scope_definition )
        {
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:161:4: ( scope_definition )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:162:5: scope_definition
        {
        pushFollow(FOLLOW_scope_definition_in_synpred7_PretCPreprocessor359);
        scope_definition();

        state._fsp--;
        if (state.failed) return ;

        }


        }
    }
    // $ANTLR end synpred7_PretCPreprocessor

    // $ANTLR start synpred10_PretCPreprocessor
    public final void synpred10_PretCPreprocessor_fragment() throws RecognitionException {   
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:202:4: ( wildcard_rule ( ( ';' ) | ( ':' ) ) )
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:202:4: wildcard_rule ( ( ';' ) | ( ':' ) )
        {
        pushFollow(FOLLOW_wildcard_rule_in_synpred10_PretCPreprocessor412);
        wildcard_rule();

        state._fsp--;
        if (state.failed) return ;
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:211:4: ( ( ';' ) | ( ':' ) )
        int alt15=2;
        int LA15_0 = input.LA(1);

        if ( (LA15_0==20) ) {
            alt15=1;
        }
        else if ( (LA15_0==21) ) {
            alt15=2;
        }
        else {
            if (state.backtracking>0) {state.failed=true; return ;}
            NoViableAltException nvae =
                new NoViableAltException("", 15, 0, input);

            throw nvae;
        }
        switch (alt15) {
            case 1 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:212:5: ( ';' )
                {
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:212:5: ( ';' )
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:212:6: ';'
                {
                match(input,20,FOLLOW_20_in_synpred10_PretCPreprocessor434); if (state.failed) return ;

                }


                }
                break;
            case 2 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:218:5: ( ':' )
                {
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:218:5: ( ':' )
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:218:6: ':'
                {
                match(input,21,FOLLOW_21_in_synpred10_PretCPreprocessor458); if (state.failed) return ;

                }


                }
                break;

        }


        }
    }
    // $ANTLR end synpred10_PretCPreprocessor

    // Delegated rules

    public final boolean synpred5_PretCPreprocessor() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred5_PretCPreprocessor_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred2_PretCPreprocessor() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred2_PretCPreprocessor_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred4_PretCPreprocessor() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred4_PretCPreprocessor_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred3_PretCPreprocessor() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred3_PretCPreprocessor_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred6_PretCPreprocessor() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred6_PretCPreprocessor_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred10_PretCPreprocessor() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred10_PretCPreprocessor_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred7_PretCPreprocessor() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred7_PretCPreprocessor_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }


    protected DFA2 dfa2 = new DFA2(this);
    protected DFA3 dfa3 = new DFA3(this);
    protected DFA4 dfa4 = new DFA4(this);
    protected DFA7 dfa7 = new DFA7(this);
    static final String DFA2_eotS =
        "\21\uffff";
    static final String DFA2_eofS =
        "\21\uffff";
    static final String DFA2_minS =
        "\3\10\4\uffff\2\0\6\uffff\1\0\1\uffff";
    static final String DFA2_maxS =
        "\1\27\1\26\1\27\4\uffff\2\0\6\uffff\1\0\1\uffff";
    static final String DFA2_acceptS =
        "\3\uffff\1\2\2\uffff\1\3\4\uffff\1\1\5\uffff";
    static final String DFA2_specialS =
        "\7\uffff\1\0\1\1\6\uffff\1\2\1\uffff}>";
    static final String[] DFA2_transitionS = {
            "\2\1\4\uffff\1\2\1\uffff\1\6\3\1\2\3\1\1\1\3",
            "\2\10\4\uffff\1\7\2\uffff\3\10\2\3\1\10",
            "\2\13\4\uffff\1\17\1\13\1\uffff\7\13",
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
            "",
            "",
            "\1\uffff",
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
            return "86:1: external_declaration : ( scope_definition -> ^( SCP_TOK scope_definition ) | line | thread_definition -> ^( THD_TOK thread_definition ) );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA2_7 = input.LA(1);

                         
                        int index2_7 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred2_PretCPreprocessor()) ) {s = 11;}

                        else if ( (synpred3_PretCPreprocessor()) ) {s = 3;}

                         
                        input.seek(index2_7);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA2_8 = input.LA(1);

                         
                        int index2_8 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred2_PretCPreprocessor()) ) {s = 11;}

                        else if ( (synpred3_PretCPreprocessor()) ) {s = 3;}

                         
                        input.seek(index2_8);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA2_15 = input.LA(1);

                         
                        int index2_15 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred2_PretCPreprocessor()) ) {s = 11;}

                        else if ( (synpred3_PretCPreprocessor()) ) {s = 3;}

                         
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
    static final String DFA3_eotS =
        "\21\uffff";
    static final String DFA3_eofS =
        "\21\uffff";
    static final String DFA3_minS =
        "\1\10\2\uffff\1\10\2\uffff\1\10\2\0\2\uffff\1\0\5\uffff";
    static final String DFA3_maxS =
        "\1\27\2\uffff\1\26\2\uffff\1\27\2\0\2\uffff\1\0\5\uffff";
    static final String DFA3_acceptS =
        "\1\uffff\1\3\1\1\11\uffff\1\2\4\uffff";
    static final String DFA3_specialS =
        "\7\uffff\1\0\1\1\2\uffff\1\2\5\uffff}>";
    static final String[] DFA3_transitionS = {
            "\2\3\4\uffff\1\6\1\1\1\uffff\3\3\2\2\1\3\1\2",
            "",
            "",
            "\2\10\4\uffff\1\7\2\uffff\3\10\2\2\1\10",
            "",
            "",
            "\2\14\4\uffff\1\13\1\14\1\uffff\7\14",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "\1\uffff",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA3_eot = DFA.unpackEncodedString(DFA3_eotS);
    static final short[] DFA3_eof = DFA.unpackEncodedString(DFA3_eofS);
    static final char[] DFA3_min = DFA.unpackEncodedStringToUnsignedChars(DFA3_minS);
    static final char[] DFA3_max = DFA.unpackEncodedStringToUnsignedChars(DFA3_maxS);
    static final short[] DFA3_accept = DFA.unpackEncodedString(DFA3_acceptS);
    static final short[] DFA3_special = DFA.unpackEncodedString(DFA3_specialS);
    static final short[][] DFA3_transition;

    static {
        int numStates = DFA3_transitionS.length;
        DFA3_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA3_transition[i] = DFA.unpackEncodedString(DFA3_transitionS[i]);
        }
    }

    class DFA3 extends DFA {

        public DFA3(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 3;
            this.eot = DFA3_eot;
            this.eof = DFA3_eof;
            this.min = DFA3_min;
            this.max = DFA3_max;
            this.accept = DFA3_accept;
            this.special = DFA3_special;
            this.transition = DFA3_transition;
        }
        public String getDescription() {
            return "()* loopback of 120:3: ( ( line ) | (fn= scope_definition ) )*";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA3_7 = input.LA(1);

                         
                        int index3_7 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretCPreprocessor()) ) {s = 2;}

                        else if ( (synpred5_PretCPreprocessor()) ) {s = 12;}

                         
                        input.seek(index3_7);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA3_8 = input.LA(1);

                         
                        int index3_8 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretCPreprocessor()) ) {s = 2;}

                        else if ( (synpred5_PretCPreprocessor()) ) {s = 12;}

                         
                        input.seek(index3_8);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA3_11 = input.LA(1);

                         
                        int index3_11 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred4_PretCPreprocessor()) ) {s = 2;}

                        else if ( (synpred5_PretCPreprocessor()) ) {s = 12;}

                         
                        input.seek(index3_11);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 3, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA4_eotS =
        "\21\uffff";
    static final String DFA4_eofS =
        "\21\uffff";
    static final String DFA4_minS =
        "\1\10\2\uffff\1\10\2\uffff\1\10\2\uffff\3\0\5\uffff";
    static final String DFA4_maxS =
        "\1\27\2\uffff\1\26\2\uffff\1\27\2\uffff\3\0\5\uffff";
    static final String DFA4_acceptS =
        "\1\uffff\1\3\1\1\11\uffff\1\2\4\uffff";
    static final String DFA4_specialS =
        "\11\uffff\1\0\1\1\1\2\5\uffff}>";
    static final String[] DFA4_transitionS = {
            "\2\3\4\uffff\1\6\1\1\1\uffff\3\3\2\2\1\3\1\2",
            "",
            "",
            "\2\11\4\uffff\1\12\2\uffff\3\11\2\2\1\11",
            "",
            "",
            "\2\14\4\uffff\1\13\1\14\1\uffff\7\14",
            "",
            "",
            "\1\uffff",
            "\1\uffff",
            "\1\uffff",
            "",
            "",
            "",
            "",
            ""
    };

    static final short[] DFA4_eot = DFA.unpackEncodedString(DFA4_eotS);
    static final short[] DFA4_eof = DFA.unpackEncodedString(DFA4_eofS);
    static final char[] DFA4_min = DFA.unpackEncodedStringToUnsignedChars(DFA4_minS);
    static final char[] DFA4_max = DFA.unpackEncodedStringToUnsignedChars(DFA4_maxS);
    static final short[] DFA4_accept = DFA.unpackEncodedString(DFA4_acceptS);
    static final short[] DFA4_special = DFA.unpackEncodedString(DFA4_specialS);
    static final short[][] DFA4_transition;

    static {
        int numStates = DFA4_transitionS.length;
        DFA4_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA4_transition[i] = DFA.unpackEncodedString(DFA4_transitionS[i]);
        }
    }

    class DFA4 extends DFA {

        public DFA4(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 4;
            this.eot = DFA4_eot;
            this.eof = DFA4_eof;
            this.min = DFA4_min;
            this.max = DFA4_max;
            this.accept = DFA4_accept;
            this.special = DFA4_special;
            this.transition = DFA4_transition;
        }
        public String getDescription() {
            return "()* loopback of 152:3: ( ( line ) | ( scope_definition ) )*";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA4_9 = input.LA(1);

                         
                        int index4_9 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred6_PretCPreprocessor()) ) {s = 2;}

                        else if ( (synpred7_PretCPreprocessor()) ) {s = 12;}

                         
                        input.seek(index4_9);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA4_10 = input.LA(1);

                         
                        int index4_10 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred6_PretCPreprocessor()) ) {s = 2;}

                        else if ( (synpred7_PretCPreprocessor()) ) {s = 12;}

                         
                        input.seek(index4_10);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA4_11 = input.LA(1);

                         
                        int index4_11 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred6_PretCPreprocessor()) ) {s = 2;}

                        else if ( (synpred7_PretCPreprocessor()) ) {s = 12;}

                         
                        input.seek(index4_11);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 4, _s, input);
            error(nvae);
            throw nvae;
        }
    }
    static final String DFA7_eotS =
        "\12\uffff";
    static final String DFA7_eofS =
        "\12\uffff";
    static final String DFA7_minS =
        "\1\10\1\uffff\1\10\4\uffff\1\0\2\uffff";
    static final String DFA7_maxS =
        "\1\27\1\uffff\1\26\4\uffff\1\0\2\uffff";
    static final String DFA7_acceptS =
        "\1\uffff\1\1\1\uffff\1\2\1\uffff\1\3\4\uffff";
    static final String DFA7_specialS =
        "\7\uffff\1\0\2\uffff}>";
    static final String[] DFA7_transitionS = {
            "\2\2\4\uffff\1\5\2\uffff\3\2\2\3\1\2\1\1",
            "",
            "\2\7\4\uffff\1\5\2\uffff\3\7\2\3\1\7",
            "",
            "",
            "",
            "",
            "\1\uffff",
            "",
            ""
    };

    static final short[] DFA7_eot = DFA.unpackEncodedString(DFA7_eotS);
    static final short[] DFA7_eof = DFA.unpackEncodedString(DFA7_eofS);
    static final char[] DFA7_min = DFA.unpackEncodedStringToUnsignedChars(DFA7_minS);
    static final char[] DFA7_max = DFA.unpackEncodedStringToUnsignedChars(DFA7_maxS);
    static final short[] DFA7_accept = DFA.unpackEncodedString(DFA7_acceptS);
    static final short[] DFA7_special = DFA.unpackEncodedString(DFA7_specialS);
    static final short[][] DFA7_transition;

    static {
        int numStates = DFA7_transitionS.length;
        DFA7_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA7_transition[i] = DFA.unpackEncodedString(DFA7_transitionS[i]);
        }
    }

    class DFA7 extends DFA {

        public DFA7(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 7;
            this.eot = DFA7_eot;
            this.eof = DFA7_eof;
            this.min = DFA7_min;
            this.max = DFA7_max;
            this.accept = DFA7_accept;
            this.special = DFA7_special;
            this.transition = DFA7_transition;
        }
        public String getDescription() {
            return "200:1: line returns [String code] : ( parallel_statement | wildcard_rule ( ( ';' ) | ( ':' ) ) -> ^( TOK ( wildcard_rule )? ( ';' )? ( ':' )? ) | wildcard_rule array_declare ( ( ';' ) | ( ':' ) ) -> ^( TOK ( wildcard_rule )? ( array_declare )? ( ';' )? ( ':' )? ) );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TokenStream input = (TokenStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA7_7 = input.LA(1);

                         
                        int index7_7 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred10_PretCPreprocessor()) ) {s = 3;}

                        else if ( (true) ) {s = 5;}

                         
                        input.seek(index7_7);
                        if ( s>=0 ) return s;
                        break;
            }
            if (state.backtracking>0) {state.failed=true; return -1;}
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 7, _s, input);
            error(nvae);
            throw nvae;
        }
    }
 

    public static final BitSet FOLLOW_external_declaration_in_translation_unit116 = new BitSet(new long[]{0x0000000000FF4302L});
    public static final BitSet FOLLOW_scope_definition_in_external_declaration139 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_line_in_external_declaration154 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_thread_definition_in_external_declaration164 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_wildcard_rule_in_scope_definition205 = new BitSet(new long[]{0x0000000000004000L});
    public static final BitSet FOLLOW_14_in_scope_definition207 = new BitSet(new long[]{0x0000000000FEC300L});
    public static final BitSet FOLLOW_line_in_scope_definition228 = new BitSet(new long[]{0x0000000000FEC300L});
    public static final BitSet FOLLOW_scope_definition_in_scope_definition258 = new BitSet(new long[]{0x0000000000FEC300L});
    public static final BitSet FOLLOW_15_in_scope_definition279 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_16_in_thread_definition301 = new BitSet(new long[]{0x0000000000000100L});
    public static final BitSet FOLLOW_IDENTIFIER_in_thread_definition303 = new BitSet(new long[]{0x0000000000020000L});
    public static final BitSet FOLLOW_17_in_thread_definition305 = new BitSet(new long[]{0x0000000000040000L});
    public static final BitSet FOLLOW_18_in_thread_definition307 = new BitSet(new long[]{0x0000000000080000L});
    public static final BitSet FOLLOW_19_in_thread_definition309 = new BitSet(new long[]{0x0000000000004000L});
    public static final BitSet FOLLOW_14_in_thread_definition311 = new BitSet(new long[]{0x0000000000FEC300L});
    public static final BitSet FOLLOW_line_in_thread_definition332 = new BitSet(new long[]{0x0000000000FEC300L});
    public static final BitSet FOLLOW_scope_definition_in_thread_definition359 = new BitSet(new long[]{0x0000000000FEC300L});
    public static final BitSet FOLLOW_15_in_thread_definition377 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_parallel_statement_in_line405 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_wildcard_rule_in_line412 = new BitSet(new long[]{0x0000000000300000L});
    public static final BitSet FOLLOW_20_in_line434 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_21_in_line458 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_wildcard_rule_in_line506 = new BitSet(new long[]{0x0000000000FE4300L});
    public static final BitSet FOLLOW_array_declare_in_line508 = new BitSet(new long[]{0x0000000000300000L});
    public static final BitSet FOLLOW_20_in_line530 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_21_in_line554 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_14_in_array_declare608 = new BitSet(new long[]{0x0000000000FE4300L});
    public static final BitSet FOLLOW_array_elements_in_array_declare610 = new BitSet(new long[]{0x0000000000008000L});
    public static final BitSet FOLLOW_15_in_array_declare612 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_array_declare_in_array_elements627 = new BitSet(new long[]{0x0000000000400002L});
    public static final BitSet FOLLOW_22_in_array_elements630 = new BitSet(new long[]{0x0000000000FE4300L});
    public static final BitSet FOLLOW_array_declare_in_array_elements632 = new BitSet(new long[]{0x0000000000400002L});
    public static final BitSet FOLLOW_14_in_array_elements639 = new BitSet(new long[]{0x00000000004E8300L});
    public static final BitSet FOLLOW_wildcard_rule_in_array_elements641 = new BitSet(new long[]{0x0000000000008000L});
    public static final BitSet FOLLOW_15_in_array_elements643 = new BitSet(new long[]{0x0000000000400002L});
    public static final BitSet FOLLOW_22_in_array_elements646 = new BitSet(new long[]{0x0000000000004000L});
    public static final BitSet FOLLOW_14_in_array_elements648 = new BitSet(new long[]{0x00000000004E8300L});
    public static final BitSet FOLLOW_wildcard_rule_in_array_elements650 = new BitSet(new long[]{0x0000000000008000L});
    public static final BitSet FOLLOW_15_in_array_elements652 = new BitSet(new long[]{0x0000000000400002L});
    public static final BitSet FOLLOW_23_in_parallel_statement671 = new BitSet(new long[]{0x0000000000020000L});
    public static final BitSet FOLLOW_17_in_parallel_statement673 = new BitSet(new long[]{0x0000000000040100L});
    public static final BitSet FOLLOW_IDENTIFIER_in_parallel_statement678 = new BitSet(new long[]{0x0000000000400000L});
    public static final BitSet FOLLOW_18_in_parallel_statement682 = new BitSet(new long[]{0x0000000000400000L});
    public static final BitSet FOLLOW_22_in_parallel_statement690 = new BitSet(new long[]{0x0000000000040100L});
    public static final BitSet FOLLOW_IDENTIFIER_in_parallel_statement695 = new BitSet(new long[]{0x0000000000480000L});
    public static final BitSet FOLLOW_18_in_parallel_statement699 = new BitSet(new long[]{0x0000000000480000L});
    public static final BitSet FOLLOW_19_in_parallel_statement711 = new BitSet(new long[]{0x0000000000100000L});
    public static final BitSet FOLLOW_20_in_parallel_statement713 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_set_in_wildcard_rule743 = new BitSet(new long[]{0x00000000004E0302L});
    public static final BitSet FOLLOW_scope_definition_in_synpred2_PretCPreprocessor139 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_line_in_synpred3_PretCPreprocessor154 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_line_in_synpred4_PretCPreprocessor228 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_scope_definition_in_synpred5_PretCPreprocessor258 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_line_in_synpred6_PretCPreprocessor332 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_scope_definition_in_synpred7_PretCPreprocessor359 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_wildcard_rule_in_synpred10_PretCPreprocessor412 = new BitSet(new long[]{0x0000000000300000L});
    public static final BitSet FOLLOW_20_in_synpred10_PretCPreprocessor434 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_21_in_synpred10_PretCPreprocessor458 = new BitSet(new long[]{0x0000000000000002L});

}