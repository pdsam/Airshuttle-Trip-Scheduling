import java.awt.BasicStroke;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Paint;
import java.awt.Shape;
import java.awt.Stroke;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;
import java.util.HashMap;

import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JRootPane;

import org.apache.commons.collections15.Transformer;
import org.apache.commons.collections15.functors.ChainedTransformer;

import edu.uci.ics.jung.algorithms.layout.AbstractLayout;
import edu.uci.ics.jung.algorithms.layout.FRLayout;
import edu.uci.ics.jung.algorithms.layout.Layout;
import edu.uci.ics.jung.algorithms.layout.StaticLayout;
import edu.uci.ics.jung.algorithms.layout.util.Relaxer;
import edu.uci.ics.jung.algorithms.layout.util.VisRunner;
import edu.uci.ics.jung.algorithms.util.IterativeContext;
import edu.uci.ics.jung.graph.Graph;
import edu.uci.ics.jung.graph.ObservableGraph;
import edu.uci.ics.jung.graph.SparseMultigraph;
import edu.uci.ics.jung.graph.util.EdgeType;
import edu.uci.ics.jung.visualization.Layer;
import edu.uci.ics.jung.visualization.VisualizationViewer;
import edu.uci.ics.jung.visualization.control.DefaultModalGraphMouse;
import edu.uci.ics.jung.visualization.decorators.AbstractVertexShapeTransformer;
import edu.uci.ics.jung.visualization.decorators.EdgeShape;
import edu.uci.ics.jung.visualization.layout.LayoutTransition;
import edu.uci.ics.jung.visualization.renderers.Renderer;
import edu.uci.ics.jung.visualization.util.Animator;

public class GraphViewerController extends javax.swing.JApplet {

	private static final long serialVersionUID = -3144451891978329262L;

	JFrame frame;

	private Graph<Number,Number> g = null;
	private VisualizationViewer<Number,Number> vv = null;
	private AbstractLayout<Number,Number> layout = null;

	private Dimension graphDimension = null;

	private boolean isDynamic;

	private HashMap<Integer, Point2D> coords;

	private HashMap<Number, String> edgeLabels;

	private HashMap<Number, Number> edgeWeights;
	private HashMap<Number, Number> edgeFlows;
	private HashMap<Number, String> edgeCaptions;

	private HashMap<Number, String> vertexLabels;

	private HashMap<Number, Integer> vertexSizes;
	private Integer definedVertexSize;

	private HashMap<Number, Icon> vertexIcons;
	private Icon definedVertexIcon;

	private Color definedEdgeColor;
	private HashMap<Number, Color> edgeColors;
	private HashMap<Number, Integer> edgeThickness;

	private boolean defineEdgeCurved;
	private Boolean definedEdgeDashed;
	private HashMap<Number, Boolean> edgeStrokeDashed;

	private final Stroke defaultEdgeStroke;
	private final Stroke dashedEdgeStroke;
	private final float dash[] = {10.0f};

	private Color definedVertexColor;
	private HashMap<Number, Color> vertexColors;

	private ImageIcon backgroundIcon = null;


	public GraphViewerController(int width, int height, boolean isDynamic) {
		graphDimension = new Dimension(width, height);
		this.isDynamic = isDynamic;

		coords = new HashMap<Integer, Point2D>();
		edgeLabels = new HashMap<Number, String>();
		edgeWeights = new HashMap<Number, Number>();
		edgeFlows = new HashMap<Number, Number>();
		edgeCaptions = new HashMap<Number, String>();
		vertexLabels = new HashMap<Number, String>();
		edgeColors = new HashMap<Number, Color>();
		edgeThickness = new HashMap<Number, Integer>();
		definedEdgeColor = Color.black;

		defineEdgeCurved = true;
		definedEdgeDashed = false;
		edgeStrokeDashed = new HashMap<Number, Boolean>();
		defaultEdgeStroke = new BasicStroke();
		dashedEdgeStroke = new BasicStroke(1.0f, BasicStroke.CAP_BUTT,
				BasicStroke.JOIN_MITER, 10.0f, dash, 0.0f);


		vertexColors = new HashMap<Number, Color>();
		definedVertexColor = Color.yellow;

		vertexSizes = new HashMap<Number, Integer>();
		definedVertexSize = 20;

		vertexIcons = new HashMap<Number, Icon>();
		definedVertexIcon = null;
	}

