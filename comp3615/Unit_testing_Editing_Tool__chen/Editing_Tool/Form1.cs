using System;
using System.Collections;
using System.ComponentModel;
using System.Collections.Generic;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Security.Permissions;
using System.IO;
using System.Xml;
using NUnit.Framework;
using System.Threading;
using GEPlugin;


namespace Editing_Tool
{
    [ComVisibleAttribute(true)]
    [PermissionSet(SecurityAction.Demand, Name = "FullTrust")]
    public partial class Form1 : Form
    {
        private const string PLUGIN_URL =
                    @"http://www.ug.it.usyd.edu.au/~cson3077/comp3615/index.html";
        private IGEPlugin ge = null;

        private Hashtable d_pool = new Hashtable();
        private TripPool t_pool = new TripPool();
        private int l_selk = -1;
        private Rec record = new Rec();
        private IKmlCamera view;
        private String kmlfpath, kmlex, kmln, txtfpath, txtex, txtn;
        private int v_sw = 1;

        private IKmlPlacemark sel_point= null;
        private String sel_style = "";

        private String header = "";
        private String body = "";
        private String footer = "";

        private System.IO.StreamReader objReader;
        private String d_name = ""; 

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            panel1.Enabled = false;
            webBrowser1.Navigate(PLUGIN_URL);
            webBrowser1.ObjectForScripting = this;
        }

        public void JSInitSuccessCallback_(object pluginInstance)
        {
            ge = (IGEPlugin)pluginInstance;
            ge.getNavigationControl().setVisibility(ge.VISIBILITY_SHOW);
            ge.getLayerRoot().enableLayerById(ge.LAYER_BORDERS, 1);
            //            ge.getLayerRoot().enableLayerById(ge.LAYER_ROADS, 1);
            panel1.Enabled = true;
        }

        public void JSInitFailureCallback_(string error)
        {
            MessageBox.Show("Error: " + error, "Plugin Load Error", MessageBoxButtons.OK,
                MessageBoxIcon.Exclamation);
        }

        public void JScallName(IKmlPlacemark point)
        {
 //           MessageBox.Show("You are clicking on " +point.getName(), "Caution");
            highlight(point);
        }

        public void highlight(IKmlPlacemark point)
        {
            de_highlight();
            sel_style = point.getStyleUrl();
            point.setStyleUrl("");
            sel_point = point;
        }

        public void de_highlight()
        {
            if (sel_point != null)
            {
                sel_point.setStyleUrl(sel_style);
            }
        }
/*
        String ns = "<Style id=\"normalStart\"><IconStyle><Icon><href>http://maps.google.com/mapfiles/kml/paddle/grn-stars.png</href></Icon><scale>0.7</scale></IconStyle><LabelStyle><color>00000000</color></LabelStyle></Style>" +
                    "<Style id=\"highlightStart\"><IconStyle><Icon><href>http://maps.google.com/mapfiles/kml/paddle/grn-stars.png</href></Icon><scale>1.2</scale></IconStyle><LabelStyle><color>ffffffff</color></LabelStyle></Style>" +
                    "<StyleMap id=\"Start\"><Pair><key>normal</key><styleUrl>#normalStart</styleUrl></Pair><Pair><key>highlight</key><styleUrl>#highlightStart</styleUrl></Pair></StyleMap>";
*/

