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
using System.Web;


namespace Editing_Tool
{
    [ComVisibleAttribute(true)]
    [PermissionSet(SecurityAction.Demand, Name = "FullTrust")]
    public partial class Form1 : Form
    {
        Parser textParser = new Parser();
        private const string PLUGIN_URL =
                    @"http://www.ug.it.usyd.edu.au/~pdat4074/ITLS/index.html";
        private IGEPlugin ge = null;

        private Hashtable d_pool = new Hashtable();
        private TripPool t_pool ;
        private int l_selk = -1;
        private Rec record = new Rec();
        private IKmlCamera view;
        private int tpi;
        private String kmlfpath, kmlex, kmln, txtfpath, txtex, txtn, poifpath, poiex, poin;
        private int v_sw = 1;
        private int tp_mode = 1;
        private PointPool p_pool = null;

        private String header = "";
        private String body = "";
        private String footer = "";

        private System.IO.StreamReader objReader;
        private String d_name = "";

        private Controller core;

        //Editor Class

        TextFileEditor txtEditor;

        //Excel File Class

        extractPOIData POIData;

        //interface stuff

        bool webBrowserSet;
        bool textPointSet;
        bool KMLPointSet;
        int temp;
        IKmlPlacemark start;
        IKmlPlacemark finish;
        IKmlPlacemark KMLStart;
        IKmlPlacemark KMLFinish;
        bool textPointHide;
        bool KMLPointhide;
        //ComboBox KMLTripOptions;
        ArrayList list = new ArrayList();

        //Testing variables

        ArrayList pointsPerSeconds;
        String estimatedTimeOfCompletion = "";
        int totalPoints = 0;
        double average = 0;
        String statusText;

        //Ruler variables
        bool rulerMode;
        IKmlPlacemark line;
        IKmlLineString linePoints;
        IKmlFolder ruler;
        int lineNumber;
        double rulerDistance;
        IKmlPoint lastPoint;
        int pointsMeasured;

        public Form1()
        {
            InitializeComponent();
            //These are all the Mouse Event Handlers to change Button colors
            txtEditor = new TextFileEditor();
            POIData = new extractPOIData();
            btLoad.MouseEnter += new EventHandler(btLoad_MouseEnter);
            btLoad.MouseLeave += new EventHandler(btLoad_MouseLeave);
            btKMLBrowse.MouseEnter += new EventHandler(btKMLBrowse_MouseEnter);
            btKMLBrowse.MouseLeave += new EventHandler(btKMLBrowse_MouseLeave);
            btTXTBrowse.MouseEnter += new EventHandler(btTXTBrowse_MouseEnter);
            btTXTBrowse.MouseLeave += new EventHandler(btTXTBrowse_MouseLeave);
            btDel.MouseEnter += new EventHandler(btDel_MouseEnter);
            btDel.MouseLeave += new EventHandler(btDel_MouseLeave);
            btSpl.MouseEnter += new EventHandler(btSpl_MouseEnter);
            btSpl.MouseLeave += new EventHandler(btSpl_MouseLeave);
            btIns.MouseEnter += new EventHandler(btInsert_MouseEnter);
            btIns.MouseLeave += new EventHandler(btInsert_MouseLeave);
            btJoi.MouseEnter += new EventHandler(btJoi_MouseEnter);
            btJoi.MouseLeave += new EventHandler(btJoi_MouseLeave);
            btClr.MouseEnter += new EventHandler(btClear_MouseEnter);
            btClr.MouseLeave += new EventHandler(btClear_MouseLeave);
            btCrt.MouseEnter += new EventHandler(btCreate_MouseEnter);
            btCrt.MouseLeave += new EventHandler(btCreate_MouseLeave);
            btMkStart.MouseEnter += new EventHandler(btMkStr_MouseEnter);
            btMkStart.MouseLeave += new EventHandler(btMkStr_MouseLeave);
            btMkFinish.MouseEnter += new EventHandler(btMkFin_MouseEnter);
            btMkFinish.MouseLeave += new EventHandler(btMkFin_MouseLeave);
            btUndo.MouseEnter += new EventHandler(btUndo_MouseEnter);
            btUndo.MouseLeave += new EventHandler(btUndo_MouseLeave);
            btCommit.MouseEnter += new EventHandler(btCommit_MouseEnter);
            btCommit.MouseLeave += new EventHandler(btCommit_MouseLeave);
            btColorChange.MouseEnter += new EventHandler(btColorChange_MouseEnter);
            btColorChange.MouseLeave += new EventHandler(btColorChange_MouseLeave);
            btReset.MouseEnter += new EventHandler(btReset_MouseEnter);
            btReset.MouseLeave += new EventHandler(btReset_MouseLeave);
            btHidePanel.MouseEnter += new EventHandler(btHide_MouseEnter);
            btHidePanel.MouseLeave += new EventHandler(btHide_MouseLeave);
            btUnhidePanel.MouseEnter += new EventHandler(btUnhide_MouseEnter);
            btUnhidePanel.MouseLeave += new EventHandler(btUnhide_MouseLeave);
            btPOIBrowse.MouseEnter += new EventHandler(btPOIBrowse_MouseEnter);
            btPOIBrowse.MouseLeave += new EventHandler(btPOIBrowse_MouseLeave);
            btControlPanel.MouseEnter += new EventHandler(btControlPanel_MouseEnter);
            btControlPanel.MouseLeave += new EventHandler(btControlPanel_MouseLeave);
            btControlPanelHide.MouseEnter += new EventHandler(btControlPanelHide_MouseEnter);
            btControlPanelHide.MouseLeave += new EventHandler(btControlPanelHide_MouseLeave);
            btMatch.MouseEnter += new EventHandler(btMatch_MouseEnter);
            btMatch.MouseLeave += new EventHandler(btMatch_MouseLeave);
            btHideTextPoints.MouseEnter += new EventHandler(btHideTextPoints_MouseEnter);
            btHideTextPoints.MouseLeave += new EventHandler(btHideTextPoints_MouseLeave);
            btHideKMLPoints.MouseEnter += new EventHandler(btHideKMLPoints_MouseEnter);
            btHideKMLPoints.MouseLeave += new EventHandler(btHideKMLPoints_MouseLeave);
            btResetTilt.MouseEnter += new EventHandler(btResetTilt_MouseEnter);
            btResetTilt.MouseLeave += new EventHandler(btResetTilt_MouseLeave);
            btTripExpand.MouseEnter += new EventHandler(btTripExpand_MouseEnter);
            btTripExpand.MouseLeave += new EventHandler(btTripExpand_MouseLeave);
            btTripContract.MouseEnter += new EventHandler(btTripContract_MouseEnter);
            btTripContract.MouseLeave += new EventHandler(btTripContract_MouseLeave);
            btRuler.MouseEnter += new EventHandler(btRuler_MouseEnter);
            btRuler.MouseLeave += new EventHandler(btRuler_MouseLeave);
            
            //other interface variables

            webBrowserSet = false;
            textPointSet = false;
            KMLPointSet = false;
            temp = 0;
            textPointHide = false;
            KMLPointhide = false;
            rulerMode = false;
            lineNumber = 0;
            pointsMeasured = 0;
            rulerDistance = 0;


            //Testing Variables
            pointsPerSeconds = new ArrayList();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            panel1.Visible = false;
            webBrowser1.Navigate(PLUGIN_URL);
            webBrowser1.ObjectForScripting = this;
            panel2.Visible = false;
            panel4.Visible = false;
            panel5.Visible = false;
            textDataPanel.Visible = false;
            webBrowser1.Width = panel3.Width;
            btUnhidePanel.Visible = false;
            btMatch.Enabled = false;
            btResetTilt.SetBounds(panel3.Width - 100, btResetTilt.Location.Y, btResetTilt.Width, btResetTilt.Height);
        }
    


  
        public void loadSession()
        {
            //If file doesnt exist, we must create it
            if (!File.Exists("data.txt"))
            {
                File.Create("data.txt").Dispose();
            }
            // Check if file contains data and correct data before attempting reload the session
            if (new FileInfo("data.txt").Length > 0)
            {
                using (StreamReader reader = new StreamReader("data.txt"))
                {
                    string line;
                    while ((line = reader.ReadLine()) != null)
                    {
                        list.Add(line); // Add to list.
                        Console.WriteLine(line); // Write to console.
                    }
                    // close the stream
                    reader.Close();
                }


                if (list.Count == 6)
                {
                    kmlfpath = list[0].ToString();
                    kmlex = list[1].ToString();
                    kmln = list[2].ToString();

                    txtfpath = list[3].ToString();
                    txtex = list[4].ToString();
                    txtn = list[5].ToString();

                    btLoad.PerformClick();
                }
                else
                {
                    MessageBox.Show("Cannot peform Restart due to error inside data.txt. Data.txt is cleared.");
                }
                // Must clear the textfile after it has been reload a session /
                File.Create("data.txt").Dispose();

            }
           
        }

        public void JSInitSuccessCallback_(object pluginInstance)
        {
            ge = (IGEPlugin)pluginInstance;
            ge.getNavigationControl().setVisibility(ge.VISIBILITY_SHOW);
            btResetTilt.Visible = true;
            ge.getLayerRoot().enableLayerById(ge.LAYER_BORDERS, 1);
            panel1.Enabled = true;
            Console.WriteLine("Google Earth GUI established");
            start = ge.createPlacemark("");
            finish = ge.createPlacemark("");
            t_pool = new TripPool(ge);

            loadSession();
        }

        public void JSInitFailureCallback_(string error)
        {
            MessageBox.Show("Error: " + error, "Plugin Load Error", MessageBoxButtons.OK,
                MessageBoxIcon.Exclamation);
        }


        /*
         * This function is called by the placemark double clicking event handler, the argument is the particular point
         */
        public void JScallName(IKmlPlacemark point)
        {
            core.highlight(point);
        }
        


