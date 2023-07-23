﻿/****************************************************************************
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
	/// Interaction logic for EditPayloadAdapter.xaml
	/// </summary>
	public partial class EditPayloadAdapter : Window
	{
		public EditPayloadAdapter( object datacontext, string bindmesh, string bindoffset, string bindmass )
		{
			InitializeComponent();

			DataContext = datacontext;

			txtMesh.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindmesh ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			txtOffset.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindoffset ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});

			txtMass.SetBinding( TextBox.TextProperty, new Binding
			{
				Source = this.DataContext,
				Path = new PropertyPath( bindmass ),
				UpdateSourceTrigger = UpdateSourceTrigger.PropertyChanged
			});
		}

		private void CommandBinding_Executed( object sender, ExecutedRoutedEventArgs e )
		{
			Close();
			return;
		}
	}
}