	private final static class VertexShapeSizeAspect<V,E>
	extends AbstractVertexShapeTransformer <V>
	implements Transformer<V,Shape>  {

		public VertexShapeSizeAspect(final HashMap<Number, Integer> vertexSizes,
				final Integer definedVertexSize)
		{
			setSizeTransformer(new Transformer<V,Integer>() {
				public Integer transform(V v) {
					Integer size = vertexSizes.get(v);
					if(size != null)
						return size;

					return definedVertexSize;
				}});
		}

		public Shape transform(V v)
		{
			return factory.getEllipse(v);
		}
	}

	public void init(Dimension windowSize) {
		//create a graph
		Graph<Number,Number> ig = new SparseMultigraph<Number, Number>();
		ObservableGraph<Number,Number> og = new ObservableGraph<Number,Number>(ig);
		this.g = og;

		Layout<Number,Number> staticLayout;

		//create a graphdraw
		if (isDynamic) {
			layout = new FRLayout<Number,Number>(g);
			layout.setSize(graphDimension);
			Relaxer relaxer = new VisRunner((IterativeContext)layout);
			relaxer.stop();
			relaxer.prerelax();

			staticLayout = new StaticLayout<Number,Number>(g, layout);
		}
		else {
			staticLayout = new StaticLayout<Number,Number>(g, 
					new ChainedTransformer<Number, Point2D>(new Transformer[]{new CoordsTransformer(coords)}));
		}


		vv = new VisualizationViewer<Number,Number>(staticLayout, windowSize);

		if(backgroundIcon != null) {
			vv.addPreRenderPaintable(new VisualizationViewer.Paintable(){
				public void paint(Graphics g) {
					if (backgroundIcon != null) {
						Graphics2D g2d = (Graphics2D)g;
						AffineTransform oldXform = g2d.getTransform();
						AffineTransform lat = 
								vv.getRenderContext().getMultiLayerTransformer().getTransformer(Layer.LAYOUT).getTransform();
						AffineTransform vat = 
								vv.getRenderContext().getMultiLayerTransformer().getTransformer(Layer.VIEW).getTransform();
						AffineTransform at = new AffineTransform();
						at.concatenate(g2d.getTransform());
						at.concatenate(vat);
						at.concatenate(lat);
						g2d.setTransform(at);
						g.drawImage(backgroundIcon.getImage(), 0, 0,
								backgroundIcon.getIconWidth(),backgroundIcon.getIconHeight(),vv);
						g2d.setTransform(oldXform);
					}
				}
				public boolean useTransform() { return false; }
			});
		}

		// edge labels
		Transformer<Number,String> edgesLabeler = new Transformer<Number,String>(){
			public String transform(Number e) {
				String str = edgeLabels.get(e);
				if (str != null)
					return str;
				else return "";
			}
		};
		vv.getRenderContext().setEdgeLabelTransformer(edgesLabeler);

		// vertex labels
		Transformer<Number,String> vertexesLabeler = new Transformer<Number,String>(){
			public String transform(Number v) {
				String str = vertexLabels.get(v);
				if (str != null)
					return str;
				else return "";
			}
		};
		vv.getRenderContext().setVertexLabelTransformer(vertexesLabeler);  
		vv.getRenderer().getVertexLabelRenderer().setPosition(Renderer.VertexLabel.Position.N); 

		//edge colors
		Transformer<Number, Paint> edgePaintTransformer =
				new Transformer<Number, Paint>() {
			public Paint transform(Number e) {
				Color c = edgeColors.get(e);
				if (c != null)
					return c;
				else return definedEdgeColor;
			}
		};

		vv.getRenderContext().setEdgeDrawPaintTransformer(edgePaintTransformer);

		//vertex sizes
		VertexShapeSizeAspect<Number,Number> vertexSizeTransformer =
				new VertexShapeSizeAspect<Number,Number>(vertexSizes, definedVertexSize);
		vv.getRenderContext().setVertexShapeTransformer(vertexSizeTransformer);

		//vertex icons
		Transformer<Number, Icon> vertexIconTransformer = new Transformer<Number, Icon>() {
			public Icon transform(Number v) {
				Icon icon = vertexIcons.get(v);

				if(icon != null)
					return icon;

				return definedVertexIcon;
			}
		};
		vv.getRenderContext().setVertexIconTransformer(vertexIconTransformer);

		//vertex colors
		Transformer<Number,Paint> vertexPaintTransformer = 
				new Transformer<Number,Paint>(){
			public Paint transform(Number v) {
				Color c = vertexColors.get(v);
				if (c != null)
					return c;
				else return definedVertexColor;
			}
		};
		vv.getRenderContext().setVertexFillPaintTransformer(vertexPaintTransformer);


		/*
		 * This does not work, refreshEdgeShape() workaround used instead
		 * 
		Transformer<Context<Graph<Number, Number>, Number>, Shape> edgeShapeTransformer =
				new Transformer<Context<Graph<Number,Number>,Number>,Shape>(){
			public Shape transform(Context<Graph<Number, Number>, Number> graphStringContext) {
				return (new Line2D.Double());
			}
		};
		vv.getRenderContext().setEdgeShapeTransformer(edgeShapeTransformer);
		 */
		refreshEdgeShape();

		//edge thickness and dashed
		Transformer<Number, Stroke> edgeStrokeTransformer =
				new Transformer<Number, Stroke>() {
			public Stroke transform(Number e) {
				Integer t = edgeThickness.get(e);
				Boolean dashed = edgeStrokeDashed.get(e);

				if(dashed == null) {
					dashed = definedEdgeDashed;
				}

				if (t != null) {
					if(!dashed)
						return new BasicStroke(t.floatValue());
					else
						return new BasicStroke(t.floatValue(), BasicStroke.CAP_BUTT,
								BasicStroke.JOIN_MITER, 10.0f, dash, 0.0f);
				}

				if(dashed)
					return dashedEdgeStroke;

				return defaultEdgeStroke;
			}
		};
		vv.getRenderContext().setEdgeStrokeTransformer(edgeStrokeTransformer);


		JRootPane rp = this.getRootPane();
		rp.putClientProperty("defeatSystemEventQueueCheck", Boolean.TRUE);

		getContentPane().setLayout(new BorderLayout());
		getContentPane().setBackground(java.awt.Color.lightGray);
		getContentPane().setFont(new Font("Serif", Font.PLAIN, 12));

		vv.setGraphMouse(new DefaultModalGraphMouse<Number,Number>());

		//vv.setForeground(Color.white);

		vv.addComponentListener(new ComponentAdapter() {
			/**
			 * @see java.awt.event.ComponentAdapter#componentResized(java.awt.event.ComponentEvent)
			 */
			@Override
			public void componentResized(ComponentEvent arg0) {
				super.componentResized(arg0);
				if (isDynamic)
					layout.setSize(arg0.getComponent().getSize());
			}});

		getContentPane().add(vv);
	}

