using System;
using System.Collections;
using System.Linq;
using System.Text;
using GEPlugin;
using System.Windows.Forms;
using System.Data;

namespace Editing_Tool
{
    class TripPool
    {
        IGEPlugin ge = null;
        ArrayList _core;
        ArrayList _attr;
        DataTable TripDetails;
        ArrayList _st;
        ArrayList _fn;
        String p_highlight;
        String _style;
        IKmlStyle sty;
        int tripCount;
        Rec record = new Rec();

        //Global Trip Data

        String HouseHoldID;
        String Day;
        String Date;
        String WeekDay;


        public TripPool(IGEPlugin _ge)
        {
            ge = _ge;
            _core = new ArrayList();
            _attr = new ArrayList();
            TripDetails = new DataTable();
            _st = new ArrayList();
            _fn = new ArrayList();
            p_highlight = "";
            _style = "";
            tripCount = 1;
            TripDetails.Columns.Add("KMLTrip");
            TripDetails.Columns.Add("Day");
            TripDetails.Columns.Add("Trip");
            TripDetails.Columns.Add("HouseHoldID");  
            TripDetails.Columns.Add("Person");
            TripDetails.Columns.Add("Date");   
            TripDetails.Columns.Add("WeekDay");  
            TripDetails.Columns.Add("Start Time");  
            TripDetails.Columns.Add("Finish Time"); 
            TripDetails.Columns.Add("Time");  
            TripDetails.Columns.Add("Distance");  
            TripDetails.Columns.Add("Speed");  
            TripDetails.Columns.Add("StartLong");  
            TripDetails.Columns.Add("StartLat");  
            TripDetails.Columns.Add("FinishLong");  
            TripDetails.Columns.Add("FinishLat");
            TripDetails.Columns.Add("Remain");

            HouseHoldID = "";
            Day = "";
            Date = "";
            WeekDay = "";
        }

        /*
         * add a new trip to the end of trippool
         */
        public void add(IKmlFolder trip)
        {
            IKmlFolder addTrip = trip;
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            IKmlPlacemark startPoint = (IKmlPlacemark)points.item(0);
            IKmlPlacemark finishPoint = (IKmlPlacemark)points.item(points.getLength()-1);
            String startTime = startPoint.getName();
            String finishTime = finishPoint.getName();
            String startLong = Module.getCoordinates(startPoint)["lon"].ToString();
            String startLat = Module.getCoordinates(startPoint)["lat"].ToString();
            String time = (DateTime.Parse(finishTime) - DateTime.Parse(startTime)).ToString();
            String distance =  Module.calDistance(trip).ToString();
            String finishLong = Module.getCoordinates(finishPoint)["lon"].ToString();
            String finishLat = Module.getCoordinates(finishPoint)["lat"].ToString();
            String[] timeSplit = new String[3];
            timeSplit = time.ToString().Split(':');
            double coEff = (3600 / (double)((Convert.ToInt32(timeSplit[0]) * 3600) + (Convert.ToInt32(timeSplit[1]) * 60) + (Convert.ToInt32(timeSplit[2]))));
            String speed = Math.Round((double.Parse(distance) * coEff), 3).ToString();
            _core.Add(addTrip);
            //_attr.Add(addAtt);
            TripDetails.Rows.Add(tripCount, Day, "-", HouseHoldID, "-", Date, WeekDay, startTime, finishTime, time, distance, speed, startLong, startLat, finishLong, finishLat, "-");
            ++tripCount;
        }

        public DataRow NewRowDataTableCustom()
        {
            DataRow newRow = TripDetails.NewRow();
            for (int i = 0; i != 17; ++i)
            {
                newRow[i] = "-";
            }
            return newRow;
        }

