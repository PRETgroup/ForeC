

import java.io.*;
import java.io.IOException;

public class CFilePrinter {
	public String filename;
	public int indent;

	private FileWriter fstream;
	private BufferedWriter fileBuffer;


	public CFilePrinter(String filename) {
		this.filename = filename;
		try {
			fstream = new FileWriter(filename);
			fileBuffer= new BufferedWriter(fstream);
		}catch(IOException e){
			System.out.println("file open error");
		}
		//line = "";
	}

	public CFilePrinter(String filename, String path) {
		this.filename = filename;
		try {
			fstream = new FileWriter(path+filename);
			fileBuffer= new BufferedWriter(fstream);
		}catch(IOException e){
			System.out.println("file open error");
		}
		//line = "";
	}
	
	public String indent(String line) {
		String indents = "";
		if (indent < 0) {
			System.out.println("warning indent less than 0 at line: "+line);
		}
		for (int i=0; i < indent; i++) {
			indents += "\t";
		}
		return indents+line;
	}		
	
	public void print(String line) {
		try {
			fileBuffer.write(indent(line));
			//line = "";
		}catch(IOException e){
			System.out.println("file write error");
		}
	}
	public void printNoIndent(String line) {
		try {
			fileBuffer.write(line);
			//line = "";
		}catch(IOException e){
			System.out.println("file write error");
		}
	}
	public void close() {
		try {
			fileBuffer.flush();
			fileBuffer.close();
			fstream.close();
		}catch(IOException e){
			System.out.println("file close error");
		}
	}

}



