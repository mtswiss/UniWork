package pirm;
import java.util.*;

import java.io.*;

/*We need different arrays for the different characteristics for each food.
 * For example, we need an array for the quantity, the price of each food.
 * Instead of have arrays, we can have an object for each food. 
 * Inside each object, we can have different characteristics for that food. 
 */

public class PIRM 
{
	private static int[] dateDay = new int[7];	
	private static int[] dateMonth = new int[7];
	private static int[] dateYear = new int[7];
	
	private static String[] type = new String[7];
	
	private static int[] useByDay = new int[7];
	private static int[] useByMonth = new int[7];
	private static int[] useByYear = new int[7];

	private static int[] quantity = new int[7];
	
	private static String[] name = new String[8];
		

	public static void main(String[] args)
	{
	
		try 
		{
			//Take data from files food.txt and people.txt and save them as arrays. 
			
			String filename = "foods.txt";
			File f = new File(filename);
			
			Scanner s = new Scanner(f);
			while (s.hasNext())
			{
				String food = s.next();
				System.out.println(food);
			}
		
		}
		catch (Exception e)
		{
		System.out.println("Exception caught "+e.getMessage());
		}
		try 
		{
			String filename2 = "people.txt";
			File g = new File(filename2);
			
			Scanner s = new Scanner(g);
			while (s.hasNext())
			{
				String people = s.next();
				System.out.println(people);
			}
		
		}
		catch (Exception e)
		{
		System.out.println("Exception caught "+e.getMessage());
		}
	
		Scanner keyboard = new Scanner(System.in);			//set keyboard as scanned object
		System.out.println("type action, e.g. eat 20-03-07 milk 2 Chris");
		String userInput = keyboard.next(); 				//scans the whole line, which is then scanned separately 
		Scanner scanInput = new Scanner(userInput);			//sets scanner to what the user just wrote
		scanInput.useDelimiter(" ");						//tell the scanner to stop after every " "
		
		while (true)										//create loop so the user can input a few commands
		{
		String command = scanInput.next();					//saves command
		String date = scanInput.next();						//saves bought date to 3 different int 
			Scanner scanBoughtDate = new Scanner(date);
			scanBoughtDate.useDelimiter("-");
			int dateDay = scanBoughtDate.nextInt();
			int dateMonth = scanBoughtDate.nextInt();
			int dateYear = scanBoughtDate.nextInt();
			// Loop forever, since the user can type as many commands as they like
		
		if (command.equals("QUIT"))
					break;
		

		if (command.equals("buy"))							//set different actions for the different commands
		{
			String type = scanInput.next();					//saves food
			String useByDate = scanInput.next();			//saves the use by date to 3 different int
				Scanner scanUseBy = new Scanner(useByDate);
				scanUseBy.useDelimiter("-");
				int useByDay = scanUseBy.nextInt();
				int useByMonth = scanUseBy.nextInt();
				int useByYear = scanUseBy.nextInt();
				int quantity = scanInput.nextInt();			//saves the quantity
			double cost = scanInput.nextDouble();			//saves the cost



			buy(dateDay, dateMonth, dayYear, type, useByDayte, useByMonth, quantity, name, price);	//call buy method with these variables
				
		}
		else if (command.equals("eat"))
		{
			String type = scanInput.next();					//saves food
			int quantity = scanInput.nextInt();				//saves quantity
			String name = scanInput.next();					//saves person who ate
			
			eat(dateDay, dateMonth, dateYear, type, quantity, name);	//call eat method with these variables

		}
		else if (command.equals("discard"))
		{
			String type = scanInput.next();					//saves type
			int quantity = scanInput.nextInt();				//saves quantity

			
			discard(dateDay,dateMonth, dateYear, type, quantity);		//call discard method with these variables
			
		}
		else if (command.equals("query"))
		{
			String type = scanInput.next();					
			String name = scanInput.next();
			
			// i want to call methods but i do not know how to call different methods from one "if" command. 
		}	
		}
				
	}
			
	public static String buy(int[] dateDay, int[] dateMonth, int[] dayYear, String[] type, int[] useByDay, int[] useByMonth, int[] useByYear, int[] quantity, String[] name, double[] cost)
	{
		System.out.println("you bought...");
		 return "";
		 // ###			
	} 
	public static String eat(int[] dateDay, int[] dateMonth, int[] dayYear, String[] type, int[] quantity, String[] name)
	{
		System.out.println("you ate...");
		return "";
		// ###			
	} 
	public static String discard(int[] dateDay, int[] dateMonth, int[] dayYear, String[] type, int[] quantity)
	{
		System.out.println("you need to discard...");
		return ""; 
		// ###			
	} 
	public static String query(int[] dateDay, int[] dateMonth, int[] dayYear)
	{
		System.out.println("these are the articles in the fridge, with the useby dates and quantities");
		return "";
		// ###			
	}
	public static String queryDate(int[] dateDay, int[] dateMonth, int[] dayYear, String[] type)
	{
		System.out.println("the next use by date is... and it cost");
		return "";
		//###
	}
	public static String queryDateType(int[] dateDay, int[] dateMonth, int[] dayYear, String[] type, String[] name)
	{
		System.out.println("this is what ... eat and what is cost ...");
		return "";
	}
}