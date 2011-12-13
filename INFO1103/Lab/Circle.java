
class Circle extends Shape
//	circle is a shape; circle inherits from shape
 
{
//intance variables
    private double r;	//radius
    
//consants
	public static final double PI=3.14159
		
//constructor
	public Circle(double x, double y, double r)
	{
		super(x,y);
/*
 *	call the superconstructor
 *	(constructor in super class);
 *	must be in 1st line in constructor
 */
		this.r=r;	
	}		

//instance methods

	public double getArea()
	{
		return PI*r*r;
	}
	/*
	 *	This method overrides the method getArea()
	 *	in the Shape class.
	 */
}