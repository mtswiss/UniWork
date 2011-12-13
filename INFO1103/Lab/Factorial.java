public class Factorial
{

    public static void main(String[] args)
    {
    	int n=4;
    	int m=n;
    	int value=n;
    	
    	while (n>1)
    	{
    		value=value*(m-1);
    		m=n-1;
    	}
    	System.out.println(n+"!="+value);
    		
    }	
    
 
    
    
}