        /*
         * Load button clicking event
         */
        private String correction(String input)
        {
            return System.Text.RegularExpressions.Regex.Replace(input, @"shapes/travelpoint.png", @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png");
        }

        public void D_parser()
        {
            IKmlObjectList days = ge.getFeatures().getChildNodes();
            IKmlDocument day = (IKmlDocument)days.item(0);
            d_pool[day.getName()] = day;

            d_name = day.getName().Split('_')[4];
            String[] line = new String[14];
            objReader = new System.IO.StreamReader(txtfpath);

            do
            {
                String buff = objReader.ReadLine();
                List<String> input = buff.Split('\t').ToList();
                if (input[0] == d_name)
                {
                    input.RemoveAt(0);
                    input.RemoveAt(0);
                    line = input.ToArray();
                    break;
                }
                else
                {
                    header += buff+"\n";
                }
            }
            while (objReader.Peek() != -1);
            objReader.Dispose();

            String temp= "";
            //Get Total Points in the KML File for estimated time
            IKmlObjectList trips = day.getFeatures().getChildNodes();
            int tripCount = trips.getLength();
            int currentTrip = 1;
            for (int i = 0; i != trips.getLength(); ++i)
            {
                IKmlFolder trip = (IKmlFolder)trips.item(i);
                IKmlObjectList points = trip.getFeatures().getChildNodes();
                totalPoints = totalPoints + points.getLength();
            }
            for (int i = 0; i != trips.getLength(); i++)
            {
                Module.writeToTestingFile("Parsing KML Data for Trip"+(i+1)+" Time:"+DateTime.Now.ToString());
                String[] att = new String[4];
                IKmlFolder trip = (IKmlFolder)trips.item(i);     
                att[0] = line[2];
                att[1] = line[0];
                att[2] = line[4];
                att[3] = line[5];
                T_parser(trip, tripCount, currentTrip);
                ++currentTrip;
               // att[8] = Math.Round((double.Parse(att[7]) / Module.durationConverter(att[6])), 3).ToString();

                t_pool.addGlobalVariables(att);

                t_pool.add(trip);
                
                /*if (i + 1 <trips.getLength())
                {
                    temp = objReader.ReadLine();
                    List<String> input = temp.Split('\t').ToList();
                    input.RemoveAt(0);
                    input.RemoveAt(0);
                    line = input.ToArray();
                } */
            }
            Module.averagePointsPerSecond(pointsPerSeconds);
            footer += temp+'\n';
        }

        public IKmlPlacemark mk_point(double lon, double lat,String name, String style)
        {
            IKmlPlacemark place = ge.createPlacemark("");
            place.setName(name);
            IKmlPoint temp = ge.createPoint("");
            temp.setLatitude(lat);
            temp.setLongitude(lon);
            place.setGeometry(temp);
            return place;
        }

        public void T_parser(IKmlFolder trip, int tripCount, int currentTrip)
        {
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            int lastRecordedTime = DateTime.Now.Second;
            int pointsInSecond = 0;
            for (int ii = 0; ii != points.getLength(); ++ii)
            {
                Console.Clear();
                Console.WriteLine(statusText + "\n" + "Trip " + currentTrip + " out of " + tripCount + "\n" + "Point " + (ii+1) + " out of " + points.getLength() + "\n" + (Math.Round(Convert.ToDouble(ii) / points.getLength() * 100, 0).ToString() + "%") + "\nTime Remaining: " + estimatedTimeOfCompletion + "\nAverage points per second: " + (int)average);
                if (lastRecordedTime == DateTime.Now.Second)
                {
                    ++pointsInSecond;
                }
                else
                {
                    totalPoints = totalPoints - pointsInSecond;
                    pointsPerSeconds.Add(pointsInSecond);
                    average = Module.averagePointsPerSecond(pointsPerSeconds);
                    double secondsLeft = totalPoints / average;
                    estimatedTimeOfCompletion = Module.getNewTime("00:00:00", secondsLeft.ToString(), 2);
                    Module.writeToTestingFile("Points this second: " + pointsInSecond);
                    pointsInSecond = 0;
                    lastRecordedTime = DateTime.Now.Second;
                }
                IKmlPlacemark point = (IKmlPlacemark)points.item(ii);
                String temp = point.getComputedStyle().getIconStyle().getColor().get();
                IKmlStyleMap sm = ge.createStyleMap("");
                IKmlStyle normal = mkStyle(temp, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3);
                IKmlStyle highlight = mkStyle(temp, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4);
                sm.setNormalStyle(normal);
                sm.setHighlightStyle(highlight);
                point.setStyleSelector(sm);
                System.Diagnostics.Process hello;
                System.Diagnostics.ProcessPriorityClass prioritySet;
                prioritySet

                //webBrowser1.Document.InvokeScript("JSmk", new object[] { point });
            }
        }

        public IKmlStyle mkStyle(String col, String shape, float size)
        {

            IKmlIcon icon = ge.createIcon("");
            icon.setHref(shape);
            IKmlStyle style = ge.createStyle("");
            style.getIconStyle().getColor().set(col);
            style.getIconStyle().setIcon(icon);
            style.getIconStyle().setScale(size);
            return style;
        }

        /*
         * Shows the starting and finshing point of the selected trip on the GE, 
         * also make sure only the checked trips are visable when the view mode == select
         */
        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cblTrips.SelectedItem != null && tp_mode == 1)
            {
                String selkd = cblTrips.SelectedItem.ToString();
                if (cblTrips.SelectedIndex != l_selk)
                {
                    if (v_sw == 1)
                    {
                        t_pool.highlight(selkd);
                        ge.getView().setAbstractView(core.zoom(selkd));
                    }
                }
                else if (rbtSel.Checked)
                {
                    IKmlFolder trip = t_pool.getByName(selkd);
                    if (trip.getVisibility() == 1)
                    {
                        trip.setVisibility(0);
                    }
                    else
                    {
                        trip.setVisibility(1);
                    }
                }
                l_selk = cblTrips.SelectedIndex;
            }
            else if (cblTrips.SelectedItem != null && tp_mode == 0)
            {
                Hashtable cords = p_pool.getCoordinates((String)cblTrips.SelectedItems[0]);
                ge.getView().setAbstractView(core.focus(p_pool.getCoordinates((String)cblTrips.SelectedItems[0])));
                p_pool.highlight((String)cblTrips.SelectedItems[0]);
                l_selk = cblTrips.SelectedIndex;
            }
        }


        /*
         * This function is used for handling the double click event on the checklist box which won't be caught by the 
         * 'checkedListBox1_SelectedIndexChanged' function in order to make sure only the selected trips are displayed 
         * under the select view mode.
         */
        private void checkedListBox1_DoubleClick(object sender, EventArgs e)
 	    {
            if (rbtSel.Checked && tp_mode == 1)
 	        {
 	            String selkd = cblTrips.SelectedItem.ToString();
 	            IKmlFolder trip = t_pool.getByName(selkd);
 	            if (trip.getVisibility() == 1)
 	            {
 	                trip.setVisibility(0);
 	            }
 	            else
 	            {
 	                trip.setVisibility(1);
 	            }
 	        }
 	    }
                
        /********************************************** Form Button Operations *********************************************/
        
        /******************
         * Load Data
         * *****************/

        private void btLoad_Click(object sender, EventArgs e)
        {
           
            data ParsedData = new data();
            data ParsedDataForDay = new data();
            if (ge != null)
            {
                if (kmlex == ".kml" && txtex == ".txt" /*&& ( poiex == ".xlsx" || poiex == ".xls" )*/ )
                {
                    try
                    {
                        statusText = "Reading KML Data";
                        ge.getFeatures().appendChild(ge.parseKml((System.IO.File.ReadAllText(kmlfpath))));
                        statusText = "Parsing KML Data";
                        D_parser();
                        statusText = "Creating Trip Selector";
                        foreach (String trip in t_pool.getNames())
                        {
                            cblTrips.Items.Add(trip);
                        }
                        core = new Controller(ge, t_pool, record);
                        panel2.Visible = true;
                        panel4.Visible = true;
                        panel5.Visible = true;
                        panel1.Visible = true;
                         
                        //Now we'll show the textDataGrid to the user
                        btUnhidePanelFunction();
                        statusText = "Parsing Text File Data";
                        Module.writeToTestingFile("Parsing Text File Data at " + DateTime.Now.ToString());
                        //If the file input is correct we will parse the text file into memory wehere it can be easily edited by the user
                        textParser.parseFileToDataSet(txtfpath, ParsedData, ParsedDataForDay, d_name);
                        txtEditor.setViewerTotal(ParsedData);
                        txtEditor.setViewer(ParsedDataForDay);
                        statusText = "Setting up Interface";
                        Module.writeToTestingFile("Setting up interface at " + DateTime.Now.ToString());
                        //Now we'll add the data to the viewer in the Form
                        textDataGrid.DataSource = txtEditor.getViewer();
                        KMLTripView.DataSource = t_pool.getTripDetails();
                        textDataGrid.Columns["Day"].Visible = false;
                        textDataGrid.Columns["HouseHold"].Visible = false;
                        textDataGrid.Columns["Person"].Visible = false;
                        textDataGrid.Columns["Date"].Visible = false;
                        textDataGrid.Columns["Weekday"].Visible = false;
                        KMLTripView.Columns["HouseHoldID"].Visible = false;
                        KMLTripView.Columns["Trip"].Visible = false;
                        KMLTripView.Columns["Person"].Visible = false;
                        KMLTripView.Columns["Day"].Visible = false;
                        KMLTripView.Columns["Date"].Visible = false;
                        KMLTripView.Columns["Weekday"].Visible = false;
                        KMLTripView.Columns["Remain"].Visible = false;
                        houseHoldText.Text = txtEditor.getViewer().Rows[0]["HouseHold"].ToString();
                        personText.Text = txtEditor.getViewer().Rows[0]["Person"].ToString();
                        dateText.Text = txtEditor.getViewer().Rows[0]["Date"].ToString();
                        dayText.Text = txtEditor.getViewer().Rows[0]["Weekday"].ToString();
                        if (t_pool.getSize() > txtEditor.getViewer().Rows.Count)
                        {
                            tripConflictText.ForeColor = System.Drawing.Color.Red;
                            tripConflictText.Text = "KML and Text File trips don't match.";
                        }
                        if (poifpath != null)
                        {
                            statusText = "Parsing POI Data";
                            Module.writeToTestingFile("Parsing POI File Data at " + DateTime.Now.ToString());
                            POIData.getDataFromExcelFile(poifpath, txtEditor.getViewer());
                        }
                        statusText = "Creating POI on map";
                        setPOIsOnMap(POIData.getHomes(), POIData.getSchools(), POIData.getWorks(), POIData.getShoppings());
                        ge.getView().setAbstractView(core.allocate());
                        statusText = "Matching KML and Text Data";
                        Module.writeToTestingFile("Match KML and Text Data at " + DateTime.Now.ToString());
                        matchKMLTripstoTextDataTrips();
                        DataGridViewComboBoxColumn temp = generateDropDownListForTrips();
                        KMLTripView.Columns.Add(temp); ;
                        match_check();
                        //Enable the Rest Tilt button
                        btResetTilt.Visible = true;
                        //btResetTilt.SetBounds((int)ge.getNavigationControl().getScreenXY().getX(), (int)ge.getNavigationControl().getScreenXY().getY() + 20, btResetTilt.Size.Width, btResetTilt.Size.Height);

                        // Disable load button until one of the file browse button is click onto
                        btLoad.Enabled = false;
                        Module.writeToTestingFile("Finish at " + DateTime.Now.ToString());
                        Module.writeTestingFile();
                        
                    }
                    catch (Exception)
                    {
                        MessageBox.Show("Unable to load '" + kmln + "'.", "ERROR");
                    }
                }
                else if (kmlfpath == null && txtfpath == null)
                {
                    MessageBox.Show("Please choose the input KML and output TXT files.", "Caution");
                }
                else
                {
                    MessageBox.Show("Wrong file format.", "Caution");
                }
            }
        }

