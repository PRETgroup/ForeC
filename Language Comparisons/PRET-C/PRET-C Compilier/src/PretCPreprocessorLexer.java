// $ANTLR 3.1.2 D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g 2011-11-24 17:30:00

import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

public class PretCPreprocessorLexer extends Lexer {
    public static final int FUN_TOK=7;
    public static final int LINE_COMMENT=13;
    public static final int T__23=23;
    public static final int LETTER=10;
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

    public PretCPreprocessorLexer() {;} 
    public PretCPreprocessorLexer(CharStream input) {
        this(input, new RecognizerSharedState());
    }
    public PretCPreprocessorLexer(CharStream input, RecognizerSharedState state) {
        super(input,state);

    }
    public String getGrammarFileName() { return "D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g"; }

    // $ANTLR start "T__14"
    public final void mT__14() throws RecognitionException {
        try {
            int _type = T__14;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:3:7: ( '{' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:3:9: '{'
            {
            match('{'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__14"

    // $ANTLR start "T__15"
    public final void mT__15() throws RecognitionException {
        try {
            int _type = T__15;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:4:7: ( '}' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:4:9: '}'
            {
            match('}'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__15"

    // $ANTLR start "T__16"
    public final void mT__16() throws RecognitionException {
        try {
            int _type = T__16;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:5:7: ( 'thread' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:5:9: 'thread'
            {
            match("thread"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__16"

    // $ANTLR start "T__17"
    public final void mT__17() throws RecognitionException {
        try {
            int _type = T__17;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:6:7: ( '(' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:6:9: '('
            {
            match('('); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__17"

    // $ANTLR start "T__18"
    public final void mT__18() throws RecognitionException {
        try {
            int _type = T__18;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:7:7: ( 'void' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:7:9: 'void'
            {
            match("void"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__18"

    // $ANTLR start "T__19"
    public final void mT__19() throws RecognitionException {
        try {
            int _type = T__19;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:8:7: ( ')' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:8:9: ')'
            {
            match(')'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__19"

    // $ANTLR start "T__20"
    public final void mT__20() throws RecognitionException {
        try {
            int _type = T__20;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:9:7: ( ';' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:9:9: ';'
            {
            match(';'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__20"

    // $ANTLR start "T__21"
    public final void mT__21() throws RecognitionException {
        try {
            int _type = T__21;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:10:7: ( ':' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:10:9: ':'
            {
            match(':'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__21"

    // $ANTLR start "T__22"
    public final void mT__22() throws RecognitionException {
        try {
            int _type = T__22;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:11:7: ( ',' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:11:9: ','
            {
            match(','); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__22"

    // $ANTLR start "T__23"
    public final void mT__23() throws RecognitionException {
        try {
            int _type = T__23;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:12:7: ( 'PAR' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:12:9: 'PAR'
            {
            match("PAR"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__23"

    // $ANTLR start "IDENTIFIER"
    public final void mIDENTIFIER() throws RecognitionException {
        try {
            int _type = IDENTIFIER;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:315:2: ( LETTER ( LETTER | '0' .. '9' )* )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:315:4: LETTER ( LETTER | '0' .. '9' )*
            {
            mLETTER(); 
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:315:11: ( LETTER | '0' .. '9' )*
            loop1:
            do {
                int alt1=2;
                int LA1_0 = input.LA(1);

                if ( ((LA1_0>='#' && LA1_0<='$')||LA1_0=='*'||LA1_0=='.'||(LA1_0>='0' && LA1_0<='9')||(LA1_0>='A' && LA1_0<='Z')||LA1_0=='_'||(LA1_0>='a' && LA1_0<='z')) ) {
                    alt1=1;
                }


                switch (alt1) {
            	case 1 :
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:
            	    {
            	    if ( (input.LA(1)>='#' && input.LA(1)<='$')||input.LA(1)=='*'||input.LA(1)=='.'||(input.LA(1)>='0' && input.LA(1)<='9')||(input.LA(1)>='A' && input.LA(1)<='Z')||input.LA(1)=='_'||(input.LA(1)>='a' && input.LA(1)<='z') ) {
            	        input.consume();

            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        recover(mse);
            	        throw mse;}


            	    }
            	    break;

            	default :
            	    break loop1;
                }
            } while (true);


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "IDENTIFIER"

    // $ANTLR start "LETTER"
    public final void mLETTER() throws RecognitionException {
        try {
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:320:2: ( '$' | 'A' .. 'Z' | 'a' .. 'z' | '_' | '.' | '#' | '*' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:
            {
            if ( (input.LA(1)>='#' && input.LA(1)<='$')||input.LA(1)=='*'||input.LA(1)=='.'||(input.LA(1)>='A' && input.LA(1)<='Z')||input.LA(1)=='_'||(input.LA(1)>='a' && input.LA(1)<='z') ) {
                input.consume();

            }
            else {
                MismatchedSetException mse = new MismatchedSetException(null,input);
                recover(mse);
                throw mse;}


            }

        }
        finally {
        }
    }
    // $ANTLR end "LETTER"

    // $ANTLR start "WS"
    public final void mWS() throws RecognitionException {
        try {
            int _type = WS;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:328:5: ( ( ' ' | '\\r' | '\\t' | '\\u000C' | '\\n' ) )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:328:8: ( ' ' | '\\r' | '\\t' | '\\u000C' | '\\n' )
            {
            if ( (input.LA(1)>='\t' && input.LA(1)<='\n')||(input.LA(1)>='\f' && input.LA(1)<='\r')||input.LA(1)==' ' ) {
                input.consume();

            }
            else {
                MismatchedSetException mse = new MismatchedSetException(null,input);
                recover(mse);
                throw mse;}

            _channel=HIDDEN;

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "WS"

    // $ANTLR start "COMMENT"
    public final void mCOMMENT() throws RecognitionException {
        try {
            int _type = COMMENT;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:332:5: ( '/*' ( options {greedy=false; } : . )* '*/' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:332:9: '/*' ( options {greedy=false; } : . )* '*/'
            {
            match("/*"); 

            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:332:14: ( options {greedy=false; } : . )*
            loop2:
            do {
                int alt2=2;
                int LA2_0 = input.LA(1);

                if ( (LA2_0=='*') ) {
                    int LA2_1 = input.LA(2);

                    if ( (LA2_1=='/') ) {
                        alt2=2;
                    }
                    else if ( ((LA2_1>='\u0000' && LA2_1<='.')||(LA2_1>='0' && LA2_1<='\uFFFF')) ) {
                        alt2=1;
                    }


                }
                else if ( ((LA2_0>='\u0000' && LA2_0<=')')||(LA2_0>='+' && LA2_0<='\uFFFF')) ) {
                    alt2=1;
                }


                switch (alt2) {
            	case 1 :
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:332:42: .
            	    {
            	    matchAny(); 

            	    }
            	    break;

            	default :
            	    break loop2;
                }
            } while (true);

            match("*/"); 

            _channel=HIDDEN;

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "COMMENT"

    // $ANTLR start "LINE_COMMENT"
    public final void mLINE_COMMENT() throws RecognitionException {
        try {
            int _type = LINE_COMMENT;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:336:5: ( '//' (~ ( '\\n' | '\\r' ) )* ( '\\r' )? '\\n' )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:336:7: '//' (~ ( '\\n' | '\\r' ) )* ( '\\r' )? '\\n'
            {
            match("//"); 

            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:336:12: (~ ( '\\n' | '\\r' ) )*
            loop3:
            do {
                int alt3=2;
                int LA3_0 = input.LA(1);

                if ( ((LA3_0>='\u0000' && LA3_0<='\t')||(LA3_0>='\u000B' && LA3_0<='\f')||(LA3_0>='\u000E' && LA3_0<='\uFFFF')) ) {
                    alt3=1;
                }


                switch (alt3) {
            	case 1 :
            	    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:336:12: ~ ( '\\n' | '\\r' )
            	    {
            	    if ( (input.LA(1)>='\u0000' && input.LA(1)<='\t')||(input.LA(1)>='\u000B' && input.LA(1)<='\f')||(input.LA(1)>='\u000E' && input.LA(1)<='\uFFFF') ) {
            	        input.consume();

            	    }
            	    else {
            	        MismatchedSetException mse = new MismatchedSetException(null,input);
            	        recover(mse);
            	        throw mse;}


            	    }
            	    break;

            	default :
            	    break loop3;
                }
            } while (true);

            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:336:26: ( '\\r' )?
            int alt4=2;
            int LA4_0 = input.LA(1);

            if ( (LA4_0=='\r') ) {
                alt4=1;
            }
            switch (alt4) {
                case 1 :
                    // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:336:26: '\\r'
                    {
                    match('\r'); 

                    }
                    break;

            }

            match('\n'); 
            _channel=HIDDEN;

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "LINE_COMMENT"

    // $ANTLR start "WILDCARD"
    public final void mWILDCARD() throws RecognitionException {
        try {
            int _type = WILDCARD;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:340:2: ( ( . ) )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:340:3: ( . )
            {
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:340:3: ( . )
            // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:340:4: .
            {
            matchAny(); 

            }


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "WILDCARD"

    public void mTokens() throws RecognitionException {
        // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:8: ( T__14 | T__15 | T__16 | T__17 | T__18 | T__19 | T__20 | T__21 | T__22 | T__23 | IDENTIFIER | WS | COMMENT | LINE_COMMENT | WILDCARD )
        int alt5=15;
        alt5 = dfa5.predict(input);
        switch (alt5) {
            case 1 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:10: T__14
                {
                mT__14(); 

                }
                break;
            case 2 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:16: T__15
                {
                mT__15(); 

                }
                break;
            case 3 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:22: T__16
                {
                mT__16(); 

                }
                break;
            case 4 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:28: T__17
                {
                mT__17(); 

                }
                break;
            case 5 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:34: T__18
                {
                mT__18(); 

                }
                break;
            case 6 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:40: T__19
                {
                mT__19(); 

                }
                break;
            case 7 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:46: T__20
                {
                mT__20(); 

                }
                break;
            case 8 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:52: T__21
                {
                mT__21(); 

                }
                break;
            case 9 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:58: T__22
                {
                mT__22(); 

                }
                break;
            case 10 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:64: T__23
                {
                mT__23(); 

                }
                break;
            case 11 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:70: IDENTIFIER
                {
                mIDENTIFIER(); 

                }
                break;
            case 12 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:81: WS
                {
                mWS(); 

                }
                break;
            case 13 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:84: COMMENT
                {
                mCOMMENT(); 

                }
                break;
            case 14 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:92: LINE_COMMENT
                {
                mLINE_COMMENT(); 

                }
                break;
            case 15 :
                // D:\\C_Extensions\\Desktop\\My Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCPreprocessor.g:1:105: WILDCARD
                {
                mWILDCARD(); 

                }
                break;

        }

    }


    protected DFA5 dfa5 = new DFA5(this);
    static final String DFA5_eotS =
        "\3\uffff\1\22\1\uffff\1\22\4\uffff\1\22\2\uffff\1\16\3\uffff\1"+
        "\22\2\uffff\1\22\4\uffff\1\22\3\uffff\2\22\1\42\1\22\1\44\1\uffff"+
        "\1\22\1\uffff\1\46\1\uffff";
    static final String DFA5_eofS =
        "\47\uffff";
    static final String DFA5_minS =
        "\1\0\2\uffff\1\150\1\uffff\1\157\4\uffff\1\101\2\uffff\1\52\3\uffff"+
        "\1\162\2\uffff\1\151\4\uffff\1\122\3\uffff\1\145\1\144\1\43\1\141"+
        "\1\43\1\uffff\1\144\1\uffff\1\43\1\uffff";
    static final String DFA5_maxS =
        "\1\uffff\2\uffff\1\150\1\uffff\1\157\4\uffff\1\101\2\uffff\1\57"+
        "\3\uffff\1\162\2\uffff\1\151\4\uffff\1\122\3\uffff\1\145\1\144\1"+
        "\172\1\141\1\172\1\uffff\1\144\1\uffff\1\172\1\uffff";
    static final String DFA5_acceptS =
        "\1\uffff\1\1\1\2\1\uffff\1\4\1\uffff\1\6\1\7\1\10\1\11\1\uffff"+
        "\1\13\1\14\1\uffff\1\17\1\1\1\2\1\uffff\1\13\1\4\1\uffff\1\6\1\7"+
        "\1\10\1\11\1\uffff\1\14\1\15\1\16\5\uffff\1\12\1\uffff\1\5\1\uffff"+
        "\1\3";
    static final String DFA5_specialS =
        "\1\0\46\uffff}>";
    static final String[] DFA5_transitionS = {
            "\11\16\2\14\1\16\2\14\22\16\1\14\2\16\2\13\3\16\1\4\1\6\1\13"+
            "\1\16\1\11\1\16\1\13\1\15\12\16\1\10\1\7\5\16\17\13\1\12\12"+
            "\13\4\16\1\13\1\16\23\13\1\3\1\13\1\5\4\13\1\1\1\16\1\2\uff82"+
            "\16",
            "",
            "",
            "\1\21",
            "",
            "\1\24",
            "",
            "",
            "",
            "",
            "\1\31",
            "",
            "",
            "\1\33\4\uffff\1\34",
            "",
            "",
            "",
            "\1\35",
            "",
            "",
            "\1\36",
            "",
            "",
            "",
            "",
            "\1\37",
            "",
            "",
            "",
            "\1\40",
            "\1\41",
            "\2\22\5\uffff\1\22\3\uffff\1\22\1\uffff\12\22\7\uffff\32\22"+
            "\4\uffff\1\22\1\uffff\32\22",
            "\1\43",
            "\2\22\5\uffff\1\22\3\uffff\1\22\1\uffff\12\22\7\uffff\32\22"+
            "\4\uffff\1\22\1\uffff\32\22",
            "",
            "\1\45",
            "",
            "\2\22\5\uffff\1\22\3\uffff\1\22\1\uffff\12\22\7\uffff\32\22"+
            "\4\uffff\1\22\1\uffff\32\22",
            ""
    };

    static final short[] DFA5_eot = DFA.unpackEncodedString(DFA5_eotS);
    static final short[] DFA5_eof = DFA.unpackEncodedString(DFA5_eofS);
    static final char[] DFA5_min = DFA.unpackEncodedStringToUnsignedChars(DFA5_minS);
    static final char[] DFA5_max = DFA.unpackEncodedStringToUnsignedChars(DFA5_maxS);
    static final short[] DFA5_accept = DFA.unpackEncodedString(DFA5_acceptS);
    static final short[] DFA5_special = DFA.unpackEncodedString(DFA5_specialS);
    static final short[][] DFA5_transition;

    static {
        int numStates = DFA5_transitionS.length;
        DFA5_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA5_transition[i] = DFA.unpackEncodedString(DFA5_transitionS[i]);
        }
    }

    class DFA5 extends DFA {

        public DFA5(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 5;
            this.eot = DFA5_eot;
            this.eof = DFA5_eof;
            this.min = DFA5_min;
            this.max = DFA5_max;
            this.accept = DFA5_accept;
            this.special = DFA5_special;
            this.transition = DFA5_transition;
        }
        public String getDescription() {
            return "1:1: Tokens : ( T__14 | T__15 | T__16 | T__17 | T__18 | T__19 | T__20 | T__21 | T__22 | T__23 | IDENTIFIER | WS | COMMENT | LINE_COMMENT | WILDCARD );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            IntStream input = _input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA5_0 = input.LA(1);

                        s = -1;
                        if ( (LA5_0=='{') ) {s = 1;}

                        else if ( (LA5_0=='}') ) {s = 2;}

                        else if ( (LA5_0=='t') ) {s = 3;}

                        else if ( (LA5_0=='(') ) {s = 4;}

                        else if ( (LA5_0=='v') ) {s = 5;}

                        else if ( (LA5_0==')') ) {s = 6;}

                        else if ( (LA5_0==';') ) {s = 7;}

                        else if ( (LA5_0==':') ) {s = 8;}

                        else if ( (LA5_0==',') ) {s = 9;}

                        else if ( (LA5_0=='P') ) {s = 10;}

                        else if ( ((LA5_0>='#' && LA5_0<='$')||LA5_0=='*'||LA5_0=='.'||(LA5_0>='A' && LA5_0<='O')||(LA5_0>='Q' && LA5_0<='Z')||LA5_0=='_'||(LA5_0>='a' && LA5_0<='s')||LA5_0=='u'||(LA5_0>='w' && LA5_0<='z')) ) {s = 11;}

                        else if ( ((LA5_0>='\t' && LA5_0<='\n')||(LA5_0>='\f' && LA5_0<='\r')||LA5_0==' ') ) {s = 12;}

                        else if ( (LA5_0=='/') ) {s = 13;}

                        else if ( ((LA5_0>='\u0000' && LA5_0<='\b')||LA5_0=='\u000B'||(LA5_0>='\u000E' && LA5_0<='\u001F')||(LA5_0>='!' && LA5_0<='\"')||(LA5_0>='%' && LA5_0<='\'')||LA5_0=='+'||LA5_0=='-'||(LA5_0>='0' && LA5_0<='9')||(LA5_0>='<' && LA5_0<='@')||(LA5_0>='[' && LA5_0<='^')||LA5_0=='`'||LA5_0=='|'||(LA5_0>='~' && LA5_0<='\uFFFF')) ) {s = 14;}

                        if ( s>=0 ) return s;
                        break;
            }
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 5, _s, input);
            error(nvae);
            throw nvae;
        }
    }
 

}