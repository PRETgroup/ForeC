// $ANTLR 3.1.2 C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g 2015-06-02 11:54:53

	import java.util.ArrayList;  
	import java.util.Hashtable;
	import java.util.Enumeration;
	import java.io.*;
	import java.util.regex.Matcher;
	import java.util.regex.Pattern;
	import java.util.Arrays; 


import org.antlr.runtime.*;
import org.antlr.runtime.tree.*;import java.util.Stack;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
public class PretCTreeGrammar extends TreeParser {
    public static final String[] tokenNames = new String[] {
        "<invalid>", "<EOR>", "<DOWN>", "<UP>", "ID_TOK", "SOURCE_TOK", "FUNCTION_TOK", "GLOBAL_DECLARATION_TOK", "DECLARATION_TOK", "TYPE_DECLARATION_TOK", "LABELED_STATMENT_TOK", "EXPRESSION_STATMENT_TOK", "SELECTION_STATMENT_TOK", "ITERATION_STATEMENT_TOK", "JUMP_STATMENT_TOK", "SCOPE_TOK", "EMPTY_TOK", "END_TOK", "ABORT_TOK", "PREPROC_TOK", "PRET_DEF_TOK", "IDENTIFIER", "DECIMAL_LITERAL", "LINE_COMMAND", "HEX_LITERAL", "OCTAL_LITERAL", "CHARACTER_LITERAL", "STRING_LITERAL", "FLOATING_POINT_LITERAL", "LETTER", "EscapeSequence", "HexDigit", "IntegerTypeSuffix", "Exponent", "FloatTypeSuffix", "OctalEscape", "UnicodeEscape", "WS", "COMMENT", "LINE_COMMENT", "'PRETDEF'", "';'", "'ReactiveInput'", "'ReactiveOutput'", "'='", "','", "'#range'", "'to'", "'thread'", "'('", "'void'", "')'", "'typedef'", "'extern'", "'static'", "'auto'", "'register'", "'unsigned'", "'signed'", "'char'", "'short'", "'int'", "'long'", "'float'", "'double'", "'{'", "'}'", "'struct'", "'union'", "':'", "'enum'", "'const'", "'volatile'", "'['", "']'", "'*'", "'...'", "'+'", "'-'", "'/'", "'%'", "'++'", "'--'", "'sizeof'", "'.'", "'->'", "'&'", "'~'", "'!'", "'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", "'>>='", "'&='", "'^='", "'|='", "'?'", "'||'", "'&&'", "'|'", "'^'", "'=='", "'!='", "'<'", "'>'", "'<='", "'>='", "'<<'", "'>>'", "'EOT'", "'case'", "'default'", "'sabort'", "'when'", "'abort'", "'wabort'", "'PAR'", "'if'", "'else'", "'switch'", "'while'", "'do'", "'for'", "'goto'", "'continue'", "'break'", "'return'"
    };
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

    protected static class loop_scope {
        String loop_continue_trans;
    }
    protected Stack loop_stack = new Stack();
    protected static class isFromFunction_scope {
        boolean data;
        boolean isSwitchData;
        String SwitchVar;
        String SwitchDefaultCondition;
        String scope_statement_arugment_end_barcket;
        String scope_statement_arugment_end_barcket_after;
    }
    protected Stack isFromFunction_stack = new Stack();


        public PretCTreeGrammar(TreeNodeStream input) {
            this(input, new RecognizerSharedState());
        }
        public PretCTreeGrammar(TreeNodeStream input, RecognizerSharedState state) {
            super(input, state);
            this.state.ruleMemo = new HashMap[38+1];
             
             
        }
        

    public String[] getTokenNames() { return PretCTreeGrammar.tokenNames; }
    public String getGrammarFileName() { return "C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g"; }


    	
    	boolean hadProjectPrefix = true;
    	Hashtable nodesTable = new Hashtable();// hash table of StatementNode test;
    	String projectName = "a";
    	String projectPrefix = "";
    	String projectInsName = "";
    	String mainPrefix = "";
    	String mainSuffix = "";
    	String outputMainFilename = projectName + ".main.c";
    	String outputThdHeaderFilename = projectName + ".thd.h";
    	String outputPretHeaderFilename = projectName + ".PRET.h";
    	String outputGlobalASMPretHeaderFilename = projectName + ".PRET.GLBASM.h";
    	Hashtable<Long,ScopeNode> scopeList = new Hashtable<Long,ScopeNode>();
    	TimeMeSimulation timeMeSim = null;
    	boolean socketOff = false;
    	boolean annotateOnly = false;
    	boolean skipVC = false;
    	int tickDelay = 0;
    	boolean scopeDelayASMPrint = false;
    	boolean trackVariables = false;
    	boolean timeMeSimulation = false;
    	boolean isFunctionBlock = false;
    	boolean notrename = true;
    	String path = "";
    	CFilePrinter writerMain;
    	CFilePrinter writerThdHdr;
    	CFilePrinter writerPretHdr;
    	CFilePrinter writerPretGlbASM;
    	CFilePrinter printer,printerTemp;
    	long debugID=0;
    	String codeTemp;
    	StatementNode nodeTemp;
    	StatementNode functionNode;
    	StatementNode getNode(String tokenNumber) {
    		debugID = new Long(tokenNumber);
    		return (StatementNode)(nodesTable.get(new Long(tokenNumber)));
    	}
    	
    	
    	String pendingASM = "";
    	
    	Boolean extraConditionVar = false;
    	
    	
    	void printASMStructeDefine(String name, String type,String init, String min, String max) {
    		if (trackVariables == false) {
    			return;
    		}
    		if (isGlobal) {
    			printerTemp = printer;
    			printer = writerPretGlbASM; 
    		}
    		type = type + name.replaceAll("[A-Za-z_ 0-9]","");
    		type = type.replaceAll(" ","");
    		name = name.replaceAll("\\Q[\\E.*",""); //take array out
    		name = name.replaceAll("[^A-Za-z_ 0-9]","");
    		name = name.replaceAll(" ","");
    		/*if (type.contains("struct") || type.contains("union")) {
    			//type is:
    			//struct start
    			//struct end
    			if (isInsideStruct>0 || scopeDelayASMPrint) {
    				pendingASM += ("asm(\"##@PRET_STRUCTURE_DECLARE "+name+" "+" "+type+"\");\n").replaceAll("  "," ");
    			}else{
    				if (pendingASM.length() > 0){
    					printer.print(pendingASM);
    					pendingASM = "";
    				}
    				printer.print(("asm(\"##@PRET_STRUCTURE_DECLARE "+name+" "+" "+type+"\");\n").replaceAll("  "," "));
    			}
    		}else{*/
    			if (isInsideStruct>0 || scopeDelayASMPrint) {
    				pendingASM += ("asm(\"nop\");/*asm(\"##@PRET_STRUCTURE_DECLARE "+name+" "+" "+type+" "+init+" "+min+" "+max+"\");*/\n").replaceAll("  "," ");
    			}else{
    				if (pendingASM.length() > 0){
    					printer.print(pendingASM);
    					pendingASM = "";
    				}
    				printer.print(("asm(\"nop\");/*asm(\"##@PRET_STRUCTURE_DECLARE "+name+" "+" "+type+" "+init+" "+min+" "+max+"\");*/\n").replaceAll("  "," "));
    			}
    		/*}*/
    		// if enum?
    		if (isGlobal) {
    			printer = printerTemp; 
    		}
    	}
    	void printASMVarDeclare(String name,String io, String type,String init, String min, String max) {
    		if (trackVariables == false) {
    			return;
    		}
    		if (isGlobal) {
    			printerTemp = printer;
    			printer = writerPretGlbASM; 
    		}
    		type = type + name.replaceAll("[A-Za-z_ 0-9]","");
    		type = type.replaceAll(" ","");
    		name = name.replaceAll("\\Q[\\E.*",""); //take array out
    		name = name.replaceAll("[^A-Za-z_ 0-9]","");
    		name = name.replaceAll(" ","");
    		if (type.contains("struct") || type.contains("union")) {
    			//type is:
    			//struct start
    			//struct end
    			if (isInsideStruct>0 || scopeDelayASMPrint) {
    				pendingASM += ("asm(\"nop\");/*asm(\"##@PRET_VAR_DECLARE "+name+" "+io+" "+type+"\");*/\n").replaceAll("  "," ");
    			}else{
    				if (pendingASM.length() > 0){
    					printer.print(pendingASM);
    					pendingASM = "";
    				}
    				printer.print(("asm(\"nop\");/*asm(\"##@PRET_VAR_DECLARE "+name+" "+io+" "+type+"\");*/\n").replaceAll("  "," "));
    			}
    		}else{
    			if (isInsideStruct>0 || scopeDelayASMPrint) {
    				pendingASM += ("asm(\"nop\");/*asm(\"##@PRET_VAR_DECLARE "+name+" "+io+" "+type+" "+init+" "+min+" "+max+"\");*/\n").replaceAll("  "," ");
    			}else{
    				if (pendingASM.length() > 0){
    					printer.print(pendingASM);
    					pendingASM = "";
    				}
    				printer.print(("asm(\"nop\");/*asm(\"##@PRET_VAR_DECLARE "+name+" "+io+" "+type+" "+init+" "+min+" "+max+"\");*/\n").replaceAll("  "," "));
    			}
    		}
    		if (isGlobal) {
    			printer = printerTemp; 
    		}
    		if (init.equals("null") == false &&type.contains("typedef")==false ) {
    			printASMSet(name+"="+init+";");
    		}
    		// if enum?
    		
    	}
    	void printASMSet(String assignment) {
    		if (trackVariables == false) {
    			return;
    		}
    		if (isGlobal) {
    			printerTemp = printer;
    			printer = writerPretGlbASM; 
    		}
    		if (assignment.contains("asm(")||assignment.contains("memset(")||assignment.contains("sizeof(")) {
    			System.out.println("Asm comment not set for: "+assignment+" system functions not handeled");
    			if (isGlobal) {
    				printer = printerTemp; 
    			}
    			return;
    		}
    		String statement = "asm(\"nop\");/*asm(\"##@PRET_TRACK_SET "+assignment.replaceAll(" ","")+"\");*/\n";
    		if (isInsideStruct>0 || scopeDelayASMPrint) {
    			pendingASM += statement;
    		}else{
    			if (pendingASM.length() > 0) {
    				printer.print(pendingASM);
    				pendingASM = "";
    			}
    			printer.print(statement);
    		}
    		if (isGlobal) {
    			printer = printerTemp; 
    		}
    	}
    	String printASMSetRet(String assignment) {
    		if (trackVariables == false) {
    			return "";
    		}
    		if (assignment.contains("asm(")||assignment.contains("memset(")||assignment.contains("sizeof(")) {
    			System.out.println("Asm comment not set for: "+assignment+" system functions not handeled");
    			return "";
    		}
    		String statement = "asm(\"nop\");/*asm(\"##@PRET_TRACK_SET "+assignment.replaceAll(" ","")+"\");*/\n";
    		return (statement);
    	}
    	String printASMTestRet(String condition) {
    		if (trackVariables == false) {
    			return "";
    		}
    		String statement = "asm(\"nop\");/*asm(\"##@PRET_TRACK_TEST ("+condition.replaceAll(" ","")+")\");*/\n";
    		return statement;
    	}
    	void printASMTest(String condition) {
    		if (trackVariables == false) {
    			return;
    		}
    		if (isGlobal) {
    			printerTemp = printer;
    			printer = writerPretGlbASM; 
    		}
    		String statement = "asm(\"nop\");/*asm(\"##@PRET_TRACK_TEST ("+condition.replaceAll(" ","")+")\");*/\n";
    		if (isInsideStruct>0 || scopeDelayASMPrint) {
    			pendingASM += statement;
    		}else{
    			if (pendingASM.length() > 0) {
    				printer.print(pendingASM);
    				pendingASM = "";
    			}
    			printer.print(statement);
    		}
    		if (isGlobal) {
    			printer = printerTemp; 
    		}
    	}
    	void ASMPrint() {
    		if (isGlobal) {
    			printerTemp = printer;
    			printer = writerPretGlbASM; 
    		}
    		if (pendingASM.length() > 0) {
    			printer.print(pendingASM);
    			pendingASM = "";
    		}
    		if (isGlobal) {
    			printer = printerTemp; 
    		}
    	}
    	long findParID(String thread) {
    		
    		for (Enumeration e = nodesTable.keys(); e.hasMoreElements() ;) {
    			StatementNode temp = getNode(""+e.nextElement());
    			
    			for (int j =0; j < temp.name.size(); j++) { //get thread names
    				//System.out.println("zzzz " + thread + " " + temp.thdInsID);
    				if (thread.equals(temp.name.get(j))&&temp.type.equals("PAR")) { //thread name equals
    					return temp.ID;
    				}
    			}
    		}
    		
    		return -1;
    	}
    	int isInsideStruct = 0;
    	public void printInnerDataStructure(ArrayList<StatementNode> nodeList, StatementNode parent, int structureNumber) {
    		//printer.print("I AM A STRUCT HERE\n");
    		isInsideStruct++;
    		
    		
    		
    		/*if (nodeList.size() > 1) {
    			System.out.println("Structure got multiple structure possible????");
    			System.out.println("Contact developer");
    			System.exit(0);
    		}*/
    		//System.out.println( nodeList.size());
    		//for (int k = 0;  k < nodeList.size(); k++) {
    			codeTemp += " "+getNewStructName(nodeList.get(structureNumber).structTypeName,parent);
    			StatementNode n = nodeList.get(structureNumber);
    			printASMStructeDefine(getNewStructName(nodeList.get(structureNumber).structTypeName,parent),"struct_start","null","null","null");
    			if (n.name.size() > 0) {
    				printer.print(codeTemp+" {\n");
    				printer.indent++;
    			}
    			printDeclare(n);
    			if (n.name.size() > 0) {
    				printer.indent--;
    				codeTemp="}";
    			}
    		//}
    		//codeTemp = "";
    			printASMStructeDefine(getNewStructName(nodeList.get(structureNumber).structTypeName,parent),"struct_end","null","null","null");
    			
    		isInsideStruct--;
    	}
    	String ASMio = "internal";
    	public void printDeclare(StatementNode n) {
    		ArrayList<String> specifiers = n.varSpecifiers;
    		ArrayList<String> types = n.declaredType;
    		ArrayList<String> name = n.name;
    		ArrayList<ArrayList<String>> init = n.constantStatement;
    		int innerStructureCount = 0;
    		
    		for (int i = 0; i < types.size(); i++) { //use type some stucts have no name
    			codeTemp = "";
    			String ASMname = "null";
    			String ASMinit = "null";
    			String ASMtype = types.get(i);
    			String min = "null";
    			String max = "null";
    			if (name.get(i).contains("(")) { //function declare 
    				if (notrename) {
    					codeTemp += specifiers.get(i) + " " +name.get(i)+";\n";
    				}else{
    					codeTemp += specifiers.get(i) + " " + projectPrefix+name.get(i)+";\n";
    				}
    				codeTemp = (codeTemp).replaceAll("  "," ");
    				String args =  name.get(i).substring((name.get(i).indexOf("(")+1),name.get(i).indexOf(")"));
    				String newArgs = name.get(i).substring((name.get(i).indexOf("(")),name.get(i).indexOf(")")+1);
    				String argsArray[] = args.split(",");
    				for (int j = 0; j < argsArray.length; j++) {
    					String elements[] = argsArray[j].split(" ");
    					
    					String argType = elements[0].replaceAll("([\\Q*\\E]|[\\Q[\\E]|[\\Q]\\E])*","");
    					
    					newArgs = newArgs.replaceFirst(argType,getNewTypeName(argType,n));
    					System.out.println(newArgs+","+argType+","+getNewTypeName(argType,n));
    				}
    				//add function prefix
    				//codeTemp=codeTemp.replaceFirst(name.get(i).substring((name.get(i).indexOf("(")-1),projectPrefix+oname.get(i).substring((name.get(i).indexOf("(")-1));
    				//function prefix
    				codeTemp=codeTemp.replaceFirst("\\Q"+name.get(i).substring((name.get(i).indexOf("(")),name.get(i).indexOf(")")+1)+"\\E",newArgs);
    				printer.print("\n//fix var name later\n"+codeTemp);
    				continue;
    			}
    			if (n.type.equals("typedef")) {
    				ASMinit = getNewTypeName(ASMtype,n);
    				ASMtype = "typedef";
    				codeTemp += "typedef ";
    			}
    			if (functionNode != null && n.type.equals("scopedVaraibles") == false ) {
    				if (annotateOnly == false) {
    					if (specifiers.get(i).contains("static ") == false && (functionNode.type.equals("thread") || functionNode.name.get(0).equals(mainFunctionName))) {
    						if (types.get(i).equals("struct") || types.get(i).equals("union")) {
    							codeTemp += "static "+types.get(i);
    						}else{
    							codeTemp += "static "+specifiers.get(i);
    						}
    					}else{
    						if (types.get(i).equals("struct") || types.get(i).equals("union")) {
    							codeTemp += types.get(i);
    						}else{
    							codeTemp += specifiers.get(i);
    						}
    					}
    				}else{
    					if (types.get(i).equals("struct") || types.get(i).equals("union")) {
    						codeTemp += types.get(i);
    					}else{
    						codeTemp += specifiers.get(i);
    					}
    				}
    			}else{
    				if (types.get(i).equals("struct") || types.get(i).equals("union")) {
    					codeTemp += types.get(i);
    				}else{
    					codeTemp += specifiers.get(i);
    				}
    			}
    			if (n.minValue.size() > i && n.maxValue.size() > i ) {
    				if ((n.minValue.get(i).equals("UNDEFINED") == false) && (n.maxValue.get(i).equals("UNDEFINED")==false)) {
    					min = n.minValue.get(i);
    					max = n.maxValue.get(i);
    				}
    			}
    			//replace type
    			codeTemp = codeTemp.replaceFirst(types.get(i),getNewTypeName(types.get(i),n));
    			
    			codeTemp = (codeTemp+" ").replaceAll("  "," ");

    			//System.out.println("ddddddddddddddd "+getNewTypeName(types.get(i),n));
    			if (types.get(i).equals("struct") || types.get(i).equals("union")) {
    				//System.out.println("dddddddddddddddddddddddddddddd");
    				//codeTemp = "";
    				//codeTemp += types.get(i);
    				//codeTemp += " "+n.structTypeName;
    				//need recurrsive adding
    				printInnerDataStructure(n.scopedVaraibles,n,innerStructureCount);
    				innerStructureCount++;
    				if (name.size() > 0) {
    					if (n.type.equals("typedef")) {
    						ASMname = getNewTypeName(name.get(i),n);
    						codeTemp += " "+ASMname;
    					}else{
    						ASMname = getNewStatementString(name.get(i),n);
    						codeTemp += " "+ASMname;
    					}
    				}
    				if (init.get(i).size() != 0) {
    					ASMinit = "";
    					
    					ASMinit += "{";
    					String tempString = "";
    					for (int j = 0; j < init.get(i).size(); j++) {
    						tempString += getNewStatementString(init.get(i).get(j),n)+",";
    					}
    					ASMinit += tempString.substring(0,tempString.length()-1); //take last "," out
    					if (specifiers.get(i).contains("const")) {
    						codeTemp += "="+ASMinit+"}";
    					}else{	
    						//codeTemp += ";"+ASMname.replaceAll("\\W","")+"="+ASMinit+"}";
    						codeTemp += "="+ASMinit+"}";
    					}
    				}
    				codeTemp += ";\n";
    			
    				printer.print(codeTemp);
    				if (min.length() == 0) {
    					min = "null";
    				}
    				if (max.length() == 0) {
    					max = "null";
    				}
    				//printer.print("DDD"+max+"ddd");
    				if (ASMname.length() == 0) {
    					printASMStructeDefine("null",getNewTypeName(ASMtype,n),ASMinit,min,max);
    				}else{
    					printASMStructeDefine(ASMname,getNewTypeName(ASMtype,n),ASMinit,min,max);
    				}
    			}else if (name.get(i).contains("[") &&  name.get(i).contains("]")) { //array
    				if (n.type.equals("typedef")) {
    					ASMname = getNewTypeName(name.get(i),n);
    					codeTemp += " "+ASMname;
    				}else{
    					ASMname = getNewStatementString(name.get(i),n);
    					codeTemp += " "+ASMname;
    				}
    				if (init.get(i).size() != 0) {
    					ASMinit = "";
    					
    					ASMinit += "{";
    					String tempString = "";
    					for (int j = 0; j < init.get(i).size(); j++) {
    						tempString += getNewStatementString(init.get(i).get(j),n)+",";
    					}
    					ASMinit += tempString.substring(0,tempString.length()-1); //take last "," out
    					if (specifiers.get(i).contains("const")) {
    						codeTemp += "="+ASMinit;
    					}else{	
    						//codeTemp += ";"+ASMname.replaceAll("\\W","")+"="+ASMinit+"}";
    						codeTemp += "="+ASMinit+"}";
    					}
    				}
    				codeTemp += ";\n";
    				
    				
    				printer.print(codeTemp);
    				printASMVarDeclare(ASMname,ASMio,getNewTypeName(ASMtype,n),ASMinit,min,max);
    			}else{

    				if (n.type.equals("typedef")) {
    					ASMname = getNewTypeName(name.get(i),n);
    					codeTemp += " "+ASMname;
    				}else{
    					ASMname = getNewStatementString(name.get(i),n);
    					codeTemp += " "+ASMname;
    				}
    				if (init.get(i).size() != 0) {
    					ASMinit = getNewStatementString(init.get(i).get(0),n);
    					if (isInsideStruct>0) {
    						codeTemp += ":"+ASMinit;
    					}else{
    						if (specifiers.get(i).contains("const") || n.type.equals("ReactiveOutput")||n.type.equals("ReactiveInput")||n.scopeID==0 /*global*/) {
    							codeTemp += "="+ASMinit;
    						}else{	
    							//codeTemp += ";"+ASMname.replaceAll("\\W","")+"="+ASMinit;
    							//codeTemp += "="+ASMinit;
    							codeTemp += ";"+ASMname.replaceAll("\\W","")+"="+ASMinit;
    						}
    					}
    				}
    				codeTemp += ";\n";
    				
    				
    				printer.print(codeTemp);
    				printASMVarDeclare(ASMname,ASMio,getNewTypeName(ASMtype,n),ASMinit,min,max);
    			}
    			
    		}
    	}
    	
