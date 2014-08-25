
set SYSDIC(systems) "auxscope calibration camera dm enclosure environment hexapod lasercal m1m3 m2 mount network operations power scheduler seeing skycam system tcs"
foreach s $SYSDIC(systems) {set SYSDIC($s,type) system}

set SYSDIC(datatypes) "byte short int long float string int64 double ubyte ushort uint ulong"

set TSYSDIC(subsystems) "<H2>Appendix A - System Dictionary</H2><P>
<H2>Contents : </H2>
<UL>
<H3>Introduction</H3>
<H3>Systems and Subsystems</H3>
<H3>Devices</H3>
<H3>Properties</H3>
<H3>Actions</H3>
<H3>Units</H3>
</UL><P><HR><P>
<H2>Introduction</H3>
<P>
This document describes the keywords used to refer to items in the
Service Abstraction Layer (SAL) mediated services. e.g. Subsystem Telemetry. 
<P>
The approved names for all subsystems, components, devices, actions, 
are defined in this dictionary. SAL generated code is validated against
the dictionary to ensure system wide consistency.
<P>
The dictionary will evolve as the individual subsystem descriptions
are completed to increasing levels of detail.
<P>
<H2>Systems and Subsystems</H2><P>"

set SYSDIC(subsystems) "auxscope - Auxiliary telescope
auxscope.Application - Derived metadata
auxscope.Electrical - Electrical system monitoring
auxscope.Metrology - Positional information
auxscope.TC - Thermal monitoring
auxscope.Camera - Imaging system
auxscope.Enclosure - Dome and vents
auxscope.Environment - Environmental monitoring
auxscope.Optics - Mirror support system
auxscope.Mount - Alt/az/rotr control
auxscope.Power - Power conditioning and monitoring
auxscope.Spectrometer - Spectroscopic instruments
auxscope.TCS - Pointing and control system
calibration - Calibration subsystem
calibration.Application - Derived metadata
calibration.Electrical - Electrical system monitoring
calibration.Metrology - Positional information
calibration.TC - Thermal monitoring
calibration.imager - Test/Commissioning camera
calibration.sources - Vis/IR calibration devices
calibration.mirror - Calibration source selection
camera - Camera sub-systems (* items not confirmed)
camera.BEE - Back-end electronics
camera.CALSYS - Calibration system
camera.CCC - Camera control system
camera.CCS - Camera control system
camera.Cluster - Camera control system
camera.Prot - Lens protection system*
camera.FCS - Filter control system
camera.Filter - Filter control system
camera.FEE - Front-end electronics
camera.PCMS - Front-end electronics
camera.FEE - Front-end electronics
camera.PWR - Power supplies
camera.Power - Power supplies
camera.GDS - Guide sensors
camera.LASERCAL - Lens monitoring and metrology*
camera.QA - Data quality
camera.RAS - Raft Alignment system
camera.RNA - Raft controller
camera.SAS - Science Array
camera.SDS - Science Data System
camera.SCS - Shutter controller
camera.Shutter - Shutter controller
camera.TC - Temperature management
camera.Cold - Temperature management, BEE cold plate
camera.Cryo - Temperature management, Camera body
camera.T4U - Temperature management, Utility trunk
camera.T5S - Temperature management, cooling
camera.T6U - Temperature management, transport
camera.TCM - Timing and control module
camera.TC - Thermal control
camera.Purge - Vacuum control
camera.VCS - Vacuum control
camera.UTIL - Utility trunk
camera.WAS - Wavefront data acquisition
camera.WDS - Wavefront data system
camera.WFS - Wavefront sensing system
camera.WTCM - Wavefront sensors timing control
camera.XCAL - Sensor calibration system*
dm - Data management subsystems
dm.derived - Derived data quality
dm.ALERT - Alert events
dm.DB - Database statistics
dm.DQR - Raw data quality assessments
dm.DQS - Science data quality assessments
dm.pointing - Astrometry calibrations
dm.WCS - Astrometry calibrations
dm.raw - Raw metrics
dm.PIPE - Pipeline statuses
enclosure - Dome mechanisms
enclosure.Application - Derived metadata
enclosure.Electrical - Electrical system monitoring
enclosure.Metrology - Positional information
enclosure.Azimuth - Dome rotation
enclosure.Crane - Camera handling system
enclosure.Environment - Dome environmental sensing
enclosure.Liftplatform - Mirror handling system
enclosure.Shutter - Dome aperture control
enclosure.TC - Temperature control systems
enclosure.Vents - Dome vents and air-flow management
environment - Environmental monitoring
environment.Dust - Particulate monitoring
environment.Electrical - Electrical system monitoring
environment.Lightning - Electrical disturbance monitoring
environment.Seismometer - Earthquake monitoring
environment.TC - Temperature control systems
environment.Weather - Local weather sensing
environment.Video - Local video cameras
hexapod - Hexapod/Rotator subsystem
hexapod.Application - Derived metadata
hexapod.Actuators - Position control systems
hexapod.Electrical - Power monitoring
hexapod.LimitSensors - Position monitoring/control
hexapod.Metrology - Position monitoring/control
hexapod.TC - Thermal monitoring/control
lasercal - Laser calibration system
lasercal.Application - Derived metadata
lasercal.Electrical - Electrical system monitoring
lasercal.TC - Temperature control systems
m1m3 - Primary/Tertiary mirror
m1m3.Application - Derived metadata
m1m3.Actuators - Figure control systems
m1m3.ActuatorSample - Figure control systems
m1m3.Electrical - Power monitoring
m1m3.LimitSensors - Position monitoring/control
m1m3.LUT - Look-up tables
m1m3.Metrology - Position monitoring/control
m1m3.Supports - Mirror/Mount interface
m1m3.Surface - Figure monitoring
m1m3.TC - Thermal monitoring/control
m2 - Secondary mirror
m2.Application - Derived metadata
m2.Actuators - Figure control systems
m2.Electrical - Power monitoring
m2.Hexapod - Hexapod monitoring
m2.LimitSensors - Position monitoring/control
m2.LUT - Look-up tables
m2.Metrology - Position monitoring/control
m2.Supports - Mirror/Mount interface
m2.Surface - Figure monitoring
m2.TC - Thermal monitoring/control
m2.Temps - Thermal monitoring/control
mount - Telescope mount
mount.Az - Azimuth axis monitoring/control
mount.Alt - Altitude axis monitoring/control
mount.Balance - Balance tuning mechanisms
mount.Hexapod - Camera mount monitoring/control
mount.Rotator - Camera mount monitoring/control
mount.Metrology - Configuration/Position/Velocity monitoring
mount.Application - Derived metadata
mount.Electrical - Electrical system monitoring
mount.Mirror_cover - Mirror covers
mount.Power - Monitoring/control of power management
mount.Services - Monitoring/control of N2/Vac/Coolant etc
mount.TC - Thermal monitoring/control
network - Computer network hardware
network.Application - Derived metadata
network.Camera - Camera specific
network.External - Links off-mountain
network.Noncritical - Non mission critical
network.Science - Science data networks
network.Telescope - On-site telescope and site
ocs - observatory control system
ocs.activity - observatory operational modes
ocs.database - observatory facility database
ocs.operator - Operator interfaces management
ocs.pointing - Telescope pointing
ocs.scheduler - observatory scheduling
ocs.staticanalysis - Debugging information
ocs.system - system overview
operations - Operator interfaces management
operations.main - Main telescope control
operations.base - Base control room
operations.cameralab - Camera checkout area
operations.enclosure - Dome floor
operations.mirrorlab - Mirror Lab and coating
operations.remote - WAN access
power - Power supply systems
power.Electrical - Electrical monitoring
power.Noncritical - Other power systems
power.Main - Main power monitoring/control , mission critical
power.TC - Thermal monitoring/control
power.UPSs - Uninterruptible power supplies
scheduler - Observation scheduling subsystem
scheduler.Application - Derived metadata
seeing.dimm - DIMM Seeing monitor system
seeing.dimm.Application - Derived metadata
seeing.dimm.Electrical - Electrical system monitoring
seeing.dimm.Metrology - Positional information
seeing.dimm.TC - Thermal monitoring
seeing.dimm.Imager - Sensor configuration and readout
seeing.dimm.Policy - Configuration and operations
seeing.dimm.Status - Summary data
seeing.dimm.Telescope - Telescope mount control
seeing.mass - MASS Seeing monitor system
seeing.mass - DIMM Seeing monitor system
seeing.mass.Application - Derived metadata
seeing.mass.Electrical - Electrical system monitoring
seeing.mass.Metrology - Positional information
seeing.mass.TC - Thermal monitoring
seeing.mass.Imager - Sensor configuration and readout
seeing.mass.Policy - Configuration and operations
seeing.mass.Status - Summary data
seeing.mass.Telescope - Telescope mount control
skycam - All-sky monitoring cameras
skycam.Application - Derived methistory

