
abstract class Shape 
/*	
 *	It doesn't make sense to
 *	create a specific object of
 *	this type, it only makes sense
 *	to create an object of a more specific type (subclass).
 */
 
{
//intance variables
    protected double x;	//center coordinates
    protected double y;
/*
 *	Only subclass can see it.
 */
    
//constructor
	protected Shape(double x,double y)
	{
		this.x=x;
		this.y=y;
	}

//instance methods

	public abstract double getArea();
/*	
 *	It doesn't make sense to write the
 *	method body (code, or implementation) now
 *	because we need to know info 
 *	from more specific classes (subclasses).
 */
	
}