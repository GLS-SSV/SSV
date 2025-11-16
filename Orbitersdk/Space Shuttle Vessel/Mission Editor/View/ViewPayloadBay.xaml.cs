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

using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using SSVMissionEditor.ViewModel;

namespace SSVMissionEditor
{
	/// <summary>
	/// Interaction logic for ViewPayloadBay.xaml
	/// </summary>
	public partial class ViewPayloadBay : Window
	{
		public ViewPayloadBay( object datacontext )
		{
			InitializeComponent();

			DataContext = datacontext;

			DrawPayloadBay();
			return;
		}
		
		const int ystbd = 25;
		const int yport = 316;
		const int ykeel = 640;
		const int ysill = 477;
		//const int yZo400 = 500;
		const int heightpl = 10;

		private void DrawPayloadBay()
		{
			// reset
			cnvPLB.Children.Clear();

			DrawStatic();

			MainWindowViewModel vm = (MainWindowViewModel)DataContext;
			ObservableCollection<EditPayloadViewModel> pl = vm.Payload_PayloadList;
			foreach (EditPayloadViewModel x in pl)
			{
				switch (x.Type)
				{
					case EditPayloadViewModel.PL_VM_TYPE_ACTIVE:
						{
							EditActivePayloadViewModel vmapl = (EditActivePayloadViewModel)x;
							List<int> pPLID = new List<int>();
							for (int i = 0; i < 4; i++)
							{
								if (vmapl.Latches[i].PLID != 0) pPLID.Add( vmapl.Latches[i].PLID );
							}

							List<int> sPLID = new List<int>();
							for (int i = 4; i < 8; i++)
							{
								if (vmapl.Latches[i].PLID != 0) sPLID.Add( vmapl.Latches[i].PLID );
							}

							List<int> kPLID = new List<int>();
							for (int i = 8; i < 12; i++)
							{
								if (vmapl.Latches[i].PLID != 0) kPLID.Add( vmapl.Latches[i].PLID );
							}

							DrawLatchPayload( 1, vmapl.Payload.Name, vmapl.HasPayload, pPLID, sPLID, kPLID );
						}
						break;
					case EditPayloadViewModel.PL_VM_TYPE_PASSIVE:
						{
							EditPassivePayloadViewModel vmppl = (EditPassivePayloadViewModel)x;
							List<int> pPLID = new List<int>();
							for (int i = 0; i < 4; i++)
							{
								if (vmppl.Latches[i].PLID != 0) pPLID.Add( vmppl.Latches[i].PLID );
							}

							List<int> sPLID = new List<int>();
							for (int i = 4; i < 8; i++)
							{
								if (vmppl.Latches[i].PLID != 0) sPLID.Add( vmppl.Latches[i].PLID );
							}

							List<int> kPLID = new List<int>();
							for (int i = 8; i < 12; i++)
							{
								if (vmppl.Latches[i].PLID != 0) kPLID.Add( vmppl.Latches[i].PLID );
							}

							DrawLatchPayload( 2, vmppl.Payload.Name, true, pPLID, sPLID, kPLID );
						}
						break;
					case EditPayloadViewModel.PL_VM_TYPE_BAY_BRIDGE:
						{
							EditBayBridgePayloadViewModel vmbb = (EditBayBridgePayloadViewModel)x;
							DrawBayBridge( vmbb.Payload.Name, vmbb.Bay, vmbb.Bridge );
						}
						break;
					case EditPayloadViewModel.PL_VM_TYPE_IUS_2:
						{
							EditUpperStageIUSViewModel vmius = (EditUpperStageIUSViewModel)x;
							DrawIUS2( vmius.Name, vmius.Payload.Name, vmius.AftPosition, vmius.Adapter_Offset );
						}
						break;
					case EditPayloadViewModel.PL_VM_TYPE_IUS_TWIN:
						// TODO
						break;
					case EditPayloadViewModel.PL_VM_TYPE_IUS_3:
						// TODO
						break;
					case EditPayloadViewModel.PL_VM_TYPE_CG:
						{
							EditUpperStageCentaurViewModel vmcg = (EditUpperStageCentaurViewModel)x;
							DrawCentaurG( vmcg.Name, vmcg.Payload.Name, vmcg.Adapter_Offset );
						}
						break;
					case EditPayloadViewModel.PL_VM_TYPE_CGP:
						{
							EditUpperStageCentaurViewModel vmcgp = (EditUpperStageCentaurViewModel)x;
							DrawCentaurGPrime( vmcgp.Name, vmcgp.Payload.Name, vmcgp.Adapter_Offset );
						}
						break;
					case EditPayloadViewModel.PL_VM_TYPE_PAM_D:
						// TODO
						break;
					case EditPayloadViewModel.PL_VM_TYPE_PAM_D2:
						// TODO
						break;
					case EditPayloadViewModel.PL_VM_TYPE_PAM_A:
						// TODO
						break;
					case EditPayloadViewModel.PL_VM_TYPE_SPDS_PORT:
						{
							EditSPDSViewModel vmpspds = (EditSPDSViewModel)x;
							List<int> pPLID = new List<int>();
							for (int i = 0; i < 2; i++)
							{
								if (vmpspds.Latches[i].PLID != 0) pPLID.Add( vmpspds.Latches[i].PLID );
							}

							List<int> sPLID = new List<int>();
							for (int i = 2; i < 4; i++)
							{
								if (vmpspds.Latches[i].PLID != 0) sPLID.Add( vmpspds.Latches[i].PLID );
							}

							List<int> kPLID = new List<int>();
							if (vmpspds.Latches[4].PLID != 0) kPLID.Add( vmpspds.Latches[4].PLID );

							DrawLatchPayload( 3, vmpspds.Payload.Name, true, pPLID, sPLID, kPLID );
						}
						break;
					case EditPayloadViewModel.PL_VM_TYPE_SPDS_STBD:
						// TODO
						break;
					case EditPayloadViewModel.PL_VM_TYPE_PL_MPM_PORT:
						// TODO ?
						break;
					case EditPayloadViewModel.PL_VM_TYPE_PL_MPM_STBD:
						// TODO ?
						break;
				}
			}

			if (vm.Orbiter_TAA != Defs.strNone) DrawTAA( vm.Orbiter_TAA == Defs.strAft, (vm.Orbiter_Airlock == Defs.strExternal) || (vm.Orbiter_ODS) );
			if ((vm.Orbiter_Airlock == Defs.strExternal) || (vm.Orbiter_ODS)) DrawExternalAirlock( vm.Orbiter_TAA == Defs.strForward, vm.Orbiter_ODS );
			if (vm.Consumables_EDOPallet == 1) DrawEDOpallet();
			// TODO OMS Kit
			return;
		}

