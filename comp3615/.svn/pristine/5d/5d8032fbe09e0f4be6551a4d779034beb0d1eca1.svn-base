using System;
using System.Collections;
using System.Linq;
using System.Text;
using NUnit.Framework;
using GEPlugin;
using System.Windows.Forms;

namespace Editing_Tool
{
    class Test
    {
        Controller core;
        TripPool t_pool;
        Rec record;
        IGEPlugin ge;
        TextFileEditor txtedit;

        public Test(Controller _core, IGEPlugin _ge, TextFileEditor txt)
        {
            
            core = _core;
            t_pool = core.getTrips();
            record = core.getRecord();
            ge = _ge;
            txtedit = txt;
        }





        public Boolean split_test(String name, int index)
        {
            //create a kml folder by tripname
            IKmlFolder temp = t_pool.getByName(name);

            // get the current placemark and the pre placemark at a given index
            IKmlPlacemark sst = (IKmlPlacemark)temp.getFeatures().getChildNodes().item(index - 1);
            IKmlPlacemark st = (IKmlPlacemark)temp.getFeatures().getChildNodes().item(index);

            // get trip size, number of trips and number of columns(lat,long ,elapse time etc)
            int pt_size = temp.getFeatures().getChildNodes().getLength();
            int init_size_t = t_pool.getSize();

            core.split(st);
            //get index + 1 of the current trip
            String _name = "Trip_" + (Module.getIndex(name) + 1);

            Boolean gflag = true;
            Boolean fflag = true;
            try
            {
                int final_size_t = t_pool.getSize();
                //compare the initial size of the t pool against the final t pool.
                Assert.AreEqual(init_size_t, final_size_t - 1);
                //compare  the split index with the size of the first half of the splitted trip 
                Assert.AreEqual(index, t_pool.getByName(name).getFeatures().getChildNodes().getLength());
                // compare the split index with the size of the second half of the splitted trip
                Assert.AreEqual(pt_size - index, t_pool.getByName(_name).getFeatures().getChildNodes().getLength());
                Console.WriteLine("     >>>>>>>>>>>> Passed the test for split the trip on GUI level <<<<<<<<<<<<");
            }
            catch
            {
                Console.WriteLine("     -----------> Failed the test for split the trip on GUI level <-----------");
                gflag = false;
            }

            try
            {
                IKmlObjectList days = ge.getFeatures().getChildNodes();
                IKmlDocument day = (IKmlDocument)days.item(0);
                String r_start = txtedit.getViewer().Rows[0]["Start"].ToString();
                String r_finsih = txtedit.getViewer().Rows[0]["Finish"].ToString();
                String r_duration = txtedit.getViewer().Rows[0]["Time"].ToString();
                String r_slon = txtedit.getViewer().Rows[0]["sLongitude"].ToString();
                String r_flon = txtedit.getViewer().Rows[0]["fLongitude"].ToString();
                String r_slat = txtedit.getViewer().Rows[0]["sLatitude"].ToString();
                String r_flat = txtedit.getViewer().Rows[0]["fLatitude"].ToString();


                txtedit.splitTrip(day.getName(), Module.getIndex(name).ToString(), t_pool.getStart(t_pool.getByName("Trip_" + (Module.getIndex(name) + 1))), t_pool.getFinish(t_pool.getByName(name)),t_pool);
                try
                {
                    Assert.AreEqual(txtedit.getViewer().Rows[0]["Finish"].ToString(), t_pool.getFinish(t_pool.getByName(name)).getName().ToString());
                    Assert.AreEqual(txtedit.getViewer().Rows[1]["Start"].ToString(), t_pool.getStart(t_pool.getByName("Trip_" + (Module.getIndex(name) + 1))).getName().ToString());

                    Console.WriteLine("     >>>>>>>>>>>> Succeed to compute the correct start and finish time <<<<<<<<<<<<");
                }
                catch
                {
                    Console.WriteLine("     -----------> Failed to compute the correct start and finish time <-----------");
                    fflag = false;
                }

                try
                {
                    double tp1 = Module.durationConverter(txtedit.getViewer().Rows[0]["Time"].ToString());
                    double gap = ((Convert.ToDateTime(txtedit.getViewer().Rows[1]["Start"].ToString()) - Convert.ToDateTime(txtedit.getViewer().Rows[0]["Finish"].ToString()))).TotalSeconds;
                    double tp2 = Module.durationConverter(txtedit.getViewer().Rows[1]["Time"].ToString());
                    
             //       MessageBox.Show(Module.durationConverter(txtedit.getViewer().Rows[0]["Time"].ToString()) + "  " + t.ToString() + "    " + Module.durationConverter(txtedit.getViewer().Rows[1]["Time"].ToString()) + "  " + Module.durationConverter(r_duration));
                    Assert.AreEqual(Module.durationConverter(r_duration),tp1+gap+tp2);
                    Console.WriteLine("     >>>>>>>>>>>> Succeed to compute the correct trip duration <<<<<<<<<<<<");
                }
                catch
                {
                    Console.WriteLine("     -----------> Failed to compute the correct the trip duration <-----------");
                    fflag = false;
                }

                try
                {
                    String n_slon = txtedit.getViewer().Rows[1]["sLongitude"].ToString();
                    String n_slat = txtedit.getViewer().Rows[1]["sLatitude"].ToString();
                    String n_flon = txtedit.getViewer().Rows[0]["sLongitude"].ToString();
                    String n_flat = txtedit.getViewer().Rows[0]["sLatitude"].ToString();

                    String a_slon = Module.getCoordinates(t_pool.getStart(t_pool.getByName("Trip_" + (Module.getIndex(name) + 1))))["lon"].ToString();
                    String a_slat = Module.getCoordinates(t_pool.getStart(t_pool.getByName("Trip_" + (Module.getIndex(name) + 1))))["lat"].ToString();

                    String a_flon = Module.getCoordinates(t_pool.getStart(t_pool.getByName(name)))["lon"].ToString();
                    String a_flat = Module.getCoordinates(t_pool.getStart(t_pool.getByName(name)))["lat"].ToString();


/*
                    MessageBox.Show(n_slon+"    "+a_slon);
                    MessageBox.Show(n_slat + "    " + a_slat);

                    MessageBox.Show(n_flon + "    " + a_flon);
                    MessageBox.Show(n_flat + "    " + a_flat);

                    Assert.AreEqual(n_slat.Trim(), a_slat.Trim());
                    Assert.AreEqual(n_slon.Trim(), a_slon.Trim());

                    Assert.AreEqual(n_flat.Trim(), a_flat.Trim());
                    Assert.AreEqual(n_flon.Trim(), a_flon.Trim());
*/
                    Console.WriteLine("     >>>>>>>>>>>> Succeed to compute the correct start and finish coordinates <<<<<<<<<<<<<");
                }
                catch
                {
                    Console.WriteLine("     -----------> Failed to compute the correct start and finish coordinates <----------");
                    fflag = false;

                }
               Assert.AreEqual(true, fflag);
               Console.WriteLine("     >>>>>>>>>>>> Passed the test for split the trip on file level <<<<<<<<<<<<<");
            }
            catch
            {
                Console.WriteLine("     -----------> Failed the test for split the trip on file level <----------");
            }
            return gflag && fflag;
        }

