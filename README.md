![SSV logo](./Doc/Space%20Shuttle%20Vessel/Images/logo1000.png)

# Space Shuttle Vessel
Space Shuttle Vessel (SSV) is an addon for Orbiter Space Flight Simulator (http://orbit.medphys.ucl.ac.uk/). The purpose of this addon is to simulate NASA’s Space Transportation System Program as much as possible. Currently only some elements have been completed and work on others is ongoing.

This release of SSV is for use in Orbiter 2016.


# Installation
1. Install Orbiter.

2. Install the required addons:

	OrbiterSound 4.0 or 5.0 (http://orbiter.dansteph.com/forum/index.php?page=download)

	Antelope Valley scenery pack (http://orbit.medphys.ucl.ac.uk/mirrors/orbiter_radio/tex_mirror.html)

3. Extract the files into your Orbiter installation folder, overwriting any existing files.
WARNING: The SSV installation overwrites the default Base.cfg and Earth.cfg files.

4. Install the "SSV_Font_A" and "SSV_Font_B" fonts, located in the "<Orbiter installation>\Install\Space Shuttle Vessel" directory, by opening them and selecting "Install". After successful installation the files can be deleted.

5. The displays in SSV require the MFD resolution of 512 x 512 (Orbiter Launchpad > Extra > Instruments and panels > MFD parameter configuration > MFD texture size).

NOTE: If you encounter the error "msvcp140.dll is missing" you need to download the Microsoft Visual C++ Redistributable for Visual Studio 2017.


## Optional addons
For a better visual experience, using the D3D9 graphics client (http://users.kymp.net/~p501474a/D3D9Client/) is strongly recommended, although not required. If using the D3D9 graphics client, the "Disable near clip plane compatibility mode" option in the D3D9 Advanced Setup dialog (Orbiter Launchpad > Video > Advanced) should be checked.

For an accurate rendezvous profile simulation, it is recommended the installation of the excellent Shuttle FDO MFD (https://github.com/indy91/Shuttle-FDO-MFD) by indy91, which handles the ground based calculations required for rendezvous.


# Credits
Space Shuttle Vessel is based on revision 3242 of Space Shuttle Ultra (svn://orbiter-radio.co.uk/shuttleultra).

The SSV vessels load JSON files with cJSON library by Dave Gamble and cJSON contributors (https://github.com/DaveGamble/cJSON), included in the code. The Mission Editor loads and saves JSON files with Json.NET by James Newton-King (https://www.newtonsoft.com/json).

Large parts of the launch autopilot were copied (with minor modifications) from PEG MFD.

Some of the attitude control code was derived from Attitude MFD V3.

SSV uses the KOST library.

Vandenberg base uses part of the VandenbergAFB-2006 addon (https://www.orbiter-forum.com/resources/vandenbergafb-2006.3523/) by Usonian.

The SurfaceRoving class is based on the GeneralVehicle addon (https://www.orbiter-forum.com/resources/generalvehicle.3158/) by Fred18.

The file "circuit_breaker.wav" comes from Project Apollo - NASSP (https://github.com/orbiternassp/NASSP).


# License
This addon is open-source and is released under the GNU GPL v2 (see file [SSV-LICENSE.txt](SSV-LICENSE.txt) for details).


# Disclaimer
The SSV team is not responsible for any crashes or other problems caused by this addon. Use at your own risk.
