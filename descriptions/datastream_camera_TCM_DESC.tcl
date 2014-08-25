set DATASTREAM_DESC(camera_TCM) "Directly beneath each packaged CCD module is a Front End Electronics Module (FEM) containing the following functionality.
<P><UL><LI>Analog signal processing ASIC
<LI>CCD clock drivers, ASIC or hybrid
<LI>Bias voltage dsitribution
</UL>This architecture minimizes the physical distance from CCD output amplifiers to the analog signal processing circuits, thus minimizing power dissipation and risk of noise pickup. The CCD clock drivers are assumed to be simple level translators, with no pattern generation at this point. Beyond generating clock signals, there is no digital activity at this level. All analog signals  are buffered and fully differential for purposes of noise immunity. Similarly, all timing signals comply with the Low Voltage Differential Signaling (LVDS) standard. Both the clock drivers and the bias generators will be programmable by means of a slow serial link."
