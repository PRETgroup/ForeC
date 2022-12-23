import java.util.Hashtable;
import java.util.Enumeration;
public class TimeMeSimulation{
	public boolean timeMeSimulation = false;
	CFilePrinter filePrinter = null;
	boolean skipVC = true;
	String filename = "";
	Hashtable<Long,ScopeNode> scopeList = new Hashtable<Long,ScopeNode>();
	boolean socketOff = false;
	public TimeMeSimulation(boolean enableSimlationCode, Hashtable<Long,ScopeNode> scopeList) {
		timeMeSimulation = enableSimlationCode;
		this.scopeList = scopeList;
	}
	String projectPrefix = "";
	public void createSimuFile(String projectName,String projectPrefix, String path) {
		if (timeMeSimulation) {
			filename = projectPrefix.substring(0,projectPrefix.length()-1) + ".simu.h";
			filePrinter = new CFilePrinter(filename,path);
			filePrinter.print("#include <stdio.h> \n");
			filePrinter.print("#include <Winsock2.h> \n");
			filePrinter.print("#include \"Simulation.h\" \n");
			filePrinter.print("#include \""+projectPrefix.substring(0,projectPrefix.length()-1) + ".h\"\n");
			
			filePrinter.print("char "+projectPrefix+"_lineCount[1024] = \"\";\n");
			filePrinter.print("char* "+projectPrefix+"_lineCountPrt = "+projectPrefix+"_lineCount;\n");



			this.projectPrefix = projectPrefix;
			
		}
	}
	
