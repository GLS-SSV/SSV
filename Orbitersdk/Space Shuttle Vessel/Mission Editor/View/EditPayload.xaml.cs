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

using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;


namespace SSVMissionEditor
{
	/// <summary>
	/// Interaction logic for EditPayload.xaml
	/// </summary>
	public partial class EditPayload : Window
	{
		public EditPayload( object datacontext, string bindvesselclass, string bindname, string bindattachid, string bindscnparams )
		{
			InitializeComponent();

			DataContext = datacontext;

			txtVesselClass.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindvesselclass ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			txtName.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindname ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			txtAttachID.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindattachid ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			txtScnParams.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindscnparams ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
		}

		private void btnPickVesselClass_Click(object sender, RoutedEventArgs e)
		{
			string str = GetVesselClass();

			if (str != null)
				txtVesselClass.Text = str;
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
	}
}
