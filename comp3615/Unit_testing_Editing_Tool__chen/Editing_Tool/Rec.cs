using System;
using System.Collections;
using System.Linq;
using System.Text;
using GEPlugin;

namespace Editing_Tool
{
    class Rec
    {
        ArrayList timeline;

        public Rec()
        {
            timeline = new ArrayList();
        }

        public void ins_trip(String data)
        {
            Hashtable mem = new Hashtable();
            mem["opt"] = "ins";
            mem["data"] = data;
            timeline.Insert(0, mem);
        }

        public void spl_trip(ArrayList data)
        {
            Hashtable mem = new Hashtable();
            mem["opt"] = "spl";
            mem["data"] = data;
            timeline.Insert(0, mem);
        }

        public void del_trip(ArrayList data)
        {
            Hashtable mem = new Hashtable();
            mem["opt"] = "del";
            mem["data"] = data;
            timeline.Insert(0, mem);
        }

        public void joi_trip(ArrayList data)
        {
            Hashtable mem = new Hashtable();
            mem["opt"] = "joi";
            mem["data"] = data;
            timeline.Insert(0, mem);
        }

        public Hashtable undo()
        {
            if (timeline.Count != 0)
            {
                Hashtable temp = (Hashtable)timeline[0];
                timeline.RemoveAt(0);
                return temp;
            }
            else
            {
                return null;
            }
        }

        public Hashtable pop()
        {
            int size = timeline.Count;
            if (size != 0)
            {
                Hashtable temp = (Hashtable)timeline[size - 1];
                timeline.RemoveAt(size - 1);
                return temp;
            }
            else
            {
                return null;
            }
        }

        public ArrayList flush()
        {
            return timeline;
        }
    }
}