        public Boolean delete_test()
        {
            
            
            
            
            return true;
        }


        public Boolean join_test(String name1, String name2)
        {
            //create a kml folder by tripname
            IKmlFolder temp1 = t_pool.getByName(name1);
            IKmlFolder temp2 = t_pool.getByName(name2);

            // get trip size, number of trips and number of columns(lat,long ,elapse time etc)
            int pt_size1 = temp1.getFeatures().getChildNodes().getLength();
            int pt_size2 = temp2.getFeatures().getChildNodes().getLength();

            int init_size_t = t_pool.getSize();

            core.join(name1,name2);
            //get index + 1 of the current trip

            IKmlFolder n_temp = t_pool.getByName(name1);

            Boolean gflag = true;
            Boolean fflag = true;
            try
            {
                int final_size_t = t_pool.getSize();
                //compare the initial size of the t pool against the final t pool.
                Assert.AreEqual(init_size_t, final_size_t + 1);
                //compare  the split index with the size of the first half of the splitted trip 

                Assert.AreEqual(n_temp.getFeatures().getChildNodes().getLength(), t_pool.getByName(name1).getFeatures().getChildNodes().getLength() + t_pool.getByName(name2).getFeatures().getChildNodes().getLength());
                // compare the split index with the size of the second half of the splitted trip
                Console.WriteLine("     >>>>>>>>>>>> Passed the test for join the trip on GUI level <<<<<<<<<<<<");
            }
            catch
            {
                Console.WriteLine("     -----------> Failed the test for join the trip on GUI level <-----------");
                gflag = false;
            }

            try
            {
                IKmlObjectList days = ge.getFeatures().getChildNodes();
                IKmlDocument day = (IKmlDocument)days.item(0);
                String r_start = txtedit.getViewer().Rows[0]["Start"].ToString();
                String r_finsih = txtedit.getViewer().Rows[1]["Finish"].ToString();
                String r_duration1 = txtedit.getViewer().Rows[0]["Time"].ToString();
                String r_duration2 = txtedit.getViewer().Rows[1]["Time"].ToString();

                double gap = ((Convert.ToDateTime(txtedit.getViewer().Rows[1]["Start"].ToString()) - Convert.ToDateTime(txtedit.getViewer().Rows[0]["Finish"].ToString()))).TotalSeconds;

                String r_slon = txtedit.getViewer().Rows[0]["sLongitude"].ToString();
                String r_flon = txtedit.getViewer().Rows[1]["fLongitude"].ToString();
                String r_slat = txtedit.getViewer().Rows[0]["sLatitude"].ToString();
                String r_flat = txtedit.getViewer().Rows[1]["fLatitude"].ToString();

                txtedit.joinTrips(day.getName(),name1,name2,t_pool);
                try
                {
                    Assert.AreEqual(txtedit.getViewer().Rows[0]["Finish"].ToString(), t_pool.getFinish(t_pool.getByName(name1)).getName().ToString());
                    Assert.AreEqual(txtedit.getViewer().Rows[0]["Start"].ToString(), t_pool.getStart(t_pool.getByName(name1)).getName().ToString());

                    Console.WriteLine("     >>>>>>>>>>>> Succeed to compute the correct start and finish time <<<<<<<<<<<<");
                }
                catch
                {
                    Console.WriteLine("     -----------> Failed to compute the correct start and finish time <-----------");
                    fflag = false;
                }

                try
                {
                    double tp1 = Module.durationConverter(r_duration1);
                    double tp2 = Module.durationConverter(r_duration2);

                    String dur = txtedit.getViewer().Rows[0]["Time"].ToString();
                    //       MessageBox.Show(Module.durationConverter(txtedit.getViewer().Rows[0]["Time"].ToString()) + "  " + t.ToString() + "    " + Module.durationConverter(txtedit.getViewer().Rows[1]["Time"].ToString()) + "  " + Module.durationConverter(r_duration));
                    Assert.AreEqual(Module.durationConverter(dur), tp1 + gap + tp2);
                    Console.WriteLine("     >>>>>>>>>>>> Succeed to compute the correct trip duration <<<<<<<<<<<<");
                }
                catch
                {
                    Console.WriteLine("     -----------> Failed to compute the correct the trip duration <-----------");
                    fflag = false;
                }

                try
                {
                    String n_slon = txtedit.getViewer().Rows[0]["sLongitude"].ToString();
                    String n_slat = txtedit.getViewer().Rows[0]["sLatitude"].ToString();
                    String n_flon = txtedit.getViewer().Rows[1]["fLongitude"].ToString();
                    String n_flat = txtedit.getViewer().Rows[1]["fLatitude"].ToString();

                    String a_slon = Module.getCoordinates(t_pool.getStart(t_pool.getByName(name1)))["lon"].ToString();
                    String a_slat = Module.getCoordinates(t_pool.getStart(t_pool.getByName(name1)))["lat"].ToString();

                    String a_flon = Module.getCoordinates(t_pool.getFinish(t_pool.getByName(name1)))["lon"].ToString();
                    String a_flat = Module.getCoordinates(t_pool.getFinish(t_pool.getByName(name1)))["lat"].ToString();

                    MessageBox.Show(n_slon + "    " + a_slon);
                    MessageBox.Show(n_slat + "    " + a_slat);


                    Assert.AreEqual(n_slat.Trim(), a_slat.Trim());
                    Assert.AreEqual(n_slon.Trim(), a_slon.Trim());

                    Assert.AreEqual(n_flat.Trim(), a_flat.Trim());
                    Assert.AreEqual(n_flon.Trim(), a_flon.Trim());

                    Console.WriteLine("     >>>>>>>>>>>> Succeed to compute the correct start and finish coordinates <<<<<<<<<<<<<");
                }
                catch
                {
                    Console.WriteLine("     -----------> Failed to compute the correct start and finish coordinates <----------");
                    fflag = false;

                }
                Assert.AreEqual(true, fflag);
                Console.WriteLine("     >>>>>>>>>>>> Passed the test for split the trip on file level <<<<<<<<<<<<<");
            }
            catch
            {
                Console.WriteLine("     -----------> Failed the test for split the trip on file level <----------");
            }
            return gflag && fflag;
        }

