struct TopicIdType {
short id;
float value;
};
#pragma keylist TopicId id



Runtime();
Runtime(const std::string& partition);
Runtime(const std::string& partition, const std::string& domain);

Topic(const std::string& name);
Topic(const std::string& name, const TopicQos& qos);
Topic(const std::string& name, const std::string& type_name);
Topic(const std::string& name, const std::string& type_name, const TopicQos& qos);

dds::Topic<TopicIdType> topic("TopicId");

template <typename T>
class dds::DataWriter : public dds::Entity {
public:
   DataWriter();
   DataWriter(Topic<T> topic) 
  
   DataWriter(Topic<T> topic, const DataWriterQos& qos) 
   DataWriter(Topic<T> topic, const DataWriterQos& qos, Publisher pub);
//
};

dds::ReturnCode_t write(const T& sample);
dds::ReturnCode_t write(const T& sample, const dds::Time_t& timestamp);
  
dds::DataInstanceWriter<T> register_instance(const T& key);

// Join the default-domain and the “LSST” partition
dds::Runtime runtime("LSST");
// Create the “TopicId” Topic
dds::Topic<TopicIdType> topic("TopicId");
// Create a DataWriter
dds::DataWriter<TopicIdType> dw(Topic);
TopicIdType ts = {1, 0.0F};
// Write Data
dw.write(ts);

template <typename T>
class dds::DataReader : public dds::Entity {
public:
   DataReader();
   DataReader(Topic<T> topic) 
  
   DataReader(Topic<T> topic, const DataReader Qos& qos) 
   DataReader(Topic<T> topic, const DataReader Qos& qos, Subscriber pub);
//
};


dds::Duration latency_budget = {2, 0};
dds::Duration deadline = {4, 0};
// Create the TopicQos
dds::TopicQos tqos;
// Set Latency Budget, Transport Priority & Deadline
tqos.set_latency_budget(latency_budget);
tqos.set_deadline(deadline);
tqos.set_priority(tsPrio);
// Create the “TopicId” Topic
dds::Topic<TopicIdType> topic("TopicId", tqos);
dds::DataWriterQos dwqos(tqos);
// Create a DataWriter
dds::DataWriter<TopicIdType> dw(topic, dwqos);



void read(TSeq& samples, dds::SampleInfoSeq& infos);
void read(std::vector<T>& data,  std::vector<dds::SampleInfo> info);
template <typename DataForwardIterator, typename InfoForwardIterator> 
uint32_t
read(DataForwardIterator data_begin, InfoForwardIterator info_begin, uint32_t max_samples);
template <typename DataOutputIterator, typename InfoOutputIterator> 
uint32_t
read(DataOutputIterator data_begin, InfoOutputIterator info_begin);


void read(std::vector<T>& data, TopicId_wrapper.java
          std::vector<dds::SampleInfo> info,
dds::SampleStateMask samples_state,
dds::ViewStateMask views_state,
dds::InstanceStateMask instances_state) 

// Join the default-domain and the “LSST” partition
dds::Runtime runtime("LSST");
// Create the “TopicId” Topic
dds::Topic<TopicIdType> topic("TopicId");
// Create a DataReader
dds::DataReader<TopicIdType> dr(topic);
std::vector<TopicIdType> data;
std::vector<SampleInfo> info;
while (true) {
   dr.read(data, info);
   for (int i =0; i < data.length(); ++i)
      std::cout << data[i] << std::endl;
   sleep(1);
};

dds::Duration latency_budget = {2, 0};
dds::Duration deadline = {4, 0};
// Create the TopicQos
dds::TopicQos tqos;
// Set Latency Budget, Transport Priority & Deadline
tqos.set_latency_budget(latency_budget);
tqos.set_deadline(deadline);
tqos.set_priority(tsPrio);
// Create the Topic
dds::Topic<TopicIdType> tsTopic("TopicId", tqos);    
// Create the DataReaderQos from TopicQos
dds::DataReaderQos drqos(tqos);
// Create the DataReader
dds::DataReader<TopicIdType> dr(tsTopic, drqos);

class TopicIdDataHandler {
public:
   void operator() (dds::DataReader<TopicIdType>& reader) {
      std::vector<TopicIdType> data;
std::vector<dds::SampleInfo>     info;
      reader.read(data, info);
      //[NOTE #1] Do whatever is needed with the data
   }   
};

dds::DataReader<TopicIdType> dr(topic);
//[NOTE #1]: Create an instance of 
//the handler
TopicIdDataHandler handler;
//[NOTE #2]: Create a read condition for 
// the given reader
auto rcond = 
   dr.create_readcondition(handler);
//[NOTE #3]: Create a Waitset and attach 
// the condition
dds::WaitSet ws;
ws.attach(rcond);
dds::Duration timeout = {1, 0};
//[NOTE #4] Wait for some condition to 
// become active, and retrieve all active
// conditions
auto conds = ws.wait(timeout);
//[NOTE #5] Execute the condition handlers
for (auto i = conds.begin(); 
     i < conds.end(); ++i)
   i->execute();
//[NOTE #5] Automatically dispatch the 
// condition handlers when conditions 
//are notified
ws.dispatch(timeout);

class TopicIdDataHandler {
public:
   void handle_data(dds::DataReader<TopicIdType>& reader) {
      std::cout << "Reading..." << std::endl;
std::vector<TopicIdType> data;
std::vector<dds::SampleInfo>     info;
      reader.read(data, info);
      //[NOTE #1] Do whatever is needed with the data
   }
};


dds::DataReader<TopicIdType> dr(topic);
//[NOTE #1]: Create an instance of the handler
TopicIdDataHandler handler;
auto func = 
   boost::bind(TopicIdDataHandler::handle_data, 
               &handler, _1);
//[NOTE #2]: Register the handler for the relevant event
auto connection = 
   dr.connect<on_data_available>(func);

/**
* Reads all new samples from any view state and alive instances. Notice
* that this call is intended to loan the <code>samples</code> as
* well as the <conde>infos</code> containers, thus will require a
* return_loan.
*/
DDS::ReturnCode_t read(TSeq& samples, DDS::SampleInfoSeq& infos)
/**
* Reads at most <code>max_samples</code> samples that have not been
* read yet from all vies and alive instances.
*/
DDS::ReturnCode_t read(TSeq& samples, long max_samples)
/**
* Most generic <code>read</code> exposing all the knobs provided by
* the OMG DDS API.
*/
DDS::ReturnCode_t
read(TSeq& samples, DDS::SampleInfoSeq& infos,long max_samples,
DDS::SampleStateMask samples_state, DDS::ViewStateMask views_state,
DDS::InstanceStateMask instances_state)
DDS::ReturnCode_t
return_loan(TSeq& samples, DDS::SampleInfoSeq& infos);


Makefile.idl
#-*-Makefile-*-
include $(SIMD_HOME)/config/apps/Macros-idl.GNU
TARGET_IDL=ShapeType.idl
include $(SIMD_HOME)/config/apps/Rules-idl.GNU

Sample State (READ | NOT_READ): Determines
wether a sample has already been read by this
DataReader or not.

Instance State (ALIVE, NOT_ALIVE, DISPOSED).
Determines wether (1) writer exist for the specific
instance, or (2) no matched writers are currently
available, or (3) the instance has been disposed

View State (NEW, NOT_NEW). Determines wether
this is the first sample of a new (or re-born) instance

