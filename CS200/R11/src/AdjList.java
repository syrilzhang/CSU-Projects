import java.util.ArrayList;

public class AdjList {	
    // An AdjList is a (source, inDegree, dests) entry of a Graph 
    private String source;               // source node label
    private int inDegree;                // # nodes pointing at this node
    private ArrayList<String> dests;     // the list of destinations     

    public AdjList(String source) {

    }

    public int size(){
    	
    }
    
    public void incrInDegree(){

    }

    // add a dest **at end** of dest List
    public void addDest(String dest) {

    }

    // return true if dest in Dest List, false otherwise
    public boolean contains(String dest){

    }
    
    public String getSource(){

    }
    
    // get dest at index
    public String getDest(int index){
        if (index < 0 || index > dests.size())
            throw new IndexOutOfBoundsException(
                            "getDest index out of bounds");  
    }
    
    public String toString(){
    	return "AdjList source: " + source + 
    		   ", inDegree: " + inDegree + 
    		   ", destinations: " + dests;
    }

    public static void main(String[] args){
    	AdjList a1List = new AdjList("a1");
    	AdjList b2List = new AdjList("b2");
    	AdjList c2List = new AdjList("c2");    	
    	AdjList d3List = new AdjList("d3");
	
    	a1List.addDest("b2");
    	b2List.incrInDegree();
    	
    	a1List.addDest("c2");
    	c2List.incrInDegree();
    	    	
    	System.out.println(a1List);
    	System.out.println("aList contains c2: " + a1List.contains("c2"));
    	System.out.println("aList contains f7: " + a1List.contains("f7"));  

    	b2List.addDest("d3");
    	d3List.incrInDegree();

    	c2List.addDest("d3");   	
    	d3List.incrInDegree();
    }
 }