	public void writeMain(String mainFunctionName) {
		if (timeMeSimulation) {
//			filePrinter.print("mxml_node_t *"+mainFunctionName+"_simdata, *"+mainFunctionName+"_simvars, *"+mainFunctionName+"_simlines;\n");

			printInitXML(mainFunctionName);
			printRunPRETXML(mainFunctionName);
/*			printHandleTickCommand();
		//write the main file
			filePrinter.print("int main() {\n");
			filePrinter.indent++;
			
			if (socketOff==false) {
				printSocketInit();
			}
			printXMLInit();
			if (socketOff==false) {
				printSocketConnect();
			}
			filePrinter.print("PRETinitXML(tick);\n");
			printOutputXml();
			
			filePrinter.print("for(;;){\n");
			filePrinter.indent++;
			if (socketOff==false) {
				printWaitForCommand();
			}
			filePrinter.print("for(;;){\n");
			filePrinter.indent++;
			
			if (socketOff==false) {
				printReadAndResponse(mainFunctionName);
			}else{
				filePrinter.print(mainFunctionName+"();\n");
			
				printXmlVariables(mainFunctionName);
				printOutputXml();
			}
			filePrinter.indent--;
			filePrinter.print("}\n");
			
			filePrinter.indent--;
			filePrinter.print("}\n");
			filePrinter.indent--;
			if (socketOff==false) {
				printSocketClose();
			}
			printXMLClose();
			filePrinter.print("return 1;");
			filePrinter.print("}\n");*/
		}
	}
	private void printRunPRETXML(String mainFunctionName) {
	
		filePrinter.print("void "+projectPrefix+"runPRETXML"+"("+projectPrefix.substring(0,projectPrefix.length()-1)+"* me) {\n");
		filePrinter.indent++;
			//print line numbers
			filePrinter.print("clearChildren(me->_simevents);"+"\n");
			filePrinter.print("clearChildren(me->_simvars);"+"\n");
			//filePrinter.print("clearChildren(me->_simstate);"+"\n");
			//filePrinter.print("clearChildren(me->_simtransitions);"+"\n");
			filePrinter.print("clearChildren(me->_simlines);"+"\n");
			
			filePrinter.print("if (strlen("+projectPrefix+"_lineCountPrt) > 0) {"+"\n");
				filePrinter.indent++;
				filePrinter.print("mxmlElementSetAttr(me->_simlines, \"Value\", "+projectPrefix+"_lineCountPrt);"+"\n");
				filePrinter.print("sprintf("+projectPrefix+"_lineCountPrt,\"\");"+"\n");
				filePrinter.indent--;
			filePrinter.print("}else{"+"\n");
				filePrinter.indent++;
				filePrinter.print("mxmlElementSetAttr(me->_simlines, \"Value\", \"-1\");"+"\n");
				filePrinter.indent--;
			filePrinter.print("}"+"\n");
			
			filePrinter.print("mxml_node_t* childnode; // used as a temp node"+"\n");
			for (Enumeration<ScopeNode> e = scopeList.elements();e.hasMoreElements();) {
				ScopeNode n = e.nextElement();
				//printer.print("//scope "+n.ID+"\n");
				for (Enumeration<String> e2 = n.variableMap.keys();e2.hasMoreElements();) {
					String variableName = e2.nextElement();
					StatementNode nDeclare = n.variableMap.get(variableName); //node of declared variable
					String newVariableName = getNewVariableName(variableName,nDeclare);
					String cast = "";
					if (n.ID == 0) { //print if scope is zero
					//if (nDeclare.type.equals("ReactiveInput")||nDeclare.type.equals("ReactiveOutput")) {
						String fbtype = "";
						String type = nDeclare.declaredType.get(0).replaceAll(" ","");
						String scope = "Internal";
						if (nDeclare.type.equals("ReactiveInput")) {
							scope = "Input";
						}else if (nDeclare.type.equals("ReactiveOutput")) {
							scope = "Output";
						}
						if (type.contains("short")) {
							fbtype = "IEC_INT";
							if (type.contains("unsigned")) {
								fbtype = "IEC_UINT";
							}
							cast = "%d";
						}else if (type.contains("int")) {
							fbtype = "IEC_DINT";
							if (type.contains("unsigned")) {
								fbtype = "IEC_UDINT";
							}
							cast = "%d";
						}else if (type.contains("long")) {
							fbtype = "IEC_LINT";
							if (type.contains("unsigned")) {
								fbtype = "IEC_ULINT";
							}
							cast = "%d";
						}else if (type.contains("float")) {
							fbtype = "IEC_REAL";
							cast = "%f";
						}else if (type.contains("double")) {
							fbtype = "IEC_DREAL";
							cast = "%f";
						}else if (type.contains("char*")){
							fbtype = "IIEC_STRING";
							cast = "%s";
						}else if (type.contains("char")) {
							fbtype = "IEC_UINT";
							cast = "%c";
						}else if (type.contains("bool")) {
							fbtype = "IEC_BOOL";
							cast = "%01x";
						}else{
							System.out.println("unknown type "+type);
							continue;
							//System.exit(0);
						}
						
						filePrinter.print("childnode = mxmlNewElement(me->_simvars,\"Var\");"+"\n");
						filePrinter.print("mxmlElementSetAttr(childnode, \"Name\", \""+variableName+"\");"+"\n");
						filePrinter.print("mxmlElementSetAttr(childnode, \"Scope\", \""+scope+"\");"+"\n");
						filePrinter.print("mxmlElementSetAttr(childnode, \"Type\", \""+type+"\");"+"\n");
						filePrinter.print("mxmlElementSetAttrf(childnode, \"Value\", \""+cast+"\","+newVariableName+") ;"+"\n");
					}else{
					
					}
					//printer.print("//"+variableName+" -> "+newVariableName+"\n");

				}
			}
			
		filePrinter.print(projectPrefix+"runXML(me);"+"\n");
		filePrinter.indent--;
		filePrinter.print("}"+"\n");
	}	
	private void printXmlVariables(String mainFunctionName) {
		//print line numbers
		filePrinter.print("clearChildren(PRETCBlock1_simvars);");

		filePrinter.print("if (strlen("+mainFunctionName+"_lineCountPrt) > 0) {"+"\n");
			filePrinter.indent++;
			filePrinter.print("mxmlElementSetAttr(PRETCBlock1_simlines, \"Value\", "+mainFunctionName+"_lineCountPrt);"+"\n");
			filePrinter.print("sprintf("+mainFunctionName+"_lineCountPrt,\"\");"+"\n");
			filePrinter.indent--;
		filePrinter.print("}else{"+"\n");
			filePrinter.indent++;
			filePrinter.print("mxmlElementSetAttr(PRETCBlock1_simlines, \"Value\", \"-1\");"+"\n");
			filePrinter.indent--;
		filePrinter.print("}"+"\n");
		
		filePrinter.print("mxml_node_t* childnode; // used as a temp node"+"\n");
		for (Enumeration<ScopeNode> e = scopeList.elements();e.hasMoreElements();) {
			ScopeNode n = e.nextElement();
			//printer.print("//scope "+n.ID+"\n");
			for (Enumeration<String> e2 = n.variableMap.keys();e2.hasMoreElements();) {
				String variableName = e2.nextElement();
				StatementNode nDeclare = n.variableMap.get(variableName); //node of declared variable
				String newVariableName = getNewVariableName(variableName,nDeclare);
				String cast = "";
				if (n.ID == 0) { //print if scope is zero
				//if (nDeclare.type.equals("ReactiveInput")||nDeclare.type.equals("ReactiveOutput")) {
					String fbtype = "";
					String type = nDeclare.declaredType.get(0).replaceAll(" ","");
					String scope = "Internal";
					if (nDeclare.type.equals("ReactiveInput")) {
						scope = "Input";
					}else if (nDeclare.type.equals("ReactiveOutput")) {
						scope = "Output";
					}
					if (type.contains("short")) {
						fbtype = "IEC_INT";
						if (type.contains("unsigned")) {
							fbtype = "IEC_UINT";
						}
						cast = "%d";
					}else if (type.contains("int")) {
						fbtype = "IEC_DINT";
						if (type.contains("unsigned")) {
							fbtype = "IEC_UDINT";
						}
						cast = "%d";
					}else if (type.contains("long")) {
						fbtype = "IEC_LINT";
						if (type.contains("unsigned")) {
							fbtype = "IEC_ULINT";
						}
						cast = "%d";
					}else if (type.contains("float")) {
						fbtype = "IEC_REAL";
						cast = "%f";
					}else if (type.contains("double")) {
						fbtype = "IEC_DREAL";
						cast = "%f";
					}else if (type.contains("char*")){
						fbtype = "IIEC_STRING";
						cast = "%s";
					}else if (type.contains("char")) {
						fbtype = "IEC_UINT";
						cast = "%c";
					}else if (type.contains("bool")) {
						fbtype = "IEC_BOOL";
						cast = "%01x";
					}else{
						System.out.println("unknown type "+type);
						continue;
						//System.exit(0);
					}
					
					filePrinter.print("childnode = mxmlNewElement("+mainFunctionName+"_simvars,\"Var\");"+"\n");
					filePrinter.print("mxmlElementSetAttr(childnode, \"Name\", \""+variableName+"\");"+"\n");
					filePrinter.print("mxmlElementSetAttr(childnode, \"Scope\", \""+scope+"\");"+"\n");
					filePrinter.print("mxmlElementSetAttr(childnode, \"Type\", \""+type+"\");"+"\n");
					filePrinter.print("mxmlElementSetAttrf(childnode, \"Value\", \""+cast+"\","+newVariableName+") ;"+"\n");
				}else{
				
				}
				//printer.print("//"+variableName+" -> "+newVariableName+"\n");

			}
		}
	}
	private void printOutputXml() {
		filePrinter.print("{\n");
		filePrinter.indent++;
		filePrinter.print("char outbuffer[1024];\n");
		filePrinter.print("mxmlSaveString(outxml, outbuffer, sizeof(outbuffer),whitespace_cb);//MXML_NO_CALLBACK);;\n");
		filePrinter.print("printf(\"Output XML: \\n\");\n");
		filePrinter.print("printf(\"\\n%s\\n\", outbuffer);\n");
		filePrinter.indent--;
		filePrinter.print("}\n");
	}
	
