
proc mavenize { subsys } {
global SAL_WORK_DIR SAL_DIR
  exec mkdir -p $SAL_WORK_DIR/sal_[set subsys]/src/main/java/org/lsst/sal/[set subsys]
  exec mkdir -p $SAL_WORK_DIR/sal_[set subsys]/src/test/java
  exec mkdir -p $SAL_WORK_DIR/sal_[set subsys]/src/main/resources
  set fout [open $SAL_WORK_DIR/sal_[set subsys]/pom.xml w]
  puts $fout "
<project xmlns=\"http://maven.apache.org/POM/4.0.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
  xsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd\">
  <modelVersion>4.0.0</modelVersion>

  <groupId>org.lsst.lsst-tsvm</groupId>
  <artifactId>sal_camera</artifactId>
  <packaging>jar</packaging>
  <name>sal_camera</name>
  <version>2.1.0</version>

  <url>http://lsst-tsvm.lsst.org</url>
  <licenses>
   <license>
    <name>LSST GPL</name>
    <url>http://lsst-tsvm.lsst.org/LICENSE/</url>
    <distribution>repo</distribution>
    <comments>A business-friendly OSS license</comments>
   </license>
  </licenses>
  <organization>
      <name>LSST</name>
         <url>http://lsst-tsvm.lsst.org</url>
  </organization>
  <developers>
   <developer>
    <id>dmills</id>
    <name>Dave Mills</name>
    <email>dmills@lsst.org</email>
    <url>http://www.lsstcorp.org</url>
    <organization>LSST</organization>
    <roles>
      <role>developer</role>
    </roles>
    <timezone>-7</timezone>
   </developer>
  </developers>
  <properties>
    <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
  </properties>
  <build>
    <plugins>
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-compiler-plugin</artifactId>
        <version>3.2</version>
        <configuration>
        <verbose>true</verbose>
        <fork>true</fork>
        <executable>/opt/jdk1.6.0_43/bin/javac</executable>
          <compilerArguments>
            <classpath>${project.basedir}/target/classes/:${project.basedir}/libs/dcpssaj.jar:.</classpath>
          </compilerArguments>
        </configuration>
      </plugin>
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-surefire-plugin</artifactId>
        <version>2.18.1</version>
        <configuration>
          <additionalClasspathElements>
            <additionalClasspathElement>${project.basedir}/libs/junit-3.8.1.jar</additionalClasspathElement>
            <additionalClasspathElement>${project.basedir}/libs/dcpssaj.jar</additionalClasspathElement>
          </additionalClasspathElements>
        </configuration>
      </plugin>
      <plugin>
        <artifactId>maven-invoker-plugin</artifactId>
        <version>1.9</version>
        <configuration>
          <debug>true</debug>
          <projectsDirectory>src/test</projectsDirectory>
          <preBuildHookScript>setup.tcl</preBuildHookScript>
          <postBuildHookScript>runtests.tcl</postBuildHookScript>
        </configuration>
        <executions>
          <execution>
            <id>integration-test</id>
            <goals>
              <goal>run</goal>
            </goals>
          </execution>
       </executions>
      </plugin>
    </plugins>
  </build>
  <reporting>                                                                              
    <plugins>                                                                            
        <plugin>                                                                         
            <groupId>org.apache.maven.plugins</groupId>                                  
            <artifactId>maven-javadoc-plugin</artifactId>                                
            <version>2.9</version>                                                       
            <configuration>                                                              
                <doclet>org.umlgraph.doclet.UmlGraphDoc</doclet>                         
                <docletArtifact>                                                         
                    <groupId>org.umlgraph</groupId>                                      
                    <artifactId>umlgraph</artifactId>                                    
                    <version>5.6</version>                                               
                </docletArtifact>                                                        
                <additionalparam>-views -all</additionalparam>                           
                <useStandardDocletOptions>true</useStandardDocletOptions>                
            </configuration>                                                             
        </plugin>                                                                        
    </plugins>                                                                           
  </reporting>     

  <dependencies>
     <dependency>
        <groupId>DDS</groupId>
        <artifactId>OpenSplice-dcpssaj</artifactId>
        <version>6.4.0</version>
        <!-- scope>system</scope>
        <systemPath>${project.basedir}/libs/dcpssaj.jar</systemPath-->
    </dependency>

    <dependency>
      <groupId>junit</groupId>
      <artifactId>junit</artifactId>
      <version>3.8.1</version>
      <scope>test</scope>
    </dependency>
  </dependencies>
  <repositories>
        <repository>
            <id>ocs-maven2-public</id>
            <name>OCS Maven 2 central repository</name>
               <url>http://dev.lsstcorp.org:8081/nexus/content/groups/ocs-maven2-public/</url>
        </repository>
  </repositories>
  <distributionManagement>
        <repository>
            <id>ocs-maven2</id>
            <name>OCS Maven2 Release repository</name>
               <url>http://dev.lsstcorp.org:8081/nexus/content/repositories/ocs-maven2/</url>
        </repository>
        <snapshotRepository>
            <id>ocs-maven2-snapshots</id>
            <name>OCS Maven2 SNAPSHOTS repository</name>
               <url>http://dev.lsstcorp.org:8081/nexus/content/repositories/ocs-maven2-snapshots/</url>
        </snapshotRepository>
        <site>
            <id>ocs-maven2-site</id>
            <name>OCS Maven2 site repository</name>
                 <url>dav:http://dev.lsstcorp.org:8081/nexus/content/sites/ocs-site/</url>
        </site>
  </distributionManagement>
  <build>
        <extensions>
            <extension>
		<groupId>org.apache.maven.wagon</groupId>
		<artifactId>wagon-webdav-jackrabbit</artifactId>
                <version>2.4</version>
            </extension>
        </extensions>
   </build>
</project>
"
  close $fout
  foreach i [glob $SAL_WORK_DIR/[set subsys]*.idl] {
     set id [join [lrange [split [file tail [file rootname $i]] _] 1 end] _]
     catch {
       exec cp $SAL_WORK_DIR/[set subsys]_[set id]/java/src/[set subsys]_[set id]DataPublisher.java $SAL_WORK_DIR/sal_[set subsys]/src/test/java/.
       exec cp $SAL_WORK_DIR/[set subsys]_[set id]/java/src/[set subsys]_[set id]DataSubscriber.java $SAL_WORK_DIR/sal_[set subsys]/src/test/java/.
       puts stdout "Processed $id"
     }
  }
  exec cp $SAL_WORK_DIR/$subsys/java/src/ErrorHandler.java $SAL_WORK_DIR/sal_[set subsys]/src/test/java/.
  exec cp $SAL_WORK_DIR/$subsys/java/src/[set subsys]Event.java $SAL_WORK_DIR/sal_[set subsys]/src/test/java/.
  exec cp $SAL_WORK_DIR/$subsys/java/src/[set subsys]EventLogger.java $SAL_WORK_DIR/sal_[set subsys]/src/test/java/.
  exec cp $SAL_WORK_DIR/$subsys/java/src/[set subsys]Commander.java $SAL_WORK_DIR/sal_[set subsys]/src/test/java/.
  exec cp $SAL_WORK_DIR/$subsys/java/src/[set subsys]Controller.java $SAL_WORK_DIR/sal_[set subsys]/src/test/java/.
  exec cp $SAL_WORK_DIR/$subsys/java/src/org/lsst/sal/SAL_[set subsys].java $SAL_WORK_DIR/sal_[set subsys]/src/main/java/org/lsst/sal/.
  exec cp -r $SAL_WORK_DIR/$subsys/java/$subsys $SAL_WORK_DIR/sal_[set subsys]/src/main/java/.
}


