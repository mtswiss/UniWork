
public class Test2 
{

    public static void main (String[] args) 
    {
    	int [] x=new int[2];
    	x[0]=9;
    	x[1]=3;
    	doSomething(x);
    	for(int i=0;i<x.length;i++)
    	{
    	System.out.println(x);
    	}
    }
    
    public static void doSomething(int[] numbers)
    {
    	for(int i=0;i<numbers.length;i++)
    	{
    	numbers[i]++;
  		}
    
	}
}