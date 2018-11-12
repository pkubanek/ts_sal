set SAL_MIN_TELEMETRY "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<?xml-stylesheet type=\"text/xsl\" href=\"http://project.lsst.org/ts/sal_objects/schema/SALTelemetrySet.xsl\"?>
<SALTelemetrySet xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
	xsi:noNamespaceSchemaLocation=\"http://project.lsst.org/ts/sal_objects/schema/SALTelemetrySet.xsd\">
<SALTelemetry>
 <Subsystem>[set SALSubsys]</Subsystem>
 <Version>$SALVERSION</Version>
 <Author>salgenerator</Author>
 <EFDB_Topic>[set SALSubsys]_exists</EFDB_Topic>
 <Explanation>http://project.lsst.org/ts/sal_objects/help/[set SALSubsys]_exists.html</Explanation>
    <item>
      <EFDB_Name>item1</EFDB_Name>
      <Description>Dummy item</Description>
      <IDL_Type>int</IDL_Type>
      <Units></Units>
      <Count>1</Count>
    </item>
</SALTelemetry>
</SALTelemetrySet>"


