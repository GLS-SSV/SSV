using SSVMissionEditor.model;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;


namespace SSVMissionEditor
{
	/// <summary>
	/// Interaction logic for OtherVessels.xaml
	/// </summary>
	public partial class OtherVessels : UserControl
	{
		public IEnumerable<T> FindVisualChildren<T>(DependencyObject depObj) where T : DependencyObject
		{
			if (depObj != null)
			{
				for (int i = 0; i < VisualTreeHelper.GetChildrenCount(depObj); i++)
				{
					DependencyObject child = VisualTreeHelper.GetChild(depObj, i);

					if (child != null && child is T)
						yield return (T)child;

					foreach (T childOfChild in FindVisualChildren<T>(child))
						yield return childOfChild;
				}
			}
		}

		public OtherVessels()
		{
			InitializeComponent();
		}

		private void btnNew_Click(object sender, RoutedEventArgs e)
		{
			Mission_Vessel tmp = new Mission_Vessel();
			tmp.Name = "New Vessel";

			ICollectionView view = (ICollectionView)CollectionViewSource.GetDefaultView( lbxOtherVesselList.ItemsSource );
			ObservableCollection<Mission_Vessel> ov = (ObservableCollection<Mission_Vessel>)view.SourceCollection;
			ov.Add( tmp );
			return;
		}

		private void btnDelete_Click(object sender, RoutedEventArgs e)
		{
			ICollectionView view = (ICollectionView)CollectionViewSource.GetDefaultView( lbxOtherVesselList.ItemsSource );
			ObservableCollection<Mission_Vessel> ov = (ObservableCollection<Mission_Vessel>)view.SourceCollection;
			ov.RemoveAt( lbxOtherVesselList.SelectedIndex );
			return;
		}

		private void btnPickVesselClass_Click(object sender, RoutedEventArgs e)
		{
			string str = GetVesselClass();

			if (str != null)
			{
				foreach (var txtbox in FindVisualChildren<TextBox>(this))
				{
					if (txtbox.Name == "txtVesselClass")
					{
						txtbox.Text = str;
					}
				}
			}
			return;
		}

		private string GetVesselClass()
		{
			MainWindow mw = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			PickVesselClass pickvesselclass = new PickVesselClass( mw.mission.AvailableVessels );
			pickvesselclass.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			if (pickvesselclass.ShowDialog() == true) return pickvesselclass.vesselclass;
			else return null;
		}

		private void txtName_TextChanged(object sender, TextChangedEventArgs e)
		{
			lbxOtherVesselList.Items.Refresh();
		}
	}
}