adata
skycam.Electrical - Electrical system monitoring
skycam.Metrology - Positional information
skycam.TC - Thermal monitoring
skycam.Imager - Sensor configuration and readout
skycam.Policy - Configuration and operations
skycam.Status - Summary data
system - System configuration/history/status interfaces
system.Command  - Comprehensive command log
system.Computer - Per-computer status
system.Hardware - Modification logs
system.Software - Modification logs
tcs - Telescope control system
tcs.kernel - Telescope pointing kernel
tcs.mount - Mount interface
tcs.optics - Active optics interface"

foreach i [split $SYSDIC(subsystems) "\n" ] {
   set t [split $i "-"]
   set ss [string trim [lindex $t 0]]
   set title [string trim [lindex $t 1]]
   set SYSDIC($ss,title) $title
}

set TSYSDIC(devices) "<P><HR><P>
<H2>Devices</H2><P>	
Devices may occur in multiple instances in a particular system or subsystem, <P>
e.g.	camera.Raft.RNA5 , <BR>
	m1m3.actuators.actuator200
<P>"

set SYSDIC(devices) "Actuator - Mirror support structures
Accelerometer - Motion detector
AC - Air conditioning unit
Alt - Altitude axis motion
A2D - Analog-digital converter
Application - Software component
Az - Azimuth axis motion
Brake - Motion damping mechanism
Calib_Lamp - Calibration lamps
Clamp - Motion prevention/protection mechanism
Command_history - Software component
Computer_status - Computer hardware components
Dome_Az - Dome azimuth axis motion
Dome_Shutter - Dome slit position motion
Dust_monitor - Dust monitoring devices
Electrical - Voltage and power consumption monitors
Fan - Air circulation mechanism
Filter - Filter positioning devices
Firmware - On-board flash memory device / EPROM
Fuse_Sensor - Overcurrent sensor mechanism
GuideStars - Camera guide sensor devices
Hand_Paddle - Operator hand paddle devices
Hardware_revision - Hardware component
Hexapod - Camera mount motion
Image - CCD Camera or imaging sensor
Lens_Cover - Camera lens protection mechanisms
Lightning_detector - Lightning detection devices
Limit_Sensor - Limit of motion detection mechanism
Metrology - Position monitoring devices
Mirror - Beam steering / fold mirrors
Mirror_Cover - Mirror cover actuators and monitors
Network_Switch - Computer network switch/router/hub
O2_Sensor - Oxygen sensor
Raft - Camera sensor raft subsystems
RNA - Camera sensor raft network adaptor
Rotator - Camera rotator mechanism
Science_sensor_metadata - Camera sensor performance
Seismometer - Seismic activity monitor
Servo_motor - Servo motor
Shutter - Dome shutter mechanism
Software_revision - Software component
Spectrometer - Calibration telescope spectrograph
Status - Generic virtual device to query status
Stepper_motor - Stepper motor
Support - Device support structures
Surface - Mirror surface control and monitoring
Temp - Temperature monitoring devices
UPS - Power management device
Vents - Dome vent control
Video_camera - Video camera subsystems
Weather - Weather monitoring devices and services
wfsRaft - Wavefront sensor raft
Wiper - Camera calibration source positioner"

