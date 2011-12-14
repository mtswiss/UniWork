using System;
using System.Collections;
using System.Linq;
using System.Text;
using GEPlugin;
using System.Windows.Forms;

namespace Editing_Tool
{
    class Controller
    {
        private Rec record = new Rec();
        private TripPool t_pool;
        private IGEPlugin ge = null;
        private String sel_style = "";
        private IKmlPlacemark sel_point = null;

        public Controller(IGEPlugin _ge, TripPool _t_pool, Rec _record)
        {
            ge = _ge;
            record = _record;
            t_pool = _t_pool;
        }

        public void highlight(IKmlPlacemark point)
        {
            de_highlight();

            IKmlIcon icon = ge.createIcon("");
            icon.setHref(@"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png");
            IKmlStyle ssty = ge.createStyle("");
            ssty.getIconStyle().setIcon(icon);
            ssty.getIconStyle().setScale((float)0.9);
            ssty.getIconStyle().getColor().set(point.getComputedStyle().getIconStyle().getColor().get());

            point.setStyleSelector(ssty);
            sel_point = point;
        }

        public bool de_highlight()
        {
            if (sel_point != null)
            {
                IKmlStyleMap sm = ge.createStyleMap("");
                IKmlStyle normal = mkStyle(sel_point.getComputedStyle().getIconStyle().getColor().get(), @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3);
                IKmlStyle highlight = mkStyle(sel_point.getComputedStyle().getIconStyle().getColor().get(), @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4);
                sm.setNormalStyle(normal);
                sm.setHighlightStyle(highlight);
                sel_point.setStyleSelector(sm);
                return true;
            }
            return false;
        }

        public Hashtable get_highlight()
        {
            Hashtable temp = new Hashtable();
            temp["point"] = sel_point;
            temp["style"] = sel_style;
            return temp;
        }

        public IKmlPlacemark get_sel_pt()
        {
            return sel_point;
        }

        public void rm_sel_pt()
        {
            sel_point = null;
        }

        public TripPool getTrips()
        {
            return t_pool;
        }

        public Rec getRecord()
        {
            return record;
        }

        public IKmlCamera allocate()
        {
            double lat = 0, lon = 0;
            IKmlObjectList days = ge.getFeatures().getChildNodes();
            IKmlDocument day = (IKmlDocument)days.item(0);
            IKmlObjectList trips = day.getFeatures().getChildNodes();
            for (int i = 0; i != ( t_pool.getSize() / 2 ); i++)
            {
                IKmlFolder trip = t_pool.getByName("Trip_"+(i+1));
                IKmlObjectList points = trip.getFeatures().getChildNodes();
                IKmlPlacemark point = (IKmlPlacemark)points.item(1);

                lon = (double)Module.getCoordinates(point)["lon"];
                lat = (double)Module.getCoordinates(point)["lat"];
            }
            //lon = lon / t_pool.getSize();
            // lat = lat / t_pool.getSize();
            IKmlCamera vw = ge.createCamera("");
            vw.set(lat, lon, 25000.0, ge.ALTITUDE_RELATIVE_TO_GROUND, 0, 0, 0);
            return vw;
        }

        public Boolean delete(String name)
        {
            try
            {
                ArrayList trip = new ArrayList();
                IKmlFolder _trip = t_pool.getByName(name);

                String[] att = t_pool.getTripDetailsForTrip(Module.getIndex(name).ToString());
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


        public IKmlFolder[] split(int index, IKmlFolder raw, IKmlPlacemark _point, String style)
        {
            IKmlFolder[] output = new IKmlFolder[2];

            String col = randomCol();
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
                    IKmlStyleMap sm = ge.createStyleMap("");
                    if (style != null)
                    {
                        if (point.getGeometry().getType() != "KmlPoint")
                        {
                            IKmlStyle sty = ge.createStyle("");
                            sty.getLineStyle().setWidth((float)4);
                            sty.getLineStyle().getColor().set(style);
                            point.setStyleSelector(sty);

                        }
                        else
                        {
                            IKmlStyle normal = mkStyle(style, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3);
                            IKmlStyle highlight = mkStyle(style, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4);
                            sm.setNormalStyle(normal);
                            sm.setHighlightStyle(highlight);
                            point.setStyleSelector(sm);
                        }
                    }
                    else
                    {
                        if (point.getGeometry().getType() != "KmlPoint")
                        {
                            IKmlStyle sty = ge.createStyle("");
                            sty.getLineStyle().setWidth((float)4);
                            sty.getLineStyle().getColor().set(col);
                            point.setStyleSelector(sty);
                        }
                        else
                        {

                            IKmlStyle normal = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3);
                            IKmlStyle highlight = mkStyle(col, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4);
                            sm.setNormalStyle(normal);
                            sm.setHighlightStyle(highlight);
                            point.setStyleSelector(sm);
                        }
                    }
                    temp2.getFeatures().appendChild(point);
                }
            }
            output[0] = temp1;
            output[1] = temp2;
            return output;
        }