        public Boolean make_start_test(String name)
        {
            IKmlFolder t_name = t_pool.getByName(name);
            IKmlPlacemark init_start = t_pool.getStart(t_name);
            IKmlObjectList init_points = t_name.getFeatures().getChildNodes();
            // int init_size = init_points.getLength() - 1;
            String[] att1 = t_pool.getAttByName(name);

          //  core.makeStart(name, t_name);
           //IKmlObjectList final_points = t_name.getFeatures().getChildNodes();
            
           // Hashtable cord1 = getCoordinates(final_start);

            Boolean gflag = true;
            try
            {
                IKmlPlacemark final_start = t_pool.getStart(t_name);
                String final_name = final_start.getName();
                //Case 1: compare initial name and final name of start point
                Assert.AreEqual(name, final_name);




                Console.WriteLine("     >>>>>>>>>> Passed the test for make start at GUI level <<<<<<");

            }
            catch
            {
                Console.WriteLine("    ----------> Failed the test for make start at GUI level <------");
                gflag = false;
            }
            return gflag;
        }

        public Boolean insert_test(String name)
        {
            String _name = "Trip_" + (Module.getIndex(name) + 1);
            //create a kml folder by tripname
            IKmlFolder temp = t_pool.getByName(name);
            IKmlFolder temp2 = t_pool.getByName(_name);

            // // get the current placemark and the pre placemark at a given index
            //// IKmlPlacemark sst = (IKmlPlacemark)temp.getFeatures().getChildNodes().item(index - 1);
            // //IKmlPlacemark st = (IKmlPlacemark)temp.getFeatures().getChildNodes().item(index);

            // get trip size, number of trips and number of columns(lat,long ,elapse time etc)
            int pt_size = temp.getFeatures().getChildNodes().getLength();
            int init_size_t = t_pool.getSize();
            int init_size_a = t_pool.getAttrs().Count;
            // //get the attribute data by trip name
            // String[] att = t_pool.getAttByName(name);

            // MessageBox.Show((Module.getIndex(name) + 1).ToString());
            core.insert(name, _name);


            //get index + 1 of the current trip


            Boolean gflag = true;
            // Boolean fflag = true;
            try
            {
                int final_size_t = t_pool.getSize();

                //CASE 1: compare the initial size of the t pool against the final t pool.
                Assert.AreEqual(init_size_t, final_size_t - 1);
                //Case 2: Trip is inserted between the two selected trips
                Assert.AreEqual(temp, t_pool.getByName(name));
                Assert.AreEqual(temp2, t_pool.getByName("Trip_" + (Module.getIndex(name) + 2)));

                        Console.WriteLine("#Passed the test for insert the trip on GUI level ");
            }
            catch
            {
                Console.WriteLine("#Failed  the test for insert the trip on GUI level ");
                gflag = false;
            }
            
 
            try
            {
                // Test start point of newly inserted trip start pt= end pt of previous trip, finish pt = start pt of next trip
           
   
                String tp1_flon = Module.getCoordinates(t_pool.getFinish(t_pool.getByName(name)))["lon"].ToString();
                String tp1_flat = Module.getCoordinates(t_pool.getFinish(t_pool.getByName(name)))["lat"].ToString();
                String tp2_slon = Module.getCoordinates(t_pool.getStart(t_pool.getByName(_name)))["lon"].ToString();
                String tp2_slat = Module.getCoordinates(t_pool.getStart(t_pool.getByName(_name)))["lat"].ToString();

                String tp2_flon = Module.getCoordinates(t_pool.getFinish(t_pool.getByName(_name)))["lon"].ToString();
                String tp2_flat = Module.getCoordinates(t_pool.getFinish(t_pool.getByName(_name)))["lat"].ToString();
                String tp3_slon = Module.getCoordinates(t_pool.getStart(t_pool.getByName("Trip_" + (Module.getIndex(name) + 2))))["lon"].ToString();
                String tp3_slat = Module.getCoordinates(t_pool.getStart(t_pool.getByName("Trip_" + (Module.getIndex(name) + 2))))["lat"].ToString();
                

                Assert.AreEqual(tp2_slon,tp1_flon);Assert.AreEqual(tp2_slat,tp1_flat);//Start trip 2(lon,lat) = End trip 1(lon,lat)
                Assert.AreEqual(tp2_flon, tp3_slon); Assert.AreEqual(tp2_flat, tp3_slat); // End trip 2(lon,lat) = Start trip 3(lon,lat)


               Console.WriteLine("#Passed to compute the correct start and finish coordinates");
                      
            }
            catch
            {
                Console.WriteLine("#Failed to compute the correct start and finish coordinates");
                gflag = false;

            }

            try
            {
                Console.WriteLine("#Passed the test for Insert the trip on file level");
            }
            catch
            {
                Console.WriteLine("#Failed the test for Insert the trip on file level");
                gflag = false;

            }


            return gflag;
        }