	static class CoordsTransformer implements Transformer<Integer,Point2D> {
		private HashMap<Integer, Point2D> map;

		public CoordsTransformer(HashMap<Integer, Point2D> map) {
			this.map = map;
		}

		public Point2D transform(Integer val) {
			return map.get(val);
		}

	}

	public void createWindow(Dimension windowSize) {
		frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().add(this);
		init(windowSize);
		frame.pack();
		frame.setVisible(true);
	}

	public void closeWindow() {
		frame.setVisible(false);
	}

	public void refreshEdgeShape() {
		/*
		 * Ideally, this should not be a function
		 * scattered around other functions, but
		 * a custom EdgeShapeTransformer in init(...)
		 */

		if(defineEdgeCurved)
			vv.getRenderContext().setEdgeShapeTransformer(
					new EdgeShape.QuadCurve<Number,Number>());
		else
			vv.getRenderContext().setEdgeShapeTransformer(
					new EdgeShape.Line<Number,Number>());
	}

	public void rearrange() {
		refreshEdgeShape();

		if (isDynamic) {
			layout.initialize();
			Relaxer relaxer = new VisRunner((IterativeContext)layout);
			relaxer.stop();
			relaxer.prerelax();
			StaticLayout<Number,Number> staticLayout =
					new StaticLayout<Number,Number>(g, layout);
			LayoutTransition<Number,Number> lt =
					new LayoutTransition<Number,Number>(vv, vv.getGraphLayout(),
							staticLayout);
			Animator animator = new Animator(lt);
			animator.start();
		}

		vv.repaint();
	}