        public DataGridViewComboBoxColumn generateDropDownListForTrips()
        {
            bool exists = false;
            //This function will generate the list of trips that can be used in the KMLTripView section
            List<String> tripList = new List<String>();
            foreach (DataRow rowText in txtEditor.getViewer().Rows)
            {
                foreach (DataRow rowKML in t_pool.getTripDetails().Rows)
                {
                    if (rowText["KMLTrip"].ToString().Equals(rowKML["KMLTrip"].ToString()))
                    {
                        exists = true;
                    }
                }
                if (!exists)
                {
                    tripList.Add(rowText["KMLTrip"].ToString());
                }
            }
            DataGridViewComboBoxColumn tripsColumn = new DataGridViewComboBoxColumn();
            tripsColumn.DataSource = tripList;
            tripsColumn.HeaderText = "KML Trip";
            return tripsColumn;
        }

        public void match_check()
        {
            for (int i = 0; i < txtEditor.getViewer().Rows.Count; i++)
            {
                if (txtEditor.getViewer().Rows[i]["KMLTrip"].ToString() == "")
                {
                    btMatch.Enabled = false;
                    controlPanel.Enabled = false;
                    btDel.ForeColor = System.Drawing.Color.DarkGray;
                    btSpl.ForeColor = System.Drawing.Color.DarkGray;
                    btJoi.ForeColor = System.Drawing.Color.DarkGray;
                    btIns.ForeColor = System.Drawing.Color.DarkGray;
                    btClr.ForeColor = System.Drawing.Color.DarkGray;
                    btCrt.ForeColor = System.Drawing.Color.DarkGray;
                    btMkStart.ForeColor = System.Drawing.Color.DarkGray;
                    btMkFinish.ForeColor = System.Drawing.Color.DarkGray;
                    btUndo.ForeColor = System.Drawing.Color.DarkGray;
                    btCommit.ForeColor = System.Drawing.Color.DarkGray;
                    btColorChange.ForeColor = System.Drawing.Color.DarkGray;
                    return;
                }
            }
            btMatch.Enabled = true;
            controlPanel.Enabled = true;
            btDel.ForeColor = System.Drawing.Color.Black;
            btSpl.ForeColor = System.Drawing.Color.Black;
            btJoi.ForeColor = System.Drawing.Color.Black;
            btIns.ForeColor = System.Drawing.Color.Black;
            btClr.ForeColor = System.Drawing.Color.Black;
            btCrt.ForeColor = System.Drawing.Color.Black;
            btMkStart.ForeColor = System.Drawing.Color.Black;
            btMkFinish.ForeColor = System.Drawing.Color.Black;
            btUndo.ForeColor = System.Drawing.Color.Black;
            btCommit.ForeColor = System.Drawing.Color.Black;
            btColorChange.ForeColor = System.Drawing.Color.Black;
        }

        public void matchKMLTripstoTextDataTrips()
        {
            //This function will match the KML trips to the Text Data trips if they match
            DataTable KMLTrips = t_pool.getTripDetails();
            DataTable TextDataTrips = txtEditor.getViewer();
            //Now once we have both the data tables we can do the matching
            //First we'll see which dataTable has more values
            if (KMLTrips.Rows.Count == Math.Max(KMLTrips.Rows.Count, TextDataTrips.Rows.Count))
            {
                //That means there are more KML trips than Text Data Trips which usually should be the case.
                //Now we'll iterate through all the KML trips and find it's match in the Text Data Trips
                for (int i = 0; i != KMLTrips.Rows.Count; ++i)
                {
                    for (int j = 0; j != TextDataTrips.Rows.Count; ++j)
                    {
                        if (KMLTrips.Rows[i]["Start Time"].ToString().Trim().Equals(TextDataTrips.Rows[j]["Start"].ToString().Trim()) && KMLTrips.Rows[i]["Finish Time"].ToString().Trim().Equals(TextDataTrips.Rows[j]["Finish"].ToString().Trim()))
                        {
                            //This means that the trips match
                            TextDataTrips.Rows[j]["KMLTrip"] = i + 1;
                            txtEditor.completeMissingData(t_pool, txtEditor.getViewer().Rows[j]["KMLTrip"].ToString());  // This will complete the missing data
                        }
                    }
                }                    
            }
        }

        /**********************************************
         * Create POIs on map
         **************************************/

        public void setPOIsOnMap(DataTable homes, DataTable schools, DataTable works, DataTable shoppings )
        {
            //First get the Homes
            IKmlIcon homeIcon = ge.createIcon("");
            homeIcon.setHref("http://maps.google.com/mapfiles/kml/shapes/ranger_station.png");
            IKmlStyle homeStyle = ge.createStyle("");
            homeStyle.getIconStyle().setIcon(homeIcon);
            for (int i = 0;  i < homes.Rows.Count; ++i)
            {
                IKmlPlacemark point = mk_point(Convert.ToDouble(homes.Rows[i]["Longitude"]), Convert.ToDouble(homes.Rows[i]["Latitude"]), "Home", "");
                point.setStyleSelector(homeStyle);
                ge.getFeatures().appendChild(point);
            }

            IKmlIcon schoolIcon = ge.createIcon("");
            schoolIcon.setHref("http://www.vishwaas.org.au/icons/school.png");
            IKmlStyle schoolStyle = ge.createStyle("");
            schoolStyle.getIconStyle().setIcon(schoolIcon);
            for (int i = 0; i < schools.Rows.Count; ++i)
            {
                IKmlPlacemark point = mk_point(Convert.ToDouble(schools.Rows[i]["Longitude"]), Convert.ToDouble(schools.Rows[i]["Latitude"]), schools.Rows[i]["Name of Institution"].ToString(), "");
                point.setStyleSelector(schoolStyle);
                ge.getFeatures().appendChild(point);
            }

            IKmlIcon workIcon = ge.createIcon("");
            workIcon.setHref("http://www.vishwaas.org.au/icons/work.png");
            IKmlStyle workStyle = ge.createStyle("");
            workStyle.getIconStyle().setIcon(workIcon);
            for (int i = 0; i < works.Rows.Count; ++i)
            {
                IKmlPlacemark point = mk_point(Convert.ToDouble(works.Rows[i]["Longitude"]), Convert.ToDouble(works.Rows[i]["Latitude"]), works.Rows[i]["Building Name"].ToString(), "");
                point.setStyleSelector(workStyle);
                ge.getFeatures().appendChild(point);
            }

            IKmlIcon shopIcon = ge.createIcon("");
            shopIcon.setHref("http://maps.google.com/mapfiles/kml/shapes/shopping.png");
            IKmlStyle shopStyle = ge.createStyle("");
            shopStyle.getIconStyle().setIcon(shopIcon);
            for (int i = 0; i < shoppings.Rows.Count; ++i)
            {
                IKmlPlacemark point = mk_point(Convert.ToDouble(shoppings.Rows[i]["Longitude"]), Convert.ToDouble(shoppings.Rows[i]["Latitude"]), shoppings.Rows[i]["Shop Name"].ToString(), "");
                point.setStyleSelector(shopStyle);
                ge.getFeatures().appendChild(point);
            }

        }
       
        /**********
         * Delete
         * ********/
        private void btDel_Click(object sender, EventArgs e)
        {
            // make sure only one trip is checked
            if (cblTrips.CheckedItems.Count == 1)
            {
                if (core.delete((String)cblTrips.CheckedItems[0]))
                {
                    txtEditor.deleteTrip(d_name, Module.getIndex((String)cblTrips.CheckedItems[0]).ToString(), t_pool);
                    cblTrips.Items.Clear();
                    cblTrips.Items.AddRange(t_pool.getNames().ToArray());
                    lastOperation.Text = txtEditor.getLastUndoTableEntry();
                    if (lastOperation.Text == "")
                        panel8.Visible = false;
                    else
                        panel8.Visible = true;
                }
                else
                {
                    MessageBox.Show("Failed to delete the trip", "Error");
                }
            }
            else
            {
                MessageBox.Show("Select ONE trip to delete at a time.", "Caution");
            }
        }
        