		private void DrawStatic()
		{
			const int gap = 1;
			const int height = 5;
			const int width = 5;
			int xpos = 20 + 50;// x offset for first PLID (edge + bulkhead offset)

			for (int plid = 154; plid <= 330; plid++)
			{
				string plidstr = plid.ToString();
				if (Defs.PLID_Xo[plid - Defs.PLID_Xo_base] > 0) plidstr += " (Xo" + Defs.PLID_Xo[plid - Defs.PLID_Xo_base] + ")";
				/*else
				{
					xpos += gap + width;
					continue;
				}*/

				// port
				Rectangle r = new Rectangle();
				r.Name = "p" + plid;
				r.ToolTip = plidstr;
				r.Stroke = Brushes.LightGray;
				r.Fill = Brushes.LightGray;
				r.Height = height;
				r.Width = width;
				cnvPLB.Children.Add( r );
				Canvas.SetTop( r, yport );
				Canvas.SetLeft( r, xpos );

				// stbd
				r = new Rectangle();
				r.Name = "s" + plid;
				r.ToolTip = plidstr;
				r.Stroke = Brushes.LightGray;
				r.Fill = Brushes.LightGray;
				r.Height = height;
				r.Width = width;
				cnvPLB.Children.Add( r );
				Canvas.SetTop( r, ystbd );
				Canvas.SetLeft( r, xpos );

				// keel
				if (plid <= 316)
				{
					r = new Rectangle();
					r.Name = "k" + plid;
					r.ToolTip = plidstr;
					r.Stroke = Brushes.LightGray;
					r.Fill = Brushes.LightGray;
					r.Height = height;
					r.Width = width;
					cnvPLB.Children.Add( r );
					Canvas.SetTop( r, ykeel );
					Canvas.SetLeft( r, xpos );
				}

				xpos += gap + width;
			}


			// top-view outline
			Line ln = new Line
			{
				X1 = 20,
				Y1 = 20,
				X2 = 1136,
				Y2 = 20,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );
			ln = new Line
			{
				X1 = 1136,
				Y1 = 20,
				X2 = 1136,
				Y2 = 325,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );
			ln = new Line
			{
				X1 = 1136,
				Y1 = 325,
				X2 = 20,
				Y2 = 325,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );
			ln = new Line
			{
				X1 = 20,
				Y1 = 325,
				X2 = 20,
				Y2 = 20,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );

			// side-view outline
			ln = new Line
			{
				X1 = 20,
				Y1 = 650,
				X2 = 1136,
				Y2 = 650,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );
			ln = new Line
			{
				X1 = 20,
				Y1 = ysill,
				X2 = 1136,
				Y2 = ysill,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );
			ln = new Line
			{
				X1 = 1136,
				Y1 = 360,
				X2 = 1136,
				Y2 = 650,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );
			ln = new Line
			{
				X1 = 20,
				Y1 = 360,
				X2 = 20,
				Y2 = 650,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );


			// draw bay boundaries
			DrawBayLine( 112 );// bay 1/2
			DrawBayLine( 202 );// bay 2/3
			DrawBayLine( 286 );// bay 3/4
			DrawBayLine( 376 );// bay 4/5
			DrawBayLine( 460 );// bay 5/6
			DrawBayLine( 554 );// bay 6/7
			DrawBayLine( 640 );// bay 7/8
			DrawBayLine( 730 );// bay 8/9
			DrawBayLine( 808 );// bay 9/10
			DrawBayLine( 886 );// bay 10/11
			DrawBayLine( 964 );// bay 11/12
			DrawBayLine( 1048 );// bay 12/13
			return;
		}


		private void DrawBayLine( int xpos )
		{
			// top-view
			Line ln = new Line
			{
				X1 = xpos,
				Y1 = ystbd + 10,
				X2 = xpos,
				Y2 = yport - 5,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );

			// side-view
			ln = new Line
			{
				X1 = xpos,
				Y1 = ysill,
				X2 = xpos,
				Y2 = ykeel - 5,
				Stroke = Brushes.DimGray,
				StrokeThickness = 1,
				SnapsToDevicePixels = true
			};
			cnvPLB.Children.Add( ln );
			return;
		}

		private void DrawLatchPayload( int type, string plname, bool installed, List<int> pPLID, List<int> sPLID, List<int> kPLID )
		{
			string name = (type == 1) ? "Active" : ((type == 2) ? "Passive" : "SPDS");
			Brush stroke = (type == 1) ? Brushes.DarkGreen : ((type == 2) ? Brushes.YellowGreen : Brushes.Teal); 
			Brush fill = (type == 1) ? (installed ? Brushes.DarkGreen : Brushes.Transparent) : ((type == 2) ? Brushes.YellowGreen : Brushes.Teal); 

			int pl_fwd = 999;
			int pl_aft = 0;
			foreach (int x in pPLID)
			{
				if (x < pl_fwd) pl_fwd = x;
				if (x > pl_aft) pl_aft = x;
				SetPLIDport( x );
			}
			foreach (int x in sPLID)
			{
				if (x < pl_fwd) pl_fwd = x;
				if (x > pl_aft) pl_aft = x;
				SetPLIDstbd( x );
			}
			foreach (int x in kPLID)
			{
				if (x < pl_fwd) pl_fwd = x;
				if (x > pl_aft) pl_aft = x;
				SetPLIDkeel( x );
			}

			pl_fwd = ((pl_fwd - 154) * 6) + 70;
			pl_aft = ((pl_aft - 154) * 6) + 70 + 5;

			int offset_y_top = 173;
			PointCollection points_top = new PointCollection()// (0,0) at center of PLB
			{
				new Point( pl_fwd - 15, 137 + offset_y_top ),
				new Point( pl_aft + 15, 137 + offset_y_top ),
				new Point( pl_aft + 15, -137 + offset_y_top ),
				new Point( pl_fwd - 15, -137 + offset_y_top )
				
			};
			Polygon plgn = new Polygon();
			plgn.Points = points_top;
			plgn.Stroke = stroke;
			plgn.Fill = fill;
			plgn.Opacity = 0.9;
			plgn.ToolTip = name + " (" + plname + ")";
			cnvPLB.Children.Add( plgn );

			int offset_y_side = 500;
			PointCollection points_side = new PointCollection()// (0,0) at center of PLB and fwd-end of bay
			{
				new Point( pl_fwd - 15, 137 + offset_y_side ),
				new Point( pl_aft + 15, 137 + offset_y_side ),
				new Point( pl_aft + 15, -137 + offset_y_side ),
				new Point( pl_fwd - 15, -137 + offset_y_side )
			};
			plgn = new Polygon();
			plgn.Points = points_side;
			plgn.Stroke = stroke;
			plgn.Fill = fill;
			plgn.Opacity = 0.9;
			plgn.ToolTip = name + " (" + plname + ")";
			cnvPLB.Children.Add( plgn );
			return;
		}

