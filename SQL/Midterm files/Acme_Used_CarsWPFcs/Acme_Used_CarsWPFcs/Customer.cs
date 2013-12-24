using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Acme_Used_CarsWPFcs
{
    public class Customer
    {
        private string cnumber;
        private string cname;
        private int cinventoryid;

        public Customer()
        {
            cnumber = "";
            cname = "";
            cinventoryid = 0;
        }

        public Customer(string number, string name, int inventoryid)
        {
            cnumber = number;
            cname = name;
            cinventoryid = inventoryid;
        }

        public string number
        {
            get
            {
                return cnumber;
            }
            set
            {
                cnumber = value;
            }
        }

        public string name
        {
            get
            {
                return cname;
            }
            set
            {
                cname = value;
            }
        }

        public int inventoryid
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
    }
}
