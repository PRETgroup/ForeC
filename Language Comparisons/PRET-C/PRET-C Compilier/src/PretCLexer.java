// $ANTLR 3.1.2 C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g 2014-09-02 19:10:02

import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

public class PretCLexer extends Lexer {
    public static final int ITERATION_STATEMENT_TOK=13;
    public static final int FloatTypeSuffix=34;
    public static final int PRET_DEF_TOK=20;
    public static final int LETTER=29;
    public static final int EOF=-1;
    public static final int EMPTY_TOK=16;
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
    public static final int T__85=85;
    public static final int JUMP_STATMENT_TOK=14;
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
    public static final int T__103=103;
    public static final int T__59=59;
    public static final int T__104=104;
    public static final int T__105=105;
    public static final int T__106=106;
    public static final int T__111=111;
    public static final int T__110=110;
    public static final int T__113=113;
    public static final int ABORT_TOK=18;
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
    public static final int LABELED_STATMENT_TOK=10;
    public static final int OCTAL_LITERAL=25;
    public static final int T__102=102;
    public static final int T__101=101;
    public static final int T__100=100;
    public static final int SELECTION_STATMENT_TOK=12;
    public static final int GLOBAL_DECLARATION_TOK=7;
    public static final int UnicodeEscape=36;
    public static final int OctalEscape=35;

    // delegates
    // delegators

    public PretCLexer() {;} 
    public PretCLexer(CharStream input) {
        this(input, new RecognizerSharedState());
    }
    public PretCLexer(CharStream input, RecognizerSharedState state) {
        super(input,state);

    }
    public String getGrammarFileName() { return "C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g"; }

