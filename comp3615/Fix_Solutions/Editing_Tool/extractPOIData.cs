using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Collections;
using Microsoft.Office.Core;
//using Excel = Microsoft.Office.Interop.Excel;

namespace Editing_Tool
{
    class extractPOIData
    {
        DataTable homeData;
        DataTable schoolData;
        DataTable workData;
        DataTable shoppingData;


        public extractPOIData()
        {
            homeData = new DataTable();
            schoolData = new DataTable();
            workData = new DataTable();
            shoppingData = new DataTable();

            //Create the home DataTable

            homeData.Columns.Add("HouseholdID");
            homeData.Columns.Add("Full Address");
            homeData.Columns.Add("Latitude");
            homeData.Columns.Add("Longitude");

            //Create the school DataTable

            schoolData.Columns.Add("HouseholdID");
            schoolData.Columns.Add("PersonID");
            schoolData.Columns.Add("Name of Institution");
            schoolData.Columns.Add("Full Address");
            schoolData.Columns.Add("Latitude");
            schoolData.Columns.Add("Longitude");
            schoolData.Columns.Add("Full Time");
            schoolData.Columns.Add("Part Time");

            //Create the work DataTable

            workData.Columns.Add("HouseholdID");
            workData.Columns.Add("PersonID");
            workData.Columns.Add("Type of Work");
            workData.Columns.Add("Building Name");
            workData.Columns.Add("Full Address");
            workData.Columns.Add("Latitude");
            workData.Columns.Add("Longitude");
            workData.Columns.Add("Full Time");
            workData.Columns.Add("Part Time");
            workData.Columns.Add("Casual");
            workData.Columns.Add("Volunteer");

            //Create the shopping DataTable

            shoppingData.Columns.Add("HouseholdID");
            shoppingData.Columns.Add("Shop Name");
            shoppingData.Columns.Add("Shopping Centre");
            shoppingData.Columns.Add("Address");
            shoppingData.Columns.Add("Latitude");
            shoppingData.Columns.Add("Longitude");
        }