	public void addEdge(int id, int v1, int v2, EdgeType type) {
		g.addEdge(id, v1, v2, type);
	}

	public void removeEdge(int k) {
		g.removeEdge(k);
		edgeLabels.remove(k);
		edgeColors.remove(k);
		edgeWeights.remove(k);
		edgeFlows.remove(k);
		edgeCaptions.remove(k);
		edgeThickness.remove(k);
	}

	public void addNode(int k, int x, int y) {
		coords.put(k, new Point2D.Double(x, y));
		g.addVertex(k);
	}

	public void removeNode(int k) {
		g.removeVertex(k);
		coords.remove(k);
		vertexLabels.remove(k);
		vertexColors.remove(k);
	}

	public void addNode(int k) {
		g.addVertex(k);
	}

	public void setEdgeWeight(int k, int weight) {
		edgeWeights.put(k, weight);
		updateEdgeLabel(k);
	}

	public void setEdgeFlow(int k, int flow) {
		edgeFlows.put(k, flow);
		updateEdgeLabel(k);
	}

	public void setEdgeLabel(int k, String label) {
		edgeCaptions.put(k, label);
		updateEdgeLabel(k);
	}

	public void clearEdgeLabel(int k) {
		edgeCaptions.remove(k);
		updateEdgeLabel(k);
	}

	public void updateEdgeLabel(int k) {
		Number weight, flow;
		String caption, label;
		label = new String();
		weight = edgeWeights.get(k);
		flow = edgeFlows.get(k);
		caption = edgeCaptions.get(k);

		if(weight != null)
			label += "w: " + weight;
		if(flow != null)
			label += " f: " + flow;
		if(caption != null)
			label += " " + caption;

		edgeLabels.put(k, label);
	}

	public void setVertexLabel(int k, String label) {
		vertexLabels.put(k, label);
	}

	public void clearVertexLabel(int k) {
		vertexLabels.remove(k);
	}

	public void defineEdgeColor(Color c) {
		definedEdgeColor = c;
	}

	public void resetEdgeColor() {
		definedEdgeColor = Color.black;
	}

	public void setEdgeColor(int k, Color c) {
		edgeColors.put(k, c);
	}

	public void clearEdgeColor(int k) {
		edgeColors.remove(k);
	}

	public void defineEdgeDashed(Boolean dashed) {
		definedEdgeDashed = dashed;
	}

	public void setEdgeDashed(int k, Boolean dashed) {
		edgeStrokeDashed.put(k, dashed);
	}

	public void defineEdgeCurved(boolean curved) {
		defineEdgeCurved = curved;
	}

	public void setEdgeThickness(int k, int thickness) {
		edgeThickness.put(k, thickness);
	}

	public void defineVertexColor(Color c) {
		definedVertexColor = c;
	}

	public void resetVertexColor() {
		definedVertexColor = Color.yellow;
	}

	public void setVertexColor(int k, Color c) {
		vertexColors.put(k, c);
	}

	public void clearVertexColor(int k) {
		vertexColors.remove(k);
	}

	public void defineVertexSize(int size) {
		definedVertexSize = size;
	}

	public void setVertexSize(int k, int size) {
		vertexSizes.put(k, size);
	}

	public void defineVertexIcon(Icon icon) {
		definedVertexIcon = icon;
	}

	public void resetVertexIcon() {
		definedVertexIcon = null;
	}

	public void setVertexIcon(int k, Icon icon) {
		vertexIcons.put(k, icon);
	}

	public void clearVertexIcon(int k) {
		vertexIcons.remove(k);
	}

	public void setBackground(String path) {
		backgroundIcon = new ImageIcon(path);
	}

	public void clearBackground() {
		backgroundIcon = null;
	}
}
