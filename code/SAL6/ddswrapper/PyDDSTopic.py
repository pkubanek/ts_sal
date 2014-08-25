# This software is copyrighted by Tech-X Corporation, 2012.  All
# rights reserved.

import sys
import PyDDS
import PyDDSWrapper
import PyDDSTypeSupport

class PyDDSTopic:
  "PyDDS class for Topic"

  ##
  # Initializations
  ##
  def __init__(self, topicName, dataspace, topicQos, topicUri):
    self.topicName   = topicName
    self.dataspace   = dataspace
    self.subscriber  = self.dataspace.get_subscriber()
    self.publisher   = self.dataspace.get_publisher()
    self.topicUri    = topicUri
    self.typeSupport = PyDDSTypeSupport.PyDDSTypeSupport(topicUri)
    pydds = PyDDS.PyDDS()
    pydds.checkStatus(
      self.typeSupport.register_type(self.dataspace.get_participant(), self.typeSupport.get_type_name()),
      "Registering HelloWorld type to domain participant"
      )

    self.topic = dataspace.get_participant().create_topic(topicName, self.typeSupport.get_type_name(), topicQos)

  ##
  # Create reader
  ##
  def create_reader(self, readerQos):
    return self.dataspace.get_subscriber().create_datareader(self.topic, readerQos)
    
  ##
  # Create writer
  ##
  def create_writer(self, writerQos):
    return self.dataspace.get_publisher().create_datawriter(self.topic, writerQos)
    
  ##
  # Create sample data
  ##
  # @@ This is not type-safe.  We need to figure out how to define the 
  #    function signature dynamically.
  def create_sample(self, *data):
    topicObj = self.parseIDL.getTopicClassObj(self.parseIDL.getMetaData(self.topicName))
    for elem in data:
      setattr(topicObj, elem.split("=")[0].strip(), elem.split("=")[1].strip())
      
    return topicObj
 
  
  ##
  # Get Object Sequence
  ##
  def getObjectSeq(self):
    return self.typeSupport.PyObjectSeq()

  ##
  # Get Topic Object
  ##
  def getTopicObject(self):
    return self.typeSupport.getTopicObject()