        public void getDataFromExcelFile(String path, DataTable textDataFile)
        {
            Microsoft.Office.Interop.Excel.Application app = new Microsoft.Office.Interop.Excel.Application();
            Microsoft.Office.Interop.Excel.Workbook workBook = app.Workbooks.Open(path, 0, true, 5, "", "", true, Microsoft.Office.Interop.Excel.XlPlatform.xlWindows, "\t", false, false, 0, true, 1, 0);

            Microsoft.Office.Interop.Excel.Worksheet homes = (Microsoft.Office.Interop.Excel.Worksheet)workBook.Sheets.get_Item(2);
            Microsoft.Office.Interop.Excel.Worksheet schools = (Microsoft.Office.Interop.Excel.Worksheet)workBook.Sheets.get_Item(3);
            Microsoft.Office.Interop.Excel.Worksheet works = (Microsoft.Office.Interop.Excel.Worksheet)workBook.Sheets.get_Item(4);
            Microsoft.Office.Interop.Excel.Worksheet shoppings = (Microsoft.Office.Interop.Excel.Worksheet)workBook.Sheets.get_Item(5);

            Array houseHolds = getAllHouseHolds(textDataFile);
            Array persons = getAllPerson(textDataFile);

            DataRow row;

            int index = 0;
            object rowIndex = 2;

            while (((Microsoft.Office.Interop.Excel.Range)homes.Cells[rowIndex, 1]).Value2 != null)
            {
                rowIndex = 2 + index;
                row = homeData.NewRow();
                row[0] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)homes.Cells[rowIndex, 1]).Value2);
                row[1] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)homes.Cells[rowIndex, 2]).Value2);
                row[2] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)homes.Cells[rowIndex, 3]).Value2);
                row[3] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)homes.Cells[rowIndex, 4]).Value2);
                index++;
                if ( isHouseHoldInCurrentData(row, houseHolds) )
                    homeData.Rows.Add(row);
            }

            index = 0;
            rowIndex = 2;

            while (((Microsoft.Office.Interop.Excel.Range)schools.Cells[rowIndex, 1]).Value2 != null)
            {
                rowIndex = 2 + index;
                row = schoolData.NewRow();
                row[0] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)schools.Cells[rowIndex, 1]).Value2);
                row[1] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)schools.Cells[rowIndex, 2]).Value2);
                row[2] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)schools.Cells[rowIndex, 3]).Value2);
                row[3] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)schools.Cells[rowIndex, 4]).Value2);
                row[4] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)schools.Cells[rowIndex, 5]).Value2);
                row[5] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)schools.Cells[rowIndex, 6]).Value2);
                row[6] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)schools.Cells[rowIndex, 7]).Value2);
                row[7] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)schools.Cells[rowIndex, 8]).Value2);
                index++;
                if (isHouseHoldInCurrentData(row, houseHolds))
                {
                    if (isPersonInCurrentData(row, persons))
                    {
                        schoolData.Rows.Add(row);
                    }
                }
            }

            index = 0;
            rowIndex = 2;

            while (((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 1]).Value2 != null)
            {
                rowIndex = 2 + index;
                row = workData.NewRow();
                row[0] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 1]).Value2);
                row[1] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 2]).Value2);
                row[2] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 3]).Value2);
                row[3] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 4]).Value2);
                row[4] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 5]).Value2);
                row[5] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 6]).Value2);
                row[6] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 7]).Value2);
                row[7] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 8]).Value2);
                row[8] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 9]).Value2);
                row[9] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 10]).Value2);
                row[10] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)works.Cells[rowIndex, 11]).Value2);
                index++;
                if (isHouseHoldInCurrentData(row, houseHolds))
                {
                    if (isPersonInCurrentData(row, persons))
                    {
                        workData.Rows.Add(row);
                    }
                }
            }

            index = 0;
            rowIndex = 2;

            while (((Microsoft.Office.Interop.Excel.Range)shoppings.Cells[rowIndex, 1]).Value2 != null)
            {
                rowIndex = 2 + index;
                row = shoppingData.NewRow();
                row[0] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)shoppings.Cells[rowIndex, 1]).Value2);
                row[1] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)shoppings.Cells[rowIndex, 3]).Value2);
                row[2] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)shoppings.Cells[rowIndex, 4]).Value2);
                row[3] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)shoppings.Cells[rowIndex, 5]).Value2);
                row[4] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)shoppings.Cells[rowIndex, 6]).Value2);
                row[5] = Convert.ToString(((Microsoft.Office.Interop.Excel.Range)shoppings.Cells[rowIndex, 7]).Value2);
                index++;
                if (isHouseHoldInCurrentData(row, houseHolds))
                    shoppingData.Rows.Add(row);
            }
            app.DisplayAlerts = false;
            app.Quit();
        }
        public Array getAllHouseHolds(DataTable textFileData)
        {
            ArrayList houseHolds = new ArrayList();
            for (int i = 0; i < textFileData.Rows.Count; ++i)
            {
                houseHolds.Add(textFileData.Rows[i]["HouseHold"]);
            }
            String[] houseHoldArray = new String[houseHolds.Count];
            houseHoldArray = (String[])houseHolds.ToArray(typeof(String));
            houseHoldArray = houseHoldArray.Distinct().ToArray();
            return houseHoldArray;
        }
        
        public Array getAllPerson(DataTable textFileData)
        {
            ArrayList persons = new ArrayList();
            for (int i = 0; i < textFileData.Rows.Count; ++i)
            {
                persons.Add(textFileData.Rows[i]["Person"]);
            }
            String[] personArray = new String[persons.Count];
            personArray = (String[])persons.ToArray(typeof(String));
            personArray = personArray.Distinct().ToArray();
            return personArray;
        }

        public bool isHouseHoldInCurrentData(DataRow row, Array houseHolds )
        {
            for (int i = 0; i < houseHolds.Length; ++i)
            {
                if (row[0].Equals(houseHolds.GetValue(i)))
                    return true;
            }
            return false;
        }

        public bool isPersonInCurrentData(DataRow row, Array persons)
        {
            for (int i = 0; i < persons.Length; ++i)
            {
                if ( row[1].Equals(persons.GetValue(i)))
                    return true;
            }
            return false;
        }

        public DataTable getHomes()
        {
            return homeData;
        }

        public DataTable getSchools()
        {
            return schoolData;
        }

        public DataTable getWorks()
        {
            return workData;
        }

        public DataTable getShoppings()
        {
            return shoppingData;
        }   
    }
}
