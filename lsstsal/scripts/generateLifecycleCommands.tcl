set SAL_GENERIC_COMMANDS "
<SALCommand>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_command_start</EFDB_Topic>
 <Alias>start</Alias>
 <Device>Settings</Device>
 <Property>set</Property>
 <Action>apply</Action>
 <Value></Value>
 <Explanation>http://project.lsst.org/ts/sal_objects/help/[set SALSubsys]_command_start.html</Explanation>
    <item>
      <EFDB_Name>settingsToApply</EFDB_Name>
      <Description>Subsystem Configuration to apply at start</Description>
       <IDL_Type>string</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALCommand>

<SALCommand>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_command_stop</EFDB_Topic>
 <Alias>stop</Alias>
 <Device>all</Device>
 <Property>motion</Property>
 <Action>stop</Action>
 <Value></Value>
 <Explanation>http://project.lsst.org/ts/sal_objects/help/[set SALSubsys]_command_stop.html</Explanation>
    <item>
      <EFDB_Name>value</EFDB_Name>
      <Description>Subsystem value</Description>
       <IDL_Type>boolean</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALCommand>

<SALCommand>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_command_abort</EFDB_Topic>
 <Alias>abort</Alias>
 <Device>all</Device>
 <Property></Property>
 <Action>abort</Action>
 <Value></Value>
 <Explanation>http://project.lsst.org/ts/sal_objects/help/[set SALSubsys]_command_abort.html</Explanation>
    <item>
      <EFDB_Name>value</EFDB_Name>
      <Description>Subsystem value</Description>
       <IDL_Type>boolean</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALCommand>

<SALCommand>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_command_enable</EFDB_Topic>
 <Alias>enable</Alias>
 <Device>controller</Device>
 <Property>command</Property>
 <Action></Action>
 <Value></Value>
 <Explanation>http://project.lsst.org/ts/sal_objects/help/[set SALSubsys]_command_enable.html</Explanation>
    <item>
      <EFDB_Name>value</EFDB_Name>
      <Description>Subsystem value</Description>
       <IDL_Type>boolean</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALCommand>

<SALCommand>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_command_disable</EFDB_Topic>
 <Alias>disable</Alias>
 <Device>controller</Device>
 <Property>command</Property>
 <Action></Action>
 <Value></Value>
 <Explanation>http://project.lsst.org/ts/sal_objects/help/[set SALSubsys]_command_disable.html</Explanation>
    <item>
      <EFDB_Name>value</EFDB_Name>
      <Description>Subsystem value</Description>
       <IDL_Type>boolean</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALCommand>

<SALCommand>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_command_standby</EFDB_Topic>
 <Alias>standby</Alias>
 <Device>controller</Device>
 <Property>command</Property>
 <Action>stop</Action>
 <Value></Value>
 <Explanation>http://project.lsst.org/ts/sal_objects/help/[set SALSubsys]_command_standby.html</Explanation>
    <item>
      <EFDB_Name>value</EFDB_Name>
      <Description>Subsystem value</Description>
       <IDL_Type>boolean</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALCommand>

<SALCommand>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_command_exitControl</EFDB_Topic>
 <Alias>exitControl</Alias>
 <Device>controller</Device>
 <Property>command</Property>
 <Action>exit</Action>
 <Value></Value>
 <Explanation>http://project.lsst.org/ts/sal_objects/help/[set SALSubsys]_command_exitControl.html</Explanation>
    <item>
      <EFDB_Name>value</EFDB_Name>
      <Description>Subsystem value</Description>
       <IDL_Type>boolean</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALCommand>

<SALCommand>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_command_enterControl</EFDB_Topic>
 <Alias>enterControl</Alias>
 <Device>controller</Device>
 <Property>command</Property>
 <Action>allow</Action>
 <Value>network</Value>
 <Explanation>http://project.lsst.org/ts/sal_objects/help/[set SALSubsys]_command_enterControl.html</Explanation>
    <item>
      <EFDB_Name>value</EFDB_Name>
      <Description>Subsystem value</Description>
       <IDL_Type>boolean</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALCommand>

<SALCommand>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_command_SetValue</EFDB_Topic>
 <Alias>SetValue</Alias>
 <Device>controller</Device>
 <Property>configuration</Property>
 <Action>set</Action>
 <Value></Value>
 <Explanation>http://project.lsst.org/ts/sal_objects/help/[set SALSubsys]_command_SetValue.html</Explanation>
    <item>
      <EFDB_Name>json_parameters</EFDB_Name>
      <Description>JSON string describing the parameter(s) to be set and their values</Description>
       <IDL_Type>string</IDL_Type>
      <Units> </Units>
      <Count>1</Count>
    </item>
</SALCommand>
"

