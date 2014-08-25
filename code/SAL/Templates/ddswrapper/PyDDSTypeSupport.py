# This software is copyrighted by Tech-X Corporation, 2012.  All
# rights reserved.

import sys
import PyDDSWrapper
import ParseIDL

class PyDDSTypeSupport:
  "PyDDS class for Type support"

  ##
  # Initializations
  ##
  def __init__(self, fileUrl=""):
    self.fileUrl      = str(fileUrl)
    self.idlFilePath  = self.fileUrl.split("#")[0]
    self.topicName    = self.fileUrl.split("#")[1]
    self.parseIDL     = ParseIDL.ParseIDL(self.idlFilePath)
    self.typeSupport  = PyDDSWrapper.create_type_support (self.parseIDL.getTopicName(self.topicName),      
                                                          self.parseIDL.getTopicKeys(self.topicName),
                                                          self.parseIDL.getMetaData(self.topicName))


  # Get the fully qualified topic name
  def get_type_name(self):
    return self.parseIDL.getTopicName(self.topicName)

  # Get the list of keys for the topic
  def get_topic_keys(self):
    return self.parseIDL.getTopicKeys(self.topicName)

  # Get the list of keys for the topic
  def get_topic_metadata(self):
    return self.parseIDL.getMetaData(self.topicName)

  # Register the type with DDS
  def register_type(self, domainParticipant, topicTypeName):
    return self.typeSupport.register_type(domainParticipant, topicTypeName)

  # Get all the info needed to create type support from ParseIDL
  def getTopicObject(self):
    return self.parseIDL.getTopicClassObj(self.parseIDL.getMetaData(self.topicName))

  # Get PyObjectSeq
  def PyObjectSeq(self):
    return PyDDSWrapper.PyObjectSeq(self, self.topicName)

