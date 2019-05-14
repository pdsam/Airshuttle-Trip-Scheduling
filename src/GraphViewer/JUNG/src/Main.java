public class Main {

	public static void main(String[] args) {
		int port = 7772;
		
		for (int i = 0; i<args.length; i++)
			if (args[i].equals("--port")) {
				i++;
				port = Integer.parseInt(args[i]);
			}
				
		Connection con = new Connection(port);
		Parser p = new Parser();
		while (true) {
			String msg = con.readLine();
			if (msg == null) 
				break;
						
			//System.out.println(msg);
			
			if (!p.parseString(msg))
				con.sendMsg("failed\n");
			else
				con.sendMsg("ok\n");
		}
	}

}