		private void DrawBayBridge( string plname, int bay, int bridge )
		{
			int[] bay_fwd = {70, 113, 203, 287, 377, 461, 555, 641, 731, 809, 887, 965, 1049};
			int[] bay_aft = {111, 201, 285, 375, 459, 553, 639, 729, 807, 885, 963, 1047, 1136};

			int bay_port = 0;
			int bay_stbd = 0;
			if (bridge == 0)// port
			{
				bay_port = 143;
				bay_stbd = 123;
			}
			else if (bridge == 1)// starboard
			{
				bay_port = -123;
				bay_stbd = -143;
			}
			else if (bridge == 2)// keel
			{
				bay_port = 20;
				bay_stbd = -20;
			}

			int offset_y_top = 173;
			PointCollection points_top = new PointCollection()// (0,0) at center of PLB and fwd-end of bay
			{
				new Point( bay_fwd[bay - 1], bay_port + offset_y_top ),
				new Point( bay_aft[bay - 1], bay_port + offset_y_top ),
				new Point( bay_aft[bay - 1], bay_stbd + offset_y_top ),
				new Point( bay_fwd[bay - 1], bay_stbd + offset_y_top )
				
			};
			Polygon plgn = new Polygon();
			plgn.Points = points_top;
			plgn.Stroke = Brushes.Orange;
			plgn.Fill = Brushes.Orange;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "Bay Bridge (" + plname + ")";
			cnvPLB.Children.Add( plgn );


			int bay_top = 0;
			int bay_bot = 0;
			if ((bridge == 0) || (bridge == 1))// port or starboard
			{
				bay_top = -30;
				bay_bot = 10;
			}
			else if (bridge == 2)// keel
			{
				bay_top = 120;
				bay_bot = 140;
			}

			int offset_y_side = 500;
			PointCollection points_side = new PointCollection()// (0,0) at center of PLB and fwd-end of bay
			{
				new Point( bay_fwd[bay - 1], bay_top + offset_y_side ),
				new Point( bay_aft[bay - 1], bay_top + offset_y_side ),
				new Point( bay_aft[bay - 1], bay_bot + offset_y_side ),
				new Point( bay_fwd[bay - 1], bay_bot + offset_y_side )
			};
			plgn = new Polygon();
			plgn.Points = points_side;
			plgn.Stroke = Brushes.Orange;
			plgn.Fill = Brushes.Orange;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "Bay Bridge (" + plname + ")";
			cnvPLB.Children.Add( plgn );
			return;
		}

		private void DrawExternalAirlock( bool aft, bool ods )
		{
			int offset_x_top = 135;
			int offset_y_top = 173;
			if (aft) offset_x_top += 126;
			PointCollection points_top = new PointCollection()// (0,0) at center of airlock
			{
				new Point( -110 + offset_x_top, -41 + offset_y_top ),
				new Point( -63 + offset_x_top, -41 + offset_y_top ),
				new Point( -63 + offset_x_top, -137 + offset_y_top ),
				new Point( 20 + offset_x_top, -137 + offset_y_top ),
				new Point( 63 + offset_x_top, -59 + offset_y_top ),
				new Point( 63 + offset_x_top, 59 + offset_y_top ),
				new Point( 20 + offset_x_top, 137 + offset_y_top ),
				new Point( -63 + offset_x_top, 137 + offset_y_top ),
				new Point( -63 + offset_x_top, 41 + offset_y_top ),
				new Point( -110 + offset_x_top, 41 + offset_y_top )
				
			};
			Polygon plgn = new Polygon();
			plgn.Points = points_top;
			plgn.Stroke = Brushes.Olive;
			plgn.Fill = Brushes.Olive;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "External Airlock";
			cnvPLB.Children.Add( plgn );
			
			int offset_x_side = 135;
			int offset_y_side = 564;
			if (aft) offset_x_side += 126;
			PointCollection points_side = new PointCollection()// (0,0) at center of airlock hatch
			{
				new Point( -110 + offset_x_side, -41 + offset_y_side ),
				new Point( -51 + offset_x_side, -41 + offset_y_side ),
				new Point( -51 + offset_x_side, -75 + offset_y_side ),
				new Point( -63 + offset_x_side, -75 + offset_y_side ),
				new Point( -63 + offset_x_side, -94 + offset_y_side ),
				new Point( -62 + offset_x_side, -94 + offset_y_side ),
				new Point( -47 + offset_x_side, -106 + offset_y_side ),
				//// ODS
				new Point( 47 + offset_x_side, -106 + offset_y_side ),
				new Point( 62 + offset_x_side, -94 + offset_y_side ),
				new Point( 62 + offset_x_side, -75 + offset_y_side ),
				new Point( 51 + offset_x_side, -75 + offset_y_side ),
				new Point( 51 + offset_x_side, -41 + offset_y_side ),
				new Point( 62 + offset_x_side, -41 + offset_y_side ),
				new Point( 62 + offset_x_side, 41 + offset_y_side ),
				new Point( 51 + offset_x_side, 41 + offset_y_side ),
				new Point( 51 + offset_x_side, 48 + offset_y_side ),
				new Point( 41 + offset_x_side, 61 + offset_y_side ),
				new Point( 17 + offset_x_side, 66 + offset_y_side ),
				new Point( -17 + offset_x_side, 66 + offset_y_side ),
				new Point( -41 + offset_x_side, 61 + offset_y_side ),
				new Point( -51 + offset_x_side, 48 + offset_y_side ),
				new Point( -51 + offset_x_side, 41 + offset_y_side ),
				new Point( -110 + offset_x_side, 41 + offset_y_side )
			};
			plgn = new Polygon();
			plgn.Points = points_side;
			plgn.Stroke = Brushes.Olive;
			plgn.Fill = Brushes.Olive;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "External Airlock";
			cnvPLB.Children.Add( plgn );
			if (ods)
			{
				points_side = new PointCollection()// (0,0) at center of airlock hatch
				{
					new Point( -47 + offset_x_side, -106 + offset_y_side ),
					new Point( -46 + offset_x_side, -156 + offset_y_side ),
					new Point( -32 + offset_x_side, -156 + offset_y_side ),
					new Point( -16 + offset_x_side, -168 + offset_y_side ),
					new Point( -8 + offset_x_side, -168 + offset_y_side ),
					new Point( 0 + offset_x_side, -156 + offset_y_side ),
					new Point( 24 + offset_x_side, -156 + offset_y_side ),
					new Point( 24 + offset_x_side, -168 + offset_y_side ),
					new Point( 35 + offset_x_side, -156 + offset_y_side ),
					new Point( 46 + offset_x_side, -156 + offset_y_side ),
					new Point( 47 + offset_x_side, -106 + offset_y_side )
				};
				plgn = new Polygon();
				plgn.Points = points_side;
				plgn.Stroke = Brushes.Olive;
				plgn.Fill = Brushes.Olive;
				plgn.Opacity = 0.9;
				plgn.ToolTip = "Orbiter Docking System";
				cnvPLB.Children.Add( plgn );
			}

			if (aft)
			{
				SetPLIDport( 177 );
				SetPLIDstbd( 177 );
				SetPLIDport( 188 );
				SetPLIDstbd( 188 );
				SetPLIDkeel( 187 );
			}
			else
			{
				SetPLIDport( 156 );
				SetPLIDstbd( 156 );
				SetPLIDport( 167 );
				SetPLIDstbd( 167 );
				SetPLIDkeel( 166 );
			}
			return;
		}