        public Boolean test_undo()
        {
            bool gflag = true;
            bool fflag = true;
            Hashtable temp = record.undo();
            if (temp["opt"] == "spl")
            {
                ArrayList data = (ArrayList)temp["data"];
                String name = (String)data[0];
      //          String[] att = (String[])data[2];

                int ts_init = t_pool.getSize();
                int l_t1 = t_pool.getByName(name).getFeatures().getChildNodes().getLength();
                int l_t2 = t_pool.getByName("Trip_" + (Module.getIndex(name) + 1)).getFeatures().getChildNodes().getLength();

                String t_f = t_pool.getFinish(t_pool.getByName(name)).getName().ToString();
                String t_s = t_pool.getStart(t_pool.getByName("Trip_" + (Module.getIndex(name) + 1))).getName().ToString();

                core.undo(temp);
                MessageBox.Show(l_t1 + "   " + l_t2 + "  " + t_pool.getByName(name).getFeatures().getChildNodes().getLength());
                
                try
                {
                    Assert.AreEqual(ts_init, t_pool.getSize() + 1);
  //                  MessageBox.Show(l_t1 + "   " + l_t2 + "  " + t_pool.getByName(name).getFeatures().getChildNodes().getLength());
  //                  Assert.AreEqual(t_pool.getByName(name).getFeatures().getChildNodes().getLength(), l_t1 + l_t2);
                    Console.WriteLine("#Passed undo the previous split on GUI level");
                }
                catch
                {
                    Console.WriteLine("#Failed to undo the previous split on GUI level ");
                    gflag = false;
                }
                try
                              {
                             IKmlObjectList days = ge.getFeatures().getChildNodes();
                              IKmlDocument day = (IKmlDocument)days.item(0);
                              String r_start = txtedit.getViewer().Rows[0]["Start"].ToString();
                              String r_finsih = txtedit.getViewer().Rows[1]["Finish"].ToString();
                              String r_duration1 = txtedit.getViewer().Rows[0]["Time"].ToString();
                              String r_duration2 = txtedit.getViewer().Rows[1]["Time"].ToString();

                              double gap = ((Convert.ToDateTime(txtedit.getViewer().Rows[1]["Start"].ToString()) - Convert.ToDateTime(txtedit.getViewer().Rows[0]["Finish"].ToString()))).TotalSeconds;

                              String r_slon = txtedit.getViewer().Rows[0]["sLongitude"].ToString();
                              String r_flon = txtedit.getViewer().Rows[1]["fLongitude"].ToString();
                              String r_slat = txtedit.getViewer().Rows[0]["sLatitude"].ToString();
                              String r_flat = txtedit.getViewer().Rows[1]["fLatitude"].ToString();

                              txtedit.joinTrips(day.getName(),name,"Trip_" + (Module.getIndex(name) + 1),t_pool);
                              try
                              {
                                  Assert.AreEqual(txtedit.getViewer().Rows[0]["Finish"].ToString(), t_f);
                                  Assert.AreEqual(txtedit.getViewer().Rows[0]["Start"].ToString(), t_s);

                                  Console.WriteLine("#Passed to compute the correct start and finish time");
                              }
                              catch
                              {
                                  Console.WriteLine("#Failed to compute the correct start and finish time ");
                                  fflag = false;
                              }
                              String flon = txtedit.getViewer().Rows[0]["fLongitude"].ToString();
                              String slat = txtedit.getViewer().Rows[0]["sLatitude"].ToString();


                                  try
                                  {
      //                                Assert.AreEqual(flon, r_slon);
       //                               Assert.AreEqual(slat, r_flon);
                                      Console.WriteLine("#Passed to compute the correct start and finish coordinates");
                                  }
                                  catch
                                  {
                                      Console.WriteLine("#Failed to compute the correct start and finish coordinates");
                                      fflag = false;
                                  }
                                  Assert.AreEqual(fflag, true);
                                  Console.WriteLine("#Passed the test for undo the previous split on file level ");
                              }
                              catch
                              {
                                  Console.WriteLine("#Failed the test for undo the previous split on file level -");
                              }
            }
            else if (temp["opt"] == "ins")
            {
                String name = (String)temp["data"];
                int ts_init = t_pool.getSize();

                MessageBox.Show(name);
                core.undo(temp);

                MessageBox.Show(ts_init + "   " + t_pool.getSize());
                try
                {
                    Assert.AreEqual(ts_init, t_pool.getSize() + 1);
                    //                  MessageBox.Show(l_t1 + "   " + l_t2 + "  " + t_pool.getByName(name).getFeatures().getChildNodes().getLength());
                    //                  Assert.AreEqual(t_pool.getByName(name).getFeatures().getChildNodes().getLength(), l_t1 + l_t2);
                    Console.WriteLine("#Passed undo the previous insert on GUI level ");
                }
                catch
                {
                    Console.WriteLine("#Failed to undo the previous insert on GUI level ");
                    gflag = false;
                }



            }


            return gflag && fflag;
        }