        public void addAtPosition(IKmlFolder trip, int tripNumber)
        {
            IKmlFolder addTrip = trip;
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            IKmlPlacemark startPoint = (IKmlPlacemark)points.item(0);
            IKmlPlacemark finishPoint = (IKmlPlacemark)points.item(points.getLength() - 1);
            String startTime = startPoint.getName();
            String finishTime = finishPoint.getName();
            String startLong = Module.getCoordinates(startPoint)["lon"].ToString();
            String startLat = Module.getCoordinates(startPoint)["lat"].ToString();
            String time = (DateTime.Parse(finishTime) - DateTime.Parse(startTime)).ToString();
            String distance = Module.calDistance(trip).ToString();
            String finishLong = Module.getCoordinates(finishPoint)["lon"].ToString();
            String finishLat = Module.getCoordinates(finishPoint)["lat"].ToString();
            String[] timeSplit = new String[3];
            timeSplit = time.ToString().Split(':');
            double coEff = (3600 / (double)((Convert.ToInt32(timeSplit[0]) * 3600) + (Convert.ToInt32(timeSplit[1]) * 60) + (Convert.ToInt32(timeSplit[2]))));
            String speed = Math.Round((double.Parse(distance) * coEff), 3).ToString();
  //          _core.Add(addTrip);
            //_attr.Add(addAtt);
            DataRow newRow = NewRowDataTableCustom();
            newRow["KMLTrip"] = tripCount;
            newRow["HouseHoldID"] = HouseHoldID;
            newRow["Trip"] = "-";
            newRow["Person"] = "-";
            newRow["Day"] = Day;
            newRow["Date"] = Date;
            newRow["WeekDay"] = WeekDay;
            newRow["Start Time"] = startTime;
            newRow["Finish Time"] = finishTime;
            newRow["Time"] = time;
            newRow["Distance"] = distance;
            newRow["Speed"] = speed;
            newRow["StartLong"] = startLong;
            newRow["StartLat"]= startLat;
            newRow["Finishlong"] = finishLong;
            newRow["FinishLat"] = finishLat;
            newRow["Remain"] = "-";
            TripDetails.Rows.InsertAt(newRow, tripNumber);
            resetTripCount();
        }

        public void addGlobalVariables(String[] att)
        {
            HouseHoldID = att[0];
            Day = att[1];
            Date = att[2];
            WeekDay = att[3];
        }

        public void resetTripData(String trip)
        {
            IKmlFolder tripData = getByName(trip);
            for (int i = 0; i != TripDetails.Rows.Count; ++i)
            {
                if (TripDetails.Rows[i]["KMLTrip"].ToString().Trim().Equals(Module.getIndex(trip).ToString()) )
                {
 //                   MessageBox.Show("FCKING "+trip);
                    IKmlFolder addTrip = tripData;
                    IKmlObjectList points = tripData.getFeatures().getChildNodes();
                    IKmlPlacemark startPoint = (IKmlPlacemark)points.item(0);
                    IKmlPlacemark finishPoint = (IKmlPlacemark)points.item(points.getLength() - 1);
                    String startTime = startPoint.getName();
                    String finishTime = finishPoint.getName();
                    String startLong = Module.getCoordinates(startPoint)["lon"].ToString();
                    String startLat = Module.getCoordinates(startPoint)["lat"].ToString();
                    String time = (Convert.ToDateTime(finishTime) - Convert.ToDateTime(startTime)).ToString();
                    String distance = Module.calDistance(tripData).ToString();
                    String finishLong = Module.getCoordinates(finishPoint)["lon"].ToString();
                    String finishLat = Module.getCoordinates(finishPoint)["lat"].ToString();
                    String[] timeSplit = new String[3];
                    timeSplit = time.ToString().Split(':');
                    double coEff = (3600 / (double)((Convert.ToInt32(timeSplit[0]) * 3600) + (Convert.ToInt32(timeSplit[1]) * 60) + (Convert.ToInt32(timeSplit[2]))));
                    String speed = Math.Round((double.Parse(distance) * coEff), 3).ToString();
                    TripDetails.Rows[i]["Start Time"] = startTime;
                    TripDetails.Rows[i]["Finish Time"] = finishTime;
                    TripDetails.Rows[i]["Time"] = time;
                    TripDetails.Rows[i]["Distance"] = distance;
                    TripDetails.Rows[i]["Speed"] = speed;
                    TripDetails.Rows[i]["StartLong"] = startLong;
                    TripDetails.Rows[i]["StartLat"] = startLat;
                    TripDetails.Rows[i]["Finishlong"] = finishLong;
                    TripDetails.Rows[i]["FinishLat"] = finishLat;
                    TripDetails.Rows[i]["Remain"] = "-";
                }

            }
        }

        public void resetTripCount()
        {
            for (int i = 0; i != TripDetails.Rows.Count; ++i)
            {
                TripDetails.Rows[i]["KMLTrip"] = i + 1;
            }
        }

