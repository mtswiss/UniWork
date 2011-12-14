using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Editing_Tool
{
    class Table
    {
        DataTable databaseViewer;
        DataTable undoTable;
        DataTable undoTypeTable;
        String dayStringViewer;
        String trip1StringViewer;
        String trip2StringViewer;
 
        public Table(data database)
        {
            assignDatabaseToViewer(database.getDataTable());
            undoTable = createUndoTable();
            undoTypeTable = createUndoTypeTable();
        }

        public DataTable createUndoTable()
        {
            DataTable dataTable = new DataTable();
            dataTable.Columns.Add("Day", typeof(String));
            dataTable.Columns.Add("Trip", typeof(String));
            dataTable.Columns.Add("HouseHold", typeof(String));
            dataTable.Columns.Add("Person", typeof(String));
            dataTable.Columns.Add("Date", typeof(String));
            dataTable.Columns.Add("Weekday", typeof(String));
            dataTable.Columns.Add("Start", typeof(String));
            dataTable.Columns.Add("Finish", typeof(String));
            dataTable.Columns.Add("Time", typeof(String));
            dataTable.Columns.Add("Distance", typeof(String));
            dataTable.Columns.Add("Speed", typeof(String));
            dataTable.Columns.Add("sLongitude", typeof(String));
            dataTable.Columns.Add("sLatitude", typeof(String));
            dataTable.Columns.Add("fLongitude", typeof(String));
            dataTable.Columns.Add("fLatitude", typeof(String));
            dataTable.Columns.Add("Remain", typeof(String));
            return dataTable;
        }

        public DataTable createUndoTypeTable()
        {
            //This function stores the type of function that was executed, so that during the undo process we know which algorithm to use.
            DataTable undoTypeTable = new DataTable();
            undoTypeTable.Columns.Add("Action Type", typeof(String));
            return undoTypeTable;
        }

        public DataRow copyDataRowContents(DataRow source, DataRow newRow)
        {
            for (int i = 0; i < 16; ++i)
            {
                newRow[i] = source[i];
            }
            return newRow;
        }



        public void addToUndotable(DataRow editedRow)
        {
            //add this row to the undo Table
            DataRow newRow = undoTable.NewRow();
            newRow = copyDataRowContents(editedRow, newRow);  // this is to prevent the row from other table problem
            undoTable.Rows.InsertAt(newRow, 0);  // this will always add the new row at the top of the table.
        }

        public void addToUndoTypeTable(String action)
        {
            //add this to the Undo Type table to know which kind of action was performed
            DataRow newRow = undoTypeTable.NewRow();
            newRow[0] = action;
            undoTypeTable.Rows.InsertAt(newRow, 0);  // this will add the action to the top of the Table.
        }

        public void assignDatabaseToViewer(DataTable database)
        {
            databaseViewer = database;
        }

        public void resetTripCountForDay(String day)
        {
            //And now we need to rename each trip as the deleted if in the middle would have messed up the index
            int tripCount = 1;
            for (int i = 0; i < databaseViewer.Rows.Count; ++i)
            {

                if (databaseViewer.Rows[i]["Day"].ToString() == day)
                {
                    databaseViewer.Rows[i]["Trip"] = (tripCount).ToString();
                    tripCount++;
                }
            }

        }

















    }
}