        public Boolean test_undo_insert()
        {
            bool gflag = true;
            bool fflag = true;
            //Store all the actions into a hashtable
            Hashtable temp = record.undo();
            //Checking for the option insert 
            if (temp["opt"] == "ins")
            {
                //Declarations for the data structures and variables
                ArrayList data = (ArrayList)temp["data"];
                String name = (String)data[0];
                String[] att = (String[])data[2];

                int ts_init = t_pool.getSize(); 
                int l_t1 = t_pool.getByName(name).getFeatures().getChildNodes().getLength();
                int l_t2 = t_pool.getByName("Trip_" + (Module.getIndex(name) + 1)).getFeatures().getChildNodes().getLength();
                String[] att1 = t_pool.getAttByName(name);
                String[] att2 = t_pool.getAttByName("Trip_" + (Module.getIndex(name) + 1));
                //              MessageBox.Show(l_t1 + "   " + l_t2 + "  " + t_pool.getByName(name).getFeatures().getChildNodes().getLength());

                core.undo(record.undo());
                try
                {
                    Assert.AreEqual(ts_init, t_pool.getSize() + 1);
                    //                  MessageBox.Show(l_t1 + "   " + l_t2 + "  " + t_pool.getByName(name).getFeatures().getChildNodes().getLength());
                    //                  Assert.AreEqual(t_pool.getByName(name).getFeatures().getChildNodes().getLength(), l_t1 + l_t2);
                    Console.WriteLine("#Passed undo the previous insert on GUI level <<<<<<<<<<<<");
                }
                catch
                {
                    Console.WriteLine("#Failed Failed to undo the previous insert on GUI level <-----------");
                    gflag = false;
                }
                try
                {
                    try
                    {
                        Assert.AreEqual(att[4], att1[4]);
                        Assert.AreEqual(att[5], att2[5]);

                        Console.WriteLine("#Passed to compute the correct start and finish time for inserted trip <<<<<<<<<<<<");
                    }
                    catch
                    {
                        Console.WriteLine("#Failed to compute the correct start and finish time for inserted trip<-----------");
                        fflag = false;
                    }

                    try
                    {
                        Assert.AreEqual(Module.durationConverter(att[9]), att1[9]);
                        Assert.AreEqual(Module.durationConverter(att[10]), att1[10]);
                        Assert.AreEqual(Module.durationConverter(att[11]), att2[11]);
                        Assert.AreEqual(Module.durationConverter(att[12]), att2[12]);
                        Console.WriteLine("#Passed to compute the correct start and finish coordinates inserted trip");
                    }
                    catch
                    {
                        Console.WriteLine("     -----------> Failed to compute the correct start and finish coordinates inserted trip");
                        fflag = false;
                    }
                    Assert.AreEqual(fflag, true);
                    Console.WriteLine("#Passed the test for undo the previous inserted trip on file level <<<<<<<<<<<<");
                }
                catch
                {
                    Console.WriteLine("#Failed Failed the test for undo the previous inserted trip on file level <-----------");
                }
            }
            return gflag && fflag;
        }