    	public StatementNode findFunctionNode(String functionName) {
    		//C does not allow 2 functions with the same name
    		for (Enumeration<StatementNode> e = nodesTable.elements(); e.hasMoreElements();) {
    			StatementNode n = e.nextElement();
    			if (n.type.equals("function")) {
    				if (n.name.get(0).equals(functionName)) {
    					return n;
    				}
    			}
    		}
    		System.out.println("Function not found: ");
    		System.out.println(getErrorInfo());
    		//System.exit(0);
    		return null;
    	}
    	long returnID = 0;
    	public String processFunctionCalls(String source, StatementNode n) {
    		/*Pattern variablePattern = Pattern.compile("[A-Za-z_][A-Za-z0-9_]*[ ]*\\Q(\\E([A-Za-z0-9_ \"\"]*)*\\Q)\\E"); //match label _text():
    		Matcher vMatcher = variablePattern.matcher(source);
    		System.out.println("Soruce "+source);
    		ArrayList<String> functionStrings = new ArrayList<String>();
    		while(vMatcher.find()) {
    			
    			for (int i = 0; i < vMatcher.groupCount();i++) {
    				//ArrayList<String> temp = new ArrayList<String>();
    				//temp.add(vMatcher.group(i));
    				functionStrings.add(vMatcher.group(i));
    				System.out.println(" 666 "+vMatcher.group(i));
    			}
    			
    		}*/
    		String output = source;
    		//System.out.println("Soruce "+source);
    		ArrayList<String> functionStrings = new ArrayList<String>();
    		int functionDepthCounter = 0;
    		int start = 0;
    		for (int i = 0; i < source.length();i++) {
    			char c = source.charAt(i);
    			if (c == '(') {
    				functionDepthCounter++;
    			}else if (c == ')') {
    				if (functionDepthCounter == 1) {
    					functionStrings.add(source.substring(start,i+1));
    					//System.out.println(" 666"+source.substring(start,i+1)); 
    					start = i+1;
    				}
    				functionDepthCounter--;
    			}
    		}
    		Pattern variablePattern = Pattern.compile("[A-Za-z_][A-Za-z0-9_]*[ ]*\\Q(\\E");
    		
    		for (int i = 0; i < functionStrings.size();i++) {
    			String s = functionStrings.get(i);
    			Matcher vMatcher = variablePattern.matcher(s);
    			//take out the 2 brackets to match inner functions
    			if (vMatcher.find()==false) {
    				continue;
    			}
    			//System.out.println("===="+));
    			String functionString = s.substring(vMatcher.start());
    			String functionName = s.substring(vMatcher.start(),vMatcher.end()-1);
    			
    			//have the correct number of brackets in the function string
    			int startBrackCnt = 0;
    			int fromIndex = 0;
    			int index = 0;
    			while((index = functionString.indexOf('(',fromIndex)) >= 0) {startBrackCnt++;fromIndex = index+1;}
    			//System.out.println(s+" cnt "+startBrackCnt);
    			fromIndex = 0;
    			index = 0;
    			for (int j = 0; j < startBrackCnt;j++) {
    				index = functionString.indexOf(')',fromIndex);
    				fromIndex = index+1;
    			}
    			
    			if (functionName.equals("asm")||functionName.equals("memset")||functionName.equals("sizeof")) {
    				continue;
    			}
    			StatementNode funcNode = findFunctionNode(functionName);
    			if (funcNode==null) 
    			{
    				continue;
    			}
    			//System.out.println("name: "+functionName+" function: "+functionString);
    			//s = s.replaceFirst("[A-Za-z_][A-Za-z0-9_]*[ ]*\\Q(\\E","");
    			//System.out.println("||||"+s);

    			s = s.substring(vMatcher.end(),s.length()-1);

    			//System.out.println(" "+fromIndex);
    			functionString = functionString.substring(0,fromIndex);
    			//System.out.println("||||2"+s);
    			String result = processFunctionCalls(s,n);
    			
    			functionString = functionString.replaceFirst("\\Q"+s+"\\E",result);
    			//System.out.println(result+" ||||2"+functionString);
    			output = output.replaceFirst("\\Q"+s+"\\E",result);
    			//System.out.println("s: "+s+" r: "+result);
    			//System.out.println("new function: "+functionString);
    			//printer.print("var = "+s+"\n");
    			long ID = -1;
    			String returnValue = "";
    			String functionReturn = "";
    			String returnType = getNewTypeName(funcNode.returnType,funcNode);
    			if (returnType.equals("void") == false){
    				ID = returnID++;
    				returnValue = "PRET_RETURN_VAR_"+funcNode.getIDwPrefix()+"_"+ID;
    				functionReturn = "PRET_RETURN_VAR_"+funcNode.getIDwPrefix();
    				
    				printASMVarDeclare(returnValue,"internal",returnType,"null","null","null");
    			}
    			//String[] arguments = s.split(",");
    			String stringArguments = functionString.replaceFirst(variablePattern.pattern(),"");
    			int lastClosingBracket = stringArguments.lastIndexOf(')');
    			stringArguments = stringArguments.substring(0,lastClosingBracket);
    			String[] arguments = stringArguments.split(",");
    			String inputArugmentASMString = "";
    			for (int j = 0; j < funcNode.functionParameter.size();j++) {
    				if (j >= arguments.length) {
    					System.out.println("function not enough arguments");
    					System.out.println(getErrorInfo());
    					System.exit(0);
    				}
    				inputArugmentASMString += getNewVariableName(funcNode.functionParameter.get(j).replaceAll("\\Q*\\E","").replaceAll(" ",""),funcNode)+"="+arguments[j]+";";
    			}
    			
    			if (funcNode.functionParameter.size() > 0) {
    				printASMSet(inputArugmentASMString);
    			}
    			if (returnType.equals("void")){
    				if (notrename) {
    					printer.print(functionString+";\n");
    				}else{
    					printer.print(projectPrefix+functionString+";\n");
    				}
    			}else{
    				if (notrename) {
    					printer.print(returnType+" "+returnValue+" = "+functionString+";\n");
    				}else{
    					printer.print(returnType+" "+returnValue+" = "+projectPrefix+functionString+";\n");
    				}
    				printASMSet(returnValue+" = "+functionReturn+";");
    			}
    			output = output.replaceFirst("\\Q"+functionString+"\\E",returnValue);
    			
    			//System.out.println(output+" zzzzzzzzzzzzzz "+functionString+" sssss "+returnValue);
    			//System.out.println("o "+output);
    			//output = output.replaceFirst("\\Q"+s+"\\E","var");
    		}
    		//System.out.println("zzzzzzzzzzzzzz "+output);
    		return output;
    	}
    	
    	
    	
    	public String getNewStatementString(String source,StatementNode n) {
    		if (notrename)
    			return source;
    		if (n.type.equals("declare") == false) { 
    			printer.print("//"+source+"\n");
    		}
    		
    		String[] sourceArray = source.split("\"");
    		//System.out.println(source+" jjj "+Arrays.asList(sourceArray));
    		ArrayList<String> sourceSortedString = new ArrayList<String>();
    		
    		String temp = "";
    		sourceSortedString.add(sourceArray[0]);
    		boolean isString = true;
    		for (int i = 1; i < sourceArray.length; i++) {
    			String s = sourceArray[i];
    			//String pre_s = sourceArray[i-1];
    			
    			if (s.charAt(s.length()-1) == '\\') {
    				temp += s+"\"";
    				continue;
    			}else{
    				if (isString) {
    					temp += s;
    					temp = "\""+temp+"\"";
    					isString = false;
    				}else{
    					temp += s;
    					isString = true;
    				}
    			}
    			sourceSortedString.add(temp);
    			temp = "";
    			
    		}
    		
    		String output = "";
    		//source = source.replaceAll(" ","");
    		for (int i = 0; i <sourceSortedString.size();i++) {
    			//sometimes there will be strings with no size after split
    			if (source.length() == 0) {
    				continue;
    			}
    			source = sourceSortedString.get(i);
    			if (source.charAt(0) =='\"') {
    				output += source;
    				continue;
    			}
    			Pattern variablePattern = Pattern.compile("[A-Za-z_][A-Za-z0-9_]*"); //match label _text():
    			Matcher vMatcher = variablePattern.matcher(source);
    			//System.out.println("SRC "+source);
    			
    			int startIndex = 0;
    			int endIndex = 0;
    			int isStructure = 0;
    			StatementNode structNodes = null;
    			String newString = "";
    			
    			
    		
    		while(vMatcher.find()) {
    			endIndex = vMatcher.end();
    			
    			String nextChar = "";
    			if (source.length() > endIndex) {
    				nextChar = ""+source.charAt(endIndex); 
    			}
    			String matchedText = vMatcher.group();
    			//System.out.println(vMatcher.group()+" "+nextChar);
    			boolean deferenced = false;
    			if(nextChar.equals("-")) {
    				if ((""+source.charAt(endIndex+1)).equals(">")) {
    					deferenced = true;
    				}
    			}
    			//System.out.println("dddrrr "+deferenced);
    			if (nextChar.equals("(")) { // function call
    				
    			}else if ((nextChar.equals(".")||isStructure>0||deferenced)) {

    				if (isStructure == 0) {
    					newString = source.substring(startIndex,vMatcher.start()); //the non variable names bit
    					newString +=  getNewVariableName(matchedText,n);
    					output += newString;
    					startIndex = endIndex;
    					structNodes = getStructDeclareNode(matchedText,n);
    				}else{
    					newString = source.substring(startIndex,vMatcher.start()); //the non variable names bit
    					String newName = getNewVariableNameSearchStruct(matchedText,structNodes);
    					if (newName != null) { 
    						newString += newName;
    						output += newString;
    						startIndex = endIndex;
    						structNodes = getStructDeclareNode(matchedText,structNodes);
    					}else{
    						newString += matchedText;
    						structNodes = null;
    					}
    				}
    				/*
    					isStructure = 0 1st enterence
    					isStructure = 1 1st layer etc
    				*/
    				if (nextChar.equals(".")||deferenced) {
    					isStructure++;
    				}else{
    					isStructure = 0;
    				}
    			}else{
    				newString = source.substring(startIndex,vMatcher.start()); //the non variable names bit
    				newString += getNewVariableName(matchedText,n);
    				output += newString;
    				startIndex = endIndex;
    				isStructure = 0;
    			}
    	
    		//System.out.println("oooooo " + newString + " n "+nextChar);
    	
    			}
    			output += source.substring(startIndex);
    			
    		}
    		output = processFunctionCalls(output, n);
    		return output;
    	}
    	//public int getNewStatement_matched_node = -1;
    	public String getNewStatement(StatementNode n) {
    		String source = n.sourceCode;
    		return getNewStatementString(source,n);
    		/*Pattern variablePattern = Pattern.compile("[A-Za-z_][A-Za-z0-9_]*"); //match label _text():
    		Matcher vMatcher = variablePattern.matcher(source);
    		//System.out.println(source);
    		String output = "";
    		int startIndex = 0;
    		int endIndex = 0;
    		int isStructure = 0;
    		StatementNode structNodes = null;
    		while(vMatcher.find()) {
    			endIndex = vMatcher.end();
    			
    			String nextChar = ""+source.charAt(endIndex); 
    			String matchedText = vMatcher.group();
    			//System.out.println(vMatcher.group()+" "+nextChar);
    			
    			
    			if (nextChar.equals("(")) { // function call
    				isStructure = 0;
    			}else if ((nextChar.equals(".")||isStructure>0)) {

    				if (isStructure == 0) {
    					output += source.substring(startIndex,vMatcher.start());
    					output += getNewVariableName(matchedText,n);
    					startIndex = endIndex;
    					structNodes = getStructDeclareNode(matchedText,n);
    				}else{
    					output += source.substring(startIndex,vMatcher.start());
    					output += getNewVariableNameSearchStruct(matchedText,structNodes);
    					startIndex = endIndex;
    					structNodes = getStructDeclareNode(matchedText,structNodes);
    				}

    				if (nextChar.equals(".")) {
    					isStructure++;
    				}else{
    					isStructure = 0;
    				}
    			}else{
    				output += source.substring(startIndex,vMatcher.start());
    				output += getNewVariableName(matchedText,n);
    				startIndex = endIndex;
    				isStructure = 0;
    			}
    			
    			
    		}
    		output += source.substring(startIndex)+"\n";
    		return output;*/
    	}
    	public StatementNode getStructDeclareNode(String structName,StatementNode n) {
    		long scope = n.scopeID;
    		//System.out.println("ddd "+structName+"xxx "+n); 
    		while(scope != -1) {
    			//System.out.println("ddd "+scope); 
    			ScopeNode scopeNode = scopeList.get(scope);
    			if (scopeNode != null) {
    				StatementNode structDefNode = scopeNode.variableMap.get(structName);
    				//System.out.println( structName+" 0000000000000000000000000 "+structDefNode);
    				if (structDefNode != null) {
    					//see if it is a type defined struct used in a struct.....
    					if (structDefNode.type.equals("scopedVaraibles")){
    						int index = -1;
    						for (int i = 0; i < structDefNode.name.size();i++) {
    							String ss = structDefNode.name.get(i);
    							if (ss.indexOf("[") != -1)
    								ss = ss.substring(0,ss.indexOf("[")); //improve me
        							if (ss.equals(structName)){
    								index = i;
    								break;
    							}
    						}
    						StatementNode tdefNode = getTypedefNode(structDefNode.declaredType.get(index),structDefNode);
    						if (tdefNode != null) {
    							structDefNode = tdefNode;
    						}
    						//System.out.println( structName+" 888888888888888888888 "+tdefNode);
    					}
    				}
    				if (structDefNode == null) {
    					structDefNode = scopeNode.listOfStruct.get(structName);
    					//System.out.println( structName+" 1111111111111111111111111 "+structDefNode);
    				}
    				if (structDefNode == null) {
    					structDefNode = scopeNode.listOfTypeDef.get(structName);
    					//System.out.println( structName+" 2222222222222222222222222 "+structDefNode);
    				}
    				
    				if (structDefNode != null) {
    					//System.out.println("ddd "+structDefNode); 

    					//1st when traced to typdef definition look for structure e.g typedef aaa
    					//System.out.println("ssssssss"); 
    					String newTypeName = getNewTypeName(structDefNode.declaredType.get(0),structDefNode);
    					//System.out.println( structName+" ddddddddddddddddddddddddddddffffffffffffffffffffffffff "+structDefNode);
    					if (structDefNode.type.equals("typedef")){
    						if (structDefNode.scopedVaraibles.size() > 0) {
    							//if it typedef sturct aaa { }  dont try to find new node
    							if (structDefNode.scopedVaraibles.get(0).name.size() == 0) { 
    								//System.out.println("wwwwwwwwww"); 
    								structName = getNewTypeName_origTypeName;
    								//System.out.println("zzz "+structName); 
    								scope = structDefNode.scopeID;
    								continue;
    							}
    						}
    					}
    					//System.out.println("aaaaaaaaaa"); 
    					//find the correct index
    					
    					//2nd is the variable declare eg. aaa apple;
    					if (newTypeName.equals(structDefNode.declaredType.get(0)) == false) {
    						//it is a typedef struct.
    						structName = getNewTypeName_origTypeName;
    						//System.out.println("bbb "+structName); 
    						scope = structDefNode.scopeID;
    						continue;
    						
    					}
    			
    					int structNumber = 0;
    					for (int i = 0; i < structDefNode.name.size();i++) {
    						if (structDefNode.declaredType.get(i).equals("struct") || structDefNode.declaredType.get(i).equals("union")) {
    							structNumber++;
    						}
    						//NOTE if only a variable doesnt matter what it returns
    						String ss = structDefNode.name.get(i); //to take the array out before compare improve me
    						if (ss.indexOf("[") != -1)
    							ss = ss.substring(0,ss.indexOf("[")); //improve me
    						if ( ss.equals(structName)){
    							break;
    						}
    					}
    					//System.out.println("vvvvv "+structName);
    					if (structNumber == 0) {
    						//top layer struct thus only 1 varaibleScope
    						//if (structDefNode.declaredType.equals("struct") || structDefNode.declaredType.equals("union")) {
    						//	return structDefNode.scopedVaraibles.get(0); //this is not a struct nested
    						//}else{
    							//lase scope
    							return null;
    						//}
    					}
    					//System.out.println(structDefNode.scopedVaraibles.get(structNumber-1));
    					return structDefNode.scopedVaraibles.get(structNumber-1);
    				}else{
    					scope = scopeNode.parentID;
    				}
    			}else{
    				System.out.println("Error 1 no such scope "+scope);
    				System.exit(0);
    			}
    		}
    		System.out.println("Error 2 struct "+structName+" not declared statement:");
    		System.out.println(getErrorInfo());
    		if (skipVC==false) {
    			System.exit(0);
    		}		System.out.println(n);

    		return null;
    	}	
    	
    	public StatementNode getTypedefNode(String oldTypeName, StatementNode n) {
    		long scope = n.scopeID;
    		
    		while(scope != -1) {

    			ScopeNode scopeNode = scopeList.get(scope);
    			if (scopeNode != null) {
    				StatementNode typeDefNode = scopeNode.listOfTypeDef.get(oldTypeName);
    				//
    				if (typeDefNode != null) {
    				
    					return typeDefNode;
    				}else{
    					scope = scopeNode.parentID;
    				}
    			}else{
    				System.out.println("Error 3 no such scope "+scope);
    				System.out.println(getErrorInfo());
    				System.exit(0);
    			}
    		}
    		//System.out.println("dddddddddddddddd "+n+" "+oldTypeName);
    		if (n.declaredType.size() > 0) {
    			if (n.declaredType.get(0).equals("struct") || n.declaredType.get(0).equals("union")) {
    				getNewTypeName_origTypeName = n.scopedVaraibles.get(0).structTypeName;
    			}else{
    				getNewTypeName_origTypeName = n.declaredType.get(0);
    			}
    		}else{
    			getNewTypeName_origTypeName = null;
    		}
    		return null;
    	}	
    	