		private void DrawTAA( bool aft, bool extal )
		{
			int offset_x_top = 86;
			int offset_y_top = 173;
			if (aft) offset_x_top += 193;
			PointCollection points_top;
			if (aft)
			{
				points_top = new PointCollection()// (0,0) at center of TAA
				{
					new Point( -88 + offset_x_top, -44 + offset_y_top ),
					new Point( -83 + offset_x_top, -49 + offset_y_top ),
					new Point( -79 + offset_x_top, -49 + offset_y_top ),
					new Point( -74 + offset_x_top, -44 + offset_y_top ),
					new Point( -74 + offset_x_top, -39 + offset_y_top ),
					new Point( -72 + offset_x_top, -39 + offset_y_top ),
					new Point( -72 + offset_x_top, -137 + offset_y_top ),
					new Point( 74 + offset_x_top, -137 + offset_y_top ),
					new Point( 74 + offset_x_top, -39 + offset_y_top ),
					new Point( 75 + offset_x_top, -39 + offset_y_top ),
					new Point( 75 + offset_x_top, -44 + offset_y_top ),
					new Point( 80 + offset_x_top, -49 + offset_y_top ),
					new Point( 84 + offset_x_top, -49 + offset_y_top ),
					new Point( 89 + offset_x_top, -44 + offset_y_top ),
					new Point( 89 + offset_x_top, 44 + offset_y_top ),
					new Point( 84 + offset_x_top, 49 + offset_y_top ),
					new Point( 80 + offset_x_top, 49 + offset_y_top ),
					new Point( 75 + offset_x_top, 44 + offset_y_top ),
					new Point( 75 + offset_x_top, 39 + offset_y_top ),
					new Point( 74 + offset_x_top, 39 + offset_y_top ),
					new Point( 74 + offset_x_top, 137 + offset_y_top ),
					new Point( -72 + offset_x_top, 137 + offset_y_top ),
					new Point( -72 + offset_x_top, 39 + offset_y_top ),
					new Point( -74 + offset_x_top, 39 + offset_y_top ),
					new Point( -74 + offset_x_top, 44 + offset_y_top ),
					new Point( -79 + offset_x_top, 49 + offset_y_top ),
					new Point( -83 + offset_x_top, 49 + offset_y_top ),
					new Point( -88 + offset_x_top, 44 + offset_y_top )
				};
			}
			else
			{
				if (extal)
				{
					points_top = new PointCollection()// (0,0) at center of TAA
					{
						new Point( -64 + offset_x_top, -39 + offset_y_top ),
						new Point( -43 + offset_x_top, -48 + offset_y_top ),
						new Point( 43 + offset_x_top, -48 + offset_y_top ),
						new Point( 64 + offset_x_top, -39 + offset_y_top ),
						new Point( 64 + offset_x_top, 39 + offset_y_top ),
						new Point( 43 + offset_x_top, 48 + offset_y_top ),
						new Point( -43 + offset_x_top, 48 + offset_y_top ),
						new Point( -64 + offset_x_top, 39 + offset_y_top )
					};
				}
				else
				{
					points_top = new PointCollection()// (0,0) at center of TAA
					{
						new Point( -64 + offset_x_top, -39 + offset_y_top ),
						new Point( -43 + offset_x_top, -48 + offset_y_top ),
						new Point( 43 + offset_x_top, -48 + offset_y_top ),
						new Point( 64 + offset_x_top, -39 + offset_y_top ),
						new Point( 102 + offset_x_top, -39 + offset_y_top ),
						new Point( 102 + offset_x_top, -44 + offset_y_top ),
						new Point( 107 + offset_x_top, -49 + offset_y_top ),
						new Point( 111 + offset_x_top, -49 + offset_y_top ),
						new Point( 116 + offset_x_top, -44 + offset_y_top ),
						new Point( 116 + offset_x_top, 44 + offset_y_top ),
						new Point( 111 + offset_x_top, 49 + offset_y_top ),
						new Point( 107 + offset_x_top, 49 + offset_y_top ),
						new Point( 102 + offset_x_top, 44 + offset_y_top ),
						new Point( 102 + offset_x_top, 39 + offset_y_top ),
						new Point( 64 + offset_x_top, 39 + offset_y_top ),
						new Point( 43 + offset_x_top, 48 + offset_y_top ),
						new Point( -43 + offset_x_top, 48 + offset_y_top ),
						new Point( -64 + offset_x_top, 39 + offset_y_top )
					};
				}
			}

			Polygon plgn = new Polygon();
			plgn.Points = points_top;
			plgn.Stroke = Brushes.Olive;
			plgn.Fill = Brushes.Olive;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "Tunnel Adapter Assembly";
			cnvPLB.Children.Add( plgn );
			
			int offset_x_side = 86;
			int offset_y_side = 564;
			if (aft) offset_x_side += 193;
			PointCollection points_side;
			if (aft)
			{
				points_side = new PointCollection()// (0,0) at center of TAA
				{
					new Point( -88 + offset_x_side, -44 + offset_y_side ),
					new Point( -83 + offset_x_side, -49 + offset_y_side ),
					new Point( -79 + offset_x_side, -49 + offset_y_side ),
					new Point( -74 + offset_x_side, -44 + offset_y_side ),
					new Point( -74 + offset_x_side, -39 + offset_y_side ),
					new Point( -72 + offset_x_side, -39 + offset_y_side ),
					new Point( -72 + offset_x_side, -90 + offset_y_side ),
					new Point( 74 + offset_x_side, -90 + offset_y_side ),
					new Point( 74 + offset_x_side, -39 + offset_y_side ),
					new Point( 75 + offset_x_side, -39 + offset_y_side ),
					new Point( 75 + offset_x_side, -44 + offset_y_side ),
					new Point( 80 + offset_x_side, -49 + offset_y_side ),
					new Point( 84 + offset_x_side, -49 + offset_y_side ),
					new Point( 89 + offset_x_side, -44 + offset_y_side ),
					new Point( 89 + offset_x_side, 44 + offset_y_side ),
					new Point( 84 + offset_x_side, 49 + offset_y_side ),
					new Point( 80 + offset_x_side, 49 + offset_y_side ),
					new Point( 75 + offset_x_side, 44 + offset_y_side ),
					new Point( 75 + offset_x_side, 39 + offset_y_side ),
					new Point( 74 + offset_x_side, 39 + offset_y_side ),
					new Point( 74 + offset_x_side, 73 + offset_y_side ),
					new Point( 66 + offset_x_side, 73 + offset_y_side ),
					new Point( 66 + offset_x_side, 39 + offset_y_side ),
					new Point( 65 + offset_x_side, 39 + offset_y_side ),
					new Point( 44 + offset_x_side, 48 + offset_y_side ),
					new Point( -43 + offset_x_side, 48 + offset_y_side ),
					new Point( -64 + offset_x_side, 39 + offset_y_side ),
					new Point( -74 + offset_x_side, 39 + offset_y_side ),
					new Point( -74 + offset_x_side, 44 + offset_y_side ),
					new Point( -79 + offset_x_side, 49 + offset_y_side ),
					new Point( -83 + offset_x_side, 49 + offset_y_side ),
					new Point( -88 + offset_x_side, 44 + offset_y_side )
				};
			}
			else
			{
				if (extal)
				{
					points_side = new PointCollection()// (0,0) at center of TAA
					{
						new Point( -64 + offset_x_side, -39 + offset_y_side ),
						new Point( -43 + offset_x_side, -48 + offset_y_side ),
						new Point( -39 + offset_x_side, -48 + offset_y_side ),
						new Point( -39 + offset_x_side, -59 + offset_y_side ),
						new Point( 39 + offset_x_side, -59 + offset_y_side ),
						new Point( 39 + offset_x_side, -48 + offset_y_side ),
						new Point( 43 + offset_x_side, -48 + offset_y_side ),
						new Point( 64 + offset_x_side, -39 + offset_y_side ),
						new Point( 64 + offset_x_side, 39 + offset_y_side ),
						new Point( 43 + offset_x_side, 48 + offset_y_side ),
						new Point( -43 + offset_x_side, 48 + offset_y_side ),
						new Point( -64 + offset_x_side, 39 + offset_y_side )
					};
				}
				else
				{
					points_side = new PointCollection()// (0,0) at center of TAA
					{
						new Point( -64 + offset_x_side, -39 + offset_y_side ),
						new Point( -43 + offset_x_side, -48 + offset_y_side ),
						new Point( -39 + offset_x_side, -48 + offset_y_side ),
						new Point( -39 + offset_x_side, -59 + offset_y_side ),
						new Point( 39 + offset_x_side, -59 + offset_y_side ),
						new Point( 39 + offset_x_side, -48 + offset_y_side ),
						new Point( 43 + offset_x_side, -48 + offset_y_side ),
						new Point( 64 + offset_x_side, -39 + offset_y_side ),
						new Point( 102 + offset_x_side, -39 + offset_y_side ),
						new Point( 102 + offset_x_side, -44 + offset_y_side ),
						new Point( 107 + offset_x_side, -49 + offset_y_side ),
						new Point( 111 + offset_x_side, -49 + offset_y_side ),
						new Point( 116 + offset_x_side, -44 + offset_y_side ),
						new Point( 116 + offset_x_side, 44 + offset_y_side ),
						new Point( 111 + offset_x_side, 49 + offset_y_side ),
						new Point( 107 + offset_x_side, 49 + offset_y_side ),
						new Point( 102 + offset_x_side, 44 + offset_y_side ),
						new Point( 102 + offset_x_side, 39 + offset_y_side ),
						new Point( 64 + offset_x_side, 39 + offset_y_side ),
						new Point( 43 + offset_x_side, 48 + offset_y_side ),
						new Point( -43 + offset_x_side, 48 + offset_y_side ),
						new Point( -64 + offset_x_side, 39 + offset_y_side )
					};
				}
			}
			plgn = new Polygon();
			plgn.Points = points_side;
			plgn.Stroke = Brushes.Olive;
			plgn.Fill = Brushes.Olive;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "Tunnel Adapter Assembly";
			cnvPLB.Children.Add( plgn );

			if (aft)
			{
				SetPLIDport( 177 );
				SetPLIDstbd( 177 );
				SetPLIDport( 200 );
				SetPLIDstbd( 200 );
				SetPLIDkeel( 200 );
			}
			return;
		}

