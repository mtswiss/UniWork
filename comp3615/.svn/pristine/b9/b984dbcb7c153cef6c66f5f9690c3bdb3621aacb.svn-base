using System;
using System.Collections;
using System.Linq;
using System.Text;
using GEPlugin;
using System.Windows.Forms;

namespace Editing_Tool
{
    class PointPool
    {
        Hashtable core;
        ArrayList names;
        String p_highlight;
        String _style;

        public PointPool(IKmlFolder trip)
        {
            core = new Hashtable();
            names = new ArrayList();
            IKmlObjectList points = trip.getFeatures().getChildNodes();
            for (int i = 0; i < points.getLength(); i++)
            {
                IKmlPlacemark pt =(IKmlPlacemark) points.item(i);
                core[pt.getName()] = pt;
                names.Add(pt.getName());
            }
            p_highlight = "";
            _style = "";
        }

        

        public void add(String name, IKmlPlacemark point)
        {
            if (!core.ContainsKey(name))
            {
                core[name] = new ArrayList();
            }
            core[name] = point;

        }

        public bool contains(String name)
        {
            return core.ContainsKey(name);
        }

        public ArrayList getNames()
        {
            return names;
        }

        public IKmlPlacemark getByName(String name)
        {
            return (IKmlPlacemark)core[name];
        }

        public void remove(String name)
        {
            core.Remove(name);
        }

        public void highlight(String name)
        {
            if (p_highlight != "")
            {
                dehighlight();
            }
            IKmlPlacemark point = getByName(name);
            point.getComputedStyle().getIconStyle().setScale((float)0.5);
            p_highlight = name;
        }

        public void dehighlight()
        {
            if (p_highlight != "")
            {
                IKmlPlacemark point = getByName(p_highlight);
                point.getComputedStyle().getIconStyle().setScale((float)0.3);
            }
        }

        public Hashtable getCoordinates(String name)
        {
            Hashtable cods = new Hashtable();
            IKmlPlacemark point = getByName(name);
            String xml = point.getKml();
            String temp = System.Text.RegularExpressions.Regex.Split(xml, "<coordinates>")[1];
            String coords = System.Text.RegularExpressions.Regex.Split(temp, "</coordinates>")[0];
            Array value = System.Text.RegularExpressions.Regex.Split(coords, ",");
            cods["lat"] = float.Parse((String)value.GetValue(1));
            cods["lon"] = float.Parse((String)value.GetValue(0));
            return cods;
        }



    }
}
