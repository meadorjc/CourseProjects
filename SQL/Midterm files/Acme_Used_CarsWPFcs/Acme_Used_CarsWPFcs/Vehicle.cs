using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Acme_Used_CarsWPFcs
{
    public class Vehicle
    {
        private int cinventoryid;
        private string cmanufacturer;
        private string cmodelname;
        private int cyear;
        private string cvehicleid;
        private decimal ccostvalue;

        public Vehicle()
        {
            cinventoryid = 0;
            cmanufacturer = "";
            cmodelname = "";
            cyear = DateTime.Today.Year;
            cvehicleid = "";
            ccostvalue = 0m;
        }

        public Vehicle(int inventoryid, string manufacturer, string modelname, int year, string vehicleid, decimal costvalue)
        {
            cinventoryid = inventoryid;
            cmanufacturer = manufacturer;
            cmodelname = modelname;
            cyear = year;
            cvehicleid = vehicleid;
            ccostvalue = costvalue;
        }

        public int InventoryID
        {
            get
            {
                return cinventoryid;
            }
            set
            {
                cinventoryid = value;
            }
        }

        public string Manufacturer
        {
            get
            {
                return cmanufacturer;
            }
            set
            {
                cmanufacturer = value;
            }
        }

        public string ModelName
        {
            get
            {
                return cmodelname;
            }
            set
            {
                cmodelname = value;
            }
        }

        public int Year
        {
            get
            {
                return cyear;
            }
            set
            {
                cyear = value;
            }
        }

        public string VehicleID
        {
            get
            {
                return cvehicleid;
            }
            set
            {
                cvehicleid = value;
            }
        }

        public decimal CostValue
        {
            get
            {
               return ccostvalue;
            }
            set
            {
                ccostvalue = value;
            }
        }
    }
}
