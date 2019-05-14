import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;


public class Connection {
	Socket clientSocket = null;	
	BufferedReader in;
	PrintWriter out;
	
	public Connection(int port) {
		ServerSocket serverSocket;
		
		try {
		    serverSocket = new ServerSocket(port);
		    clientSocket = serverSocket.accept();
			in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
	        out = new PrintWriter(clientSocket.getOutputStream(), true);
		} catch (IOException e) {
			e.printStackTrace();
		    System.out.println("Could not listen on port: " + port);
		    System.exit(-1);
		}
		
	}

	public String readLine() {
		try {
			return in.readLine();
		} catch (IOException e) {
			System.exit(0);
		}
		return null;
	}
	
	public void sendMsg(String msg) {
		out.print(msg);
		out.flush();
	}
}