        private void button1_Click(object sender, EventArgs e)
        {
            if (ge != null)
            {
                if (kmlex == ".kml" && txtex == ".txt")
                {
                    try
                    {
                        ge.getFeatures().appendChild(ge.parseKml(correction(System.IO.File.ReadAllText(kmlfpath))));

                        data textDatabase = new data();
                        Parser textParser = new Parser();
                        textParser.parseFileToDataSet(txtfpath, textDatabase);

                        D_parser();
                        foreach (String trip in t_pool.getNames())
                        {
                            checkedListBox1.Items.Add(trip);
                        }

                        ge.getView().setAbstractView(allocate());
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

        private String correction(String input)
        {
            return System.Text.RegularExpressions.Regex.Replace(input, @"shapes/travelpoint.png", @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png");
        }

        private IKmlCamera allocate()
        {
            double lat = 0, lon = 0;
            IKmlObjectList days = ge.getFeatures().getChildNodes();
            IKmlDocument day = (IKmlDocument)days.item(0);
            IKmlObjectList trips = day.getFeatures().getChildNodes();
            for (int i = 0; i != trips.getLength(); i++)
            {
                IKmlFolder trip = (IKmlFolder)trips.item(i);
                IKmlObjectList points = trip.getFeatures().getChildNodes();
                IKmlPlacemark point = (IKmlPlacemark)points.item(0);

                lon += (double)getCoordinates(point)["lon"];
                lat += (double)getCoordinates(point)["lat"];
            }
            lon = lon / trips.getLength();
            lat = lat / trips.getLength();
            IKmlCamera vw = ge.createCamera("");
            vw.set(lon, lat, 18000.0, ge.ALTITUDE_RELATIVE_TO_GROUND, 0, 0, 0);
            return vw;
        }

        public Hashtable getCoordinates(IKmlPlacemark point)
        {
            Hashtable cods = new Hashtable();
            String xml = point.getKml();
            String temp = System.Text.RegularExpressions.Regex.Split(xml, "<coordinates>")[1];
            String coords = System.Text.RegularExpressions.Regex.Split(temp, "</coordinates>")[0];
            Array value = System.Text.RegularExpressions.Regex.Split(coords, ",");
            cods["lon"] = double.Parse((String)value.GetValue(1));
            cods["lat"] = double.Parse((String)value.GetValue(0));
            return cods;
        }

        public double getDistance(IKmlPlacemark point)
        {
            String xml = point.getDescription();
            String temp =System.Text.RegularExpressions.Regex.Split(xml, "Distance</td><td>")[1];
            return double.Parse((String) temp.Split('<')[0]);
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

            String temp= "";
            IKmlObjectList trips = day.getFeatures().getChildNodes();
            for (int i = 0; i != trips.getLength(); i++)
            {
                IKmlFolder trip = (IKmlFolder)trips.item(i);
                String[] att = line;

                double dis = T_parser(trip);
                att[6] = duration(att[4],att[5]);
                att[7] = dis.ToString();

                att[8] = Math.Round((double.Parse(att[7]) / durationConverter(att[6])),3).ToString();

                t_pool.add(trip, att);

                temp = objReader.ReadLine();
                List<String> input = temp.Split('\t').ToList();
                input.RemoveAt(0);
                input.RemoveAt(0);
                line = input.ToArray(); 
            }
            footer += temp+'\n';
        }

        public double T_parser(IKmlFolder trip)
        {
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            double dis = 0;
            for (int ii = 0; ii != points.getLength(); ii++)
            {
                IKmlPlacemark point = (IKmlPlacemark)points.item(ii);
                webBrowser1.Document.InvokeScript("JSmk", new object[] { point });
                if (ii != 0)
                {
                    dis+=getDistance(point);
                }
            }
            return Math.Round(dis,3);
        }

        public Hashtable getSFpt(String input)
        {

            return null;
        }

        private IKmlCamera zoom(String trip)
        {
                IKmlCamera vw = ge.createCamera("");
                Hashtable coords = t_pool.getFocus(trip);
                vw.set((float)coords["lon"], (float)coords["lat"], 6000.0, ge.ALTITUDE_RELATIVE_TO_GROUND, 0, 0, 0);
                return vw;
        }


        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (checkedListBox1.SelectedItem != null)
            {
                String selkd = checkedListBox1.SelectedItem.ToString();
                if (checkedListBox1.SelectedIndex != l_selk)
                {
                    if (v_sw == 1)
                    {
                        t_pool.highlight(selkd);
                        ge.getView().setAbstractView(zoom(selkd));
                    }
                }
                else if (radioButton2.Checked)
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
                l_selk = checkedListBox1.SelectedIndex;
            }
        }



        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            if (triger == 0)
            {
                radioButton1.PerformClick();
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

        int triger = 0;

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (triger == 0)
            {
                radioButton2.PerformClick();
                triger = 1;
                foreach (String name in t_pool.getNames())
                {
                    if (!checkedListBox1.CheckedItems.Contains(name))
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

        private void checkedListBox1_DoubleClick(object sender, EventArgs e)
        {
            if (radioButton2.Checked)
            {
                String selkd = checkedListBox1.SelectedItem.ToString();
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

        /*
         *  delete function
         */
        private void button4_Click(object sender, EventArgs e)
        {
            if (checkedListBox1.CheckedItems.Count == 1)
            {
                if (delete((String)checkedListBox1.CheckedItems[0]))
                {
                    checkedListBox1.Items.Clear();
                    checkedListBox1.Items.AddRange(t_pool.getNames().ToArray());
                }
                else
                {
                    MessageBox.Show("Failed to delete the trip","Error");
                }
            }
            else
            {
                MessageBox.Show("Select ONE trip to delete at a time.", "Caution");
            }
        }


        private Boolean delete(String name)
        {
            try
            {
                ArrayList trip = new ArrayList();
                IKmlFolder _trip = t_pool.getByName(name);

                String[] att = t_pool.getAttByName(name);
                _trip.setVisibility(0);
                trip.Add(name);
                trip.Add(_trip);
                trip.Add(att);

                t_pool.remove(name);
                record.del_trip(trip);
                return true;
            }
            catch
            {
                return false;
            }
        }
        

        private String duration(String st, String fn)
        {
            return Convert.ToDateTime(fn).Subtract(Convert.ToDateTime(st)).ToString();
        }


        /*
         * distance calculation using big-circle formula
         * 
         */
        private double calDistance(IKmlFolder trip)
        {
            double distance = 0;
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            IKmlPlacemark prev = null;
            for (int i = 0; i != (points.getLength()); i++)
            {
                IKmlPlacemark curr = (IKmlPlacemark)points.item(i);
                if (prev != null)
                {
                    double d = DistanceAlgorithm.DistanceBetweenPlaces((double)getCoordinates(curr)["lat"], (double)getCoordinates(curr)["lon"]
                        , (double)getCoordinates(prev)["lat"], (double)getCoordinates(prev)["lon"]);
                    distance += d;
                }
                prev = curr;
            }
            return Math.Round(distance*1000, 3);
        }

        /*
         * Split function
         */
        private void button5_Click(object sender, EventArgs e)
        {
            if (sel_point == null) { MessageBox.Show("Select a split point first.", "Caution"); return; }

            t_pool.de_highlight();
            de_highlight();

            if (split(sel_point))
            {
                sel_point = null;
                checkedListBox1.Items.Clear();
                checkedListBox1.Items.AddRange(t_pool.getNames().ToArray());
            }
            else
            {
                MessageBox.Show("Failed to split a trip a point.","Error");
            }
        }


        private Boolean split(IKmlPlacemark sp_point)
        {
            try{
                Hashtable cords = getCoordinates(sp_point);

                IKmlFolder _trip = (IKmlFolder)sp_point.getParentNode();
                _trip.setVisibility(0);

                String t_name = t_pool.getParent(sp_point.getName());
                String[] t_att = t_pool.getAttByName(t_name);
                ArrayList trip = new ArrayList();
                trip.Add(t_name);
                trip.Add(_trip);
                trip.Add(t_att);
                record.spl_trip(trip);

                int index = int.Parse((t_name.Split('_')[1]));
                IKmlFolder[] sub = split(index, _trip, sp_point, sp_point.getStyleUrl());

                IKmlPlacemark fn = t_pool.getFinish(sub[0]);
                Hashtable _cords = getCoordinates(fn);

                String[] att_temp1 = (String[])t_att.Clone();
                String[] att_temp2 = (String[])t_att.Clone();

                att_temp1[5] = fn.getName();
                att_temp2[4] = sp_point.getName();

                att_temp1[6] = duration(att_temp1[4], att_temp1[5]);
                att_temp2[6] = duration(att_temp2[4], att_temp2[5]);

                att_temp1[11] = _cords["lon"].ToString();
                att_temp1[12] = _cords["lat"].ToString();

                att_temp2[9] = cords["lon"].ToString();
                att_temp2[10] = cords["lat"].ToString();

                IKmlObjectList days = ge.getFeatures().getChildNodes();
                IKmlDocument day = (IKmlDocument)days.item(0);

                day.getFeatures().appendChild(sub[0]);
                day.getFeatures().appendChild(sub[1]);

                if (sub[0].getFeatures().getChildNodes().getLength() <= sub[1].getFeatures().getChildNodes().getLength())
                {
                    double distance = calDistance(sub[0]);
                    att_temp1[7] = distance.ToString();
                    att_temp2[7] = (double.Parse(t_att[7]) - distance).ToString();
                }
                else
                {
                    double distance = calDistance(sub[1]);
                    att_temp2[7] = distance.ToString();
                    att_temp1[7] = (double.Parse(t_att[7]) - distance).ToString();
                }

                /*
                 * The duration of a trip from might be less than 0 when the program interpreter inconsistent kml and txt file
                 * 
                 * chen
                 */
                try
                {
                    att_temp1[8] = Math.Round((double.Parse(att_temp1[7]) / durationConverter(att_temp1[6])), 3).ToString();
                    att_temp2[8] = Math.Round((double.Parse(att_temp2[7]) / durationConverter(att_temp2[6])), 3).ToString();
                }
                catch
                {
                    MessageBox.Show("kml and txt file doesn't match");
                    att_temp2[8] = "-0";
                    att_temp1[8] = "-0";
                }
                t_pool.insert(index, sub[0], att_temp1, sub[1], att_temp2);

                return true;
                }
            catch
            {
                return false;
            }

        }


        /*
         * durationConvert convers the time from a string into a double
         * 
         */
        private double durationConverter(String input)
        {
            return Convert.ToDateTime(input).Subtract(Convert.ToDateTime("0:0:0")).TotalSeconds;
        }

        private IKmlFolder[] split(int index, IKmlFolder raw, IKmlPlacemark _point, String style)
        {
            IKmlFolder[] output = new IKmlFolder[2];

            IKmlFolder temp1 = ge.createFolder("");
            IKmlFolder temp2 = ge.createFolder("");
            temp1.setName("Trip_" + (index).ToString());
            temp2.setName("Trip_" + (index + 1).ToString());

            int sw = 0;
            IKmlObjectList points = raw.getFeatures().getChildNodes();

            for (int i = 0; i != points.getLength(); i++)
            {
                IKmlPlacemark point = (IKmlPlacemark)points.item(i);
                if (point.getName() == _point.getName())
                {
                    sw = 1;
                }
                if (sw == 0)
                {
                    temp1.getFeatures().appendChild(point);
                    
                }
                else
                {
                    point.setStyleUrl(style);
                    temp2.getFeatures().appendChild(point);
                }
            }
            output[0] = temp1;
            output[1] = temp2;
            return output;
        }


        /*
         * Join function
         */
        private void button7_Click(object sender, EventArgs e)
        {
            if (checkedListBox1.CheckedItems.Count == 2 && Math.Abs(checkedListBox1.CheckedIndices[1] - checkedListBox1.CheckedIndices[0]) == 1)
            {
                t_pool.de_highlight();
                de_highlight();

                if (join((String)checkedListBox1.CheckedItems[0], (String)checkedListBox1.CheckedItems[1]))
                {
                    checkedListBox1.Items.Clear();
                    checkedListBox1.Items.AddRange(t_pool.getNames().ToArray());
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

        private Boolean join(String t_name1, String t_name2)
        {
            try
            {
                IKmlFolder temp = ge.createFolder("");
                String[] trip1 = t_pool.getAttByName(t_name1);
                String[] trip2 = t_pool.getAttByName(t_name2);

                IKmlPlacemark point = t_pool.getStart(t_pool.getByName(t_name2));

                String[] trip = (String[])trip1.Clone();
                trip[5] = trip2[5];
                trip[6] = duration(trip[4], trip[5]);
                trip[11] = trip2[11];
                trip[12] = trip2[12];

                Hashtable cord1 = getCoordinates(t_pool.getFinish(t_pool.getByName(t_name1)));
                Hashtable cord2 = getCoordinates(t_pool.getStart(t_pool.getByName(t_name2)));

                trip[7] = (double.Parse(trip1[7]) + double.Parse(trip2[7]) + DistanceAlgorithm.DistanceBetweenPlaces((double)cord1["lat"], (double)cord1["lon"]
                            , (double)cord2["lat"], (double)cord2["lon"])).ToString();

                trip[8] = Math.Round((double.Parse(trip[7]) / durationConverter(trip[6])), 3).ToString();

                String style = t_pool.insert(t_name1, temp, trip);
                IKmlObjectList days = ge.getFeatures().getChildNodes();
                IKmlDocument day = (IKmlDocument)days.item(0);
                day.getFeatures().appendChild(temp);

                ArrayList data = new ArrayList();
                data.Add(t_name1);
                data.Add(point);
                data.Add(trip1);
                data.Add(trip2);
                data.Add(style);
                record.joi_trip(data);

                return true;
            }
            catch
            {
                return false;
            }
        }

        /*
         * Undo funcion
         */
        private void button8_Click(object sender, EventArgs e)
        {
            Hashtable mem = record.undo();
            if (mem != null)
            {
                if (mem["opt"] == "del")
                {
                    ArrayList rev = (ArrayList)mem["data"];

                    IKmlFolder _trip = (IKmlFolder)rev[1];
                    _trip.setVisibility(1);
                    t_pool.add((String)rev[0],_trip, (String[])rev[2]);
                    
                    checkedListBox1.Items.Clear();
                    checkedListBox1.Items.AddRange(t_pool.getNames().ToArray());
                }
                else if (mem["opt"] == "spl")
                {
                    ArrayList rev = (ArrayList)mem["data"];
                    IKmlFolder trip = (IKmlFolder)rev[1];

                    t_pool.insert((String)rev[0], trip, (String[]) rev[2]);
                    trip.setVisibility(1);
                    IKmlObjectList days = ge.getFeatures().getChildNodes();
                    IKmlDocument day = (IKmlDocument)days.item(0);
                    day.getFeatures().appendChild(trip);

                    checkedListBox1.Items.Clear();
                    checkedListBox1.Items.AddRange(t_pool.getNames().ToArray());
                }
                else if (mem["opt"] == "joi")
                {
                    t_pool.de_highlight();
                    de_highlight();

                    ArrayList rev = (ArrayList)mem["data"];
                    IKmlFolder temp = ge.createFolder("");

                    String name = (String)rev[0];
                    IKmlFolder[] sub = split(int.Parse((name.Split('_')[1])), t_pool.getByName(name), (IKmlPlacemark)rev[1], (String)rev[4]);

                    IKmlObjectList days = ge.getFeatures().getChildNodes();
                    IKmlDocument day = (IKmlDocument)days.item(0);

                    day.getFeatures().appendChild(sub[0]);
                    day.getFeatures().appendChild(sub[1]);

                    t_pool.insert(int.Parse((name.Split('_')[1])),sub[0], (String[]) rev[2], sub[1], (String[]) rev[3]);

                    checkedListBox1.Items.Clear();
                    checkedListBox1.Items.AddRange(t_pool.getNames().ToArray());
                }
                else if (mem["opt"] == "ins")
                {
                    String rev = (String)mem["data"];
                    IKmlFolder trip = t_pool.getByName(rev);
                    trip.setVisibility(0);
                    t_pool.remove(rev);

                    checkedListBox1.Items.Clear();
                    checkedListBox1.Items.AddRange(t_pool.getNames().ToArray());
                }
            }
        }

        /*
         * browse KML file
         */
        private void button10_Click(object sender, EventArgs e)
        {
            OpenFileDialog open_fd = new OpenFileDialog();
            open_fd.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyComputer);
            open_fd.ShowDialog();
            kmlfpath = open_fd.FileName;
            kmlex = Path.GetExtension(kmlfpath);
            kmln = Path.GetFileName(kmlfpath);
            textBox1.Text = kmlfpath;
        }

        int tig = 0;
        /*
         * auto pilot switch
         */
        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            if (tig == 0)
            {
                radioButton3.PerformClick();
                tig = 1;
                v_sw = 1;
            }
            else
            {
                tig = 0;
            }
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            if (tig == 0)
            {
                radioButton4.PerformClick();
                tig = 1;
                v_sw = 0;
            }
            else
            {
                tig = 0;
            }
        }

        /*
         * browse TXT file
         */
        private void button11_Click(object sender, EventArgs e)
        {
            OpenFileDialog open_fd = new OpenFileDialog();
            open_fd.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.MyComputer);
            open_fd.ShowDialog();
            txtfpath = open_fd.FileName;
            txtex = Path.GetExtension(txtfpath);
            txtn = Path.GetFileName(txtfpath);
            textBox2.Text = txtfpath;
        }


        /*
         * 
         * Commit
         * 
         */
        private void button9_Click(object sender, EventArgs e)
        {
            if (objReader != null)
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
            }
        }

        private void button12_Click(object sender, EventArgs e)
        {
            IKmlFolder temp = t_pool.getByName((String)checkedListBox1.CheckedItems[0]);
            MessageBox.Show(calDistance(temp).ToString());
        }

        private void button2_Click(object sender, EventArgs e)
        {
            IKmlFolder trip = t_pool.getByName((String)checkedListBox1.CheckedItems[0]);
            double sum = 0;
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            for (int i = 0; i != (points.getLength()); i++)
            {
                if (i != 0)
                {
                    sum += getDistance((IKmlPlacemark)points.item(i));
                }
            }
            MessageBox.Show(sum.ToString());

        }

        private void button3_Click(object sender, EventArgs e)
        {
            foreach (int trip in checkedListBox1.CheckedIndices)
            {
                checkedListBox1.SetItemCheckState(trip, 0);
            }
            if (sel_point != null)
            {
                de_highlight();
                sel_point = null;
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if (checkedListBox1.CheckedItems.Count == 2 && Math.Abs(checkedListBox1.CheckedIndices[1] - checkedListBox1.CheckedIndices[0]) == 1)
            {
                String tp1 = (String)checkedListBox1.CheckedItems[0];
                String tp2 = (String)checkedListBox1.CheckedItems[1];

                IKmlPlacemark tp1fn = t_pool.getFinish(t_pool.getByName(tp1));
                IKmlPlacemark tp2st = t_pool.getStart(t_pool.getByName(tp2));


                IKmlPlacemark _temp = ge.createPlacemark("");


                /*
                 * I also make the name of the placemaker different to the others so it won't be treat by my program 
                 * as other normal placemarker ( named from 0:0:0 to 24:0:0 ) which crash the program.
                 * 
                 * Chen
                 */
                _temp.setName("99:99:99");


                IKmlLineString temp = ge.createLineString("");

                _temp.setGeometry(temp);

                Hashtable cds1 = getCoordinates(tp1fn);
                Hashtable cds2 = getCoordinates(tp2st);

                temp.getCoordinates().pushLatLngAlt((double)cds1["lon"], (double)cds1["lat"], 0);
                temp.getCoordinates().pushLatLngAlt((double)cds2["lon"], (double)cds2["lat"], 0);

                IKmlFolder temp1 = ge.createFolder("");
                temp1.getFeatures().appendChild(_temp);

                /*
                 * To Ekin:
                 * 
                 * I have resolved the bug cause by the highligh() as it would look for the String[] which stores all the 
                 * info associate with the trip user select on the checklist, since in the previous program you didnt add
                 * new trip info into the _att array in TripPool which means after the first insert there are 7 trips in
                 * _core but only 6 in _att, when the program look for _core[6] is ok but _att[6] just cause it to crash.
                 * 
                 * I have changed the highligh() by removing the getAttsBy() function call( that function call is not 
                 * actually required for  highligh(), I used to leave the code there for testing and forgot to remove at 
                 * the end ), I also create a string array attributes where all the trip info should stored, it is now empty 
                 * and load directly into the _att, but to make the whole program work the empty column should be filled in
                 * with actual data.
                 * 
                 * Chen
                 */

                String[] attributes = new String[14];

                t_pool.add(tp2, temp1,attributes);
                ge.getFeatures().appendChild(temp1);

                record.ins_trip(tp2);

                checkedListBox1.Items.Clear();
                checkedListBox1.Items.AddRange(t_pool.getNames().ToArray());
            }
            else
            {
                MessageBox.Show("Must select two trips to perform insert trip in between");
            }
        }

        /*
         * EXTEND FUNCTION
         * The extend code which selects a new start for a trip, replacing start time, recalculating distance, duration
         * speed, start longitude and start latitude
         * 
         * 
         * TO BE WORKED ON AND NEED MORE CLARIFICATION!!!!
         */
        private void button2_Click_1(object sender, EventArgs e)
        {
            if (sel_point == null)
            {
                MessageBox.Show("Select a point to extend to", "Caution");
                return;
            }
            else
            {
                t_pool.de_highlight();
                de_highlight();

                Hashtable cords = getCoordinates(sel_point);

                ArrayList trip = new ArrayList();

                String t_name = t_pool.getParent(sel_point.getName());

                String[] att = t_pool.getAttByName(t_name);
                
                att[4] = sel_point.getName();
                att[6] = duration(att[4], att[5]);
                att[7] = calDistance(t_pool.getByName(t_name)).ToString();
                att[8] = Math.Round((double.Parse(att[7]) / durationConverter(att[6])), 3).ToString();
                att[9] = (String)cords["lon"];
                att[10] = (String)cords["lat"];
                highlight(sel_point);

            }
        }


        /* Unit Testing for All Functions */

        private void button13_Click(object sender, EventArgs e)
        {
            try
            {
                MessageBox.Show("Test for selecting a point");
                try
                {
                    IKmlPlacemark temp = t_pool.getStart(t_pool.getByName("Trip_1"));
                    JScallName(temp);
                    Assert.AreNotEqual(null, sel_point);
                    MessageBox.Show("Successfully selected a point");
                }
                catch
                {
                    MessageBox.Show("Failed to select a point", "ERROR");
                    return;
                }

                //-------------------------------------------------------------------------------------
                MessageBox.Show("Test for deselecting a point");
                try
                {
                    de_highlight();
                    Assert.AreEqual(sel_style, sel_point.getStyleUrl());
                    MessageBox.Show("Successfully deselected a point");
                }
                catch
                {
                    MessageBox.Show("Failed to deselect a point", "ERROR");
                    return;
                }

                //-------------------------------------------------------------------------------------
                MessageBox.Show("Test for Zoom to selected trip");
                try
                {
                    IKmlCamera test = zoom("Trip_1");
                    ge.getView().setAbstractView(test);
                    IKmlCamera temp = ge.getView().copyAsCamera(ge.ALTITUDE_CLAMP_TO_GROUND);
                    Assert.AreNotEqual(temp, test);
                    MessageBox.Show("Successfully Zoomed to selected trip");
                }
                catch
                {
                    MessageBox.Show("Failed to Zoom to selected trip", "ERROR");
                    return;
                }

                //-------------------------------------------------------------------------------------
                MessageBox.Show("Test for de-auto zoom");
                try
                {
                    KmlLookAtCoClass lookAt1 = ge.getView().copyAsLookAt(ge.ALTITUDE_CLAMP_TO_GROUND);
                    KmlLookAtCoClass lookAt2 = ge.getView().copyAsLookAt(ge.ALTITUDE_CLAMP_TO_GROUND);

                    Assert.AreEqual(lookAt1.getLatitude(), lookAt2.getLatitude());
                    Assert.AreEqual(lookAt1.getLongitude(), lookAt2.getLongitude());
                    MessageBox.Show("Successfully de-auto-zoomed to selected trip");
                }
                catch
                {
                    MessageBox.Show("Failed to de-auto-zoom to selected trip", "ERROR");
                    return;
                }

                //-------------------------------------------------------------------------------------
                MessageBox.Show("Test for split a trip at its first point");
                try
                {
                    String name = "Trip_6";
                    IKmlFolder temp = t_pool.getByName(name);

                    IKmlPlacemark sst = (IKmlPlacemark)temp.getFeatures().getChildNodes().item(0);
                    IKmlPlacemark st = (IKmlPlacemark)temp.getFeatures().getChildNodes().item(1);
             
                    int pt_size = temp.getFeatures().getChildNodes().getLength();
                    int init_size_t = t_pool.getSize();
                    int init_size_a = t_pool.getAttrs().Count;
                    String[] att = t_pool.getAttByName(name);
                    split(st);

                    int flag = 0;
                    try
                    {
                        int final_size_t = t_pool.getSize();
                        Assert.AreEqual(init_size_t, final_size_t - 1);
                        Assert.AreEqual(1, t_pool.getByName("Trip_6").getFeatures().getChildNodes().getLength());
                        Assert.AreEqual(pt_size-1, t_pool.getByName("Trip_7").getFeatures().getChildNodes().getLength());
                        MessageBox.Show("Passed the test for split a trip at its first point on GUI level");
                    }
                    catch
                    {
                        MessageBox.Show("Failed the test for split a trip at its first point on GUI level");
                        flag = 1;
                    }


                    try
                    {
                        int final_size_a = t_pool.getAttrs().Count;
                        Assert.AreEqual(init_size_a, final_size_a - 1);   
                        String[] att1 = t_pool.getAttByName("Trip_6");
                        String[] att2 = t_pool.getAttByName("Trip_7");

                        try
                        {  
                            Assert.AreEqual(att[4],att1[4]);
                            Assert.AreEqual(att[5], att2[5]);

                            MessageBox.Show("Succeed to compute the correct start and finish time");
                        }
                        catch{
                            MessageBox.Show("Failed to compute the correct start and finish time");
                            flag = 1;
                        }

                        try
                        {
                            Assert.AreEqual(durationConverter(att[6]), durationConverter(att1[6])+durationConverter(att2[6])+durationConverter(duration(st.getName(),sst.getName())));
                            MessageBox.Show("Succeed to compute the correct trip duration");
                        }
                        catch
                        {
                            MessageBox.Show("Failed to compute the correct the trip duration");
                            flag = 1;
                        }

                        try
                        {
                            Hashtable cord0 = getCoordinates(sst);
                            Hashtable cord1 = getCoordinates(st);
                            Assert.AreEqual(durationConverter(att[9]), att1[9]);
                            Assert.AreEqual(durationConverter(att[10]), att1[10]);
                            Assert.AreEqual(cord0["lon"], att2[11]);
                            Assert.AreEqual(cord0["lat"], att2[12]);

                            Assert.AreEqual(cord1["lon"], att2[9]);
                            Assert.AreEqual(cord1["lat"], att2[10]);
                            Assert.AreEqual(durationConverter(att[11]), att2[11]);
                            Assert.AreEqual(durationConverter(att[12]), att2[12]);
                            MessageBox.Show("Succeed to compute the correct start and finish coordinates");
                        }
                        catch
                        {
                            MessageBox.Show("Failed to compute the correct start and finish coordinates");
                            flag = 1;

                        }
                        Assert.AreEqual(0,flag);
                        MessageBox.Show("Passed the test for split a trip at its first point on file level");
                    }
                    catch
                    {
                        MessageBox.Show("Failed the test for split a trip at its first point on file level");
                        return;
                    }
                    MessageBox.Show("Successfully split a trip at its first point");
                }
                catch
                {
                    MessageBox.Show("Failed to split a trip at its first point", "ERROR");
                    return;
                }

                //-------------------------------------------------------------------------------------
                MessageBox.Show("Test for split a trip at any point");
                try
                {
                    String name = "Trip_5";
                    IKmlFolder temp = t_pool.getByName(name);
                    int index = (temp.getFeatures().getChildNodes().getLength())/2;

                    IKmlPlacemark sst = (IKmlPlacemark)temp.getFeatures().getChildNodes().item(index-1);
                    IKmlPlacemark st = (IKmlPlacemark)temp.getFeatures().getChildNodes().item(index);

                    int pt_size = temp.getFeatures().getChildNodes().getLength();
                    int init_size_t = t_pool.getSize();
                    int init_size_a = t_pool.getAttrs().Count;
                    String[] att = t_pool.getAttByName(name);
                    split(st);

                    try
                    {
                        int final_size_t = t_pool.getSize();
                        Assert.AreEqual(init_size_t, final_size_t - 1);
                        Assert.AreEqual(pt_size, t_pool.getByName("Trip_5").getFeatures().getChildNodes().getLength() + t_pool.getByName("Trip_6").getFeatures().getChildNodes().getLength());
                        MessageBox.Show("Passed the test for split a trip at any point on GUI level");
                    }
                    catch
                    {
                        MessageBox.Show("Failed the test for split a trip at any point on GUI level");
                        return;
                    }

                    try
                    {
                        int final_size_a = t_pool.getAttrs().Count;
                        Assert.AreEqual(init_size_a, final_size_a - 1);
                        String[] att1 = t_pool.getAttByName("Trip_5");
                        String[] att2 = t_pool.getAttByName("Trip_6");

                        try
                        {
                            Assert.AreEqual(att[4], att1[4]);
                            Assert.AreEqual(att[5], att2[5]);

                            MessageBox.Show("Succeed to compute the correct start and finish time");
                        }
                        catch
                        {
                            MessageBox.Show("Failed to compute the correct start and finish time");
                        }

                        try
                        {
                            Assert.AreEqual(durationConverter(att[6]), durationConverter(att1[6]) + durationConverter(att2[6]) + durationConverter(duration(st.getName(), sst.getName())));
                            MessageBox.Show("Succeed to compute the correct trip duration");
                        }
                        catch
                        {
                            MessageBox.Show("Failed to compute the correct the trip duration");
                        }

                        try
                        {
                            Hashtable cord0 = getCoordinates((IKmlPlacemark)temp.getFeatures().getChildNodes().item(index-1));
                            Hashtable cord1 = getCoordinates(st);
                            Assert.AreEqual(durationConverter(att[9]), att1[9]);
                            Assert.AreEqual(durationConverter(att[10]), att1[10]);
                            Assert.AreEqual(cord0["lon"], att2[11]);
                            Assert.AreEqual(cord0["lat"], att2[12]);

                            Assert.AreEqual(cord1["lon"], att2[9]);
                            Assert.AreEqual(cord1["lat"], att2[10]);
                            Assert.AreEqual(durationConverter(att[11]), att2[11]);
                            Assert.AreEqual(durationConverter(att[12]), att2[12]);
                            MessageBox.Show("Succeed to compute the correct start and finish coordinates");
                        }
                        catch
                        {
                            MessageBox.Show("Failed to compute the correct start and finish coordinates");

                        }

                        MessageBox.Show("Passed the test for split a trip at any point on file level");
                    }
                    catch
                    {
                        MessageBox.Show("Failed the test for split a trip at any point on file level");
                        return;
                    }
                    MessageBox.Show("Successfully split a trip at any point");
                }
                catch
                {
                    MessageBox.Show("Failed to split a trip at any point", "ERROR");
                }

                //-------------------------------------------------------------------------------------
                MessageBox.Show("Test for split a trip at its last point");
                try
                {
                    String name = "Trip_4";
                    IKmlFolder temp = t_pool.getByName(name);

                    int pt_size = temp.getFeatures().getChildNodes().getLength();

                    IKmlPlacemark sst = (IKmlPlacemark)temp.getFeatures().getChildNodes().item(pt_size-2);
                    IKmlPlacemark st = (IKmlPlacemark)temp.getFeatures().getChildNodes().item(pt_size-1);

                    int init_size_t = t_pool.getSize();
                    int init_size_a = t_pool.getAttrs().Count;
                    String[] att = t_pool.getAttByName(name);
                    split(st);
                    try
                    {

                        int final_size_t = t_pool.getSize();
                        Assert.AreEqual(init_size_t, final_size_t - 1);
                        Assert.AreEqual(0, t_pool.getByName("Trip_4").getFeatures().getChildNodes().getLength());
                        Assert.AreEqual(pt_size, t_pool.getByName("Trip_5").getFeatures().getChildNodes().getLength());
                        MessageBox.Show("Passed the test for split a trip at its final point on GUI level");
                    }
                    catch
                    {
                        MessageBox.Show("Failed the test for split a trip at its final point on GUI level");
                        return;
                    }


                    try
                    {
                        int final_size_a = t_pool.getAttrs().Count;
                        Assert.AreEqual(init_size_a, final_size_a - 1);
                        String[] att1 = t_pool.getAttByName("Trip_4");
                        String[] att2 = t_pool.getAttByName("Trip_5");

                        try
                        {
                            Assert.AreEqual(att[4], att1[4]);
                            Assert.AreEqual(att[5], att2[5]);

                            MessageBox.Show("Succeed to compute the correct start and finish time");
                        }
                        catch
                        {
                            MessageBox.Show("Failed to compute the correct start and finish time");
                        }

                        try
                        {
                            Assert.AreEqual(durationConverter(att[6]), durationConverter(att1[6]) + durationConverter(att2[6]) + durationConverter(duration(st.getName(), sst.getName())));
                            MessageBox.Show("Succeed to compute the correct trip duration");
                        }
                        catch
                        {
                            MessageBox.Show("Failed to compute the correct the trip duration");
                        }

                        try
                        {
                            Hashtable cord0 = getCoordinates((IKmlPlacemark)temp.getFeatures().getChildNodes().item(pt_size-1));
                            Hashtable cord1 = getCoordinates(st);
                            Assert.AreEqual(durationConverter(att[9]), att1[9]);
                            Assert.AreEqual(durationConverter(att[10]), att1[10]);
                            Assert.AreEqual(cord0["lon"], att2[11]);
                            Assert.AreEqual(cord0["lat"], att2[12]);

                            Assert.AreEqual(cord1["lon"], att2[9]);
                            Assert.AreEqual(cord1["lat"], att2[10]);
                            Assert.AreEqual(durationConverter(att[11]), att2[11]);
                            Assert.AreEqual(durationConverter(att[12]), att2[12]);
                            MessageBox.Show("Succeed to compute the correct start and finish coordinates");
                        }
                        catch
                        {
                            MessageBox.Show("Failed to compute the correct start and finish coordinates");

                        }

                        MessageBox.Show("Passed the test for split a trip at its final point on file level");
                    }
                    catch
                    {
                        MessageBox.Show("Failed the test for split a trip at its final point on file level");
                        return;
                    }
                    MessageBox.Show("Successfully split a trip at its final point");
                }
                catch
                {
                    MessageBox.Show("Failed to split a trip at its final point", "ERROR");
                    return;
                }

                //-------------------------------------------------------------------------------------
                MessageBox.Show("Test for Join 2 consective trips");
                try
                {
                    String name = "Trip_4";
                    String[] temp = new String[14];
                    int size1 = t_pool.getByName(name).getFeatures().getChildNodes().getLength();
                    int size2 = t_pool.getByName("Trip_5").getFeatures().getChildNodes().getLength();
                    t_pool.insert(name,t_pool.getByName(name),temp);

                    int size = t_pool.getByName(name).getFeatures().getChildNodes().getLength();

                    Assert.AreEqual(size, size1+size2);
                    MessageBox.Show("Successfully Joined 2 consective trips");
                }
                catch
                {
                    MessageBox.Show("Failed to Join 2 consective trip", "ERROR");
                    return;
                }

                //-------------------------------------------------------------------------------------
                MessageBox.Show("Test for delete a trip");
                try
                {
                    String name = "Trip_4";

                    int size = t_pool.getSize();
                    t_pool.remove(name);
                    int _size = t_pool.getSize();
                    Assert.AreEqual(size, _size+1);
                    MessageBox.Show("Successfully deleted a trip");
                }
                catch
                {
                    MessageBox.Show("Failed to delete a trip", "ERROR");
                    return;
                }

                //-------------------------------------------------------------------------------------
                MessageBox.Show("Test for Making Start");
                try
                {
                    String name = "Trip_4";
                    IKmlFolder t_name = t_pool.getByName(name);
                    IKmlPlacemark initStart = t_pool.getStart(t_name);
                    IKmlObjectList initpoints = t_name.getFeatures().getChildNodes();
                    int initsize = initpoints.getLength() - 1;
                    String[] att1 = t_pool.getAttByName("Trip_4");
                    

                    // I want to make a new start with a new point. How do I call that function?
                    //makestart(newpoint);
                    IKmlPlacemark finalStart = t_pool.getStart(t_name);
                    IKmlObjectList finalpoints = t_name.getFeatures().getChildNodes();
                    int finalsize = finalpoints.getLength() - 1;
                    Assert.AreNotSame(initStart, finalStart);
                    Assert.AreEqual(initsize, finalsize + 1);
                    MessageBox.Show("Successfully Made New Starting point");
                    Hashtable cord1 = getCoordinates(finalStart);


                    try
                    {
                        Assert.AreSame(att1[4], name);
                        Assert.AreEqual(att1[9], cord1["lon"]);
                        Assert.AreEqual(att1[9], cord1["lat"]);
                        MessageBox.Show("Successfully modified the txt file for the Make Start function");
                    }
                    catch
                    {
                        MessageBox.Show("Failed to modify txt file with the Make Start function");
                    }

                }
                catch
                {
                    MessageBox.Show("Failed to make start", "ERROR");
                    return;
                }

                //--------------------------------------------------------------------------------
                MessageBox.Show("Test for Making Finish");
                try
                {
                    String name = "Trip_4";
                    IKmlFolder t_name = t_pool.getByName(name);
                    IKmlPlacemark initFinish = t_pool.getFinish(t_name);
                    IKmlObjectList initpoints = t_name.getFeatures().getChildNodes();
                    int initsize = initpoints.getLength() - 1;
                    String[] att1 = t_pool.getAttByName("Trip_4");
                    
                    // I want to make a new finish with a new point. How do I call that function?
                    //makefinish(newpoint);
                    IKmlPlacemark finalFinish = t_pool.getStart(t_name);
                    IKmlObjectList finalpoints = t_name.getFeatures().getChildNodes();
                    int finalsize = finalpoints.getLength() - 1;
                    Assert.AreNotSame(initFinish, finalFinish);
                    Assert.AreEqual(initsize, finalsize + 1);
                    MessageBox.Show("Successfully Made New Finishing point");
                    Hashtable cord1 = getCoordinates(finalFinish);
                    try
                    {
                        Assert.AreSame(att1[4], name);
                        Assert.AreEqual(att1[9], cord1["lon"]);
                        Assert.AreEqual(att1[9], cord1["lat"]);
                        MessageBox.Show("Successfully modified the txt file for the Make Finish function");
                    }
                    catch
                    {
                        MessageBox.Show("Failed to modify txt file with the Make Finish function");
                    }

                }
                catch
                {
                    MessageBox.Show("Failed to make finish", "ERROR");
                    return;
                }
                //---------------------------------------------------------------------------
            }
            catch
            {
                MessageBox.Show("Failed to initialize test, KML and TXT file required");

            }

        }
   }
}
