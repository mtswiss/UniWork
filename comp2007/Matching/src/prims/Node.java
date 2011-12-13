package prims;

public class Node implements Comparable<Node>{
	int id;
	int value;
	public Node(int value, int id){
		this.value = value;
		this.id = id;
	}
	
	public int compareTo(Node n){
		if(n.value>this.value)
			return -1;
		else if(n.value<this.value)
			return 1;
		else
			return 0;
	}
}



// 