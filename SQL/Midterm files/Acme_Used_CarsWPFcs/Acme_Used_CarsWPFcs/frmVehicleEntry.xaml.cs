using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using CSClassLibrary;

namespace Acme_Used_CarsWPFcs
{
    /// <summary>
    /// Interaction logic for frmVehicleEntry.xaml
    /// </summary>
    public partial class frmVehicleEntry : Window
    {
        public frmVehicleEntry()
        {
            InitializeComponent();
        }

        private void btnInsert_Click(object sender, RoutedEventArgs e)
        {
            if (IsValidData())
            {
                int inventoryID = Convert.ToInt32(txtInventoryID.Text);
                string manufacturer = txtManufacturer.Text;
                string modelname = txtModelName.Text;
                int year = Convert.ToInt32(txtModelYear.Text);
                string vehicleid = txtVehicleID.Text;
                decimal costvalue = Convert.ToDecimal(txtCostValue.Text);
                Vehicle vehicle = new Vehicle(inventoryID, manufacturer, modelname, year, vehicleid, costvalue);
                if (VehicleDB.InsertVehicle(vehicle))
                {
                    txtMessage.Text = "The above vehicle was added to the database.";
                }
                else
                {
                    txtMessage.Text = "The above vehicle was not added to the database.";
                }
            }
        }

        private void btnClear_Click(object sender, RoutedEventArgs e)
        {
            txtCostValue.Clear();
            txtInventoryID.Clear();
            txtManufacturer.Clear();
            txtModelName.Clear();
            txtModelYear.Clear();
            txtVehicleID.Clear();
            txtMessage.Text = "";
            txtInventoryID.Focus();
        }

        private void btnExit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
        private bool IsValidData()
        {
            return WPFValidator.IsPresent(txtInventoryID) &&
                   WPFValidator.IsInteger(txtInventoryID) &&
                   WPFValidator.IsPresent(txtManufacturer) &&
                   WPFValidator.IsPresent(txtModelName) &&
                   WPFValidator.IsPresent(txtModelYear) &&
                   WPFValidator.IsInteger(txtModelYear) &&
                   WPFValidator.IsPresent(txtVehicleID) &&
                   WPFValidator.IsPresent(txtCostValue) &&
                   WPFValidator.IsDecimal(txtCostValue) &&
                   WPFValidator.IsDecimal(txtCostValue, 0m);
        }
    }
}