        public String randomCol()
        {
            char[] colors = new char[16];
            colors[0]='0';
            colors[1]='1';
            colors[2]='2';
            colors[3]='3';
            colors[4]='4';
            colors[5]='5';
            colors[5]='6';
            colors[6]='7';
            colors[7]='8';
            colors[8]='9';
            colors[9]='a';
            colors[10]='b';
            colors[11]='c';
            colors[12]='d';
            colors[13]='e';
            colors[14]='f';
            String color = "ff";

            Random rnd = new Random();
            for (int i=0;i<6;i++)
            {
                color+=colors[rnd.Next(0,14)];
            }
            return color;
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

        public Boolean split(IKmlPlacemark sp_point)
        {
            try
            {
                Hashtable cords = Module.getCoordinates(sp_point);

                IKmlFolder _trip = (IKmlFolder)sp_point.getParentNode();
                _trip.setVisibility(0);

                String t_name = t_pool.getParent(sp_point.getName());
                String[] t_att = t_pool.getTripDetailsForTrip(Module.getIndex(t_name).ToString());
                ArrayList trip = new ArrayList();
                trip.Add(t_name);
                trip.Add(_trip);
                trip.Add(t_att);
                record.spl_trip(trip);

                int index = int.Parse((t_name.Split('_')[1]));
                IKmlFolder[] sub = split(index, _trip, sp_point,null);

                IKmlPlacemark fn = t_pool.getFinish(sub[0]);
                Hashtable _cords = Module.getCoordinates(fn);

                String[] att_temp1 = (String[])t_att.Clone();
                String[] att_temp2 = (String[])t_att.Clone();
/*
                att_temp1[5] = fn.getName();
                att_temp2[4] = sp_point.getName();

                att_temp1[6] = Module.duration(att_temp1[4], att_temp1[5]);
                att_temp2[6] = Module.duration(att_temp2[4], att_temp2[5]);

                att_temp1[11] = _cords["lon"].ToString();
                att_temp1[12] = _cords["lat"].ToString();

                att_temp2[9] = cords["lon"].ToString();
                att_temp2[10] = cords["lat"].ToString();
*/
                IKmlObjectList days = ge.getFeatures().getChildNodes(); 
                IKmlDocument day = (IKmlDocument)days.item(0);

                day.getFeatures().appendChild(sub[0]);
                day.getFeatures().appendChild(sub[1]);
/*
                if (sub[0].getFeatures().getChildNodes().getLength() <= sub[1].getFeatures().getChildNodes().getLength())
                {
                    double distance = Module.calDistance(sub[0]);
                    att_temp1[7] = distance.ToString();
                    att_temp2[7] = (double.Parse(t_att[7]) - distance).ToString();
                }
                else
                {
                    double distance = Module.calDistance(sub[1]);
                    att_temp2[7] = distance.ToString();
                    att_temp1[7] = (double.Parse(t_att[7]) - distance).ToString();
                }
*/
                /*
                 * The duration of a trip from might be less than 0 when the program interpreter inconsistent kml and txt file
                 * 
                 * chen
                 */
 /*               try
                {
                    att_temp1[8] = Math.Round((double.Parse(att_temp1[7]) / Module.durationConverter(att_temp1[6])), 3).ToString();
                    att_temp2[8] = Math.Round((double.Parse(att_temp2[7]) / Module.durationConverter(att_temp2[6])), 3).ToString();
                }
                catch
                {
                    MessageBox.Show("kml and txt file doesn't match");
                    att_temp2[8] = "-0";
                    att_temp1[8] = "-0";
                }
 */ 
                t_pool.insert(index, sub[0], att_temp1, sub[1], att_temp2);
                
                return true;
            }
            catch
            {
                return false;
            }
        }

        public IKmlCamera zoom(String trip)
        {
            IKmlCamera vw = ge.createCamera("");
            Hashtable coords = t_pool.getFocus(trip);
            vw.set((float)coords["lat"], (float)coords["lon"], 6000.0, ge.ALTITUDE_RELATIVE_TO_GROUND, 0, 0, 0);
            return vw;
        }

        public IKmlCamera focus(Hashtable coords)
        {
            IKmlCamera vw = ge.createCamera("");
            vw.set((float)coords["lat"], (float)coords["lon"], 100.0, ge.ALTITUDE_RELATIVE_TO_GROUND, 0, 0, 0);
            return vw;
        }

        public Boolean join(String t_name1, String t_name2)
        {
            try
            {
                IKmlFolder temp = ge.createFolder("");
                String[] trip1 = t_pool.getTripDetailsForTrip(Module.getIndex(t_name1).ToString());
                String[] trip2 = t_pool.getTripDetailsForTrip(Module.getIndex(t_name2).ToString());

                IKmlPlacemark point = t_pool.getStart(t_pool.getByName(t_name2));

                String[] trip = (String[])trip1.Clone();
 /*               trip[5] = trip2[5];
                trip[6] = Module.duration(trip[4], trip[5]);
                trip[11] = trip2[11];
                trip[12] = trip2[12];
*/
                Hashtable cord1 = Module.getCoordinates(t_pool.getFinish(t_pool.getByName(t_name1)));
                Hashtable cord2 = Module.getCoordinates(t_pool.getStart(t_pool.getByName(t_name2)));
/*
                trip[7] = (double.Parse(trip1[7]) + double.Parse(trip2[7]) + DistanceAlgorithm.DistanceBetweenPlaces((double)cord1["lat"], (double)cord1["lon"]
                            , (double)cord2["lat"], (double)cord2["lon"])).ToString();

                trip[8] = Math.Round((double.Parse(trip[7]) / Module.durationConverter(trip[6])), 3).ToString();
*/
                String style = t_pool.insert(t_name1, temp, trip, ge.createStyle(""));
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

        public Boolean insert(String tp1, String tp2)
        {
            try
            {
                // Get the end placemark of the 1st trip  and the start placemark of the second trip
                IKmlPlacemark tp1fn = t_pool.getFinish(t_pool.getByName(tp1));
                IKmlPlacemark tp2st = t_pool.getStart(t_pool.getByName(tp2));

                //create a place mark to store the new place mark

                IKmlPlacemark start = ge.createPlacemark("");
                IKmlPlacemark finish = ge.createPlacemark("");

                start.setName(tp1fn.getName());
                finish.setName(tp2st.getName());

                IKmlPoint sp = ge.createPoint("");
                IKmlPoint fp = ge.createPoint("");

                IKmlPlacemark _temp = ge.createPlacemark("");

                IKmlLineString temp = ge.createLineString("");
                
                // Retrieve the coordinates of the two trips
                Hashtable cds1 = Module.getCoordinates(tp1fn);
                Hashtable cds2 = Module.getCoordinates(tp2st);

                sp.setLatLng((double)cds1["lat"], (double)cds1["lon"]);
                start.setGeometry(sp);
                fp.setLatLng((double)cds2["lat"], (double)cds2["lon"]);
                finish.setGeometry(fp);

                String color = randomCol();

                IKmlStyleMap sm = ge.createStyleMap("");
                IKmlStyle normal = mkStyle(color, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.3);
                IKmlStyle highlight = mkStyle(color, @"http://maps.google.com/mapfiles/kml/paddle/wht-blank.png", (float)0.4);
                sm.setNormalStyle(normal);
                sm.setHighlightStyle(highlight);
                start.setStyleSelector(sm);
                finish.setStyleSelector(sm);

                temp.getCoordinates().pushLatLngAlt((double)cds1["lat"], (double)cds1["lon"], 0);
                temp.getCoordinates().pushLatLngAlt((double)cds2["lat"], (double)cds2["lon"], 0);
                _temp.setGeometry(temp);

                IKmlStyle sty = ge.createStyle("");
                sty.getLineStyle().setWidth((float)4);
                sty.getLineStyle().getColor().set(color);

                _temp.setStyleSelector(sty);

                //create a new KML folder for the new trip  and append the tmp features of the previous trip
                IKmlFolder temp1 = ge.createFolder("");

                temp1.getFeatures().appendChild(start);
                temp1.getFeatures().appendChild(_temp);
                temp1.getFeatures().appendChild(finish);

                String[] attributes = new String[14];

                //Add the new trip to the trip pools
                t_pool.add(tp2, temp1, attributes);
                ge.getFeatures().appendChild(temp1);

                // record the insert action for undo action
                record.ins_trip(tp2);


                return true;
            }
            catch
            {
                return false;
            }
        }

        public Boolean undo(Hashtable mem)
        {
            try
            {
                if (mem["opt"] == "del")
                {
                    ArrayList rev = (ArrayList)mem["data"];

                    IKmlFolder _trip = (IKmlFolder)rev[1];
                    _trip.setVisibility(1);
                    t_pool.add((String)rev[0], _trip, (String[])rev[2]);
                    
                }
                else if (mem["opt"] == "spl")
                {
                    ArrayList rev = (ArrayList)mem["data"];
                    IKmlFolder trip = (IKmlFolder)rev[1];

                    t_pool.insert((String)rev[0], trip, (String[])rev[2],ge.createStyle(""));
                    trip.setVisibility(1);
                    IKmlObjectList days = ge.getFeatures().getChildNodes();
                    IKmlDocument day = (IKmlDocument)days.item(0);
                    day.getFeatures().appendChild(trip);
                }
                else if (mem["opt"] == "joi")
                {
                    ArrayList rev = (ArrayList)mem["data"];
                    IKmlFolder temp = ge.createFolder("");

                    String name = (String)rev[0];
                    IKmlFolder[] sub = split(int.Parse((name.Split('_')[1])), t_pool.getByName(name), (IKmlPlacemark)rev[1], (String)rev[4]);

                    IKmlObjectList days = ge.getFeatures().getChildNodes();
                    IKmlDocument day = (IKmlDocument)days.item(0);

                    day.getFeatures().appendChild(sub[0]);
                    day.getFeatures().appendChild(sub[1]);

                    t_pool.insert(int.Parse((name.Split('_')[1])), sub[0], (String[])rev[2], sub[1], (String[])rev[3]);
                }
                else if (mem["opt"] == "ins")
                {
                    String rev = (String)mem["data"];
                    IKmlFolder trip = t_pool.getByName(rev);
                    trip.setVisibility(0);

                    t_pool.remove(rev);
                }
                else if (mem["opt"] == "crt")
                {
                    IKmlPlacemark pt =(IKmlPlacemark)mem["data"];
                    ge.getFeatures().removeChild(pt);
                }
                else if (mem["opt"] == "mk_start" || mem["opt"] == "mk_finish")
                {
                    ArrayList rev = (ArrayList)mem["data"];
                    IKmlPlacemark pt = (IKmlPlacemark)rev[1];
                    IKmlFolder trip = t_pool.getByName((String)rev[0]);
                    //trip.getFeatures().removeChild(pt);
                    //ge.getFeatures().appendChild(pt);
                }
                else if (mem["opt"] == "tm_start")
                {
                    ArrayList rev = (ArrayList) mem["data"];
                    IKmlFolder trip = t_pool.getByName((String)rev[0]);
                    IKmlObjectList points = trip.getFeatures().getChildNodes();
//                   MessageBox.Show(points.getLength().ToString()+" "+rev.Count.ToString());
                    for (int i = rev.Count - 1; i != 0; i--)
                    {
                        points = trip.getFeatures().getChildNodes();
                        trip.getFeatures().insertBefore(rev[i], points.item(0));
                    }

                }
                else if (mem["opt"] == "tm_finish")
                {
                    ArrayList rev = (ArrayList)mem["data"];
                    IKmlFolder trip = t_pool.getByName((String)rev[0]);
                    IKmlObjectList points = trip.getFeatures().getChildNodes();
                    //                   MessageBox.Show(points.getLength().ToString()+" "+rev.Count.ToString());
                    for (int i = rev.Count - 1; i != 0; i--)
                    {
                        points = trip.getFeatures().getChildNodes();
                        trip.getFeatures().insertBefore(rev[i], points.item(points.getLength()-1));
                    }

                }
                else if (mem["opt"] == "ch_color")
                {
                    ArrayList rev = (ArrayList)mem["data"];
                    t_pool.ch_col((String)rev[0],(String)rev[1]);
                }
                return true;
            }
            catch
            {
                return false;
            }
        }

    }
}
