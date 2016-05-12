<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="13008000">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
	<Item Name="My Computer" Type="My Computer">
		<Property Name="NI.SortType" Type="Int">3</Property>
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="OpenConnection" Type="Folder">
			<Item Name="OpenConnectionInstances" Type="Folder">
				<Item Name="OpenConnection_Control1.vi" Type="VI" URL="../OpenConnection/OpenConnectionInstances/OpenConnection_Control1.vi"/>
				<Item Name="OpenConnection_Control2.vi" Type="VI" URL="../OpenConnection/OpenConnectionInstances/OpenConnection_Control2.vi"/>
				<Item Name="OpenConnection_DBL.vi" Type="VI" URL="../OpenConnection/OpenConnectionInstances/OpenConnection_DBL.vi"/>
				<Item Name="OpenConnection_String.vi" Type="VI" URL="../OpenConnection/OpenConnectionInstances/OpenConnection_String.vi"/>
			</Item>
			<Item Name="OpenConnection.vi" Type="VI" URL="../OpenConnection/OpenConnection.vi"/>
		</Item>
		<Item Name="ReadValue" Type="Folder">
			<Item Name="ReadValueInstances" Type="Folder">
				<Item Name="ReadValue_Control1.vi" Type="VI" URL="../ReadValue/ReadValueInstances/ReadValue_Control1.vi"/>
				<Item Name="ReadValue_Control2.vi" Type="VI" URL="../ReadValue/ReadValueInstances/ReadValue_Control2.vi"/>
				<Item Name="ReadValue_DBL.vi" Type="VI" URL="../ReadValue/ReadValueInstances/ReadValue_DBL.vi"/>
				<Item Name="ReadValue_String.vi" Type="VI" URL="../ReadValue/ReadValueInstances/ReadValue_String.vi"/>
			</Item>
			<Item Name="ReadValue.vi" Type="VI" URL="../ReadValue/ReadValue.vi"/>
		</Item>
		<Item Name="Typedefs" Type="Folder">
			<Item Name="Control 1.ctl" Type="VI" URL="../Typedefs/Control 1.ctl"/>
			<Item Name="Control 2.ctl" Type="VI" URL="../Typedefs/Control 2.ctl"/>
		</Item>
		<Item Name="WriteValue" Type="Folder">
			<Item Name="WriteValueInstances" Type="Folder">
				<Item Name="WriteValue_DBL.vi" Type="VI" URL="../WriteValue/WriteValueInstances/WriteValue_DBL.vi"/>
				<Item Name="WriteValue_String.vi" Type="VI" URL="../WriteValue/WriteValueInstances/WriteValue_String.vi"/>
				<Item Name="WriteValue_Control1.vi" Type="VI" URL="../WriteValue/WriteValueInstances/WriteValue_Control1.vi"/>
				<Item Name="WriteValue_Control2.vi" Type="VI" URL="../WriteValue/WriteValueInstances/WriteValue_Control2.vi"/>
			</Item>
			<Item Name="WriteValue.vi" Type="VI" URL="../WriteValue/WriteValue.vi"/>
		</Item>
		<Item Name="main.vi" Type="VI" URL="../main.vi"/>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
