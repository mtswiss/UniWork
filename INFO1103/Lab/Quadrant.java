class Quadrant
{
	public static void main(String[]args)	
	{
		int x= -5, y=1;
		
		if (x==0 && y==0)
			System.out.println("origin");	
		else if (x>0 && y>0)
			System.out.println("1st quadrant");
		else if (x<0 && y>0)
			System.out.println("2nd quadrant");	
		else if (x<0 && y<0)
			System.out.println("3rd quadrant");	
		else if (x>0 && y<0)
			System.out.println("4th quadrant");	
	}
}