        /************************
         * Split button clicking event
         ******************************/
        private void btSpl_Click(object sender, EventArgs e)
       {
            //make sure the user has selected a point for spliting
           if (core == null || core.get_sel_pt() == null) { MessageBox.Show("Select a split point first.", "Caution"); return; }

            t_pool.de_highlight();
            core.de_highlight();
            IKmlPlacemark temp = core.get_sel_pt();
            String spl = t_pool.getParent(core.get_sel_pt().getName());
            if (core.split(core.get_sel_pt()))
            {

                txtEditor.splitTrip(d_name,Module.getIndex(spl).ToString(),t_pool.getStart(t_pool.getByName("Trip_"+(Module.getIndex(spl)+1).ToString())), t_pool.getFinish(t_pool.getByName(spl)), t_pool);
                 txtEditor.completeMissingData(t_pool);
                core.de_highlight();
                cblTrips.Items.Clear();
                cblTrips.Items.AddRange(t_pool.getNames().ToArray());
                lastOperation.Text = txtEditor.getLastUndoTableEntry();
                if (lastOperation.Text == "")
                    panel8.Visible = false;
                else
                    panel8.Visible = true;
            }
            else
            {
                MessageBox.Show("Failed to split a trip a point.","Error");
            }
        }


        /*******************************
         * Join button clicking event
         *******************************/
        private void btJoi_Click(object sender, EventArgs e)
        {
            //make sure 2 trips are checked for join
          if (cblTrips.CheckedItems.Count == 2 && Math.Abs(cblTrips.CheckedIndices[1] - cblTrips.CheckedIndices[0]) == 1)
            {
                t_pool.de_highlight();
                core.de_highlight();

                if (core.join((String)cblTrips.CheckedItems[0], (String)cblTrips.CheckedItems[1]))
                {
                    txtEditor.joinTrips(d_name, Module.getIndex((String)cblTrips.CheckedItems[0]).ToString(), Module.getIndex((String)cblTrips.CheckedItems[1]).ToString(), t_pool);
                    cblTrips.Items.Clear();
                    cblTrips.Items.AddRange(t_pool.getNames().ToArray());
                    lastOperation.Text = txtEditor.getLastUndoTableEntry();
                    if (lastOperation.Text == "")
                        panel8.Visible = false;
                    else
                        panel8.Visible = true;
                }
                else
                {
                    MessageBox.Show("Failed to join 2 trips.","Error");
                }
            }
            else
            {
                MessageBox.Show("Select two consecutive trips to join them together.", "Caution");
            }
        }


