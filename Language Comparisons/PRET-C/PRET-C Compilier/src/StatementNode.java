import java.util.ArrayList;

public class StatementNode {
	public long funcScopeID;
	public long scopeID;
	public long ID;
	public long line;
	public String sourceCode;
	public String type;
	public String IDprefix;
	/*
	function
	typedef
	declare
	label
	case
	default
	goto
	continue
	break
	return
	return2
	if
	else
	switch
	while
	dowhile
	for
	expression
	
	ReactiveInput
	ReactiveOutput
	PAR
	thread
	EOT
	strongAbort
	weakAbort
	
	scopedVaraibles
	*/
	public ArrayList<String> name; //name of declared VAR / function name / thread name / lable name
	
	public ArrayList<Long> thdInsID; //name of declared VAR / function name
	public String returnType;
	public ArrayList<String> declaredType; //name of declared VAR / function name
	public ArrayList<String> varSpecifiers = new ArrayList<String>(); //static const ... etc int
	/*possible add type extension for extern static etc and constant volitile etc*/
	public String condition;
	public ArrayList<ArrayList<String>> constantStatement;
	public ArrayList<String> assignmentExpression;
	public ArrayList<String> functionParameter;
	public ArrayList<String> assignedVars;
	public ArrayList<StatementNode> scopedVaraibles = new ArrayList<StatementNode>(); //for structs etc...
	public StatementNode sourceNode; //for structs etc...
	public ArrayList<String> minValue = new ArrayList<String>();
	public ArrayList<String> maxValue = new ArrayList<String>();
	public String loopBound = "";
	public String structTypeName = ""; //structure and union type name
	//for EOTs and PAR
	/*public ArrayList<String> weakAborts;
	public ArrayList<String> strongAborts;
	public ArrayList<String> hierWeakAborts;
	public ArrayList<String> hierStrongAborts;*/
	//for PAR
	//name = thread names
	StatementNode() {
		funcScopeID = -1;
		scopeID = -1;
		ID = -1;
		line = -1;
		sourceCode = "";
		type = "";
		name = new ArrayList<String>();
		thdInsID = new ArrayList<Long>();
		declaredType = new ArrayList<String>();
		returnType ="";
		condition = "";
		constantStatement = new ArrayList<ArrayList<String>>();
		ArrayList<String> constatntStatement1stElement = new ArrayList<String>();
		constantStatement.add(constatntStatement1stElement);
		assignmentExpression = new ArrayList<String>();
		functionParameter = new ArrayList<String>();
		assignedVars = new ArrayList<String>();
		sourceNode = null;
	}
	
	public String getIDwPrefix() {
		return "_"+IDprefix+"_"+ID;
	}
	public String getScopeIDwPrefix() {
		return "_"+IDprefix+"_"+scopeID;
	}
	public void addScopedVaraibles(StatementNode n) {
		n.sourceNode = this;
		//... add more as needed 
		scopedVaraibles.add(n);
	}
	public String toString() {
		if (type.equals("scopedVaraibles") == false) {
			String output = "";
			output += "Function scope: " + funcScopeID + "\n";
			output += "Scope: " + scopeID + "\n";
			output += "ID: " + ID + "\n";
			output += "Line: " + line + "\n";
			output += "Source Code: " + sourceCode + "\n";
			output += "TYPE: " + type + "\n";
			for (int i=0; i < name.size();i++) {
				output += "Name: " + i + ": "+name.get(i) +"\n";
			}
			for (int i=0; i < thdInsID.size();i++) {
				output += "Thread Instance ID: " + i + ": "+thdInsID.get(i) +"\n";
			}
			for (int i=0; i < declaredType.size();i++) {
				output += "declaredType: " + i + ": "+declaredType.get(i) +"\n";
			}
			for (int i=0; i < varSpecifiers.size();i++) {
				output += "varSpecifiers: " + i + ": "+varSpecifiers.get(i) +"\n";
			}
			output += "StructTypeName: " +structTypeName + "\n";
			output += "Return type: " + returnType + "\n";
			output += "condition: " + condition + "\n";
			output += "loop bound: "+loopBound+"\n";
			for (int i=0; i < constantStatement.size();i++) {
				output += "Constant Statment: " + i + ": "+constantStatement.get(i) +"\n";
			}		
			for (int i=0; i < assignmentExpression.size();i++) {
				output += "Assignment Expression: " + i + ": "+assignmentExpression.get(i) +"\n";
			}	
			for (int i=0; i < minValue.size();i++) {
				output += "\tminValue: " + i + ": "+minValue.get(i) +"\n";
			}	
			for (int i=0; i < maxValue.size();i++) {
				output += "\tmaxValue: " + i + ": "+maxValue.get(i) +"\n";
			}		
			for (int i=0; i < functionParameter.size();i++) {
				output += "Function Parameter: " + i + ": "+functionParameter.get(i) +"\n";
			}
			for (int i=0; i < assignedVars.size();i++) {
				output += "Assigned Vars: " + i + ": "+assignedVars.get(i) +"\n";
			}
			for (int i=0; i < scopedVaraibles.size();i++) {
				output += "scopedVaraibles Vars: " + i + ": "+scopedVaraibles.get(i) +"\n";
			}
			return output;
		}else{
			String output = "\n";
			output += "StructTypeName: " +structTypeName + "\n";
			//output += "Source Node ID: " +sourceNode.ID + "\n";
			output += "\tScope: " + scopeID + "\n";
			output += "\tTYPE: " + type + "\n";
			for (int i=0; i < name.size();i++) {
				output += "\tName: " + i + ": "+name.get(i) +"\n";
			}
			for (int i=0; i < declaredType.size();i++) {
				output += "\tdeclaredType: " + i + ": "+declaredType.get(i) +"\n";
			}
			for (int i=0; i < varSpecifiers.size();i++) {
				output += "varSpecifiers: " + i + ": "+varSpecifiers.get(i) +"\n";
			}
			for (int i=0; i < constantStatement.size();i++) {
				output += "\tConstant Statment: " + i + ": "+constantStatement.get(i) +"\n";
			}	
			for (int i=0; i < minValue.size();i++) {
				output += "\tminValue: " + i + ": "+minValue.get(i) +"\n";
			}	
			for (int i=0; i < maxValue.size();i++) {
				output += "\tmaxValue: " + i + ": "+maxValue.get(i) +"\n";
			}				
			for (int i=0; i < assignmentExpression.size();i++) {
				output += "\tAssignment Expression: " + i + ": "+assignmentExpression.get(i) +"\n";
			}	
			for (int i=0; i < scopedVaraibles.size();i++) {
				output += "scopedVaraibles Vars: " + i + ": "+scopedVaraibles.get(i) +"\n";
			}
			return output;
		
		
		}
	}

}