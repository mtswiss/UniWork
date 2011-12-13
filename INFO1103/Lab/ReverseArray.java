class ReverseArray
{
	public static void main(String[]args)	
	{
	int [] array = new int[args.length];
	int [] answer = new int[args.length];

			for(int i=0;i<array.length;i++)
			{
				array[i] = Integer.parseInt(args[i]);
			}
			for(int i=args.length-1; i>=0;i--)
			{
			System.out.println(array[i]);
			}
	}	
		
		

}