    	String getNewTypeName_origTypeName = "";
    	public String getNewTypeName(String oldTypeName, StatementNode n) {
    		if (notrename)
    			return oldTypeName;
    		long scope = n.scopeID;
    		
    		
    		//System.out.println("||"+oldTypeName+"||");
    		//dont want to replace old type as there is space needed for const etc
    		String oldTypeNameTemp = oldTypeName.replaceAll(" ","");
    		while(scope != -1) {
    			ScopeNode scopeNode = scopeList.get(scope);
    			
    			if (scopeNode != null) {
    				StatementNode typeDefNode = scopeNode.listOfTypeDef.get(oldTypeNameTemp);

    				if (typeDefNode != null) {	
    					if (n.declaredType.size() > 0) {
    						if (n.declaredType.get(0).equals("struct") || n.declaredType.get(0).equals("union")) {
    							getNewTypeName_origTypeName = n.scopedVaraibles.get(0).structTypeName;
    						}else{
    							getNewTypeName_origTypeName = n.declaredType.get(0);
    						}
    					}else{
    						getNewTypeName_origTypeName = null;
    					}
    					
    					return oldTypeName.trim()+"_PRET_"+typeDefNode.getScopeIDwPrefix();
    				}else{
    					scope = scopeNode.parentID;
    				}
    			}else{
    				System.out.println("Error 2 no such scope "+scope);
    				System.out.println(getErrorInfo());
    				System.exit(0);
    			}
    		}
    		//System.out.println("dddddddddddddddd "+oldTypeName);
    		if (n.declaredType.size() > 0) {
    			if (n.declaredType.get(0).equals("struct") || n.declaredType.get(0).equals("union")) {
    				getNewTypeName_origTypeName = n.scopedVaraibles.get(0).structTypeName;
    			}else{
    				getNewTypeName_origTypeName = n.declaredType.get(0);
    			}
    		}else{
    			getNewTypeName_origTypeName = null;
    		}
    		return oldTypeName;
    	}	
    	public String getNewStructName(String oldStructName, StatementNode n) {
    		if (notrename)
    			return oldStructName;
    		//System.out.println("dddffffffffffff "+oldStructName+" "+n.scopeID);
    		long scope = n.scopeID;
    		while(scope != -1) {
    			ScopeNode scopeNode = scopeList.get(scope);
    			if (scopeNode != null) {
    				StatementNode structDefNode = scopeNode.listOfStruct.get(oldStructName);
    				if (structDefNode != null) {
    					return oldStructName+"_PRET_"+structDefNode.getScopeIDwPrefix();
    				}else{
    					scope = scopeNode.parentID;
    				}
    			}else{
    				System.out.println("Error 5 no such scope "+scope);
    				System.exit(0);
    			}
    		}
    		System.out.println("Error struct "+oldStructName+ " not declared statement:");
    		System.out.println(getErrorInfo());
    		System.out.println(n);
    		System.exit(0);
    		return null;
    	}

    	public String getNewVariableName(String oldVarName, StatementNode n) {
    		if (notrename)
    			return oldVarName;
    		if (isFunctionBlock == true) {
    			if (oldVarName.equals("me")) {
    				return oldVarName;
    			}
    		}
    	
    		long scope = n.scopeID;
    		while(scope != -1) {
    			
    			ScopeNode scopeNode = scopeList.get(scope);
    			//System.out.println(oldVarName+"scopeID "+scope+" "+scopeNode);
    			if (scopeNode != null) {
    				StatementNode declareNode = scopeNode.variableMap.get(oldVarName);
    				if (declareNode != null) {
    					return oldVarName+"_PRET_"+declareNode.getScopeIDwPrefix();
    				}else{
    					scope = scopeNode.parentID;
    				}
    			}else{
    				System.out.println("Error 3 no such scope");
    				System.exit(0);
    			}
    		}
    		String newType = getNewTypeName(oldVarName, n);
    		if (oldVarName.equals(newType) == false) {
    			return newType;
    		}
    		if (skipVC == false) {
    			System.out.println("Error variable: "+oldVarName+ " not declared statement:");
    			System.out.println(getErrorInfo());
    		
    			System.exit(0);
    		}else{
    			System.out.println("Warning variable: "+oldVarName+ " not declared statement:");
    		}
    		return oldVarName;
    	}
    	public String getNewVariableNameSearchStruct(String oldVarName, StatementNode structNodes) {
    		if (notrename)
    			return oldVarName;
    		//
    		//while(scope != -1) {
    		//System.out.println("sssss " +oldVarName+ "  "+ structNodes);
    		//for (int i = 0; i < structNodes.size(); i++) {
    		if (structNodes != null) {
    			StatementNode n = structNodes;
    			long scope = n.scopeID;
    			ScopeNode scopeNode = scopeList.get(scope);
    			if (scopeNode != null) {
    				StatementNode structNode =scopeNode.variableMap.get(oldVarName);
    				//System.out.println("xxxxxxxxxxxxxxxxxxxx "+scopeNode.variableMap);
    				if (structNode != null) {
    					//getNewStatement_matched_node = i;
    					return oldVarName+"_PRET_"+structNode.getScopeIDwPrefix();
    				}/*else{
    					scope = scopeNode.parentID;
    				}*/
    			}else{
    				System.out.println("Error 4 no such scope "+scope);
    				System.out.println(getErrorInfo());
    				System.exit(0);
    			}
    		}
    		if (skipVC == false) {
    			System.out.println("Error variable: "+oldVarName+ " not declared statement in struct, statement: ");
    			System.out.println(getErrorInfo());
    			/*StatementNode errorNode = structNodes;
    			while (errorNode.sourceCode.equals("") == true) {
    				errorNode = errorNode.sourceNode;
    			}
    			System.out.println(errorNode.sourceCode);*/
    			System.exit(0);
    			return null;
    		}else{
    			return null;
    		}	
    	}
    	//------------------------------------
    	String currentSource = "";
    	long currentLine = -1;
    	void setErrorInfo(StatementNode n) {
    		currentSource = n.sourceCode;
    		currentLine = n.line;
    	}
    	
    	String getErrorInfo() {
    		return "\nSource: "+currentSource+"\n"
    			+"Line: "+currentLine+"\n";
    	}
    	boolean errorReported = false;
    	protected void mismatch(IntStream input, int ttype, BitSet follow)
    		throws RecognitionException
    	{
    		System.out.println("ddddd "+input);
    		throw new MismatchedTokenException(ttype, input);
    		
    	}
    	
    	public Object recoverFromMismatchedSet(IntStream input, RecognitionException e,BitSet follow)
    		throws RecognitionException
    	{
    		System.out.println("eeeee "+input);
    		throw e;
    	}

    	public String getErrorMessage(RecognitionException e, String[] tokenNames) {
    		return e+"\nlast token matched at: "+((StatementNode)(nodesTable.get(new Long(debugID)))).line;
    	}
    	
    	
    	//global declear of PRET stay inside the method
    	String globalDeclare = "";
    	//main function name
    	String mainFunctionName = "main";
    	//
    	boolean isGlobal = true;
    	



