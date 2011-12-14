using System;
using System.Collections.Generic;
using System.Linq;
using System.Data;
using System.Text;

namespace Editing_Tool
{
    public class data
    {
        DataTable TextDataTable;
        public data()
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
            assignDataTable(dataTable);
        }

        public void addRow(String[] line, data textDatabase)
        {
            textDatabase.TextDataTable.Rows.Add("", line[0], line[1], line[2], line[3], line[4], line[5], line[6], line[7], line[8], line[9], line[10], line[11], line[12], line[13], line[14], line[15]);
        }

        public DataTable getDataTable()
        {
            return this.TextDataTable;
        }

        public void assignDataTable(DataTable table)
        {
            TextDataTable = table;
        }
    }

}