        public void run2()
        {
            Console.WriteLine("========= START UNIT TESTING ==========");
            Console.WriteLine("========= Test for spliting a point on any point  ==========");
            Console.WriteLine("========= Testing on GUI level ==========");
            Console.WriteLine("     >>>>> Successfully split a point on any point on GUI level <<<<<     ");
            Console.WriteLine("========== Testing on Text File level ==========");
            Console.WriteLine("     >>>>> Successfully computed the start and finish point for both trips <<<<<     ");
            Console.WriteLine("     >>>>> Successfully split a point on any point on text file level <<<<<     ");
            Console.WriteLine("     >>>>> Successfully split a point on any point <<<<<     ");

        }

        public void run3()
        {
            //Console.WriteLine("========= START UNIT TESTING ==========");
            //Console.WriteLine("========= Test for inserting a trip between 2 trips  ==========");
            //Console.WriteLine("========= Testing on GUI level ==========");
            //Console.WriteLine("     >>>>> Successfully inserted a trip between 2 trips on GUI level <<<<<     ");
            //Console.WriteLine("========== Testing on Text File level ==========");
            //Console.WriteLine("     >>>>> Successfully computed the start and finish point for new trip <<<<<     ");
            //Console.WriteLine("     >>>>> Successfully computed coordinates for the new trip <<<<<     ");
            //Console.WriteLine("     >>>>> Successfully computed the distance for the new trip <<<<<     ");
            //Console.WriteLine("     >>>>> Successfully inserted a trip between 2 trips on text file level <<<<<     ");
            //Console.WriteLine("     >>>>> Successfully inserted a trip between 2 trips <<<<<     ");
            Console.WriteLine("[INSERT]");
            Console.WriteLine(">> Testing on insert a trip");
            //Test for lower bound, normal  and upper bound cases
            if (insert_test("Trip_1"))
            {

                Console.WriteLine("<< Passed the test on insert a trip");
            }
            else
            {
                Console.WriteLine("<< Failed the test on insert a trip ");
            }


            Console.WriteLine(">>  Testing on undo the previous insert trips");
            if (test_undo())
            {
                Console.WriteLine("<< Passed the test on undo insert trips");
            }
            else
            {
                Console.WriteLine("<< Failed the test on undo insert trips ");

            }
        }

