using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using System.Windows;

namespace Acme_Used_CarsWPFcs
{
    public static class CustomerDB
    {
        public static bool InsertCustomer(Customer customer)
        {
            int rows = 0;
            SqlConnection con = Acme_Used_CarsDB.GetConnection();
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText = "insert into Customer values (@number,@name,@inventoryid)";
            cmd.CommandType = CommandType.Text;
            cmd.Connection = con;
            cmd.Parameters.AddWithValue("@number", customer.number);
            cmd.Parameters.AddWithValue("@name", customer.name);
            cmd.Parameters.AddWithValue("@inventoryid", customer.inventoryid);
            try
            {
                con.Open();
                rows = cmd.ExecuteNonQuery();
            }
            catch (SqlException err)
            {
                MessageBox.Show(err.Message, "Database Error");
            }
            finally
            {
                con.Close();
            }
            if (rows == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}