set TSYSDIC(properties) " <P><HR><P>
<H2>Properties</H2>
<P>
Each device in a system or subsystem may have many different
properties associated with it. Properties are used for both
control and monitoring purposes.  ie Some properties may be
controlled; others may only monitored. In general, if a property can
be controlled there should also be another  item to allow monitoring so
that both the target and actual properties are logged.<P>"

set SYSDIC(properties) "acceleration - meters/second/second or steps/second/second
active - boolean state true/false
aborted - boolean state true/false
algorithm - software algorithm name
angle - in degrees
author - Name of a software author
bandwidth - of network links (bps, Mbps)
biasvoltage - ccd bias
blobtype - datatype for large vector/image/other objects
brightness - in lumens (?)
certificate - sofware security certificate
checksum - software check value
clamped - boolean state true/false
clockfreq - ccd clock frequency
cpu - manufacturer-architecture-revision
credential - software security credential
current - in amps, milli/micro
deadband -
declination - in ddd:mm:ss.sss
deceleration - meters/second/second or steps/second/second
delay - in seconds, milli/micro
demand - in amps, milli/micro
diq - Delivered image quality (metric TBD)
distance - in meters , centi/milli/micro
email - an email address
encoder - in raw counts
encoder_constant - in raw counts
epoch - yyyy.xxxxxxxx
equinox - yyyy.xxxxxxxx
errcode - a compact error code
errtext - a human readable error message
failure - boolean state true/false
filter_name - Comprehensive descriptor
filter_response - Filter response curve
focus - in microns
force - in Newtons
function - F(x) - Name of function
frequency - in Hz
fwhm - in arcseonds / pixels
gain - dimensionless multiplier
ha - Hour angle in hh:mm:ss.sss
index - integer enumerator
interface - Standard name
interlock - boolean state true/false
interpolator - Name of function
interval - integer value
ip4addr- an IP4 address
ip6addr - an IP6 address
jogspeed - arcsec per sec
load_cell - pressure in psi
load_limit - in psi
load_range - in psi
lvdt - load cell reading, raw data
macaddr - a network device MAC address
maximum - any numeric type
md5sum - software check value
memory - in kb, Mb, Gb
minimum - any numeric type
model - name of model (mathematical)
moving - boolean state true/false
motion_profile - vector tracking state of a moving device
motor_ratio - dimensionless multiplier
motor_steps - steps per revolution
name - Descriptive
offset - in arcseconds
parclock - ccd parallel clockin
pager - a pager number
period - in seconds
permission - software access credentials (r/w/e/d/c etc)
phone - a telephone number
position - Descriptive, may be numerical
power - boolean state true/false
pressure - in psi
ra - Right Ascension in hh:mm:ss.sss
regulated - boolean state true/false
resolution - in milli/micro/nano meters
revision - Software/Hardware code
retries - retry count, number of attempts allowed
retry - boolean state true/false
scale - dimensionless multiplier
serclock - ccd serial clocking
severity - a severity indication for a warning/error condition
simulator - boolean state true/false
speed - in meter/second
state - Descriptive (may be limited to a set)
status - Descriptive (may be limited to a set)
stepper - stepper motor count
stepper_accel - acceleration in steps/sec/sec
stepper_power - current in amps
stepper_speed - steps/second
storage_capacity - in kb/Mb/Gb/Tb
success - boolean state true/false
temperature - in degrees C/K
threshold - dimensionless numeric
tolerance - dimensionless numeric
torque -
track - boolean state true/false
update - boolean state true/false
uri - universal resource identifier
username - login credential
vacuum - in tor (?)
velocity - in meters/second
voltage - in volts, milli/micro
wavelength - in Ang.,
width - dimensionless numeric
x - dimensionless numeric
y - dimensionless numeric
z - dimensionless numeric
zn - zernicke polynomial coefficients
zd - zenith distance - in degrees"


