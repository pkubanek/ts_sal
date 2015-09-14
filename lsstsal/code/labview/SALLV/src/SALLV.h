#include <string>
#include <exception>
#include <iostream>
#include <vector>
#include <cstring>
#include "omnithread.h"


class SALLV
{

public:

	enum DevState { OFFLINE, ACTIVE , CMDERROR, ERROR, HALT, FAULT, DONE /*, __max_DevState=0xffffffff */ };

	enum EventType {
	CONFIG_EVENT=0,
	QOS_EVENT,
	INFO_EVENT,
	WARN_EVENT,
	ALARM_EVENT,
	};

	struct _DevCommandInfo
	{
	string 		cmd_name;
	long 		cmd_tag;
	long 		in_type;
	long 		out_type;
	string 		in_type_desc;
	string 		out_type_desc;
	
	bool operator==(const _DevCommandInfo &);
	};


	struct _SubsysInfo
	{
	string dev_class;
	string server_id;
	string server_host;
	long server_version;
	string doc_url;
	string dev_type;
	};
	
	typedef _SubsysInfo SubsysInfo;


	typedef _CommandInfo CommandInfo;


	bool writable;
	typedef bool AttrWriteType;
 	typedef std::exception DevFailed;

	enum AttrDataFormat { SCALAR, SPECTRUM, IMAGE, FMT_UNKNOWN *,__max_AttrDataFormat=0xffffffff */ };



	struct SubsysList {
        };

        struct TimeVal {    
           long tv_sec;
           long tv_usec;
           long tv_nsec;
           double stamp;
        };

	struct SubsysAttribute {
        };


	struct AttributeInfo {
            int size;
            std::string name;
            bool writable;
            int data_format;
            int data_type;
            std::string label;
            std::string unit;
            std::string format;
            int disp_level;
        };

	typedef vector<AttributeInfo> AttributeInfoList;


	struct CallBack {
        };


  	CommandInfoList* command_list_query (void) 
    throw (DevFailed);

  	AttributeInfoList* attribute_list_query (void) 
    throw (DevFailed);

  	SubsysAttribute read_attribute (const std::string& attr_name) 
    throw (DevFailed);

  	SubsysAttribute read_attribute (const char * attr_name) 
    throw (DevFailed);

  std::vector<SubsysAttribute>* read_attributes (const std::vector<std::string>&attr_names) 
    throw (DevFailed);

  void write_attribute (const SubsysAttribute& attr_value) 
    throw (DevFailed);

  void write_attributes (const std::vector<SubsysAttribute>& attr_values) 
    throw (DevFailed);
    
    SubsysData command_inout (const std::string& cmd_name) 
    throw (DevFailed);

	SubsysData command_inout (const char * cmd_name) 
    throw (DevFailed);

  SubsysData command_inout (const std::string& cmd_name, const SubsysData &d) 
    throw (DevFailed);

	SubsysData command_inout (const char *cmd_name, const SubsysData &d) 
    throw (DevFailed);


class Except
{
public:
     static const char throw_exception(const char *msg, const char *m2, const char *m3)
     {
         std::cout << msg << std::endl;
     }
};

class SubsysData
{

public :
//
// constructor methods
//
	enum except_flags
	{
		isempty_flag,
		wrongtype_flag,
		numFlags
	};

	SubsysData();
	SubsysData(const SubsysData &);
	SubsysData & operator=(const SubsysData &);
	~SubsysData();

	bool is_empty() {return any_is_null();}
	void exceptions(bitset<numFlags> fl) {exceptions_flags = fl;}
	bitset<numFlags> exceptions() {return exceptions_flags;}
	void reset_exceptions(except_flags fl) {exceptions_flags.reset((size_t)fl);}
	void set_exceptions(except_flags fl) {exceptions_flags.set((size_t)fl);}
	int get_type();
		
//
--
	bool operator >> (const std::vector<long>* &datum);
	bool operator >> (const std::vector<long long>* &datum);
	bool operator >> (const std::vector<unsigned long>* &datum);
	bool operator >> (const std::vector<unsigned long long>* &datum);
	bool operator >> (const std::vector<float>* &datum);
	bool operator >> (const std::vector<double>* &datum);
	bool operator >> (const std::vector<std::string>* &datum);
	
	friend ostream &operator<<(ostream &,SubsysData &);

protected :
	bool any_is_null();
	
	bitset<numFlags> 	exceptions_flags;
	
	SubsysDataExt		*ext;			// Class extension
};


class EventData
{
public :
	EventData(SubsysProxy *dev,string &nam,string &evt,SubsysAttribute *attr_value_in,
	DevErrorList &errors_in);
	~EventData();
	EventData(const EventData &);
	EventData & operator=(const EventData &);
	
	SubsysProxy *subsys;
	string attr_name;
	string event;
	SubsysAttribute *attr_value;
	bool err;
	DevErrorList errors;
	/**
	 * The date when the event arrived
	 */
	TimeVal reception_date;
	TimeVal &get_date() {return reception_date;}
private:
	void set_time();
};



class Group
{
   long get_size(bool x);
};


class SubsysProxy
{
public:
  SubsysProxy (const std::string& dev_name) 
    throw (DevFailed);

  SubsysProxy (const char * dev_name) 
    throw (DevFailed);

  virtual ~SubsysProxy ();

  const std::string status (void) 
    throw (DevFailed);

  DevState state (void) 
    throw (DevFailed);

  void set_timeout_millis( int ms);

  int ping (void) 
    throw (DevFailed);

  SALLV::CommandInfoList* command_list_query (void) 
    throw (DevFailed);

  std::vector<std::string>* get_attribute_list (void) 
    throw (DevFailed);

  SALLV::AttributeInfoList* attribute_list_query (void) 
    throw (DevFailed);

  SALLV::SubsysAttribute read_attribute (const std::string& attr_name) 
    throw (DevFailed);

  SALLV::SubsysAttribute read_attribute (const char * attr_name) 
    throw (DevFailed);

  std::vector<SALLV::SubsysAttribute>* read_attributes (const std::vector<std::string>& attr_names) 
    throw (DevFailed);

  void write_attribute (const SALLV::SubsysAttribute& attr_value) 
    throw (DevFailed);

  void write_attributes (const std::vector<SALLV::SubsysAttribute>& attr_values) 
    throw (DevFailed);

  SALLV::SubsysData command_inout (const std::string& cmd_name) 
    throw (DevFailed);

	SALLV::SubsysData command_inout (const char * cmd_name) 
    throw (DevFailed);

  SALLV::SubsysData command_inout (const std::string& cmd_name, const SALLV::SubsysData &d) 
    throw (DevFailed);

	SALLV::SubsysData command_inout (const char *cmd_name, const SALLV::SubsysData &d) 
    throw (DevFailed);
 
  int subscribe_event(const std::string &attr_name, 
                      SALLV::EventType event, 
                      SALLV::CallBack *cb, 
                      const std::vector<std::string> &filters) 
    throw (DevFailed);

	void unsubscribe_event(int event_id) 
    throw (DevFailed);


  const std::string& dev_name (void) const;

  void set_timeout (size_t tmo_msecs);


};


};


