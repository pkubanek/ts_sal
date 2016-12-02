#!/usr/bin/tclsh

# set SAL_DIR $env(SAL_DIR)
# set SAL_WORK_DIR $env(SAL_WORK_DIR)
# source $SAL_DIR/versioning.tcl
#

proc mavenize { subsys } {
global env SAL_WORK_DIR SAL_DIR SALVERSION
  exec mkdir -p $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/src/main/java/org/lsst/sal/[set subsys]
  exec mkdir -p $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/src/test/java
  exec mkdir -p $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/src/main/resources
  set fout [open $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/pom.xml w]
  puts $fout "
<project xmlns=\"http://maven.apache.org/POM/4.0.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"
  xsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd\">
  <modelVersion>4.0.0</modelVersion>

  <groupId>org.lsst.lsst-tsvm</groupId>
  <artifactId>sal_[set subsys]</artifactId>
  <packaging>jar</packaging>
  <name>sal_[set subsys]</name>
  <version>$SALVERSION</version>

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
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>3.8.1</version>
            <scope>test</scope>
        </dependency>
        <dependency>
            <groupId>openslice.dds</groupId>
            <artifactId>dcpssaj</artifactId>
            <version>6.4.0</version>
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
  </project>
"
  close $fout
  foreach i [glob $SAL_WORK_DIR/idl-templates/validated/[set subsys]_*.idl] {
     set id [join [lrange [split [file tail [file rootname $i]] _] 1 end] _]
     set type [lindex [split $id _] 0]
     if { $type != "command" && $type != "logevent" } {
       exec cp $SAL_WORK_DIR/[set subsys]_[set id]/java/src/[set subsys]_[set id]DataPublisher.java $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/src/test/java/.
       exec cp $SAL_WORK_DIR/[set subsys]_[set id]/java/src/[set subsys]_[set id]DataSubscriber.java $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/src/test/java/.
       puts stdout "Processed $id"
     }
  }
  set allj [glob $SAL_WORK_DIR/$subsys/java/src/*.java]
  foreach fj $allj {
     exec cp $fj $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/src/test/java/.
     puts stdout "Processed $fj"
  }
  exec cp $SAL_WORK_DIR/$subsys/java/src/org/lsst/sal/SAL_[set subsys].java $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/src/main/java/org/lsst/sal/.
  exec cp $SAL_WORK_DIR/$subsys/java/src/org/lsst/sal/salActor.java $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/src/main/java/org/lsst/sal/.
  exec cp -r $SAL_WORK_DIR/$subsys/java/$subsys $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/src/main/java/.
  exec mkdir -p $SAL_WORK_DIR/maven/libs
  exec cp $env(OSPL_HOME)/jar/dcpssaj.jar $SAL_WORK_DIR/maven/libs/.
  exec cp $SAL_DIR/../lib/junit.jar $SAL_WORK_DIR/maven/libs/.
}


proc mavenunittests { subsys } {
global env SAL_WORK_DIR SAL_DIR SALVERSION CMD_ALIASES CMDS SYSDIC 
   if { [info exists SYSDIC($subsys,keyedID)] } {
       set initializer "( (short) 1)"
   } else {
       set initializer "()"
   }
  set fout [open $SAL_WORK_DIR/maven/[set subsys]_[set SALVERSION]/src/test/java/[set subsys]CommanderTest.java w]
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
  set cmds [split [exec grep "pragma keylist command_" $SAL_WORK_DIR/idl-templates/validated/sal/sal_[set subsys].idl] \n]
  foreach i $cmds {
     set alias [lindex [split [lindex $i 2] _] 1]
     puts $fout "
  public void test[set subsys]Commander_[set alias]() \{
	    SAL_[set subsys] mgr = new SAL_[set subsys][set initializer];

	    // Issue command
            int cmdId=0;
            int status=0;
            int timeout=1;

  	    mgr.salCommand(\"[set subsys]_command_[set alias]\");
	    [set subsys].command_[set alias] command  = new [set subsys].command_[set alias]();

	    command.private_revCode = \"LSST TEST COMMAND\";
	    command.device = \"$alias\";
	    command.property =  \"\";
	    command.action =  \"\";
	    command.value = \"\";

	    cmdId = mgr.issueCommand_[set alias](command);

	    try \{Thread.sleep(1000);\} catch (InterruptedException e)  \{ e.printStackTrace(); \}
	    status = mgr.waitForCompletion_[set alias](cmdId, timeout);

	    /* Remove the DataWriters etc */
	    mgr.salShutdown();

  \}
"
  }
  puts $fout "
\}"
  close $fout
}



