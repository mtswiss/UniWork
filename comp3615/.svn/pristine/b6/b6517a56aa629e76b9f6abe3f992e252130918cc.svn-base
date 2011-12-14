//*********************************************************************************************************************************************
//Text File Editing Section
//Last Modified : 111014
//Features Enabled : Delete Trip, Join Trips, Undo for Delete, Join
//*********************************************************************************************************************************************

using System;
using System.Collections;
using System.ComponentModel;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Security.Permissions;
using System.IO;
using NUnit.Framework;
using GEPlugin;
using System.Data;
namespace Editing_Tool
{
    class TextFileEditor
    {
        //This section will set up the DataTables that will store the information from the text files.

        DataTable databaseViewer;   // This object will contain the trips from the day
        DataTable databaseViewerTotal;  // This object will contain all the trips in the text file.
        DataTable undoTable;
        DataTable undoTypeTable;
        String GlobalDay;
        DataTable writeToFile;

        public void setViewerTotal(data ParsedData)
        {
            databaseViewerTotal = ParsedData.getDataTable();
        }

        public void setViewer(data ParsedDataViewer)
        {
            databaseViewer = ParsedDataViewer.getDataTable();
            GlobalDay = databaseViewer.Rows[0]["Day"].ToString();
        }

        public DataTable getViewer()
        {
            return databaseViewer;
        }


        public TextFileEditor()
        {
            undoTable = createUndoTable();
            undoTypeTable = createUndoTypeTable();
            writeToFile = createWriteTable();
        }