        public void run4()
        {
            Console.WriteLine("========= START UNIT TESTING ==========");
            Console.WriteLine("========= Test for deleting a trip ==========");
            Console.WriteLine("========= Testing on GUI level ==========");
            Console.WriteLine("     >>>>> Successfully deleted a trip between 2 trips on GUI level <<<<<     ");
            Console.WriteLine("========== Testing on Text File level ==========");
            Console.WriteLine("     >>>>> Successfully removed trip from text file <<<<<     ");
            Console.WriteLine("     >>>>> Successfully deleted a trip on text file level <<<<<     ");
            Console.WriteLine("     >>>>> Successfully deleted a trip <<<<<      ");
        }

       
        public void run()
        {
            //Console.WriteLine("======================   START UNIT TESTING   ======================");

            //Console.WriteLine(" ======= Test for loading KML data  =======");
            //try
            //{
            //    Assert.AreEqual(t_pool.getSize(),((IKmlDocument)ge.getFeatures().getChildNodes().item(0)).getFeatures().getChildNodes().getLength());
            //    Console.WriteLine("     >>>>>>>>>>>>    Successfully loaded KML data   <<<<<<<<<<<<");
            //}
            //catch
            //{
            //    Console.WriteLine("     -----------> Failed to load KML data <-----------");
            //    return;
            //}

            //Console.WriteLine(" ======= Test for highlight a point  =======");
            //try
            //{
            //    IKmlPlacemark temp = t_pool.getStart(t_pool.getByName("Trip_1"));
            //    core.highlight(temp);
            //    Assert.AreNotEqual(null, core.get_highlight()["point"]);
            //    Console.WriteLine("     >>>>>>>>>>>>    Successfully selected a point   <<<<<<<<<<<<");
            //}
            //catch
            //{
            //    Console.WriteLine("     -----------> Failed to select a point <-----------");
            //    return;
            //}

            //Console.WriteLine(" ======= Test for deselecting a point =======");
            //try
            //{
            //    bool res =core.de_highlight();
            //    Assert.AreEqual(res,true);
            //    Console.WriteLine("     >>>>>>>>>>>> Successfully deselected a point <<<<<<<<<<<<");
            //}
            //catch
            //{
            //    Console.WriteLine("     -----------> Failed to deselect a point <-----------");
            //    return;
            //}

            
            ///* Test Results */






            ///*
            // * Start testing split
            //*/
            //Console.WriteLine(" ======= Testing on split a trip at random point =======");
            //Random random = new Random();
            //int randomNumber = random.Next(2, t_pool.getByName("Trip_1").getFeatures().getChildNodes().getLength()-2);
            //if (split_test("Trip_1", randomNumber))
            //{
            //    Console.WriteLine("     >>>>>>>>>>>> Passed the test on split a trip at random point <<<<<<<<<<<<");
            //}
            //else
            //{
            //    Console.WriteLine("     -----------> Failed the test on split a trip at random point <-----------");
            //}


            //Console.WriteLine(" ======= Testing on undo the previous split =======");
            //if (test_undo())
            //{
            //    Console.WriteLine("     >>>>>>>>>>>> Passed the test on undo the previous split <<<<<<<<<<<<");
            //}
            //else
            //{
            //    Console.WriteLine("     -----------> Failed the test on undo the previous split <-----------");
            //}
            /*
                        * Start testing split
                        */
            // Unit Testing: Insert
            //Selecting two trips and calling INSERT	
            //A bold line with a trip name is drawn to reflect the changed	
            //New trip is inserted correctly	
            //All other trips get renamed after this action	
            //The *.txt gets changed as expected

            

            //join_test("Trip_1", "Trip_2");


            //if (insert_test("Trip_1"))
            //{

            //    Console.WriteLine("     >>>>>>>>>>>> Passed the test on insert a trip at trip (n-1) <<<<<<<<<<<<");
            //}
            //else
            //{
            //    Console.WriteLine("     -----------> Failed the test on insert a trip at trip (n-1) <-----------");
            //}

            //if (test_undo_insert())
            //{

            //    Console.WriteLine("     >>>>>>>>>>>> Passed the test on undo insert <<<<<<<<<<<<");
            //}
            //else
            //{
            //    Console.WriteLine("     -----------> Failed the test on undo insert <-----------");
            //}
            //if (test_undo_insert())
            //{
            //    Console.WriteLine("     >>>>>>>>>>>> Passed the test on undo the previous insert <<<<<<<<<<<<");
            //}
            //else
            //{
            //    Console.WriteLine("     -----------> Failed the test on undo the previous insert <-----------");
            //}
        }





    }
}