        public void removeKMLTrip(String trip)
        {
            for (int i = 0; i < TripDetails.Rows.Count; ++i)
            {
                if (TripDetails.Rows[i]["KMLTrip"].Equals(trip))
                {
                    TripDetails.Rows[i].Delete();
                }
            }
            resetTripCount();
        }

        public DataTable getTripDetails()
        {
            return TripDetails;
        }

        public void removeLastPoint(String trip)
        {
            //This will remove the last point of the trip
            IKmlFolder tripDetails = getByName(trip);
            //Once we have the trip, we'll remove the last child
            tripDetails.getFeatures().removeChild(tripDetails.getFeatures().getLastChild());   
        }

        public void removeFirstPoint(String trip)
        {
            //This will remove the first point of the trip
            IKmlFolder tripDetails = getByName(trip);
            //Once we've found the trip, we'll remove the first child
            tripDetails.getFeatures().removeChild(tripDetails.getFeatures().getFirstChild());
        }


        public String[] getTripDetailsForTrip(String tripNumber)
        {
            String[] returnString = new String[17];
            for (int i = 0; i != TripDetails.Rows.Count; ++i)
            {
                if (TripDetails.Rows[i]["KMLTrip"].Equals(tripNumber))
                {
                    for (int j = 0; j != 17; ++j)
                    {
                        returnString[j] = TripDetails.Rows[i][j].ToString();
                    }
                }
            }
            return returnString;
        }

        /*
         * add a new trip to a particular position of trippool defined by its name index
         */
        public void add(String name, IKmlFolder trip, String[] att)
        {
 	            de_highlight();
 	            int index = Module.getIndex(name);
 	            _core.Insert(index - 1, trip);
 	            //_attr.Insert(index - 1, att);
        }

        /*
         * insert 2 trips into trippool and remove the old trip at the same index of first trip ( this is used by split )
         */
        public void insert(int index, IKmlFolder trip1, String[] att1, IKmlFolder trip2, String[] att2)
        {
            int t = Module.getIndex(trip1.getName());
            _core.RemoveAt(t-1);

            //_attr.RemoveAt(t - 1);


            _core.Insert(t - 1, trip1);
            //_attr.Insert(t - 1, att1);

            _core.Insert(t, trip2);
            //_attr.Insert(t, att2);
        }