        public DataTable createWriteTable()
        {
            DataTable dataTable = new DataTable();
            dataTable.Columns.Add("KMLTrip", typeof(String));
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
        public void completeMissingData(TripPool t_pool, String trip)
        {
            //This function will complete the fields of speed, distance and time which are currently empty in the original text file.
            //So we'll run through each record in the table and fill in these fields.
            for (int i = 0; i < databaseViewer.Rows.Count; ++i)
            {
                if (databaseViewer.Rows[i]["KMLTrip"].Equals(trip))
                {
                    databaseViewer.Rows[i]["Time"] = t_pool.getTripDetails().Rows[i]["Time"];
                    databaseViewer.Rows[i]["Distance"] = t_pool.getTripDetails().Rows[i]["Distance"];
                    databaseViewer.Rows[i]["Speed"] = t_pool.getTripDetails().Rows[i]["Speed"];
                }
            }
        }

        public void completeMissingData(TripPool t_pool)
        {
            //This function will complete the fields of speed, distance and time which are currently empty in the original text file.
            //So we'll run through each record in the table and fill in these fields.
            for (int i = 0; i < databaseViewer.Rows.Count; ++i)
            {
                databaseViewer.Rows[i]["Time"] = t_pool.getTripDetails().Rows[i]["Time"];
                databaseViewer.Rows[i]["Distance"] = t_pool.getTripDetails().Rows[i]["Distance"];
                databaseViewer.Rows[i]["Speed"] = t_pool.getTripDetails().Rows[i]["Speed"];
            }
        }

        public void addToDataTableForDay(String[] KMLTripDetails)
        {
            DataRow row = NewRowDataTableCustom();
            row[0] = KMLTripDetails[0];
            row[1] = KMLTripDetails[1];
            row[2] = "-";
            row[3] = KMLTripDetails[3];
            row[4] = "-";
            row[5] = KMLTripDetails[5];
            row[6] = KMLTripDetails[6];
            row[7] = KMLTripDetails[7];
            row[8] = KMLTripDetails[8];
            row[9] = KMLTripDetails[9];
            row[10] = KMLTripDetails[10];
            row[11] = KMLTripDetails[11];
            row[12] = KMLTripDetails[12];
            row[13] = KMLTripDetails[13];
            row[14] = KMLTripDetails[14];
            row[15] = KMLTripDetails[15];
            row[16] = "-";
            databaseViewer.Rows.InsertAt(row, databaseViewer.Rows.Count);
            resetTripCountForDay();
        }

        public DataTable createUndoTable()
        {
            DataTable dataTable = new DataTable();
            dataTable.Columns.Add("KMLTrip", typeof(String));
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

        public DataRow NewRowUndoTableCustom()
        {
            DataRow newRow = undoTable.NewRow();
            for (int i = 0; i != 17; ++i)
            {
                newRow[i] = "-";
            }
            return newRow;
        }

        public DataRow NewRowDataTableCustom()
        {
            DataRow newRow = databaseViewer.NewRow();
            for (int i = 0; i != 17; ++i)
            {
                newRow[i] = "-";
            }
            return newRow;
        }



        public void addToUndotable(DataRow editedRow)
        {
            //add this row to the undo Table
            DataRow newRow = NewRowUndoTableCustom();
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

        public void resetTripCountForDay()
        {
            //And now we need to rename each trip as the deleted if in the middle would have messed up the index
            int tripCount = 1;
            for (int i = 0; i < databaseViewer.Rows.Count; ++i)
            {
                databaseViewer.Rows[i]["Trip"] = (tripCount).ToString();
                databaseViewer.Rows[i]["KMLTrip"] = (tripCount).ToString();
                tripCount++;
            }

        }


        public void deleteTrip(String day, String trip, TripPool t_pool)
        {
            //This function will delete a trip specified by the particulars in each of the fields
            // These fields will correspond to the passed in values.
            //Now that we have the particulars required to find the right trip we will just go in and delete our trip
            //First we will find right row to edit. The day and the trip strings should match
            for (int i = 0; i < databaseViewer.Rows.Count; ++i)
            {
                if (databaseViewer.Rows[i]["KMLTrip"].ToString() == trip)
                {
                    //Once we have found the row and are going to delete it, we will first add it to the undo table.
                    addToUndotable(databaseViewer.Rows[i]);  // here we add it to the undo table
                    addToUndoTypeTable("Delete"); // here we add the type of action that is performed                      
                    databaseViewer.Rows[i].Delete(); // then we actually delete the row
                    break;
                }
            }
            resetTripCountForDay();
            t_pool.resetTripCount();
        }

        public String getLastUndoTableEntry()
        {
            if (undoTypeTable.Rows.Count == 0)
            {
                return "";
            }
            else if (undoTypeTable.Rows[0][0] == "Join")
                return undoTypeTable.Rows[0][0].ToString() + " on Trips " + undoTable.Rows[0]["KMLTrip"] + " and " + undoTable.Rows[1]["KMLTrip"];
            else
                return undoTypeTable.Rows[0][0].ToString() + " on Trip " + undoTable.Rows[0]["KMLTrip"];
        }

        public void makeStart(String trip, IKmlPlacemark newStartPoint, TripPool t_pool)
        {
            //This function will change the starting time of a trip
            //First we'll find the row to edit. The trip should match
            for (int i = 0; i < databaseViewer.Rows.Count; ++i)
            {
                if (databaseViewer.Rows[i]["KMLTrip"].ToString().Equals(trip))
                {
                    addToUndotable(databaseViewer.Rows[i]);
                    addToUndoTypeTable("Make Start");
                    databaseViewer.Rows[i]["Start"] = newStartPoint.getName();
                    databaseViewer.Rows[i]["sLongitude"] = Module.getCoordinates(newStartPoint)["lon"];
                    databaseViewer.Rows[i]["sLatitude"] = Module.getCoordinates(newStartPoint)["lat"];
                    t_pool.getTripDetails().Rows[i]["StartLong"] = Module.getCoordinates(newStartPoint)["lon"];
                    t_pool.getTripDetails().Rows[i]["StartLat"] = Module.getCoordinates(newStartPoint)["lat"];
                    t_pool.getTripDetails().Rows[i]["Start Time"] = newStartPoint.getName();
                    t_pool.resetTripData("Trip_" + trip);
                    completeMissingData(t_pool, trip);
                }
            }
        }

        public void makeFinish(String trip, IKmlPlacemark newFinishPoint, TripPool t_pool)
        {
            //This function will change the starting time of a trip
            //First we'll find the row to edit. The trip should match
            for (int i = 0; i < databaseViewer.Rows.Count; ++i)
            {
                if (databaseViewer.Rows[i]["KMLTrip"].ToString().Equals(trip))
                {
                    addToUndotable(databaseViewer.Rows[i]);
                    addToUndoTypeTable("Make Finish");
                    databaseViewer.Rows[i]["Finish"] = newFinishPoint.getName();
                    databaseViewer.Rows[i]["fLongitude"] = Module.getCoordinates(newFinishPoint)["lon"];
                    databaseViewer.Rows[i]["fLatitude"] = Module.getCoordinates(newFinishPoint)["lat"];
                    t_pool.getTripDetails().Rows[i]["FinishLong"] = Module.getCoordinates(newFinishPoint)["lon"];
                    t_pool.getTripDetails().Rows[i]["FinishLat"] = Module.getCoordinates(newFinishPoint)["lat"];
                    t_pool.getTripDetails().Rows[i]["Finish Time"] = newFinishPoint.getName();
                    t_pool.resetTripData("Trip_" + trip);
                    completeMissingData(t_pool, trip);
                }
            }
        }

        public void insertTrip(IKmlFolder trip, String tripNumber, TripPool t_pool)
        {
            //This will add a trip to the dataTable
            addToUndoTypeTable("Insert");
            undoTable.Rows.Add(tripNumber, "");
            DataRow row = NewRowDataTableCustom();
            row[0] = tripNumber;
            row[1] = databaseViewer.Rows[0][1];
            //The trip count will be set with the resetTripCount
            row[3] = databaseViewer.Rows[0][3];
            row[4] = databaseViewer.Rows[0][4];
            row[5] = databaseViewer.Rows[0][5];
            row[6] = databaseViewer.Rows[0][6];
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            IKmlPlacemark startPoint = (IKmlPlacemark)points.item(0);
            IKmlPlacemark finishPoint = (IKmlPlacemark)points.item(points.getLength() - 1);
            row[12] = Module.getCoordinates(startPoint)["lon"].ToString();
            row[13] = Module.getCoordinates(startPoint)["lat"].ToString();
            row[14] = Module.getCoordinates(finishPoint)["lon"].ToString();
            row[15] = Module.getCoordinates(finishPoint)["lat"].ToString();
            databaseViewer.Rows.InsertAt(row, Convert.ToInt32(tripNumber)-1);
            DataRow newRowKML = t_pool.NewRowDataTableCustom();
            newRowKML = copyDataRowContents(row, newRowKML);
            t_pool.getTripDetails().Rows.InsertAt(newRowKML, Convert.ToInt32(tripNumber)-1);
            completeMissingData(t_pool);
            t_pool.resetTripCount();
            resetTripCountForDay();
        }

        public void undoTripAction(TripPool t_pool)
        {
            //First we'll see what the last type of action was.
            String lastAction = undoTypeTable.Rows[0]["Action Type"].ToString(); // so this will bring down what the last action was.
            //We should then delete this action from the undoTypeTable
            undoTypeTable.Rows[0].Delete(); // this will delete the entry from the undoTable
            switch (lastAction)
            {

                case "Insert":
                    //When the last operation was an insert
                    String tripNumberInsert = undoTable.Rows[0][0].ToString();
                    //Find this trip in the databaseViewer
                    for (int i = 0; i != databaseViewer.Rows.Count; ++i)
                    {
                        if (databaseViewer.Rows[i]["KMLTrip"].Equals(tripNumberInsert))
                        {
                            databaseViewer.Rows[i].Delete();
                            //t_pool.getTripDetails().Rows[i].Delete();
                            t_pool.resetTripCount();
                            resetTripCountForDay();
                        }
                    }
                    break;

                case "Delete":
                    //If the last action was a delete action
                    //Then we simply have to re-instate the row in the UndoTable and place it back in the databaseViewer Table
                    //But before that we also need to find where exactly the row goes.
                    //We will do that by finding the day and trip number of the deleted row.And then inserting the row at that position.
                    String day = undoTable.Rows[0]["Day"].ToString();
                    String trip = undoTable.Rows[0]["KMLTrip"].ToString();
                    //Once we have the day and trip information we will find the right place to add the row back in the database.
                    if (databaseViewer.Rows.Count == 0)
                    {
                        DataRow newRow = NewRowDataTableCustom();
                        newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                        databaseViewer.Rows.InsertAt(newRow, 0);
                        DataRow newRowKML = t_pool.NewRowDataTableCustom();
                        newRowKML = copyDataRowContents(undoTable.Rows[0], newRowKML);
                        t_pool.getTripDetails().Rows.InsertAt(newRowKML, 0);
                        undoTable.Rows[0].Delete();
                        resetTripCountForDay();
                        t_pool.resetTripCount();
                        break;
                    }
                    else if (databaseViewer.Rows.Count < Convert.ToInt32(trip))
                    {
                        DataRow newRow = NewRowDataTableCustom();
                        newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                        databaseViewer.Rows.InsertAt(newRow, databaseViewer.Rows.Count);
                        DataRow newRowKML = t_pool.NewRowDataTableCustom();
                        newRowKML = copyDataRowContents(undoTable.Rows[0], newRowKML);
                        t_pool.getTripDetails().Rows.InsertAt(newRowKML, databaseViewer.Rows.Count);
                        undoTable.Rows[0].Delete();
                        resetTripCountForDay();
                        t_pool.resetTripCount();
                        break;
                    }
                    else
                    {
                        for (int i = 0; i < databaseViewer.Rows.Count; ++i)
                        {
                            if (Convert.ToInt32(databaseViewer.Rows[i]["KMLTrip"].ToString()) == Convert.ToInt32(trip))
                            {
                                //Now we'll add our trip at this location.
                                //Simply copying a row from one table to another table doesn't work. So we'll create a new DataRow to add
                                DataRow newRow = NewRowDataTableCustom();
                                newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                                databaseViewer.Rows.InsertAt(newRow, i);
                                DataRow newRowKML = t_pool.NewRowDataTableCustom();
                                newRowKML = copyDataRowContents(undoTable.Rows[0], newRowKML);
                                t_pool.getTripDetails().Rows.InsertAt(newRowKML, i);
                                resetTripCountForDay();
                                t_pool.resetTripCount();
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
                    trip = undoTable.Rows[0]["KMLTrip"].ToString();
                    if (databaseViewer.Rows.Count == 0)
                    {
                        DataRow newRow = NewRowDataTableCustom();
                        newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                        databaseViewer.Rows.InsertAt(newRow, 0);
                        t_pool.getTripDetails().Rows.InsertAt(newRow, 0);
                        resetTripCountForDay();
                        t_pool.resetTripCount();
                        undoTable.Rows[0].Delete();
                        break;
                    }
                    else if ( databaseViewer.Rows.Count < Convert.ToInt32(trip) )
                    {
                        DataRow newRow = NewRowDataTableCustom();
                        newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                        databaseViewer.Rows.InsertAt(newRow, databaseViewer.Rows.Count);
                        t_pool.getTripDetails().Rows.InsertAt(newRow, databaseViewer.Rows.Count  );
                        resetTripCountForDay();
                        t_pool.resetTripCount();
                        undoTable.Rows[0].Delete();
                        break;
                    }
                    else
                    {
                        for (int i = 0; i < databaseViewer.Rows.Count; ++i)
                        {
                            if (databaseViewer.Rows[i]["KMLTrip"].ToString() == trip)
                            {
                                DataRow newRow = NewRowDataTableCustom();
                                newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                                databaseViewer.Rows.InsertAt(newRow, i);
                                DataRow newRowKML = t_pool.NewRowDataTableCustom();
                                newRowKML = copyDataRowContents(undoTable.Rows[0], newRowKML);
                                t_pool.getTripDetails().Rows.InsertAt(newRowKML, i);
                                if (databaseViewer.Rows.Count > 1)
                                {
                                    databaseViewer.Rows[i + 1].Delete();
                                    t_pool.getTripDetails().Rows[i + 1].Delete();
                                }
                                undoTable.Rows[0].Delete();
                                resetTripCountForDay();
                                t_pool.resetTripCount();
                                break;
                            }
                        }
                    }
                    trip = undoTable.Rows[0]["KMLTrip"].ToString();
                    if (databaseViewer.Rows.Count < Convert.ToInt32(trip))
                    {
                        DataRow newRow = NewRowDataTableCustom();
                        newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                        databaseViewer.Rows.InsertAt(newRow, databaseViewer.Rows.Count);
                        DataRow newRowKML = t_pool.NewRowDataTableCustom();
                        newRowKML = copyDataRowContents(undoTable.Rows[0], newRowKML);
                        t_pool.getTripDetails().Rows.InsertAt(newRowKML, databaseViewer.Rows.Count);
                        resetTripCountForDay();
                        t_pool.resetTripCount();
                        undoTable.Rows[0].Delete();
                        break;
                    }
                    else
                    {
                        for (int i = 0; i < databaseViewer.Rows.Count; ++i)
                        {
                            if (databaseViewer.Rows[i]["KMLTrip"].ToString() == trip)
                            {
                                DataRow newRow = NewRowDataTableCustom();
                                newRow = copyDataRowContents(undoTable.Rows[0], newRow);
                                databaseViewer.Rows.InsertAt(newRow, i);
                                DataRow newRowKML = t_pool.NewRowDataTableCustom();
                                newRowKML = copyDataRowContents(undoTable.Rows[0], newRowKML);
                                t_pool.getTripDetails().Rows.InsertAt(newRowKML, i);
                                resetTripCountForDay();
                                t_pool.resetTripCount();
                                undoTable.Rows[0].Delete();
                                break;
                            }
                        }
                    }
                    break;

                case "Split":
                    //Now if the last operation was a split operation, the undo for it will be as follows
                    //We'll first find the tripNumber of the trip that was split.
                    String tripNumber = undoTable.Rows[0]["KMLTrip"].ToString();
                    //Now we'll find the trip with the same number in the current table. Once we've found it, we'll delete it and the row after it.
                    for (int i = 0; i < databaseViewer.Rows.Count; ++i)
                    {
                        if (databaseViewer.Rows[i]["KMLTrip"].ToString().Equals(tripNumber))
                        {
                            //Now we've found the dataRow which contains the trip where our undo trip should be. So we'll delete this record entry
                            databaseViewer.Rows[i].Delete();
                            t_pool.getTripDetails().Rows[i].Delete();
                            //Once that row has been deleted, the row below it will fall into the same index as the row that deleted before. So we'll perform the delete action again
                            databaseViewer.Rows[i].Delete();
                            t_pool.getTripDetails().Rows[i].Delete();
                            //Now we'll add the dataRow from our undoTable
                            DataRow newRow = NewRowDataTableCustom();
                            copyDataRowContents(undoTable.Rows[0], newRow);
                            databaseViewer.Rows.InsertAt(newRow, i);
                            DataRow newRowKML = t_pool.NewRowDataTableCustom();
                            copyDataRowContents(undoTable.Rows[0], newRowKML);
                            t_pool.getTripDetails().Rows.InsertAt(newRowKML, i);
                            //Now once all the data has been deleted and added, we'll reset the tripCount
                            resetTripCountForDay();
                            t_pool.resetTripCount();
                            //And now once all the data has been successfully restored we can delete the undo Table fields
                            undoTable.Rows[0].Delete();
                            break;
                        }
                    }
                    break;

                case "Make Start":
                    //That means that last operation was a Make Start on one of the trips
                    tripNumber = undoTable.Rows[0]["KMLTrip"].ToString();
                    for (int i = 0; i < databaseViewer.Rows.Count; ++i)
                    {
                        if ( databaseViewer.Rows[i]["KMLTrip"].ToString().Equals(tripNumber) )
                        {
                            databaseViewer.Rows[i].Delete();
                            DataRow newRow = NewRowDataTableCustom();
                            copyDataRowContents(undoTable.Rows[0], newRow);
                            databaseViewer.Rows.InsertAt(newRow, i);
                            t_pool.getTripDetails().Rows[i].Delete();
                            DataRow newRowKML = t_pool.NewRowDataTableCustom();
                            copyDataRowContents(undoTable.Rows[0], newRowKML);
                            t_pool.getTripDetails().Rows.InsertAt(newRowKML, i);
                            undoTable.Rows[0].Delete();
                            t_pool.removeFirstPoint("Trip_"+databaseViewer.Rows[i]["KMLTrip"]);
       //                     undoTypeTable.Rows[0].Delete();
                        }
                    }
                    //I think this should be in a different place, but it's not happening at the moment, so I'll do it here
                    //We should also delete the point that was created as the start point
                    //So it's just going to be the start point of the trip
                    break;

                case "Make Finish":
                    //That means that last operation was a Make Start on one of the trips
                    tripNumber = undoTable.Rows[0]["Trip"].ToString();
                    for (int i = 0; i < databaseViewer.Rows.Count; ++i)
                    {
                        if (databaseViewer.Rows[i]["KMLTrip"].ToString().Equals(tripNumber))
                        {
                            databaseViewer.Rows[i].Delete();
                            DataRow newRow = NewRowDataTableCustom();
                            copyDataRowContents(undoTable.Rows[0], newRow);
                            databaseViewer.Rows.InsertAt(newRow, i);
                            t_pool.getTripDetails().Rows[i].Delete();
                            DataRow newRowKML = t_pool.NewRowDataTableCustom();
                            copyDataRowContents(undoTable.Rows[0], newRowKML);
                            t_pool.getTripDetails().Rows.InsertAt(newRowKML, i);
                            undoTable.Rows[0].Delete();
                            t_pool.removeLastPoint("Trip_" + databaseViewer.Rows[i]["KMLTrip"]);
                            //                     undoTypeTable.Rows[0].Delete();
                        }
                    }
                    break;

                default:
                    break;

            }
        }

        public void joinTrips(String day, String trip1, String trip2, TripPool t_pool)
        {
            int trip1Number = Convert.ToInt32(trip1);
            int trip2Number = Convert.ToInt32(trip2);
            //If trip1 and trip2 are the same
            if (trip1Number == trip2Number)
            {
                MessageBox.Show("Please select two different trips");
                return;
            }
            //If the trip1 is greater than trip2
            if (trip1Number > trip2Number)
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
                if (databaseViewer.Rows[i]["KMLTrip"].ToString() == trip1)
                {
                    trip1Index = i;
                }
                if (databaseViewer.Rows[i]["KMLTrip"].ToString() == trip2)
                {
                    trip2Index = i;
                    break;
                }
            }
            //Now that we have the indices of the two trips, let us move the values around.
            //So the finish times and co-ordinates from trip2 go into trip1
            //But before that we'll add both rows to the undo Table and the type of action to the Undo Type Table
            addToUndotable(databaseViewer.Rows[trip2Index]);
            addToUndotable(databaseViewer.Rows[trip1Index]);
            addToUndoTypeTable("Join");
            databaseViewer.Rows[trip1Index]["Finish"] = databaseViewer.Rows[trip2Index]["Finish"];  // copy the trip2 finish time
            t_pool.getTripDetails().Rows[trip1Index]["Finish Time"] = databaseViewer.Rows[trip2Index]["Finish"];
            databaseViewer.Rows[trip1Index]["fLongitude"] = databaseViewer.Rows[trip2Index]["fLongitude"];  // copy the the trip2 longitude
            t_pool.getTripDetails().Rows[trip2Index]["FinishLong"] = databaseViewer.Rows[trip2Index]["fLongitude"];
            databaseViewer.Rows[trip1Index]["fLatitude"] = databaseViewer.Rows[trip2Index]["fLatitude"];  // copy the trip2 latitude.
            t_pool.getTripDetails().Rows[trip2Index]["FinishLat"] = databaseViewer.Rows[trip2Index]["fLatitude"];
            databaseViewer.Rows[trip2Index].Delete();  // This will delete the trip2 row.
            t_pool.getTripDetails().Rows[trip2Index].Delete();
            resetTripCountForDay();
            t_pool.resetTripCount();
            t_pool.resetTripData("Trip_"+ trip1);
            completeMissingData(t_pool);
            return;
        }

        public void splitTrip(String day, String trip, IKmlPlacemark s_point, IKmlPlacemark f_point, TripPool t_pool)
        {
 //           MessageBox.Show(tripData.getFeatures().getChildNodes().getLength().ToString() + " " + point.getName() +"    "+point.getId());


            Module testModule = new Module();
            //This function will split a trip in the text file
            //First we'll need to find the day we're talking about
            for (int i = 0; i < databaseViewer.Rows.Count; ++i)
            {
                    //once we have found the right day we'll go and find the right trip
                    if (databaseViewer.Rows[i]["KMLTrip"].ToString() == trip)
                    {
                        //Once we have found the trip we'll first have to add it to the Undo Table
                        //First we'll add the entry of what type of action was performed.
                        addToUndoTypeTable("Split");
                        addToUndotable(databaseViewer.Rows[i]);  // So we've added the whole row back into place.
                        //once we have found our trip record we'll make the further modifications
                        //Now the split point of the trip will become the finishing point of the original trip. Before we insert the new values, we should store the other values first
                        String oldFinishTime = databaseViewer.Rows[i]["Finish"].ToString();
                        String oldFinishLat = databaseViewer.Rows[i]["fLatitude"].ToString();
                        String oldFinishLong = databaseViewer.Rows[i]["fLongitude"].ToString();
                        //Now that we've stored these values, we can safely replace these fields with the new data.
                        databaseViewer.Rows[i]["Finish"] = f_point.getName();
                        t_pool.getTripDetails().Rows[i]["Finish Time"] = f_point.getName();
                        Hashtable coords = Module.getCoordinates(f_point);
                        databaseViewer.Rows[i]["fLatitude"] = coords["lat"];
                        databaseViewer.Rows[i]["fLongitude"] = coords["lon"];
                        t_pool.getTripDetails().Rows[i]["FinishLat"] = coords["lat"];
                        t_pool.getTripDetails().Rows[i]["FinishLong"] = coords["long"];
                        t_pool.resetTripData("Trip_"+ trip);
                        //By this time the original trip would have been modified correctly. Now we need to create a new trip and set it's fields correctly
                        //Now we need to get the details of the next point
 //                       point = getNextPoint(tripData, point); //This should give us the next point after the split point.
                        coords = Module.getCoordinates(s_point);
                        //Now once we have all the information we'll create a new record in the table
                        DataRow newRow = NewRowDataTableCustom();
                        DataRow newRowKML = t_pool.NewRowDataTableCustom();
                        //Most of the information will be the same as the current record
                        newRow["Day"] = databaseViewer.Rows[i]["Day"];
                        newRow["Household"] = databaseViewer.Rows[i]["HouseHold"];
                        newRow["Person"] = databaseViewer.Rows[i]["Person"];
                        newRow["Date"] = databaseViewer.Rows[i]["Date"];
                        newRow["Weekday"] = databaseViewer.Rows[i]["Weekday"];
                        newRow["Remain"] = databaseViewer.Rows[i]["Remain"];
                        //Now we'll add the new data
                        newRow["KMLTrip"] = (Convert.ToInt32(databaseViewer.Rows[i]["KMLTrip"])+1).ToString();
                        newRow["Start"] = s_point.getName();
                        newRow["Finish"] = oldFinishTime;
                        newRow["sLongitude"] = coords["lon"];
                        newRow["sLatitude"] = coords["lat"];
                        newRow["fLongitude"] = oldFinishLong;
                        newRow["fLatitude"] = oldFinishLat;
                        //Now we'll add this row in the dataTable
                        databaseViewer.Rows.InsertAt(newRow, i+1);
                        newRowKML = copyDataRowContents(newRow, newRowKML);
                        t_pool.getTripDetails().Rows.InsertAt(newRowKML, i + 1);
                        //Now once everything is done, we'll reset the tripCount for that day
                        resetTripCountForDay();
                        t_pool.resetTripCount();
                        t_pool.resetTripData("Trip_" + (Convert.ToInt32(trip)+1).ToString());
                        completeMissingData(t_pool);
                    }
                
            }
        }
        public IKmlPlacemark getNextPoint(IKmlFolder trip, IKmlPlacemark point)
        {
            bool flag = false;
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            for (int i = 0; i != points.getLength(); ++i)
            {
                IKmlPlacemark pt = (IKmlPlacemark) points.item(i);
                if (flag == true)
                {
                    return pt;
                }
                if (pt.getName() == point.getName())
                {
                    flag = true;
                }
            }
            return null;
        }

        public void writeTextToFile(String filePath)
        {
            //Once the user has completed editing, we will write the text file
            //Now the write will be a combination of the Viewer file which the user was editing and the total file which wasn't being edited.
            //So we'll go through all the trips in the total database and if we're on the trip that we were editing we'll use the values from our Viewer.
            String day;
            int i = 0;
            day = databaseViewerTotal.Rows[0]["Day"].ToString();
            String[] dayStartCoordinates = new String[2];
            String[] dayFinishCoordinates = new String[2];
            dayStartCoordinates[0] = databaseViewerTotal.Rows[i]["sLongitude"].ToString();
            dayStartCoordinates[1] = databaseViewerTotal.Rows[i]["sLatitude"].ToString();
            while (i != databaseViewerTotal.Rows.Count)
            {
                if (databaseViewerTotal.Rows[i]["Day"].Equals(day))
                {
                    if (databaseViewerTotal.Rows[i]["Day"].Equals(GlobalDay))
                    {
                        for (int j = 0; j != databaseViewer.Rows.Count; ++j)
                        {
                            //We will use data from the  Viewer dataTable
                            DataRow row = writeToFile.NewRow();
                            row = copyDataRowContents(databaseViewer.Rows[j], row);
                            dayFinishCoordinates[0] = databaseViewer.Rows[j]["fLongitude"].ToString();
                            dayFinishCoordinates[1] = databaseViewer.Rows[j]["fLatitude"].ToString();
                            writeToFile.Rows.Add(row);
                        }
                        //Once all the data for this file is written we should fill out the other information
                        //But before that we need to find the next set of trip
                        while (databaseViewerTotal.Rows[i]["Day"].Equals(GlobalDay))
                        {
                            ++i;
                        }
                        DataRow row1 = writeToFile.NewRow();
                        row1[1] = "The return distance back to the start is " + Math.Round(DistanceAlgorithm.DistanceBetweenPlaces(Convert.ToDouble(dayStartCoordinates[1]), Convert.ToDouble(dayStartCoordinates[0]), Convert.ToDouble(dayFinishCoordinates[1]), Convert.ToDouble(dayFinishCoordinates[0])), 2) + " km.";
                        writeToFile.Rows.Add(row1);
                        dayStartCoordinates[0] = databaseViewerTotal.Rows[i]["sLongitude"].ToString();
                        dayStartCoordinates[1] = databaseViewerTotal.Rows[i]["sLatitude"].ToString();
                        row1 = writeToFile.NewRow();
                        row1[1] = "The distance between the days is " + Math.Round(DistanceAlgorithm.DistanceBetweenPlaces(Convert.ToDouble(dayFinishCoordinates[1]), Convert.ToDouble(dayFinishCoordinates[0]), Convert.ToDouble(dayStartCoordinates[1]), Convert.ToDouble(dayStartCoordinates[0])), 2) + " km.";
                        writeToFile.Rows.Add(row1);
                        day = databaseViewerTotal.Rows[i]["Day"].ToString();
                    }
                    else
                    {
                        DataRow row = writeToFile.NewRow();
                        row = copyDataRowContents(databaseViewerTotal.Rows[i], row);
                        writeToFile.Rows.Add(row);
                        ++i;
                    }
                }
                else
                {
                    //If a new trip has started. Then we should first fill in some information
                    DataRow row = writeToFile.NewRow();
                    dayFinishCoordinates[0] = databaseViewerTotal.Rows[i - 1]["fLongitude"].ToString();
                    dayFinishCoordinates[1] = databaseViewerTotal.Rows[i - 1]["fLatitude"].ToString();
                    row[1] = "The return distance back to the start is " + Math.Round(DistanceAlgorithm.DistanceBetweenPlaces(Convert.ToDouble(dayStartCoordinates[1]), Convert.ToDouble(dayStartCoordinates[0]), Convert.ToDouble(dayFinishCoordinates[1]), Convert.ToDouble(dayFinishCoordinates[0])), 2) + " km.";
                    writeToFile.Rows.Add(row);
                    dayStartCoordinates[0] = databaseViewerTotal.Rows[i]["sLongitude"].ToString();
                    dayStartCoordinates[1] = databaseViewerTotal.Rows[i]["sLatitude"].ToString();
                    row = writeToFile.NewRow();
                    row[1] = "The distance between the days is " + Math.Round(DistanceAlgorithm.DistanceBetweenPlaces(Convert.ToDouble(dayFinishCoordinates[1]), Convert.ToDouble(dayFinishCoordinates[0]), Convert.ToDouble(dayStartCoordinates[1]), Convert.ToDouble(dayStartCoordinates[0])), 2) + " km.";
                    writeToFile.Rows.Add(row);
                    day = databaseViewerTotal.Rows[i]["Day"].ToString();
                }
            }
            //Now once we've collected all the information in the datatable we'll write it out to a file
            DateTime currentDateTime = DateTime.Now;
            String tempDateTime = currentDateTime.ToString("yyMMdd_HHmmss");
            String newFilePath = filePath.Split('.')[0] + "_" + tempDateTime + ".txt";
            String newFileText = buildStringForWriting(writeToFile);
            //First we'll copy the contents of the current file, into the new file
            File.Move(filePath, newFilePath);
            //Then we will copy the clear the contents of the current file
            System.IO.StreamWriter file = new System.IO.StreamWriter(filePath);
            file.WriteLine(newFileText);
            file.Close();
            MessageBox.Show("The text file has been written to " + filePath + "\nThe previous version was saved in " + newFilePath);
        }

        public String buildStringForWriting(DataTable writeTable)
        {
            int rowCount = writeTable.Rows.Count;
            String outputText = "";
            String finalOutputText = "";
            finalOutputText = finalOutputText + "Day\tTrip\tHouseHold\tPerson\tDate\tWeekday\tStart\tFinish\tTime\tDistance\tSpeed\tsLongitude\tsLatitude\tfLongitude\tfLatitude\tRemain\r\n";
            DataRow[] rows = writeTable.Select();
            for (int i = 0; i < rows.Length; i++)
            {
                int j = 1;
                for (j = 1; j < 16; j++)
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
