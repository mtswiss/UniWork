using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Text_Parser
{
    public partial class Viewer : Form
    {
        DataTable databaseViewer;
        DataTable undoTable;
        DataTable undoTypeTable;
        String dayStringViewer;
        String trip1StringViewer;
        String trip2StringViewer;
        public Viewer(data database)
        {
            InitializeComponent();
            TextDataGrid.DataSource = database.getDataTable();
            assignDatabaseToViewer(database.getDataTable());
            undoTable = createUndoTable();
            undoTypeTable = createUndoTypeTable();
            undoTypeTableView.DataSource = undoTable;
            undoTableView.DataSource = undoTypeTable;
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

        private void day_TextChanged(object sender, EventArgs e)
        {
            String dayString;
            dayString = day.Text;
            dayStringViewer = dayString;

        }

        private void trip1_TextChanged(object sender, EventArgs e)
        {
            String trip1String;
            trip1String = trip1.Text;
            trip1StringViewer = trip1String;
        }

        private void trip2_TextChanged(object sender, EventArgs e)
        {
            String trip2String;
            trip2String = trip2.Text;
            trip2StringViewer = trip2String;

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

        private void deleteTrip_Click(object sender, EventArgs e)
        {
            //This function will delete a trip specified by the particulars in each of the fields
            // These fields will correspond to the passed in values.
            String day = "";
            String trip1 = "";
            day = String.Copy(dayStringViewer);
            trip1 = String.Copy(trip1StringViewer);
            //Now that we have the particulars required to find the right trip we will just go in and delete our trip
            //First we will find right row to edit. The day and the trip strings should match
            for (int i = 0; i < databaseViewer.Rows.Count; ++i)
            {
                if (databaseViewer.Rows[i]["Day"].ToString() == day)
                {
                    if (databaseViewer.Rows[i]["Trip"].ToString() == trip1)
                    {
                        //Once we have found the row and are going to delete it, we will first add it to the undo table.
                        addToUndotable(databaseViewer.Rows[i]);  // here we add it to the undo table
                        addToUndoTypeTable("Delete"); // here we add the type of action that is performed                      
                        databaseViewer.Rows[i].Delete(); // then we actually delete the row
                        break;
                    }
                }
            }
            resetTripCountForDay(day);
        }

        private void deleteTrip_MouseHover(object sender, EventArgs e)
        {
            deleteTrip.BackColor = System.Drawing.Color.Orange;
            label4.Text = "Delete Trip is being hovered over";
        }

        private void deleteTrip_MouseLeave ( object sender, EventArgs e )
        {
            deleteTrip.BackColor = System.Drawing.Color.Transparent;
            label4.Text = "label4";
        }

        private void undoTrip_Click(object sender, EventArgs e)
        {
            //First we'll see what the last type of action was.
            String lastAction = undoTypeTable.Rows[0]["Action Type"].ToString(); // so this will bring down what the last action was.
            //We should then delete this action from the undoTypeTable
            undoTypeTable.Rows[0].Delete(); // this will delete the entry from the undoTable
            switch (lastAction)
            {
                case "Delete":
                    //If the last action was a delete action
                    //Then we simply have to re-instate the row in the UndoTable and place it back in the databaseViewer Table
                    //But before that we also need to find where exactly the row goes.
                    //We will do that by finding the day and trip number of the deleted row.And then inserting the row at that position.
                    String day = undoTable.Rows[0]["Day"].ToString();
                    String trip = undoTable.Rows[0]["Trip"].ToString();
                    //Once we have the day and trip information we will find the right place to add the row back in the database.
                    if (databaseViewer.Rows.Count == 0)
                    {
                        DataRow newRow = databaseViewer.NewRow();
                        newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                        databaseViewer.Rows.InsertAt(newRow, 0);
                        resetTripCountForDay(day);
                        undoTable.Rows[0].Delete();
                        break;
                    }
                    for (int i = 0; i < databaseViewer.Rows.Count; ++i)
                    {
                        if (Convert.ToInt32(databaseViewer.Rows[i]["Day"].ToString()) > Convert.ToInt32(day))
                        {
                            DataRow newRow = databaseViewer.NewRow();
                            newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                            databaseViewer.Rows.InsertAt(newRow, i);
                            undoTable.Rows[0].Delete();
                            resetTripCountForDay(day);
                            break;
                        }
                        else
                        {
                            if (databaseViewer.Rows[i]["Trip"].ToString() == trip)
                            {
                                //Now we'll add our trip at this location.
                                //Simply copying a row from one table to another table doesn't work. So we'll create a new DataRow to add
                                DataRow newRow = databaseViewer.NewRow();
                                newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                                databaseViewer.Rows.InsertAt(newRow, i);
                                resetTripCountForDay(day);
                                // One the row has been safely added back to the database, it is safe to remove it from the undo Table
                                undoTable.Rows[0].Delete();
                                break;
                            }
                        }
                    }
                    break;

                case "Join":
                    //If the last action was a join action
                    //That means we have to re-instate the two rows that are in the undo table in their respective order.
                    //First we'll find the current trip1 and delete it.
                    day = undoTable.Rows[0]["Day"].ToString();
                    trip = undoTable.Rows[0]["Trip"].ToString();
                    if (databaseViewer.Rows.Count == 0)
                    {
                        DataRow newRow = databaseViewer.NewRow();
                        newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                        databaseViewer.Rows.InsertAt(newRow, 0);
                        resetTripCountForDay(day);
                        undoTable.Rows[0].Delete();
                        break;
                    }
                    for (int i=0; i<databaseViewer.Rows.Count; ++i)
                    {
                        if (Convert.ToInt32(databaseViewer.Rows[i]["Day"].ToString()) > Convert.ToInt32(day))
                        {
                            DataRow newRow = databaseViewer.NewRow();
                            newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                            databaseViewer.Rows.InsertAt(newRow, i);
                            undoTable.Rows[0].Delete();
                            resetTripCountForDay(day);
                            break;
                        }
                        if (databaseViewer.Rows[i]["Day"].ToString() == day)
                        {
                            if (databaseViewer.Rows[i]["Trip"].ToString() == trip)
                            {
                                DataRow newRow = databaseViewer.NewRow();
                                newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                                databaseViewer.Rows.InsertAt(newRow, i);
                                databaseViewer.Rows[i+1].Delete();
                                undoTable.Rows[0].Delete();
                                break;
                             }
                        }
                    }
                    day = undoTable.Rows[0]["Day"].ToString();
                    trip = undoTable.Rows[0]["Trip"].ToString();
                    for (int i = 0; i < databaseViewer.Rows.Count; ++i)
                    {
                        if (Convert.ToInt32(databaseViewer.Rows[i]["Day"].ToString()) > Convert.ToInt32(day))
                        {
                            DataRow newRow = databaseViewer.NewRow();
                            newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                            databaseViewer.Rows.InsertAt(newRow, i);
                            undoTable.Rows[0].Delete();
                            resetTripCountForDay(day);
                            break;
                        }
                        if (databaseViewer.Rows[i]["Day"].ToString() == day)
                        {
                            if (databaseViewer.Rows[i]["Trip"].ToString() == trip)
                            {
                                DataRow newRow = databaseViewer.NewRow();
                                newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                                databaseViewer.Rows.InsertAt(newRow, i);
                                resetTripCountForDay(day);
                                undoTable.Rows[0].Delete();
                                break;
                            }
                        }
                    }
                    break;

                default:
                    break;
            }
        }

        private void joinTrip_Click(object sender, EventArgs e)
        {
            String day = String.Copy(dayStringViewer);
            String trip1 = String.Copy(trip1StringViewer);
            String trip2 = String.Copy(trip2StringViewer);
            int trip1Number = Convert.ToInt32(trip1);
            int trip2Number = Convert.ToInt32(trip2);
            //If trip1 and trip2 are the same
            if ( trip1Number == trip2Number )
            {
                MessageBox.Show("Please select two different trips");
                return;
            }
            //If the trip1 is greater than trip2
            if ( trip1Number > trip2Number )
            {
                String temp = trip1;
                trip1 = trip2;
                trip2 = temp;
            }
            int trip1Index = 0;
            int trip2Index = 0;
            //Now in this function we're going to join two trips.
            //So the basics of this is that we'll be copying the finishing time and co-ordinates of the first trip into the finish time and co-ordinates of the first trip.
            //So first what we'll do is find the trip that the finish time is going to go to.
            for (int i = 0; i < databaseViewer.Rows.Count; ++i)
            {
                if ( databaseViewer.Rows[i]["Day"].ToString() == day )
                {
                    if ( databaseViewer.Rows[i]["Trip"].ToString() == trip1 )
                    {
                        trip1Index = i;
                    }
                    if (databaseViewer.Rows[i]["Trip"].ToString() == trip2)
                    {
                        trip2Index = i;
                        break;
                    }

                }
            }
            //Now that we have the indices of the two trips, let us move the values around.
            //So the finish times and co-ordinates from trip2 go into trip1
            //But before that we'll add both rows to the undo Table and the type of action to the Undo Type Table
            addToUndotable(databaseViewer.Rows[trip2Index]);
            addToUndotable(databaseViewer.Rows[trip1Index]);
            addToUndoTypeTable("Join");
            databaseViewer.Rows[trip1Index]["Finish"] = databaseViewer.Rows[trip2Index]["Finish"];  // copy the trip2 finish time
            databaseViewer.Rows[trip1Index]["fLongitude"] = databaseViewer.Rows[trip2Index]["fLongitude"];  // copy the the trip2 longitude
            databaseViewer.Rows[trip1Index]["fLatitude"] = databaseViewer.Rows[trip2Index]["fLatitude"];  // copy the trip2 latitude.
            databaseViewer.Rows[trip2Index].Delete();  // This will delete the trip2 row.
            resetTripCountForDay(day);
            return;
        }



    }
}