		private void DrawEDOpallet()
		{
			int offset_x_top = 991;
			int offset_y_top = 173;
			PointCollection points_top = new PointCollection()// (0,0) at center of PLB and fwd face
			{
				new Point( 0 + offset_x_top, -142 + offset_y_top ),
				new Point( 145 + offset_x_top, -142 + offset_y_top ),
				new Point( 145 + offset_x_top, 142 + offset_y_top ),
				new Point( 0 + offset_x_top, 142 + offset_y_top ),
			};
			Polygon plgn = new Polygon();
			plgn.Points = points_top;
			plgn.Stroke = Brushes.RosyBrown;
			plgn.Fill = Brushes.RosyBrown;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "EDO Pallet";
			cnvPLB.Children.Add( plgn );
			
			int offset_x_side = 991;
			int offset_y_side = 500;
			PointCollection points_side = new PointCollection()// (0,0) at center of PLB and fwd face
			{
				new Point( 0 + offset_x_side, -132 + offset_y_side ),
				new Point( 145 + offset_x_side, -132 + offset_y_side ),
				new Point( 145 + offset_x_side, 115 + offset_y_side ),
				new Point( 40 + offset_x_side, 115 + offset_y_side ),
				new Point( 40 + offset_x_side, 132 + offset_y_side ),
				new Point( 6 + offset_x_side, 132 + offset_y_side ),
				new Point( 6 + offset_x_side, 115 + offset_y_side ),
				new Point( 0 + offset_x_side, 115 + offset_y_side ),
			};
			plgn = new Polygon();
			plgn.Points = points_side;
			plgn.Stroke = Brushes.RosyBrown;
			plgn.Fill = Brushes.RosyBrown;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "EDO Pallet";
			cnvPLB.Children.Add( plgn );

			SetPLIDport( 311 );
			SetPLIDstbd( 311 );
			SetPLIDkeel( 311 );
			return;
		}

