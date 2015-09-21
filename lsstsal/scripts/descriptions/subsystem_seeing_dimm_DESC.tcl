set SUBSYSTEM_DESC(seeing_dimm) "Seeing canmera, differential image motion monitor<P>
The first DIMM was developed by M. Sarazin and F. Roddier (Sarazin, M., Roddier, F., The ESO differential image motion monitor, 1990, Astron. Astrophy. 227, 294). Refer to this paper for more complete information, especially on the theory.
<P>
Image quality through a telescope is directly related to the statistics of the perturbations of the incoming wavefront. The DIMM method consists of measuring wavefront slope differences over 2 small pupils some distance apart. Because it is a differential method, the technique is inherently insensitive to tracking errors and wind shake. In practice, starlight goes through 2 small circular subapertures, cut in a mask placed at the entrance of a small telescope. One of the subapertures contains a prism in order to create a second image of the star on the detector. The dual star images obtained exhibit a relative motion in the image plane that represents the local wavefront tilts, which can be expressed in terms of an absolute seeing scale 
<P>Sources of error:<BR>
Pixel scale: the FWHM varies as the 6/5 power of the standard deviation of the motion, which is measured in fractions of pixels. The pixel angular scale is determined typically with a 1% accuracy, leading to a 1.2% error in the FWHM.
<P>
Instrumental noise: the accuracy of the centroid algorithm, measured in laboratory on 2 fixed spots, corresponds to an equivalent random error of about 0.03 arcsec rms.
<P>
Statistical errors: it decreases with the square root of the sampling (number of images used). In our case, the variance of image motion is obtained from typically 250 short exposures per minute in each direction (i.e.. 500 in total), which leads to an accuracy of 3.8% in the image size.
<P>
Exposure time: the error caused by the finite exposure time is minimized by using very short exposures that can freeze the motion of the atmosphere in most conditions. We implemented the 5ms to 10ms (the minimum CCD frame transfer time is 1ms) interleaving technique and calculate (and log) the extrapolated seeing for a virtual integration time of 0ms (we know from ESO that 5ms is freezing the image motion 99% of the time in Chilean sites)."
