set SAL_GENERIC_EVENTS "
<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<?xml-stylesheet type=\"text/xsl\" href=\"http://lsst-sal.tuc.noao.edu/schema/SALEventSet.xsl\"?>
<SALEventSet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
	xsi:noNamespaceSchemaLocation=\"http://lsst-sal.tuc.noao.edu/schema/SALEventSet.xsd\">

<SALEvent>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_logevent_SettingVersions</EFDB_Topic>
 <Alias>SettingVersions</Alias>
 <Device>configuration</Device>
 <Property>settings</Property>
 <Action>list</Action>
 <Value></Value>
 <Explanation>http://sal.lsst.org/SAL/Events/[set SALSubsys]_logevent_SettingVersions.html</Explanation>
    <item>
      <EFDB_Name>recommendedSettingVersion</EFDB_Name>
      <Description>Comma delimited set of available Setting Sets</Description>
       <IDL_Type>string</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALEvent>

<SALEvent>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_logevent_SummaryState</EFDB_Topic>
 <Alias>SummaryState</Alias>
 <Device>statemachine</Device>
 <Property>state</Property>
 <Action></Action>
 <Value></Value>
 <Explanation>http://sal.lsst.org/SAL/Events/[set SALSubsys]_logevent_SummaryState.html</Explanation>
    <item>
      <EFDB_Name>SummaryStateValue</EFDB_Name>
      <Description>Enumerated state id</Description>
       <IDL_Type>long</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALEvent>

<SALEvent>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_logevent_ErrorCode</EFDB_Topic>
 <Alias>ErrorCode</Alias>
 <Device>statemachine</Device>
 <Property>error</Property>
 <Action></Action>
 <Value></Value>
 <Explanation>http://sal.lsst.org/SAL/Events/[set SALSubsys]_logevent_ErrorCode.html</Explanation>
    <item>
      <EFDB_Name>errorCode</EFDB_Name>
      <Description>Error code value</Description>
       <IDL_Type>long</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALEvent>

<SALEvent>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_logevent_AppliedSettingsMatchStart</EFDB_Topic>
 <Alias>AppliedSettingsMatchStart</Alias>
 <Device>statemachine</Device>
 <Property>state</Property>
 <Action></Action>
 <Value></Value>
 <Explanation>http://sal.lsst.org/SAL/Events/[set SALSubsys]_logevent_AppliedSettingsMatchStart.html</Explanation>
    <item>
      <EFDB_Name>appliedSettingsMatchStartIsTrue</EFDB_Name>
      <Description>Confirmation that required settings have been achieved</Description>
       <IDL_Type>boolean</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALEvent>

</SALEventSet>"

