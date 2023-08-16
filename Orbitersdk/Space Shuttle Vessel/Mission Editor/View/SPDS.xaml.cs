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
using System.Windows.Input;

namespace SSVMissionEditor
{
	/// <summary>
	/// Interaction logic for SPDS.xaml
	/// </summary>
	public partial class SPDS : Window
	{
		public SPDS( object datacontext, string bind )
		{
			this.bind = bind;

			InitializeComponent();

			DataContext = datacontext;

			cmdEditPort1.SetBinding( Button.ContentProperty, new Binding
			{
				Source = DataContext,
				Mode = BindingMode.OneWay,
				Path = new PropertyPath( bind + ".Latches[0].PLID" ),
				Converter = new Convert_PLID_Edit_Button()
			});
			cmdEditPort2.SetBinding( Button.ContentProperty, new Binding
			{
				Source = DataContext,
				Mode = BindingMode.OneWay,
				Path = new PropertyPath( bind + ".Latches[1].PLID" ),
				Converter = new Convert_PLID_Edit_Button()
			});
			cmdEditStbd1.SetBinding( Button.ContentProperty, new Binding
			{
				Source = DataContext,
				Mode = BindingMode.OneWay,
				Path = new PropertyPath( bind + ".Latches[2].PLID" ),
				Converter = new Convert_PLID_Edit_Button()
			});
			cmdEditStbd2.SetBinding( Button.ContentProperty, new Binding
			{
				Source = DataContext,
				Mode = BindingMode.OneWay,
				Path = new PropertyPath( bind + ".Latches[3].PLID" ),
				Converter = new Convert_PLID_Edit_Button()
			});
			cmdEditKeel1.SetBinding( Button.ContentProperty, new Binding
			{
				Source = DataContext,
				Mode = BindingMode.OneWay,
				Path = new PropertyPath( bind + ".Latches[4].PLID" ),
				Converter = new Convert_PLID_Edit_Button()
			});
		}

		private void btnPayload_Click(object sender, RoutedEventArgs e)
		{
			EditPayload editpayload = new EditPayload( DataContext, bind + ".Payload.VesselClass", bind + ".Payload.Name", bind + ".Payload.AttachmentID", bind + ".Payload.ScnParams" );
			editpayload.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editpayload.ShowDialog();
			return;
		}

		private void ShowEditLatch( int latch_idx, bool pedestal, bool keel )
		{
			EditLatch editlatch = new EditLatch( DataContext, bind, latch_idx, pedestal ? 2 : 3, keel );
			editlatch.Owner = Application.Current.Windows.OfType<MainWindow>().FirstOrDefault();
			editlatch.ShowDialog();
			return;
		}

		private void CmdEditPort1_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 0, true, false );
			return;
		}

		private void CmdEditPort2_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 1, true, false );
			return;
		}

		private void CmdEditStbd1_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 2, false, false );
			return;
		}

		private void CmdEditStbd2_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 3, false, false );
			return;
		}

		private void CmdEditKeel1_Click(object sender, RoutedEventArgs e)
		{
			ShowEditLatch( 4, false, true );
			return;
		}

		private void CommandBinding_Executed( object sender, ExecutedRoutedEventArgs e )
		{
			Close();
			return;
		}

		string bind;
	}
}
