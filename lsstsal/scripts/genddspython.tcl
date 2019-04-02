#!/usr/bin/env tclsh

proc genDDSpython { subsys } {
global SAL_WORK_DIR TLM_ALIASES CMD_ALIASES EVENT_ALIASES
   genDDSbaseclass $subsys
   set fout [open $SAL_WORK_DIR/python/SAL_[set subsys]_Topic.py w]
   puts $fout "from dds import *"
   puts $fout "import os"
   puts $fout "import time"
   puts $fout "import ddsutil"
   puts $fout "import logging"
   puts $fout "import random"
   puts $fout "import sal_defines_dict"
   puts $fout ""
   puts $fout "[set subsys]_revCodes = \{"
   set idlfile $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl
   set ptypes [lsort [split [exec grep pragma $idlfile] \n]]
   set last [lindex [lindex $ptypes end] 2]
   foreach j $ptypes {
     set topic [lindex $j 2]
     if { $topic != "ackcmd" && $topic != "command" && $topic != "logevent" } {
       set revcode [getRevCode [set subsys]_[set topic] short]
       set type [lindex [split $topic _] 0]
       if { $topic != $last } {
         puts $fout "    \"[set topic]\": \"[set subsys]::[set topic][set revcode]\","
       } else {
         puts $fout "    \"[set topic]\": \"[set subsys]::[set topic][set revcode]\""
       }
     }
   }
   puts $fout "\}"
   puts $fout ""
   puts $fout "class SAL_[set subsys]_Listener(Listener):"
   puts $fout "    def __init__(self, topic):"
   puts $fout "        Listener.__init__(self)"
   puts $fout ""
   puts $fout "    \"\"\" The on_data_available routine is a placeholder that should be replaced"
   puts $fout "        by application specific code. In order to use the callback the following"
   puts $fout "        code should be used  e.g. for $subsys $last: "
   puts $fout ""
   puts $fout "        mgr = SAL_[set subsys]()"
   puts $fout "        myTopic = SAL_[set subsys]_Topic(mgr, \"[set last]\")"
   puts $fout "        myTopic.salCallback()"
   puts $fout "    \"\"\""
   puts $fout "    def on_data_available(self, entity):"
   puts $fout "        logging.debug('on_data_available called for [set subsys]')"
   puts $fout "        lsamp = entity.take(1)"
   puts $fout "        c = 0"
   puts $fout "        for (sd, si) in lsamp:"
   puts $fout "            if si.valid_data:"
   puts $fout "                logging.debug('Callback data : ' + self.aTopic.name)"
   puts $fout "                sd.print_vars()"
   puts $fout "                c = c+1"
   puts $fout "        if c > 0:"
   puts $fout "            self.aTopic.lastSample = sd"
   puts $fout ""
   puts $fout "    def setType(self, salTopic):"
   puts $fout "        self.aTopic = salTopic"
   puts $fout ""
   puts $fout ""
   puts $fout "class SAL_[set subsys]_Topic:"
   puts $fout "    def __init__(self, sal, topic):"
   puts $fout "        self.IdlLoc = os.environ\['SAL_IDL_DIR'\] + '/sal_revCoded_[set subsys].idl'"
   puts $fout "        self.type = ddsutil.get_dds_classes_from_idl(self.IdlLoc,"
   puts $fout "                                                    self.getTopicHandle(topic))"
   puts $fout "        self.topicReg = self.type.register_topic(sal.dp,"
   puts $fout "                                                 self.getTopicName(topic),"
   puts $fout "                                                 sal.qp.get_topic_qos())"
   puts $fout "        self.salHandle = sal"
   puts $fout "        self.hasReader = False"
   puts $fout "        self.hasWriter = False"
   puts $fout "        self.hasAckReader = False"
   puts $fout "        self.hasAckWriter = False"
   puts $fout "        self.name = self.getTopicName(topic)"
   puts $fout "        self.revCode = self.name\[-8:\]"
   puts $fout "        self.sampleAge = 1.0e20"
   puts $fout "        self.maxSamples = 1000"
   puts $fout "        self.tuneableQos = False"
   puts $fout "        self.sndSeqNum = random.randint(1, 9999999)"
   puts $fout "        self.pub = sal.dp.create_publisher(sal.pubqos)"
   puts $fout "        self.sub = sal.dp.create_subscriber(sal.subqos)"
   puts $fout ""
   puts $fout "    def getTopicHandle(salTopic, topicName):"
   puts $fout "        return [set subsys]_revCodes.get(topicName)"
   puts $fout ""
   puts $fout "    def getTopicName(salTopic, topicName):"
   puts $fout "        name = [set subsys]_revCodes.get(topicName)"
   puts $fout "        return name.replace(\"::\", \"_\")"
   puts $fout ""
   puts $fout "    def getReader(salTopic):"
   puts $fout "        if not salTopic.hasReader:"
   puts $fout "            if salTopic.salHandle.id > 0:"
   puts $fout "                salTopic.filtername = 'filtered_' + salTopic.name"
   puts $fout "                salTopic.filter = '[set subsys]ID = ' + str(salTopic.salHandle.id)"
   puts $fout "                salTopic.filteredReg = salTopic.salHandle.dp.create_contentfilteredtopic("
   puts $fout "                    salTopic.filtername,"
   puts $fout "                    salTopic.topicReg,salTopic.filter, '')"
   puts $fout "                logging.debug('Creating filtered reader for ' + salTopic.name)"
   puts $fout "                salTopic.reader = salTopic.sub.create_datareader("
   puts $fout "                                  salTopic.filteredReg,"
   puts $fout "                                  salTopic.salHandle.qp.get_reader_qos())"
   puts $fout "            else:"
   puts $fout "                logging.debug('Creating reader for ' + salTopic.name)"
   puts $fout "                salTopic.reader = salTopic.sub.create_datareader("
   puts $fout "                                  salTopic.topicReg,"
   puts $fout "                                  salTopic.salHandle.qp.get_reader_qos())"
   puts $fout "            salTopic.hasReader = True"
   puts $fout ""
   puts $fout "    def getAckReader(salTopic):"
   puts $fout "        if not salTopic.hasAckReader:"
   puts $fout "            if salTopic.salHandle.id > 0:"
   puts $fout "                salTopic.filtername = 'filtered_ackcmd'"
   puts $fout "                salTopic.filter = '[set subsys]ID = ' + str(salTopic.salHandle.id)"
   puts $fout "                salTopic.filteredReg = salTopic.salHandle.dp.create_contentfilteredtopic("
   puts $fout "                         salTopic.filtername,"
   puts $fout "                         salTopic.salHandle.ackcmd_topic,salTopic.filter, '')"
   puts $fout "                logging.debug('Creating filtered reader for ' + salTopic.name)"
   puts $fout "                salTopic.ackReader = salTopic.sub.create_datareader("
   puts $fout "                                  salTopic.filteredReg,"
   puts $fout "                                  salTopic.salHandle.qp.get_reader_qos())"
   puts $fout "            else:"
   puts $fout "                logging.debug('Creating reader for ' + salTopic.name)"
   puts $fout "                salTopic.ackReader = salTopic.sub.create_datareader("
   puts $fout "                                  salTopic.salHandle.ackcmd_topic,"
   puts $fout "                                  salTopic.salHandle.qp.get_reader_qos())"
   puts $fout "            salTopic.hasAckReader = True"
   puts $fout ""
   puts $fout "    def getSample(salTopic):"
   puts $fout "        logging.debug('Reading topic ' + salTopic.name)"
   puts $fout "        salTopic.getReader()"
   puts $fout "        s = salTopic.reader.take(salTopic.maxSamples)"
   puts $fout "        c = 0"
   puts $fout "        for sd, si in s:"
   puts $fout "            if si.valid_data:"
   puts $fout "                sd.print_vars()"
   puts $fout "                logging.debug('Sample is '+"
   puts $fout "                    str(sd.private_sndStamp))"
   puts $fout "                c = c+1"
   puts $fout "        if c == 0:"
   puts $fout "            return SAL__RETCODE.get('NO_UPDATES')"
   puts $fout "        salTopic.lastSample = sd"
   puts $fout "        return sd"
   puts $fout ""
   puts $fout "    def flushSamples(salTopic):"
   puts $fout "        logging.debug('Flushing topic ' + salTopic.name)"
   puts $fout "        salTopic.getReader()"
   puts $fout "        s = reader.take(999999)"
   puts $fout "        c = 0"
   puts $fout "        for sd, si in s:"
   puts $fout "            if si.valid_data:"
   puts $fout "                sd.print_vars()"
   puts $fout "                logging.debug('Sample was '+"
   puts $fout "                    str(sd.private_sndStamp))"
   puts $fout "                c = c+1"
   puts $fout "        if c == 0:"
   puts $fout "            return SAL__RETCODE.get('NO_UPDATES')"
   puts $fout "        salTopic.lastSample = sd"
   puts $fout "        return SAL__RETCODE.get('OK')"
   puts $fout ""
   puts $fout "    def getLastSample(salTopic, topic):"
   puts $fout "        return salTopic.lastSample"
   puts $fout ""
   puts $fout "    def getNextSample(salTopic, topic):"
   puts $fout "        logging.debug('Reading next sample ' + salTopic.name)"
   puts $fout "        salTopic.getReader()"
   puts $fout "        s = topic.take(1)"
   puts $fout "        c = 0"
   puts $fout "        for sd, si in s:"
   puts $fout "            if si.valid_data:"
   puts $fout "                sd.print_vars()"
   puts $fout "                logging.debug('Sample is '+"
   puts $fout "                    str(sd.private_sndStamp))"
   puts $fout "                c = c+1"
   puts $fout "        if c == 0:"
   puts $fout "            return SAL__RETCODE.get('NO_UPDATES')"
   puts $fout "        salTopic.lastSample = sd"
   puts $fout "        return sd"
   puts $fout ""
   puts $fout "    def getEvent(salTopic, topic):"
   puts $fout "        salTopic.getNextSample(salTopic, topic)"
   puts $fout ""
   puts $fout "    def logEvent(salTopic, sample):"
   puts $fout "        salTopic.putSample(salTopic, sample)"
   puts $fout ""
   puts $fout "    def putSample(salTopic, sample):"
   puts $fout "        logging.debug('Publishing topic ' + salTopic.name)"
   puts $fout "        if not salTopic.hasWriter:"
   puts $fout "            salTopic.writer = salTopic.pub.create_datawriter("
   puts $fout "                       salTopic.topicReg,"
   puts $fout "                       salTopic.salHandle.qp.get_writer_qos())"
   puts $fout "            salTopic.hasWriter = True"
   puts $fout "        now = time.time()"
   puts $fout "        sample.private_sndStamp = now"
   puts $fout "        sample.private_origin = 1"
   puts $fout "        sample.private_revCode = salTopic.revCode"
   puts $fout "        sample.private_seqNum = salTopic.sndSeqNum"
   puts $fout "        salTopic.sndSeqNum = salTopic.sndSeqNum + 1"
   puts $fout "        if salTopic.salHandle.id > 0:"
   puts $fout "            sample.[set subsys]ID = salTopic.salHandle.id"
   puts $fout "        salTopic.writer.write(sample)"
   puts $fout ""
   puts $fout "    def salCallback(salTopic):"
   puts $fout "        listener = SAL_[set subsys]_Listener(salTopic)"
   puts $fout "        listener.setType(salTopic)"
   puts $fout "        salTopic.sub.create_datareader(salTopic.topicReg,"
   puts $fout "                   salTopic.salHandle.qp.get_reader_qos(),"
   puts $fout "                   listener)"
   puts $fout ""
   puts $fout "    def salTelemetryPub(salTopic):"
   puts $fout "        if not salTopic.hasWriter:"
   puts $fout "            salTopic.writer = salTopic.pub.create_datawriter("
   puts $fout "                salTopic.topicReg,"
   puts $fout "                salTopic.salHandle.qp.get_writer_qos())"
   puts $fout ""
   puts $fout "    def salTelemetrySub(salTopic):"
   puts $fout "        salTopic.getReader()"
   puts $fout ""
   puts $fout "    def salProcessor(salTopic):"
   puts $fout "        salTopic.getReader()"
   puts $fout "        if not salTopic.hasAckWriter:"
   puts $fout "            salTopic.ackwriter = salTopic.pub.create_datawriter("
   puts $fout "                salTopic.salHandle.ackcmd_topic,"
   puts $fout "                salTopic.salHandle.qp.get_writer_qos())"
   puts $fout "            salTopic.hasAckWriter = True"
   puts $fout ""
   puts $fout "    def salCommander(salTopic):"
   puts $fout "        if not salTopic.hasWriter:"
   puts $fout "            salTopic.writer = salTopic.pub.create_datawriter("
   puts $fout "                salTopic.topicReg,"
   puts $fout "                salTopic.salHandle.qp.get_writer_qos())"
   puts $fout "        if not salTopic.hasAckReader:"
   puts $fout "            salTopic.getAckReader()"
   puts $fout ""
   puts $fout "    def issueCommand(salTopic, sample):"
   puts $fout "        logging.debug('Sending command ' + salTopic.name)"
   puts $fout "        salTopic.putSample(sample)"
   puts $fout "        return salTopic.sndSeqNum-1"
   puts $fout ""
   puts $fout "    def getResponse(salTopic, ackSample):"
   puts $fout "        logging.debug('Checking reponse ' + salTopic.name)"
   puts $fout "        response = salTopic.getNextSample(salTopic,"
   puts $fout "                       salTopic.salHandle.ackcmd_topic)"
   puts $fout "        if response == SAL__RETCODE.get('NO_UPDATES'):"
   puts $fout "            return SAL__RETCODE.get('NO_UPDATES')"
   puts $fout "        if response.ack == SAL__RETCODE.get('CMD_NOACK'):"
   puts $fout "            return SAL__RETCODE.get('NO_UPDATES')"
   puts $fout "        ackSample.ack = response.ack"
   puts $fout "        ackSample.error = response.error"
   puts $fout "        ackSample.result = response.result"
   puts $fout "        return response.ack"
   close $fout
}