        /*********************
         * Undo funcion
         **********************/
        private void btUndo_Click(object sender, EventArgs e)
        {
            Hashtable mem = record.undo();
            if (mem != null)
            {
                t_pool.de_highlight();
                core.de_highlight();
                if (p_pool != null)
                {
                    p_pool.dehighlight();
                }

                if (!core.undo(mem))
                {
                    MessageBox.Show("Failed to undo previouse operation.", "Error");
                }
                else if (mem["opt"] != "crt" && mem["opt"] != "ch_color")
                {
                    txtEditor.undoTripAction(t_pool);
                    cblTrips.Items.Clear();
                    cblTrips.Items.AddRange(t_pool.getNames().ToArray());
                    lastOperation.Text = txtEditor.getLastUndoTableEntry();
                    if (lastOperation.Text == "")
                        panel8.Visible = false;
                    else
                        panel8.Visible = true;
                }
            }
        }

 
        /****************************
         * browse TXT file
         ****************************/
        private void btTXTBrowse_Click(object sender, EventArgs e)
        {
            OpenFileDialog open_fd = new OpenFileDialog();
	        open_fd.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyComputer);
	        open_fd.ShowDialog();
            txtfpath = open_fd.FileName;
	        txtex = Path.GetExtension(txtfpath);
	        txtn = Path.GetFileName(txtfpath);
            tbTXTBrowse.Text = txtfpath;
            btLoad.Enabled = true;
        }

        /****************************
         * browse POI file
         ****************************/
        private void btPOIBrowse_Click(object sender, EventArgs e)
        {
            OpenFileDialog open_fd = new OpenFileDialog();
            open_fd.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyComputer);
            open_fd.ShowDialog();
            poifpath = open_fd.FileName;
            poiex = Path.GetExtension(poifpath);
            poin = Path.GetFileName(poifpath);
            tbPOIBrowse.Text = poifpath;

            btLoad.Enabled = true;
        }


        int tig = 0;

        /***********************
         * browse KML file
         **************************/

        private void btKMLBrowse_Click(object sender, EventArgs e)
        {
            OpenFileDialog open_fd = new OpenFileDialog();
            open_fd.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyComputer);
            open_fd.ShowDialog();
            kmlfpath = open_fd.FileName;
            kmlex = Path.GetExtension(kmlfpath);
            kmln = Path.GetFileName(kmlfpath);
            tbKMLBrowse.Text = kmlfpath;

            btLoad.Enabled = true;
        }

        /*********************
         * Commit
         **********************/
        private void btCommit_Click(object sender, EventArgs e)
        {
           /* if (objReader != null)
            {
                String fname = System.Text.RegularExpressions.Regex.Replace(txtfpath, txtn + "$", "new_" + txtn);
                MessageBox.Show(fname);
                ArrayList datas = t_pool.getAttrs();
                body = "";
                int i = 1;
                foreach (String[] data in datas)
                {
                    String line = "";
                    foreach (String entry in data)
                    {
                        line += entry + "\t";
                    }
                    line = d_name + "\t" + i.ToString() + "\t" + line + "\n";
                    body += line;
                    i++;
                }

                do
                {
                    footer += objReader.ReadLine() + "\n";
                }
                while (objReader.Peek() != -1);
                TextWriter tw = new StreamWriter(fname);
                tw.Write(header + body + footer);
                tw.Close();
            } */

            txtEditor.writeTextToFile(txtfpath);  // This will write the information to the text file
        }

        /***************
         * Unknown Button
         * *********************/
        private void button2_Click(object sender, EventArgs e)
        {
            IKmlFolder trip = t_pool.getByName((String)cblTrips.CheckedItems[0]);
            double sum = 0;
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            for (int i = 0; i != (points.getLength()); i++)
            {
                if (i != 0)
                {
                    sum += Module.getDistance((IKmlPlacemark)points.item(i));
                }
            }
            MessageBox.Show(sum.ToString());

        }

        /*******************************
         * Clearing the screen
         ***********************************/

        private void btClr_Click(object sender, EventArgs e)
        {
            foreach (int trip in cblTrips.CheckedIndices)
            {
                cblTrips.SetItemCheckState(trip, 0);
            }
            t_pool.de_highlight();
            if (core != null && core.get_sel_pt() != null)
            {
                core.de_highlight();
            }
        }
        
        /*************************
         * Inserting a trip
         *****************************/

        private void btIns_Click(object sender, EventArgs e)
        {
            if (cblTrips.CheckedItems.Count == 2 && Math.Abs(cblTrips.CheckedIndices[1] - cblTrips.CheckedIndices[0]) == 1 || (cblTrips.CheckedItems.Count == 2 && cblTrips.CheckedIndices[0] == 0 && cblTrips.CheckedIndices[1] == cblTrips.Items.Count-1 ))
            {
                //This will ensure that the user has selected 
                //1.Two consecutive trips OR
                //2. The first and the last trip. So the user can basically use this function to create a back to home trip.
                if (!core.insert((String)cblTrips.CheckedItems[0], (String)cblTrips.CheckedItems[1]))
                {
                    MessageBox.Show("Failed to insert a trip.", "Error");
                }
                else
                {
                    txtEditor.insertTrip(t_pool.getByName((String)cblTrips.CheckedItems[1]), Module.getIndex((String)cblTrips.CheckedItems[1]).ToString(), t_pool);
                    cblTrips.Items.Clear();
                    cblTrips.Items.AddRange(t_pool.getNames().ToArray());
                    lastOperation.Text = txtEditor.getLastUndoTableEntry();
                    if (lastOperation.Text == "")
                        panel8.Visible = false;
                    else
                        panel8.Visible = true;
                }
            }
            else
            {
                MessageBox.Show("Must select two trips to perform insert trip in between");
            }
        }


        /******************************
         * Reset Application
         ******************************/

        private void btReset_Click(object sender, EventArgs e)
        {
            DialogResult result;
            result = MessageBox.Show("Are you sure you want to reset to the beginning", "Reset Confirmation", MessageBoxButtons.YesNo);

            if (result == DialogResult.No)
            {
                
            }

            if (result == DialogResult.Yes)
            {
                saveSession();
                Application.Restart();
                 

                 
            }
        }

        private void saveSession()
        {
            
            // create a writer and open the file
            TextWriter tw = new StreamWriter("data.txt");

            

            // write the rest of the text lines
            tw.WriteLine(kmlfpath);
            tw.WriteLine(kmlex);
            tw.WriteLine(kmln);

            tw.WriteLine(txtfpath);
            tw.WriteLine(txtex);
            tw.WriteLine(txtn);


            // close the stream
            tw.Close();

            ////// read the text file back ...
            ////// create reader & open file
            ////TextReader tr = new StreamReader("date.txt");

            ////// read first line of text (here date/time)
            ////Console.WriteLine(tr.ReadLine());

            ////// read the text, next 2 lines
            ////Console.WriteLine(tr.ReadLine());
            ////Console.WriteLine(tr.ReadLine());

            ////// read the rest of the text lines
            ////Console.WriteLine(tr.ReadToEnd());

            //// close the stream
            ////tr.Close();

            //// wait to look at console display
            //Console.Write("\nPress Enter to exit ...");
            //Console.Read();
        }

   
        /* MAKE START FUNCTION
         * a modification of the EXTENDS FUNCTION
         * Will need a point and a trip.
         * The point will be the starting point of that trip
         */
        
        private void btMkStart_Click(object sender, EventArgs e)
        {
            if (core.get_sel_pt() == null)
            {
                MessageBox.Show("Select a point to make it the start", "Caution"); // checks to see if a point is selected
                return;
            }
            else if (cblTrips.CheckedItems.Count != 1)
            {
                MessageBox.Show("Please select one trip to make the point a start of", "Caution");
                return;
            }
            else
            { 
                core.de_highlight();
                t_pool.de_highlight();

                 IKmlPlacemark selected = core.get_sel_pt();

                if (selected.getName() != "")
                {
                    String t_name = t_pool.getParent(core.get_sel_pt().getName());

                    ArrayList buffer = t_pool.trimToStart(t_name, selected.getName());
                    buffer.Insert(0, t_name);
                    record.tm_start(buffer);
                    txtEditor.makeStart(Module.getIndex(t_name).ToString(), selected, t_pool);
                    core.highlight(core.get_sel_pt());
                    lastOperation.Text = txtEditor.getLastUndoTableEntry();
                    if (lastOperation.Text == "")
                        panel8.Visible = false;
                    else
                        panel8.Visible = true;
                }

                else
                {

                    String t_name = cblTrips.CheckedItems[0].ToString(); // gets the currently selected trip
                    String[] TripDetails = t_pool.getTripDetailsForTrip(Module.getIndex(t_name).ToString());
                    String speed = TripDetails[11]; // gets the speed of the currently selected trip
                    String old_distance = TripDetails[10]; // gets the distance of the currently selected trip
                    String old_start = TripDetails[7]; //gets the start time of the current trip
                    IKmlPlacemark oldStart = t_pool.getStart(t_pool.getByName(t_name));
                    t_pool.addToStart(t_name, selected); //gets the selected point and places it at the start of the currently selected trip

                    IKmlPlacemark newStart = t_pool.getStart(t_pool.getByName(t_name)); //gets the new starting point object 
                    Hashtable temp_cords = Module.getCoordinates(newStart);
                    Hashtable cords = Module.getCoordinates(oldStart);
                    String new_distance = DistanceAlgorithm.DistanceBetweenPlaces((double)temp_cords["lat"],(double)temp_cords["lon"],(double)cords["lat"],(double)cords["lon"]).ToString();
                    
                    String temp_duration = (double.Parse(new_distance) / double.Parse(speed)).ToString();
                    temp_duration = (Convert.ToDouble(temp_duration) * 3600).ToString();
                    //String newName = ((Module.durationConverter(old_start) - double.Parse(temp_duration))).ToString();
                    String newName = Module.getNewTime(old_start, temp_duration, 1);
                    if (newName.Equals("fail"))
                    {
                        //Then we'll have to revert everything that has happened before this which is not local to this function.
                        t_pool.removeFirstPoint(t_name);
                    }
                    else
                    {
                        selected.setName(newName);
                        webBrowser1.Document.InvokeScript("JSbl", new object[] { selected, "<b> " + selected.getName() + "</b><br><br><table><tr><td><b>Attribute</b></td><td><b>Value</b></td></tr><tr><td> Longitude: </td><td>" + cords["lon"] + "</td></tr>" + "<tr><td> Latitude: </td><td>" + cords["lat"] + "</td></tr></table>" }); //storing the long and lat in the balloon

                        ArrayList buf = new ArrayList();
                        buf.Add(t_name);
                        buf.Add(selected);
                        record.mk_start(buf);
                        
                        txtEditor.makeStart(Module.getIndex(t_name).ToString(), selected, t_pool);
                        core.highlight(core.get_sel_pt());
                        lastOperation.Text = txtEditor.getLastUndoTableEntry();
                        if (lastOperation.Text == "")
                            panel8.Visible = false;
                        else
                            panel8.Visible = true;
                    }
                }
                core.rm_sel_pt();
            }
        }

        private String convertToTime(String duration)
        {
            double hh;
            double mm;
            double ss;

            hh = (int)((double.Parse(duration) / 3600));
            mm = (int)(((double.Parse(duration) / 3600 - hh ) * 60)) ;
            ss =(int)(((((double.Parse(duration) / 3600 - hh) * 60 - mm) * 60)));
            
          return hh.ToString() + ":" + mm.ToString() + ":" + ss.ToString();
        }

        /* MAKE FINISH FUNCTION
         * Makes a point become the last point of a trip. 
         */


        private void btMkFin_Click(object sender, EventArgs e)
        {
            if (core.get_sel_pt() == null)
            {
                MessageBox.Show("Select a point to make it the end", "Caution");
                return;
            }
            else if (cblTrips.CheckedItems.Count != 1)
            {
                MessageBox.Show("Please select one trip to make the point a start of", "Caution");
                return;
            }
            else
            {
                core.de_highlight();

                IKmlPlacemark selected = core.get_sel_pt();

                if (selected.getName() != "")
                {
                    String t_name = t_pool.getParent(core.get_sel_pt().getName());

                    ArrayList buf = t_pool.trimToEnd(t_name, selected.getName());
                    buf.Insert(0, t_name);
                    record.tm_finish(buf);

                    txtEditor.makeFinish(Module.getIndex(t_name).ToString(), selected, t_pool);
                    core.highlight(core.get_sel_pt());
                    lastOperation.Text = txtEditor.getLastUndoTableEntry();
                    if (lastOperation.Text == "")
                        panel8.Visible = false;
                    else
                        panel8.Visible = true;
                }

                else
                {

                    String t_name = cblTrips.CheckedItems[0].ToString(); // gets the currently selected trip
                    String[] TripDetails = t_pool.getTripDetailsForTrip(Module.getIndex(t_name).ToString());
                    String speed = TripDetails[11]; // gets the speed of the currently selected trip
                    String old_distance = TripDetails[10]; // gets the distance of the currently selected trip
                    String old_finish = TripDetails[8]; //gets the start time of the current trip
                    IKmlPlacemark oldFinish = t_pool.getFinish(t_pool.getByName(t_name));
                    t_pool.addToEnd(t_name, selected); //gets the selected point and places it at the start of the currently selected trip

                    IKmlPlacemark newFinish = t_pool.getFinish(t_pool.getByName(t_name)); //gets the new starting point object 
                    Hashtable temp_cords = Module.getCoordinates(newFinish);
                    Hashtable cords = Module.getCoordinates(oldFinish);
                    String new_distance = DistanceAlgorithm.DistanceBetweenPlaces((double)temp_cords["lat"], (double)temp_cords["lon"], (double)cords["lat"], (double)cords["lon"]).ToString();

                    String temp_duration = (double.Parse(new_distance) / double.Parse(speed)).ToString();
                    temp_duration = (Convert.ToDouble(temp_duration) * 3600).ToString();
                    String newName = Module.getNewTime(old_finish, temp_duration, 2);
                    if (newName.Equals("fail"))
                    {
                        //Then we'll have to revert everything that has happened before this which is not local to this function.
                        t_pool.removeLastPoint(t_name);
                    }
                    else
                    {
                        selected.setName(newName);
                        webBrowser1.Document.InvokeScript("JSbl", new object[] { selected, "<table><tr><td><b> " + selected.getName() + "</b></td></tr><br><br><tr><td><b>Attribute</b></td><td><b>Value</b></td></tr><tr><td> Longitude: </td><td>" + cords["lon"] + "</td></tr>" + "<tr><td> Latitude: </td><td>" + cords["lat"] + "</td></tr></table>" }); //storing the long and lat in the balloon

                        ArrayList buf = new ArrayList();
                        buf.Add(t_name);
                        buf.Add(selected);
                        record.mk_finish(buf);

                        txtEditor.makeFinish(Module.getIndex(t_name).ToString(), selected, t_pool);
                        core.highlight(core.get_sel_pt());
                        lastOperation.Text = txtEditor.getLastUndoTableEntry();
                        if (lastOperation.Text == "")
                            panel8.Visible = false;
                        else
                            panel8.Visible = true;
                    }

                }
                core.rm_sel_pt();
            }
        }

        /* Create button
         * this function create the event handler to invoke the create point function defined near the beginning
         */

        private void btCrt_Click(object sender, EventArgs e)
        {
            if (cblTrips.CheckedItems.Count == 0) //makes sure a trip is selected 
	        { 
 	            MessageBox.Show("Please select a trip to create a point for", "Caution"); 
 	        } 
 	         else if (cblTrips.CheckedItems.Count > 1) //makes sure only one trip is selected 
 	        { 
 	            MessageBox.Show("Please select only one trip", "Caution"); 
 	        } 
            else 
 	        {
                btCrt.Enabled = false;
                webBrowser1.Document.InvokeScript("JSct", new object[] { });
 	        } 

        }
        /*
 * Function used to create a random point on the map
 * */
        /*
         * This function is called by the globe double clicking event handler, the argument is the newly created point
         */
        public void CreatePoint(IKmlPlacemark point)
        {

            IKmlFolder trip = t_pool.getByName((String)cblTrips.CheckedItems[0]); //gets the selected trip object

            String col = ((IKmlPlacemark)trip.getFeatures().getChildNodes().item(1)).getComputedStyle().getIconStyle().getColor().get();


            IKmlStyleMap sm = ge.createStyleMap("");
            IKmlStyle normal = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3);
            IKmlStyle highlight = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4);
            sm.setNormalStyle(normal);
            sm.setHighlightStyle(highlight);



            point.setStyleSelector(sm); //getting the style of the trip

            Hashtable _temp = Module.getCoordinates(point); //getting the coordinates of a point
            GEHtmlStringBalloonCoClass temp = ge.createHtmlStringBalloon(""); // creates a balloon with the new point
            temp.setFeature(point);
            btCrt.Enabled = true;

            webBrowser1.Document.InvokeScript("JSmk", new object[] { point });

            record.crt_point(point);           

            ge.getFeatures().appendChild(point);


        }

        /*This is called by the Javascript function that will show the ruler point on the map and will do the calculation of distance */
        public void createRulerPoint(IKmlPlacemark rulerPoint, IKmlPoint point)
        {
            IKmlIcon rulerPointIcon = ge.createIcon("");
            rulerPointIcon.setHref("http://maps.google.com/mapfiles/kml/shapes/placemark_square.png");
            IKmlStyle rulerPointStyle = ge.createStyle("");
            rulerPointStyle.getIconStyle().setIcon(rulerPointIcon);
            rulerPoint.setStyleSelector(rulerPointStyle);
            ruler.getFeatures().appendChild(rulerPoint);  // Add the point to the map.
            /*We will then implement the feature that will calculate the distance between the points*/
            linePoints.getCoordinates().pushLatLngAlt(point.getLatitude(), point.getLongitude(), 0);
            line.setGeometry(linePoints);
            if (pointsMeasured != 0)
            {
                //This means this is not the first point we're measuring. Hence we should find out the distance
                //The distance will be the distance measured so far, plus the distance between the last point and the current point
                rulerDistance += Math.Round(DistanceAlgorithm.DistanceBetweenPlaces(lastPoint.getLatitude(), lastPoint.getLongitude(), point.getLatitude(), point.getLongitude()), 2);
                rulerDistanceText.Text = rulerDistance.ToString() + " km";
                ++pointsMeasured;
            }
            else
            {
                ++pointsMeasured;
            }
            lastPoint = point;
        }


        private void btHidePanel_Click(object sender, EventArgs e)
        {
            textDataPanel.Visible = false;
            webBrowser1.Width = panel3.Width - 25;
            btResetTilt.SetBounds(panel3.Width - 125, btResetTilt.Location.Y, btResetTilt.Width, btResetTilt.Height);
            btUnhidePanel.Visible = true;
        }

        private void btUnhidePanel_Click(object sender, EventArgs e)
        {
            textDataPanel.Visible = true;
            webBrowser1.Width = panel3.Width - 545;
            btResetTilt.SetBounds(webBrowser1.Width - 100, btResetTilt.Location.Y, btResetTilt.Width, btResetTilt.Height);
            btUnhidePanel.Visible = false;
        }

        private void btUnhidePanelFunction()
        {
            textDataPanel.Visible = true;
            webBrowser1.Width = panel3.Width - 545;
            btResetTilt.SetBounds(webBrowser1.Width - 100, btResetTilt.Location.Y, btResetTilt.Width, btResetTilt.Height);
        }

        private void btHideControlPanel_Click(object sender, EventArgs e)
        {
            panel2.Visible = false;
            btControlPanel.Visible = true;
            if (!webBrowserSet)
            {
                webBrowser1.SetBounds(30, webBrowser1.Location.Y, webBrowser1.Width - 30, webBrowser1.Height);
                webBrowserSet = true;
            }
        }

        private void btShowControlPanel_Click(object sender, EventArgs e)
        {
            panel2.Visible = true;
        }



        private void btTesting_Click(object sender, EventArgs e)
        {
            Test tx = new Test(core,ge,txtEditor);
            tx.run3();
        }

        private void btChanging_Click(object sender, EventArgs e)
        {
            t_pool.de_highlight();
            if (p_pool != null)
            {
                p_pool.dehighlight();
            }
            core.de_highlight();

            if (cblTrips.CheckedItems.Count != 1)
            {
                MessageBox.Show("Can only change the color of one trip at one time.", "Caution");
            }
            else
            {
                String col = t_pool.ch_col((String)cblTrips.CheckedItems[0], Module.randomCol());
                ArrayList data = new ArrayList();
                data.Add((String)cblTrips.CheckedItems[0]);
                data.Add(col);
                record.ch_col(data);
            }


        }

        


        /***********************************************Graphic Function Collection***********************************************/


        private void btLoad_MouseEnter(object sender, EventArgs e)
        {
            this.btLoad.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btLoad_MouseLeave(object sender, EventArgs e)
        {
            this.btLoad.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }
        
        private void btKMLBrowse_MouseEnter(object sender, EventArgs e)
        {
            this.btKMLBrowse.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btKMLBrowse_MouseLeave(object sender, EventArgs e)
        {
            this.btKMLBrowse.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btTXTBrowse_MouseEnter(object sender, EventArgs e)
        {
            this.btTXTBrowse.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btTXTBrowse_MouseLeave(object sender, EventArgs e)
        {
            this.btTXTBrowse.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btSpl_MouseEnter(object sender, EventArgs e)
        {
            this.btSpl.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btSpl_MouseLeave(object sender, EventArgs e)
        {
            this.btSpl.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btDel_MouseEnter(object sender, EventArgs e)
        {
            this.btDel.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btDel_MouseLeave(object sender, EventArgs e)
        {
            this.btDel.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btJoi_MouseEnter(object sender, EventArgs e)
        {
            this.btJoi.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btJoi_MouseLeave(object sender, EventArgs e)
        {
            this.btJoi.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btMkStr_MouseEnter(object sender, EventArgs e)
        {
            this.btMkStart.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btMkStr_MouseLeave(object sender, EventArgs e)
        {
            this.btMkStart.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btMkFin_MouseEnter(object sender, EventArgs e)
        {
            this.btMkFinish.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btMkFin_MouseLeave(object sender, EventArgs e)
        {
            this.btMkFinish.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btInsert_MouseEnter(object sender, EventArgs e)
        {
            this.btIns.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btInsert_MouseLeave(object sender, EventArgs e)
        {
            this.btIns.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btClear_MouseEnter(object sender, EventArgs e)
        {
            this.btClr.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btClear_MouseLeave(object sender, EventArgs e)
        {
            this.btClr.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btCreate_MouseEnter(object sender, EventArgs e)
        {
            this.btCrt.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btCreate_MouseLeave(object sender, EventArgs e)
        {
            this.btCrt.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btUndo_MouseEnter(object sender, EventArgs e)
        {
            this.btUndo.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btUndo_MouseLeave(object sender, EventArgs e)
        {
            this.btUndo.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btCommit_MouseEnter(object sender, EventArgs e)
        {
            this.btCommit.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btCommit_MouseLeave(object sender, EventArgs e)
        {
            this.btCommit.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btReset_MouseEnter(object sender, EventArgs e)
        {
            this.btReset.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btReset_MouseLeave(object sender, EventArgs e)
        {
            this.btReset.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btHide_MouseEnter(object sender, EventArgs e)
        {
            this.btHidePanel.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btHide_MouseLeave(object sender, EventArgs e)
        {
            this.btHidePanel.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btUnhide_MouseEnter(object sender, EventArgs e)
        {
            this.btUnhidePanel.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btUnhide_MouseLeave(object sender, EventArgs e)
        {
            this.btUnhidePanel.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btPOIBrowse_MouseEnter(object sender, EventArgs e)
        {
            this.btPOIBrowse.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btPOIBrowse_MouseLeave(object sender, EventArgs e)
        {
            this.btPOIBrowse.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btControlPanel_MouseEnter(object sender, EventArgs e)
        {
            this.btControlPanel.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btControlPanel_MouseLeave(object sender, EventArgs e)
        {
            this.btControlPanel.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btControlPanelHide_MouseEnter(object sender, EventArgs e)
        {
            this.btControlPanelHide.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btControlPanelHide_MouseLeave(object sender, EventArgs e)
        {
            this.btControlPanelHide.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btMatch_MouseEnter(object sender, EventArgs e)
        {
            this.btMatch.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btMatch_MouseLeave(object sender, EventArgs e)
        {
            this.btMatch.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btHideTextPoints_MouseEnter(object sender, EventArgs e)
        {
            this.btHideTextPoints.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btHideTextPoints_MouseLeave(object sender, EventArgs e)
        {
            this.btHideTextPoints.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btHideKMLPoints_MouseEnter(object sender, EventArgs e)
        {
            this.btHideKMLPoints.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btHideKMLPoints_MouseLeave(object sender, EventArgs e)
        {
            this.btHideKMLPoints.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btColorChange_MouseEnter(object sender, EventArgs e)
        {
            this.btColorChange.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btColorChange_MouseLeave(object sender, EventArgs e)
        {
            this.btColorChange.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btResetTilt_MouseEnter(object sender, EventArgs e)
        {
            this.btResetTilt.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btResetTilt_MouseLeave(object sender, EventArgs e)
        {
            this.btResetTilt.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btTripExpand_MouseEnter(object sender, EventArgs e)
        {
            this.btTripExpand.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btTripExpand_MouseLeave(object sender, EventArgs e)
        {
            this.btTripExpand.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btTripContract_MouseEnter(object sender, EventArgs e)
        {
            this.btTripContract.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btTripContract_MouseLeave(object sender, EventArgs e)
        {
            this.btTripContract.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
        }

        private void btRuler_MouseEnter(object sender, EventArgs e)
        {
            this.btRuler.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));
        }

        private void btRuler_MouseLeave(object sender, EventArgs e)
        {
            if (!rulerMode)
            {
                this.btRuler.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal));
            }
        }

        //View mode select radio button, show only the trips that are selected
        private void rbtSel_CheckedChanged(object sender, EventArgs e)
        {
            if (triger == 0)
            {
                rbtAll.PerformClick();
                triger = 1;
                foreach (String name in t_pool.getNames())
                {
                    t_pool.getByName(name).setVisibility(1);

                }
            }
            else
            {
                triger = 0;
            }
        }

        /* "All" radio button
         *  when this button is selected shows all trips
         */
        int triger = 0;

        private void rbtAll_CheckedChanged(object sender, EventArgs e)
        {
            if (triger == 0)
            {
                rbtSel.PerformClick();
                triger = 1;
                foreach (String name in t_pool.getNames())
                {
                    if (!cblTrips.CheckedItems.Contains(name))
                    {
                        t_pool.getByName(name).setVisibility(0);
                    }
                }
            }
            else
            {
                triger = 0;
            }
        }

        /* turn on auto pilot mode
        */
        private void rbtOn_CheckedChanged(object sender, EventArgs e)
        {
            if (tig == 0)
            {
                rbtOff.PerformClick();
                tig = 1;
                v_sw = 0;
            }
            else
            {
                tig = 0;
            }
        }

        /* turn off auto pilot mode
        */
        private void rbtOff_CheckedChanged(object sender, EventArgs e)
        {
            if (tig == 0)
            {
                rbtOn.PerformClick();
                tig = 1;
                v_sw = 1;
            }
            else
            {
                tig = 0;
            }
        }

        private void selectTextDataRow(object sender, DataGridViewCellMouseEventArgs e)
        {
            if ( textPointSet == true )
            { 
                ge.getFeatures().removeChild(start);
                ge.getFeatures().removeChild(finish);
            }
            float scale = 2;
            textPointSet = true;
            //When you select a row in the DataTable it populates it's information in the Panel
            DataGridViewRow row = textDataGrid.SelectedRows[0];
            startTimeText.Text = row.Cells[7].Value.ToString();
            finishTimeText.Text = row.Cells[8].Value.ToString();
            startCoordinatesText.Text = row.Cells[12].Value.ToString() + ", " + row.Cells[13].Value.ToString();
            finishCoordinatesText.Text = row.Cells[14].Value.ToString() + ". " + row.Cells[15].Value.ToString();
            distanceText.Text = row.Cells[10].Value.ToString() + " km";
            timeText.Text = row.Cells[9].Value.ToString() + " hrs";
            speedText.Text = Math.Round(Convert.ToDecimal(row.Cells[11].Value), 2).ToString() + " kmph";
            panel6.Visible = true;

            IKmlIcon startIcon = ge.createIcon("");
            startIcon.setHref("http://maps.google.com/mapfiles/kml/paddle/S.png");
            IKmlStyle startPointStyle = ge.createStyle("");
            startPointStyle.getIconStyle().setIcon(startIcon);
            startPointStyle.getIconStyle().setScale(scale);

            IKmlIcon finishIcon = ge.createIcon("");
            finishIcon.setHref("http://maps.google.com/mapfiles/kml/paddle/F.png");
            IKmlStyle finishPointStyle = ge.createStyle(""); 
            finishPointStyle.getIconStyle().setIcon(finishIcon);
            finishPointStyle.getIconStyle().setScale(scale);

            IKmlPlacemark textTripStartPlaceMark = ge.createPlacemark("start" + temp); 
            IKmlPlacemark textTripFinishPlaceMark = ge.createPlacemark("finish" + temp);
            ++temp;

            textTripStartPlaceMark.setStyleSelector(startPointStyle);
            textTripFinishPlaceMark.setStyleSelector(finishPointStyle);

            IKmlPoint textTripStartPoint = ge.createPoint("");
            IKmlPoint textTripFinishPoint = ge.createPoint("");

            textTripStartPoint.setLatitude(Convert.ToDouble(row.Cells[13].Value));
            textTripStartPoint.setLongitude(Convert.ToDouble(row.Cells[12].Value));

            textTripFinishPoint.setLatitude(Convert.ToDouble(row.Cells[15].Value));
            textTripFinishPoint.setLongitude(Convert.ToDouble(row.Cells[14].Value));

            textTripStartPlaceMark.setGeometry(textTripStartPoint);
            textTripFinishPlaceMark.setGeometry(textTripFinishPoint);

            ge.getFeatures().appendChild(textTripStartPlaceMark);
            ge.getFeatures().appendChild(textTripFinishPlaceMark);

            start = textTripStartPlaceMark;
            finish = textTripFinishPlaceMark;

            if (textPointHide)
            {
                start.setVisibility(0);
                finish.setVisibility(0);
            }
            
        }

        private void selectKMLDataRow(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (KMLPointSet == true)
            {
                ge.getFeatures().removeChild(KMLStart);
                ge.getFeatures().removeChild(KMLFinish);
            }
            float scale = 2;
            KMLPointSet = true;
            //When you select a row in the DataTable it populates it's information in the Panel
            DataGridViewRow row = KMLTripView.SelectedRows[0];
            startTimeText.Text = row.Cells[7].Value.ToString();
            finishTimeText.Text = row.Cells[8].Value.ToString();
            startCoordinatesText.Text = row.Cells[12].Value.ToString() + ", " + row.Cells[13].Value.ToString();
            finishCoordinatesText.Text = row.Cells[14].Value.ToString() + ". " + row.Cells[15].Value.ToString();
            distanceText.Text = row.Cells[10].Value.ToString() + " km";
            timeText.Text = row.Cells[9].Value.ToString() + " hrs";
            speedText.Text = Math.Round(Convert.ToDecimal(row.Cells[11].Value), 2).ToString() + " kmph";
            panel6.Visible = true;

            IKmlIcon KMLstartIcon = ge.createIcon("");
            KMLstartIcon.setHref("http://www.vishwaas.org.au/icons/KMLStart.png");
            IKmlStyle KMLstartPointStyle = ge.createStyle("");
            KMLstartPointStyle.getIconStyle().setIcon(KMLstartIcon);
            KMLstartPointStyle.getIconStyle().setScale(scale);

            IKmlIcon KMLfinishIcon = ge.createIcon("");
            KMLfinishIcon.setHref("http://www.vishwaas.org.au/icons/KMLFinish.png");
            IKmlStyle KMLfinishPointStyle = ge.createStyle("");
            KMLfinishPointStyle.getIconStyle().setIcon(KMLfinishIcon);
            KMLfinishPointStyle.getIconStyle().setScale(scale);

            IKmlPlacemark KMLTripStartPlaceMark = ge.createPlacemark("KMLstart" + temp);
            IKmlPlacemark KMLTripFinishPlaceMark = ge.createPlacemark("KMLfinish" + temp);
            ++temp;

            KMLTripStartPlaceMark.setStyleSelector(KMLstartPointStyle);
            KMLTripFinishPlaceMark.setStyleSelector(KMLfinishPointStyle);

            IKmlPoint KMLTripStartPoint = ge.createPoint("");
            IKmlPoint KMLTripFinishPoint = ge.createPoint("");

            KMLTripStartPoint.setLatitude(Convert.ToDouble(row.Cells[13].Value));
            KMLTripStartPoint.setLongitude(Convert.ToDouble(row.Cells[12].Value));

            KMLTripFinishPoint.setLatitude(Convert.ToDouble(row.Cells[15].Value));
            KMLTripFinishPoint.setLongitude(Convert.ToDouble(row.Cells[14].Value));

            KMLTripStartPlaceMark.setGeometry(KMLTripStartPoint);
            KMLTripFinishPlaceMark.setGeometry(KMLTripFinishPoint);

            ge.getFeatures().appendChild(KMLTripStartPlaceMark);
            ge.getFeatures().appendChild(KMLTripFinishPlaceMark);

            KMLStart = KMLTripStartPlaceMark;
            KMLFinish = KMLTripFinishPlaceMark;

            if (KMLPointhide)
            {
                KMLStart.setVisibility(0);
                KMLFinish.setVisibility(0);
            }

        }
        private void btMatch_Click(object sender, EventArgs e)
        {
     //       MessageBox.Show(t_pool.getSize().ToString());
            t_pool.de_highlight();
            ArrayList matches = new ArrayList();
            foreach (String tp in t_pool.getNames())
            {
      //          MessageBox.Show("run");
                for (int i = 0; i < txtEditor.getViewer().Rows.Count; i++ )
                {
                    if (txtEditor.getViewer().Rows[i]["KMLTrip"].ToString() == Module.getIndex(tp).ToString())
                    {
                        IKmlFolder trip = t_pool.getByName(tp);
                        if (Convert.ToDateTime(t_pool.getStart(trip).getName()) > Convert.ToDateTime(txtEditor.getViewer().Rows[i]["Start"])
                            ||  (Module.getCoordinates(t_pool.getStart(trip))["lon"] != txtEditor.getViewer().Rows[i]["sLongitude"].ToString())
                            || (Module.getCoordinates(t_pool.getStart(trip))["lat"] != txtEditor.getViewer().Rows[i]["sLatitude"].ToString())
                            )
                        {
               //             MessageBox.Show(tp + "  start    " + t_pool.getStart(trip).getName() + "   >   " + txtEditor.getViewer().Rows[i]["Start"]);
                            String tt =(trip.getFeatures().getChildNodes().getLength().ToString());
                            t_pool.addToStart(tp, mk_point(double.Parse(txtEditor.getViewer().Rows[i]["sLongitude"].ToString()),double.Parse(txtEditor.getViewer().Rows[i]["sLatitude"].ToString()), txtEditor.getViewer().Rows[i]["Start"].ToString(), ""));
     //                       MessageBox.Show(tt + "  start     " + trip.getFeatures().getChildNodes().getLength().ToString());
                            t_pool.resetTripData(tp);
                        }
                        else if (Convert.ToDateTime(t_pool.getStart(trip).getName()) < Convert.ToDateTime(txtEditor.getViewer().Rows[i]["Start"]))
                        {
                   //         MessageBox.Show(tp + "  start    " + t_pool.getStart(trip).getName() + "   <   " + txtEditor.getViewer().Rows[i]["Start"]);
                            t_pool.trimToStart(tp, txtEditor.getViewer().Rows[i]["Start"].ToString());
                        }

                        if (Convert.ToDateTime(t_pool.getFinish(trip).getName()) > Convert.ToDateTime(txtEditor.getViewer().Rows[i]["Finish"])
                            || (Module.getCoordinates(t_pool.getFinish(trip))["lon"] != txtEditor.getViewer().Rows[i]["fLongitude"].ToString())
                            || (Module.getCoordinates(t_pool.getFinish(trip))["lat"] != txtEditor.getViewer().Rows[i]["fLatitude"].ToString())
                            )
                        {
                    //        MessageBox.Show(tp + "  finish    " + t_pool.getFinish(trip).getName() + "   >   " + txtEditor.getViewer().Rows[i]["Finish"]);
                            t_pool.trimToEnd(tp, txtEditor.getViewer().Rows[i]["Finish"].ToString());
                            t_pool.resetTripData(tp);
                        }
                        else if (Convert.ToDateTime(t_pool.getFinish(trip).getName()) < Convert.ToDateTime(txtEditor.getViewer().Rows[i]["Finish"]))
                        {
                   //         MessageBox.Show(tp + "  finish    " + t_pool.getFinish(trip).getName() + "   <   " + txtEditor.getViewer().Rows[i]["Finish"]);
                            t_pool.addToEnd(tp, mk_point(double.Parse(txtEditor.getViewer().Rows[i]["fLongitude"].ToString()), double.Parse(txtEditor.getViewer().Rows[i]["fLatitude"].ToString()), txtEditor.getViewer().Rows[i]["Finish"].ToString(), ""));
                        }
                        matches.Add(i+1);
                        break;
                    }
                }
            }
            txtEditor.completeMissingData(t_pool);
            foreach (String tp in t_pool.getNames())
            {
                if (!matches.Contains(Module.getIndex(tp)))
                {
                    //We'll retrieve the trip information
                    String[] KMLTripDetails = t_pool.getTripDetailsForTrip(Module.getIndex("Trip"+(tp)).ToString());
                    txtEditor.addToDataTableForDay(KMLTripDetails);
                }

            }
            t_pool.resetTripCount();
            tripConflictText.Visible = false;
        }

        private void textDataGrid_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            match_check();
        }

        // Back button for viewing trip, points, and etc
        private void button1_Click(object sender, EventArgs e)
        {
            /*if (cblTrips.Items.Count != 0)
            {
                if (p_pool.contains((String)cblTrips.Items[0]))
                {
                    p_pool.dehighlight();
                    if (v_sw == 1)
                    {
                        ge.getView().setAbstractView(view);
                    }
                    IKmlPlacemark pt = p_pool.getByName((String)cblTrips.Items[0]);
                    IKmlFolder trip = (IKmlFolder)pt.getParentNode();
                    IKmlObjectList points = trip.getFeatures().getChildNodes();
                    for (int i = 0; i != points.getLength(); i++)
                    {
                        IKmlPlacemark point = (IKmlPlacemark)points.item(i);
                        if (record.valid(point.getName()))
                        {
                            point.setVisibility(1);
                        }
                    }

                    cblTrips.Items.Clear();
                    foreach (String name in t_pool.getNames())
                    {
                        if (record.valid(name))
                        {
                            cblTrips.Items.Add(name);
                        }

                    }


                    // checkedListBox1.Items.AddRange(t_pool.getNames().ToArray());
                }
                else if (t_pool.contains((String)cblTrips.Items[0]))
                {
                    t_pool.de_highlight();
                    cblTrips.Items.Clear();
                    foreach (String day in d_pool.Keys)
                    {
                        cblTrips.Items.Add(day);
                    }
                }
            }*/
        }

        // Expand button to view, trip, points, and etc
        private void button2_Click_1(object sender, EventArgs e)
        {
           /* if (cblTrips.Items.Count != 0)
            {
                ArrayList opts = new ArrayList();
                foreach (String chkd in cblTrips.CheckedItems)
                {
                    if (d_pool.ContainsKey(chkd))
                    {
                        IKmlDocument day = (IKmlDocument)d_pool[chkd];
                        IKmlObjectList trips = day.getFeatures().getChildNodes();
                        for (int i = 0; i != trips.getLength(); i++)
                        {
                            IKmlFolder trip = (IKmlFolder)trips.item(i);
                            if (record.valid(trip.getName()))
                            {
                                t_pool.add(trip.getName(), trip);
                                opts.Add(trip.getName());
                            }
                        }
                    }
                    else if (t_pool.contains(chkd))
                    {
                        if (cblTrips.CheckedItems.Count > 1)
                        {
                            MessageBox.Show("Each trip should be edited individidually.", "Caution");
                            return;
                        }
                        view = ge.getView().copyAsCamera(1);
                        t_pool.de_highlight();
                        IKmlFolder trip = (IKmlFolder)t_pool.getByName(chkd);
                        IKmlObjectList points = trip.getFeatures().getChildNodes();
                        for (int i = 0; i != points.getLength(); i++)
                        {
                            IKmlPlacemark point = (IKmlPlacemark)points.item(i);
                            if (record.valid(point.getName()))
                            {
                                p_pool.add(point.getName(), point);
                                opts.Add(point.getName());
                                webBrowser1.Document.InvokeScript("addEvent", new object[] { point });
                            }
                        }
                    }
                }
                if (opts.Count != 0)
                {
                    cblTrips.Items.Clear();
                    cblTrips.Items.AddRange(opts.ToArray());
                }
            }*/
        }

        private void btTripExpand_Click(object sender, EventArgs e)
        {
            if (cblTrips.CheckedItems.Count != 1)
            {
                MessageBox.Show("You can only expend one trip at a time.", "Caution");
                return;
            }
            else
            {
                t_pool.de_highlight();
                view = ge.getView().copyAsCamera(1);
                tpi = cblTrips.CheckedIndices[0];
                IKmlFolder trip = t_pool.getByName(cblTrips.CheckedItems[0].ToString());
                IKmlObjectList points = trip.getFeatures().getChildNodes();
                cblTrips.Items.Clear();
                p_pool = new PointPool(trip);
                cblTrips.Items.AddRange(p_pool.getNames().ToArray());
                tp_mode = 0;
            }
        }

        private void btTripContract_Click(object sender, EventArgs e)
        {
            cblTrips.Items.Clear();
            p_pool.dehighlight();
            cblTrips.Items.AddRange(t_pool.getNames().ToArray());
            ge.getView().setAbstractView(view);
            cblTrips.SetItemChecked(tpi, true);
            tp_mode = 1;
        }

        private void btHideTextPoints_Click(object sender, EventArgs e)
        {
            if (textPointSet)
            {
                if (!textPointHide)
                {
                    start.setVisibility(0);
                    finish.setVisibility(0);
                    btHideTextPoints.Text = "Show Points";
                    textPointHide = true;
                }
                else
                {
                    start.setVisibility(1);
                    finish.setVisibility(1);
                    btHideTextPoints.Text = "Hide Points";
                    textPointHide = false;
                }
            }
        }

        private void btHideKMLPoints_Click(object sender, EventArgs e)
        {
            if (KMLPointSet)
            {
                if (!KMLPointhide)
                {
                    KMLStart.setVisibility(0);
                    KMLFinish.setVisibility(0);
                    btHideKMLPoints.Text = "Show Points";
                    KMLPointhide = true;
                }
                else
                {
                    KMLStart.setVisibility(1);
                    KMLFinish.setVisibility(1);
                    btHideKMLPoints.Text = "Hide Points";
                    KMLPointhide = false;
                }
            }
        }

        private void btResetTilt_Click(object sender, EventArgs e)
        {
            //This will reset the tilt of the camera when the user has zoomed in. This was a special client request after client deployment
            IKmlCamera currentView = ge.getView().copyAsCamera(0);
            IKmlCamera resetView = ge.createCamera("");
            resetView.set(currentView.getLatitude(), currentView.getLongitude(), currentView.getAltitude(), ge.ALTITUDE_RELATIVE_TO_GROUND, currentView.getHeading(), 0, currentView.getRoll());
            ge.getView().setAbstractView(resetView);
        }

        private void btRuler_Click(object sender, EventArgs e)
        {
            if (!rulerMode)  //If the program isn't in ruler mode
            {
                //Okay so this function will allow the user to create points on the map that will be used to calculate distance
                //between a path.
                //So the first we'll have to do is call the JsCrt function which readies the double click event handler.
                webBrowser1.Document.InvokeScript("JSrulerPoint", new object[] { });
                //So now the map will be ready for a double click
                rulerMode = true;
                this.btRuler.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.hover));  // This will leave the colour on, giving the user an indication that rulerMode is still on.
                IKmlPlacemark newLine = ge.createPlacemark("line"+lineNumber);
                IKmlLineString newLinePoints = ge.createLineString("linePoints" + lineNumber);
                IKmlFolder rulerConstruct = ge.createFolder("construct"+lineNumber);
                ++lineNumber;
                line = newLine;
                linePoints = newLinePoints;
                ruler = rulerConstruct;
                ruler.getFeatures().appendChild(line);
                ge.getFeatures().appendChild(ruler);
                rulerPanel.Visible = true;

            }
            else
            {
                //Now the user has completed measuring the path, so now we should delete the points that were created and call of the double click event handler
                webBrowser1.Document.InvokeScript("JSrmCT", new object[] {} );
                this.btRuler.BackgroundImage = ((System.Drawing.Image)(Properties.Resources.normal)); //This will put the colour back to normal, giving the user an indication that rulerMode is off.
                rulerMode = false;
                ge.getFeatures().removeChild(ruler);
                rulerDistance = 0;
                rulerDistanceText.Text = "";
                pointsMeasured = 0;
                rulerPanel.Visible = false;
            } 
        }
        

        // I'd also like the starting and finishing points to be shown on the map, so let's do that too.
        // I'd also like the starting and finishing points to be shown on the map, so let's do that too.
        /* clearing out a marker */

        //private void button1_Click_1(object sender, EventArgs e)
        //{
        //    if (core.get_sel_pt() == null) //makes sure a trip is selected 
        //    {
        //        MessageBox.Show("Please select a trip to create a point for", "Caution");
        //    }
        //    else if (cblTrips.CheckedItems.Count > 1) //makes sure only one trip is selected 
        //    {
        //        MessageBox.Show("Please select only one trip", "Caution");
        //    }
        //    else
        //    {
        //        core.dehi 
               
        //    } 

        //}
        
        
   }
}
