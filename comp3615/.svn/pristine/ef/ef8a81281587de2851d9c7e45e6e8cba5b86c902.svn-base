using System;
using System.Data;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;


// This will be the file that will do the parsing of the text file. The main idea that this will be an arraylist and the array list will contain a Hashtable.
namespace Text_Parser
{
    class Parser
    {
        public Parser()
        {}
        //This will contain the data in parsed form.

        public static System.Array resizeArray(System.Array oldArray, int newSize)  // this function will resize our temporary string array that is used to store the parsed Line.
        {
            int oldSize = oldArray.Length;
            System.Type elementType = oldArray.GetType().GetElementType();
            System.Array newArray = System.Array.CreateInstance(elementType, newSize);
            return newArray;
        }
        public void parseFileToDataSet(String filePath, data textDatabase)    //This will parse the data to a Data Set
        {
            //This function is a test function to parse items into a dataset.
            String[] FileLines = System.IO.File.ReadAllLines(filePath); // This will store all the lines of the file into a string array
            foreach (String line in FileLines)
            {
                int tabCount = 0; // reset the tabCount
                String[] temp = new String[tabCount];
                foreach (char c in line)
                {
                    if (c.Equals('\t'))
                    {
                        tabCount++;
                    }
                }
                if (tabCount > 0)  // if the line contains tab characters, it means that it is a data line. So it should be parsed and added to our data structure.
                {
                    // here we will resize the array depending on the tabCount
                    temp = (String[])resizeArray(temp, tabCount + 1);
                    temp = line.Split('\t');
                    if ( temp[0].Equals("Day") || temp[0].StartsWith("The") || temp[0].Equals("") )  // this won't add the first row which contains the headings.
                        /*do nothing*/;
                    else
                        textDatabase.addRow(temp, textDatabase);  // This will add the parsed data as a row in the database.                    
                }
            }
        }

        public String buildStringForWriting(DataTable writeTable)
        {
            int rowCount = writeTable.Rows.Count;
            String outputText = "";
            String finalOutputText = "";
            DataRow[] rows = writeTable.Select();
            for (int i = 0; i < rows.Length; i++)
            {
                int j = 0;
                for (j = 0; j < 16; j++)
                {
                    outputText = rows[i][j].ToString();
                    finalOutputText = finalOutputText + outputText + '\t';
                }
                finalOutputText = finalOutputText + "\r\n";
            }
            return finalOutputText;
        }
    }
}
