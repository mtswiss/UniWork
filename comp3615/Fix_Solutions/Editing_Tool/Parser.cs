using System;
using System.Collections.Generic;
using System.Linq;
using System.Data;
using System.Text;

namespace Editing_Tool
{
    class Parser
    {
        public Parser()
        { }
        //This will contain the data in parsed form.

        public static System.Array resizeArray(System.Array oldArray)  // this function will resize our temporary string array that is used to store the parsed Line.
        {
            int oldSize = oldArray.Length;
            System.Type elementType = oldArray.GetType().GetElementType();
            System.Array newArray = System.Array.CreateInstance(elementType, 16);
            //now we'll copy the contents of the old array into the new array
            for (int i = 0; i < oldArray.Length; ++i)
            {
                newArray.SetValue(oldArray.GetValue(i), i);
            }
            newArray.SetValue("", 15);
            return newArray;
        }
        public void parseFileToDataSet(String filePath, data textDatabase, data textDatabaseView, String day)    //This will parse the data to a Data Set
        {
            //This function is a test function to parse items into a dataset.
            String[] FileLines = System.IO.File.ReadAllLines(filePath); // This will store all the lines of the file into a string array
            foreach (String line in FileLines)
            {
                int tabCount = 0; // reset the tabCount
                String[] temp = new String[tabCount];
                // here we will resize the array depending on the tabCount
                temp = line.Split('\t');
                if (temp.Count() < 16 && temp.Count() != 1)
                {
                    temp = (String[])resizeArray(temp); // in some lines in the text file, the last field is sometimes incomplete and without a tab character.
                }
                if (temp[0].Equals("Day") || temp[0].Equals("") || temp[0].StartsWith("The") || temp[0].StartsWith("***") )  // this won't add the first row which contains the headings.
                    Console.WriteLine();  // just a stupid step
                else
                {
                    textDatabase.addRow(temp, textDatabase);
                    if(temp[0].Equals(day))  // and if it belongs to the day from the KML file, we'll use that.
                    {
                        //Check if this is the day before the day we want
                        textDatabaseView.addRow(temp, textDatabaseView);  // This will add the parsed data as a row in the database. //But this will add only the days for this KML file
                    }
                }
            }
        }
        public String buildStringForWriting(data table)
        {
            int rowCount = table.getDataTable().Rows.Count;
            String outputText = "";
            String finalOutputText = "";
            DataRow[] rows = table.getDataTable().Select();
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
