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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Acme_Used_CarsWPFcs
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void btnVehicleEntry_Click(object sender, RoutedEventArgs e)
        {
            frmVehicleEntry vehicleForm = new frmVehicleEntry();
            vehicleForm.Show();
        }

        private void btnCustomerEntry_Click(object sender, RoutedEventArgs e)
        {
            frmCustomerEntry customerEntry = new frmCustomerEntry();
            customerEntry.Show();
        }

        private void btnExit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}
