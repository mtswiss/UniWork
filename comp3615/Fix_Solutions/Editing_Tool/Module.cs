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
    class Module
    {
        public static String finalText;

        public static int getIndex(String name)
        {
            return int.Parse(name.Split('_')[1]);
        }

        public static String randomCol()
        {
            char[] colors = new char[16];
            colors[0] = '0';
            colors[1] = '1';
            colors[2] = '2';
            colors[3] = '3';
            colors[4] = '4';
            colors[5] = '5';
            colors[5] = '6';
            colors[6] = '7';
            colors[7] = '8';
            colors[8] = '9';
            colors[9] = 'a';
            colors[10] = 'b';
            colors[11] = 'c';
            colors[12] = 'd';
            colors[13] = 'e';
            colors[14] = 'f';
            String color = "ff";

            Random rnd = new Random();
            for (int i = 0; i < 6; i++)
            {
                color += colors[rnd.Next(0, 14)];
            }
            return color;
        }

        public static void writeToTestingFile(String text)
        {
            finalText = finalText + text + "\r\n";
        }

        public static void writeTestingFile()
        {
            DateTime currentDateTime = DateTime.Now;
            String tempDateTime = currentDateTime.ToString("HHmmss");
            String newFilePath = Application.StartupPath.ToString() + @"\speedTest.txt";
            System.IO.StreamWriter file = new System.IO.StreamWriter(newFilePath);
            file.WriteLine(finalText);
            file.Close();
        }

        public static double averagePointsPerSecond(ArrayList pointsPerSecond)
        {
            int total = 0;
            for( int i=0; i!=pointsPerSecond.Count; ++i )
            {
                total = total + Convert.ToInt32(pointsPerSecond[i]);
            }
            double average = total / pointsPerSecond.Count;
            writeToTestingFile("Average number of points recorded per second : " + average + "\r\n");
            return average;

        }

        /*
         * get the GPS coordinate of a point
         */
        public static Hashtable getCoordinates(IKmlPlacemark point)
        {
            Hashtable cods = new Hashtable();
            String xml = point.getKml();
            String temp = System.Text.RegularExpressions.Regex.Split(xml, "<coordinates>")[1];
            String coords = System.Text.RegularExpressions.Regex.Split(temp, "</coordinates>")[0];
            Array value = System.Text.RegularExpressions.Regex.Split(coords, ",");
            cods["lon"] = double.Parse((String)value.GetValue(0));
            cods["lat"] = double.Parse((String)value.GetValue(1));
            return cods;
        }

        public static String getNewTime(String oldTime, String duration, int type)
        {
            //This is going to return the new time after deleting a time duration from the previous time
            //We'll first convert the previous time into a string array 
            String[] timeSplit = new String[3];
            timeSplit = oldTime.Split(':');
            //Now we'll convert that into seconds
            double oldTimeInSeconds = Convert.ToDouble(timeSplit[0]) * 3600 + Convert.ToDouble(timeSplit[1]) * 60 + Convert.ToDouble(timeSplit[2]);
            double durationInSeconds = Convert.ToDouble(duration);
            double newTimeInSeconds;
            if (type == 1)
               newTimeInSeconds  = oldTimeInSeconds - durationInSeconds;
            else
                newTimeInSeconds = oldTimeInSeconds + durationInSeconds;
            if (newTimeInSeconds > 86399 || newTimeInSeconds < 1)
            {
                MessageBox.Show("Point created has a time in another day. Operation could not be completed.");
                //And then we'll exit this function
                return "fail";
            }
            timeSplit[2] = (newTimeInSeconds % 60).ToString();
            timeSplit[1] = (((newTimeInSeconds - Convert.ToDouble(timeSplit[2])) % 3600)/60).ToString();
            timeSplit[0] = ((newTimeInSeconds - (newTimeInSeconds % 3600)) / 3600).ToString();
            timeSplit[2] = Math.Round(Convert.ToDouble(timeSplit[2]), 0).ToString();
            String newTime = timeSplit[0] + ":" + timeSplit[1] + ":" + timeSplit[2];
            return newTime;
        }


        /*
         *  covert the standard formatted time duration into seconds
         */
        public static double durationConverter(String input)
        {
            return Convert.ToDateTime(input).Subtract(Convert.ToDateTime("0:0:0")).TotalSeconds;
        }

        /*
         * get the trip distance from kml
         */
        public static double getDistance(IKmlPlacemark point)
        {
            String xml = point.getDescription();
            String temp = System.Text.RegularExpressions.Regex.Split(xml, "Distance</td><td>")[1];
            return double.Parse((String)temp.Split('<')[0]);
        }

        /*
         * convert the start finish time into duration
         */
        public static String duration(String st, String fn)
        {
            return Convert.ToDateTime(fn).Subtract(Convert.ToDateTime(st)).ToString();
        }


        /*
         * distance calculation using big-circle formula
         */
        public static double calDistance(IKmlFolder trip)
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
                        , (double)getCoordinates(prev)["lat" ], (double)getCoordinates(prev)["lon"]);
                    distance += d;
                }
                prev = curr;
            }
            return Math.Round(distance, 3);
        }

    }

}

   
