#!/usr/bin/python


# Script for SALData_SALTopic example.  Use OpenSplice's example SALData_SALTopic
# Subscriber to receive the sample.
import os
import sys
import logging
import time

sys.path.append("SAL_WORK_DIR/scripts/code/python/PyDDS/"")
from ddswrapper import *

# use the lowest logging level since we are developing
logging.basicConfig(level = logging.INFO)
logging.info("Get an instance of the TxPyDDS::Runtime...")

# Idl File and Topic name being used
idlFilePath = os.getcwd() + "/SALDATA.idl"
topicName = "SALData"

# Set up PyDDS environment
pydds = PyDDS.PyDDS()
ddsLogger = logging.getLogger("PyDDS")
pydds.setLogger(ddsLogger)

try:
    logging.info("Create a new DomainParticipant...")
    dp = pydds.create_participant("")
except PyDDSWrapper.InvalidHandle as ex:
    logging.error("Caught TxPyDDS::InvalidHandle exception"
                  " when creating domain participant\n" 
                  "Is the OSPL daemon running?\n" 
                  "From:" + ex.what())
    exit(-1)
else:
    logging.info("Domain Participant created in domain:"+dp.get_domain_id())

try:
    logging.info("Creating SALData TypeSupport...")
    SALData_SALTopicTS = pydds.create_type_support (idlFilePath + "#" + topicName)
    
    topicTypeName = "SALData_SALTopicTopic" #SALData_SALTopicTS.get_type_name()
    pydds.checkStatus(
        SALData_SALTopicTS.register_type(dp, topicTypeName),
        "Registering SALData_SALTopic type to domain participant"
        )

    # Creating a topicQos structure
    HWTopicQos = pydds.TopicQos()
    pydds.checkStatus(
        dp.get_default_topic_qos(HWTopicQos),
        "Retrieving default topicQos from domain participant"
        )

    HWTopicQos.set_reliable()
    HWTopicQos.set_transient()

    pydds.checkStatus(
        dp.set_default_topic_qos(HWTopicQos),
        "Setting default topicQos in domain participant"
        )

    HWTopic = dp.create_topic ("SALData_SALTopic", topicTypeName, HWTopicQos)

    publisherQos = pydds.PublisherQos()
    pydds.checkStatus(
        dp.get_default_publisher_qos(publisherQos),
        "Retrieving default publisher QoS"
        )

    publisherQos.set_partition("SALData_SALTopic example")

    publisher = dp.create_publisher (publisherQos)

    writerQos = pydds.DataWriterQos()
    pydds.checkStatus(
        publisher.get_default_datawriter_qos(writerQos),
        "Retrieving default DataWriter QoS"
        )
    pydds.checkStatus(
        publisher.copy_from_topic_qos(writerQos, HWTopicQos),
        "Copying DataWriter QoS from SALData_SALTopic topic QoS"
        )
    # Set autodispose unregistered instance here

    logging.info("Creating SALData_SALTopic datawriter!")
    HWwriter = publisher.create_datawriter(HWTopic, writerQos)

    # Now we write data here
    done = 0
    SALData_SALTopicSample = SALData_SALTopicTS.getTopicObject()
    while (done != 1):
###INSERT PYTHON WRITE
        status = HWwriter.write(SALData_SALTopicSample)
        pydds.checkStatus(status, "Writing a SALData_SALTopic sample")
        counter += 1

    time.sleep(1)

except PyDDSWrapper.Exception as ex:
    logging.warning("Caught TxPyDDS::Exception: " +
                    ex.error_name() + " when " +
                    ex.what())
except PyDDSWrapper.InvalidHandle,  ex:
    logging.warning("Caught TxPyDDS::InvalidHandle exception" +
    "From:" + ex.what())
except PyDDSWrapper.NotImplemented, ex:
    logging.warning("Caught TxPyDDS::NotImplemented exception" +
    "From:" + ex.what())
except TypeError, ex:
    logging.warning("Unexpected exception TypeError: %s" % str(ex))
except:
    logging.warning("Unexpected exception: %s" % str(sys.exc_info()[0]))
    raise
else:
    logging.info("End pydds SALData_SALTopic publisher...")

