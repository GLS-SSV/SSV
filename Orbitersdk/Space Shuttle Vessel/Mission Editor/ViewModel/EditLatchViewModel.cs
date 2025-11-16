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

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Windows;

namespace SSVMissionEditor.ViewModel
{
	class EditLatchViewModel : INotifyPropertyChanged
	{
		/// <summary>
		/// type:
		/// 0 = Active
		/// 1 = Passive
		/// 2 = SPDS pedestal
		/// 3 = SPDS PRLA
		/// </summary>
		public EditLatchViewModel( int type, bool keel, int[] PLID_nom_src, int[] PLID_rev_src )
		{
			this.PLID_nom_src = PLID_nom_src;
			this.PLID_rev_src = PLID_rev_src;
			Update_PLID_src();

			HasAttachmentOption = Visibility.Visible;
			HasReversedOption = Visibility.Visible;
			HasLatchOption = Visibility.Visible;
			HasGuidesOption = Visibility.Visible;
			switch (type)
			{
				case 0:// Active
					if (keel)
					{
						// keel
						// hide unneeded controls
						HasReversedOption = Visibility.Hidden;
						HasGuidesOption = Visibility.Hidden;
					}
					break;
				case 1:// Passive
					if (keel)
					{
						// keel
						// hide unneeded controls
						HasReversedOption = Visibility.Hidden;
					}

					// hide unneeded controls
					HasLatchOption = Visibility.Hidden;
					HasGuidesOption = Visibility.Hidden;
					break;
				case 2:// SPDS pedestal
					// hide unneeded controls
					HasAttachmentOption = Visibility.Hidden;
					HasLatchOption = Visibility.Hidden;
					HasGuidesOption = Visibility.Hidden;
					break;
				case 3:// SPDS PRLA
					if (keel)
					{
						// keel
						// hide unneeded controls
						HasReversedOption = Visibility.Hidden;
					}

					// hide unneeded controls
					HasAttachmentOption = Visibility.Hidden;
					HasLatchOption = Visibility.Hidden;
					HasGuidesOption = Visibility.Hidden;
					break;
			}
			return;
		}

		public static string[] Latch_src{ get; } = { "P/L 1 Latch 1", "P/L 1 Latch 2", "P/L 1 Latch 3", "P/L 1 Latch 4", "P/L 1 Latch 5", "P/L 2 Latch 1", "P/L 2 Latch 2", "P/L 2 Latch 3", "P/L 2 Latch 4", "P/L 2 Latch 5", "P/L 3 Latch 1", "P/L 3 Latch 2", "P/L 3 Latch 3", "P/L 3 Latch 4", "P/L 3 Latch 5" };

		private int latch;
		public int Latch
		{
			get { return latch; }
			set
			{
				latch = value;
				OnPropertyChanged( "Latch" );
			}
		}

		private void Update_PLID_src()
		{
			List<string> PLID_src_tmp = new List<string>();

			int[] tmp = Reversed ? PLID_rev_src : PLID_nom_src;
			foreach (int x in tmp)
			{
				PLID_src_tmp.Add( x + " (Xo" + Defs.PLID_Xo[x - Defs.PLID_Xo_base] + ")" );
			}

			PLID_src = PLID_src_tmp;

			PLID_idx = 0;
			return;
		}

		private readonly int[] PLID_nom_src;
		private readonly int[] PLID_rev_src;

		public int PLID
		{
			get
			{
				int[] plids = Reversed ? PLID_rev_src : PLID_nom_src;
				if ((PLID_idx < 0) || (PLID_idx >= plids.Length)) return plids[0];
				return plids[PLID_idx];
			}
			set
			{
				if (value == 0) PLID_idx = 0;
				else
				{
					int[] plids = Reversed ? PLID_rev_src : PLID_nom_src;
					int i = Array.FindIndex( plids, item => item == value );
					PLID_idx = i;
				}
			}
		}

		private int plid_idx;
		public int PLID_idx
		{
			get { return plid_idx; }
			set
			{
				plid_idx = value;
				OnPropertyChanged( "PLID_idx" );
			}
		}

		private List<string> plid_src;
		public List<string> PLID_src
		{
			get { return plid_src; }
			set
			{
				plid_src = value;
				OnPropertyChanged( "PLID_src" );
			}
		}

		private bool reversed;
		public bool Reversed
		{
			get { return reversed; }
			set
			{
				reversed = value;
				Update_PLID_src();
				OnPropertyChanged( "Reversed" );
			}
		}

		private bool attachment;
		public bool Attachment
		{
			get { return attachment; }
			set
			{
				attachment = value;
				OnPropertyChanged( "Attachment" );
				OnPropertyChanged( "Attachment_ena" );
			}
		}

		public bool Attachment_ena
		{
			get { return !attachment; }
		}

		private int fwdguide;
		public int FwdGuide
		{
			get { return fwdguide; }
			set
			{
				fwdguide = value;
				OnPropertyChanged( "FwdGuide" );
			}
		}

		private int aftguide;
		public int AftGuide
		{
			get { return aftguide; }
			set
			{
				aftguide = value;
				OnPropertyChanged( "AftGuide" );
			}
		}

		/// <summary>
		/// List of Guides options.
		/// </summary>
		public static string[] Guides_src{ get; } = { "None", "22''", "24''" };

		/// <summary>
		/// Has Attachment option.
		/// </summary>
		public Visibility HasAttachmentOption { get; }

		/// <summary>
		/// Has Reversed option.
		/// </summary>
		public Visibility HasReversedOption { get; }

		/// <summary>
		/// Has Latch option.
		/// </summary>
		public Visibility HasLatchOption { get; }

		/// <summary>
		/// Has Guides option.
		/// </summary>
		public Visibility HasGuidesOption { get; }


		public event PropertyChangedEventHandler PropertyChanged;
		private void OnPropertyChanged( string prop )
		{
			PropertyChanged?.Invoke( this, new PropertyChangedEventArgs( prop ) );
			return;
		}
	}
}
