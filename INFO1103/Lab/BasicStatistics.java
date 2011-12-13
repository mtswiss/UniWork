class BasicStatistics

	public static void main(String[]args)	
	{
	double [] array = new double[7];

			for(int i=0;i<array.length;i++)
			{
				array[i] = Double.parseDouble(args[i]);
			}
			double sum = array[0];
			double min = array[0];
			double max = array[0];
			for(int i=1; i<array.length;i++)
			{
				if(array[i]<min)
				min==array[i];
			}
	}	
		
		

}