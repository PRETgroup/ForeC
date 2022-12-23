import java.io.*;
import org.antlr.runtime.*;
import org.antlr.runtime.tree.*;
import java.util.ArrayList;  
import java.util.Hashtable;
import java.util.Enumeration;

public class PreProcMain {
public static void main(String args[]) throws Exception {
	int done = 1;
	Hashtable occurence = new Hashtable();
	InputStream is;
	String source = "";
	while(done > 0) {
		PretCPreprocessorLexer lex = new PretCPreprocessorLexer();
		
		if (source.equals("")) {

			if (args.length >= 1) {	
				lex = new PretCPreprocessorLexer(new ANTLRFileStream(args[0]));
			}else{
				lex = new PretCPreprocessorLexer(new ANTLRInputStream(System.in));
			}
		}else{
			is = new ByteArrayInputStream(source.getBytes("UTF-8"));
			lex = new PretCPreprocessorLexer(new ANTLRInputStream(is));
		}
		CommonTokenStream tokens = new CommonTokenStream(lex);
		PretCPreprocessorParser parser = new PretCPreprocessorParser(tokens);
		parser.occurence = occurence;
		//pre
		PretCPreprocessorParser.translation_unit_return r = parser.translation_unit();
		
		//post
		ArrayList threadKeys = new ArrayList<String>();
		occurence = new Hashtable();
		for (Enumeration e = parser.threads.keys(); e.hasMoreElements() ;) {
			String key = (String)e.nextElement();
			String thread = (String)parser.threads.get(key);
			//System.out.println("sss "+key);
			threadKeys.add(key);
		}
		
		for (ArrayList e = parser.pars;e.isEmpty()==false;) {
			String parThd = (String)e.remove(0);
			//System.out.println("zzzzzz "+parThd);
			if (threadKeys.contains(parThd)){
				//System.out.println(parThd);
				if (occurence.get(parThd) == null) {
					occurence.put(parThd,1);
				}else{
					int count = (Integer)occurence.get(parThd);
					count++;
					occurence.put(parThd,count);
				}
			}else if(parThd.equals("void")) {
				occurence.put(parThd,1);
				//does nothing
			}else{
				System.out.println("Used Thread in PAR \""+parThd+"\" but not declared");
				System.exit(0); 
			}
		}
		//System.out.println("zzzzzz "+occurence.get("Timer_count"));
		done--;
		for (Enumeration e = occurence.keys(); e.hasMoreElements() ;) {
			String thd = (String)e.nextElement();
			int number = (Integer)occurence.get(thd);
			if (number > 1) {
				done+=2;
				break;
			}
		}
		//System.out.println(occurence);
		
		source = parser.source;
	}
	System.out.println("END\n");
	CFilePrinter output = new CFilePrinter(args[0]+".PRETProc.c");
	output.print(source);
	output.close();
	//parser.pars
/*
	CommonTreeNodeStream nodes = new CommonTreeNodeStream(r.tree); 
	PretCTreeGrammar walker = new PretCTreeGrammar(nodes);
	walker.nodesTable = parser.nodesTable;
	
	if (args.length >= 2) {	
		//System.out.println("filename " + args[1]);
		//walker.filename = args[1];
		walker.projectName = args[1];
	}
	walker.translation_unit();
	System.out.println("Files Created " +walker.outputMainFilename +" "+walker.outputThdHeaderFilename+" "+walker.outputPretHeaderFilename);
*/
	}
}