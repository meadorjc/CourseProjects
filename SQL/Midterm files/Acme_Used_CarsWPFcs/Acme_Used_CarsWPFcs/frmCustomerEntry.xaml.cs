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
    /// Interaction logic for frmCustomerEntry.xaml
    /// </summary>
    public partial class frmCustomerEntry : Window
    {
        public frmCustomerEntry()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            List<Vehicle> vehlist = VehicleDB.GetVehicles();
            foreach (Vehicle v in vehlist)
            {
                cboInventoryID.Items.Add(v.InventoryID);
            }
            cboInventoryID.SelectedIndex = -1;
        }

        private void btnInsert_Click(object sender, RoutedEventArgs e)
        {
            if (WPFValidator.IsPresent(txtNumber) && WPFValidator.IsPresent(txtName) && WPFValidator.IsSelected(cboInventoryID))
            {
                string number = txtNumber.Text;
                string name = txtName.Text;
                int inventoryid = Convert.ToInt32(cboInventoryID.SelectedItem);
                Customer c = new Customer(number, name, inventoryid);
                if (CustomerDB.InsertCustomer(c))
                {
                    txtMessage.Text = "The above customer was entered into the database.";
                }
                else
                {
                    txtMessage.Text = "The above customer was not entered into the database.";
                }
            }
        }

        private void btnClear_Click(object sender, RoutedEventArgs e)
        {
            txtNumber.Text = "";
            txtName.Text = "";
            txtMessage.Text = "";
            cboInventoryID.SelectedIndex = -1;
            txtNumber.Focus();
        }

        private void btnExit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
