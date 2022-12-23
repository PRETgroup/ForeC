
public class TimeMeNotify {
	/**
	 * This is to replace the special character for XML for its equivalents
	 * @param input string
	 * @return string with special characters replaced
	 */
	public static String replaceSpecialChars(String input) {
		return input.replaceAll("&","&amp;") //& has to be first for will replaced others
					.replaceAll("<", "&lt;")
					.replaceAll(">", "&gt;")
					.replaceAll("\"", "&quot;")
					.replaceAll("'", "&apos;");
	}

	public static void notice(String blockID, String message) {
		message = replaceSpecialChars(message);
		blockID = replaceSpecialChars(blockID);
		System.out.println("<Notices>");
		System.out.println("<Notice>");
		System.out.println("<BlockID="+blockID+"/>");
		System.out.println("<Message="+message+"/>");
		System.out.println("</Notice>");
		System.out.println("</Notices>");

		
	}
}