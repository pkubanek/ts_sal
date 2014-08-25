====================================================================
How to download, install, & configure Prismtech OpenSplice IDS compiler, runtime, libraries:
====================================================================
Goto web site and download OpenSplice DDS Community Edition 
register here:  http://www.opensplice.com/user.asp  
download here:  http://www.opensplice.org/cgi-bin/twiki/view/Community/Downloads

I used 4.1 for my testing (for gcc4.1.2 and gnuc2.5), your errors may vary.
http://www.opensplice.org/releases/downloads/releases/OpenSpliceDDSV4.1.090617-x86.linux2.6-gcc412-gnuc25-HDE.tar.gz

cd /opt/dev-tools
mkdir OpenSpliceDDSV4.1.0-x86.linux2.6
mv /tmp/OpenSpliceDDSV4.1.090617-x86.linux2.6-gcc412-gnuc25-HDE.tar.gz /opt/dev-tools/OpenSpliceDDSV4.1.0-x86.linux2.6
tar -xzf OpenSpliceDDSV4.1.090617-x86.linux2.6-gcc412-gnuc25-HDE.tar.gz


====================================================================
Got Doc ? :
====================================================================
http://activemq.apache.org/camel/dds.html


====================================================================
How to check out prismtech DDS code :
====================================================================

You can browse our SVN repository at http://65.164.187.133/svn/apache.

There are two projects: camel-dds and maven-dds.

Commands to check them out are:
svn checkout svn://65.164.187.133/apache/camel-dds/trunk camel-dds
svn checkout svn://65.164.187.133/apache/maven-dds/trunk maven-dds

If for some reason the SVN native protocol doesn't work, you can use http with commands like:
svn checkout http://65.164.187.133/svn/apache/camel-dds/trunk camel-dds
svn checkout http://65.164.187.133/svn/apache/maven-dds/trunk maven-dds

Let me know if you'd like me to create an account for you so you can commit changes.

====================================================================
How to build Prismtech OpenSplice maven-dds plugin, and camel-dss component
====================================================================
--- Open a new shell

--- Set environment variables in your system/shell prior to building maven-dds or camel-dds components. Add the Maven bin directory to your path, set JAVA_HOME and add the Java executable to your path. Also, the release.com script within the OpenSplice installation needs to be edited by hand, replace the string @@INSTALLDIR@@ with the location of the OpenSplice installation.

cd ~/workspace/maven-dds/plugins/opensplice-idl-plugin
source /opt/dev_tools/OpenSpliceDDSV4.1.0-x86.linux2.6/HDE/x86.linux2.6/release.com
M2=$OSPL_HOME
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$OSPL_HOME/lib/

mvn clean
mvn package 
mvn install

cd ~/workspace/camel-dds/components/camel-dds
<if in a different shell> source /opt/dev_tools/OpenSpliceDDSV4.1.0-x86.linux2.6/HDE/x86.linux2.6/release.com

To build camel-dds the OpenSplice jar dcpssaj.jar needs to be installed into the Maven repository. A utility script is provided in camel-dds/docs to install this jar. OpenSplice needs to be running for the camel-dds tests to run.

We have found that the test process hangs on linux, and ospl stop needs to force the process to quit (you can see this by running "ospl stop"). Attempts to repeat the tests without stopping OpenSplice may result in SIGSEGV and a hotspot error generated from the jvm. If this error occurs then stop and restart OpenSplice, you may need to kill any rogue java processes. You can see that the tests pass from the package step, but the hang prevents Maven from installing the jar for us to use, to work around this issue we just run a cut down version of the tests for now. This only seems to affect the Linux platform at this time.

mvn clean
ospl start
mvn package
mvn install

The cut down test suite command is :

mvn -Dtest=org.apache.camel.component.dds.QoSSettingTest,org.apache.camel.component.dds.ContentFilteredTopic_Expr3Test,org.apache.camel.component.dds.camelcentric.CamelDdsTopicTest,org.apache.camel.component.dds.DdsEndpointTest,org.apache.camel.component.dds.ContentFilteredTopicURITest,org.apache.camel.component.dds.MultipleInputRouteTest,org.apache.camel.component.dds.ContentFilteredTopic_Expr1Test,org.apache.camel.component.dds.camelcentric.DDSProducerRouteTest,org.apache.camel.component.dds.UriConfigurationTest,org.apache.camel.component.dds.ContentFilteredTopic_Expr2Test,org.apache.camel.component.dds.camelcentric.UriConfigurationTest install