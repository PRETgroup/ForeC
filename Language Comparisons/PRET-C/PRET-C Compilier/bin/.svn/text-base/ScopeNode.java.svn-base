import java.util.Hashtable;

public class ScopeNode {
	public long ID = -1;
	public long parentID = -1;
	public Hashtable<String,StatementNode> variableMap = new Hashtable<String,StatementNode>(); //key = name of var in scope, var = the node
	//list of stuct and unions
	public Hashtable<String,StatementNode> listOfStruct= new Hashtable<String,StatementNode>();
	public Hashtable<String,StatementNode> listOfTypeDef = new Hashtable<String,StatementNode>();
	public ScopeNode(long ID) {
		this.ID = ID;
	}

	public void variableMapPut(String key, StatementNode value) {
		variableMap.put(key.replaceAll("(\\Q*\\E)+","").replaceAll("(\\Q[\\E)[A-Za-z0-9]*(\\Q]\\E)","").replaceAll(" ",""),value);
	}
	
	public String toString() {
		String output = "";
		output += "ID: "+ID+"\n";
		output += "PARENT: "+parentID+"\n";
		output += "Variable Map:\n "+variableMap.keySet()+"\n";	
		output += "List of Stucts and Unions:\n " + listOfStruct.keySet() +"\n";
		output += "List of TypeDef:\n " + listOfTypeDef.keySet()+"\n";
		return output;

	}
}
