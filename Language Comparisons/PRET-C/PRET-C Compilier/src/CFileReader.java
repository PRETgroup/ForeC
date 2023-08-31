
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;


public class CFileReader {
	public String fullfilename = "";
	public String path = "";
	public String filename = "";
	public String data = "";
	public CFileReader(String fullfilename) {
		this.fullfilename = fullfilename;
		try {
			File CfileFILE = new File(fullfilename);
			BufferedReader Cfile = new BufferedReader(new FileReader(CfileFILE));
			path = CfileFILE.getParent()+File.separator;
			filename = CfileFILE.getName().substring(0, CfileFILE.getName().lastIndexOf('.'));
			String line = "";
			for(;;line = Cfile.readLine()) {
				if (line == null) {
					break;
				}
				data += line+'\n';
			}
			Cfile.close();
		}catch(IOException e){
			System.out.println("file open error" + e);
		}
		//line = "";
	}
	
	public CFileReader(String fullfilename,boolean readdata) {
		this.fullfilename = fullfilename;
		try {
			File CfileFILE = new File(fullfilename);
			BufferedReader Cfile = new BufferedReader(new FileReader(CfileFILE));
			path = CfileFILE.getParent()+File.separator;
			filename = CfileFILE.getName().substring(0, CfileFILE.getName().lastIndexOf('.'));
			String line = "";
			if (readdata) {
				for(;;line = Cfile.readLine()) {
					if (line == null) {
						break;
					}
					data += line+'\n';
				}
			}
			Cfile.close();
		}catch(IOException e){
			System.out.println("file open error" + e);
		}
		//line = "";
	}
	
	public void readData() {
		try {
			File CfileFILE = new File(fullfilename);
			BufferedReader Cfile = new BufferedReader(new FileReader(CfileFILE));
			String line = "";
			for(;;line = Cfile.readLine()) {
				if (line == null) {
					break;
				}
				data += line+'\n';
			}
			Cfile.close();
		}catch(IOException e){
			System.out.println("file open error" + e);
		}
	}
}