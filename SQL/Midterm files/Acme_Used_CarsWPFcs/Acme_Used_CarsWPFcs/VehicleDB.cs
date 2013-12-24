using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.SqlClient;
using System.Windows;

namespace Acme_Used_CarsWPFcs
{
    public static class VehicleDB
    {
        public static List<Vehicle> GetVehicles()
        {
            SqlConnection con = Acme_Used_CarsDB.GetConnection();
            List<Vehicle> vehList = new List<Vehicle>();
            SqlCommand command = new SqlCommand();
            command.CommandText = "select * from Vehicle";
            command.CommandType = CommandType.Text;
            command.Connection = con;
            try
            {
                con.Open();
                SqlDataReader reader = command.ExecuteReader();
                while (reader.Read())
                {
                    Vehicle v = new Vehicle();
                    v.InventoryID = Convert.ToInt32(reader[0]);
                    v.Manufacturer = reader[1].ToString();
                    v.ModelName = reader[2].ToString();
                    v.Year = Convert.ToInt32(reader[3]);
                    v.VehicleID = reader[4].ToString();
                    v.CostValue = Convert.ToDecimal(reader[5]);
                    vehList.Add(v);
                }
                reader.Close();
            }
            catch (SqlException err)
            {
                MessageBox.Show(err.Message, "Database Error");
            }
            finally
            {
                con.Close();
            }
            return vehList;
        }

        public static bool InsertVehicle(Vehicle vehicle)
        {
            int rows = 0;
            SqlConnection con = Acme_Used_CarsDB.GetConnection();
            SqlCommand command = new SqlCommand();
            command.CommandText = "insert into Vehicle values (@inventoryid,@manufacturer,@ModelName,@year,@vehicleid,@costvalue)";
            command.CommandType = CommandType.Text;
            command.Connection = con;
            command.Parameters.AddWithValue("@inventoryid", vehicle.InventoryID);
            command.Parameters.AddWithValue("@manufacturer", vehicle.Manufacturer);
            command.Parameters.AddWithValue("@ModelName", vehicle.ModelName);
            command.Parameters.AddWithValue("@year", vehicle.Year);
            command.Parameters.AddWithValue("@vehicleid", vehicle.VehicleID);
            command.Parameters.AddWithValue("@costvalue", vehicle.CostValue);
            try
            {
                con.Open();
                rows = command.ExecuteNonQuery();
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