		private void DrawIUS2( string name, string plname, bool aft, double adapterheight )
		{
			int offset_x_top = 730;
			int offset_y_top = 173;
			if (aft) offset_x_top += 84;
			PointCollection points_top = new PointCollection()// (0,0) at center of PL interface
			{
				// payload 75'' diameter, 200'' length
				// payload adapter: 80'' diameter, custom length
				new Point( -(adapterheight * 60) + offset_x_top, 61 + offset_y_top ),// adapter
				new Point( -(adapterheight * 60) + offset_x_top, 115 + offset_y_top ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_top, 115 + offset_y_top ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_top, -115 + offset_y_top ),// payload
				new Point( -(adapterheight * 60) + offset_x_top, -115 + offset_y_top ),// payload
				new Point( -(adapterheight * 60) + offset_x_top, -61 + offset_y_top ),// adapter

				new Point( 0 + offset_x_top, -88 + offset_y_top ),
				new Point( 25 + offset_x_top, -84 + offset_y_top ),
				new Point( 25 + offset_x_top, -117 + offset_y_top ),
				new Point( 3 + offset_x_top, -117 + offset_y_top ),
				new Point( 3 + offset_x_top, -124 + offset_y_top ),
				new Point( 25 + offset_x_top, -124 + offset_y_top ),
				new Point( 25 + offset_x_top, -138 + offset_y_top ),
				new Point( 39 + offset_x_top, -138 + offset_y_top ),
				new Point( 39 + offset_x_top, -124 + offset_y_top ),
				new Point( 59 + offset_x_top, -124 + offset_y_top ),
				new Point( 59 + offset_x_top, -117 + offset_y_top ),
				new Point( 39 + offset_x_top, -117 + offset_y_top ),
				new Point( 39 + offset_x_top, -79 + offset_y_top ),
				new Point( 54 + offset_x_top, -70 + offset_y_top ),
				new Point( 220 + offset_x_top, -70 + offset_y_top ),
				new Point( 220 + offset_x_top, -117 + offset_y_top ),
				new Point( 226 + offset_x_top, -117 + offset_y_top ),
				new Point( 205 + offset_x_top, -129 + offset_y_top ),
				new Point( 172 + offset_x_top, -129 + offset_y_top ),
				new Point( 172 + offset_x_top, -138 + offset_y_top ),
				new Point( 208 + offset_x_top, -138 + offset_y_top ),
				new Point( 229 + offset_x_top, -132 + offset_y_top ),
				new Point( 235 + offset_x_top, -132 + offset_y_top ),
				new Point( 255 + offset_x_top, -138 + offset_y_top ),
				new Point( 290 + offset_x_top, -138 + offset_y_top ),
				new Point( 290 + offset_x_top, -129 + offset_y_top ),
				new Point( 258 + offset_x_top, -129 + offset_y_top ),
				new Point( 238 + offset_x_top, -117 + offset_y_top ),
				new Point( 251 + offset_x_top, -117 + offset_y_top ),
				new Point( 278 + offset_x_top, -79 + offset_y_top ),
				new Point( 278 + offset_x_top, -27 + offset_y_top ),
				new Point( 314 + offset_x_top, -40 + offset_y_top ),
				new Point( 314 + offset_x_top, 40 + offset_y_top ),
				new Point( 278 + offset_x_top, 27 + offset_y_top ),
				new Point( 278 + offset_x_top, 79 + offset_y_top ),
				new Point( 251 + offset_x_top, 117 + offset_y_top ),
				new Point( 238 + offset_x_top, 117 + offset_y_top ),
				new Point( 258 + offset_x_top, 129 + offset_y_top ),
				new Point( 290 + offset_x_top, 129 + offset_y_top ),
				new Point( 290 + offset_x_top, 138 + offset_y_top ),
				new Point( 255 + offset_x_top, 138 + offset_y_top ),
				new Point( 235 + offset_x_top, 132 + offset_y_top ),
				new Point( 229 + offset_x_top, 132 + offset_y_top ),
				new Point( 208 + offset_x_top, 138 + offset_y_top ),
				new Point( 172 + offset_x_top, 138 + offset_y_top ),
				new Point( 172 + offset_x_top, 129 + offset_y_top ),
				new Point( 205 + offset_x_top, 129 + offset_y_top ),
				new Point( 226 + offset_x_top, 117 + offset_y_top ),
				new Point( 220 + offset_x_top, 117 + offset_y_top ),
				new Point( 220 + offset_x_top, 70 + offset_y_top ),
				new Point( 54 + offset_x_top, 70 + offset_y_top ),
				new Point( 39 + offset_x_top, 79 + offset_y_top ),
				new Point( 39 + offset_x_top, 117 + offset_y_top ),
				new Point( 59 + offset_x_top, 117 + offset_y_top ),
				new Point( 59 + offset_x_top, 124 + offset_y_top ),
				new Point( 39 + offset_x_top, 124 + offset_y_top ),
				new Point( 39 + offset_x_top, 138 + offset_y_top ),
				new Point( 25 + offset_x_top, 138 + offset_y_top ),
				new Point( 25 + offset_x_top, 124 + offset_y_top ),
				new Point( 3 + offset_x_top, 124 + offset_y_top ),
				new Point( 3 + offset_x_top, 117 + offset_y_top ),
				new Point( 25 + offset_x_top, 117 + offset_y_top ),
				new Point( 25 + offset_x_top, 84 + offset_y_top ),
				new Point( 0 + offset_x_top, 88 + offset_y_top )
				
			};
			Polygon plgn = new Polygon();
			plgn.Points = points_top;
			plgn.Stroke = Brushes.Red;
			plgn.Fill = Brushes.Red;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "IUS 2-stage (" + name + " + " + plname + ")";
			cnvPLB.Children.Add( plgn );
			
			int offset_x_side = 730;
			int offset_y_side = 500;
			if (aft) offset_x_side += 84;
			PointCollection points_side = new PointCollection()// (0,0) at center of PL interface
			{
				// payload 75'' diameter, 200'' length
				// payload adapter: 80'' diameter, custom length
				new Point( -(adapterheight * 60) + offset_x_side, 61 + offset_y_side ),// adapter
				new Point( -(adapterheight * 60) + offset_x_side, 115 + offset_y_side ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_side, 115 + offset_y_side ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_side, -115 + offset_y_side ),// payload
				new Point( -(adapterheight * 60) + offset_x_side, -115 + offset_y_side ),// payload
				new Point( -(adapterheight * 60) + offset_x_side, -61 + offset_y_side ),// adapter

				new Point( 0 + offset_x_side, -88 + offset_y_side ),
				new Point( 36 + offset_x_side, -81 + offset_y_side ),
				new Point( 54 + offset_x_side, -70 + offset_y_side ),
				new Point( 220 + offset_x_side, -70 + offset_y_side ),
				new Point( 220 + offset_x_side, -88 + offset_y_side ),
				new Point( 278 + offset_x_side, -88 + offset_y_side ),
				new Point( 278 + offset_x_side, -27 + offset_y_side ),
				new Point( 314 + offset_x_side, -40 + offset_y_side ),
				new Point( 314 + offset_x_side, 40 + offset_y_side ),
				new Point( 278 + offset_x_side, 27 + offset_y_side ),
				new Point( 278 + offset_x_side, 88 + offset_y_side ),
				new Point( 220 + offset_x_side, 88 + offset_y_side ),
				new Point( 220 + offset_x_side, 84 + offset_y_side ),
				new Point( 39 + offset_x_side, 84 + offset_y_side ),
				new Point( 39 + offset_x_side, 139 + offset_y_side ),
				new Point( 25 + offset_x_side, 139 + offset_y_side ),
				new Point( 25 + offset_x_side, 83 + offset_y_side ),
				new Point( 0 + offset_x_side, 88 + offset_y_side )
			};
			plgn = new Polygon();
			plgn.Points = points_side;
			plgn.Stroke = Brushes.Red;
			plgn.Fill = Brushes.Red;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "IUS 2-stage (" + name + " + " + plname + ")";
			cnvPLB.Children.Add( plgn );

			if (aft)
			{
				SetPLIDport( 283 );
				SetPLIDstbd( 283 );
				SetPLIDport( 307 );
				SetPLIDstbd( 307 );
				SetPLIDport( 325 );
				SetPLIDstbd( 325 );
				SetPLIDkeel( 283 );
			}
			else
			{
				SetPLIDport( 269 );
				SetPLIDstbd( 269 );
				SetPLIDport( 293 );
				SetPLIDstbd( 293 );
				SetPLIDport( 311 );
				SetPLIDstbd( 311 );
				SetPLIDkeel( 269 );
			}
			return;
		}

