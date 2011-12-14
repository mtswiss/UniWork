using System;
using System.Collections;
using System.Linq;
using System.Text;
using GEPlugin;
using System.Windows.Forms;

namespace Editing_Tool
{
    class TripPool
    {
        ArrayList _core;
        ArrayList _attr;
        String p_highlight;
        String _style;
        Rec record = new Rec();


        public TripPool()
        {
            _core = new ArrayList();
            _attr = new ArrayList();
            p_highlight = "";
            _style = "";
        }

        public void add(IKmlFolder trip, String[] att)
        {
            if (!_core.Contains(trip))
            {
                _core.Add(trip);
                _attr.Add(att);
            }
        }

        public void add(String name, IKmlFolder trip, String[] att)
        {
            de_highlight();
            int index = getIndex(name);
            _core.Insert(index - 1, trip);
            _attr.Insert(index - 1, att);
        }

        public void insert(int index, IKmlFolder trip1, String[] att1, IKmlFolder trip2, String[] att2)
        {
            int t = getIndex(trip1.getName());
            _core.RemoveAt(t-1);
            _attr.RemoveAt(t - 1);

            _core.Insert(t - 1, trip1);
            _attr.Insert(t - 1, att1);

            _core.Insert(t, trip2);
            _attr.Insert(t, att2);
        }

        public String insert(String name, IKmlFolder trip, String[] att)
        {
            de_highlight();
            int index = int.Parse(name.Split('_')[1]);
            String style = "";
            String _style = "";

            IKmlFolder temp1 = getByName("Trip_" + index);
            IKmlFolder temp2 = getByName("Trip_" + (index + 1));
            
            IKmlObjectList points = temp1.getFeatures().getChildNodes();
            for (int ii = 0; ii != points.getLength(); ii++)
            {
                IKmlPlacemark point = (IKmlPlacemark)points.item(ii);
                trip.getFeatures().appendChild(point);
                if (ii == 1)
                {
                    style = point.getStyleUrl();
                }
            }

            points = temp2.getFeatures().getChildNodes();
            for (int ii = 0; ii != points.getLength(); ii++)
            {
                IKmlPlacemark point = (IKmlPlacemark)points.item(ii);
                if (ii == 1)
                {
                    _style = point.getStyleUrl();
                }
                point.setStyleUrl(style);
                trip.getFeatures().appendChild(point);
            }

            _core.RemoveAt(index - 1);
            _attr.RemoveAt(index - 1);

            _core.RemoveAt(index - 1);
            _attr.RemoveAt(index - 1);

            _core.Insert(index - 1, trip);
            _attr.Insert(index - 1, att);

            return _style;
        }

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

        public IKmlFolder getByName(String name)
        {
            return (IKmlFolder)_core[getIndex(name) - 1];
        }

        public String[] getAttByName(String name)
        {
            return (String[])_attr[getIndex(name) - 1];
        }

        public int getIndex(String name)
        {
            return int.Parse(name.Split('_')[1]);
        }


        public void remove(String name)
        {
            de_highlight();
            int index = getIndex(name);
            _core.RemoveAt(index - 1);
            _attr.RemoveAt(index - 1);
        }

        public Hashtable getFocus(String name)
        {
            Hashtable output = new Hashtable();
            IKmlFolder trip = getByName(name);
            IKmlPlacemark s_point = getStart(trip);
            IKmlPlacemark f_point = getFinish(trip);
            Hashtable s_cords = getCoordinates(s_point);
            Hashtable f_cords = getCoordinates(f_point);
            float m_lon = (float.Parse((String)s_cords["lon"]) + float.Parse((String)f_cords["lon"])) / 2;
            float m_lat = (float.Parse((String)s_cords["lat"]) + float.Parse((String)f_cords["lat"])) / 2;
            output["lon"] = m_lon;
            output["lat"] = m_lat;
            return output;
        }

        private Hashtable getCoordinates(IKmlPlacemark point)
        {
            Hashtable cods = new Hashtable();
            String xml = point.getKml();
            String temp = System.Text.RegularExpressions.Regex.Split(xml, "<coordinates>")[1];
            String coords = System.Text.RegularExpressions.Regex.Split(temp, "</coordinates>")[0];
            Array value = System.Text.RegularExpressions.Regex.Split(coords, ",");
            cods["lon"] = value.GetValue(1);
            cods["lat"] = value.GetValue(0);
            return cods;
        }


        public IKmlPlacemark getStart(IKmlFolder trip)
        {
            IKmlObjectList points = trip.getFeatures().getChildNodes();
 //           MessageBox.Show(points.getLength().ToString());
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

            _style = s_point.getStyleUrl();
            s_point.setStyleUrl("");
            f_point.setStyleUrl("");
             p_highlight = name;
        }

        public void de_highlight()
        {
            if (p_highlight != "")
            {
                IKmlPlacemark p_s_point = getStart(getByName( p_highlight));
                IKmlPlacemark p_f_point = getFinish(getByName( p_highlight));
                p_s_point.setStyleUrl(_style);
                p_f_point.setStyleUrl(_style);
                p_highlight = "";
            }
        }

        public ArrayList getAttrs()
        {
            return _attr;
        }
    }
}