set TSYSDIC(actions) "<P><HR><P>
<H2>Actions</H2><P>
Every subsystem supports a set of commands which can be
issued by clients. Each command may optionally include one of the 
following actions, and may optionally include a set of action
specific operators to refine the request."

set SYSDIC(actions) "abort - immediate cessation of a specific command
ack - acknowlege receipt of external command
adjust - modify numeric parameter
arm - prepare a mechanism for motion
backup - save subsystem state
begin - start a cyclical activity
busy - an action state
cancel - cancel a command before it executes
capture - initiate data capture
center - move a mechanism to mid-range
clear - cancel all queued commands
close - close a mechanism (cover, shutter etc)
configure - loads a predefined configuration
continue - resume a paused command
delete - remove a queued command
disable - accept no more commands (except enable)
disarm - cancel an arming command
disengage - unlock a mechanism
done - an action state
dump - dump memory
enable - enable regular commanding
end - terminate a cyclical operation
engage - lock a mechanism
erase - clear memory
error - an action state
execute - execute a queued command
failed - an action state
free - free allocated buffers
go - initiate a prepared motion
index - move to an index mark
initialize - prepare a mechanism for use
insert - move component into operational location
install - software update
kill - immediately power down a component
mark - remember current location
maximize - maximize a tunable parameter
minimize - minimize a tunable parameter
move - generic motion command
off - generic state command
on - generic state command
open - open a mechanism (cover, shutter etc)
pause - temporarily pause queued commands
query - inquire command status
quit - exit from a series of queued commands (loop)
reboot - restart a computer/embedded system
remove - remove a command from a queue
reset - generic state command
restart - generic state command
restore - recover memory contents
resume - resume a paused command queue
save - snapshot subsystem state
select - generic state command
send - transmit data packet
set - generic state command
show - generic state command
start - generic state command
status - inquire component status
stop - generic state command
suspend - interrupt a command (may be resumed)
trigger - launch a previously armed operation"

