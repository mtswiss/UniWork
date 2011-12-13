

import java.util.*;
import java.io.*;
 
public class Jars 
{
	public static void main(String[] args) 
		{
		// create arrays of attributes of the items in the jar, including
		// names, prices, and sizes of the items
		String[] itemStored = {"Nails", "Lollies", "Lollies", "Pebbles", "Pins"}; // the names of the items in the jar
		int[] numberOfItems = {104, 57, 62, 2367, 322};  // the number of items stored in the jar
		double[] pricePerItem = {0.26, 0.53, 0.78, 0.01, 0.11}; // the price per item in the jar
		
		

		
		/*
		 * Question 1: re-set these three arrays with interactive inputs from
		 * keyboard by using Scanner class
		 * 
		 * your code goes below
		 */

		Scanner s = new Scanner(System.in);
		System.out.println("enter the items: attributes of name, price, and size:");
		
		for (int i=0; i<itemStored.length; i++)
		{
		System.out.println("new item");
		itemStored[i] = s.next();
		System.out.println("new price");
		pricePerItem[i] = s.nextDouble();
		System.out.println("new number");
		numberOfItems[i] = s.nextInt();
		}
		
		
		
		/*
		 * Question 2: display the items by using System.out.printf() method on
		 * the screen as the format: itemNo itemname quantity  $price
		 * 1   Nails       104     $0.26 
		 * 2   Lollies     57      $0.53
		 * 3   Lollies     62      $0.78 
		 * 4   Pebbles     2367    $0.01 
		 * 5   Pins        322     $0.11 
		 * 
		 * 
		 * Your code goes below
		 */
		
		for (int i = 0; i<itemStored.length;i++)
		{
		int number = i+1
		System.out.printf(number /t %s /t %d /t %4.2f, itemStored[i], numberOfItems[i], pricePerItems[i]);
		}

		// sample outputs of method calls
		System.out.println("Average price per item: $" + averagePrice(pricePerItem));
		
		System.out.println("ITEM WITH BIGGEST TOTAL VALUE:");
		displayMaxValue(itemStored, numberOfItems, pricePerItem);
		}
	
	public static double averagePrice(double[] pricePerItem)
		{
			return 0; // ###			
		} 
		
	public static void displayMaxValue(String[] itemStored, int[] numberOfItems, double[] pricePerItem)
		{
			//###
		}
	
	/** Q3. define a method to calculate the average price per item. */
	

	
	/** Q4. define a method to find and display the item with biggest total value */
}