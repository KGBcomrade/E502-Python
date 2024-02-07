#ifndef ADCDOCSTRINGS_H
#define ADCDOCSTRINGS_H
PyDoc_STRVAR(adcSetChannelCountDoc, "Sets the number of logical channels for an ADC.\n"
			            "Args:\n"
				    "	n (int): the number of logical channels.\n"
				    "Don't forget to apply adc.configure() after setting up an ADC.");
PyDoc_STRVAR(adcSetChannelDoc, "Sets a logical channel\'s physical number, mode, range and averaging.\n"
			       "Args:\n"
			       "   lChannel (int): number of logical channel to set up\n"
			       "   pChannel (int): number of physical channel\n"
			       "   mode ({\'comm\', \'diff\', \'zero\'}): mode of logical channel.\n"
			       "        \'comm\': Common ground measurement\n"
			       "        \'diff\': Differential measurement\n"
			       "        \'zero\': Zero measurement\n"
			       "   range ({0.2, 0.5, 1, 2, 5, 10}): measurement range in volts.\n"
			       "   avg (int): averaging coefficient. If zero, sets to default.\n"
			       "Don't forget to apply adc.configure() after setting up an ADC.");
PyDoc_STRVAR(adcSetFreqDoc, "Sets an ADC's acquisition frequency to the closest to the given one.\n"
			    "Args:\n"
			    "   freq (float): desired frequency of data acquisition.\n"
			    "   freq_c (float, optional): desired frame acquisiton frequency. By defaults, set the maximal possible one.\n"
			    "Returns:\n"
			    "   freq (float): actual data acquisition frequency set.\n"
			    "Don't forget to apply adc.configure() after setting up an ADC.");
PyDoc_STRVAR(adcConfigureDoc, "Apply configuraions setted up by setChannelCount, setChannel, setFreq methods for an ADC.");
PyDoc_STRVAR(adcAsyncGetFrameDoc, "Makes single frame acquisition. Time delay between differrent frames acquired with this function can not be defined."
			       "To be performed, stream input must be disabled (see setStreamsEnabled method).\n"
			       "Args:\n"
			       "   volts (boolean, optional): if True, provides output in volts. Defaults to True.\n"
			       "   timeout (int, optional): performing timeout. Defaults to 1000.\n"
			       "Returns:\n"
			       "   out (list of floats): measured voltage values for specified logical channels.");
PyDoc_STRVAR(adcStreamsSetEnabledDoc, "Allows/disables stream data input.\n"
				   "Args:\n"
				   "   enabled (bool): if True, enables stream data input. If False, disables.");
PyDoc_STRVAR(adcStreamsStartDoc, "Starts stream data input. Needs stream data input to be enabled (see setStreamsEnabled method).");
PyDoc_STRVAR(adcStreamsStopDoc, "Stops stream data input.");
PyDoc_STRVAR(adcSyncGetFrameDoc, "Reads acquired data from buffer. Needs stream data input to be started (see startStreams method).\n"
			      "Args:\n"
     		              "   volts (boolean, optional): if True, provides output in volts. Defaults to True.\n"
     		              "   timeout (int, optional): performing timeout. Defaults to 1000.\n"
     		              "Returns:\n"
     		              "   out (list of floats): measured voltage values for specified logical channels.");
#endif