set TSYSDIC(units) "<P><HR><P>
<H2>Units</H2><P>"

set SYSDIC(units) "amps - amperes of electrical current (SI unit)
angstroms - wavelength 1A = 0.1nanometers
ampere - electrical current (SI unit)
arcsecs - 1/3600 of a degree
btus - British thermal unit of energy
centimeters - 1/100 meter
coulombs - amount of charge displaced by a 1amp current in 1 second
counts - dimensionless
cycles - no of repeats of an operation
days -time
degrees - in Centigrade or Kelvin
dynes - unit of force , 1dyne = 10 micronewtons (cgs unit)
gauss - magnetic field of 1 maxwell per sq centimeter (cgs unit)
gb - Gigabytes 1024^3 for memory (1e9 bytes otherwise)
gbps - Gigabits per second
grams - 1/1000 kilogram
hertz - cycles per second
hours - time
joules - unit of force/energy , 1joule = 1 Newton-meter
kelvin - temperature (SI unit)
kilograms - mass (SU unit)
kilometers - 1000 meters
mb - Megabytes 1024^2 for memory (1e6 otherwise)
mbps - Megabits per second
meters - length (SI unit)
microns - 1/1000000 meter
microradians - ratio between the length of an arc and its radius.
milliarcs - 1/3600000 of a degree
millimeters - 1/000 meter
minutes - time
months - time
newtons - 1N= force required to acc 1kg mass at a rate of 1m/s/s
ohms - unit of electrical resistance
pascals - 1 pascal = 1 newton per square meter or one Joule per cubic meter.
radians - ratio between the length of an arc and its radius.
rpm - revolutions per minute
seconds - time
steps - of a stepper motor
volts - 1V = one joule of energy per coulomb of charge (SI derived)
watts - 1W = one joule of energy per second (SI derived)
years -time"

proc add_system_dictionary_appendix { fout } {
global TSYSDIC SYSDIC
   foreach section "subsystems devices properties actions units" {
      puts $fout $TSYSDIC($section)
      puts $fout "<P><UL>"
      foreach i [split $SYSDIC($section) \n] {
         puts $fout "<B>[lindex $i 0]</B>[lrange $i 1 end]<BR>"
      }
      puts $fout "</UL><P>"
   }
}








