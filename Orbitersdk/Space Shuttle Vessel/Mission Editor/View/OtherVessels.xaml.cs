/****************************************************************************
  This file is part of Space Shuttle Vessel Mission Editor
  
  Space Shuttle Vessel is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
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