    // $ANTLR start "translation_unit"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1167:1: translation_unit : ( external_declaration )+ ;
    public final void translation_unit() throws RecognitionException {
        int translation_unit_StartIndex = input.index();

        	timeMeSim = new TimeMeSimulation(timeMeSimulation,scopeList);
        	System.out.println(nodesTable);
        	System.out.println("-------------------------------");
        	System.out.println(scopeList);
        	projectInsName = projectPrefix;
        	if (projectPrefix.length() == 0) {
        		hadProjectPrefix = false;
        		projectPrefix = projectName+"_";
        	}else{
        		projectPrefix = projectPrefix+"_"+projectName+"_";
        	}	 
        	if (projectName.equals("a") == false && isFunctionBlock == false) {
        		outputMainFilename = projectName + ".main.c";
        		outputThdHeaderFilename = projectName + ".thd.h";
        		outputPretHeaderFilename = projectName + ".PRET.h";	
        		outputGlobalASMPretHeaderFilename = projectName+".PRET.GLBASM.h";
        	}else if (isFunctionBlock == true) {
        		String temp = projectPrefix.substring(0,projectPrefix.length()-1);
        		outputMainFilename = temp + ".c";
        		outputThdHeaderFilename = temp + ".thd.h";
        		outputPretHeaderFilename = temp + ".PRET.h";	
        		outputGlobalASMPretHeaderFilename = temp+".PRET.GLBASM.h";
        	}

        	//setup ID prefix to nodes
        	for (Enumeration<StatementNode> e = nodesTable.elements();e.hasMoreElements();) {
        		StatementNode s = e.nextElement();
        		s.IDprefix = projectPrefix;
        	}

        	//
        	
        	//TIME ME SIMULATION
        	timeMeSim.socketOff = socketOff;
        	timeMeSim.createSimuFile(projectName,projectPrefix,path);
        	
        	timeMeSim.writeMain(mainFunctionName);
        	//
        	
        	writerMain = new CFilePrinter(outputMainFilename,path);
        	writerMain.print(mainPrefix);
        	writerThdHdr = new CFilePrinter(outputThdHeaderFilename,path);
        	writerPretHdr =  new CFilePrinter(outputPretHeaderFilename,path);
        	writerPretGlbASM = new CFilePrinter(outputGlobalASMPretHeaderFilename,path);
        	String codeTemp ="";
        	printer = writerMain;
        	if (isFunctionBlock) {
        		writerMain.print("#include \""+projectPrefix.substring(0,projectPrefix.length()-1)+".h\"\n");
        	}
        	if (timeMeSim.timeMeSimulation) {
        		
        		writerMain.print("#include \""+projectPrefix.substring(0,projectPrefix.length()-1)+".simu.h\"\n");
        		
        	

        		
        	}
        	
        	if (isFunctionBlock) {
        		writerMain.print("void "+projectPrefix.substring(0,projectPrefix.length()-1)+"init("+projectPrefix.substring(0,projectPrefix.length()-1)+"* me) {\n");

           		writerMain.print("memset(me,0 , sizeof("+projectPrefix.substring(0,projectPrefix.length()-1)+"));\n");

        		writerMain.print("}\n");
        	}
        	if (annotateOnly) {
        	
        	}else{
        		
        		printer.print("#include \""+outputPretHeaderFilename+"\"\n"); 
        		codeTemp = "static Node PRET_Node_main_ID_0,GlobalTick";
        		
        		StatementNode node;
        		
        		for (Enumeration e = nodesTable.keys(); e.hasMoreElements() ;) {
        			node = getNode(""+e.nextElement());
        			//System.out.println("ssss2"+node);
        			if (node.type.equals("PAR")) {
        				for (int j=0; j<node.name.size(); j++) {
        					//System.out.println("ssss3"+node.name.get(j));
        					codeTemp += ",PRET_Node_"+node.name.get(j)+"_ID_"+node.thdInsID.get(j);
        					//possibly add check to see thread really exists
        				}
        			}
        		}
        		codeTemp += ";\n";
        		/*replaced the 2 lines with  */
        		//printer.print(codeTemp);
        		globalDeclare += codeTemp;
        		//printer.print("Node* activeNode = &PRET_Node_main_ID_0;\n" );
        		globalDeclare += "static Node* activeNode = &PRET_Node_main_ID_0;\n";
        		
        	
        		printer = writerPretHdr;
        		printer.print("#ifndef PRET_C_NODE\n");
        		printer.print("#define PRET_C_NODE\n");
        		printer.print("typedef struct _Node{\n");
        		printer.indent++;
        		printer.print("void *PC;\n");
        		printer.print("void *deathAddr;\n");
        		printer.print("int spawnCtr;\n");
        		printer.print("struct _Node *next;\n");
        		printer.print("struct _Node *prev;\n");
        		printer.print("struct _Node *parent;\n");
        		printer.indent--;
        		printer.print("} Node;\n");
        		printer.print("#endif\n"); 
        		   
        		
        		printer = writerMain;
        	}
        	

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 1) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1303:2: ( ( external_declaration )+ )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1303:4: ( external_declaration )+
            {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1303:4: ( external_declaration )+
            int cnt1=0;
            loop1:
            do {
                int alt1=2;
                int LA1_0 = input.LA(1);

                if ( ((LA1_0>=FUNCTION_TOK && LA1_0<=GLOBAL_DECLARATION_TOK)||LA1_0==PRET_DEF_TOK||(LA1_0>=42 && LA1_0<=43)||LA1_0==48) ) {
                    alt1=1;
                }


                switch (alt1) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:0:0: external_declaration
            	    {
            	    pushFollow(FOLLOW_external_declaration_in_translation_unit86);
            	    external_declaration();

            	    state._fsp--;
            	    if (state.failed) return ;

            	    }
            	    break;

            	default :
            	    if ( cnt1 >= 1 ) break loop1;
            	    if (state.backtracking>0) {state.failed=true; return ;}
                        EarlyExitException eee =
                            new EarlyExitException(1, input);
                        throw eee;
                }
                cnt1++;
            } while (true);


            }

            if ( state.backtracking==0 ) {

              	//Time Me sim
              	timeMeSim.closeSimuFile();

              	//
              	writerMain.print("\n");
              	writerMain.print(mainSuffix);
              	writerMain.close();
              	if (annotateOnly) {
              	
              	}else{
              		writerThdHdr.print("\n");
              		writerPretHdr.print("\n");
              	
              		writerThdHdr.close();
              		writerPretHdr.close();
              	}
              	writerPretGlbASM.print("\n");
              	writerPretGlbASM.close();
              	//printer.close();

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 1, translation_unit_StartIndex); }
        }
        return ;
    }
    // $ANTLR end "translation_unit"


    // $ANTLR start "external_declaration"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1305:1: external_declaration options {k=1; } : ( ^( FUNCTION_TOK ID_TOK SOURCE_TOK ( declaration )* scope_statement ) | ^( GLOBAL_DECLARATION_TOK declaration ) | ^( 'ReactiveInput' ID_TOK SOURCE_TOK ) | ^( 'ReactiveOutput' ID_TOK SOURCE_TOK ) | ^( 'thread' ID_TOK SOURCE_TOK scope_statement ) | PRET_DEF_TOK );
    public final void external_declaration() throws RecognitionException {
        isFromFunction_stack.push(new isFromFunction_scope());

        int external_declaration_StartIndex = input.index();
        CommonTree ID_TOK1=null;
        CommonTree SOURCE_TOK2=null;
        CommonTree ID_TOK3=null;
        CommonTree SOURCE_TOK4=null;
        CommonTree ID_TOK5=null;
        CommonTree ID_TOK6=null;


        	((isFromFunction_scope)isFromFunction_stack.peek()).data = new Boolean(false);
        	((isFromFunction_scope)isFromFunction_stack.peek()).isSwitchData = new Boolean(false); 
        	((isFromFunction_scope)isFromFunction_stack.peek()).SwitchVar = "";
        	((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket ="";
        	((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket_after ="";
        	isGlobal = true;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 2) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1318:2: ( ^( FUNCTION_TOK ID_TOK SOURCE_TOK ( declaration )* scope_statement ) | ^( GLOBAL_DECLARATION_TOK declaration ) | ^( 'ReactiveInput' ID_TOK SOURCE_TOK ) | ^( 'ReactiveOutput' ID_TOK SOURCE_TOK ) | ^( 'thread' ID_TOK SOURCE_TOK scope_statement ) | PRET_DEF_TOK )
            int alt3=6;
            switch ( input.LA(1) ) {
            case FUNCTION_TOK:
                {
                alt3=1;
                }
                break;
            case GLOBAL_DECLARATION_TOK:
                {
                alt3=2;
                }
                break;
            case 42:
                {
                alt3=3;
                }
                break;
            case 43:
                {
                alt3=4;
                }
                break;
            case 48:
                {
                alt3=5;
                }
                break;
            case PRET_DEF_TOK:
                {
                alt3=6;
                }
                break;
            default:
                if (state.backtracking>0) {state.failed=true; return ;}
                NoViableAltException nvae =
                    new NoViableAltException("", 3, 0, input);

                throw nvae;
            }

            switch (alt3) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1318:4: ^( FUNCTION_TOK ID_TOK SOURCE_TOK ( declaration )* scope_statement )
                    {
                    match(input,FUNCTION_TOK,FOLLOW_FUNCTION_TOK_in_external_declaration123); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK1=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_external_declaration125); if (state.failed) return ;
                    SOURCE_TOK2=(CommonTree)match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_external_declaration127); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK1!=null?ID_TOK1.getText():null)));
                      			
                      		
                    }
                    if ( state.backtracking==0 ) {

                      			isGlobal = false;
                      			//System.out.println("ID: "+ getNode("1"));
                      			//codeTemp  = getNode((ID_TOK1!=null?ID_TOK1.getText():null)).sourceCode+"\n";
                      			functionNode = getNode((ID_TOK1!=null?ID_TOK1.getText():null));
                      			codeTemp = getNewTypeName(functionNode.returnType,functionNode);
                      		//	if (functionNode.name.get(0).equals("main")) {
                      			if (notrename==false) {
                      				if (functionNode.name.get(0).equals(mainFunctionName)) {
                      			
                      					if (isFunctionBlock) {
                      						if (hadProjectPrefix==false) {
                      							codeTemp += " "+projectInsName+functionNode.name.get(0);
                      						}else{
                      							codeTemp += " "+projectInsName+"_"+functionNode.name.get(0);
                      						}
                      					}else{
                      						codeTemp += " "+functionNode.name.get(0);
                      					}
                      				}else{
                      					codeTemp += " "+projectPrefix+functionNode.name.get(0);
                      				}
                      			}else{
                      				codeTemp += " "+functionNode.name.get(0);
                      			}
                      			codeTemp += "(";
                      			if (isFunctionBlock) {
                      				codeTemp += projectPrefix.substring(0,projectPrefix.length()-1) + " *me";
                      			}else{
                      				//System.out.println("ppppppppppppppp "+functionNode.functionParameter.size());
                      				for (int i = 1; i < functionNode.varSpecifiers.size();i++) {
                      					//i = 0 is the return type
                      					int i2 = i-1;
                      					codeTemp +=getNewTypeName(functionNode.varSpecifiers.get(i),functionNode);
                      					//printer.print("ddd|"+functionNode.varSpecifiers.get(i)+"|");
                      					//System.out.println("ww "+i);
                      					if (functionNode.functionParameter.size() == 0) {
                      						break;
                      					}
                      					codeTemp += " "+ getNewStatementString(functionNode.functionParameter.get(i2),functionNode)+",";
                      					
                      				} 
                      				//System.out.println("ddddddddddddddd "+(SOURCE_TOK2!=null?SOURCE_TOK2.getText():null));
                      				if (functionNode.varSpecifiers.size() > 1) {
                      					codeTemp = codeTemp.substring(0,codeTemp.length()-1);
                      				}
                      			}
                      			codeTemp = codeTemp.replaceAll("  "," ");
                      			codeTemp += ")\n";
                      			printer.print(codeTemp);
                      			((isFromFunction_scope)isFromFunction_stack.peek()).data = true;
                      		
                    }
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1375:5: ( declaration )*
                    loop2:
                    do {
                        int alt2=2;
                        int LA2_0 = input.LA(1);

                        if ( ((LA2_0>=DECLARATION_TOK && LA2_0<=TYPE_DECLARATION_TOK)||LA2_0==PREPROC_TOK) ) {
                            alt2=1;
                        }


                        switch (alt2) {
                    	case 1 :
                    	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:0:0: declaration
                    	    {
                    	    pushFollow(FOLLOW_declaration_in_external_declaration137);
                    	    declaration();

                    	    state._fsp--;
                    	    if (state.failed) return ;

                    	    }
                    	    break;

                    	default :
                    	    break loop2;
                        }
                    } while (true);

                    pushFollow(FOLLOW_scope_statement_in_external_declaration140);
                    scope_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1376:4: ^( GLOBAL_DECLARATION_TOK declaration )
                    {
                    match(input,GLOBAL_DECLARATION_TOK,FOLLOW_GLOBAL_DECLARATION_TOK_in_external_declaration147); if (state.failed) return ;

                    if ( state.backtracking==0 ) {
                      functionNode = null;
                    }

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    pushFollow(FOLLOW_declaration_in_external_declaration152);
                    declaration();

                    state._fsp--;
                    if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1377:4: ^( 'ReactiveInput' ID_TOK SOURCE_TOK )
                    {
                    match(input,42,FOLLOW_42_in_external_declaration159); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK3=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_external_declaration161); if (state.failed) return ;
                    SOURCE_TOK4=(CommonTree)match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_external_declaration163); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK3!=null?ID_TOK3.getText():null)));
                      		
                    }
                    if ( state.backtracking==0 ) {

                      		//codeTemp = getNode((ID_TOK3!=null?ID_TOK3.getText():null));
                      		//printer.print((SOURCE_TOK4!=null?SOURCE_TOK4.getText():null));
                      		ASMio = "input";
                      		printer.print("//reactive input\n");
                      		printDeclare(getNode((ID_TOK3!=null?ID_TOK3.getText():null)));
                      		ASMio = "internal";
                      	//System.out.println("RRRRRRRRRRRRR "+getNode((ID_TOK3!=null?ID_TOK3.getText():null)));
                      		
                    }

                    }
                    break;
                case 4 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1391:4: ^( 'ReactiveOutput' ID_TOK SOURCE_TOK )
                    {
                    match(input,43,FOLLOW_43_in_external_declaration179); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK5=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_external_declaration181); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_external_declaration183); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK5!=null?ID_TOK5.getText():null)));
                      		
                    }
                    if ( state.backtracking==0 ) {

                      		ASMio = "input";
                      		printer.print("//reactive output\n");
                      		printDeclare(getNode((ID_TOK5!=null?ID_TOK5.getText():null)));
                      		ASMio = "internal";
                      		
                    }

                    }
                    break;
                case 5 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1402:4: ^( 'thread' ID_TOK SOURCE_TOK scope_statement )
                    {
                    match(input,48,FOLLOW_48_in_external_declaration198); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK6=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_external_declaration200); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_external_declaration202); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK6!=null?ID_TOK6.getText():null)));
                      		
                    }
                    if ( state.backtracking==0 ) {
                       
                      			isGlobal = false;
                      			printer = writerThdHdr;
                      			printer.print("/*Thread "+ getNode((ID_TOK6!=null?ID_TOK6.getText():null)).name.get(0) + " */\n");
                      			printer.print(getNode((ID_TOK6!=null?ID_TOK6.getText():null)).name.get(0)+":\n");
                      			//printer.print("PRET_Node_main_ID_0:;\n");
                      	  		printer.print("asm(\"nop\");/*asm(\"#@PRET_Thread start "+getNode((ID_TOK6!=null?ID_TOK6.getText():null)).name.get(0)+"\");*/\n");
                      			functionNode = getNode((ID_TOK6!=null?ID_TOK6.getText():null));
                      			
                      			((isFromFunction_scope)isFromFunction_stack.peek()).data = true;
                      		
                    }
                    pushFollow(FOLLOW_scope_statement_in_external_declaration215);
                    scope_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {
                      printer = writerMain;
                    }

                    }
                    break;
                case 6 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1419:4: PRET_DEF_TOK
                    {
                    match(input,PRET_DEF_TOK,FOLLOW_PRET_DEF_TOK_in_external_declaration223); if (state.failed) return ;

                    }
                    break;

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 2, external_declaration_StartIndex); }
            isFromFunction_stack.pop();

        }
        return ;
    }
    // $ANTLR end "external_declaration"


    // $ANTLR start "declaration"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1422:1: declaration : ( ^( TYPE_DECLARATION_TOK ID_TOK SOURCE_TOK ) | ^( DECLARATION_TOK ID_TOK SOURCE_TOK ) | PREPROC_TOK );
    public final void declaration() throws RecognitionException {
        int declaration_StartIndex = input.index();
        CommonTree ID_TOK7=null;
        CommonTree ID_TOK8=null;
        CommonTree PREPROC_TOK9=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 3) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1423:2: ( ^( TYPE_DECLARATION_TOK ID_TOK SOURCE_TOK ) | ^( DECLARATION_TOK ID_TOK SOURCE_TOK ) | PREPROC_TOK )
            int alt4=3;
            switch ( input.LA(1) ) {
            case TYPE_DECLARATION_TOK:
                {
                alt4=1;
                }
                break;
            case DECLARATION_TOK:
                {
                alt4=2;
                }
                break;
            case PREPROC_TOK:
                {
                alt4=3;
                }
                break;
            default:
                if (state.backtracking>0) {state.failed=true; return ;}
                NoViableAltException nvae =
                    new NoViableAltException("", 4, 0, input);

                throw nvae;
            }

            switch (alt4) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1423:4: ^( TYPE_DECLARATION_TOK ID_TOK SOURCE_TOK )
                    {
                    match(input,TYPE_DECLARATION_TOK,FOLLOW_TYPE_DECLARATION_TOK_in_declaration238); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK7=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_declaration240); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_declaration242); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK7!=null?ID_TOK7.getText():null)));
                      			printer.print("// line:"+getNode((ID_TOK7!=null?ID_TOK7.getText():null)).line+"\n");
                      			if (timeMeSim.timeMeSimulation && functionNode != null) {
                      				printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK7!=null?ID_TOK7.getText():null)).line+",\");\n");
                      			}
                      		
                    }
                    if ( state.backtracking==0 ) {

                      			//System.out.println("ID: "+ getNode("1"));
                      			
                      			//codeTemp  = getNode((ID_TOK7!=null?ID_TOK7.getText():null)).sourceCode+"\n";
                      			//printer.print(codeTemp);
                      			printDeclare(getNode((ID_TOK7!=null?ID_TOK7.getText():null)));
                      			//System.out.println("TTTTTTTTTTTT "+getNode((ID_TOK7!=null?ID_TOK7.getText():null)));
                      		
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1440:4: ^( DECLARATION_TOK ID_TOK SOURCE_TOK )
                    {
                    match(input,DECLARATION_TOK,FOLLOW_DECLARATION_TOK_in_declaration258); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK8=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_declaration260); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_declaration262); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK8!=null?ID_TOK8.getText():null)));
                      			printer.print("// line:"+getNode((ID_TOK8!=null?ID_TOK8.getText():null)).line+"\n");
                      			if (timeMeSim.timeMeSimulation && functionNode != null) {
                      				printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK8!=null?ID_TOK8.getText():null)).line+",\");\n");
                      			}
                      		
                    }
                    if ( state.backtracking==0 ) {

                      			//System.out.println("ID: "+ getNode("1"));
                      			//System.out.println( getNode((ID_TOK8!=null?ID_TOK8.getText():null)));
                      			//System.out.println("dd"+functionNode.name+"dd");
                      			
                      			printDeclare(getNode((ID_TOK8!=null?ID_TOK8.getText():null)));
                      			
                      			//codeTemp  = getNode((ID_TOK8!=null?ID_TOK8.getText():null)).sourceCode+"\n";
                      			//force static or else on return lose var states
                      			/*if (functionNode != null) {
                      				if (codeTemp.contains("static ") == false && (functionNode.type.equals("thread") || functionNode.name.get(0).equals(mainFunctionName))) {
                      					codeTemp = "static "+codeTemp;
                      				}
                      			}
                      			printer.print(codeTemp);*/
                      			//System.out.println("TTTTTTTTTTTT "+getNode((ID_TOK8!=null?ID_TOK8.getText():null)));
                      		
                    }

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1466:4: PREPROC_TOK
                    {
                    PREPROC_TOK9=(CommonTree)match(input,PREPROC_TOK,FOLLOW_PREPROC_TOK_in_declaration276); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			printer.print("\n"+(PREPROC_TOK9!=null?PREPROC_TOK9.getText():null));
                      		
                    }

                    }
                    break;

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 3, declaration_StartIndex); }
        }
        return ;
    }
    // $ANTLR end "declaration"


    // $ANTLR start "scope_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1473:1: scope_statement : ^( SCOPE_TOK ( compound_statement | EMPTY_TOK ) END_TOK ) ;
    public final void scope_statement() throws RecognitionException {
        int scope_statement_StartIndex = input.index();
        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 4) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1581:2: ( ^( SCOPE_TOK ( compound_statement | EMPTY_TOK ) END_TOK ) )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1581:4: ^( SCOPE_TOK ( compound_statement | EMPTY_TOK ) END_TOK )
            {
            match(input,SCOPE_TOK,FOLLOW_SCOPE_TOK_in_scope_statement305); if (state.failed) return ;

            if ( state.backtracking==0 ) {

              		
              		printer.print("{\n");
              		printer.indent++;
              		scopeDelayASMPrint = false;
              		ASMPrint();
              		if (functionNode.name.get(0).equals(mainFunctionName)&&(isFromFunction_stack.size() > 0 && ((isFromFunction_scope)isFromFunction_stack.peek()).data == true)) {
              			printer.print("#include \""+outputGlobalASMPretHeaderFilename+"\"\n"); 
              		}
              		if (annotateOnly) {
              			if (functionNode.name.get(0).equals(mainFunctionName)&&(isFromFunction_stack.size() > 0 && ((isFromFunction_scope)isFromFunction_stack.peek()).data == true)) {
              				//printer.print("asm(\"#@PRET_Parse start\");\n");
              				//printer.print("asm(\"#@PRET_Thread start PRET_Node_main_ID_0\");\n");
              			}
              		}else{
              			if (functionNode.name.get(0).equals(mainFunctionName)&&(isFromFunction_stack.size() > 0 && ((isFromFunction_scope)isFromFunction_stack.peek()).data == true)) {
              			//pret setup code
              				//print global vars
              				printer.print("//global thread state vars \n");
              				printer.print(globalDeclare.replaceAll("\n"," ")+"\n");
              				// if not main as main function need test if 1st enterence or not entry or not
              				if (mainFunctionName.equals("main") == false) {
              					printer.print("static char PRET_FIRST_ENTER = 1; \n");
              					printer.print("if (PRET_FIRST_ENTER == 0) { \n");
              					printer.indent++;
              						printer.print("goto *(activeNode->PC); \n");
              					printer.indent--;
              					printer.print("}else{\n");
              					printer.indent++;
              						printer.print("PRET_FIRST_ENTER = 0; \n");
              					printer.indent--;
              					printer.print("}");
              				}
              				
              				printer.print("//setup code \n");
              				printer.print("GlobalTick.PC = &&GlobalTick_function;\n");
              				printer.print("GlobalTick.prev=&PRET_Node_main_ID_0;\n");
              				printer.print("GlobalTick.next=&PRET_Node_main_ID_0;\n");
              				printer.print("GlobalTick.parent=0;\n");
              		 		printer.print("PRET_Node_main_ID_0.prev=&GlobalTick;\n");
              				printer.print("PRET_Node_main_ID_0.next=&GlobalTick;\n");
              				printer.print("PRET_Node_main_ID_0.parent=0; /*its parent is null*/\n");
              				printer.print("PRET_Node_main_ID_0.spawnCtr=0;\n");
              		  		printer.print("//setup code \n");
              		  		printer.print("asm(\"nop\");/*asm(\"#@PRET_Parse start\");*//*asm(\"#@PRET_Thread start PRET_Node_main_ID_0\");*/\n");
              		  		printer.print("PRET_Node_main_ID_0:;\n");
              		  		
              			}
              		}
              		if (functionNode.type.equals("function")&&(isFromFunction_stack.size() > 0 && ((isFromFunction_scope)isFromFunction_stack.peek()).data == true)) {

              			for (int i = 1; i < functionNode.varSpecifiers.size();i++) {
              				//i = 0 is the return type
              				int i2 = i-1;
              				String type = getNewTypeName(functionNode.varSpecifiers.get(i),functionNode);
              				//System.out.println("ww "+i);
              				if (functionNode.functionParameter.size() == 0) {
              					break;
              				}
              				String name = " "+ getNewStatementString(functionNode.functionParameter.get(i2),functionNode);
              				if (functionNode.minValue.size() > i2 && functionNode.maxValue.size() > i2 ) {
              					String min = functionNode.minValue.get(i2);
              					String max = functionNode.maxValue.get(i2);
              					if (min.equals("UNDEFINED") || max.equals("UNDEFINED")) {
              						printASMVarDeclare(name,"internal",type,"null","null","null");
              					}else{
              						printASMVarDeclare(name,"internal",type,"null",min,max);
              					}
              				}else{
              					printASMVarDeclare(name,"internal",type,"null","null","null");
              				}
              			} 
              			
              			if (functionNode.returnType.equals("void") == false){
              				String functionReturn = "PRET_RETURN_VAR_"+functionNode.getIDwPrefix();	
              				String returnType = functionNode.returnType + functionNode.name.get(0).replaceAll("[A-Za-z_ 0-9]","");
              				printASMVarDeclare(functionReturn,"internal",returnType,"null","null","null");
              			}

              		}
              		
            }

            match(input, Token.DOWN, null); if (state.failed) return ;
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1662:5: ( compound_statement | EMPTY_TOK )
            int alt5=2;
            alt5 = dfa5.predict(input);
            switch (alt5) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1662:6: compound_statement
                    {
                    pushFollow(FOLLOW_compound_statement_in_scope_statement312);
                    compound_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1662:25: EMPTY_TOK
                    {
                    match(input,EMPTY_TOK,FOLLOW_EMPTY_TOK_in_scope_statement314); if (state.failed) return ;

                    }
                    break;

            }

            match(input,END_TOK,FOLLOW_END_TOK_in_scope_statement317); if (state.failed) return ;

            match(input, Token.UP, null); if (state.failed) return ;

            }

            if ( state.backtracking==0 ) {

              	//System.out.println(functionNode.name.get(0) + "ssssssssssssssssssssssssssss");
              	if (functionNode.name.get(0).equals(mainFunctionName)&&(isFromFunction_stack.size() > 0 && ((isFromFunction_scope)isFromFunction_stack.peek()).data == true)) {
              		if (annotateOnly) {
              		
              		}else{
              			if (mainFunctionName.equals("main") == false) {
              				printer.print("activeNode->PC = &&PRET_END;\n");	
              			}	 
              			printer.print("PRET_END:; \n");
              			printer.print("asm(\"nop\");/*asm(\"#@PRET_EOT start\");#@PRET_NL*/\\\n");
              			//make it alway return when died
              			if (mainFunctionName.equals("main") == false) {
              	    			printer.print("return;\n");	
              			}
              			printer.print("asm(\"nop\");/*asm(\"#@PRET_EOT end\");#@PRET_NL*/\\\n");
              			printer.print("goto PRET_END;\n");
              			
              			printer.print("#include \""+outputThdHeaderFilename+"\"\n"); 
              		
              			printer.print("GlobalTick_function:; \n");
              			printer.print("asm(\"nop\");/*asm(\"#@PRET_Thread start GlobalTick_function\");*/\n");
              			printer.print("asm(\"nop\");/*asm(\"#@PRET_Parse end\");*/\n");
              			if (tickDelay != 0) {
              				printer.print("usleep("+tickDelay+");\n");
              			}
              			printer.print("//variable map \n");
              			for (Enumeration<ScopeNode> e = scopeList.elements();e.hasMoreElements();) {
              				ScopeNode n = e.nextElement();
              				printer.print("//scope "+n.ID+"\n");
              				for (Enumeration<String> e2 = n.variableMap.keys();e2.hasMoreElements();) {
              					String variableName = e2.nextElement();
              					StatementNode nDeclare = n.variableMap.get(variableName); //node of declared variable
              					String newVariableName = getNewVariableName(variableName,nDeclare);
              					if (nDeclare.type.equals("ReactiveOutput")) {
              						printer.print("//reactive Output\n");
              					}else if (nDeclare.type.equals("ReactiveInput")) {
              						printer.print("//reactive Input\n");
              					}else{
              					
              					}
              					printer.print("//"+variableName+" -> "+newVariableName+"\n");

              				}
              				
              				
              			}
              			if (timeMeSim.timeMeSimulation) {
              				printer.print(projectPrefix+"runPRETXML(me);\n");
              			}
              			printer.print("\tactiveNode = GlobalTick.next;\n");
              			if (mainFunctionName.equals("main") == false) {
              				printer.print("return;\n");
              			}else{
              				printer.print("\tgoto *(activeNode->PC);\n");
              			}
              		}
              	} 
              	if (functionNode.type.equals("thread")&&(isFromFunction_stack.size() > 0 && ((isFromFunction_scope)isFromFunction_stack.peek()).data == true)) {
              		printer.print(functionNode.name.get(0)+"_death:\n");
              		printer.print("KILL_"+functionNode.name.get(0)+"\n");
              		printerTemp = printer;
              		printer = writerPretHdr;
              		//String thread = "PRET_Node_"+nodeTemp.name.get(0)+"_ID_"+nodeTemp.thdInsID.get(0);
              		printer.print("#define KILL_"+functionNode.name.get(0)+" \\\n");
              		printer.print("asm(\"nop\");/*asm(\"#@PRET_KILL start\");*/"+"/*asm(\"#@PRET_GroupID "+findParID(functionNode.name.get(0))+"\");#@PRET_NL*/\\\n"); //temp id is 0 need other if hugh needs it
              		printer.print("(activeNode->parent)->spawnCtr--;\\\n");
              		
              //		printer.print("asm(\"#@GroupID " #ID);\

                   	printer.print("if((activeNode->parent)->spawnCtr==0) /* means all children are dead, revive parent thread #@PRET_NL*/\\\n");
              		printer.print("{\\\n");
              		printer.indent++;
                     	printer.print("(activeNode->prev)->next = (activeNode->parent);\\\n");
                      printer.print("(activeNode->next)->prev = (activeNode->parent);\\\n");
                      printer.print("(activeNode->parent)->prev=activeNode->prev;\\\n");
                      printer.print("(activeNode->parent)->next=activeNode->next;\\\n");
                      printer.print("activeNode=activeNode->parent;\\\n");
                      printer.print("goto *(activeNode->PC);\\\n");
                      printer.indent--;
                      printer.print("}else{\\\n");
                      printer.indent++;
                      printer.print("(activeNode->prev)->next = activeNode->next;\\\n");
                      printer.print("(activeNode->next)->prev = activeNode->prev;\\\n");
              		printer.print("activeNode=activeNode->next;\\\n");
                      printer.print("goto *(activeNode->PC);\\\n");
                      printer.print("asm(\"nop\");/*asm(\"#@PRET_KILL end\");#@PRET_NL*/\\\n");
                      printer.indent--;
                    	printer.print("}\\\n\n");     
                    
              		printer = printerTemp;
              	}

              	if (isFromFunction_stack.size() > 0 && ((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket.length() > 0) {
              		printer.print( ((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket+"\n");
              		 ((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket = "";
              	}
              	
              	
              	printer.indent--;
              	printer.print("}\n");
              	if (isFromFunction_stack.size() > 0 && ((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket_after.length() > 0) {
              		printer.print(((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket_after+"\n");
              		((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket_after = "";
              	}

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 4, scope_statement_StartIndex); }
        }
        return ;
    }
    // $ANTLR end "scope_statement"


    // $ANTLR start "compound_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1665:1: compound_statement : ( declaration | statement_list )* ;
    public final void compound_statement() throws RecognitionException {
        int compound_statement_StartIndex = input.index();
        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 5) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1666:2: ( ( declaration | statement_list )* )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1666:4: ( declaration | statement_list )*
            {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1666:4: ( declaration | statement_list )*
            loop6:
            do {
                int alt6=3;
                alt6 = dfa6.predict(input);
                switch (alt6) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1666:6: declaration
            	    {
            	    pushFollow(FOLLOW_declaration_in_compound_statement335);
            	    declaration();

            	    state._fsp--;
            	    if (state.failed) return ;

            	    }
            	    break;
            	case 2 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1666:20: statement_list
            	    {
            	    pushFollow(FOLLOW_statement_list_in_compound_statement339);
            	    statement_list();

            	    state._fsp--;
            	    if (state.failed) return ;

            	    }
            	    break;

            	default :
            	    break loop6;
                }
            } while (true);


            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 5, compound_statement_StartIndex); }
        }
        return ;
    }
    // $ANTLR end "compound_statement"


    // $ANTLR start "statement_list"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1669:1: statement_list : ( statement )+ ;
    public final void statement_list() throws RecognitionException {
        int statement_list_StartIndex = input.index();
        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 6) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1670:2: ( ( statement )+ )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1670:4: ( statement )+
            {
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1670:4: ( statement )+
            int cnt7=0;
            loop7:
            do {
                int alt7=2;
                alt7 = dfa7.predict(input);
                switch (alt7) {
            	case 1 :
            	    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:0:0: statement
            	    {
            	    pushFollow(FOLLOW_statement_in_statement_list353);
            	    statement();

            	    state._fsp--;
            	    if (state.failed) return ;

            	    }
            	    break;

            	default :
            	    if ( cnt7 >= 1 ) break loop7;
            	    if (state.backtracking>0) {state.failed=true; return ;}
                        EarlyExitException eee =
                            new EarlyExitException(7, input);
                        throw eee;
                }
                cnt7++;
            } while (true);


            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 6, statement_list_StartIndex); }
        }
        return ;
    }
    // $ANTLR end "statement_list"


    // $ANTLR start "statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1673:1: statement : ( ^( LABELED_STATMENT_TOK ID_TOK SOURCE_TOK ) | ^( EXPRESSION_STATMENT_TOK ID_TOK SOURCE_TOK ) | selection_statement | iteration_statement | ^( JUMP_STATMENT_TOK ID_TOK SOURCE_TOK ) | parallel_statement | ^( 'EOT' ID_TOK SOURCE_TOK ) | preemption_statment | scope_statement );
    public final void statement() throws RecognitionException {
        int statement_StartIndex = input.index();
        CommonTree ID_TOK10=null;
        CommonTree ID_TOK11=null;
        CommonTree ID_TOK12=null;
        CommonTree ID_TOK13=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 7) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1680:2: ( ^( LABELED_STATMENT_TOK ID_TOK SOURCE_TOK ) | ^( EXPRESSION_STATMENT_TOK ID_TOK SOURCE_TOK ) | selection_statement | iteration_statement | ^( JUMP_STATMENT_TOK ID_TOK SOURCE_TOK ) | parallel_statement | ^( 'EOT' ID_TOK SOURCE_TOK ) | preemption_statment | scope_statement )
            int alt8=9;
            alt8 = dfa8.predict(input);
            switch (alt8) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1680:4: ^( LABELED_STATMENT_TOK ID_TOK SOURCE_TOK )
                    {
                    match(input,LABELED_STATMENT_TOK,FOLLOW_LABELED_STATMENT_TOK_in_statement368); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK10=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_statement370); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK10!=null?ID_TOK10.getText():null)));
                      			printer.print("// line:"+getNode((ID_TOK10!=null?ID_TOK10.getText():null)).line+"\n");
                      			if (timeMeSim.timeMeSimulation) {
                      				printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK10!=null?ID_TOK10.getText():null)).line+",\");\n");
                      			}
                      		
                    }
                    if ( state.backtracking==0 ) {

                      			codeTemp  = getNode((ID_TOK10!=null?ID_TOK10.getText():null)).sourceCode+";\n";
                      			System.out.println("label: "+codeTemp);
                      			printer.print(codeTemp);
                      			if (isFromFunction_stack.size() > 0 && ((isFromFunction_scope)isFromFunction_stack.peek()).isSwitchData == true) {
                      				if (getNode((ID_TOK10!=null?ID_TOK10.getText():null)).type.equals("case")) {
                      					String PRETvar = ((isFromFunction_scope)isFromFunction_stack.peek()).SwitchVar;
                      					printASMTest((getNode((ID_TOK10!=null?ID_TOK10.getText():null)).sourceCode).replaceFirst("case",PRETvar+"==").replaceAll(":",""));
                      					((isFromFunction_scope)isFromFunction_stack.peek()).SwitchDefaultCondition += (getNode((ID_TOK10!=null?ID_TOK10.getText():null)).sourceCode).replaceFirst("case",PRETvar+"==").replaceAll(":","") + "&&";
                      				}else if (getNode((ID_TOK10!=null?ID_TOK10.getText():null)).type.equals("default")) {
                      					String defaultCondition = ((isFromFunction_scope)isFromFunction_stack.peek()).SwitchDefaultCondition;
                      					defaultCondition = defaultCondition.substring(0,defaultCondition.length()-2);
                      					printASMTest("!("+defaultCondition+")");
                      				}
                      			}
                      		
                    }
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_statement384); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1707:4: ^( EXPRESSION_STATMENT_TOK ID_TOK SOURCE_TOK )
                    {
                    match(input,EXPRESSION_STATMENT_TOK,FOLLOW_EXPRESSION_STATMENT_TOK_in_statement394); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK11=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_statement396); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_statement398); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK11!=null?ID_TOK11.getText():null)));
                      			printer.print("// line:"+getNode((ID_TOK11!=null?ID_TOK11.getText():null)).line+"\n");
                      			if (timeMeSim.timeMeSimulation) {
                      				printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK11!=null?ID_TOK11.getText():null)).line+",\");\n");
                      			}
                      		
                    }
                    if ( state.backtracking==0 ) {

                      			//codeTemp  = getNode((ID_TOK11!=null?ID_TOK11.getText():null)).sourceCode+"\n";
                      			codeTemp = getNewStatement(getNode((ID_TOK11!=null?ID_TOK11.getText():null)))+"\n";
                      			printASMSet(codeTemp.replaceAll("\n",""));
                      			printer.print(codeTemp);
                      		
                    }

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1722:4: selection_statement
                    {
                    pushFollow(FOLLOW_selection_statement_in_statement413);
                    selection_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    }
                    break;
                case 4 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1723:4: iteration_statement
                    {
                    pushFollow(FOLLOW_iteration_statement_in_statement419);
                    iteration_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    }
                    break;
                case 5 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1724:4: ^( JUMP_STATMENT_TOK ID_TOK SOURCE_TOK )
                    {
                    match(input,JUMP_STATMENT_TOK,FOLLOW_JUMP_STATMENT_TOK_in_statement426); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK12=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_statement428); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_statement430); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK12!=null?ID_TOK12.getText():null)));
                      			printer.print("// line:"+getNode((ID_TOK12!=null?ID_TOK12.getText():null)).line+"\n");
                      			if (timeMeSim.timeMeSimulation) {
                      				printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK12!=null?ID_TOK12.getText():null)).line+",\");\n");
                      			}
                      		
                    }
                    if ( state.backtracking==0 ) {

                      			if ( getNode((ID_TOK12!=null?ID_TOK12.getText():null)).type.equals("return2")) {
                      				String input = getNode((ID_TOK12!=null?ID_TOK12.getText():null)).sourceCode.replaceFirst("return","");
                      				printASMSet("PRET_RETURN_VAR_"+functionNode.getIDwPrefix()+"="+getNewStatementString(input,getNode((ID_TOK12!=null?ID_TOK12.getText():null))));
                      				codeTemp = "return "+ getNewStatementString(input,getNode((ID_TOK12!=null?ID_TOK12.getText():null)))+"\n";
                      				
                      			}else if (getNode((ID_TOK12!=null?ID_TOK12.getText():null)).type.equals("continue")) {
                      				codeTemp  = ((loop_scope)loop_stack.peek()).loop_continue_trans+" //"+getNode((ID_TOK12!=null?ID_TOK12.getText():null)).sourceCode+"\n";
                      			}else{
                      				codeTemp  = getNode((ID_TOK12!=null?ID_TOK12.getText():null)).sourceCode+"\n";
                      			}
                      			
                      			printer.print(codeTemp); 
                      		
                    }

                    }
                    break;
                case 6 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1747:4: parallel_statement
                    {
                    pushFollow(FOLLOW_parallel_statement_in_statement444);
                    parallel_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    }
                    break;
                case 7 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1748:4: ^( 'EOT' ID_TOK SOURCE_TOK )
                    {
                    match(input,112,FOLLOW_112_in_statement450); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK13=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_statement452); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_statement454); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK13!=null?ID_TOK13.getText():null)));
                      			printer.print("// line:"+getNode((ID_TOK13!=null?ID_TOK13.getText():null)).line+"\n");
                      			if (timeMeSim.timeMeSimulation) {
                      				printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK13!=null?ID_TOK13.getText():null)).line+",\");\n");
                      			}
                      		
                    }
                    if ( state.backtracking==0 ) {

                      			StatementNode s = getNode((ID_TOK13!=null?ID_TOK13.getText():null));
                      			printer.print("EOT"+s.getIDwPrefix()+"\n");
                      			printer.print("EOT_"+s.getIDwPrefix()+":;\n");
                      			printer.print("asm(\"nop\");/*asm(\"#@PRET_EOT end\");*/\n");
                      			printerTemp = printer;
                      			printer = writerPretHdr;
                      			printer.print("#define EOT"+s.getIDwPrefix()+" \\\n");
                      			printer.print("asm(\"nop\");/*asm(\"#@PRET_EOT start\");#@PRET_NL*/\\\n");
                      			printer.print("activeNode->PC = &&"+"EOT_"+s.getIDwPrefix()+";\\\n");
                      			printer.print("activeNode = activeNode->next;\\\n");
                          			printer.print("goto *(activeNode->PC);\\\n\n");	
                          		
                          		printer = printerTemp;
                      		
                    }

                    }
                    break;
                case 8 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1772:4: preemption_statment
                    {
                    pushFollow(FOLLOW_preemption_statment_in_statement469);
                    preemption_statment();

                    state._fsp--;
                    if (state.failed) return ;

                    }
                    break;
                case 9 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1773:4: scope_statement
                    {
                    pushFollow(FOLLOW_scope_statement_in_statement474);
                    scope_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    }
                    break;

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 7, statement_StartIndex); }
        }
        return ;
    }
    // $ANTLR end "statement"


    // $ANTLR start "preemption_statment"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1775:1: preemption_statment : ( ^( ABORT_TOK ^( ( 'sabort' | 'abort' ) ID_TOK SOURCE_TOK ) scope_statement ) | ^( ABORT_TOK ^( 'wabort' ID_TOK SOURCE_TOK ) scope_statement ) );
    public final void preemption_statment() throws RecognitionException {
        isFromFunction_stack.push(new isFromFunction_scope());

        int preemption_statment_StartIndex = input.index();
        CommonTree ID_TOK14=null;
        CommonTree SOURCE_TOK15=null;
        CommonTree ID_TOK16=null;
        CommonTree SOURCE_TOK17=null;


        	String condition;
        	((isFromFunction_scope)isFromFunction_stack.peek()).data = new Boolean(false);
        	((isFromFunction_scope)isFromFunction_stack.peek()).isSwitchData = new Boolean(false); 
        	((isFromFunction_scope)isFromFunction_stack.peek()).SwitchVar = "";
        	((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket ="";
        	((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket_after ="";


        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 8) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1786:2: ( ^( ABORT_TOK ^( ( 'sabort' | 'abort' ) ID_TOK SOURCE_TOK ) scope_statement ) | ^( ABORT_TOK ^( 'wabort' ID_TOK SOURCE_TOK ) scope_statement ) )
            int alt9=2;
            int LA9_0 = input.LA(1);

            if ( (LA9_0==ABORT_TOK) ) {
                int LA9_1 = input.LA(2);

                if ( (LA9_1==DOWN) ) {
                    int LA9_2 = input.LA(3);

                    if ( (synpred23_PretCTreeGrammar()) ) {
                        alt9=1;
                    }
                    else if ( (true) ) {
                        alt9=2;
                    }
                    else {
                        if (state.backtracking>0) {state.failed=true; return ;}
                        NoViableAltException nvae =
                            new NoViableAltException("", 9, 2, input);

                        throw nvae;
                    }
                }
                else {
                    if (state.backtracking>0) {state.failed=true; return ;}
                    NoViableAltException nvae =
                        new NoViableAltException("", 9, 1, input);

                    throw nvae;
                }
            }
            else {
                if (state.backtracking>0) {state.failed=true; return ;}
                NoViableAltException nvae =
                    new NoViableAltException("", 9, 0, input);

                throw nvae;
            }
            switch (alt9) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1786:4: ^( ABORT_TOK ^( ( 'sabort' | 'abort' ) ID_TOK SOURCE_TOK ) scope_statement )
                    {
                    match(input,ABORT_TOK,FOLLOW_ABORT_TOK_in_preemption_statment495); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    if ( input.LA(1)==115||input.LA(1)==117 ) {
                        input.consume();
                        state.errorRecovery=false;state.failed=false;
                    }
                    else {
                        if (state.backtracking>0) {state.failed=true; return ;}
                        MismatchedSetException mse = new MismatchedSetException(null,input);
                        throw mse;
                    }


                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK14=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_preemption_statment505); if (state.failed) return ;
                    SOURCE_TOK15=(CommonTree)match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_preemption_statment507); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK14!=null?ID_TOK14.getText():null)));
                      			printer.print("// line:"+getNode((ID_TOK14!=null?ID_TOK14.getText():null)).line+"\n");
                      			if (timeMeSim.timeMeSimulation) {
                      				printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK14!=null?ID_TOK14.getText():null)).line+",\");\n");
                      			}
                      		
                    }
                    if ( state.backtracking==0 ) {

                      			StatementNode s = getNode((ID_TOK14!=null?ID_TOK14.getText():null));
                      			condition = getNewStatementString(s.sourceCode,s);
                      			printer.print("//strong abort\n");
                      			printer.print("PRET_S_ABORT_"+s.getIDwPrefix()+"_START\n");
                      			
                      			printerTemp = printer;
                      			printer = writerPretHdr;
                      			printer.print("#define PRET_S_ABORT_"+s.getIDwPrefix()+"_START \\\n");
                      			printer.print("asm(\"nop\");/*asm(\"#@STRONG_ABORT_begin\");#@PRET_NL*/\\\n");
                      			printer.print("Node PRET_Abort_Node_ID_"+s.getIDwPrefix()+",PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			printer.print("PRET_Abort_Node_ID_"+s.getIDwPrefix()+".next=activeNode;\\\n");
                      			printer.print("PRET_Abort_Node_ID_"+s.getIDwPrefix()+".prev=activeNode->prev;\\\n");
                      			printer.print("PRET_Abort_Node_ID_"+s.getIDwPrefix()+".spawnCtr=0; /*self spwan*/ \\\n");
                      			printer.print("(activeNode->prev)->next=&PRET_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			printer.print("activeNode->prev=&PRET_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			//printer.print("activeNode->spawnCtr++;\\\n");
                      			printer.print("PRET_Abort_Node_ID_"+s.getIDwPrefix()+".parent=activeNode;\\\n");
                      			printer.print("PRET_Abort_Node_ID_"+s.getIDwPrefix()+".PC=&&PRET_ABORT_"+s.getIDwPrefix()+";\\\n");
                      /*end abort code*/

                      			printer.print("PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".next=activeNode->next;\\\n");
                      			printer.print("PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".prev=activeNode;\\\n");
                      			printer.print("PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".spawnCtr=0; /*self spwan*/ \\\n");
                      			printer.print("(activeNode->next)->prev=&PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			printer.print("activeNode->next=&PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			//printer.print("activeNode->spawnCtr++;\\\n");
                      			printer.print("PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".parent=activeNode;\\\n");
                      			printer.print("PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".PC=&&PRET_END_ABORT_"+s.getIDwPrefix()+";\\\n");
                      /*end abort code*/	
                      				
                      			printer.print("activeNode->PC = &&PRET_S_ABORT_"+s.getIDwPrefix()+"_BODY;\\\n");
                      			printer.print("activeNode = &PRET_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			printer.print("asm(\"nop\");/*asm(\"##@PRET_ABORT_"+s.ID+"\");#@PRET_NL*/\\\n");
                      			printer.print("PRET_ABORT_"+s.getIDwPrefix()+":;\\\n");
                      		
                      			
                      			if (extraConditionVar) {
                      				printer.print("char __PRET__TempVar"+s.getIDwPrefix()+"__="+condition+";\\\n");
                      				printASMVarDeclare("__PRET__TempVar"+s.getIDwPrefix()+"__","internal","char",condition, "0", "1");
                      				printer.print("if ("+"__PRET__TempVar"+s.getIDwPrefix()+"__"+") {\\\n");
                      				printASMTest("__PRET__TempVar"+s.getIDwPrefix()+"__");
                      			}else{
                      				printer.print("if ("+condition+") {\\\n");
                      				printASMTest(condition);
                      			}
                      			printer.indent++;
                      			printer.print("goto PRET_S_ABORT_"+s.getIDwPrefix()+"_KILL;\\\n");
                      			printer.indent--;
                      			printer.print("}else{\\\n");
                      			if (extraConditionVar) {
                      				printASMTest("!(__PRET__TempVar"+s.getIDwPrefix()+"__)");
                      			}else{
                      				printASMTest("!("+condition+")");
                      			}
                      			printer.print("}\\\n");
                      			printer.print("activeNode = activeNode->next;\\\n");
                      			printer.print("goto *(activeNode->PC);\\\n");
                      			printer.print("asm(\"nop\");/*asm(\"##@PRET_END_ABORT_"+s.ID+"\");#@PRET_NL*/\\\n");
                      			printer.print("PRET_END_ABORT_"+s.getIDwPrefix()+":\\\n");
                      			printer.print("activeNode = activeNode->next;\\\n");
                      			printer.print("goto *(activeNode->PC);\\\n");
                      			printer.print("asm(\"nop\");/*asm(\"##@PRET_S_ABORT_"+s.ID+"_BODY\");#@PRET_NL*/\\\n");
                      			printer.print("PRET_S_ABORT_"+s.getIDwPrefix()+"_BODY:\\\n\n");
                      			printer = printerTemp;
                      		
                    }
                    pushFollow(FOLLOW_scope_statement_in_preemption_statment520);
                    scope_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			StatementNode s = getNode((ID_TOK14!=null?ID_TOK14.getText():null));
                      			printer.print("//when "+(SOURCE_TOK15!=null?SOURCE_TOK15.getText():null)+"\n");	
                      			printer.print("PRET_S_ABORT_"+s.getIDwPrefix()+"_END\n");
                      			
                      			printerTemp = printer;
                      			printer = writerPretHdr;
                      			printer.print("#define PRET_S_ABORT_"+s.getIDwPrefix()+"_END \\\n");
                      			printer.print("PRET_S_ABORT_"+s.getIDwPrefix()+"_KILL:\\\n");
                      			printer.print("asm(\"nop\");/*asm(\"##@PRET_S_ABORT_"+s.ID+"_KILL\");#@PRET_NL*/\\\n");
                      			printer.print("activeNode=PRET_Abort_Node_ID_"+s.getIDwPrefix()+".parent;\\\n");
                      			printer.print("activeNode->next=PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".next;\\\n");		
                      			printer.print("activeNode->prev=PRET_Abort_Node_ID_"+s.getIDwPrefix()+".prev;\\\n");	
                      			printer.print("(PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".next)->prev = activeNode;\\\n");		
                      			printer.print("(PRET_Abort_Node_ID_"+s.getIDwPrefix()+".prev)->next = activeNode;\\\n");				
                      			printer.print("activeNode->spawnCtr = 0;\\\n\n");

                      			
                      			printer = printerTemp;
                      		
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1882:4: ^( ABORT_TOK ^( 'wabort' ID_TOK SOURCE_TOK ) scope_statement )
                    {
                    match(input,ABORT_TOK,FOLLOW_ABORT_TOK_in_preemption_statment531); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    match(input,118,FOLLOW_118_in_preemption_statment534); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK16=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_preemption_statment536); if (state.failed) return ;
                    SOURCE_TOK17=(CommonTree)match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_preemption_statment538); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			//error codes
                      			setErrorInfo(getNode((ID_TOK16!=null?ID_TOK16.getText():null)));
                      			printer.print("// line:"+getNode((ID_TOK16!=null?ID_TOK16.getText():null)).line+"\n");
                      			if (timeMeSim.timeMeSimulation) {
                      				printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK16!=null?ID_TOK16.getText():null)).line+",\");\n");
                      			}
                      		
                    }
                    if ( state.backtracking==0 ) {

                      			StatementNode s = getNode((ID_TOK16!=null?ID_TOK16.getText():null));
                      			condition = getNewStatementString(s.sourceCode,s);
                      			printer.print("//weak abort\n");
                      			
                      			printer.print("PRET_W_ABORT_"+s.getIDwPrefix()+"_START\n");
                      			
                      			printerTemp = printer;
                      			printer = writerPretHdr;
                      			printer.print("#define PRET_W_ABORT_"+s.getIDwPrefix()+"_START \\\n");
                      			printer.print("asm(\"nop\");/*asm(\"#@WAEK_ABORT_begin\");#@PRET_NL*/\\\n");
                      			printer.print("Node PRET_Abort_Node_ID_"+s.getIDwPrefix()+",PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			printer.print("PRET_Abort_Node_ID_"+s.getIDwPrefix()+".next=activeNode->next;\\\n");
                      			printer.print("PRET_Abort_Node_ID_"+s.getIDwPrefix()+".prev=activeNode;\\\n");
                      			printer.print("PRET_Abort_Node_ID_"+s.getIDwPrefix()+".spawnCtr=0; /*self spwan*/ \\\n");
                      			printer.print("(activeNode->next)->prev=&PRET_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			printer.print("activeNode->next=&PRET_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			//printer.print("activeNode->spawnCtr++;\\\n");
                      			printer.print("PRET_Abort_Node_ID_"+s.getIDwPrefix()+".parent=activeNode;\\\n");
                      			printer.print("PRET_Abort_Node_ID_"+s.getIDwPrefix()+".PC=&&PRET_ABORT_"+s.getIDwPrefix()+";\\\n");
                      /*end abort code*/

                      			printer.print("PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".next=activeNode;\\\n");
                      			printer.print("PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".prev=activeNode->prev;\\\n");
                      			printer.print("PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".spawnCtr=0; /*self spwan*/ \\\n");
                      			printer.print("(activeNode->prev)->next=&PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			printer.print("activeNode->prev=&PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+";\\\n");
                      			//printer.print("activeNode->spawnCtr++;\\\n");
                      			printer.print("PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".parent=activeNode;\\\n");
                      			printer.print("PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".PC=&&PRET_END_ABORT_"+s.getIDwPrefix()+";\\\n");
                      /*end abort code*/			
                      			printer.print("activeNode->PC = &&PRET_W_ABORT_"+s.getIDwPrefix()+"_BODY;\\\n");
                      			printer.print("goto *(activeNode->PC);\\\n"); /*weak abort dont check until EOT*/
                      			printer.print("asm(\"nop\");/*asm(\"##@PRET_ABORT_"+s.ID+"\");#@PRET_NL*/\\\n");
                      			printer.print("PRET_ABORT_"+s.getIDwPrefix()+":;\\\n");
                      			
                      			if (extraConditionVar) {
                      				printer.print("char __PRET__TempVar"+s.getIDwPrefix()+"__="+condition+";\\\n");
                      				printASMVarDeclare("__PRET__TempVar"+s.getIDwPrefix()+"__","internal","char",condition, "0", "1");
                      				printer.print("if ("+"__PRET__TempVar"+s.getIDwPrefix()+"__"+") {\\\n");
                      				printASMTest("__PRET__TempVar"+s.getIDwPrefix()+"__");
                      			}else{
                      				printer.print("if ("+condition+") {\\\n");
                      				printASMTest(condition);
                      			}	
                      			printer.indent++;
                      			printer.print("goto PRET_W_ABORT_"+s.getIDwPrefix()+"_KILL;\\\n");
                      			printer.indent--;
                      			printer.print("}else{\\\n");
                      			
                      			if (extraConditionVar) {
                      				printASMTest("!(__PRET__TempVar"+s.getIDwPrefix()+"__)");
                      			}else{
                      				printASMTest("!("+condition+")");
                      			}
                      			printer.print("}\\\n");
                      			printer.print("activeNode = activeNode->next;\\\n");
                      			printer.print("goto *(activeNode->PC);\\\n");
                      			printer.print("asm(\"nop\");/*asm(\"##@PRET_END_ABORT_"+s.ID+"\");#@PRET_NL*/\\\n");
                      			printer.print("PRET_END_ABORT_"+s.getIDwPrefix()+":\\\n");
                      			printer.print("activeNode = activeNode->next;\\\n");
                      			printer.print("goto *(activeNode->PC);\\\n");
                      			printer.print("asm(\"nop\");/*asm(\"##@PRET_W_ABORT_"+s.ID+"_BODY\");#@PRET_NL*/\\\n");
                      			printer.print("PRET_W_ABORT_"+s.getIDwPrefix()+"_BODY:\\\n\n");
                      			printer = printerTemp;
                      		
                    }
                    pushFollow(FOLLOW_scope_statement_in_preemption_statment551);
                    scope_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      			StatementNode s = getNode((ID_TOK16!=null?ID_TOK16.getText():null));
                      			printer.print("//when "+(SOURCE_TOK17!=null?SOURCE_TOK17.getText():null)+"\n");	
                      			printer.print("PRET_W_ABORT_"+s.getIDwPrefix()+"_END\n");
                      			
                      			printerTemp = printer;
                      			printer = writerPretHdr;
                      			printer.print("#define PRET_W_ABORT_"+s.getIDwPrefix()+"_END \\\n");
                      			printer.print("PRET_W_ABORT_"+s.getIDwPrefix()+"_KILL:\\\n");
                      			printer.print("asm(\"nop\");/*asm(\"##@PRET_W_ABORT_"+s.ID+"_KILL\");#@PRET_NL*/\\\n");
                      			printer.print("activeNode=PRET_Abort_Node_ID_"+s.getIDwPrefix()+".parent;\\\n");
                      			printer.print("activeNode->next=PRET_Abort_Node_ID_"+s.getIDwPrefix()+".next;\\\n");		
                      			printer.print("activeNode->prev=PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".prev;\\\n");	
                      			printer.print("(PRET_Abort_Node_ID_"+s.getIDwPrefix()+".next)->prev = activeNode;\\\n");		
                      			printer.print("(PRET_End_Abort_Node_ID_"+s.getIDwPrefix()+".prev)->next = activeNode;\\\n");				
                      			printer.print("activeNode->spawnCtr = 0;\\\n\n");		
                      			printer = printerTemp;
                      		
                    }

                    }
                    break;

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 8, preemption_statment_StartIndex); }
            isFromFunction_stack.pop();

        }
        return ;
    }
    // $ANTLR end "preemption_statment"


    // $ANTLR start "parallel_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1977:1: parallel_statement : ^( 'PAR' ID_TOK SOURCE_TOK ) ;
    public final void parallel_statement() throws RecognitionException {
        int parallel_statement_StartIndex = input.index();
        CommonTree ID_TOK18=null;

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 9) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1978:2: ( ^( 'PAR' ID_TOK SOURCE_TOK ) )
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1978:4: ^( 'PAR' ID_TOK SOURCE_TOK )
            {
            match(input,119,FOLLOW_119_in_parallel_statement568); if (state.failed) return ;

            match(input, Token.DOWN, null); if (state.failed) return ;
            ID_TOK18=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_parallel_statement570); if (state.failed) return ;
            match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_parallel_statement572); if (state.failed) return ;

            match(input, Token.UP, null); if (state.failed) return ;
            if ( state.backtracking==0 ) {

              			//error codes
              			setErrorInfo(getNode((ID_TOK18!=null?ID_TOK18.getText():null)));
              			printer.print("// line:"+getNode((ID_TOK18!=null?ID_TOK18.getText():null)).line+"\n");
              			if (timeMeSim.timeMeSimulation) {
              				printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK18!=null?ID_TOK18.getText():null)).line+",\");\n");
              			}
              		
            }
            if ( state.backtracking==0 ) {

              			//System.out.println("ERROR\n");
              			nodeTemp = getNode((ID_TOK18!=null?ID_TOK18.getText():null));
              			String ID = (ID_TOK18!=null?ID_TOK18.getText():null);
              			int children = nodeTemp.name.size();
              			
              			if (children > 0) {
              				//System.out.println("Fixed\n");
              				//PRET_Node_(name)_ID_(ID)
              				//String parentID = "PRET_Node_"+functionNode.name.get(0)+"_ID_"+functionNode.getIDwPrefix();
              				String parentID = "(*activeNode)";
              				String joinLabel = functionNode.name.get(0)+"_join"+ID; //this ID is PAR ID
              				printer.print("//PAR ID: "+ID+" Threads: "+nodeTemp.name+" \n");
              				/*String temp = "PAR"+ID+"("+ID+","+nodeTemp.name.size();
              				for (int i = 0 ; i < nodeTemp.name.size(); i++) {
              					temp += ",PRET_Node_"+nodeTemp.name.get(i)+"_ID_"+nodeTemp.thdInsID.get(i);
              				}
              				temp += ","+parentID;
              				temp += ","+joinLabel;
              				temp += ");\n";
              				printer.print(temp);*/
              				printer.print("PAR"+ID+"\n");
              				printerTemp = printer;
              				printer = writerPretHdr;
              				
              				/*printer.print("#define "+temp+"\\\n");//PAR3(ID,NC,C1,C2,C3,P,P_addr);\

              				printer.print("asm(\"#PAR_begin\");\\\n");
              				printer.print("asm(\"#@GroupID \" #ID );\\\n");
              				printer.print("asm(\"#@NoOfChildren \" #NC );\\\n");
              				printer.print("P.PC = P_addr;
              				printer.print("P.spawnCtr = #NC;*/
              				printer.print("#define PAR"+ID+" \\\n");
              				printer.print("asm(\"nop\");/*asm(\"#@PRET_PAR start\");*/"+"/*asm(\"#@PRET_GroupID "+ID+"\" );#@PRET_NL*/\\\n");
              				//printer.print("asm(\"#@NoOfChildren "+children+"\" );\\\n"); //no needed anymore
              				printer.print(parentID+".PC = &&"+joinLabel+";\\\n");
              				printer.print(parentID+".spawnCtr += "+children+";\\\n");
              				printer.print("/*update the next pointers of parent node*/\\\n");
              				
              				String FirstChildID = "PRET_Node_"+nodeTemp.name.get(0)+"_ID_"+nodeTemp.thdInsID.get(0);
              				printer.print(parentID+".prev->next = &"+FirstChildID+";\\\n");
              				String LastChildID = "PRET_Node_"+nodeTemp.name.get(nodeTemp.name.size()-1)+"_ID_"+nodeTemp.thdInsID.get(nodeTemp.name.size()-1);
              				printer.print(parentID+".next->prev = &"+LastChildID+";\\\n");
              				String c1 ="";
              				String c2 ="";
              				printer.print("/*update next#@PRET_NL*/\\\n");
              				
              				for (int i = 0 ; i < nodeTemp.name.size()-1; i++) {
              					c1 = "PRET_Node_"+nodeTemp.name.get(i)+"_ID_"+nodeTemp.thdInsID.get(i);
              					c2 = "PRET_Node_"+nodeTemp.name.get(i+1)+"_ID_"+nodeTemp.thdInsID.get(i+1);
              					printer.print(c1+".next=&"+c2+";\\\n");
              				}
              				printer.print(LastChildID+".next="+parentID+".next;\\\n");
              				printer.print("/*updade prev#@PRET_NL*/\\\n");
              				printer.print(FirstChildID+".prev="+parentID+".prev;\\\n");
              				for (int i = nodeTemp.name.size()-1 ; i > 0; i--) {
              					c2 = "PRET_Node_"+nodeTemp.name.get(i)+"_ID_"+nodeTemp.thdInsID.get(i);
              					c1 = "PRET_Node_"+nodeTemp.name.get(i-1)+"_ID_"+nodeTemp.thdInsID.get(i-1);
              					printer.print(c2+".prev=&"+c1+";\\\n");
              				}
              				for (int i = 0 ; i < nodeTemp.name.size(); i++) {
              					c1 = "PRET_Node_"+nodeTemp.name.get(i)+"_ID_"+nodeTemp.thdInsID.get(i);
              					printer.print(c1+".spawnCtr=0;\\\n");
              				}
              				for (int i = 0 ; i < nodeTemp.name.size(); i++) {
              					c1 = "PRET_Node_"+nodeTemp.name.get(i)+"_ID_"+nodeTemp.thdInsID.get(i);
              					//printer.print("asm(\"#@Death"+i+"address\");\\\n"); no need now
              					printer.print(c1+".deathAddr=&&"+nodeTemp.name.get(i)+"_death;\\\n");
              				}
              				for (int i = 0 ; i < nodeTemp.name.size(); i++) {
              					c1 = "PRET_Node_"+nodeTemp.name.get(i)+"_ID_"+nodeTemp.thdInsID.get(i);
              					//printer.print("asm(\"#@Parent"+i+"address\");\\\n"); no need now
              					printer.print(c1+".parent=&"+parentID+";\\\n");
              				}
              				for (int i = 0 ; i < nodeTemp.name.size(); i++) {
              					c1 = "PRET_Node_"+nodeTemp.name.get(i)+"_ID_"+nodeTemp.thdInsID.get(i);
              					printer.print("/*asm(\"#@PRET_Child"+i+" address\");#@PRET_NL*/"+c1+".PC = &&"+nodeTemp.name.get(i)+";\\\n");
              				}
              				printer.print("/*change active thread*/ \\\n");
              				printer.print("activeNode=&"+FirstChildID+";\\\n");
              				printer.print("goto *"+FirstChildID+".PC;\\\n\n");
              				
              				printer = printerTemp;
              				printer.print(joinLabel+":;\n");
              				printer.print("asm(\"nop\");/*asm(\"#@PRET_PAR end\");*/\n");
              			}else{
              				printer.print("//PAR ID: "+ID+" Threads: "+nodeTemp.name+" \n");
              			}
              		
            }

            }

        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 9, parallel_statement_StartIndex); }
        }
        return ;
    }
    // $ANTLR end "parallel_statement"


    // $ANTLR start "selection_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2076:1: selection_statement : ( ^( SELECTION_STATMENT_TOK ^( 'if' id1= ID_TOK SOURCE_TOK ) scope_statement ( ^( 'else' id2= ID_TOK SOURCE_TOK ) scope_statement )? ) | ^( SELECTION_STATMENT_TOK ^( 'switch' ID_TOK SOURCE_TOK ) scope_statement ) );
    public final void selection_statement() throws RecognitionException {
        isFromFunction_stack.push(new isFromFunction_scope());

        int selection_statement_StartIndex = input.index();
        CommonTree id1=null;
        CommonTree id2=null;
        CommonTree ID_TOK19=null;


        	((isFromFunction_scope)isFromFunction_stack.peek()).data = new Boolean(false);
        	((isFromFunction_scope)isFromFunction_stack.peek()).isSwitchData = new Boolean(false); 
        	((isFromFunction_scope)isFromFunction_stack.peek()).SwitchVar = "";
        	boolean hasElse = false;
        	StatementNode s = null;
        	String condition = "";
        	((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket_after = "";
        	((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket = "";


        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 10) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2089:2: ( ^( SELECTION_STATMENT_TOK ^( 'if' id1= ID_TOK SOURCE_TOK ) scope_statement ( ^( 'else' id2= ID_TOK SOURCE_TOK ) scope_statement )? ) | ^( SELECTION_STATMENT_TOK ^( 'switch' ID_TOK SOURCE_TOK ) scope_statement ) )
            int alt11=2;
            int LA11_0 = input.LA(1);

            if ( (LA11_0==SELECTION_STATMENT_TOK) ) {
                int LA11_1 = input.LA(2);

                if ( (LA11_1==DOWN) ) {
                    int LA11_2 = input.LA(3);

                    if ( (synpred25_PretCTreeGrammar()) ) {
                        alt11=1;
                    }
                    else if ( (true) ) {
                        alt11=2;
                    }
                    else {
                        if (state.backtracking>0) {state.failed=true; return ;}
                        NoViableAltException nvae =
                            new NoViableAltException("", 11, 2, input);

                        throw nvae;
                    }
                }
                else {
                    if (state.backtracking>0) {state.failed=true; return ;}
                    NoViableAltException nvae =
                        new NoViableAltException("", 11, 1, input);

                    throw nvae;
                }
            }
            else {
                if (state.backtracking>0) {state.failed=true; return ;}
                NoViableAltException nvae =
                    new NoViableAltException("", 11, 0, input);

                throw nvae;
            }
            switch (alt11) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2089:5: ^( SELECTION_STATMENT_TOK ^( 'if' id1= ID_TOK SOURCE_TOK ) scope_statement ( ^( 'else' id2= ID_TOK SOURCE_TOK ) scope_statement )? )
                    {
                    match(input,SELECTION_STATMENT_TOK,FOLLOW_SELECTION_STATMENT_TOK_in_selection_statement606); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    match(input,120,FOLLOW_120_in_selection_statement609); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    id1=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_selection_statement613); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_selection_statement615); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      				//error codes
                      				setErrorInfo(getNode((id1!=null?id1.getText():null)));
                      				printer.print("// line:"+getNode((id1!=null?id1.getText():null)).line + "\n");
                      				if (timeMeSim.timeMeSimulation) {
                      					printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((id1!=null?id1.getText():null)).line+",\");\n");
                      				}
                      			
                    }
                    if ( state.backtracking==0 ) {

                      				s = getNode((id1!=null?id1.getText():null));
                      				condition = getNewStatementString(s.assignmentExpression.get(0),getNode((id1!=null?id1.getText():null)));
                      				if (extraConditionVar) {
                      					printer.print("char __PRET__TempVar"+s.getIDwPrefix()+"__="+condition+";\n");
                      					printASMVarDeclare("__PRET__TempVar"+s.getIDwPrefix()+"__","internal","char",condition, "0", "1");
                      				}
                      				scopeDelayASMPrint = true;
                      				if (extraConditionVar) {
                      					printer.print("if (__PRET__TempVar"+s.getIDwPrefix()+"__)\n");
                      					printASMTest("__PRET__TempVar"+s.getIDwPrefix()+"__");
                      				}else{
                      					printer.print("if ("+condition+")\n");
                      					printASMTest(condition);
                      				}
                      				((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "goto PRET_IF_AFTER_"+s.getIDwPrefix()+";"; 
                      				
                      				//codeTemp  = getNode((id1!=null?id1.getText():null)).sourceCode+"\n";
                      				//System.out.println(getNode((id1!=null?id1.getText():null)));
                      				//printer.print(codeTemp);  
                      			
                    }
                    pushFollow(FOLLOW_scope_statement_in_selection_statement631);
                    scope_statement();

                    state._fsp--;
                    if (state.failed) return ;
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2119:19: ( ^( 'else' id2= ID_TOK SOURCE_TOK ) scope_statement )?
                    int alt10=2;
                    int LA10_0 = input.LA(1);

                    if ( (LA10_0==121) ) {
                        alt10=1;
                    }
                    switch (alt10) {
                        case 1 :
                            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2119:20: ^( 'else' id2= ID_TOK SOURCE_TOK ) scope_statement
                            {
                            match(input,121,FOLLOW_121_in_selection_statement635); if (state.failed) return ;

                            match(input, Token.DOWN, null); if (state.failed) return ;
                            id2=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_selection_statement639); if (state.failed) return ;
                            match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_selection_statement641); if (state.failed) return ;

                            match(input, Token.UP, null); if (state.failed) return ;
                            if ( state.backtracking==0 ) {

                              				//error codes
                              				setErrorInfo(getNode((id2!=null?id2.getText():null)));
                              				printer.print("// line:"+getNode((id2!=null?id2.getText():null)).line+"\n");
                              				if (timeMeSim.timeMeSimulation) {
                              					printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((id2!=null?id2.getText():null)).line+",\");\n");
                              				}
                              			
                            }
                            if ( state.backtracking==0 ) {

                              				hasElse = true;
                              				codeTemp  = getNode((id2!=null?id2.getText():null)).sourceCode+"\n";
                              				printer.print(codeTemp);
                              				scopeDelayASMPrint = true;
                              				if (extraConditionVar) {
                              					printASMTest("!(__PRET__TempVar"+s.getIDwPrefix()+"__)");
                              				}else{
                              					printASMTest("!("+condition+")");
                              				}
                              				((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket_after +="PRET_IF_AFTER_"+s.getIDwPrefix()+":;"+"asm(\"nop\");\n"; 
                              			
                            }
                            pushFollow(FOLLOW_scope_statement_in_selection_statement657);
                            scope_statement();

                            state._fsp--;
                            if (state.failed) return ;

                            }
                            break;

                    }


                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {
                      	//generate extra else for asm comment only
                      				if (hasElse == false) {
                      					codeTemp  = "else{\n";
                      					
                      					printer.print(codeTemp);
                      					printer.indent++;
                      					if (extraConditionVar) {
                      						printASMTest("!(__PRET__TempVar"+s.getIDwPrefix()+"__)");
                      					}else{
                      						printASMTest("!("+condition+")");
                      					}
                      					printer.indent--;
                      					printer.print("}\n");
                      					printer.print("PRET_IF_AFTER_"+s.getIDwPrefix()+":;\n"); 
                      					printer.print("asm(\"nop\");\n"); 
                      				}
                      				
                      			
                    }

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2159:5: ^( SELECTION_STATMENT_TOK ^( 'switch' ID_TOK SOURCE_TOK ) scope_statement )
                    {
                    match(input,SELECTION_STATMENT_TOK,FOLLOW_SELECTION_STATMENT_TOK_in_selection_statement672); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    match(input,122,FOLLOW_122_in_selection_statement675); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK19=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_selection_statement677); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_selection_statement679); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      				//error codes
                      				setErrorInfo(getNode((ID_TOK19!=null?ID_TOK19.getText():null)));
                      				printer.print("// line:"+getNode((ID_TOK19!=null?ID_TOK19.getText():null)).line+"\n");
                      				if (timeMeSim.timeMeSimulation) {
                      					printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK19!=null?ID_TOK19.getText():null)).line+",\");\n");
                      				}
                      			
                    }
                    if ( state.backtracking==0 ) {

                      				s = getNode((ID_TOK19!=null?ID_TOK19.getText():null));
                      				condition = getNewStatementString(s.assignmentExpression.get(0),getNode((ID_TOK19!=null?ID_TOK19.getText():null)));
                      				if (extraConditionVar) {
                      					printer.print("int __PRET__TempVar"+s.getIDwPrefix()+"__="+condition+";\n");
                      					printASMVarDeclare("__PRET__TempVar"+s.getIDwPrefix()+"__","internal","int",condition, "null", "null");
                      					printer.print("switch (__PRET__TempVar"+s.getIDwPrefix()+"__)\n");
                      				}else{
                      					printer.print("switch ("+condition+")\n");
                      				}
                      				//System.out.println(s);
                      				//codeTemp  = getNode((ID_TOK19!=null?ID_TOK19.getText():null)).sourceCode+"\n";
                      				//printer.print(codeTemp);
                      				((isFromFunction_scope)isFromFunction_stack.peek()).isSwitchData = new Boolean(true); 
                      				if (extraConditionVar) {
                      					((isFromFunction_scope)isFromFunction_stack.peek()).SwitchVar = "__PRET__TempVar"+s.getIDwPrefix()+"__";
                      				}else{
                      					((isFromFunction_scope)isFromFunction_stack.peek()).SwitchVar = "("+condition+")";
                      				}
                      				((isFromFunction_scope)isFromFunction_stack.peek()).SwitchDefaultCondition = "";
                      			
                    }
                    pushFollow(FOLLOW_scope_statement_in_selection_statement695);
                    scope_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      				((isFromFunction_scope)isFromFunction_stack.peek()).isSwitchData = new Boolean(false); 
                      				((isFromFunction_scope)isFromFunction_stack.peek()).SwitchVar = "";
                      				((isFromFunction_scope)isFromFunction_stack.peek()).SwitchDefaultCondition = "";
                      				
                      			
                    }

                    }
                    break;

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 10, selection_statement_StartIndex); }
            isFromFunction_stack.pop();

        }
        return ;
    }
    // $ANTLR end "selection_statement"


    // $ANTLR start "iteration_statement"
    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2198:1: iteration_statement : ( ^( ITERATION_STATEMENT_TOK ^( 'while' ID_TOK SOURCE_TOK ) scope_statement ) | ^( ITERATION_STATEMENT_TOK ^( 'do' 'while' ID_TOK SOURCE_TOK ) scope_statement ) | ^( ITERATION_STATEMENT_TOK ^( 'for' ID_TOK SOURCE_TOK ) scope_statement ) );
    public final void iteration_statement() throws RecognitionException {
        isFromFunction_stack.push(new isFromFunction_scope());
        loop_stack.push(new loop_scope());

        int iteration_statement_StartIndex = input.index();
        CommonTree ID_TOK20=null;
        CommonTree ID_TOK21=null;
        CommonTree ID_TOK22=null;


        	((isFromFunction_scope)isFromFunction_stack.peek()).data = new Boolean(false);
        	((isFromFunction_scope)isFromFunction_stack.peek()).isSwitchData = new Boolean(false); 
        	((isFromFunction_scope)isFromFunction_stack.peek()).SwitchVar = "";
        	((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket ="";
        	((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket_after ="";
        	((loop_scope)loop_stack.peek()).loop_continue_trans ="";
        	String condition = "";
        	String conditionPRETVar = "";

        try {
            if ( state.backtracking>0 && alreadyParsedRule(input, 11) ) { return ; }
            // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2215:2: ( ^( ITERATION_STATEMENT_TOK ^( 'while' ID_TOK SOURCE_TOK ) scope_statement ) | ^( ITERATION_STATEMENT_TOK ^( 'do' 'while' ID_TOK SOURCE_TOK ) scope_statement ) | ^( ITERATION_STATEMENT_TOK ^( 'for' ID_TOK SOURCE_TOK ) scope_statement ) )
            int alt12=3;
            int LA12_0 = input.LA(1);

            if ( (LA12_0==ITERATION_STATEMENT_TOK) ) {
                int LA12_1 = input.LA(2);

                if ( (LA12_1==DOWN) ) {
                    int LA12_2 = input.LA(3);

                    if ( (synpred26_PretCTreeGrammar()) ) {
                        alt12=1;
                    }
                    else if ( (synpred27_PretCTreeGrammar()) ) {
                        alt12=2;
                    }
                    else if ( (true) ) {
                        alt12=3;
                    }
                    else {
                        if (state.backtracking>0) {state.failed=true; return ;}
                        NoViableAltException nvae =
                            new NoViableAltException("", 12, 2, input);

                        throw nvae;
                    }
                }
                else {
                    if (state.backtracking>0) {state.failed=true; return ;}
                    NoViableAltException nvae =
                        new NoViableAltException("", 12, 1, input);

                    throw nvae;
                }
            }
            else {
                if (state.backtracking>0) {state.failed=true; return ;}
                NoViableAltException nvae =
                    new NoViableAltException("", 12, 0, input);

                throw nvae;
            }
            switch (alt12) {
                case 1 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2215:4: ^( ITERATION_STATEMENT_TOK ^( 'while' ID_TOK SOURCE_TOK ) scope_statement )
                    {
                    match(input,ITERATION_STATEMENT_TOK,FOLLOW_ITERATION_STATEMENT_TOK_in_iteration_statement732); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    match(input,123,FOLLOW_123_in_iteration_statement735); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK20=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_iteration_statement738); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_iteration_statement740); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      				//error codes
                      				setErrorInfo(getNode((ID_TOK20!=null?ID_TOK20.getText():null)));
                      				printer.print("// line:"+getNode((ID_TOK20!=null?ID_TOK20.getText():null)).line+"\n");
                      				if (timeMeSim.timeMeSimulation) {
                      					printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK20!=null?ID_TOK20.getText():null)).line+",\");\n");
                      				}
                      			
                    }
                    if ( state.backtracking==0 ) {

                      				StatementNode s = getNode((ID_TOK20!=null?ID_TOK20.getText():null));
                      				condition = getNewStatementString(s.assignmentExpression.get(0),getNode((ID_TOK20!=null?ID_TOK20.getText():null)));
                      				if (extraConditionVar) {
                      					printer.print("char __PRET__TempVar"+s.getIDwPrefix()+"__="+condition+";\n");
                      					conditionPRETVar = "__PRET__TempVar"+s.getIDwPrefix()+"__";
                      					printASMVarDeclare("__PRET__TempVar"+s.getIDwPrefix()+"__","internal","char",condition, "0", "1");
                      				}else{
                      					conditionPRETVar = condition;
                      				}
                      				scopeDelayASMPrint = true;
                      				
                      				if (s.loopBound.length() > 0) {
                      					printer.print("//code to enforce bounds no need tracking\n");
                      					printer.print("char __PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__="+0+";\n");
                      				}
                      				((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "PRET_END_OF_LOOP_"+s.getIDwPrefix()+":;";
                      				((loop_scope)loop_stack.peek()).loop_continue_trans ="goto PRET_END_OF_LOOP_"+s.getIDwPrefix()+";";
                      				if (extraConditionVar) {
                      					printer.print("while (__PRET__TempVar"+s.getIDwPrefix()+"__)\n");
                      					printASMTest("__PRET__TempVar"+s.getIDwPrefix()+"__");
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "__PRET__TempVar"+s.getIDwPrefix()+"__="+condition+";";
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += printASMSetRet("__PRET__TempVar"+s.getIDwPrefix()+"__="+condition+";");
                      				}else{
                      					printer.print("while ("+condition+")\n");
                      					printASMTest(condition);
                      				}

                      				if (s.loopBound.length() > 0) {
                      					//printer.print("//code to enforce bounds no need tracking");
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "__PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__++;";
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "if (__PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__=="+s.loopBound+"){break;}"; 
                      				}
                      				if (s.loopBound.length() > 0) {
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket +="asm(\"nop\");/*asm(\"#@PRET_Bound "+s.loopBound+ "\");*/\n";
                      				}
                      				//codeTemp  = getNode((ID_TOK20!=null?ID_TOK20.getText():null)).sourceCode+"\n";
                      				//printer.print(codeTemp);
                      				((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "/*asm(\"nop\");*/ //force asm comment to stay put\n";
                      			
                    }

                    match(input, Token.UP, null); if (state.failed) return ;
                    pushFollow(FOLLOW_scope_statement_in_iteration_statement756);
                    scope_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;

                    }
                    break;
                case 2 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2265:4: ^( ITERATION_STATEMENT_TOK ^( 'do' 'while' ID_TOK SOURCE_TOK ) scope_statement )
                    {
                    match(input,ITERATION_STATEMENT_TOK,FOLLOW_ITERATION_STATEMENT_TOK_in_iteration_statement763); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    match(input,124,FOLLOW_124_in_iteration_statement766); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    match(input,123,FOLLOW_123_in_iteration_statement768); if (state.failed) return ;
                    ID_TOK21=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_iteration_statement770); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      				StatementNode s = getNode((ID_TOK21!=null?ID_TOK21.getText():null));
                      				condition = getNewStatementString(s.assignmentExpression.get(0),getNode((ID_TOK21!=null?ID_TOK21.getText():null)));
                      				if (extraConditionVar) {
                      					printer.print("char __PRET__TempVar"+s.getIDwPrefix()+"__="+condition+";\n");
                      					conditionPRETVar = "__PRET__TempVar"+s.getIDwPrefix()+"__";
                      					printASMVarDeclare("__PRET__TempVar"+s.getIDwPrefix()+"__","internal","char",condition, "0", "1");
                      				}else{
                      					conditionPRETVar = condition;
                      				}
                      				if (s.loopBound.length() > 0) {
                      					printer.print("//code to enforce bounds no need tracking\n");
                      					printer.print("char __PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__="+0+";\n");
                      				}
                      				printer.print("do\n");
                      				((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "PRET_END_OF_LOOP_"+s.getIDwPrefix()+":;";
                      				((loop_scope)loop_stack.peek()).loop_continue_trans ="goto PRET_END_OF_LOOP_"+s.getIDwPrefix()+";";
                      				if (extraConditionVar) {
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "__PRET__TempVar"+s.getIDwPrefix()+"__="+condition+";";
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += printASMSetRet("__PRET__TempVar"+s.getIDwPrefix()+"__="+condition+";");
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += printASMTestRet("__PRET__TempVar"+s.getIDwPrefix()+"__");
                      				}else{
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += printASMTestRet(condition);
                      				}
                      				if (s.loopBound.length() > 0) {
                      					//printer.print("//code to enforce bounds no need tracking");
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "__PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__++;";
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "if (__PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__=="+s.loopBound+"){break;}"; 
                      				}
                      				if (s.loopBound.length() > 0) {
                      					((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket +="asm(\"nop\");/*asm(\"#@PRET_Bound "+s.loopBound+ "\");*/\n";
                      				}
                      				((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "/*asm(\"nop\"); *///force asm comment to stay put\n";
                      			
                    }
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_iteration_statement786); if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;
                    pushFollow(FOLLOW_scope_statement_in_iteration_statement789);
                    scope_statement();

                    state._fsp--;
                    if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      				//error codes
                      				setErrorInfo(getNode((ID_TOK21!=null?ID_TOK21.getText():null)));
                      				printer.print("// line:"+getNode((ID_TOK21!=null?ID_TOK21.getText():null)).line+"\n");
                      				if (timeMeSim.timeMeSimulation) {
                      					printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK21!=null?ID_TOK21.getText():null)).line+",\");\n");
                      				}
                      			
                    }
                    if ( state.backtracking==0 ) {

                      				StatementNode s = getNode((ID_TOK21!=null?ID_TOK21.getText():null));
                      				//printer.print("char __PRET__TempVar"+s.getIDwPrefix()+"__="+getNewStatementString(s.assignmentExpression.get(0),getNode((ID_TOK21!=null?ID_TOK21.getText():null)))+";\n");
                      				if (extraConditionVar) {
                      					printer.print("while (__PRET__TempVar"+s.getIDwPrefix()+"__);\n");
                      				}else{
                      					printer.print("while ("+conditionPRETVar+");\n");
                      				}
                      				//codeTemp  = getNode((ID_TOK21!=null?ID_TOK21.getText():null)).sourceCode+"\n";
                      				//printer.print(codeTemp);
                      			
                    }

                    match(input, Token.UP, null); if (state.failed) return ;

                    }
                    break;
                case 3 :
                    // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2323:4: ^( ITERATION_STATEMENT_TOK ^( 'for' ID_TOK SOURCE_TOK ) scope_statement )
                    {
                    match(input,ITERATION_STATEMENT_TOK,FOLLOW_ITERATION_STATEMENT_TOK_in_iteration_statement811); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    match(input,125,FOLLOW_125_in_iteration_statement814); if (state.failed) return ;

                    match(input, Token.DOWN, null); if (state.failed) return ;
                    ID_TOK22=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_iteration_statement816); if (state.failed) return ;
                    match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_iteration_statement818); if (state.failed) return ;
                    if ( state.backtracking==0 ) {

                      				//error codes
                      				setErrorInfo(getNode((ID_TOK22!=null?ID_TOK22.getText():null)));
                      				printer.print("// line:"+getNode((ID_TOK22!=null?ID_TOK22.getText():null)).line+"\n");
                      				if (timeMeSim.timeMeSimulation) {
                      					printer.print(""+projectPrefix+"_lineCountPrt = strcat( "+projectPrefix+"_lineCountPrt, \""+getNode((ID_TOK22!=null?ID_TOK22.getText():null)).line+",\");\n");
                      				}
                      			
                    }
                    if ( state.backtracking==0 ) {

                      				StatementNode s = getNode((ID_TOK22!=null?ID_TOK22.getText():null));
                      				String assignmentExpression1 = getNewStatementString(s.assignmentExpression.get(0),getNode((ID_TOK22!=null?ID_TOK22.getText():null)));
                      				String assignmentExpression2 = getNewStatementString(s.assignmentExpression.get(1),getNode((ID_TOK22!=null?ID_TOK22.getText():null)));
                      				String assignmentExpression3 = getNewStatementString(s.assignmentExpression.get(2),getNode((ID_TOK22!=null?ID_TOK22.getText():null)));
                      				String declare1 = "";
                      				String var = "";
                      				((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "PRET_END_OF_LOOP_"+s.getIDwPrefix()+":;";
                      				((loop_scope)loop_stack.peek()).loop_continue_trans ="goto PRET_END_OF_LOOP_"+s.getIDwPrefix()+";";
                      				if (extraConditionVar) {
                      					conditionPRETVar = "__PRET__TempVar"+s.getIDwPrefix()+"__";
                      					if (assignmentExpression1.equals("") == false) {
                      						printer.print(assignmentExpression1+";\n");
                      						printASMSet(assignmentExpression1);
                      					}
                      					//increment then condition
                      					
                      					if (assignmentExpression3.equals("") == false) {
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += assignmentExpression3+";";
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += printASMSetRet(assignmentExpression3);
                      					}
                      	
                      					if (assignmentExpression2.equals("") == false) {
                      						
                      						var = "__PRET__TempVar"+s.getIDwPrefix()+"__";
                      						printASMVarDeclare(var,"internal","char",assignmentExpression2, "0", "1");
                      						condition = assignmentExpression2;
                      						declare1 = "char "+var;
                      						printer.print(declare1+"="+assignmentExpression2+";\n");
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += var+"="+assignmentExpression2+";"; //condition
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += printASMSetRet(var+"="+assignmentExpression2+";");
                      					}else{
                      						var = "__PRET__TempVar"+s.getIDwPrefix()+"__";
                      						printASMVarDeclare(var,"internal","char",assignmentExpression2, "0", "1");
                      						declare1 = "char "+var;
                      						printer.print(declare1+"="+1+";\n");
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += var+"="+1+";"; //if no condition it always true
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += printASMSetRet("__PRET__TempVar"+s.getIDwPrefix()+"__="+1+";");
                      					}
                      					if (s.loopBound.length() > 0) {
                      						printer.print("//code to enforce bounds no need tracking\n");
                      						printer.print("char __PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__="+0+";\n");
                      					}
                      					if (s.loopBound.length() > 0) {
                      						//printer.print("//code to enforce bounds no need tracking");
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "__PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__++;";
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "if (__PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__=="+s.loopBound+"){break;}"; 
                      					}
                      					printer.print("while("+var+")\n");
                      					if (s.loopBound.length() > 0) {
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket +="asm(\"nop\");/*asm(\"#@PRET_Bound "+s.loopBound+ "\");*/\n";
                      					}
                      				}else{
                      					conditionPRETVar = assignmentExpression2;
                      					if (assignmentExpression1.equals("") == false) {
                      						printer.print(assignmentExpression1+";\n");
                      						printASMSet(assignmentExpression1);
                      					}
                      					if (assignmentExpression3.equals("") == false) {
                      						//scope_statement_arugment_end_barcket += assignmentExpression3+";";
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += printASMSetRet(assignmentExpression3);
                      					}
                      					if (assignmentExpression2.equals("") == false) {
                      						var = assignmentExpression2;
                      					}else{
                      						conditionPRETVar = "1";
                      						var = "1";
                      					}
                      					if (s.loopBound.length() > 0) {
                      						printer.print("//code to enforce bounds no need tracking\n");
                      						printer.print("char __PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__="+0+";\n");
                      					}
                      					if (s.loopBound.length() > 0) {
                      						//printer.print("//code to enforce bounds no need tracking");
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "__PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__++;";
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "if (__PRET__TempVarBoundLimiter"+s.getIDwPrefix()+"__=="+s.loopBound+"){break;}"; 
                      					}
                      					printer.print("for("+assignmentExpression1+";"+assignmentExpression2+";"+assignmentExpression3+")\n");
                      					if (s.loopBound.length() > 0) {
                      						((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket +="asm(\"nop\");/*asm(\"#@PRET_Bound "+s.loopBound+ "\");*/\n";
                      					}
                      				}
                      				scopeDelayASMPrint = true;
                      				printASMTest(var);		
                      				/*printer.print("for("+declare1+";"+declare2+";"+declare3+")\n");*/
                      				((isFromFunction_scope)isFromFunction_stack.peek()).scope_statement_arugment_end_barcket += "asm(\"nop\"); //force asm comment to stay put\n";
                      				//System.out.println(getNode((ID_TOK22!=null?ID_TOK22.getText():null)));
                      				//codeTemp  = getNode((ID_TOK22!=null?ID_TOK22.getText():null)).sourceCode+"\n";
                      				//printer.print(codeTemp);
                      			
                    }

                    match(input, Token.UP, null); if (state.failed) return ;
                    pushFollow(FOLLOW_scope_statement_in_iteration_statement836);
                    scope_statement();

                    state._fsp--;
                    if (state.failed) return ;

                    match(input, Token.UP, null); if (state.failed) return ;

                    }
                    break;

            }
            if ( state.backtracking==0 ) {

              	
              	printASMTest("!("+conditionPRETVar+")");

            }
        }
        catch (RecognitionException re) {
            reportError(re);
            recover(input,re);
        }
        finally {
            if ( state.backtracking>0 ) { memoize(input, 11, iteration_statement_StartIndex); }
            isFromFunction_stack.pop();
            loop_stack.pop();

        }
        return ;
    }
    // $ANTLR end "iteration_statement"

    // $ANTLR start synpred13_PretCTreeGrammar
    public final void synpred13_PretCTreeGrammar_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1670:4: ( statement )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1670:4: statement
        {
        pushFollow(FOLLOW_statement_in_synpred13_PretCTreeGrammar353);
        statement();

        state._fsp--;
        if (state.failed) return ;

        }
    }
    // $ANTLR end synpred13_PretCTreeGrammar

    // $ANTLR start synpred23_PretCTreeGrammar
    public final void synpred23_PretCTreeGrammar_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1786:4: ( ^( ABORT_TOK ^( ( 'sabort' | 'abort' ) ID_TOK SOURCE_TOK ) scope_statement ) )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:1786:4: ^( ABORT_TOK ^( ( 'sabort' | 'abort' ) ID_TOK SOURCE_TOK ) scope_statement )
        {
        match(input,ABORT_TOK,FOLLOW_ABORT_TOK_in_synpred23_PretCTreeGrammar495); if (state.failed) return ;

        match(input, Token.DOWN, null); if (state.failed) return ;
        if ( input.LA(1)==115||input.LA(1)==117 ) {
            input.consume();
            state.errorRecovery=false;state.failed=false;
        }
        else {
            if (state.backtracking>0) {state.failed=true; return ;}
            MismatchedSetException mse = new MismatchedSetException(null,input);
            throw mse;
        }


        match(input, Token.DOWN, null); if (state.failed) return ;
        match(input,ID_TOK,FOLLOW_ID_TOK_in_synpred23_PretCTreeGrammar505); if (state.failed) return ;
        match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_synpred23_PretCTreeGrammar507); if (state.failed) return ;

        match(input, Token.UP, null); if (state.failed) return ;
        pushFollow(FOLLOW_scope_statement_in_synpred23_PretCTreeGrammar520);
        scope_statement();

        state._fsp--;
        if (state.failed) return ;

        match(input, Token.UP, null); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred23_PretCTreeGrammar

    // $ANTLR start synpred25_PretCTreeGrammar
    public final void synpred25_PretCTreeGrammar_fragment() throws RecognitionException {   
        CommonTree id1=null;
        CommonTree id2=null;

        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2089:5: ( ^( SELECTION_STATMENT_TOK ^( 'if' id1= ID_TOK SOURCE_TOK ) scope_statement ( ^( 'else' id2= ID_TOK SOURCE_TOK ) scope_statement )? ) )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2089:5: ^( SELECTION_STATMENT_TOK ^( 'if' id1= ID_TOK SOURCE_TOK ) scope_statement ( ^( 'else' id2= ID_TOK SOURCE_TOK ) scope_statement )? )
        {
        match(input,SELECTION_STATMENT_TOK,FOLLOW_SELECTION_STATMENT_TOK_in_synpred25_PretCTreeGrammar606); if (state.failed) return ;

        match(input, Token.DOWN, null); if (state.failed) return ;
        match(input,120,FOLLOW_120_in_synpred25_PretCTreeGrammar609); if (state.failed) return ;

        match(input, Token.DOWN, null); if (state.failed) return ;
        id1=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_synpred25_PretCTreeGrammar613); if (state.failed) return ;
        match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_synpred25_PretCTreeGrammar615); if (state.failed) return ;

        match(input, Token.UP, null); if (state.failed) return ;
        pushFollow(FOLLOW_scope_statement_in_synpred25_PretCTreeGrammar631);
        scope_statement();

        state._fsp--;
        if (state.failed) return ;
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2119:19: ( ^( 'else' id2= ID_TOK SOURCE_TOK ) scope_statement )?
        int alt14=2;
        int LA14_0 = input.LA(1);

        if ( (LA14_0==121) ) {
            alt14=1;
        }
        switch (alt14) {
            case 1 :
                // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2119:20: ^( 'else' id2= ID_TOK SOURCE_TOK ) scope_statement
                {
                match(input,121,FOLLOW_121_in_synpred25_PretCTreeGrammar635); if (state.failed) return ;

                match(input, Token.DOWN, null); if (state.failed) return ;
                id2=(CommonTree)match(input,ID_TOK,FOLLOW_ID_TOK_in_synpred25_PretCTreeGrammar639); if (state.failed) return ;
                match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_synpred25_PretCTreeGrammar641); if (state.failed) return ;

                match(input, Token.UP, null); if (state.failed) return ;
                pushFollow(FOLLOW_scope_statement_in_synpred25_PretCTreeGrammar657);
                scope_statement();

                state._fsp--;
                if (state.failed) return ;

                }
                break;

        }


        match(input, Token.UP, null); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred25_PretCTreeGrammar

    // $ANTLR start synpred26_PretCTreeGrammar
    public final void synpred26_PretCTreeGrammar_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2215:4: ( ^( ITERATION_STATEMENT_TOK ^( 'while' ID_TOK SOURCE_TOK ) scope_statement ) )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2215:4: ^( ITERATION_STATEMENT_TOK ^( 'while' ID_TOK SOURCE_TOK ) scope_statement )
        {
        match(input,ITERATION_STATEMENT_TOK,FOLLOW_ITERATION_STATEMENT_TOK_in_synpred26_PretCTreeGrammar732); if (state.failed) return ;

        match(input, Token.DOWN, null); if (state.failed) return ;
        match(input,123,FOLLOW_123_in_synpred26_PretCTreeGrammar735); if (state.failed) return ;

        match(input, Token.DOWN, null); if (state.failed) return ;
        match(input,ID_TOK,FOLLOW_ID_TOK_in_synpred26_PretCTreeGrammar738); if (state.failed) return ;
        match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_synpred26_PretCTreeGrammar740); if (state.failed) return ;

        match(input, Token.UP, null); if (state.failed) return ;
        pushFollow(FOLLOW_scope_statement_in_synpred26_PretCTreeGrammar756);
        scope_statement();

        state._fsp--;
        if (state.failed) return ;

        match(input, Token.UP, null); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred26_PretCTreeGrammar

    // $ANTLR start synpred27_PretCTreeGrammar
    public final void synpred27_PretCTreeGrammar_fragment() throws RecognitionException {   
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2265:4: ( ^( ITERATION_STATEMENT_TOK ^( 'do' 'while' ID_TOK SOURCE_TOK ) scope_statement ) )
        // C:\\Dropbox\\my projects\\PRET-C\\PRET C Compilier\\PretCTreeGrammar.g:2265:4: ^( ITERATION_STATEMENT_TOK ^( 'do' 'while' ID_TOK SOURCE_TOK ) scope_statement )
        {
        match(input,ITERATION_STATEMENT_TOK,FOLLOW_ITERATION_STATEMENT_TOK_in_synpred27_PretCTreeGrammar763); if (state.failed) return ;

        match(input, Token.DOWN, null); if (state.failed) return ;
        match(input,124,FOLLOW_124_in_synpred27_PretCTreeGrammar766); if (state.failed) return ;

        match(input, Token.DOWN, null); if (state.failed) return ;
        match(input,123,FOLLOW_123_in_synpred27_PretCTreeGrammar768); if (state.failed) return ;
        match(input,ID_TOK,FOLLOW_ID_TOK_in_synpred27_PretCTreeGrammar770); if (state.failed) return ;
        match(input,SOURCE_TOK,FOLLOW_SOURCE_TOK_in_synpred27_PretCTreeGrammar786); if (state.failed) return ;

        match(input, Token.UP, null); if (state.failed) return ;
        pushFollow(FOLLOW_scope_statement_in_synpred27_PretCTreeGrammar789);
        scope_statement();

        state._fsp--;
        if (state.failed) return ;

        match(input, Token.UP, null); if (state.failed) return ;

        }
    }
    // $ANTLR end synpred27_PretCTreeGrammar

    // Delegated rules

    public final boolean synpred23_PretCTreeGrammar() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred23_PretCTreeGrammar_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred13_PretCTreeGrammar() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred13_PretCTreeGrammar_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred25_PretCTreeGrammar() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred25_PretCTreeGrammar_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred26_PretCTreeGrammar() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred26_PretCTreeGrammar_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }
    public final boolean synpred27_PretCTreeGrammar() {
        state.backtracking++;
        int start = input.mark();
        try {
            synpred27_PretCTreeGrammar_fragment(); // can never throw exception
        } catch (RecognitionException re) {
            System.err.println("impossible: "+re);
        }
        boolean success = !state.failed;
        input.rewind(start);
        state.backtracking--;
        state.failed=false;
        return success;
    }


    protected DFA5 dfa5 = new DFA5(this);
    protected DFA6 dfa6 = new DFA6(this);
    protected DFA7 dfa7 = new DFA7(this);
    protected DFA8 dfa8 = new DFA8(this);
    static final String DFA5_eotS =
        "\17\uffff";
    static final String DFA5_eofS =
        "\17\uffff";
    static final String DFA5_minS =
        "\1\10\16\uffff";
    static final String DFA5_maxS =
        "\1\167\16\uffff";
    static final String DFA5_acceptS =
        "\1\uffff\1\1\14\uffff\1\2";
    static final String DFA5_specialS =
        "\17\uffff}>";
    static final String[] DFA5_transitionS = {
            "\10\1\1\16\3\1\134\uffff\1\1\6\uffff\1\1",
            "",
            "",
            "",
            "",
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
            return "1662:5: ( compound_statement | EMPTY_TOK )";
        }
    }
    static final String DFA6_eotS =
        "\17\uffff";
    static final String DFA6_eofS =
        "\1\1\16\uffff";
    static final String DFA6_minS =
        "\1\10\16\uffff";
    static final String DFA6_maxS =
        "\1\167\16\uffff";
    static final String DFA6_acceptS =
        "\1\uffff\1\3\1\uffff\1\1\2\uffff\1\2\10\uffff";
    static final String DFA6_specialS =
        "\17\uffff}>";
    static final String[] DFA6_transitionS = {
            "\2\3\6\6\1\uffff\1\1\1\6\1\3\134\uffff\1\6\6\uffff\1\6",
            "",
            "",
            "",
            "",
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

    static final short[] DFA6_eot = DFA.unpackEncodedString(DFA6_eotS);
    static final short[] DFA6_eof = DFA.unpackEncodedString(DFA6_eofS);
    static final char[] DFA6_min = DFA.unpackEncodedStringToUnsignedChars(DFA6_minS);
    static final char[] DFA6_max = DFA.unpackEncodedStringToUnsignedChars(DFA6_maxS);
    static final short[] DFA6_accept = DFA.unpackEncodedString(DFA6_acceptS);
    static final short[] DFA6_special = DFA.unpackEncodedString(DFA6_specialS);
    static final short[][] DFA6_transition;

    static {
        int numStates = DFA6_transitionS.length;
        DFA6_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA6_transition[i] = DFA.unpackEncodedString(DFA6_transitionS[i]);
        }
    }

    class DFA6 extends DFA {

        public DFA6(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 6;
            this.eot = DFA6_eot;
            this.eof = DFA6_eof;
            this.min = DFA6_min;
            this.max = DFA6_max;
            this.accept = DFA6_accept;
            this.special = DFA6_special;
            this.transition = DFA6_transition;
        }
        public String getDescription() {
            return "()* loopback of 1666:4: ( declaration | statement_list )*";
        }
    }
    static final String DFA7_eotS =
        "\31\uffff";
    static final String DFA7_eofS =
        "\1\1\30\uffff";
    static final String DFA7_minS =
        "\1\10\5\uffff\11\0\12\uffff";
    static final String DFA7_maxS =
        "\1\167\5\uffff\11\0\12\uffff";
    static final String DFA7_acceptS =
        "\1\uffff\1\2\16\uffff\1\1\10\uffff";
    static final String DFA7_specialS =
        "\6\uffff\1\0\1\1\1\2\1\3\1\4\1\5\1\6\1\7\1\10\12\uffff}>";
    static final String[] DFA7_transitionS = {
            "\2\1\1\6\1\7\1\10\1\11\1\12\1\16\1\uffff\1\1\1\15\1\1\134\uffff"+
            "\1\14\6\uffff\1\13",
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
            return "()+ loopback of 1670:4: ( statement )+";
        }
        public int specialStateTransition(int s, IntStream _input) throws NoViableAltException {
            TreeNodeStream input = (TreeNodeStream)_input;
        	int _s = s;
            switch ( s ) {
                    case 0 : 
                        int LA7_6 = input.LA(1);

                         
                        int index7_6 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred13_PretCTreeGrammar()) ) {s = 16;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index7_6);
                        if ( s>=0 ) return s;
                        break;
                    case 1 : 
                        int LA7_7 = input.LA(1);

                         
                        int index7_7 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred13_PretCTreeGrammar()) ) {s = 16;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index7_7);
                        if ( s>=0 ) return s;
                        break;
                    case 2 : 
                        int LA7_8 = input.LA(1);

                         
                        int index7_8 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred13_PretCTreeGrammar()) ) {s = 16;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index7_8);
                        if ( s>=0 ) return s;
                        break;
                    case 3 : 
                        int LA7_9 = input.LA(1);

                         
                        int index7_9 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred13_PretCTreeGrammar()) ) {s = 16;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index7_9);
                        if ( s>=0 ) return s;
                        break;
                    case 4 : 
                        int LA7_10 = input.LA(1);

                         
                        int index7_10 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred13_PretCTreeGrammar()) ) {s = 16;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index7_10);
                        if ( s>=0 ) return s;
                        break;
                    case 5 : 
                        int LA7_11 = input.LA(1);

                         
                        int index7_11 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred13_PretCTreeGrammar()) ) {s = 16;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index7_11);
                        if ( s>=0 ) return s;
                        break;
                    case 6 : 
                        int LA7_12 = input.LA(1);

                         
                        int index7_12 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred13_PretCTreeGrammar()) ) {s = 16;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index7_12);
                        if ( s>=0 ) return s;
                        break;
                    case 7 : 
                        int LA7_13 = input.LA(1);

                         
                        int index7_13 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred13_PretCTreeGrammar()) ) {s = 16;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index7_13);
                        if ( s>=0 ) return s;
                        break;
                    case 8 : 
                        int LA7_14 = input.LA(1);

                         
                        int index7_14 = input.index();
                        input.rewind();
                        s = -1;
                        if ( (synpred13_PretCTreeGrammar()) ) {s = 16;}

                        else if ( (true) ) {s = 1;}

                         
                        input.seek(index7_14);
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
    static final String DFA8_eotS =
        "\12\uffff";
    static final String DFA8_eofS =
        "\12\uffff";
    static final String DFA8_minS =
        "\1\12\11\uffff";
    static final String DFA8_maxS =
        "\1\167\11\uffff";
    static final String DFA8_acceptS =
        "\1\uffff\1\1\1\2\1\3\1\4\1\5\1\6\1\7\1\10\1\11";
    static final String DFA8_specialS =
        "\12\uffff}>";
    static final String[] DFA8_transitionS = {
            "\1\1\1\2\1\3\1\4\1\5\1\11\2\uffff\1\10\135\uffff\1\7\6\uffff"+
            "\1\6",
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

    static final short[] DFA8_eot = DFA.unpackEncodedString(DFA8_eotS);
    static final short[] DFA8_eof = DFA.unpackEncodedString(DFA8_eofS);
    static final char[] DFA8_min = DFA.unpackEncodedStringToUnsignedChars(DFA8_minS);
    static final char[] DFA8_max = DFA.unpackEncodedStringToUnsignedChars(DFA8_maxS);
    static final short[] DFA8_accept = DFA.unpackEncodedString(DFA8_acceptS);
    static final short[] DFA8_special = DFA.unpackEncodedString(DFA8_specialS);
    static final short[][] DFA8_transition;

    static {
        int numStates = DFA8_transitionS.length;
        DFA8_transition = new short[numStates][];
        for (int i=0; i<numStates; i++) {
            DFA8_transition[i] = DFA.unpackEncodedString(DFA8_transitionS[i]);
        }
    }

    class DFA8 extends DFA {

        public DFA8(BaseRecognizer recognizer) {
            this.recognizer = recognizer;
            this.decisionNumber = 8;
            this.eot = DFA8_eot;
            this.eof = DFA8_eof;
            this.min = DFA8_min;
            this.max = DFA8_max;
            this.accept = DFA8_accept;
            this.special = DFA8_special;
            this.transition = DFA8_transition;
        }
        public String getDescription() {
            return "1673:1: statement : ( ^( LABELED_STATMENT_TOK ID_TOK SOURCE_TOK ) | ^( EXPRESSION_STATMENT_TOK ID_TOK SOURCE_TOK ) | selection_statement | iteration_statement | ^( JUMP_STATMENT_TOK ID_TOK SOURCE_TOK ) | parallel_statement | ^( 'EOT' ID_TOK SOURCE_TOK ) | preemption_statment | scope_statement );";
        }
    }
 

    public static final BitSet FOLLOW_external_declaration_in_translation_unit86 = new BitSet(new long[]{0x00010C00001000C2L});
    public static final BitSet FOLLOW_FUNCTION_TOK_in_external_declaration123 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_external_declaration125 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_external_declaration127 = new BitSet(new long[]{0x0000000000088300L});
    public static final BitSet FOLLOW_declaration_in_external_declaration137 = new BitSet(new long[]{0x0000000000088300L});
    public static final BitSet FOLLOW_scope_statement_in_external_declaration140 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_GLOBAL_DECLARATION_TOK_in_external_declaration147 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_declaration_in_external_declaration152 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_42_in_external_declaration159 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_external_declaration161 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_external_declaration163 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_43_in_external_declaration179 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_external_declaration181 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_external_declaration183 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_48_in_external_declaration198 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_external_declaration200 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_external_declaration202 = new BitSet(new long[]{0x0000000000088300L});
    public static final BitSet FOLLOW_scope_statement_in_external_declaration215 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_PRET_DEF_TOK_in_external_declaration223 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_TYPE_DECLARATION_TOK_in_declaration238 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_declaration240 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_declaration242 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_DECLARATION_TOK_in_declaration258 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_declaration260 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_declaration262 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_PREPROC_TOK_in_declaration276 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_SCOPE_TOK_in_scope_statement305 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_compound_statement_in_scope_statement312 = new BitSet(new long[]{0x0000000000020000L});
    public static final BitSet FOLLOW_EMPTY_TOK_in_scope_statement314 = new BitSet(new long[]{0x0000000000020000L});
    public static final BitSet FOLLOW_END_TOK_in_scope_statement317 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_declaration_in_compound_statement335 = new BitSet(new long[]{0x00000000000CFF02L,0x0081000000000000L});
    public static final BitSet FOLLOW_statement_list_in_compound_statement339 = new BitSet(new long[]{0x00000000000CFF02L,0x0081000000000000L});
    public static final BitSet FOLLOW_statement_in_statement_list353 = new BitSet(new long[]{0x00000000000CFF02L,0x0081000000000000L});
    public static final BitSet FOLLOW_LABELED_STATMENT_TOK_in_statement368 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_statement370 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_statement384 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_EXPRESSION_STATMENT_TOK_in_statement394 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_statement396 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_statement398 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_selection_statement_in_statement413 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_iteration_statement_in_statement419 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_JUMP_STATMENT_TOK_in_statement426 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_statement428 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_statement430 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_parallel_statement_in_statement444 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_112_in_statement450 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_statement452 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_statement454 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_preemption_statment_in_statement469 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_scope_statement_in_statement474 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ABORT_TOK_in_preemption_statment495 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_set_in_preemption_statment499 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_preemption_statment505 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_preemption_statment507 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_preemption_statment520 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_ABORT_TOK_in_preemption_statment531 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_118_in_preemption_statment534 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_preemption_statment536 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_preemption_statment538 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_preemption_statment551 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_119_in_parallel_statement568 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_parallel_statement570 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_parallel_statement572 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_SELECTION_STATMENT_TOK_in_selection_statement606 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_120_in_selection_statement609 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_selection_statement613 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_selection_statement615 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_selection_statement631 = new BitSet(new long[]{0x0000000000000008L,0x0200000000000000L});
    public static final BitSet FOLLOW_121_in_selection_statement635 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_selection_statement639 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_selection_statement641 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_selection_statement657 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_SELECTION_STATMENT_TOK_in_selection_statement672 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_122_in_selection_statement675 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_selection_statement677 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_selection_statement679 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_selection_statement695 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_ITERATION_STATEMENT_TOK_in_iteration_statement732 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_123_in_iteration_statement735 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_iteration_statement738 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_iteration_statement740 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_iteration_statement756 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_ITERATION_STATEMENT_TOK_in_iteration_statement763 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_124_in_iteration_statement766 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_123_in_iteration_statement768 = new BitSet(new long[]{0x0000000000000010L});
    public static final BitSet FOLLOW_ID_TOK_in_iteration_statement770 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_iteration_statement786 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_iteration_statement789 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_ITERATION_STATEMENT_TOK_in_iteration_statement811 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_125_in_iteration_statement814 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_iteration_statement816 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_iteration_statement818 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_iteration_statement836 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_statement_in_synpred13_PretCTreeGrammar353 = new BitSet(new long[]{0x0000000000000002L});
    public static final BitSet FOLLOW_ABORT_TOK_in_synpred23_PretCTreeGrammar495 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_set_in_synpred23_PretCTreeGrammar499 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_synpred23_PretCTreeGrammar505 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_synpred23_PretCTreeGrammar507 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_synpred23_PretCTreeGrammar520 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_SELECTION_STATMENT_TOK_in_synpred25_PretCTreeGrammar606 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_120_in_synpred25_PretCTreeGrammar609 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_synpred25_PretCTreeGrammar613 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_synpred25_PretCTreeGrammar615 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_synpred25_PretCTreeGrammar631 = new BitSet(new long[]{0x0000000000000008L,0x0200000000000000L});
    public static final BitSet FOLLOW_121_in_synpred25_PretCTreeGrammar635 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_synpred25_PretCTreeGrammar639 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_synpred25_PretCTreeGrammar641 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_synpred25_PretCTreeGrammar657 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_ITERATION_STATEMENT_TOK_in_synpred26_PretCTreeGrammar732 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_123_in_synpred26_PretCTreeGrammar735 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_ID_TOK_in_synpred26_PretCTreeGrammar738 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_synpred26_PretCTreeGrammar740 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_synpred26_PretCTreeGrammar756 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_ITERATION_STATEMENT_TOK_in_synpred27_PretCTreeGrammar763 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_124_in_synpred27_PretCTreeGrammar766 = new BitSet(new long[]{0x0000000000000004L});
    public static final BitSet FOLLOW_123_in_synpred27_PretCTreeGrammar768 = new BitSet(new long[]{0x0000000000000010L});
    public static final BitSet FOLLOW_ID_TOK_in_synpred27_PretCTreeGrammar770 = new BitSet(new long[]{0x0000000000000020L});
    public static final BitSet FOLLOW_SOURCE_TOK_in_synpred27_PretCTreeGrammar786 = new BitSet(new long[]{0x0000000000000008L});
    public static final BitSet FOLLOW_scope_statement_in_synpred27_PretCTreeGrammar789 = new BitSet(new long[]{0x0000000000000008L});

}