    // $ANTLR start "T__40"
    public final void mT__40() throws RecognitionException {
        try {
            int _type = T__40;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:3:7: ( 'PRETDEF' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:3:9: 'PRETDEF'
            {
            match("PRETDEF"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__40"

    // $ANTLR start "T__41"
    public final void mT__41() throws RecognitionException {
        try {
            int _type = T__41;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:4:7: ( ';' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:4:9: ';'
            {
            match(';'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__41"

    // $ANTLR start "T__42"
    public final void mT__42() throws RecognitionException {
        try {
            int _type = T__42;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:5:7: ( 'ReactiveInput' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:5:9: 'ReactiveInput'
            {
            match("ReactiveInput"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__42"

    // $ANTLR start "T__43"
    public final void mT__43() throws RecognitionException {
        try {
            int _type = T__43;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:6:7: ( 'ReactiveOutput' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:6:9: 'ReactiveOutput'
            {
            match("ReactiveOutput"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__43"

    // $ANTLR start "T__44"
    public final void mT__44() throws RecognitionException {
        try {
            int _type = T__44;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:7:7: ( '=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:7:9: '='
            {
            match('='); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__44"

    // $ANTLR start "T__45"
    public final void mT__45() throws RecognitionException {
        try {
            int _type = T__45;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:8:7: ( ',' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:8:9: ','
            {
            match(','); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__45"

    // $ANTLR start "T__46"
    public final void mT__46() throws RecognitionException {
        try {
            int _type = T__46;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:9:7: ( '#range' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:9:9: '#range'
            {
            match("#range"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__46"

    // $ANTLR start "T__47"
    public final void mT__47() throws RecognitionException {
        try {
            int _type = T__47;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:10:7: ( 'to' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:10:9: 'to'
            {
            match("to"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__47"

    // $ANTLR start "T__48"
    public final void mT__48() throws RecognitionException {
        try {
            int _type = T__48;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:11:7: ( 'thread' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:11:9: 'thread'
            {
            match("thread"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__48"

    // $ANTLR start "T__49"
    public final void mT__49() throws RecognitionException {
        try {
            int _type = T__49;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:12:7: ( '(' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:12:9: '('
            {
            match('('); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__49"

    // $ANTLR start "T__50"
    public final void mT__50() throws RecognitionException {
        try {
            int _type = T__50;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:13:7: ( 'void' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:13:9: 'void'
            {
            match("void"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__50"

    // $ANTLR start "T__51"
    public final void mT__51() throws RecognitionException {
        try {
            int _type = T__51;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:14:7: ( ')' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:14:9: ')'
            {
            match(')'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__51"

    // $ANTLR start "T__52"
    public final void mT__52() throws RecognitionException {
        try {
            int _type = T__52;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:15:7: ( 'typedef' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:15:9: 'typedef'
            {
            match("typedef"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__52"

    // $ANTLR start "T__53"
    public final void mT__53() throws RecognitionException {
        try {
            int _type = T__53;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:16:7: ( 'extern' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:16:9: 'extern'
            {
            match("extern"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__53"

    // $ANTLR start "T__54"
    public final void mT__54() throws RecognitionException {
        try {
            int _type = T__54;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:17:7: ( 'static' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:17:9: 'static'
            {
            match("static"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__54"

    // $ANTLR start "T__55"
    public final void mT__55() throws RecognitionException {
        try {
            int _type = T__55;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:18:7: ( 'auto' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:18:9: 'auto'
            {
            match("auto"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__55"

    // $ANTLR start "T__56"
    public final void mT__56() throws RecognitionException {
        try {
            int _type = T__56;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:19:7: ( 'register' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:19:9: 'register'
            {
            match("register"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__56"

    // $ANTLR start "T__57"
    public final void mT__57() throws RecognitionException {
        try {
            int _type = T__57;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:20:7: ( 'unsigned' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:20:9: 'unsigned'
            {
            match("unsigned"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__57"

    // $ANTLR start "T__58"
    public final void mT__58() throws RecognitionException {
        try {
            int _type = T__58;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:21:7: ( 'signed' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:21:9: 'signed'
            {
            match("signed"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__58"

    // $ANTLR start "T__59"
    public final void mT__59() throws RecognitionException {
        try {
            int _type = T__59;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:22:7: ( 'char' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:22:9: 'char'
            {
            match("char"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__59"

    // $ANTLR start "T__60"
    public final void mT__60() throws RecognitionException {
        try {
            int _type = T__60;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:23:7: ( 'short' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:23:9: 'short'
            {
            match("short"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__60"

    // $ANTLR start "T__61"
    public final void mT__61() throws RecognitionException {
        try {
            int _type = T__61;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:24:7: ( 'int' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:24:9: 'int'
            {
            match("int"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__61"

    // $ANTLR start "T__62"
    public final void mT__62() throws RecognitionException {
        try {
            int _type = T__62;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:25:7: ( 'long' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:25:9: 'long'
            {
            match("long"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__62"

    // $ANTLR start "T__63"
    public final void mT__63() throws RecognitionException {
        try {
            int _type = T__63;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:26:7: ( 'float' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:26:9: 'float'
            {
            match("float"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__63"

    // $ANTLR start "T__64"
    public final void mT__64() throws RecognitionException {
        try {
            int _type = T__64;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:27:7: ( 'double' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:27:9: 'double'
            {
            match("double"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__64"

    // $ANTLR start "T__65"
    public final void mT__65() throws RecognitionException {
        try {
            int _type = T__65;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:28:7: ( '{' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:28:9: '{'
            {
            match('{'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__65"

    // $ANTLR start "T__66"
    public final void mT__66() throws RecognitionException {
        try {
            int _type = T__66;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:29:7: ( '}' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:29:9: '}'
            {
            match('}'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__66"

    // $ANTLR start "T__67"
    public final void mT__67() throws RecognitionException {
        try {
            int _type = T__67;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:30:7: ( 'struct' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:30:9: 'struct'
            {
            match("struct"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__67"

    // $ANTLR start "T__68"
    public final void mT__68() throws RecognitionException {
        try {
            int _type = T__68;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:31:7: ( 'union' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:31:9: 'union'
            {
            match("union"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__68"

    // $ANTLR start "T__69"
    public final void mT__69() throws RecognitionException {
        try {
            int _type = T__69;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:32:7: ( ':' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:32:9: ':'
            {
            match(':'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__69"

    // $ANTLR start "T__70"
    public final void mT__70() throws RecognitionException {
        try {
            int _type = T__70;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:33:7: ( 'enum' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:33:9: 'enum'
            {
            match("enum"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__70"

    // $ANTLR start "T__71"
    public final void mT__71() throws RecognitionException {
        try {
            int _type = T__71;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:34:7: ( 'const' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:34:9: 'const'
            {
            match("const"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__71"

    // $ANTLR start "T__72"
    public final void mT__72() throws RecognitionException {
        try {
            int _type = T__72;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:35:7: ( 'volatile' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:35:9: 'volatile'
            {
            match("volatile"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__72"

    // $ANTLR start "T__73"
    public final void mT__73() throws RecognitionException {
        try {
            int _type = T__73;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:36:7: ( '[' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:36:9: '['
            {
            match('['); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__73"

    // $ANTLR start "T__74"
    public final void mT__74() throws RecognitionException {
        try {
            int _type = T__74;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:37:7: ( ']' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:37:9: ']'
            {
            match(']'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__74"

    // $ANTLR start "T__75"
    public final void mT__75() throws RecognitionException {
        try {
            int _type = T__75;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:38:7: ( '*' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:38:9: '*'
            {
            match('*'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__75"

    // $ANTLR start "T__76"
    public final void mT__76() throws RecognitionException {
        try {
            int _type = T__76;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:39:7: ( '...' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:39:9: '...'
            {
            match("..."); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__76"

    // $ANTLR start "T__77"
    public final void mT__77() throws RecognitionException {
        try {
            int _type = T__77;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:40:7: ( '+' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:40:9: '+'
            {
            match('+'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__77"

    // $ANTLR start "T__78"
    public final void mT__78() throws RecognitionException {
        try {
            int _type = T__78;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:41:7: ( '-' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:41:9: '-'
            {
            match('-'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__78"

    // $ANTLR start "T__79"
    public final void mT__79() throws RecognitionException {
        try {
            int _type = T__79;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:42:7: ( '/' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:42:9: '/'
            {
            match('/'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__79"

    // $ANTLR start "T__80"
    public final void mT__80() throws RecognitionException {
        try {
            int _type = T__80;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:43:7: ( '%' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:43:9: '%'
            {
            match('%'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__80"

    // $ANTLR start "T__81"
    public final void mT__81() throws RecognitionException {
        try {
            int _type = T__81;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:44:7: ( '++' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:44:9: '++'
            {
            match("++"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__81"

    // $ANTLR start "T__82"
    public final void mT__82() throws RecognitionException {
        try {
            int _type = T__82;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:45:7: ( '--' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:45:9: '--'
            {
            match("--"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__82"

    // $ANTLR start "T__83"
    public final void mT__83() throws RecognitionException {
        try {
            int _type = T__83;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:46:7: ( 'sizeof' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:46:9: 'sizeof'
            {
            match("sizeof"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__83"

    // $ANTLR start "T__84"
    public final void mT__84() throws RecognitionException {
        try {
            int _type = T__84;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:47:7: ( '.' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:47:9: '.'
            {
            match('.'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__84"

    // $ANTLR start "T__85"
    public final void mT__85() throws RecognitionException {
        try {
            int _type = T__85;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:48:7: ( '->' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:48:9: '->'
            {
            match("->"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__85"

    // $ANTLR start "T__86"
    public final void mT__86() throws RecognitionException {
        try {
            int _type = T__86;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:49:7: ( '&' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:49:9: '&'
            {
            match('&'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__86"

    // $ANTLR start "T__87"
    public final void mT__87() throws RecognitionException {
        try {
            int _type = T__87;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:50:7: ( '~' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:50:9: '~'
            {
            match('~'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__87"

    // $ANTLR start "T__88"
    public final void mT__88() throws RecognitionException {
        try {
            int _type = T__88;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:51:7: ( '!' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:51:9: '!'
            {
            match('!'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__88"

    // $ANTLR start "T__89"
    public final void mT__89() throws RecognitionException {
        try {
            int _type = T__89;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:52:7: ( '*=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:52:9: '*='
            {
            match("*="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__89"

    // $ANTLR start "T__90"
    public final void mT__90() throws RecognitionException {
        try {
            int _type = T__90;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:53:7: ( '/=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:53:9: '/='
            {
            match("/="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__90"

    // $ANTLR start "T__91"
    public final void mT__91() throws RecognitionException {
        try {
            int _type = T__91;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:54:7: ( '%=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:54:9: '%='
            {
            match("%="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__91"

    // $ANTLR start "T__92"
    public final void mT__92() throws RecognitionException {
        try {
            int _type = T__92;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:55:7: ( '+=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:55:9: '+='
            {
            match("+="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__92"

    // $ANTLR start "T__93"
    public final void mT__93() throws RecognitionException {
        try {
            int _type = T__93;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:56:7: ( '-=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:56:9: '-='
            {
            match("-="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__93"

    // $ANTLR start "T__94"
    public final void mT__94() throws RecognitionException {
        try {
            int _type = T__94;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:57:7: ( '<<=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:57:9: '<<='
            {
            match("<<="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__94"

    // $ANTLR start "T__95"
    public final void mT__95() throws RecognitionException {
        try {
            int _type = T__95;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:58:7: ( '>>=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:58:9: '>>='
            {
            match(">>="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__95"

    // $ANTLR start "T__96"
    public final void mT__96() throws RecognitionException {
        try {
            int _type = T__96;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:59:7: ( '&=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:59:9: '&='
            {
            match("&="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__96"

    // $ANTLR start "T__97"
    public final void mT__97() throws RecognitionException {
        try {
            int _type = T__97;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:60:7: ( '^=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:60:9: '^='
            {
            match("^="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__97"

    // $ANTLR start "T__98"
    public final void mT__98() throws RecognitionException {
        try {
            int _type = T__98;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:61:7: ( '|=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:61:9: '|='
            {
            match("|="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__98"

    // $ANTLR start "T__99"
    public final void mT__99() throws RecognitionException {
        try {
            int _type = T__99;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:62:7: ( '?' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:62:9: '?'
            {
            match('?'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__99"

    // $ANTLR start "T__100"
    public final void mT__100() throws RecognitionException {
        try {
            int _type = T__100;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:63:8: ( '||' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:63:10: '||'
            {
            match("||"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__100"

    // $ANTLR start "T__101"
    public final void mT__101() throws RecognitionException {
        try {
            int _type = T__101;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:64:8: ( '&&' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:64:10: '&&'
            {
            match("&&"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__101"

    // $ANTLR start "T__102"
    public final void mT__102() throws RecognitionException {
        try {
            int _type = T__102;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:65:8: ( '|' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:65:10: '|'
            {
            match('|'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__102"

    // $ANTLR start "T__103"
    public final void mT__103() throws RecognitionException {
        try {
            int _type = T__103;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:66:8: ( '^' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:66:10: '^'
            {
            match('^'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__103"

    // $ANTLR start "T__104"
    public final void mT__104() throws RecognitionException {
        try {
            int _type = T__104;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:67:8: ( '==' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:67:10: '=='
            {
            match("=="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__104"

    // $ANTLR start "T__105"
    public final void mT__105() throws RecognitionException {
        try {
            int _type = T__105;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:68:8: ( '!=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:68:10: '!='
            {
            match("!="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__105"

    // $ANTLR start "T__106"
    public final void mT__106() throws RecognitionException {
        try {
            int _type = T__106;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:69:8: ( '<' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:69:10: '<'
            {
            match('<'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__106"

    // $ANTLR start "T__107"
    public final void mT__107() throws RecognitionException {
        try {
            int _type = T__107;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:70:8: ( '>' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:70:10: '>'
            {
            match('>'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__107"

    // $ANTLR start "T__108"
    public final void mT__108() throws RecognitionException {
        try {
            int _type = T__108;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:71:8: ( '<=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:71:10: '<='
            {
            match("<="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__108"

    // $ANTLR start "T__109"
    public final void mT__109() throws RecognitionException {
        try {
            int _type = T__109;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:72:8: ( '>=' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:72:10: '>='
            {
            match(">="); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__109"

    // $ANTLR start "T__110"
    public final void mT__110() throws RecognitionException {
        try {
            int _type = T__110;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:73:8: ( '<<' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:73:10: '<<'
            {
            match("<<"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__110"

    // $ANTLR start "T__111"
    public final void mT__111() throws RecognitionException {
        try {
            int _type = T__111;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:74:8: ( '>>' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:74:10: '>>'
            {
            match(">>"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__111"

    // $ANTLR start "T__112"
    public final void mT__112() throws RecognitionException {
        try {
            int _type = T__112;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:75:8: ( 'EOT' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:75:10: 'EOT'
            {
            match("EOT"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__112"

    // $ANTLR start "T__113"
    public final void mT__113() throws RecognitionException {
        try {
            int _type = T__113;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:76:8: ( 'case' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:76:10: 'case'
            {
            match("case"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__113"

    // $ANTLR start "T__114"
    public final void mT__114() throws RecognitionException {
        try {
            int _type = T__114;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:77:8: ( 'default' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:77:10: 'default'
            {
            match("default"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__114"

    // $ANTLR start "T__115"
    public final void mT__115() throws RecognitionException {
        try {
            int _type = T__115;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:78:8: ( 'sabort' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:78:10: 'sabort'
            {
            match("sabort"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__115"

    // $ANTLR start "T__116"
    public final void mT__116() throws RecognitionException {
        try {
            int _type = T__116;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:79:8: ( 'when' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:79:10: 'when'
            {
            match("when"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__116"

    // $ANTLR start "T__117"
    public final void mT__117() throws RecognitionException {
        try {
            int _type = T__117;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:80:8: ( 'abort' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:80:10: 'abort'
            {
            match("abort"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__117"

    // $ANTLR start "T__118"
    public final void mT__118() throws RecognitionException {
        try {
            int _type = T__118;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:81:8: ( 'wabort' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:81:10: 'wabort'
            {
            match("wabort"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__118"

    // $ANTLR start "T__119"
    public final void mT__119() throws RecognitionException {
        try {
            int _type = T__119;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:82:8: ( 'PAR' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:82:10: 'PAR'
            {
            match("PAR"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__119"

    // $ANTLR start "T__120"
    public final void mT__120() throws RecognitionException {
        try {
            int _type = T__120;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:83:8: ( 'if' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:83:10: 'if'
            {
            match("if"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__120"

    // $ANTLR start "T__121"
    public final void mT__121() throws RecognitionException {
        try {
            int _type = T__121;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:84:8: ( 'else' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:84:10: 'else'
            {
            match("else"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__121"

    // $ANTLR start "T__122"
    public final void mT__122() throws RecognitionException {
        try {
            int _type = T__122;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:85:8: ( 'switch' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:85:10: 'switch'
            {
            match("switch"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__122"

    // $ANTLR start "T__123"
    public final void mT__123() throws RecognitionException {
        try {
            int _type = T__123;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:86:8: ( 'while' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:86:10: 'while'
            {
            match("while"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__123"

    // $ANTLR start "T__124"
    public final void mT__124() throws RecognitionException {
        try {
            int _type = T__124;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:87:8: ( 'do' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:87:10: 'do'
            {
            match("do"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__124"

    // $ANTLR start "T__125"
    public final void mT__125() throws RecognitionException {
        try {
            int _type = T__125;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:88:8: ( 'for' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:88:10: 'for'
            {
            match("for"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__125"

    // $ANTLR start "T__126"
    public final void mT__126() throws RecognitionException {
        try {
            int _type = T__126;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:89:8: ( 'goto' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:89:10: 'goto'
            {
            match("goto"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__126"

    // $ANTLR start "T__127"
    public final void mT__127() throws RecognitionException {
        try {
            int _type = T__127;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:90:8: ( 'continue' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:90:10: 'continue'
            {
            match("continue"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__127"

    // $ANTLR start "T__128"
    public final void mT__128() throws RecognitionException {
        try {
            int _type = T__128;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:91:8: ( 'break' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:91:10: 'break'
            {
            match("break"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__128"

    // $ANTLR start "T__129"
    public final void mT__129() throws RecognitionException {
        try {
            int _type = T__129;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:92:8: ( 'return' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:92:10: 'return'
            {
            match("return"); 


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "T__129"

    // $ANTLR start "IDENTIFIER"
    public final void mIDENTIFIER() throws RecognitionException {
        try {
            int _type = IDENTIFIER;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1482:2: ( LETTER ( LETTER | '0' .. '9' )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1482:4: LETTER ( LETTER | '0' .. '9' )*
            {
            mLETTER(); 
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1482:11: ( LETTER | '0' .. '9' )*
            loop1:
            do {
                int alt1=2;
                int LA1_0 = input.LA(1);

                if ( (LA1_0=='$'||(LA1_0>='0' && LA1_0<='9')||(LA1_0>='A' && LA1_0<='Z')||LA1_0=='_'||(LA1_0>='a' && LA1_0<='z')) ) {
                    alt1=1;
                }


                switch (alt1) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
            	    {
            	    if ( input.LA(1)=='$'||(input.LA(1)>='0' && input.LA(1)<='9')||(input.LA(1)>='A' && input.LA(1)<='Z')||input.LA(1)=='_'||(input.LA(1)>='a' && input.LA(1)<='z') ) {
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
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1487:2: ( '$' | 'A' .. 'Z' | 'a' .. 'z' | '_' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
            {
            if ( input.LA(1)=='$'||(input.LA(1)>='A' && input.LA(1)<='Z')||input.LA(1)=='_'||(input.LA(1)>='a' && input.LA(1)<='z') ) {
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

    // $ANTLR start "CHARACTER_LITERAL"
    public final void mCHARACTER_LITERAL() throws RecognitionException {
        try {
            int _type = CHARACTER_LITERAL;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1494:5: ( '\\'' ( EscapeSequence | ~ ( '\\'' | '\\\\' ) ) '\\'' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1494:9: '\\'' ( EscapeSequence | ~ ( '\\'' | '\\\\' ) ) '\\''
            {
            match('\''); 
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1494:14: ( EscapeSequence | ~ ( '\\'' | '\\\\' ) )
            int alt2=2;
            int LA2_0 = input.LA(1);

            if ( (LA2_0=='\\') ) {
                alt2=1;
            }
            else if ( ((LA2_0>='\u0000' && LA2_0<='&')||(LA2_0>='(' && LA2_0<='[')||(LA2_0>=']' && LA2_0<='\uFFFF')) ) {
                alt2=2;
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 2, 0, input);

                throw nvae;
            }
            switch (alt2) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1494:16: EscapeSequence
                    {
                    mEscapeSequence(); 

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1494:33: ~ ( '\\'' | '\\\\' )
                    {
                    if ( (input.LA(1)>='\u0000' && input.LA(1)<='&')||(input.LA(1)>='(' && input.LA(1)<='[')||(input.LA(1)>=']' && input.LA(1)<='\uFFFF') ) {
                        input.consume();

                    }
                    else {
                        MismatchedSetException mse = new MismatchedSetException(null,input);
                        recover(mse);
                        throw mse;}


                    }
                    break;

            }

            match('\''); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "CHARACTER_LITERAL"

    // $ANTLR start "STRING_LITERAL"
    public final void mSTRING_LITERAL() throws RecognitionException {
        try {
            int _type = STRING_LITERAL;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1498:5: ( '\"' ( EscapeSequence | ~ ( '\\\\' | '\"' ) )* '\"' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1498:8: '\"' ( EscapeSequence | ~ ( '\\\\' | '\"' ) )* '\"'
            {
            match('\"'); 
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1498:12: ( EscapeSequence | ~ ( '\\\\' | '\"' ) )*
            loop3:
            do {
                int alt3=3;
                int LA3_0 = input.LA(1);

                if ( (LA3_0=='\\') ) {
                    alt3=1;
                }
                else if ( ((LA3_0>='\u0000' && LA3_0<='!')||(LA3_0>='#' && LA3_0<='[')||(LA3_0>=']' && LA3_0<='\uFFFF')) ) {
                    alt3=2;
                }


                switch (alt3) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1498:14: EscapeSequence
            	    {
            	    mEscapeSequence(); 

            	    }
            	    break;
            	case 2 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1498:31: ~ ( '\\\\' | '\"' )
            	    {
            	    if ( (input.LA(1)>='\u0000' && input.LA(1)<='!')||(input.LA(1)>='#' && input.LA(1)<='[')||(input.LA(1)>=']' && input.LA(1)<='\uFFFF') ) {
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

            match('\"'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "STRING_LITERAL"

    // $ANTLR start "HEX_LITERAL"
    public final void mHEX_LITERAL() throws RecognitionException {
        try {
            int _type = HEX_LITERAL;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1501:13: ( '0' ( 'x' | 'X' ) ( HexDigit )+ ( IntegerTypeSuffix )? )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1501:15: '0' ( 'x' | 'X' ) ( HexDigit )+ ( IntegerTypeSuffix )?
            {
            match('0'); 
            if ( input.LA(1)=='X'||input.LA(1)=='x' ) {
                input.consume();

            }
            else {
                MismatchedSetException mse = new MismatchedSetException(null,input);
                recover(mse);
                throw mse;}

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1501:29: ( HexDigit )+
            int cnt4=0;
            loop4:
            do {
                int alt4=2;
                int LA4_0 = input.LA(1);

                if ( ((LA4_0>='0' && LA4_0<='9')||(LA4_0>='A' && LA4_0<='F')||(LA4_0>='a' && LA4_0<='f')) ) {
                    alt4=1;
                }


                switch (alt4) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1501:29: HexDigit
            	    {
            	    mHexDigit(); 

            	    }
            	    break;

            	default :
            	    if ( cnt4 >= 1 ) break loop4;
                        EarlyExitException eee =
                            new EarlyExitException(4, input);
                        throw eee;
                }
                cnt4++;
            } while (true);

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1501:39: ( IntegerTypeSuffix )?
            int alt5=2;
            int LA5_0 = input.LA(1);

            if ( (LA5_0=='L'||LA5_0=='U'||LA5_0=='l'||LA5_0=='u') ) {
                alt5=1;
            }
            switch (alt5) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1501:39: IntegerTypeSuffix
                    {
                    mIntegerTypeSuffix(); 

                    }
                    break;

            }


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "HEX_LITERAL"

    // $ANTLR start "DECIMAL_LITERAL"
    public final void mDECIMAL_LITERAL() throws RecognitionException {
        try {
            int _type = DECIMAL_LITERAL;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1503:17: ( ( '0' | '1' .. '9' ( '0' .. '9' )* ) ( IntegerTypeSuffix )? )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1503:19: ( '0' | '1' .. '9' ( '0' .. '9' )* ) ( IntegerTypeSuffix )?
            {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1503:19: ( '0' | '1' .. '9' ( '0' .. '9' )* )
            int alt7=2;
            int LA7_0 = input.LA(1);

            if ( (LA7_0=='0') ) {
                alt7=1;
            }
            else if ( ((LA7_0>='1' && LA7_0<='9')) ) {
                alt7=2;
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 7, 0, input);

                throw nvae;
            }
            switch (alt7) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1503:20: '0'
                    {
                    match('0'); 

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1503:26: '1' .. '9' ( '0' .. '9' )*
                    {
                    matchRange('1','9'); 
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1503:35: ( '0' .. '9' )*
                    loop6:
                    do {
                        int alt6=2;
                        int LA6_0 = input.LA(1);

                        if ( ((LA6_0>='0' && LA6_0<='9')) ) {
                            alt6=1;
                        }


                        switch (alt6) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1503:35: '0' .. '9'
                    	    {
                    	    matchRange('0','9'); 

                    	    }
                    	    break;

                    	default :
                    	    break loop6;
                        }
                    } while (true);


                    }
                    break;

            }

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1503:46: ( IntegerTypeSuffix )?
            int alt8=2;
            int LA8_0 = input.LA(1);

            if ( (LA8_0=='L'||LA8_0=='U'||LA8_0=='l'||LA8_0=='u') ) {
                alt8=1;
            }
            switch (alt8) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1503:46: IntegerTypeSuffix
                    {
                    mIntegerTypeSuffix(); 

                    }
                    break;

            }


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "DECIMAL_LITERAL"

    // $ANTLR start "OCTAL_LITERAL"
    public final void mOCTAL_LITERAL() throws RecognitionException {
        try {
            int _type = OCTAL_LITERAL;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1505:15: ( '0' ( '0' .. '7' )+ ( IntegerTypeSuffix )? )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1505:17: '0' ( '0' .. '7' )+ ( IntegerTypeSuffix )?
            {
            match('0'); 
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1505:21: ( '0' .. '7' )+
            int cnt9=0;
            loop9:
            do {
                int alt9=2;
                int LA9_0 = input.LA(1);

                if ( ((LA9_0>='0' && LA9_0<='7')) ) {
                    alt9=1;
                }


                switch (alt9) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1505:22: '0' .. '7'
            	    {
            	    matchRange('0','7'); 

            	    }
            	    break;

            	default :
            	    if ( cnt9 >= 1 ) break loop9;
                        EarlyExitException eee =
                            new EarlyExitException(9, input);
                        throw eee;
                }
                cnt9++;
            } while (true);

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1505:33: ( IntegerTypeSuffix )?
            int alt10=2;
            int LA10_0 = input.LA(1);

            if ( (LA10_0=='L'||LA10_0=='U'||LA10_0=='l'||LA10_0=='u') ) {
                alt10=1;
            }
            switch (alt10) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1505:33: IntegerTypeSuffix
                    {
                    mIntegerTypeSuffix(); 

                    }
                    break;

            }


            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "OCTAL_LITERAL"

    // $ANTLR start "HexDigit"
    public final void mHexDigit() throws RecognitionException {
        try {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1508:10: ( ( '0' .. '9' | 'a' .. 'f' | 'A' .. 'F' ) )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1508:12: ( '0' .. '9' | 'a' .. 'f' | 'A' .. 'F' )
            {
            if ( (input.LA(1)>='0' && input.LA(1)<='9')||(input.LA(1)>='A' && input.LA(1)<='F')||(input.LA(1)>='a' && input.LA(1)<='f') ) {
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
    // $ANTLR end "HexDigit"

    // $ANTLR start "IntegerTypeSuffix"
    public final void mIntegerTypeSuffix() throws RecognitionException {
        try {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1512:2: ( ( 'u' | 'U' )? ( 'l' | 'L' ) | ( 'u' | 'U' ) ( 'l' | 'L' )? )
            int alt13=2;
            int LA13_0 = input.LA(1);

            if ( (LA13_0=='U'||LA13_0=='u') ) {
                int LA13_1 = input.LA(2);

                if ( (LA13_1=='L'||LA13_1=='l') ) {
                    alt13=1;
                }
                else {
                    alt13=2;}
            }
            else if ( (LA13_0=='L'||LA13_0=='l') ) {
                alt13=1;
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 13, 0, input);

                throw nvae;
            }
            switch (alt13) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1512:4: ( 'u' | 'U' )? ( 'l' | 'L' )
                    {
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1512:4: ( 'u' | 'U' )?
                    int alt11=2;
                    int LA11_0 = input.LA(1);

                    if ( (LA11_0=='U'||LA11_0=='u') ) {
                        alt11=1;
                    }
                    switch (alt11) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
                            {
                            if ( input.LA(1)=='U'||input.LA(1)=='u' ) {
                                input.consume();

                            }
                            else {
                                MismatchedSetException mse = new MismatchedSetException(null,input);
                                recover(mse);
                                throw mse;}


                            }
                            break;

                    }

                    if ( input.LA(1)=='L'||input.LA(1)=='l' ) {
                        input.consume();

                    }
                    else {
                        MismatchedSetException mse = new MismatchedSetException(null,input);
                        recover(mse);
                        throw mse;}


                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1513:4: ( 'u' | 'U' ) ( 'l' | 'L' )?
                    {
                    if ( input.LA(1)=='U'||input.LA(1)=='u' ) {
                        input.consume();

                    }
                    else {
                        MismatchedSetException mse = new MismatchedSetException(null,input);
                        recover(mse);
                        throw mse;}

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1513:15: ( 'l' | 'L' )?
                    int alt12=2;
                    int LA12_0 = input.LA(1);

                    if ( (LA12_0=='L'||LA12_0=='l') ) {
                        alt12=1;
                    }
                    switch (alt12) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
                            {
                            if ( input.LA(1)=='L'||input.LA(1)=='l' ) {
                                input.consume();

                            }
                            else {
                                MismatchedSetException mse = new MismatchedSetException(null,input);
                                recover(mse);
                                throw mse;}


                            }
                            break;

                    }


                    }
                    break;

            }
        }
        finally {
        }
    }
    // $ANTLR end "IntegerTypeSuffix"

    // $ANTLR start "FLOATING_POINT_LITERAL"
    public final void mFLOATING_POINT_LITERAL() throws RecognitionException {
        try {
            int _type = FLOATING_POINT_LITERAL;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1517:5: ( ( '0' .. '9' )+ '.' ( '0' .. '9' )* ( Exponent )? ( FloatTypeSuffix )? | '.' ( '0' .. '9' )+ ( Exponent )? ( FloatTypeSuffix )? | ( '0' .. '9' )+ Exponent ( FloatTypeSuffix )? | ( '0' .. '9' )+ ( Exponent )? FloatTypeSuffix )
            int alt25=4;
            alt25 = dfa25.predict(input);
            switch (alt25) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1517:9: ( '0' .. '9' )+ '.' ( '0' .. '9' )* ( Exponent )? ( FloatTypeSuffix )?
                    {
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1517:9: ( '0' .. '9' )+
                    int cnt14=0;
                    loop14:
                    do {
                        int alt14=2;
                        int LA14_0 = input.LA(1);

                        if ( ((LA14_0>='0' && LA14_0<='9')) ) {
                            alt14=1;
                        }


                        switch (alt14) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1517:10: '0' .. '9'
                    	    {
                    	    matchRange('0','9'); 

                    	    }
                    	    break;

                    	default :
                    	    if ( cnt14 >= 1 ) break loop14;
                                EarlyExitException eee =
                                    new EarlyExitException(14, input);
                                throw eee;
                        }
                        cnt14++;
                    } while (true);

                    match('.'); 
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1517:25: ( '0' .. '9' )*
                    loop15:
                    do {
                        int alt15=2;
                        int LA15_0 = input.LA(1);

                        if ( ((LA15_0>='0' && LA15_0<='9')) ) {
                            alt15=1;
                        }


                        switch (alt15) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1517:26: '0' .. '9'
                    	    {
                    	    matchRange('0','9'); 

                    	    }
                    	    break;

                    	default :
                    	    break loop15;
                        }
                    } while (true);

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1517:37: ( Exponent )?
                    int alt16=2;
                    int LA16_0 = input.LA(1);

                    if ( (LA16_0=='E'||LA16_0=='e') ) {
                        alt16=1;
                    }
                    switch (alt16) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1517:37: Exponent
                            {
                            mExponent(); 

                            }
                            break;

                    }

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1517:47: ( FloatTypeSuffix )?
                    int alt17=2;
                    int LA17_0 = input.LA(1);

                    if ( (LA17_0=='D'||LA17_0=='F'||LA17_0=='d'||LA17_0=='f') ) {
                        alt17=1;
                    }
                    switch (alt17) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1517:47: FloatTypeSuffix
                            {
                            mFloatTypeSuffix(); 

                            }
                            break;

                    }


                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1518:9: '.' ( '0' .. '9' )+ ( Exponent )? ( FloatTypeSuffix )?
                    {
                    match('.'); 
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1518:13: ( '0' .. '9' )+
                    int cnt18=0;
                    loop18:
                    do {
                        int alt18=2;
                        int LA18_0 = input.LA(1);

                        if ( ((LA18_0>='0' && LA18_0<='9')) ) {
                            alt18=1;
                        }


                        switch (alt18) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1518:14: '0' .. '9'
                    	    {
                    	    matchRange('0','9'); 

                    	    }
                    	    break;

                    	default :
                    	    if ( cnt18 >= 1 ) break loop18;
                                EarlyExitException eee =
                                    new EarlyExitException(18, input);
                                throw eee;
                        }
                        cnt18++;
                    } while (true);

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1518:25: ( Exponent )?
                    int alt19=2;
                    int LA19_0 = input.LA(1);

                    if ( (LA19_0=='E'||LA19_0=='e') ) {
                        alt19=1;
                    }
                    switch (alt19) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1518:25: Exponent
                            {
                            mExponent(); 

                            }
                            break;

                    }

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1518:35: ( FloatTypeSuffix )?
                    int alt20=2;
                    int LA20_0 = input.LA(1);

                    if ( (LA20_0=='D'||LA20_0=='F'||LA20_0=='d'||LA20_0=='f') ) {
                        alt20=1;
                    }
                    switch (alt20) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1518:35: FloatTypeSuffix
                            {
                            mFloatTypeSuffix(); 

                            }
                            break;

                    }


                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1519:9: ( '0' .. '9' )+ Exponent ( FloatTypeSuffix )?
                    {
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1519:9: ( '0' .. '9' )+
                    int cnt21=0;
                    loop21:
                    do {
                        int alt21=2;
                        int LA21_0 = input.LA(1);

                        if ( ((LA21_0>='0' && LA21_0<='9')) ) {
                            alt21=1;
                        }


                        switch (alt21) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1519:10: '0' .. '9'
                    	    {
                    	    matchRange('0','9'); 

                    	    }
                    	    break;

                    	default :
                    	    if ( cnt21 >= 1 ) break loop21;
                                EarlyExitException eee =
                                    new EarlyExitException(21, input);
                                throw eee;
                        }
                        cnt21++;
                    } while (true);

                    mExponent(); 
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1519:30: ( FloatTypeSuffix )?
                    int alt22=2;
                    int LA22_0 = input.LA(1);

                    if ( (LA22_0=='D'||LA22_0=='F'||LA22_0=='d'||LA22_0=='f') ) {
                        alt22=1;
                    }
                    switch (alt22) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1519:30: FloatTypeSuffix
                            {
                            mFloatTypeSuffix(); 

                            }
                            break;

                    }


                    }
                    break;
                case 4 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1520:9: ( '0' .. '9' )+ ( Exponent )? FloatTypeSuffix
                    {
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1520:9: ( '0' .. '9' )+
                    int cnt23=0;
                    loop23:
                    do {
                        int alt23=2;
                        int LA23_0 = input.LA(1);

                        if ( ((LA23_0>='0' && LA23_0<='9')) ) {
                            alt23=1;
                        }


                        switch (alt23) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1520:10: '0' .. '9'
                    	    {
                    	    matchRange('0','9'); 

                    	    }
                    	    break;

                    	default :
                    	    if ( cnt23 >= 1 ) break loop23;
                                EarlyExitException eee =
                                    new EarlyExitException(23, input);
                                throw eee;
                        }
                        cnt23++;
                    } while (true);

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1520:21: ( Exponent )?
                    int alt24=2;
                    int LA24_0 = input.LA(1);

                    if ( (LA24_0=='E'||LA24_0=='e') ) {
                        alt24=1;
                    }
                    switch (alt24) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1520:21: Exponent
                            {
                            mExponent(); 

                            }
                            break;

                    }

                    mFloatTypeSuffix(); 

                    }
                    break;

            }
            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "FLOATING_POINT_LITERAL"

    // $ANTLR start "Exponent"
    public final void mExponent() throws RecognitionException {
        try {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1524:10: ( ( 'e' | 'E' ) ( '+' | '-' )? ( '0' .. '9' )+ )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1524:12: ( 'e' | 'E' ) ( '+' | '-' )? ( '0' .. '9' )+
            {
            if ( input.LA(1)=='E'||input.LA(1)=='e' ) {
                input.consume();

            }
            else {
                MismatchedSetException mse = new MismatchedSetException(null,input);
                recover(mse);
                throw mse;}

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1524:22: ( '+' | '-' )?
            int alt26=2;
            int LA26_0 = input.LA(1);

            if ( (LA26_0=='+'||LA26_0=='-') ) {
                alt26=1;
            }
            switch (alt26) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:
                    {
                    if ( input.LA(1)=='+'||input.LA(1)=='-' ) {
                        input.consume();

                    }
                    else {
                        MismatchedSetException mse = new MismatchedSetException(null,input);
                        recover(mse);
                        throw mse;}


                    }
                    break;

            }

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1524:33: ( '0' .. '9' )+
            int cnt27=0;
            loop27:
            do {
                int alt27=2;
                int LA27_0 = input.LA(1);

                if ( ((LA27_0>='0' && LA27_0<='9')) ) {
                    alt27=1;
                }


                switch (alt27) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1524:34: '0' .. '9'
            	    {
            	    matchRange('0','9'); 

            	    }
            	    break;

            	default :
            	    if ( cnt27 >= 1 ) break loop27;
                        EarlyExitException eee =
                            new EarlyExitException(27, input);
                        throw eee;
                }
                cnt27++;
            } while (true);


            }

        }
        finally {
        }
    }
    // $ANTLR end "Exponent"

    // $ANTLR start "FloatTypeSuffix"
    public final void mFloatTypeSuffix() throws RecognitionException {
        try {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1527:17: ( ( 'f' | 'F' | 'd' | 'D' ) )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1527:19: ( 'f' | 'F' | 'd' | 'D' )
            {
            if ( input.LA(1)=='D'||input.LA(1)=='F'||input.LA(1)=='d'||input.LA(1)=='f' ) {
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
    // $ANTLR end "FloatTypeSuffix"

    // $ANTLR start "EscapeSequence"
    public final void mEscapeSequence() throws RecognitionException {
        try {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1531:5: ( '\\\\' ( 'b' | 't' | 'n' | 'f' | 'r' | '\\\"' | '\\'' | '\\\\' ) | OctalEscape )
            int alt28=2;
            int LA28_0 = input.LA(1);

            if ( (LA28_0=='\\') ) {
                int LA28_1 = input.LA(2);

                if ( (LA28_1=='\"'||LA28_1=='\''||LA28_1=='\\'||LA28_1=='b'||LA28_1=='f'||LA28_1=='n'||LA28_1=='r'||LA28_1=='t') ) {
                    alt28=1;
                }
                else if ( ((LA28_1>='0' && LA28_1<='7')) ) {
                    alt28=2;
                }
                else {
                    NoViableAltException nvae =
                        new NoViableAltException("", 28, 1, input);

                    throw nvae;
                }
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 28, 0, input);

                throw nvae;
            }
            switch (alt28) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1531:9: '\\\\' ( 'b' | 't' | 'n' | 'f' | 'r' | '\\\"' | '\\'' | '\\\\' )
                    {
                    match('\\'); 
                    if ( input.LA(1)=='\"'||input.LA(1)=='\''||input.LA(1)=='\\'||input.LA(1)=='b'||input.LA(1)=='f'||input.LA(1)=='n'||input.LA(1)=='r'||input.LA(1)=='t' ) {
                        input.consume();

                    }
                    else {
                        MismatchedSetException mse = new MismatchedSetException(null,input);
                        recover(mse);
                        throw mse;}


                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1532:9: OctalEscape
                    {
                    mOctalEscape(); 

                    }
                    break;

            }
        }
        finally {
        }
    }
    // $ANTLR end "EscapeSequence"

    // $ANTLR start "OctalEscape"
    public final void mOctalEscape() throws RecognitionException {
        try {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1537:5: ( '\\\\' ( '0' .. '3' ) ( '0' .. '7' ) ( '0' .. '7' ) | '\\\\' ( '0' .. '7' ) ( '0' .. '7' ) | '\\\\' ( '0' .. '7' ) )
            int alt29=3;
            int LA29_0 = input.LA(1);

            if ( (LA29_0=='\\') ) {
                int LA29_1 = input.LA(2);

                if ( ((LA29_1>='0' && LA29_1<='3')) ) {
                    int LA29_2 = input.LA(3);

                    if ( ((LA29_2>='0' && LA29_2<='7')) ) {
                        int LA29_5 = input.LA(4);

                        if ( ((LA29_5>='0' && LA29_5<='7')) ) {
                            alt29=1;
                        }
                        else {
                            alt29=2;}
                    }
                    else {
                        alt29=3;}
                }
                else if ( ((LA29_1>='4' && LA29_1<='7')) ) {
                    int LA29_3 = input.LA(3);

                    if ( ((LA29_3>='0' && LA29_3<='7')) ) {
                        alt29=2;
                    }
                    else {
                        alt29=3;}
                }
                else {
                    NoViableAltException nvae =
                        new NoViableAltException("", 29, 1, input);

                    throw nvae;
                }
            }
            else {
                NoViableAltException nvae =
                    new NoViableAltException("", 29, 0, input);

                throw nvae;
            }
            switch (alt29) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1537:9: '\\\\' ( '0' .. '3' ) ( '0' .. '7' ) ( '0' .. '7' )
                    {
                    match('\\'); 
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1537:14: ( '0' .. '3' )
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1537:15: '0' .. '3'
                    {
                    matchRange('0','3'); 

                    }

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1537:25: ( '0' .. '7' )
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1537:26: '0' .. '7'
                    {
                    matchRange('0','7'); 

                    }

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1537:36: ( '0' .. '7' )
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1537:37: '0' .. '7'
                    {
                    matchRange('0','7'); 

                    }


                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1538:9: '\\\\' ( '0' .. '7' ) ( '0' .. '7' )
                    {
                    match('\\'); 
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1538:14: ( '0' .. '7' )
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1538:15: '0' .. '7'
                    {
                    matchRange('0','7'); 

                    }

                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1538:25: ( '0' .. '7' )
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1538:26: '0' .. '7'
                    {
                    matchRange('0','7'); 

                    }


                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1539:9: '\\\\' ( '0' .. '7' )
                    {
                    match('\\'); 
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1539:14: ( '0' .. '7' )
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1539:15: '0' .. '7'
                    {
                    matchRange('0','7'); 

                    }


                    }
                    break;

            }
        }
        finally {
        }
    }
    // $ANTLR end "OctalEscape"

    // $ANTLR start "UnicodeEscape"
    public final void mUnicodeEscape() throws RecognitionException {
        try {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1544:5: ( '\\\\' 'u' HexDigit HexDigit HexDigit HexDigit )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1544:9: '\\\\' 'u' HexDigit HexDigit HexDigit HexDigit
            {
            match('\\'); 
            match('u'); 
            mHexDigit(); 
            mHexDigit(); 
            mHexDigit(); 
            mHexDigit(); 

            }

        }
        finally {
        }
    }
    // $ANTLR end "UnicodeEscape"

    // $ANTLR start "WS"
    public final void mWS() throws RecognitionException {
        try {
            int _type = WS;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1547:5: ( ( ' ' | '\\r' | '\\t' | '\\u000C' | '\\n' ) )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1547:8: ( ' ' | '\\r' | '\\t' | '\\u000C' | '\\n' )
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
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1551:5: ( '/*' ( options {greedy=false; } : . )* '*/' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1551:9: '/*' ( options {greedy=false; } : . )* '*/'
            {
            match("/*"); 

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1551:14: ( options {greedy=false; } : . )*
            loop30:
            do {
                int alt30=2;
                int LA30_0 = input.LA(1);

                if ( (LA30_0=='*') ) {
                    int LA30_1 = input.LA(2);

                    if ( (LA30_1=='/') ) {
                        alt30=2;
                    }
                    else if ( ((LA30_1>='\u0000' && LA30_1<='.')||(LA30_1>='0' && LA30_1<='\uFFFF')) ) {
                        alt30=1;
                    }


                }
                else if ( ((LA30_0>='\u0000' && LA30_0<=')')||(LA30_0>='+' && LA30_0<='\uFFFF')) ) {
                    alt30=1;
                }


                switch (alt30) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1551:42: .
            	    {
            	    matchAny(); 

            	    }
            	    break;

            	default :
            	    break loop30;
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
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1555:5: ( '//' (~ ( '\\n' | '\\r' ) )* ( '\\r' )? '\\n' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1555:7: '//' (~ ( '\\n' | '\\r' ) )* ( '\\r' )? '\\n'
            {
            match("//"); 

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1555:12: (~ ( '\\n' | '\\r' ) )*
            loop31:
            do {
                int alt31=2;
                int LA31_0 = input.LA(1);

                if ( ((LA31_0>='\u0000' && LA31_0<='\t')||(LA31_0>='\u000B' && LA31_0<='\f')||(LA31_0>='\u000E' && LA31_0<='\uFFFF')) ) {
                    alt31=1;
                }


                switch (alt31) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1555:12: ~ ( '\\n' | '\\r' )
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
            	    break loop31;
                }
            } while (true);

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1555:26: ( '\\r' )?
            int alt32=2;
            int LA32_0 = input.LA(1);

            if ( (LA32_0=='\r') ) {
                alt32=1;
            }
            switch (alt32) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1555:26: '\\r'
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

    // $ANTLR start "LINE_COMMAND"
    public final void mLINE_COMMAND() throws RecognitionException {
        try {
            int _type = LINE_COMMAND;
            int _channel = DEFAULT_TOKEN_CHANNEL;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1560:5: ( '#' (~ ( '\\n' | '\\r' ) )* ( '\\r' )? '\\n' )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1560:7: '#' (~ ( '\\n' | '\\r' ) )* ( '\\r' )? '\\n'
            {
            match('#'); 
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1560:11: (~ ( '\\n' | '\\r' ) )*
            loop33:
            do {
                int alt33=2;
                int LA33_0 = input.LA(1);

                if ( ((LA33_0>='\u0000' && LA33_0<='\t')||(LA33_0>='\u000B' && LA33_0<='\f')||(LA33_0>='\u000E' && LA33_0<='\uFFFF')) ) {
                    alt33=1;
                }


                switch (alt33) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1560:11: ~ ( '\\n' | '\\r' )
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
            	    break loop33;
                }
            } while (true);

            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1560:25: ( '\\r' )?
            int alt34=2;
            int LA34_0 = input.LA(1);

            if ( (LA34_0=='\r') ) {
                alt34=1;
            }
            switch (alt34) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1560:25: '\\r'
                    {
                    match('\r'); 

                    }
                    break;

            }

            match('\n'); 

            }

            state.type = _type;
            state.channel = _channel;
        }
        finally {
        }
    }
    // $ANTLR end "LINE_COMMAND"

    public void mTokens() throws RecognitionException {
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:8: ( T__40 | T__41 | T__42 | T__43 | T__44 | T__45 | T__46 | T__47 | T__48 | T__49 | T__50 | T__51 | T__52 | T__53 | T__54 | T__55 | T__56 | T__57 | T__58 | T__59 | T__60 | T__61 | T__62 | T__63 | T__64 | T__65 | T__66 | T__67 | T__68 | T__69 | T__70 | T__71 | T__72 | T__73 | T__74 | T__75 | T__76 | T__77 | T__78 | T__79 | T__80 | T__81 | T__82 | T__83 | T__84 | T__85 | T__86 | T__87 | T__88 | T__89 | T__90 | T__91 | T__92 | T__93 | T__94 | T__95 | T__96 | T__97 | T__98 | T__99 | T__100 | T__101 | T__102 | T__103 | T__104 | T__105 | T__106 | T__107 | T__108 | T__109 | T__110 | T__111 | T__112 | T__113 | T__114 | T__115 | T__116 | T__117 | T__118 | T__119 | T__120 | T__121 | T__122 | T__123 | T__124 | T__125 | T__126 | T__127 | T__128 | T__129 | IDENTIFIER | CHARACTER_LITERAL | STRING_LITERAL | HEX_LITERAL | DECIMAL_LITERAL | OCTAL_LITERAL | FLOATING_POINT_LITERAL | WS | COMMENT | LINE_COMMENT | LINE_COMMAND )
        int alt35=101;
        alt35 = dfa35.predict(input);
        switch (alt35) {
            case 1 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:10: T__40
                {
                mT__40(); 

                }
                break;
            case 2 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:16: T__41
                {
                mT__41(); 

                }
                break;
            case 3 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:22: T__42
                {
                mT__42(); 

                }
                break;
            case 4 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:28: T__43
                {
                mT__43(); 

                }
                break;
            case 5 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:34: T__44
                {
                mT__44(); 

                }
                break;
            case 6 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:40: T__45
                {
                mT__45(); 

                }
                break;
            case 7 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:46: T__46
                {
                mT__46(); 

                }
                break;
            case 8 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:52: T__47
                {
                mT__47(); 

                }
                break;
            case 9 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:58: T__48
                {
                mT__48(); 

                }
                break;
            case 10 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:64: T__49
                {
                mT__49(); 

                }
                break;
            case 11 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:70: T__50
                {
                mT__50(); 

                }
                break;
            case 12 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:76: T__51
                {
                mT__51(); 

                }
                break;
            case 13 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:82: T__52
                {
                mT__52(); 

                }
                break;
            case 14 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:88: T__53
                {
                mT__53(); 

                }
                break;
            case 15 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:94: T__54
                {
                mT__54(); 

                }
                break;
            case 16 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:100: T__55
                {
                mT__55(); 

                }
                break;
            case 17 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:106: T__56
                {
                mT__56(); 

                }
                break;
            case 18 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:112: T__57
                {
                mT__57(); 

                }
                break;
            case 19 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:118: T__58
                {
                mT__58(); 

                }
                break;
            case 20 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:124: T__59
                {
                mT__59(); 

                }
                break;
            case 21 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:130: T__60
                {
                mT__60(); 

                }
                break;
            case 22 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:136: T__61
                {
                mT__61(); 

                }
                break;
            case 23 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:142: T__62
                {
                mT__62(); 

                }
                break;
            case 24 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:148: T__63
                {
                mT__63(); 

                }
                break;
            case 25 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:154: T__64
                {
                mT__64(); 

                }
                break;
            case 26 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:160: T__65
                {
                mT__65(); 

                }
                break;
            case 27 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:166: T__66
                {
                mT__66(); 

                }
                break;
            case 28 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:172: T__67
                {
                mT__67(); 

                }
                break;
            case 29 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:178: T__68
                {
                mT__68(); 

                }
                break;
            case 30 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:184: T__69
                {
                mT__69(); 

                }
                break;
            case 31 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:190: T__70
                {
                mT__70(); 

                }
                break;
            case 32 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:196: T__71
                {
                mT__71(); 

                }
                break;
            case 33 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:202: T__72
                {
                mT__72(); 

                }
                break;
            case 34 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:208: T__73
                {
                mT__73(); 

                }
                break;
            case 35 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:214: T__74
                {
                mT__74(); 

                }
                break;
            case 36 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:220: T__75
                {
                mT__75(); 

                }
                break;
            case 37 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:226: T__76
                {
                mT__76(); 

                }
                break;
            case 38 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:232: T__77
                {
                mT__77(); 

                }
                break;
            case 39 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:238: T__78
                {
                mT__78(); 

                }
                break;
            case 40 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:244: T__79
                {
                mT__79(); 

                }
                break;
            case 41 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:250: T__80
                {
                mT__80(); 

                }
                break;
            case 42 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:256: T__81
                {
                mT__81(); 

                }
                break;
            case 43 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:262: T__82
                {
                mT__82(); 

                }
                break;
            case 44 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:268: T__83
                {
                mT__83(); 

                }
                break;
            case 45 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:274: T__84
                {
                mT__84(); 

                }
                break;
            case 46 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:280: T__85
                {
                mT__85(); 

                }
                break;
            case 47 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:286: T__86
                {
                mT__86(); 

                }
                break;
            case 48 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:292: T__87
                {
                mT__87(); 

                }
                break;
            case 49 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:298: T__88
                {
                mT__88(); 

                }
                break;
            case 50 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:304: T__89
                {
                mT__89(); 

                }
                break;
            case 51 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:310: T__90
                {
                mT__90(); 

                }
                break;
            case 52 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:316: T__91
                {
                mT__91(); 

                }
                break;
            case 53 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:322: T__92
                {
                mT__92(); 

                }
                break;
            case 54 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:328: T__93
                {
                mT__93(); 

                }
                break;
            case 55 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:334: T__94
                {
                mT__94(); 

                }
                break;
            case 56 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:340: T__95
                {
                mT__95(); 

                }
                break;
            case 57 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:346: T__96
                {
                mT__96(); 

                }
                break;
            case 58 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:352: T__97
                {
                mT__97(); 

                }
                break;
            case 59 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:358: T__98
                {
                mT__98(); 

                }
                break;
            case 60 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:364: T__99
                {
                mT__99(); 

                }
                break;
            case 61 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:370: T__100
                {
                mT__100(); 

                }
                break;
            case 62 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:377: T__101
                {
                mT__101(); 

                }
                break;
            case 63 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:384: T__102
                {
                mT__102(); 

                }
                break;
            case 64 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:391: T__103
                {
                mT__103(); 

                }
                break;
            case 65 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:398: T__104
                {
                mT__104(); 

                }
                break;
            case 66 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:405: T__105
                {
                mT__105(); 

                }
                break;
            case 67 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:412: T__106
                {
                mT__106(); 

                }
                break;
            case 68 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:419: T__107
                {
                mT__107(); 

                }
                break;
            case 69 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:426: T__108
                {
                mT__108(); 

                }
                break;
            case 70 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:433: T__109
                {
                mT__109(); 

                }
                break;
            case 71 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:440: T__110
                {
                mT__110(); 

                }
                break;
            case 72 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:447: T__111
                {
                mT__111(); 

                }
                break;
            case 73 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:454: T__112
                {
                mT__112(); 

                }
                break;
            case 74 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:461: T__113
                {
                mT__113(); 

                }
                break;
            case 75 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:468: T__114
                {
                mT__114(); 

                }
                break;
            case 76 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:475: T__115
                {
                mT__115(); 

                }
                break;
            case 77 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:482: T__116
                {
                mT__116(); 

                }
                break;
            case 78 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:489: T__117
                {
                mT__117(); 

                }
                break;
            case 79 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:496: T__118
                {
                mT__118(); 

                }
                break;
            case 80 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:503: T__119
                {
                mT__119(); 

                }
                break;
            case 81 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:510: T__120
                {
                mT__120(); 

                }
                break;
            case 82 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:517: T__121
                {
                mT__121(); 

                }
                break;
            case 83 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:524: T__122
                {
                mT__122(); 

                }
                break;
            case 84 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:531: T__123
                {
                mT__123(); 

                }
                break;
            case 85 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:538: T__124
                {
                mT__124(); 

                }
                break;
            case 86 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:545: T__125
                {
                mT__125(); 

                }
                break;
            case 87 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:552: T__126
                {
                mT__126(); 

                }
                break;
            case 88 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:559: T__127
                {
                mT__127(); 

                }
                break;
            case 89 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:566: T__128
                {
                mT__128(); 

                }
                break;
            case 90 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:573: T__129
                {
                mT__129(); 

                }
                break;
            case 91 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:580: IDENTIFIER
                {
                mIDENTIFIER(); 

                }
                break;
            case 92 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:591: CHARACTER_LITERAL
                {
                mCHARACTER_LITERAL(); 

                }
                break;
            case 93 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:609: STRING_LITERAL
                {
                mSTRING_LITERAL(); 

                }
                break;
            case 94 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:624: HEX_LITERAL
                {
                mHEX_LITERAL(); 

                }
                break;
            case 95 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:636: DECIMAL_LITERAL
                {
                mDECIMAL_LITERAL(); 

                }
                break;
            case 96 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:652: OCTAL_LITERAL
                {
                mOCTAL_LITERAL(); 

                }
                break;
            case 97 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:666: FLOATING_POINT_LITERAL
                {
                mFLOATING_POINT_LITERAL(); 

                }
                break;
            case 98 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:689: WS
                {
                mWS(); 

                }
                break;
            case 99 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:692: COMMENT
                {
                mCOMMENT(); 

                }
                break;
            case 100 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:700: LINE_COMMENT
                {
                mLINE_COMMENT(); 

                }
                break;
            case 101 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretC.g:1:713: LINE_COMMAND
                {
                mLINE_COMMAND(); 

                }
                break;

        }

    }


    protected DFA25 dfa25 = new DFA25(this);
    protected DFA35 dfa35 = new DFA35(this);
    static final String DFA25_eotS =
        "\7\uffff\1\10\2\uffff";
    static final String DFA25_eofS =
        "\12\uffff";
    static final String DFA25_minS =
        "\2\56\1\uffff\1\53\2\uffff\2\60\2\uffff";
    static final String DFA25_maxS =
        "\1\71\1\146\1\uffff\1\71\2\uffff\1\71\1\146\2\uffff";
    static final String DFA25_acceptS =
        "\2\uffff\1\2\1\uffff\1\1\1\4\2\uffff\2\3";
    static final String DFA25_specialS =
        "\12\uffff}>";
    static final String[] DFA25_transitionS = {
            "\1\2\1\uffff\12\1",
            "\1\4\1\uffff\12\1\12\uffff\1\5\1\3\1\5\35\uffff\1\5\1\3\1"+
            "\5",
            "",
            "\1\6\1\uffff\1\6\2\uffff\12\7",
            "",
            "",
            "\12\7",
            "\12\7\12\uffff\1\11\1\uffff\1\11\35\uffff\1\11\1\uffff\1\11",
            "",
            ""
    };

    static final short[] DFA25_eot = DFA.unpackEncodedString(DFA25_eotS);
    static final short[] DFA25_eof = DFA.unpackEncodedString(DFA25_eofS);
    static final char[] DFA25_min = DFA.unpackEncodedStringToUnsignedChars(DFA25_minS);
    static final char[] DFA25_max = DFA.unpackEncodedStringToUnsignedChars(DFA25_maxS);
    static final short[] DFA25_accept = DFA.unpackEncodedString(DFA25_acceptS);
    static final short[] DFA25_special = DFA.unpackEncodedString(DFA25_specialS);
    static final short[][] DFA25_transition;

    static {
        int numStates = DFA25_transitionS.length;
        DFA25_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA25_transition[i] = DFA.unpackEncodedString(DFA25_transitionS[i]);
        }
    }

    class DFA25 extends DFA {

        public DFA25(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 25;
            this.eot = DFA25_eot;
            this.eof = DFA25_eof;
            this.min = DFA25_min;
            this.max = DFA25_max;
            this.accept = DFA25_accept;
            this.special = DFA25_special;
            this.transition = DFA25_transition;
        }
        public String getDescription() {
            return "1516:1: FLOATING_POINT_LITERAL : ( ( '0' .. '9' )+ '.' ( '0' .. '9' )* ( Exponent )? ( FloatTypeSuffix )? | '.' ( '0' .. '9' )+ ( Exponent )? ( FloatTypeSuffix )? | ( '0' .. '9' )+ Exponent ( FloatTypeSuffix )? | ( '0' .. '9' )+ ( Exponent )? FloatTypeSuffix );";
        }
    }
    static final String DFA35_eotS =
        "\1\uffff\1\54\1\uffff\1\54\1\66\2\uffff\1\54\1\uffff\1\54\1\uffff"+
        "\12\54\5\uffff\1\124\1\127\1\132\1\136\1\142\1\144\1\147\1\uffff"+
        "\1\151\1\154\1\157\1\161\1\164\1\uffff\4\54\3\uffff\2\174\1\uffff"+
        "\3\54\4\uffff\1\u0082\23\54\1\u009b\3\54\1\u00a0\1\54\27\uffff\1"+
        "\u00a3\2\uffff\1\u00a5\7\uffff\5\54\1\uffff\1\u00ac\1\uffff\1\174"+
        "\1\54\1\u00ae\1\54\2\uffff\27\54\1\u00c9\1\uffff\2\54\1\u00cc\1"+
        "\54\1\uffff\1\54\4\uffff\1\u00cf\5\54\1\uffff\1\54\1\uffff\1\54"+
        "\1\uffff\2\54\1\u00da\2\54\1\u00dd\1\u00de\7\54\1\u00e6\5\54\1\u00ec"+
        "\2\54\1\u00ef\1\uffff\1\u00f0\1\54\1\uffff\2\54\1\uffff\1\u00f4"+
        "\2\54\1\u00f7\3\54\1\uffff\2\54\1\uffff\2\54\2\uffff\4\54\1\u0104"+
        "\2\54\1\uffff\1\u0107\3\54\1\u010b\1\uffff\1\u010c\1\54\2\uffff"+
        "\1\u010e\2\54\1\uffff\1\u0111\1\54\1\uffff\1\u0113\2\54\1\u0116"+
        "\1\u0117\2\54\1\u011a\1\u011b\1\u011c\1\u011d\1\u011e\1\uffff\1"+
        "\u011f\1\u0120\1\uffff\1\54\1\u0122\1\54\2\uffff\1\54\1\uffff\1"+
        "\u0125\1\54\1\uffff\1\u0127\1\uffff\1\u0128\1\54\2\uffff\1\u012a"+
        "\1\54\7\uffff\1\54\1\uffff\2\54\1\uffff\1\u012f\2\uffff\1\54\1\uffff"+
        "\1\u0132\1\u0133\1\u0134\1\u0135\1\uffff\2\54\4\uffff\6\54\1\u013e"+
        "\1\54\1\uffff\1\u0140\1\uffff";
    static final String DFA35_eofS =
        "\u0141\uffff";
    static final String DFA35_minS =
        "\1\11\1\101\1\uffff\1\145\1\75\1\uffff\1\0\1\150\1\uffff\1\157"+
        "\1\uffff\1\154\1\141\1\142\1\145\1\156\1\141\1\146\1\157\1\154\1"+
        "\145\5\uffff\1\75\1\56\1\53\1\55\1\52\1\75\1\46\1\uffff\1\75\1\74"+
        "\3\75\1\uffff\1\117\1\141\1\157\1\162\3\uffff\2\56\1\uffff\1\105"+
        "\1\122\1\141\2\uffff\1\0\1\uffff\1\44\1\162\1\160\1\151\1\164\1"+
        "\165\1\163\1\141\1\147\1\157\1\142\1\151\1\164\1\157\1\147\1\151"+
        "\1\141\1\156\1\163\1\164\1\44\1\156\1\157\1\162\1\44\1\146\27\uffff"+
        "\1\75\2\uffff\1\75\7\uffff\1\124\1\145\1\142\1\164\1\145\1\uffff"+
        "\1\56\1\uffff\1\56\1\124\1\44\1\143\1\0\1\uffff\2\145\1\144\1\141"+
        "\1\145\1\155\1\145\1\164\1\165\1\156\1\145\1\162\1\157\1\164\1\157"+
        "\1\162\1\151\1\165\1\151\1\157\1\162\1\163\1\145\1\44\1\uffff\1"+
        "\147\1\141\1\44\1\142\1\uffff\1\141\4\uffff\1\44\1\156\1\154\2\157"+
        "\1\141\1\uffff\1\104\1\uffff\1\164\1\0\1\141\1\144\1\44\1\164\1"+
        "\162\2\44\1\151\1\143\1\145\1\157\1\164\1\162\1\143\1\44\1\164\1"+
        "\163\1\162\1\147\1\156\1\44\1\164\1\151\1\44\1\uffff\1\44\1\164"+
        "\1\uffff\1\154\1\165\1\uffff\1\44\1\145\1\162\1\44\1\153\1\105\1"+
        "\151\1\0\1\144\1\145\1\uffff\1\151\1\156\2\uffff\1\143\1\164\1\144"+
        "\1\146\1\44\1\164\1\150\1\uffff\1\44\1\164\2\156\1\44\1\uffff\1"+
        "\44\1\156\2\uffff\1\44\1\145\1\154\1\uffff\1\44\1\164\1\uffff\1"+
        "\44\1\106\1\166\1\0\1\44\1\146\1\154\5\44\1\uffff\2\44\1\uffff\1"+
        "\145\1\44\1\145\2\uffff\1\165\1\uffff\1\44\1\164\1\uffff\1\44\1"+
        "\uffff\1\44\1\145\2\uffff\1\44\1\145\7\uffff\1\162\1\uffff\1\144"+
        "\1\145\1\uffff\1\44\2\uffff\1\111\1\uffff\4\44\1\uffff\1\156\1\165"+
        "\4\uffff\1\160\1\164\1\165\1\160\1\164\1\165\1\44\1\164\1\uffff"+
        "\1\44\1\uffff";
    static final String DFA35_maxS =
        "\1\176\1\122\1\uffff\1\145\1\75\1\uffff\1\uffff\1\171\1\uffff\1"+
        "\157\1\uffff\1\170\1\167\1\165\1\145\1\156\1\157\1\156\3\157\5\uffff"+
        "\1\75\1\71\1\75\1\76\3\75\1\uffff\2\75\1\76\1\75\1\174\1\uffff\1"+
        "\117\1\150\1\157\1\162\3\uffff\1\170\1\146\1\uffff\1\105\1\122\1"+
        "\141\2\uffff\1\uffff\1\uffff\1\172\1\162\1\160\1\154\1\164\1\165"+
        "\1\163\1\162\1\172\1\157\1\142\1\151\1\164\1\157\1\164\1\163\1\141"+
        "\1\156\1\163\1\164\1\172\1\156\1\157\1\162\1\172\1\146\27\uffff"+
        "\1\75\2\uffff\1\75\7\uffff\1\124\1\151\1\142\1\164\1\145\1\uffff"+
        "\1\146\1\uffff\1\146\1\124\1\172\1\143\1\uffff\1\uffff\2\145\1\144"+
        "\1\141\1\145\1\155\1\145\1\164\1\165\1\156\1\145\1\162\1\157\1\164"+
        "\1\157\1\162\1\151\1\165\1\151\1\157\1\162\1\164\1\145\1\172\1\uffff"+
        "\1\147\1\141\1\172\1\142\1\uffff\1\141\4\uffff\1\172\1\156\1\154"+
        "\2\157\1\141\1\uffff\1\104\1\uffff\1\164\1\uffff\1\141\1\144\1\172"+
        "\1\164\1\162\2\172\1\151\1\143\1\145\1\157\1\164\1\162\1\143\1\172"+
        "\1\164\1\163\1\162\1\147\1\156\1\172\1\164\1\151\1\172\1\uffff\1"+
        "\172\1\164\1\uffff\1\154\1\165\1\uffff\1\172\1\145\1\162\1\172\1"+
        "\153\1\105\1\151\1\uffff\1\144\1\145\1\uffff\1\151\1\156\2\uffff"+
        "\1\143\1\164\1\144\1\146\1\172\1\164\1\150\1\uffff\1\172\1\164\2"+
        "\156\1\172\1\uffff\1\172\1\156\2\uffff\1\172\1\145\1\154\1\uffff"+
        "\1\172\1\164\1\uffff\1\172\1\106\1\166\1\uffff\1\172\1\146\1\154"+
        "\5\172\1\uffff\2\172\1\uffff\1\145\1\172\1\145\2\uffff\1\165\1\uffff"+
        "\1\172\1\164\1\uffff\1\172\1\uffff\1\172\1\145\2\uffff\1\172\1\145"+
        "\7\uffff\1\162\1\uffff\1\144\1\145\1\uffff\1\172\2\uffff\1\117\1"+
        "\uffff\4\172\1\uffff\1\156\1\165\4\uffff\1\160\1\164\1\165\1\160"+
        "\1\164\1\165\1\172\1\164\1\uffff\1\172\1\uffff";
    static final String DFA35_acceptS =
        "\2\uffff\1\2\2\uffff\1\6\2\uffff\1\12\1\uffff\1\14\12\uffff\1\32"+
        "\1\33\1\36\1\42\1\43\7\uffff\1\60\5\uffff\1\74\4\uffff\1\133\1\134"+
        "\1\135\2\uffff\1\142\3\uffff\1\101\1\5\1\uffff\1\145\32\uffff\1"+
        "\62\1\44\1\45\1\141\1\55\1\52\1\65\1\46\1\53\1\56\1\66\1\47\1\63"+
        "\1\143\1\144\1\50\1\64\1\51\1\71\1\76\1\57\1\102\1\61\1\uffff\1"+
        "\105\1\103\1\uffff\1\106\1\104\1\72\1\100\1\73\1\75\1\77\5\uffff"+
        "\1\136\1\uffff\1\137\5\uffff\1\10\30\uffff\1\121\4\uffff\1\125\1"+
        "\uffff\1\67\1\107\1\70\1\110\6\uffff\1\140\1\uffff\1\120\32\uffff"+
        "\1\26\2\uffff\1\126\2\uffff\1\111\12\uffff\1\13\2\uffff\1\37\1\122"+
        "\7\uffff\1\20\5\uffff\1\24\2\uffff\1\112\1\27\3\uffff\1\115\2\uffff"+
        "\1\127\14\uffff\1\25\2\uffff\1\116\3\uffff\1\35\1\40\1\uffff\1\30"+
        "\2\uffff\1\124\1\uffff\1\131\2\uffff\1\7\1\11\2\uffff\1\16\1\17"+
        "\1\34\1\23\1\54\1\114\1\123\1\uffff\1\132\2\uffff\1\31\1\uffff\1"+
        "\117\1\1\1\uffff\1\15\4\uffff\1\113\2\uffff\1\41\1\21\1\22\1\130"+
        "\10\uffff\1\3\1\uffff\1\4";
    static final String DFA35_specialS =
        "\6\uffff\1\0\60\uffff\1\5\111\uffff\1\3\56\uffff\1\4\46\uffff\1"+
        "\2\43\uffff\1\1\105\uffff}>";
    static final String[] DFA35_transitionS = {
            "\2\61\1\uffff\2\61\22\uffff\1\61\1\42\1\56\1\6\1\54\1\37\1"+
            "\40\1\55\1\10\1\12\1\32\1\34\1\5\1\35\1\33\1\36\1\57\11\60\1"+
            "\27\1\2\1\43\1\4\1\44\1\47\1\uffff\4\54\1\50\12\54\1\1\1\54"+
            "\1\3\10\54\1\30\1\uffff\1\31\1\45\1\54\1\uffff\1\15\1\53\1\20"+
            "\1\24\1\13\1\23\1\52\1\54\1\21\2\54\1\22\5\54\1\16\1\14\1\7"+
            "\1\17\1\11\1\51\3\54\1\25\1\46\1\26\1\41",
            "\1\63\20\uffff\1\62",
            "",
            "\1\64",
            "\1\65",
            "",
            "\162\70\1\67\uff8d\70",
            "\1\72\6\uffff\1\71\11\uffff\1\73",
            "",
            "\1\74",
            "",
            "\1\77\1\uffff\1\76\11\uffff\1\75",
            "\1\103\6\uffff\1\102\1\101\12\uffff\1\100\2\uffff\1\104",
            "\1\106\22\uffff\1\105",
            "\1\107",
            "\1\110",
            "\1\113\6\uffff\1\111\6\uffff\1\112",
            "\1\115\7\uffff\1\114",
            "\1\116",
            "\1\117\2\uffff\1\120",
            "\1\122\11\uffff\1\121",
            "",
            "",
            "",
            "",
            "",
            "\1\123",
            "\1\125\1\uffff\12\126",
            "\1\130\21\uffff\1\131",
            "\1\133\17\uffff\1\135\1\134",
            "\1\140\4\uffff\1\141\15\uffff\1\137",
            "\1\143",
            "\1\146\26\uffff\1\145",
            "",
            "\1\150",
            "\1\152\1\153",
            "\1\156\1\155",
            "\1\160",
            "\1\162\76\uffff\1\163",
            "",
            "\1\165",
            "\1\167\6\uffff\1\166",
            "\1\170",
            "\1\171",
            "",
            "",
            "",
            "\1\126\1\uffff\10\173\2\126\12\uffff\3\126\21\uffff\1\172"+
            "\13\uffff\3\126\21\uffff\1\172",
            "\1\126\1\uffff\12\175\12\uffff\3\126\35\uffff\3\126",
            "",
            "\1\176",
            "\1\177",
            "\1\u0080",
            "",
            "",
            "\141\70\1\u0081\uff9e\70",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u0083",
            "\1\u0084",
            "\1\u0085\2\uffff\1\u0086",
            "\1\u0087",
            "\1\u0088",
            "\1\u0089",
            "\1\u008a\20\uffff\1\u008b",
            "\1\u008c\22\uffff\1\u008d",
            "\1\u008e",
            "\1\u008f",
            "\1\u0090",
            "\1\u0091",
            "\1\u0092",
            "\1\u0093\14\uffff\1\u0094",
            "\1\u0096\11\uffff\1\u0095",
            "\1\u0097",
            "\1\u0098",
            "\1\u0099",
            "\1\u009a",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u009c",
            "\1\u009d",
            "\1\u009e",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\24"+
            "\54\1\u009f\5\54",
            "\1\u00a1",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\u00a2",
            "",
            "",
            "\1\u00a4",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\u00a6",
            "\1\u00a7\3\uffff\1\u00a8",
            "\1\u00a9",
            "\1\u00aa",
            "\1\u00ab",
            "",
            "\1\126\1\uffff\10\173\2\126\12\uffff\3\126\35\uffff\3\126",
            "",
            "\1\126\1\uffff\12\175\12\uffff\3\126\35\uffff\3\126",
            "\1\u00ad",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u00af",
            "\156\70\1\u00b0\uff91\70",
            "",
            "\1\u00b1",
            "\1\u00b2",
            "\1\u00b3",
            "\1\u00b4",
            "\1\u00b5",
            "\1\u00b6",
            "\1\u00b7",
            "\1\u00b8",
            "\1\u00b9",
            "\1\u00ba",
            "\1\u00bb",
            "\1\u00bc",
            "\1\u00bd",
            "\1\u00be",
            "\1\u00bf",
            "\1\u00c0",
            "\1\u00c1",
            "\1\u00c2",
            "\1\u00c3",
            "\1\u00c4",
            "\1\u00c5",
            "\1\u00c6\1\u00c7",
            "\1\u00c8",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "",
            "\1\u00ca",
            "\1\u00cb",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u00cd",
            "",
            "\1\u00ce",
            "",
            "",
            "",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u00d0",
            "\1\u00d1",
            "\1\u00d2",
            "\1\u00d3",
            "\1\u00d4",
            "",
            "\1\u00d5",
            "",
            "\1\u00d6",
            "\147\70\1\u00d7\uff98\70",
            "\1\u00d8",
            "\1\u00d9",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u00db",
            "\1\u00dc",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u00df",
            "\1\u00e0",
            "\1\u00e1",
            "\1\u00e2",
            "\1\u00e3",
            "\1\u00e4",
            "\1\u00e5",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u00e7",
            "\1\u00e8",
            "\1\u00e9",
            "\1\u00ea",
            "\1\u00eb",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u00ed",
            "\1\u00ee",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u00f1",
            "",
            "\1\u00f2",
            "\1\u00f3",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u00f5",
            "\1\u00f6",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u00f8",
            "\1\u00f9",
            "\1\u00fa",
            "\145\70\1\u00fb\uff9a\70",
            "\1\u00fc",
            "\1\u00fd",
            "",
            "\1\u00fe",
            "\1\u00ff",
            "",
            "",
            "\1\u0100",
            "\1\u0101",
            "\1\u0102",
            "\1\u0103",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u0105",
            "\1\u0106",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u0108",
            "\1\u0109",
            "\1\u010a",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u010d",
            "",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u010f",
            "\1\u0110",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u0112",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u0114",
            "\1\u0115",
            "\0\70",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u0118",
            "\1\u0119",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "",
            "\1\u0121",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u0123",
            "",
            "",
            "\1\u0124",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u0126",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u0129",
            "",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u012b",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "\1\u012c",
            "",
            "\1\u012d",
            "\1\u012e",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "",
            "",
            "\1\u0130\5\uffff\1\u0131",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "",
            "\1\u0136",
            "\1\u0137",
            "",
            "",
            "",
            "",
            "\1\u0138",
            "\1\u0139",
            "\1\u013a",
            "\1\u013b",
            "\1\u013c",
            "\1\u013d",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
            "\1\u013f",
            "",
            "\1\54\13\uffff\12\54\7\uffff\32\54\4\uffff\1\54\1\uffff\32"+
            "\54",
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
            return "1:1: Tokens : ( T__40 | T__41 | T__42 | T__43 | T__44 | T__45 | T__46 | T__47 | T__48 | T__49 | T__50 | T__51 | T__52 | T__53 | T__54 | T__55 | T__56 | T__57 | T__58 | T__59 | T__60 | T__61 | T__62 | T__63 | T__64 | T__65 | T__66 | T__67 | T__68 | T__69 | T__70 | T__71 | T__72 | T__73 | T__74 | T__75 | T__76 | T__77 | T__78 | T__79 | T__80 | T__81 | T__82 | T__83 | T__84 | T__85 | T__86 | T__87 | T__88 | T__89 | T__90 | T__91 | T__92 | T__93 | T__94 | T__95 | T__96 | T__97 | T__98 | T__99 | T__100 | T__101 | T__102 | T__103 | T__104 | T__105 | T__106 | T__107 | T__108 | T__109 | T__110 | T__111 | T__112 | T__113 | T__114 | T__115 | T__116 | T__117 | T__118 | T__119 | T__120 | T__121 | T__122 | T__123 | T__124 | T__125 | T__126 | T__127 | T__128 | T__129 | IDENTIFIER | CHARACTER_LITERAL | STRING_LITERAL | HEX_LITERAL | DECIMAL_LITERAL | OCTAL_LITERAL | FLOATING_POINT_LITERAL | WS | COMMENT | LINE_COMMENT | LINE_COMMAND );";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            IntStream input = _input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA35_6 = input.LA(1);

                        s = -1;
                        if ( (LA35_6=='r') ) {s = 55;}

                        else if ( ((LA35_6>='\u0000' && LA35_6<='q')||(LA35_6>='s' && LA35_6<='\uFFFF')) ) {s = 56;}

                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA35_251 = input.LA(1);

                        s = -1;
                        if ( ((LA35_251>='\u0000' && LA35_251<='\uFFFF')) ) {s = 56;}

                        else s = 278;

                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA35_215 = input.LA(1);

                        s = -1;
                        if ( (LA35_215=='e') ) {s = 251;}

                        else if ( ((LA35_215>='\u0000' && LA35_215<='d')||(LA35_215>='f' && LA35_215<='\uFFFF')) ) {s = 56;}

                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA35_129 = input.LA(1);

                        s = -1;
                        if ( (LA35_129=='n') ) {s = 176;}

                        else if ( ((LA35_129>='\u0000' && LA35_129<='m')||(LA35_129>='o' && LA35_129<='\uFFFF')) ) {s = 56;}

                        if ( s>=0 ) return s;
                        break;
                    case 4 : 
                        int LA35_176 = input.LA(1);

                        s = -1;
                        if ( (LA35_176=='g') ) {s = 215;}

                        else if ( ((LA35_176>='\u0000' && LA35_176<='f')||(LA35_176>='h' && LA35_176<='\uFFFF')) ) {s = 56;}

                        if ( s>=0 ) return s;
                        break;
                    case 5 : 
                        int LA35_55 = input.LA(1);

                        s = -1;
                        if ( (LA35_55=='a') ) {s = 129;}

                        else if ( ((LA35_55>='\u0000' && LA35_55<='`')||(LA35_55>='b' && LA35_55<='\uFFFF')) ) {s = 56;}

                        if ( s>=0 ) return s;
                        break;
            }
            NoViableAltException nvae =
                new NoViableAltException(getDescription(), 35, _s, input);
            error(nvae);
            throw nvae;
        }
    }
 

}