		private void DrawCentaurG( string name, string plname, double adapterheight )
		{
			int offset_x_top = 763;
			int offset_y_top = 173;
			PointCollection points_top = new PointCollection()// (0,0) at center of PL interface
			{
				// payload 75'' diameter, 200'' length
				// payload adapter: 80'' diameter, custom length
				new Point( -(adapterheight * 60) + offset_x_top, 61 + offset_y_top ),// adapter
				new Point( -(adapterheight * 60) + offset_x_top, 115 + offset_y_top ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_top, 115 + offset_y_top ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_top, -115 + offset_y_top ),// payload
				new Point( -(adapterheight * 60) + offset_x_top, -115 + offset_y_top ),// payload
				new Point( -(adapterheight * 60) + offset_x_top, -61 + offset_y_top ),// adapter

				new Point( 0 + offset_x_top, -85 + offset_y_top ),
				new Point( 47 + offset_x_top, -132 + offset_y_top ),
				new Point( 149 + offset_x_top, -132 + offset_y_top ),
				new Point( 190 + offset_x_top, -94 + offset_y_top ),
				new Point( 196 + offset_x_top, -94 + offset_y_top ),
				new Point( 196 + offset_x_top, -136 + offset_y_top ),
				new Point( 347 + offset_x_top, -136 + offset_y_top ),
				new Point( 347 + offset_x_top, -73 + offset_y_top ),
				new Point( 365 + offset_x_top, -66 + offset_y_top ),
				new Point( 365 + offset_x_top, 66 + offset_y_top ),
				new Point( 347 + offset_x_top, 73 + offset_y_top ),
				new Point( 347 + offset_x_top, 136 + offset_y_top ),
				new Point( 196 + offset_x_top, 136 + offset_y_top ),
				new Point( 196 + offset_x_top, 94 + offset_y_top ),
				new Point( 190 + offset_x_top, 94 + offset_y_top ),
				new Point( 149 + offset_x_top, 132 + offset_y_top ),
				new Point( 47 + offset_x_top, 132 + offset_y_top ),
				new Point( 0 + offset_x_top, 85 + offset_y_top )
			};
			Polygon plgn = new Polygon();
			plgn.Points = points_top;
			plgn.Stroke = Brushes.Red;
			plgn.Fill = Brushes.Red;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "Centaur G (" + name + " + " + plname + ")";
			cnvPLB.Children.Add( plgn );
			
			int offset_x_side = 763;
			int offset_y_side = 500;
			PointCollection points_side = new PointCollection()// (0,0) at center of PL interface
			{
				// payload 75'' diameter, 200'' length
				// payload adapter: 80'' diameter, custom length
				new Point( -(adapterheight * 60) + offset_x_side, 61 + offset_y_side ),// adapter
				new Point( -(adapterheight * 60) + offset_x_side, 115 + offset_y_side ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_side, 115 + offset_y_side ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_side, -115 + offset_y_side ),// payload
				new Point( -(adapterheight * 60) + offset_x_side, -115 + offset_y_side ),// payload
				new Point( -(adapterheight * 60) + offset_x_side, -61 + offset_y_side ),// adapter

				new Point( 0 + offset_x_side, -85 + offset_y_side ),
				new Point( 47 + offset_x_side, -132 + offset_y_side ),
				new Point( 149 + offset_x_side, -132 + offset_y_side ),
				new Point( 190 + offset_x_side, -94 + offset_y_side ),
				new Point( 284 + offset_x_side, -94 + offset_y_side ),
				new Point( 284 + offset_x_side, -56 + offset_y_side ),
				new Point( 365 + offset_x_side, -18 + offset_y_side ),
				new Point( 365 + offset_x_side, 18 + offset_y_side ),
				new Point( 284 + offset_x_side, 56 + offset_y_side ),
				new Point( 284 + offset_x_side, 94 + offset_y_side ),
				new Point( 261 + offset_x_side, 137 + offset_y_side ),
				new Point( 196 + offset_x_side, 137 + offset_y_side ),
				new Point( 196 + offset_x_side, 94 + offset_y_side ),
				new Point( 190 + offset_x_side, 94 + offset_y_side ),
				new Point( 149 + offset_x_side, 132 + offset_y_side ),
				new Point( 47 + offset_x_side, 132 + offset_y_side ),
				new Point( 0 + offset_x_side, 85 + offset_y_side )
			};
			plgn = new Polygon();
			plgn.Points = points_side;
			plgn.Stroke = Brushes.Red;
			plgn.Fill = Brushes.Red;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "Centaur G (" + name + " + " + plname + ")";
			cnvPLB.Children.Add( plgn );

			// CISS
			SetPLIDport( 305 );
			SetPLIDstbd( 305 );
			SetPLIDport( 323 );
			SetPLIDstbd( 323 );
			SetPLIDkeel( 311 );
			// Centaur
			SetPLIDport( 270 );
			SetPLIDstbd( 270 );
			SetPLIDkeel( 270 );
			return;
		}