        /*
         * insert a trip into trippool and remove the trip at the same index as well as the one after ( this is used by join )
         */
        public String insert(String name, IKmlFolder trip, String[] att, IKmlStyle sty)
        {
            de_highlight();
            int index = int.Parse(name.Split('_')[1]);
            String style = "";
            IKmlFolder temp1 = getByName("Trip_" + index);
            IKmlFolder temp2 = getByName("Trip_" + (index + 1));
            
            IKmlObjectList points = temp1.getFeatures().getChildNodes();
            for (int ii = 0; ii != points.getLength(); ii++)
            {
                IKmlPlacemark point = (IKmlPlacemark)points.item(ii);
                trip.getFeatures().appendChild(point);
                if (ii == 0)
                {
                    style = point.getComputedStyle().getIconStyle().getColor().get();
                }
            }
            points = temp2.getFeatures().getChildNodes();

	 	    IKmlStyleMap sm = ge.createStyleMap(""); 
	 	    IKmlStyle normal = mkStyle(style, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3); 
	 	    IKmlStyle highlight = mkStyle(style, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4); 
	 	    sm.setNormalStyle(normal); 
	 	    sm.setHighlightStyle(highlight); 
            for (int ii = 0; ii != points.getLength(); ii++)
            {
                IKmlPlacemark point = (IKmlPlacemark)points.item(ii);


                if (ii == 0)
                {
                    _style = point.getComputedStyle().getIconStyle().getColor().get();
                }
                if (point.getGeometry().getType() != "KmlPoint")
                {
                    point.getComputedStyle().getLineStyle().setWidth((float)4);
                    point.getComputedStyle().getLineStyle().getColor().set(style);

                }
                else
                {
                    point.setStyleSelector(sm);
                }
                    trip.getFeatures().appendChild(point);
            }

            _core.RemoveAt(index - 1);
           // _attr.RemoveAt(index - 1);
           // removeKMLTrip(index.ToString());

            _core.RemoveAt(index - 1);
            //_attr.RemoveAt(index - 1);
           // removeKMLTrip(index.ToString());

            _core.Insert(index - 1, trip);
           // _attr.Insert(index - 1, att);
           // addAtPosition(trip, index - 1);

            return _style;
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
         * get the parent trip name of placemark
         */
        public String getParent(String name)
        {
            for (int i = 0; i != _core.Count; i++)
            {
                IKmlFolder trip = (IKmlFolder)_core[i];
                if (include(trip, name))
                {
                    return ("Trip_"+(i+1).ToString());
                }
            }
            return null;
        }

        /*
         * check whether a point is included in the trip
         */
        public bool include(IKmlFolder trip, String point)
        {
           DateTime s_point = Convert.ToDateTime(getStart(trip).getName());
            DateTime _point = Convert.ToDateTime(point);

            if (Convert.ToDateTime(getFinish(trip).getName()).CompareTo(_point) == 1 && _point.CompareTo(Convert.ToDateTime(getStart(trip).getName())) == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        /*
         * get size of the trippool
         */
        public int getSize()
        {
            return _core.Count;
        }

        public ArrayList getNames()
        {
            ArrayList output = new ArrayList();
            for (int i = 0; i != _core.Count; i++)
            {
                output.Add("Trip_" + (i + 1).ToString());
            }
            return output;
        }

        public String ch_col(String name, String col)
        {
            IKmlStyleMap sm = ge.createStyleMap("");
            IKmlStyle normal = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3);
            IKmlStyle highlight = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4);
            sm.setNormalStyle(normal);
            sm.setHighlightStyle(highlight);
            IKmlFolder trip = getByName(name);
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            String temp = ((IKmlPlacemark)points.item(0)).getComputedStyle().getIconStyle().getColor().get();
            for (int i = 0; i < points.getLength(); i++)
            {
                IKmlPlacemark pt =(IKmlPlacemark) points.item(i);
                pt.setStyleSelector(sm);
            }
            return temp;
        }

        /*
         * get the trip object by its name
         */
        public IKmlFolder getByName(String name)
        {
            return (IKmlFolder)_core[Module.getIndex(name) - 1];
        }

        /*
         * get the trip info by its name
         */
        public String[] getAttByName(String name)
        {
            return (String[])_attr[Module.getIndex(name) - 1];
        }

        public void remove(String name)
        {
            de_highlight();
            int index = Module.getIndex(name);
            _core.RemoveAt(index - 1);
            //_attr.RemoveAt(index - 1);
            TripDetails.Rows[index - 1].Delete();
        }

        public Hashtable getFocus(String name)
        {
            Hashtable output = new Hashtable();
            IKmlFolder trip = getByName(name);
            IKmlPlacemark s_point = getStart(trip);
            IKmlPlacemark f_point = getFinish(trip);
            Hashtable s_cords = Module.getCoordinates(s_point);
            Hashtable f_cords = Module.getCoordinates(f_point);
            float m_lon = (float.Parse(s_cords["lon"].ToString()) + float.Parse(f_cords["lon"].ToString())) / 2;
            float m_lat = (float.Parse(s_cords["lat"].ToString()) + float.Parse(f_cords["lat"].ToString())) / 2;
            output["lon"] = m_lon;
            output["lat"] = m_lat;
            return output;
        }

        /*
         * get the coordinates of a point
         */

        public IKmlPlacemark getStart(IKmlFolder trip)
        {
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            return (IKmlPlacemark)points.item(0);
        }

        public IKmlPlacemark getFinish(IKmlFolder trip)
        {
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            return (IKmlPlacemark)points.item(points.getLength() - 1);
        }

        public void highlight(String name)
        {
            if (p_highlight != "")
            {
                de_highlight();
            }
            IKmlFolder trip = getByName(name);
            IKmlPlacemark s_point = getStart(trip);
            IKmlPlacemark f_point = getFinish(trip);

            if (s_point == f_point)
            {
                return;
            }

            String col = ((IKmlPlacemark)trip.getFeatures().getChildNodes().item(0)).getComputedStyle().getIconStyle().getColor().get();

            IKmlIcon icon = ge.createIcon("");
            icon.setHref(@"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png");
            IKmlStyle ssty = ge.createStyle("");
            ssty.getIconStyle().setIcon(icon);
            ssty.getIconStyle().setScale((float)0.9);
            ssty.getIconStyle().getColor().set(col);

            s_point.setStyleSelector(ssty);
            f_point.setStyleSelector(ssty);
            p_highlight = name;
        }

        public void de_highlight()
        {
            if (p_highlight != "")
            {
                IKmlPlacemark p_s_point = getStart(getByName( p_highlight));
                IKmlPlacemark p_f_point = getFinish(getByName( p_highlight));

                String col = ((IKmlPlacemark)getByName(p_highlight).getFeatures().getChildNodes().item(0)).getComputedStyle().getIconStyle().getColor().get();

	 	        IKmlStyleMap sm = ge.createStyleMap(""); 
	 	        IKmlStyle normal = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3); 
	 	        IKmlStyle highlight = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4); 
	 	        sm.setNormalStyle(normal); 
	 	        sm.setHighlightStyle(highlight); 
	 	        p_s_point.setStyleSelector(sm); 
	 	        p_f_point.setStyleSelector(sm); 

                p_highlight = "";
            }
        }

