using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Text_Parser
{
    class program
    {
        public static void Main()
        {
            //Let us first create an instance of the database
            data textDatabase = new data();
            //Let us also create an instance of the parser class
            Parser textParser = new Parser();
            //Let us also get the filePath that we're going to use. For now, it is going to be hard-coded
            String filePath = Application.StartupPath.ToString() + @"\tripResult_m.txt";
            // This will be the main store for the data that we collect from the text file
            //Now we shall add the parased data to this database.
            textParser.parseFileToDataSet(filePath, textDatabase);
            //Now once we have parsed the database. We need to view it in our DataGridView.
            //For that we will first create an instance of the Viewer
            Application.Run(new Viewer(textDatabase));
            DateTime currentDateTime = DateTime.Now;
            String tempDateTime = currentDateTime.ToString("yyMMdd_HHmmss");
            //String newFilePath = @"C:\Users\Abhishek Datar\Documents\Visual Studio 2010\Projects\Text Parser\Text Parser\tripResult_m_" + tempDateTime + ".txt";
            String newFilePath = Application.StartupPath.ToString() + @"\tripResult_m_" + tempDateTime + ".txt";
            String newFileText = textParser.buildStringForWriting(textDatabase);
            System.IO.StreamWriter file = new System.IO.StreamWriter(newFilePath);
            file.WriteLine(newFileText);
            file.Close();
        }
  
        
    }
}
