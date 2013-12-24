using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;

namespace Acme_Used_CarsWPFcs
{
    public static class Acme_Used_CarsDB
    {
        public static SqlConnection GetConnection()
        {
            SqlConnection connection = new SqlConnection();
            connection.ConnectionString = "Data Source=localhost\\sqlexp2012;Initial Catalog='Acme Used Cars';Integrated Security=SSPI";
            return connection;
        }
    }
}