		private void DrawCentaurGPrime( string name, string plname, double adapterheight )
		{
			int offset_x_top = 587;
			int offset_y_top = 173;
			PointCollection points_top = new PointCollection()// (0,0) at center of PL interface
			{
				// payload 75'' diameter, 200'' length
				// payload adapter: 80'' diameter, custom length
				new Point( -(adapterheight * 60) + offset_x_top, 61 + offset_y_top ),// adapter
				new Point( -(adapterheight * 60) + offset_x_top, 115 + offset_y_top ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_top, 115 + offset_y_top ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_top, -115 + offset_y_top ),// payload
				new Point( -(adapterheight * 60) + offset_x_top, -115 + offset_y_top ),// payload
				new Point( -(adapterheight * 60) + offset_x_top, -61 + offset_y_top ),// adapter

				new Point( 0 + offset_x_top, -85 + offset_y_top ),
				new Point( 74 + offset_x_top, -132 + offset_y_top ),
				new Point( 230 + offset_x_top, -132 + offset_y_top ),
				new Point( 317 + offset_x_top, -94 + offset_y_top ),
				new Point( 338 + offset_x_top, -94 + offset_y_top ),
				new Point( 338 + offset_x_top, -136 + offset_y_top ),
				new Point( 523 + offset_x_top, -136 + offset_y_top ),
				new Point( 523 + offset_x_top, -73 + offset_y_top ),
				new Point( 541 + offset_x_top, -66 + offset_y_top ),
				new Point( 541 + offset_x_top, 66 + offset_y_top ),
				new Point( 523 + offset_x_top, 73 + offset_y_top ),
				new Point( 523 + offset_x_top, 136 + offset_y_top ),
				new Point( 338 + offset_x_top, 136 + offset_y_top ),
				new Point( 338 + offset_x_top, 94 + offset_y_top ),
				new Point( 317 + offset_x_top, 94 + offset_y_top ),
				new Point( 230 + offset_x_top, 132 + offset_y_top ),
				new Point( 74 + offset_x_top, 132 + offset_y_top ),
				new Point( 0 + offset_x_top, 85 + offset_y_top )
			};
			Polygon plgn = new Polygon();
			plgn.Points = points_top;
			plgn.Stroke = Brushes.Red;
			plgn.Fill = Brushes.Red;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "Centaur G' (" + name + " + " + plname + ")";
			cnvPLB.Children.Add( plgn );
			
			int offset_x_side = 587;
			int offset_y_side = 500;
			PointCollection points_side = new PointCollection()// (0,0) at center of PL interface
			{
				// payload 75'' diameter, 200'' length
				// payload adapter: 80'' diameter, custom length
				new Point( -(adapterheight * 60) + offset_x_side, 61 + offset_y_side ),// adapter
				new Point( -(adapterheight * 60) + offset_x_side, 115 + offset_y_side ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_side, 115 + offset_y_side ),// payload
				new Point( -305 - (adapterheight * 60) + offset_x_side, -115 + offset_y_side ),// payload
				new Point( -(adapterheight * 60) + offset_x_side, -115 + offset_y_side ),// payload
				new Point( -(adapterheight * 60) + offset_x_side, -61 + offset_y_side ),// adapter

				new Point( 0 + offset_x_side, -85 + offset_y_side ),
				new Point( 74 + offset_x_side, -132 + offset_y_side ),
				new Point( 230 + offset_x_side, -132 + offset_y_side ),
				new Point( 317 + offset_x_side, -94 + offset_y_side ),
				new Point( 460 + offset_x_side, -94 + offset_y_side ),
				new Point( 460 + offset_x_side, -56 + offset_y_side ),
				new Point( 541 + offset_x_side, -18 + offset_y_side ),
				new Point( 541 + offset_x_side, 18 + offset_y_side ),
				new Point( 460 + offset_x_side, 56 + offset_y_side ),
				new Point( 460 + offset_x_side, 94 + offset_y_side ),
				new Point( 437 + offset_x_side, 137 + offset_y_side ),
				new Point( 338 + offset_x_side, 137 + offset_y_side ),
				new Point( 338 + offset_x_side, 94 + offset_y_side ),
				new Point( 317 + offset_x_side, 94 + offset_y_side ),
				new Point( 230 + offset_x_side, 132 + offset_y_side ),
				new Point( 74 + offset_x_side, 132 + offset_y_side ),
				new Point( 0 + offset_x_side, 85 + offset_y_side )
			};
			plgn = new Polygon();
			plgn.Points = points_side;
			plgn.Stroke = Brushes.Red;
			plgn.Fill = Brushes.Red;
			plgn.Opacity = 0.9;
			plgn.ToolTip = "Centaur G' (" + name + " + " + plname + ")";
			cnvPLB.Children.Add( plgn );

			// CISS
			SetPLIDport( 297 );
			SetPLIDstbd( 297 );
			SetPLIDport( 323 );
			SetPLIDstbd( 323 );
			SetPLIDkeel( 311 );
			// Centaur
			SetPLIDport( 241 );
			SetPLIDstbd( 241 );
			SetPLIDkeel( 241 );
			return;
		}

		void SetPLIDport( int PLID )
		{
			string strplid = "p" + PLID;
			foreach (UIElement x in cnvPLB.Children)
			{
				Rectangle r = x as Rectangle;
				if (r == null) continue;

				if (r.Name == strplid)
				{
					r.Stroke = Brushes.LimeGreen;
					r.Fill = Brushes.LimeGreen;
					r.Height = heightpl;
					Canvas.SetTop( r, yport - 5 );
					break;
				}
			}
			return;
		}

		void SetPLIDstbd( int PLID )
		{
			string strplid = "s" + PLID;
			foreach (UIElement x in cnvPLB.Children)
			{
				Rectangle r = x as Rectangle;
				if (r == null) continue;

				if (r.Name == strplid)
				{
					r.Stroke = Brushes.LimeGreen;
					r.Fill = Brushes.LimeGreen;
					r.Height = heightpl;
					break;
				}
			}
			return;
		}

		void SetPLIDkeel( int PLID )
		{
			string strplid = "k" + PLID;
			foreach (UIElement x in cnvPLB.Children)
			{
				Rectangle r = x as Rectangle;
				if (r == null) continue;

				if (r.Name == strplid)
				{
					r.Stroke = Brushes.LimeGreen;
					r.Fill = Brushes.LimeGreen;
					r.Height = heightpl;
					Canvas.SetTop( r, ykeel - 5 );
					break;
				}
			}
			return;
		}

		private void CommandBinding_Executed( object sender, ExecutedRoutedEventArgs e )
		{
			Close();
			return;
		}
	}
}