	private void printInitXML(String mainFunctionName){
		filePrinter.print("void "+projectPrefix+"initXML(mxml_node_t* node, "+projectPrefix.substring(0,projectPrefix.length()-1)+"* me, char* instancename)" + "\n");
		filePrinter.print("{" + "\n");
			filePrinter.indent++;
			filePrinter.print("me->_simdata = mxmlNewElement( MXML_NO_PARENT, \"Instance\");" + "\n");
			filePrinter.print("mxml_node_t* childnode; // used as a temp node" + "\n");
			filePrinter.print("// Add to tree" + "\n");
			filePrinter.print("mxmlAdd(node, MXML_ADD_AFTER, NULL, me->_simdata);" + "\n");
			filePrinter.print("// Add constanty things);" + "\n");
			filePrinter.print("mxmlElementSetAttrf(me->_simdata, \"Name\", \"%s\", instancename);" + "\n");
			filePrinter.print("mxmlElementSetAttr(me->_simdata, \"Type\", \""+mainFunctionName.substring(0,mainFunctionName.length()-3)+"\");" + "\n");
			filePrinter.print("me->_simevents = mxmlNewElement(me->_simdata,\"Events\");" + "\n");
			filePrinter.print("me->_simvars = mxmlNewElement(me->_simdata,\"Vars\");" + "\n");
			//filePrinter.print("me->_simstate = mxmlNewElement(me->_simdata,\"ECState\");" + "\n");
			//filePrinter.print("me->_simtransitions = mxmlNewElement(me->_simdata,\"Transitions\");" + "\n");
			filePrinter.print("me->_simlines = mxmlNewElement(me->_simdata,\"Lines\");" + "\n");
			filePrinter.indent--;
		filePrinter.print("}"+ "\n");
	}
	private void printInitXML_OLD(String mainFunctionName){
		filePrinter.print("void PRETinitXML(mxml_node_t* node)" + "\n");
		filePrinter.print("{" + "\n");
			filePrinter.indent++;
			filePrinter.print(mainFunctionName+"_simdata = mxmlNewElement( MXML_NO_PARENT, \"Instance\");" + "\n");
			filePrinter.print("mxml_node_t* childnode; // used as a temp node" + "\n");
			filePrinter.print("// Add to tree" + "\n");
			filePrinter.print("mxmlAdd(node, MXML_ADD_AFTER, NULL, "+mainFunctionName+"_simdata);" + "\n");
			filePrinter.print("// Add constanty things" + "\n");
			filePrinter.print("mxmlElementSetAttrf("+mainFunctionName+"_simdata, \"Name\", \"%s\", \""+mainFunctionName+"\");" + "\n");
			filePrinter.print("mxmlElementSetAttr("+mainFunctionName+"_simdata, \"Type\", \""+mainFunctionName+"\");" + "\n");
			
			filePrinter.print(""+mainFunctionName+"_simvars = mxmlNewElement("+mainFunctionName+"_simdata,\"Vars\");" + "\n");
			filePrinter.print(""+mainFunctionName+"_simlines = mxmlNewElement("+mainFunctionName+"_simdata,\"Lines\");" + "\n");
			filePrinter.indent--;
		filePrinter.print("}"+ "\n");
	}
	String getNewTypeName_origTypeName = "";
	public String getNewTypeName(String oldTypeName, StatementNode n) {
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
				//System.out.println(getErrorInfo());
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
	public String getNewVariableName(String oldVarName, StatementNode n) {
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
			//System.out.println(getErrorInfo());
		
			System.exit(0);
		}else{
			System.out.println("Warning variable: "+oldVarName+ " not declared statement:");
		}
		return oldVarName;
	}
	private void printHandleTickCommand() {
		filePrinter.print("void handleTickCommand(mxml_node_t* tree, mxml_node_t* tickNode)" + "\n");
		filePrinter.print("{\n");
		filePrinter.indent++;
		
		filePrinter.print("mxml_node_t *var;"+ "\n");
		filePrinter.print("const char* nameAttr;"+ "\n");
		filePrinter.print("const char* valueAttr;"+ "\n");

		filePrinter.print("printf(\"Handle tick\\n\");"+ "\n");
    
		filePrinter.print("var = mxmlFindElement(tickNode, tree, \"Var\",NULL, NULL,MXML_DESCEND);"+ "\n");
		filePrinter.print("// Get input data"+ "\n");
		filePrinter.print("while( var != NULL )"+ "\n");
		filePrinter.print("{"+ "\n");
		filePrinter.indent++;
		filePrinter.print("if( strcmp(var->value.opaque, \"Var\") == 0 )"+ "\n");
        filePrinter.print("{"+ "\n");
            filePrinter.print("nameAttr = mxmlElementGetAttr ( var, \"Name\" );"+ "\n");
            filePrinter.print("valueAttr = mxmlElementGetAttr ( var, \"Value\" );"+ "\n");
            filePrinter.indent++;
				filePrinter.print("if( nameAttr != NULL && valueAttr != NULL)"+ "\n");
				filePrinter.print("{"+ "\n");
				filePrinter.indent++;
		for (Enumeration<ScopeNode> e = scopeList.elements();e.hasMoreElements();) {
			ScopeNode n = e.nextElement();
			//printer.print("//scope "+n.ID+"\n");
			for (Enumeration<String> e2 = n.variableMap.keys();e2.hasMoreElements();) {
				String variableName = e2.nextElement();
				StatementNode nDeclare = n.variableMap.get(variableName); //node of declared variable
				String newVariableName = getNewVariableName(variableName,nDeclare);
				if (nDeclare.type.equals("ReactiveOutput")) {
					//printer.print("//reactive Output\n");
				}else if (nDeclare.type.equals("ReactiveInput")) {
					String fbtype = "";
					String type = nDeclare.declaredType.get(0).replaceAll(" ","");
					
					if (type.contains("short")) {
						fbtype = "IEC_INT";
						if (type.contains("unsigned")) {
							fbtype = "IEC_UINT";
						}
					}else if (type.contains("int")) {
						fbtype = "IEC_DINT";
						if (type.contains("unsigned")) {
							fbtype = "IEC_UDINT";
						}
					}else if (type.contains("long")) {
						fbtype = "IEC_LINT";
						if (type.contains("unsigned")) {
							fbtype = "IEC_ULINT";
						}
					}else if (type.contains("float")) {
						fbtype = "IEC_REAL";
					}else if (type.contains("double")) {
						fbtype = "IEC_DREAL";
					}else if (type.contains("char*")){
						fbtype = "IIEC_STRING";
					}else if (type.contains("char")) {
						fbtype = "IEC_UINT";
					}else if (type.contains("bool")) {
						fbtype = "IEC_BOOL";
					}else{
						System.out.println("unknown type "+type);
						System.exit(0);
					}
					filePrinter.print("//reactive Input\n");
					filePrinter.print("if( stricmp(nameAttr, \""+variableName+"\") == 0 )\n");
					filePrinter.print("{\n");
					filePrinter.indent++;
						filePrinter.print("stringToVoid(valueAttr, "+fbtype+", 1, &"+newVariableName+");\n");
					filePrinter.indent--;	
					filePrinter.print("}\n");
				}else{
				
				}
				//printer.print("//"+variableName+" -> "+newVariableName+"\n");

			}
		}
		filePrinter.indent--;
		filePrinter.print("}\n");
		filePrinter.indent--;
		filePrinter.print("}\n");		
		filePrinter.print("var = var->next;\n");
		filePrinter.indent--;
		filePrinter.print("}\n");
		
		filePrinter.indent--;
		filePrinter.print("}\n");
		
		
	}
	private void printReadAndResponse(String mainFunctionName) {
    		filePrinter.print("if( node->value.opaque != NULL )"+"\n");
    		filePrinter.print("{"+"\n");
				filePrinter.indent++;
    			filePrinter.print("printf(\"%s\\n\", node->value.opaque);"+"\n");
    			filePrinter.print("if( stricmp(node->value.opaque,\"Tick\") == 0)"+"\n");
    			filePrinter.print("{"+"\n");
					filePrinter.indent++;
                    filePrinter.print("printf(\"Handling tick #%d\\n\", ++tickCount);"+"\n");
    				
    				filePrinter.print("handleTickCommand(tree, node);"+"\n");
    				filePrinter.print(mainFunctionName+"();\n");
    				
    				printXmlVariables(mainFunctionName);
    				//printOutputXml();
    				
    				filePrinter.print("// Respond!!!"+"\n");
    				
    				filePrinter.print("outsize = mxmlSaveString(outxml, outbuffer, sizeof(outbuffer),"+"\n");
    				filePrinter.print("	whitespace_cb);//MXML_NO_CALLBACK);"+"\n");
                    filePrinter.print("printf(\"Output XML: \\n\");"+"\n");
                    filePrinter.print("printf(\"\\n%s\\n\", outbuffer);"+"\n");
    				filePrinter.print("if( outsize > 0 ){"+"\n");
						filePrinter.indent++;
    				    filePrinter.print("// Send buffer over TCP"+"\n");
                        filePrinter.print("iResult = send( conn_s, outbuffer, outsize, 0 );"+"\n");
    		 			filePrinter.print("if (iResult == SOCKET_ERROR) {"+"\n");
							filePrinter.indent++;
							filePrinter.print("printf(\"send() failed with error: %d\\n\", WSAGetLastError());"+"\n");
							filePrinter.print("closesocket(conn_s);"+"\n");
							filePrinter.print("WSACleanup();"+"\n");
							filePrinter.print("return 1;"+"\n");
							filePrinter.indent--;
    					filePrinter.print("}"+"\n");
    				    filePrinter.print("printf(\"Sent: \\n\\n\\\"\\\"\\\"%s\\\"\\\"\\\"\\n\",outbuffer);"+"\n");
						filePrinter.indent--;
					filePrinter.print("}"+"\n");
					filePrinter.indent--;
    			filePrinter.print("}"+"\n");
    			filePrinter.print("else if( stricmp(node->value.opaque,\"Stop\") == 0)"+"\n");
    			filePrinter.print("{"+"\n");
					filePrinter.indent++;
    				filePrinter.print("printf(\"Stop command received. Exiting.\\n\");"+"\n");
    				filePrinter.print("exit(0);"+"\n");
					filePrinter.indent--;
    			filePrinter.print("}"+"\n");
			filePrinter.indent--;
    		filePrinter.print("}"+"\n");
    		filePrinter.print("if( node->next != NULL )"+"\n");
            filePrinter.print("{"+"\n");     
				filePrinter.indent++;
				filePrinter.print("printf(\"node %p, ->next %p != NULL\\n\", node, node->next);"+"\n");
    			filePrinter.print("node = node->next;"+"\n");
				filePrinter.indent--;
    		filePrinter.print("}else"+"\n");
				filePrinter.indent++;
    			filePrinter.print("break;"+"\n");
			filePrinter.indent--;
	}
	
