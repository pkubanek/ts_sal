set DATASTREAM_DESC(camera_TC_control) "The Thermal Control (TCS) manager software controls temperature in multiple thermal zones in the focal plane, cryostat, and camera body.  Feedback control is based on trim heaters for actuation and temperature sensors for readback.<P>
<P>Temperature monitoring  for sensors located in the camera
subsystem.<BR>Raw sensor readings, calibrated temperatures,
timeseries statistics, sensor health.
<P>
The basic requirement of the Camera Thermal Comtrol System is to allow the solidstate
detectors that form the Focal Plane Array (FPA) to operate at ~ 170K to reduce the contribution of thermal noise to the electronic signals while in parallel optimizing
quantum efficiency (QE). The thermal gradient across the sensors must also be adequately
reduced (±0.30K) to maintain uniform quantum efficiency in each pixel. For efficient camera
operation, thermal stability of the FPA is necessary to maintain optical sensor performance as well as to eliminate the growth of mechanical distortions to the FPA, once it is aligned. 
<P>
The additional functions of the thermal control system are to provide a particulate free environment for the sensor surfaces, heat extraction from both the front end and back end electronics systems, and antifog protection for the three optical elements.   The camera is composed of a cryostat containing the FPA and its readout electronics and an outer camera body which houses the cryostat, shutter, L2 optic, and the five filters and filter exchange mechanism. The cryostat is closed by the L3 optic and the outer camera body by the L1 optic. The cryostat is operated at ~10e-6 Torr vacuum while the region between the cryostat and outer body will contain an inert gas (eg: dry nitrogen will be assumed) regulated to be slightly above atmospheric pressure. The temperature of the N2 gas will be controlled to maintain a stable thermal envelope. The other important role of the inert gas is to prevent degradation of the filter coatings.
<P>
Components: 
Off Camera: flex line umbilicals; chillers, auxiliary pumps, reservoirs, purge system, plumbing systems,
sensors and flow meters, local operator's terminal, vacuum system for insulating vacuum, racks, consoles.<P>
Requirements:
<P>
Control temperature to derived requirement below 3oC<BR>
Log temperatures, heater current for all 189 sensor thermal zones<BR>
Monitor temperature stability over time<BR>
Graph temperatures and heater current vs time for trending analysis<BR>
Graphically map temperatures of all Grid bays<BR>
Send caution signal if dTemp/dTime approaches limits<BR>
Send warning signal if dTemp/dTime exceeds limits<BR>
Override of over/undertemp caution and warning alarms<BR>
Change/store/download temp setpoints and limits for all control zones<BR>
Save configurations of heater power for different operating scenarios<BR>
Log temperatures, heater current for all thermal plates<BR>
Graph temperatures and heater current vs time for trending analysis<BR>
Graphically map temperatures and heater current of all Grid bays<BR>
Override of over/undertemp caution and warning alarms<BR>
Change/store/download heater current setpoints for all control zones<BR>
Provide manual realtime adjustment of individual heater currents<BR>
Save configurations of heater current for different operating scenarios <BR>
Log temperatures, heater current for all Cold Plate, BEE boards, cryogen line inlets/outlets<BR>
Graph temperatures and heater current vs time for trending analysis<BR>
Graphically map temperatures and heater current of all BEE module locations<BR>
Override of over/undertemp caution and warning alarms<BR>
Temperatures from Cold Plate thermal zone can be combined with all other thermal data<BR>
Change/store/download heater current setpoints for all control zones<BR>
Provide manual realtime adjustment of individual heater currents<BR>
Save configurations of heater current for different operating scenarios<BR>
"
