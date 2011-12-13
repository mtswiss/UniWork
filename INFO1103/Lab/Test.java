
public class Test 
{

    public static void main (String[] args) 
    {
    	Shape[] shapes = new Shape[2];
    	shapes[0] = new Rectable(...);
    	shapes[1] = new Circle(...);
    	
    	for(int i=0;i<shapes.length;i++)
    	
    	System.out.println(shapes[i].getArea());
    	/*	
    	 *	POLYMORPHISM
    	 *	the specific method getArea()
    	 *	is called depending on the specific
    	 *	type (dynamic type, or specific shape)
    	 */
    }
}