	private void printXMLInit() {
		filePrinter.print("// Input:"+"\n");
		filePrinter.print("mxml_node_t *inxml = mxmlNewXML(\"1.0\");"+"\n");
		filePrinter.print("mxml_node_t *tree;"+"\n");
		filePrinter.print("mxml_node_t *node;"+"\n");
    
		filePrinter.print("// Output:"+"\n");
		filePrinter.print("mxml_node_t *outxml = mxmlNewXML(\"1.0\");"+"\n");
		filePrinter.print("mxml_node_t *tick = mxmlNewElement(outxml, \"Tick\");"+"\n");
	}
	private void printXMLClose() {
		filePrinter.print("WSACleanup();"+"\n");
	}
	private void printSocketInit() {
		filePrinter.print("int conn_s; /* connection socket */"+"\n");
		filePrinter.print("const short int port = 61495; /* port number */"+"\n");
		filePrinter.print("struct sockaddr_in servaddr;  /* socket address structure */"+"\n");
		filePrinter.print("char inbuffer[1024]; /* character buffer */"+"\n");
		filePrinter.print("int insize = 0;"+"\n");
		filePrinter.print("int tickCount = 0;"+"\n");
		filePrinter.print("// Declare and initialize variables"+"\n");
		filePrinter.print("WSADATA wsaData = {0};"+"\n");
		filePrinter.print("int iResult = 0;"+"\n");
		filePrinter.print("char outbuffer[10240]; // TODO: Malloc string as required"+"\n");
		filePrinter.print("int outsize = 0;"+"\n");
		filePrinter.print("FILE *fp, *outtest;"+"\n");

		filePrinter.print("// Initialize Winsock"+"\n");
		filePrinter.print("iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);"+"\n");
		filePrinter.print("if (iResult != 0) {"+"\n");
			filePrinter.indent++;
			filePrinter.print("printf(\"WSAStartup failed: %d\\n\", iResult);"+"\n");
			filePrinter.print("return 1;"+"\n");
			filePrinter.indent--;
		filePrinter.print("}"+"\n");
	}
	private void printSocketClose() {
		filePrinter.print("closesocket(conn_s);"+"\n");
	}
	private void printSocketConnect() {
		filePrinter.print("// Client socket"+"\n");
		filePrinter.print("if ( (conn_s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0 ) {"+"\n");
			filePrinter.indent++;
			filePrinter.print("fprintf(stderr, \"Simulator: Error creating listening socket: %d\\n\", WSAGetLastError());"+"\n");
			filePrinter.print("exit(EXIT_FAILURE);"+"\n");
			filePrinter.indent--;
		filePrinter.print("}"+"\n");
		filePrinter.print("//  Set all bytes in socket address structure to"+"\n");
		filePrinter.print("//  zero, and fill in the relevant data members"+"\n");
		filePrinter.print("memset(&servaddr, 0, sizeof(servaddr));"+"\n");
		filePrinter.print("servaddr.sin_family      = AF_INET;"+"\n");
		filePrinter.print("servaddr.sin_addr.s_addr = inet_addr( \"127.0.0.1\" );"+"\n");
		filePrinter.print("servaddr.sin_port        = htons(port);"+"\n");
		
		
		filePrinter.print("// Connect to server."+"\n");
		filePrinter.print("if ( connect( conn_s, (SOCKADDR*) &servaddr, sizeof(servaddr) ) == SOCKET_ERROR) {"+"\n");
			filePrinter.indent++;
			filePrinter.print("printf( \"Failed to connect: %d\\n\", WSAGetLastError());"+"\n");
			filePrinter.print("WSACleanup();"+"\n");
			filePrinter.print("return;"+"\n");
			filePrinter.indent--;
		filePrinter.print("}"+"\n");
		
		filePrinter.print("// Tell IDE"+"\n");
		filePrinter.print("outsize = mxmlSaveString(outxml, outbuffer, sizeof(outbuffer),"+"\n");
    	filePrinter.print("whitespace_cb);//MXML_NO_CALLBACK);"+"\n");
        filePrinter.print("// Send buffer over TCP"+"\n");
        filePrinter.print("iResult = send( conn_s, outbuffer, outsize, 0 );"+"\n");
    	filePrinter.print("if (iResult == SOCKET_ERROR) {"+"\n");
			filePrinter.indent++;
    	    filePrinter.print("printf(\"send() failed with error: %d\\n\", WSAGetLastError());"+"\n");
    		filePrinter.print("closesocket(conn_s);"+"\n");
    		filePrinter.print("WSACleanup();"+"\n");
    		filePrinter.print("return 1;"+"\n");
			filePrinter.indent--;
    	filePrinter.print("}"+"\n");
		filePrinter.print("printf(\"Sent: \\n\\n\\\"\\\"\\\"%s\\\"\\\"\\\"\\n\",outbuffer);"+"\n");
	}
	