proc mavenunittests { subsys } {
global SAL_WORK_DIR SAL_DIR
  set fout $SAL_WORK_DIR/sal_[set subsys]/src/test/java/[set subsys]CommanderTest.java w]
  puts $fout "
package org.lsst.sal.junit.[set subsys];

import junit.framework.TestCase;
import [set subsys].*;
import org.lsst.sal.SAL_[set subsys];

public class [set subsys]CommanderTest extends TestCase \{
  
   public [set subsys]CommanderTest(String name) \{
      super(name);
   \}

"
  set cmds [exec grep "struct command" $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl]
  foreach i $cmds {
     set alias [lindex [split [lindex $i 1] _] 1]
     puts $fout "
  public void test[set subsys]Commander_configure() \{
	    SAL_[set subsys] mgr = new SAL_[set subsys]();

	    // Issue command
            int cmdId=0;
            int status=0;
            int timeout=1;

  	    mgr.salCommand();
	    [set subsys].command command  = new [set subsys].command();

	    command.private_revCode = \"LSST TEST COMMAND\";
	    command.device = \"$alias\";
	    command.property =  \"\";
	    command.action =  \"\";
	    command.value = \"\";

	    cmdId = mgr.issueCommand(command);

	    try \{Thread.sleep(1000);\} catch (InterruptedException e)  \{ e.printStackTrace(); \}
	    status = mgr.waitForCompletion(cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

  \}
"
  }
  puts $fout "
\}"
  close $fout
}


