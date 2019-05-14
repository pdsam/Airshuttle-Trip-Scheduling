import java.awt.Color;
import java.awt.Dimension;

import javax.swing.ImageIcon;

import edu.uci.ics.jung.graph.util.EdgeType;


public class Parser {
	GraphViewerController gvc;
	
	private boolean newGraph(String[] splitted) {
		if (splitted.length == 4) {
			Integer width, height;
			Boolean dynamic;
			try {
				width = Integer.parseInt(splitted[1]);
				height = Integer.parseInt(splitted[2]);
				dynamic = Boolean.parseBoolean(splitted[3]);
			}
			catch (Exception e) {
				return false;
			}
			gvc = new GraphViewerController(width, height, dynamic);
			return true;
		}
		return false;
	}
	
	private boolean createWindow(String[] splitted) {
		if (splitted.length == 3) {
			Integer width, height;
			try {
				width = Integer.parseInt(splitted[1]);
				height = Integer.parseInt(splitted[2]);
			}
			catch (Exception e) {
				return false;
			}
			gvc.createWindow(new Dimension(width, height));
			return true;
		}
		return false;
	}
	
	private boolean closeWindow(String[] splitted) {
		if (splitted.length == 1) {
			try {
				gvc.closeWindow();
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean addNode1(String[] splitted) {
		if (splitted.length == 2) {
			Integer id;
			try {
				id = Integer.parseInt(splitted[1]);
			}
			catch (Exception e) {
				return false;
			}
			gvc.addNode(id);
			return true;
		}
			
		return false;
	}
	
	private boolean addNode3(String[] splitted) {
		if (splitted.length == 4) {
			Integer id, x, y;
			try {
				id = Integer.parseInt(splitted[1]);
				x = Integer.parseInt(splitted[2]);
				y = Integer.parseInt(splitted[3]);
			}
			catch (Exception e) {
				return false;
			}
			gvc.addNode(id, x, y);
			return true;
		}
		return false;
	}
	
	private boolean addEdge(String[] splitted) {
		if (splitted.length == 5) {
			Integer id, v1, v2, ntype;
			EdgeType type;
			try {
				id = Integer.parseInt(splitted[1]);
				v1 = Integer.parseInt(splitted[2]);
				v2 = Integer.parseInt(splitted[3]);
				ntype = Integer.parseInt(splitted[4]);
			}
			catch (Exception e) {
				return false;
			}
			if (ntype == 1)
				type = EdgeType.DIRECTED;
			else
				type = EdgeType.UNDIRECTED;
			
			gvc.addEdge(id, v1, v2, type);

			return true;
		}
		return false;
	}

	private boolean removeNode(String[] splitted) {
		if (splitted.length == 2) {
			Integer id;
			try {
				id = Integer.parseInt(splitted[1]);
			}
			catch (Exception e) {
				return false;
			}
			gvc.removeNode(id);
			return true;
		}
			
		return false;
	}

	private boolean removeEdge(String[] splitted) {
		if (splitted.length == 2) {
			Integer id;
			try {
				id = Integer.parseInt(splitted[1]);
			}
			catch (Exception e) {
				return false;
			}
			gvc.removeEdge(id);
			return true;
		}
			
		return false;
	}
	
	private boolean setEdgeLabel(String[] splitted) {
		if (splitted.length>=3) {
			try {
				String str = new String();
				for (int i = 2; i<splitted.length; i++)
					str += " " + splitted[i];
				gvc.setEdgeLabel(Integer.parseInt(splitted[1]), str);
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean clearEdgeLabel(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.clearEdgeLabel(Integer.parseInt(splitted[1]));
			} catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean setVertexLabel(String[] splitted) {
		if (splitted.length>=3) {
			try {
				String str = new String();
				for (int i = 2; i<splitted.length; i++)
					str += " " + splitted[i];
				gvc.setVertexLabel(Integer.parseInt(splitted[1]), str);
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean clearVertexLabel(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.clearVertexLabel(Integer.parseInt(splitted[1]));
			} catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean defineEdgeColor(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.defineEdgeColor((Color)Class.forName("java.awt.Color").getField(splitted[1]).get(null));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean resetEdgeColor(String[] splitted) {
		if (splitted.length == 1) {
			gvc.resetEdgeColor();
			return true;
		}
		return false;
	}
	
	private boolean setEdgeColor(String[] splitted) {
		if (splitted.length == 3) {
			try {
				gvc.setEdgeColor(Integer.parseInt(splitted[1]), (Color)Class.forName("java.awt.Color").getField(splitted[2]).get(null));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean clearEdgeColor(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.clearEdgeColor(Integer.parseInt(splitted[1]));
			} catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean defineEdgeDashed(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.defineEdgeDashed(Boolean.parseBoolean(splitted[1]));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean setEdgeDashed(String[] splitted) {
		if (splitted.length == 3) {
			try {
				gvc.setEdgeDashed(Integer.parseInt(splitted[1]), Boolean.parseBoolean(splitted[2]));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean defineEdgeCurved(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.defineEdgeCurved(Boolean.parseBoolean(splitted[1]));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}

	private boolean setEdgeThickness(String[] splitted) {
		if (splitted.length == 3) {
			try {
				gvc.setEdgeThickness(Integer.parseInt(splitted[1]), Integer.parseInt(splitted[2]));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean defineVertexColor(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.defineVertexColor((Color)Class.forName("java.awt.Color").getField(splitted[1]).get(null));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean resetVertexColor(String[] splitted) {
		if (splitted.length == 1) {
			try {
				gvc.resetVertexColor();
			} catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean setVertexColor(String[] splitted) {
		if (splitted.length == 3) {
			try {
				gvc.setVertexColor(Integer.parseInt(splitted[1]), (Color)Class.forName("java.awt.Color").getField(splitted[2]).get(null));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean clearVertexColor(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.clearVertexColor(Integer.parseInt(splitted[1]));
			} catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean setVertexSize(String[] splitted) {
		if (splitted.length == 3) {
			try {
				gvc.setVertexSize(Integer.parseInt(splitted[1]), Integer.parseInt(splitted[2]));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean defineVertexSize(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.defineVertexSize(Integer.parseInt(splitted[1]));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean setVertexIcon(String[] splitted) {
		if (splitted.length == 3) {
			try {
				gvc.setVertexIcon(Integer.parseInt(splitted[1]), new ImageIcon(splitted[2]));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean clearVertexIcon(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.clearVertexIcon(Integer.parseInt(splitted[1]));
			} catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean defineVertexIcon(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.defineVertexIcon(new ImageIcon(splitted[1]));
			}
			catch (Exception e) {
				return false;
			}
			return true;
		}
		return false;
	}
	
	private boolean resetVertexIcon(String[] splitted) {
		if (splitted.length == 1) {
			gvc.resetVertexIcon();
			return true;
		}
		return false;
	}
	
	private boolean rearrange(String[] splitted) {
		if (splitted.length == 1) {
			gvc.rearrange();
			return true;
		}
		return false;
	}
	
	private boolean setBackground(String[] splitted) {
		if (splitted.length == 2) {
			try {
				gvc.setBackground(splitted[1]);
				return true;
			}
			catch (Exception e) {
				System.err.println("Can't load \""+splitted[1]+"\"");
				return false;
			}
		}
		return false;
	}
	
	private boolean clearBackground(String[] splitted) {
		if (splitted.length == 1) {
			gvc.clearBackground();
			return true;
		}
		return false;
	}
	
	public boolean parseString(String str) {
		String[] splitted = str.split(" ");
		if (splitted[0].equals("newGraph"))
			return newGraph(splitted);
		if (splitted[0].equals("createWindow"))
			return createWindow(splitted);
		if (splitted[0].equals("closeWindow"))
			return closeWindow(splitted);
		if (splitted[0].equals("addNode1"))
			return addNode1(splitted);
		if (splitted[0].equals("addNode3"))
			return addNode3(splitted);
		if (splitted[0].equals("addEdge"))
			return addEdge(splitted);
		if (splitted[0].equals("removeNode"))
			return removeNode(splitted);
		if (splitted[0].equals("removeEdge"))
			return removeEdge(splitted);
		if (splitted[0].equals("setEdgeLabel"))
			return setEdgeLabel(splitted);
		if (splitted[0].equals("clearEdgeLabel"))
			return clearEdgeLabel(splitted);
		if (splitted[0].equals("setVertexLabel"))
			return setVertexLabel(splitted);
		if (splitted[0].equals("clearVertexLabel"))
			return clearVertexLabel(splitted);
		if (splitted[0].equals("defineEdgeColor"))
			return defineEdgeColor(splitted);
		if (splitted[0].equals("resetEdgeColor"))
			return resetEdgeColor(splitted);
		if (splitted[0].equals("setEdgeColor"))
			return setEdgeColor(splitted);
		if (splitted[0].equals("clearEdgeColor"))
			return clearEdgeColor(splitted);
		if (splitted[0].equals("defineEdgeDashed"))
			return defineEdgeDashed(splitted);
		if (splitted[0].equals("setEdgeDashed"))
			return setEdgeDashed(splitted);
		if (splitted[0].equals("defineEdgeCurved"))
			return defineEdgeCurved(splitted);
		if (splitted[0].equals("setEdgeThickness"))
			return setEdgeThickness(splitted);
		if (splitted[0].equals("defineVertexColor"))
			return defineVertexColor(splitted);
		if (splitted[0].equals("resetVertexColor"))
			return resetVertexColor(splitted);
		if (splitted[0].equals("setVertexColor"))
			return setVertexColor(splitted);
		if (splitted[0].equals("clearVertexColor"))
			return clearVertexColor(splitted);
		if (splitted[0].equals("defineVertexSize"))
			return defineVertexSize(splitted);
		if (splitted[0].equals("setVertexSize"))
			return setVertexSize(splitted);
		if (splitted[0].equals("defineVertexIcon"))
			return defineVertexIcon(splitted);
		if (splitted[0].equals("resetVertexIcon"))
			return resetVertexIcon(splitted);
		if (splitted[0].equals("setVertexIcon"))
			return setVertexIcon(splitted);
		if (splitted[0].equals("clearVertexIcon"))
			return clearVertexIcon(splitted);
		if (splitted[0].equals("setBackground"))
			return setBackground(splitted);
		if (splitted[0].equals("clearBackground"))
			return clearBackground(splitted);
		if (splitted[0].equals("setEdgeWeight"))
			return setEdgeWeight(splitted);
		if (splitted[0].equals("setEdgeFlow"))
			return setEdgeFlow(splitted);
		if (splitted[0].equals("rearrange"))
			return rearrange(splitted);
		return false;
	}

	private boolean setEdgeFlow(String[] splitted) {
		if (splitted.length == 3) {
			try {
				gvc.setEdgeWeight(Integer.parseInt(splitted[1]), Integer.parseInt(splitted[2]));
				return true;
			}
			catch (Exception e) {
				return false;
			}
		}
		return false;
	}

	private boolean setEdgeWeight(String[] splitted) {
		if (splitted.length == 3) {
			try {
				gvc.setEdgeFlow(Integer.parseInt(splitted[1]), Integer.parseInt(splitted[2]));
				return true;
			}
			catch (Exception e) {
				return false;
			}
		}
		return false;
	}
}