	private void printWaitForCommand() {
		filePrinter.print("insize = recv(conn_s, inbuffer, 1024, 0);"+"\n");
        filePrinter.print("if( insize == 0 ){"+"\n");
			filePrinter.indent++;
            filePrinter.print("printf(\"Connection ended\\n\");"+"\n");
            filePrinter.print(" break; // tcp connection end"+"\n");
        filePrinter.print("}"+"\n");
        filePrinter.print("if( insize == SOCKET_ERROR ){"+"\n");
        	filePrinter.indent++;
			filePrinter.print("printf(\"recv() failed with error: %d\\n\", WSAGetLastError());"+"\n");
        	filePrinter.print("closesocket(conn_s);"+"\n");
            filePrinter.print("WSACleanup();"+"\n");
            filePrinter.print("return 1;"+"\n");
			filePrinter.indent--;
        filePrinter.print("}"+"\n");
    	filePrinter.print("inbuffer[insize] = '\\0';"+"\n");
    	filePrinter.print("printf(\"Got: %d bytes: \\n\\n\\\"\\\"\\\"%s\\\"\\\"\\\"\\n\",insize, inbuffer);"+"\n");
        filePrinter.print("clearChildren(inxml);"+"\n");
    	filePrinter.print("tree = mxmlLoadString(inxml, inbuffer, MXML_OPAQUE_CALLBACK ); // MXML_ELEMENT );"+"\n");
    	
    	filePrinter.print("if( tree->child == NULL )"+"\n");
    	filePrinter.print("{"+"\n");
			filePrinter.indent++;
    		filePrinter.print("printf(\"No xml commands found :(\\n\");"+"\n");
    		filePrinter.print("continue;"+"\n");
			filePrinter.indent--;
    	filePrinter.print("}"+"\n");
    	filePrinter.print("node = tree->child;"+"\n");
		filePrinter.print("printf(\"%s\\n\",node);"+"\n");
	
	}
	public void closeSimuFile() {
		if (timeMeSimulation) {
			filePrinter.close();
		}
	}
}