proc genDDSbaseclass { subsys } {
global SAL_WORK_DIR TLM_ALIASES CMD_ALIASES EVENT_ALIASES
  set fout [open $SAL_WORK_DIR/python/SAL_[set subsys].py w]
  puts $fout "from dds import *"
  puts $fout "import os"
  puts $fout "import time"
  puts $fout "import ddsutil"
  puts $fout "from sal_defines_dict import *"
  puts $fout "from SAL_[set subsys]_Topic import *"
  puts $fout ""
  puts $fout ""
  puts $fout "class SAL_[set subsys]:"
  puts $fout "    \"\"\" SAL DDS wrapper for [set subsys] Command/Event/Telemetry data types"
  puts $fout ""
  puts $fout "    Parameters"
  puts $fout "    ----------"
  puts $fout ""
  puts $fout "    id  (optional)"
  puts $fout "    Used to set the subsystem ID when there are multiple copies of it"
  puts $fout "    \"\"\""
  puts $fout ""
  puts $fout ""
  puts $fout "    def __init__(self, id=0):"
  puts $fout "        self.id = id"
  puts $fout "        QosLoc = os.environ\['LSST_DDS_QOS'\]"
  puts $fout "        self.qp = QosProvider(QosLoc,"
  puts $fout "                              'DDS DefaultQosProfile')"
  puts $fout "        self.dp = DomainParticipant(qos=self.qp.get_participant_qos())"
  puts $fout "        self.pubqos = self.qp.get_publisher_qos()"
  puts $fout "        self.subqos = self.qp.get_subscriber_qos()"
  puts $fout "        self.IdlLoc = os.environ\['SAL_IDL_DIR'\] + '/sal_revCoded_[set subsys].idl'"
  puts $fout "        self.ackcmd = ddsutil.get_dds_classes_from_idl("
  puts $fout "                                        self.IdlLoc, '[set subsys]::ackcmd')"
  puts $fout "        self.ackcmd_topic = self.ackcmd.register_topic(self.dp,"
  puts $fout "                                \"[set subsys]_ackcmd\", self.qp.get_topic_qos())"
  puts $fout ""
  puts $fout "    def getTelemetryNames(sal):"
  puts $fout "        telemetry = \[\]"
  foreach topic [lsort $TLM_ALIASES($subsys)] {
    puts $fout "        telemetry.append('$topic')"
  }
  puts $fout "        return telemetry"
  puts $fout ""
  puts $fout "    def getCommandNames(sal):"
  puts $fout "        commands = \[\]"
  foreach topic [lsort $CMD_ALIASES($subsys)] {
    puts $fout "        commands.append('$topic')"
  }
  puts $fout "        return commands"
  puts $fout ""
  puts $fout "    def getEventNames(sal):"
  puts $fout "        events = \[\]"
  foreach topic [lsort $EVENT_ALIASES($subsys)] {
    puts $fout "        events.append('$topic')"
  }
  puts $fout "        return events"
  puts $fout ""
  puts $fout "if __name__ == '__main__':"
  puts $fout "    mySal = SAL_[set subsys]()"
  puts $fout "    what = mySal.getTelemetryNames()"
  puts $fout "    print('Telemetry : ' + str(what))"
  puts $fout "    when = mySal.getEventNames()"
  puts $fout "    print('Events : ' + str(when))"
  puts $fout "    how = mySal.getCommandNames()"
  puts $fout "    print('Commands : ' + str(how))"
  puts $fout "    myTopic = SAL_[set subsys]_Topic(mySal, 'logevent_errorCode')"
  puts $fout "    print('Done topic creation')"
  puts $fout "    sample = myTopic.type.topic_data_class(errorCode=77777)"
  puts $fout "    myTopic.putSample(sample)"
  puts $fout "    print('Done putSample')"
  puts $fout "    news = myTopic.getSample()"
  puts $fout "    print('Done getSample')"
  puts $fout "    print('lastsample is')"
  puts $fout "    print(myTopic.lastSample.print_vars())"
  puts $fout "    myTopic.salCallback()"
  puts $fout "    print('Done callback init')"
  puts $fout "    sample.errorCode = 88888"
  puts $fout "    myTopic.putSample(sample)"
  puts $fout "    print('Done putSample')"
  puts $fout "    time.sleep(3)"
  puts $fout "    print('lastsample is now')"
  puts $fout "    print(myTopic.lastSample.print_vars())"
  puts $fout "    print('Done callback')"
  puts $fout "    myCmd = SAL_[set subsys]_Topic(mySal,'command_enable')"
  puts $fout "    myCmd.salCommander()"
  puts $fout "    print('Done salCommander')"
  puts $fout "    payload = myCmd.type.topic_data_class(value=True)"
  puts $fout "    cmdId = myCmd.issueCommand(payload)"
  puts $fout "    print('Done issueCommand')"
  close $fout
}



set SAL_DIR $env(SAL_DIR)
set SAL_WORK_DIR $env(SAL_WORK_DIR)

source $SAL_DIR/activaterevcodes.tcl
source $SAL_WORK_DIR/idl-templates/validated/[set argv]_revCodes.tcl
source $SAL_WORK_DIR/idl-templates/validated/[set argv]_cmddef.tcl
source $SAL_WORK_DIR/idl-templates/validated/[set argv]_evtdef.tcl
source $SAL_WORK_DIR/idl-templates/validated/[set argv]_tlmdef.tcl
genDDSpython $argv


