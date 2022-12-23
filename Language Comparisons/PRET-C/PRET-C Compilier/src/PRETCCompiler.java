
import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;

import org.antlr.runtime.*;
import org.antlr.runtime.tree.*;
public class PRETCCompiler {

public static ArrayList<String> FBCompile(String fbName, String PretCCode, String outputPath, String instanceName, String runXMLCode, boolean simulation) {
	CFilePrinter PRETCCode = new CFilePrinter(fbName+".pret.temp",outputPath);
	PRETCCode.print("PRETDEF "+fbName+";");
	PRETCCode.print(PretCCode);
	PRETCCode.close();
	String PRETCFile = outputPath+fbName+".pret.temp";
	ArrayList<String> arguments = new ArrayList<String>();
	arguments.add("-l");
	arguments.add(PRETCFile);
	arguments.add("-function");
	arguments.add(fbName+"run");
	arguments.add("-p");
	arguments.add(fbName);
	if (simulation) {
		arguments.add("-timeMeSim");
		arguments.add("-prefix");
		arguments.add(runXMLCode);
	}else{
		arguments.add("-timeMeFB");
	}
	arguments.add("-skipVC");
	arguments.add("-o");
	arguments.add(outputPath);
	arguments.add("-FBins");
	arguments.add(instanceName);
	try{
		return PRETCCompiler.run(arguments.toArray(new String[1]));
	}catch (Exception e) {
		e.printStackTrace();
	}
	return null;
}
public static void main(String args[]) throws Exception {
	run(args);
}
public static ArrayList<String> run(String args[]) throws Exception {
	//test fb
	ArrayList<String> arguments1 = new ArrayList<String>(Arrays.asList(args));
	if ((arguments1.indexOf("-fbtest") >= 0)) {
		String code = "void adder(adder* me) \n"
					+	"{\n"
					+	"int a = 0; \n"
					+	"a++; \n"
					+	"me->IN1 = 3; \n"
					+	"EOT; \n"
					+	"apple(apple(3))+apple(1);\n"
					+	"banan(1);\n"
					+	"} \n"
					+ "int apple(int a) { int a = 0; a++;}\n"
					+ "int apple(int);\n";
		
		FBCompile("adder",code,"c:\\test\\","my","RUNCODE HERE\n",false);

		return null;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	String projectName = "a";
	String mainFunctionName = "main";
	String inputfile = "";
	int tickDelay = 0;
	boolean skipProprocessing = false;
	boolean annotateOnly = false;
	boolean skipVC = false;
	boolean timeMeSimulation = false;
	boolean socketOff = false;
	boolean isTimeMeFB =false;
	String fbInstanceName = "";
	String outputPath = "";
	ArrayList<String> extraFileLocation = new ArrayList<String>();
	String mainPrefix = "";
	String mainSuffix = "";
	if (args.length <= 0) {
		System.out.println("Usage \t-l <Main PRET-C file>\n" +
							" \t-a <other .c>,<and .h files>\n"+
							" \t-p <output project name> (default: a)\n" +
							" \t\t generates <project name>.thd.h <project name>.PRET.h <project name>.main.c\n" + 
							" \t-function <main function name> (defualt: main)\n" +	
							" \t-PP (allow duplicating thread reusage, may not work for strange C code)\n"+
							" \t-AO (Annotate only no PRET-C)\n" +
							" \t-skipVC (skips declarationg checking)\n" +
							" \t-timeMeSim\n"+
							" \t-timeMeFB\n"+
							" \t-FBins (function block instance name)\n"+
							" \t-o (output path)\n"+
							" \t-prefix (main prefix)\n"+
							" \t-suffix (main suffix)\n"+
							" \t-tickDelay (integer)\n"+
				              "date of JAR: 02/June/2015\n"+
				              "Recent changes: fix initalisation of global variables, find bound assembly comment"
							  ) ;
		System.exit(0);
	}else{
		ArrayList<String> arguments = new ArrayList<String>(Arrays.asList(args));
		
		if (arguments.indexOf("-l") >= 0) {
			inputfile = arguments.get(arguments.indexOf("-l")+1);
		}
		if (arguments.indexOf("-p") >= 0) {
			projectName = arguments.get(arguments.indexOf("-p")+1);
		}
		if (arguments.indexOf("-function") >= 0) {
			mainFunctionName = arguments.get(arguments.indexOf("-function")+1);
		}	
		skipProprocessing = true;
		if (arguments.indexOf("-PP") >= 0) {
			skipProprocessing = false;
		}
		
		if (arguments.indexOf("-skipVC") >= 0) {
			skipVC = true;
		}
		if (arguments.indexOf("-AO") >= 0) {
			annotateOnly = true;
		}
		if (arguments.indexOf("-socketOff") >= 0) {
			socketOff = true;
		}
		if (arguments.indexOf("-timeMeSim") >= 0) {
			skipProprocessing = true;
			timeMeSimulation = true;
			skipVC = true;
			annotateOnly = false;
			/*if (mainFunctionName.length() > 0) {
				System.out.println("Need a main function");
				System.exit(0);
			}*/
			isTimeMeFB = true;
		}
		if (arguments.indexOf("-timeMeFB") >= 0) {
			skipProprocessing = true;
			isTimeMeFB = true;
		}
		if (arguments.indexOf("-FBins") >= 0) {
			fbInstanceName = arguments.get(arguments.indexOf("-FBins")+1);
		}	
		if (arguments.indexOf("-0") >= 0) {
			outputPath = arguments.get(arguments.indexOf("-0")+1);
		}
		
		if (arguments.indexOf("-a") >= 0) {
			extraFileLocation.addAll(Arrays.asList(arguments.get(arguments.indexOf("-a")+1).split(",")));
			System.out.println(arguments.get(arguments.indexOf("-a")+1));
		}
		if (arguments.indexOf("-tickDelay") >= 0) {
			tickDelay = Integer.parseInt(arguments.get(arguments.indexOf("-tickDelay")+1));
		}
	}
	if (inputfile == "") {		
		System.out.println("No input file argument");
		System.exit(0);
	}
	
	TimeMeNotify.notice(mainFunctionName,"Compiling");
	CFileReader myMainFile,currentFile;
	String combileFileData = "";
	if (extraFileLocation.size() > 0) {
		myMainFile = new CFileReader(inputfile);
		combileFileData = myMainFile.data;
		
		for (int i = 0; i < extraFileLocation.size();i++) {
			String currentFileName = extraFileLocation.get(i);
			String extension = currentFileName.substring(currentFileName.lastIndexOf('.')+1);
			if (extension.equals("h")) {

			}else if(extension.equals("c")) {
				currentFile = new CFileReader(currentFileName);
				combileFileData = "//"+currentFileName+"\n"+currentFile.data +combileFileData;
			}else{
				System.out.println("unrecongised extension: "+extension+" filename: "+currentFileName);
				System.exit(0);
			}
		}
		for (int i = 0; i < extraFileLocation.size();i++) {
			String currentFileName = extraFileLocation.get(i);
			String extension = currentFileName.substring(currentFileName.lastIndexOf('.')+1);
			if (extension.equals("h")) {
				String include = "#include \"(.*)?"+currentFileName+"\"";
				currentFile = new CFileReader(currentFileName);
				combileFileData = combileFileData.replaceFirst(include,"//"+currentFileName+"\n"+currentFile.data);
				combileFileData = combileFileData.replaceAll(include,"//"+include);
			}else if (extension.equals("c")) {

			}else{
				System.out.println("unrecongised extension: "+extension+" filename: "+currentFileName);
				System.exit(0);
			}
		}
	
		CFilePrinter combined = new CFilePrinter(inputfile+".combined.c");
		combined.print(combileFileData);
		combined.close();
		inputfile = inputfile+".combined.c";
	
	}
	String path = "";
	String filename = "";
	/////preprocessing
	File CfileFILE = new File(inputfile);
	BufferedReader Cfile = new BufferedReader(new FileReader(CfileFILE));
	if (outputPath.length() == 0) {
		path = CfileFILE.getParent()+File.separator;
	}else{
		path = outputPath;
	}
	filename = CfileFILE.getName();
		
	
	if (path.equals("null"+File.separator)) {
		path = "";
	}
	if (skipProprocessing != true) {
		String preProcArgs[] = {inputfile};
		PreProcMain.main(preProcArgs);
		inputfile += ".PRETProc.c";
	}
	
	PretCLexer lex = new PretCLexer();
	lex = new PretCLexer(new ANTLRFileStream(inputfile));

	CommonTokenStream tokens = new CommonTokenStream(lex);
	PretCParser parser = new PretCParser(tokens);
	PretCParser.translation_unit_return r = parser.translation_unit();

	CommonTreeNodeStream nodes = new CommonTreeNodeStream(r.tree); 
	PretCTreeGrammar walker = new PretCTreeGrammar(nodes);
	walker.nodesTable = parser.nodesTable;
	walker.scopeList = parser.scopeList;
	walker.projectName = projectName;
	walker.path = path;
	walker.mainFunctionName = mainFunctionName;
	walker.annotateOnly = annotateOnly;
	walker.skipVC = skipVC;
	walker.timeMeSimulation = timeMeSimulation;
	walker.socketOff = socketOff;
	walker.projectPrefix = fbInstanceName;
	walker.mainPrefix = mainPrefix;
	walker.mainSuffix = mainSuffix;
	walker.isFunctionBlock = isTimeMeFB;
	walker.tickDelay = tickDelay;
	walker.translation_unit();
	ArrayList<String> output = new ArrayList<String>();
	if (annotateOnly) {
		System.out.println("Files Created " +walker.outputMainFilename);
	}else if (timeMeSimulation) {
		System.out.println("Files Created " +walker.outputMainFilename +" "+walker.outputThdHeaderFilename+" "+walker.outputPretHeaderFilename+" "+walker.timeMeSim.filename);
		output.add(walker.outputMainFilename);
		output.add(walker.outputThdHeaderFilename);
		output.add(walker.outputPretHeaderFilename);
		output.add(walker.timeMeSim.filename);
	}else{
		System.out.println("Files Created " +walker.outputMainFilename +" "+walker.outputThdHeaderFilename+" "+walker.outputPretHeaderFilename);
		output.add(walker.outputMainFilename);
		output.add(walker.outputThdHeaderFilename);
		output.add(walker.outputPretHeaderFilename);
	}
	return output;
}
}