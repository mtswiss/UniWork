public class Text1 
{

    public static void main(String[] args)
    {
    	for (int i = 0; i < 5; i++)
			{
			int j = 7 - i;
				if (j % 3 == 0)
					{
					System.out.println("i: "+i + ", j: " + j);
					}
				else
					{
					i++;
					}
			}
    }
       
    
}