 /*      public void de_highlight_start()
        {
            if (p_highlight != "")
            {
                IKmlPlacemark p_s_point = getStart(getByName(p_highlight));
                p_s_point.setStyleUrl(_style);
                p_highlight = "";
            }
        }

        public void de_highlight_finish()
        {
            if (p_highlight != "")
            {
                IKmlPlacemark p_f_point = getStart(getByName(p_highlight));
                p_f_point.setStyleUrl(_style);
                p_highlight = "";
            }
        }
*/

        public ArrayList getAttrs()
        {
            return _attr;
        }

        public void addToStart(String name, IKmlPlacemark point)
        {
            IKmlFolder trip = getByName(name);
            IKmlObjectList points = trip.getFeatures().getChildNodes();

            String col = ((IKmlPlacemark)trip.getFeatures().getChildNodes().item(2)).getComputedStyle().getIconStyle().getColor().get();

	 	    IKmlStyleMap sm = ge.createStyleMap(""); 
	 	    IKmlStyle normal = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3); 
	 	    IKmlStyle highlight = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4); 
	 	    sm.setNormalStyle(normal); 
	 	    sm.setHighlightStyle(highlight); 
	 	 
	 	    point.setStyleSelector(sm);

            trip.getFeatures().insertBefore(point,points.item(0));
        }

        public void addToEnd(string name, IKmlPlacemark point)
        {
            IKmlFolder trip = getByName(name);
            IKmlObjectList points = trip.getFeatures().getChildNodes();

            String col = ((IKmlPlacemark)trip.getFeatures().getChildNodes().item(2)).getComputedStyle().getIconStyle().getColor().get();

	 	    IKmlStyleMap sm = ge.createStyleMap(""); 
	 	    IKmlStyle normal = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3); 
	 	    IKmlStyle highlight = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4); 
	 	    sm.setNormalStyle(normal); 
	 	    sm.setHighlightStyle(highlight); 
	 	    point.setStyleSelector(sm);

            trip.getFeatures().appendChild(point);
        }

        public ArrayList trimToStart(String name, String time)
        {
            IKmlFolder trip = getByName(name);
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            ArrayList buffer = new ArrayList();
            for (int i = 0; i < points.getLength(); i++)
            {
                if (Convert.ToDateTime(((IKmlPlacemark)points.item(i)).getName()) < Convert.ToDateTime(time))
                {
                    buffer.Add(points.item(i));
                }
                else
                {
                    break;
                }
            }

            for (int i = 0; i < buffer.Count; i++)
            {
                trip.getFeatures().removeChild(buffer[i]);
            }
            return buffer;
        }

        public ArrayList trimToEnd(String name, String time)
        {
            IKmlFolder trip = getByName(name);
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            ArrayList buffer = new ArrayList();
            for (int i = points.getLength()-1; i >=  0; i--)
            {
                if (Convert.ToDateTime(((IKmlPlacemark)points.item(i)).getName()) > Convert.ToDateTime(time))
                {
                    buffer.Add(points.item(i));
                }
                else
                {
                    break;
                }
            }
            for (int i = 0; i < buffer.Count; i++)
            {
                trip.getFeatures().removeChild(buffer[i]);
            }
            return buffer;
        }

        public void clear()
        {
            _core.Clear();
        }

    }
}
