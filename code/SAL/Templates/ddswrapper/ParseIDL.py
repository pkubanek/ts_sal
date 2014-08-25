# This software is copyrighted by Tech-X Corporation, 2012.  All
# rights reserved.

"""
--------------------------------------------------------------------
Parses the IDL file and creates dictionaries for structs and key lists

Author: Roopa Pundaleeka (roopa@txcorp.com)

$Id: ParseIDL.py  $
--------------------------------------------------------------------
"""

import sys, os, re, string
import xml.dom.minidom
from xml.dom.minidom import Node

class ParseIDL:
  "Class to hold type specific information by parsing DDS IDL file."

  ##
  # Initializations
  ##
  def __init__(self, idlFileName=""):
    self.idlFileName = str(idlFileName)
    self.moduleName  = ""
    self.structDict  = dict()
    self.keyList     = dict()
    
    # Parse the IDL file
    self.parseIdl()
  
  ##
  # Get the topic name needed to register type
  ##
  def getTopicName(self, topicName):
    return self.structDict.keys()[0] + "::" + topicName

  ##
  # Get the topic keys
  ##
  def getTopicKeys(self, topicName):
    return self.keyList[topicName]

  ##
  # Parse the struct dictionary and generate the metadata
  ##
  def getMetaData(self, topicName):
    metaData = "<MetaData version=\"1.0.0\">"
    for module in self.structDict.keys():
      metaData += "<Module name=\"" + module + "\">"
      for struct in self.structDict[module].keys():
        if struct == topicName:
          metaData += "<Struct name=\"" + struct + "\">"
          for memCount in self.structDict[module][struct].keys():
            member = self.structDict[module][struct][memCount]
            metaData += "<Member name=\"" + member.split(":")[0] + "\">"
            metaData += "<" + member.split(":")[1] + "/>"
            metaData += "</Member>"
          metaData += "</Struct>"
      metaData += "</Module>"
    metaData += "</MetaData>"
    return metaData

  ##
  # Generate topic type dynamically using the meta data
  ##
  def getTopicClassObj(self, metaData):
    className = ""

    metaDataElement = xml.dom.minidom.parseString(metaData)
    moduleElement = metaDataElement.getElementsByTagName("Module").item(0)
    className += moduleElement.getAttribute("name")

    structElement = moduleElement.getElementsByTagName("Struct").item(0)
    structName = structElement.getAttribute("name")
    className += "." + structName

    members = {}
    typedInstance = {
      'Boolean': bool(False),
      'Char': int(0),
      'Octet': int(0),
      'Short': int (0),
      'UShort': int (0),
      'Long':  int(0),
      'ULong': int(0),
      'LongLong': long(0),  # Perhaps
      'ULongLong': long(0), # Perhaps
      'Float': float(0),
      'Double': float(0),
      'String': str('')
      } 
    for memberElement in structElement.getElementsByTagName("Member"):
      memberType = memberElement.childNodes[0].nodeName
      # Appropriate types
      # @@ Need to figure out a way to check that a short int variables
      # (short, octet, char) do not overflow....
      members[memberElement.getAttribute("name")] = typedInstance[memberType]

      # Add the meta data to the object as well
      members["metaData"] = self.structDict[self.moduleName][structName]

    dynamicClass = type(str(className), (object,), members)
    return dynamicClass

  ##
  # Parse the give IDL file and store required info in a dictionary
  ##
  def parseIdl(self):
    idlFile = open(self.idlFileName, 'r')

    while True:
      line = idlFile.readline()

      # EOF reached
      if len(line) == 0: break

      # Strip white spaces
      line = line.strip()
    
      # Skip commented lines
      if re.match(r'^//', line): continue
      if re.match('^/\*', line):
        while True:
          line = idlFile.readline()
          if "*/" in line: 
            break
        continue

      # Parse Module definition
      if "module" in line and line.split()[0] == "module":
        self.moduleName = line.split()[1]
        self.structDict[self.moduleName] = dict()
        continue  

      # Parse key list
      if "#pragma" in line and line.split()[0] == "#pragma":
        topicName = line.split()[2]
        keys = line.split("#pragma keylist " + topicName)[1].strip()
        self.keyList[topicName] = re.sub('\s', ',', keys)

      # Parse Struct defs
      if "struct" in line and line.split()[0] == "struct":
        structName = line.split()[1]
        self.structDict[self.moduleName][structName] = dict()
      
        # Parse through the struct to get all the members
        memCount = 0
        while True:
          line = idlFile.readline()
        
          # Unexpected EOF reached
          if len(line) == 0: 
            print "Unexpected End of File"
            sys.exit(3)
      
          # Strip white spaces
          line = line.strip()

          # End of struct def
          if "};" in line: break

          # Skip commented lines
          if re.match(r'^//', line): continue
          if re.match('^/\*', line):
            while True:
              line = idlFile.readline()
              if "*/" in line: 
                break
            continue
                
          # Get member names and types
          if ";" in line:
            line = line.split(';')[0]
            member = line.split()
            memberName = member[len(member) - 1]
            memberType = ' '.join(member[0:(len(member) - 1)])

            typedName = {
              'boolean': ':Boolean',
              'short': ':Short',
              'char': ':Char',
              'octet': ':Octet',
              'unsigned short': ':UShort',
              'long': ':Long',
              'unsigned long': ':ULong',
              'long long': ':LongLong',
              'unsigned long long': ':ULongLong',
              'float': ':Float',
              'double': ':Double',
              'string': ':String'
              }
            # Appropriate types
            try:
              self.structDict[self.moduleName][structName][memCount] = memberName + typedName[memberType]
            except KeyError:
              print "Invalid type: ", memberType
              sys.exit(4)

            memCount = memCount + 1
