using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace Editing_Tool
{
    class GPSUtil
    {
        private double deg2rad(double deg)
        {
            return (deg * Math.PI / 180.0);
        }

        private double rad2deg(double rad)
        {
            return (rad / Math.PI * 180.0);
        }
        private double GetSpeed(double lat1, double lon1, double lat2, double lon2, DateTime CurTime, DateTime PrevTime)
        {
            //code for speed in Kilo Meter/Hour
            TimeSpan TimeDifference = CurTime.Subtract(PrevTime);
            double TimeDifferenceInSeconds = Math.Round(TimeDifference.TotalSeconds, 0);
            double theta = lon1 - lon2;
            double dist = Math.Sin(deg2rad(lat1)) * Math.Sin(deg2rad(lat2)) + Math.Cos(deg2rad(lat1)) * Math.Cos(deg2rad(lat2)) * Math.Cos(deg2rad(theta));
            dist = rad2deg(Math.Acos(dist)) * 60 * 1.1515 * 1.609344;
            double Speed = Math.Abs(Math.Round((dist / Math.Abs(TimeDifferenceInSeconds)) * 60 * 60, 0));
            return (Speed);
        }

        private double GetDuration(DateTime CurTime, DateTime PrevTime)
        {
            //code for speed in Kilo Meter/Hour
            TimeSpan TimeDifference = CurTime.Subtract(PrevTime);
            double TimeDifferenceInSeconds = Math.Abs(Math.Round(TimeDifference.TotalSeconds, 0));
            return (TimeDifferenceInSeconds);
        }
    }
}
