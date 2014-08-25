# This software is copyrighted by Tech-X Corporation, 2012.  All
# rights reserved.

import sys
import PyDDSWrapper
import PyDDSTypeSupport
import PyDDSTopic
import ParseIDL

class PyDDS:
  "Wrapper class to PyDDSWrapper. Also holds IDL file info needed"

  ##
  # Initialize and return Runtime instance
  ##
  def __init__(self):
    self.runtime = PyDDSWrapper.Runtime()

  def setLogger(self, ddsLogger):
    self.runtime.setLogger(ddsLogger)

  # Create domain participant
  def create_participant(self, participantName):
    return self.runtime.create_participant(participantName)

  # Create dataspace with a single partition
  def create_dataspace(self, domainName, partitionName):
    return self.runtime.create_dataspace(domainName, partitionName)
 
  # Create dataspace with multiple partitions
  def create_dataspace_partitions(self, domainName, partitionNames):
    return self.runtime.create_dataspace_partitions(domainName, partitionNames)

  # Connect domain participant, publisher and subscriber in a dataspace
  def connect_dataspace(domainParticipant, pub, sub):
    return self.runtime.connect_dataspace(domainParticipant, pub, sub)    

  # Get all the info needed to create type support from ParseIDL
  def create_type_support(self, idlFileUrl):
    return PyDDSTypeSupport.PyDDSTypeSupport(idlFileUrl)

  # Get topic
  def create_topic(self, topicName, dataspace, topicQos, topicUri):
    return PyDDSTopic.PyDDSTopic(topicName, dataspace, topicQos, topicUri)

  # Check Status
  def checkStatus(self, callObj, msg):
    PyDDSWrapper.checkStatus(callObj, msg)

  # Get Topic Qos
  def TopicQos(self):
    return PyDDSWrapper.TopicQos()

  # Get Publisher Qos
  def PublisherQos(self):
    return PyDDSWrapper.PublisherQos()

  # Get DataWriter Qos
  def DataWriterQos(self):
    return PyDDSWrapper.DataWriterQos()

  # Get Subscriber Qos
  def SubscriberQos(self):
    return PyDDSWrapper.SubscriberQos()

  # Get DataWriter Qos
  def DataReaderQos(self):
    return PyDDSWrapper.DataReaderQos()

  # Get InfoSeq
  def InfoSeq(self):
    return PyDDSWrapper.InfoSeq()
