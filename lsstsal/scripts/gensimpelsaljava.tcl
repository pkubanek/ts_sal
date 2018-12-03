#!/usr/bin/env tclsh
#
#  Generate a simpleSAL maven project for a subsystem
#

proc gensimplesaldirs { subsys } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set SSAL_BASE $SAL_WORK_DIR/maven/org-lsst-[set subsys]-simple-sal-master
   exec mkdir -p $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]
   exec touch $SAL_WORK_DIR/maven/org-lsst-[set subsys]-simple-sal-master/nbactions.xml
   exec mkdir -p $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/command
   exec mkdir -p $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/event
   exec mkdir -p $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/main
   exec mkdir -p $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/states
   exec mkdir -p $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/telemetry
   exec mkdir -p $SSAL_BASE/src/test/java/org/lsst/sal/[set subsys]
   set fout [open $SSAL_BASE/pom.xml w]
   puts $fout "
<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<project xmlns=\"http://maven.apache.org/POM/4.0.0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" x
si:schemaLocation=\"http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd\">

    <!-- FIXNE: This brings in all sort of dependencies which are not needed -->
    <parent>
        <groupId>org.lsst</groupId>
        <artifactId>org-lsst-ccs</artifactId>
        <version>4.0.10</version>
        <relativePath />
    </parent>

    <name>LSST [set subsys] - Simple SAL libary</name>
    <modelVersion>4.0.0</modelVersion>
    <groupId>org.lsst</groupId>
    <artifactId>org-lsst-sal-[set subsys]</artifactId>
    <version>1.0.0-SNAPSHOT</version>
    <packaging>jar</packaging>
    <url>\${org.lsst.ccs.site.url}</url>
    
    <build>
        <plugins>
            <plugin>
                <groupId>org.apache.maven.plugins</groupId>
                <artifactId>maven-surefire-plugin</artifactId>
                <configuration>
                    <environmentVariables>
                        <LSST_DDS_DOMAIN>test-[set subsys]</LSST_DDS_DOMAIN>
                    </environmentVariables>
                </configuration>
            </plugin>
        </plugins>
    </build>

    <repositories>
        <repository>
            <id>lsst-maven2-public</id>
            <name>LSST Maven 2 central repository</name>
            <url>http://dev.lsstcorp.org:8081/nexus/content/groups/[set subsys]-maven2-public/</url>
        </repository>
        <repository>
            <id>ocs-maven2-public</id>
            <name>OCS Maven 2 central repository</name>
            <url>http://dev.lsstcorp.org:8081/nexus/content/groups/ocs-maven2-public/</url>
        </repository>
    </repositories>

    <distributionManagement>
        <site>
            <id>lsst-maven2-site</id>
            <name>LSST Maven2 central site repository</name>
            <url>dav:\${org.lsst.ccs.site.url}</url>
        </site>
    </distributionManagement>

    <properties>
        <org.lsst.ccs.site.url>http://dev.lsstcorp.org:8081/nexus/content/sites/\${org.lsst.ccs.site.name}/
site-root/org-lsst-sal-[set subsys]/\${project.version}/\${project.artifactId}</org.lsst.ccs.site.url>
    </properties>

    <dependencies>
        <dependency>
            <groupId>org.lsst.lsst-tsvm</groupId>
            <artifactId>sal_[set subsys]</artifactId>
            <version>[set SALVERSION]</version>
        </dependency>
    </dependencies>
</project>

"
   close $fout
   set fout [open $SSAL_BASE/README.md w]
   puts $fout "# SimpleSAL
A simplified Java interface to SAL (salgenerator alpha test version).
"
   close $fout
}

proc gensimplesalcmdsuper { subsys } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/[set subsys]Command.java w]
   puts $fout "
package org.lsst.sal.[set subsys];

import java.time.Duration;
import org.lsst.sal.SAL_[set subsys];

/**
 * Super class for all [set subsys] commands,
 *
 * @author tonyj
 */
public abstract class [set subsys]Command \{

    private SAL_[set subsys] mgr;
    private int cmdId;

    /**
     * Constructor used for preparing a command to be sent. Note that the cmdId
     * is always zero in this case (it will be set internally when the command
     * is issued).
     */
    public [set subsys]Command() \{
    \}

    /**
     * Used to set the cmdId and manager when the command is received.
     *
     * @param cmdId The cmdId associated withe the command
     * @param mgr The SAL manager that received the command
     */
    void setManager(int cmdId, SAL_[set subsys] mgr) \{
        this.cmdId = cmdId;
        this.mgr = mgr;
    \}

    /**
     * (optionally) called by the receiver of the command to acknowledge the
     * command was relieved and accepted.
     *
     * @param timeToComplete The estimated time for completion of the command.
     */
    public void acknowledgeCommand(Duration timeToComplete) \{
        acknowledgeCommand(SAL_[set subsys].SAL__CMD_INPROGRESS, (int) timeToComplete.getSeconds(), \"Ack : OK\");
    \}

    /**
     * Called by the receiver of the command to indicate the command has been
     * completed successfully.
     */
    public void reportComplete() \{
        acknowledgeCommand(SAL_[set subsys].SAL__CMD_COMPLETE, 0, \"Done : OK\");
    \}

    /**
     * Called by the receiver to indicate that the command execution failed.
     *
     * @param ex The exception containing the reason for failure.
     */
    public void reportError(Exception ex) \{
        acknowledgeCommand(SAL_[set subsys].SAL__CMD_FAILED, 0, \"Error : \" + ex.getMessage());
    \}

    /**
     * Called by the receiver of the command to indicate that the command was
     * rejected.
     *
     * @param reason The reason for rejection.
     */
    public void rejectCommand(String reason) \{
        acknowledgeCommand(SAL_[set subsys].SAL__CMD_FAILED, 0, \"Ack : NO \" + reason);
    \}

    public int getCmdId() \{
        return cmdId;
    \}

    protected SAL_[set subsys] getManager() \{
        return mgr;
    \}

    protected abstract void acknowledgeCommand(int response, int timeout, String message);

    protected abstract int issueCommand(SAL_[set subsys] mgr);

    protected abstract void waitForResponse(SAL_[set subsys] mgr, int cmdId, Duration timeout);
\}
"
   close $fout
}


proc gensimplesalevtsuper { subsys } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/[set subsys]Event.java w]
   puts $fout "
package org.lsst.sal.[set subsys];

import org.lsst.sal.SAL_[set subsys];

/**
 * A base class for all [set subsys] events.
 * @author tonyj
 */
public abstract class [set subsys]Event \{

    private final int priority;
    
    protected [set subsys]Event(int priority) \{
        this.priority = priority;
    \}

    public int getPriority() \{
        return priority;
    \}

    protected abstract void logEvent(SAL_[set subsys] mgr);
\}
"
   close $fout
}

proc gensimplesaltlmsuper { subsys } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/[set subsys]Telemetry.java w]
   puts $fout "
package org.lsst.sal.[set subsys];

/**
 * Generic exception thrown if a communication error occurs.
 * @author tonyj
 */
public class SALException extends Exception \{

    private static final long serialVersionUID = -4498159426443909034L;
    SALException(String message, Throwable cause) \{
        super(message,cause);
    \}
\}
"
   close $fout 
}


proc gensimplesalmain { subsys } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/[set subsys]/main/Main.java w]
   puts $fout "
package org.lsst.sal.[set subsys].main;

import java.time.Duration;
import org.lsst.sal.[set subsys].[set subsys]Command;
import org.lsst.sal.[set subsys].SAL[set subsys];
import org.lsst.sal.[set subsys].SALException;

/**
 *
 * @author tonyj
 */
public class Main \{
    public static void main(String[] args) throws SALException, InterruptedException \{
        SAL[set subsys] [set subsys] = SAL[set subsys].create();
        [set subsys]Command command = [set subsys].getNextCommand(Duration.ofSeconds(60));
        System.out.println(\"Got \"+command);
        command.acknowledgeCommand(Duration.ofSeconds(1));
        Thread.sleep(500);
        command.reportComplete();
    \}
\}
"
   close $fout 
   set fout [open $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/[set subsys]/main/Main2.java w]
   puts $fout "
package org.lsst.sal.[set subsys].main;

import java.time.Duration;
import org.lsst.sal.[set subsys].CommandResponse;
import org.lsst.sal.[set subsys].command.EnableCommand;
import org.lsst.sal.[set subsys].SAL[set subsys];
import org.lsst.sal.[set subsys].SALException;

/**
 *
 * @author tonyj
 */
public class Main2 \{
    public static void main(String[] args) throws SALException \{
       SAL[set subsys] [set subsys] = SAL[set subsys].create();
       CommandResponse response = [set subsys].issueCommand(new EnableCommand());
       response.waitForResponse(Duration.ofSeconds(10));
    \}
\}
"
   close $fout 
}


proc gensimplesaltlmsuper { subsys } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/[set subsys]Telemetry.java w]
   puts $fout "
package org.lsst.sal.[set subsys];

import org.lsst.sal.SAL_[set subsys];

/**
 * Base class for all [set subsys] telemetry
 * @author tonyj
 */
public abstract class [set subsys]Telemetry \{
    public [set subsys]Telemetry() {
        
    \}

    abstract void putSample(SAL_[set subsys] mgr);
\}
"
   close $fout
}

proc gensimplesalimpl { subsys } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/[set subsys]Implementation.java w]
   puts $fout "
package org.lsst.sal.[set subsys];

import java.time.Duration;
import java.time.Instant;
import org.lsst.sal.SAL_[set subsys];
import org.lsst.sal.[set subsys].event.GenericEvent;"

   puts $fout "
import org.lsst.sal.[set subsys].states.SummaryStateEvent;
"

   puts $fout "
import org.lsst.sal.[set subsys].event.StartRaftIntegrationEvent;
"

   puts $fout "
import org.lsst.sal.[set subsys].command.TakeImagesCommand;
"

   puts $fout "
/**
 * An implementation of SAL[set subsys] which works by using the existing SAL
 * interface. This can be used as-is, but might be better generated by SAL.
 *
 * @author tonyj
 */
class SAL[set subsys]Implementation extends SAL[set subsys] \{

    private final SAL_[set subsys] mgr;

    SAL[set subsys]Implementation() \{
        mgr = new SAL_[set subsys]();
        // TODO: Some checks that connection was succesful, to prevent later
        // unexpected errors  
"

   puts $fout "      
        mgr.salProcessor(\"[set subsys]_command_setFilter\");
        // Telemetry (note may also need salTelemetrySub to subscribe)
"

   puts $fout "
        mgr.salTelemetryPub(\"[set subsys]_Cold\");
"

   puts $fout "
        // Events
        mgr.salEvent(\"[set subsys]_logevent_SummaryState\");
"

   puts $fout "
    \}

    @Override
    @SuppressWarnings(\"SleepWhileInLoop\")
    public [set subsys]Command getNextCommand(Duration timeout) throws SALException \{
        Instant stop = Instant.now().plus(timeout);
        int cmdId = 0;
        // Currently we have to poll for each command
"

   puts $fout "
        [set subsys].command_startImage startImageCommand = new [set subsys].command_startImage();
"

   puts $fout "
        while (!Instant.now().isAfter(stop)) \{
"

   puts $fout "
            cmdId = mgr.acceptCommand_takeImages(takeImagesCommand);
            if (cmdId > 0) \{
                [set subsys]Command cmd = new TakeImagesCommand(takeImagesCommand.expTime, takeImagesCommand.numImages, takeImagesCommand.shutter,
                        takeImagesCommand.science, takeImagesCommand.wfs, takeImagesCommand.guide, takeImagesCommand.imageSequenceName);
                cmd.setManager(cmdId, mgr);
                return cmd;
            \}
"

   puts $fout "
            try \{
                // FIXME: Would be great if we did not have to poll
                Thread.sleep(10);
            \} catch (InterruptedException ex) \{
                throw new SALException(\"Unexpected interupt while polling for command\", ex);
            \}
        \}
        return null; // Timeout
    \}

    @Override
    public CommandResponse issueCommand([set subsys]Command command) throws SALException \{
        int cmdId = command.issueCommand(mgr);
        return new CommandResponse(mgr, command, cmdId);
    \}

    @Override
    public void logEvent([set subsys]Event event) throws SALException \{
        event.logEvent(mgr);
    \}

    @Override
    @SuppressWarnings(\"SleepWhileInLoop\")
    public [set subsys]Event getNextEvent(Duration timeout) throws SALException \{
        Instant stop = Instant.now().plus(timeout);
        int rc = 0;
        // Currently we have to poll for each event
"

   puts $fout "
        [set subsys].logevent_SummaryState summaryStateEvent = new [set subsys].logevent_SummaryState();  
"

   puts $fout "
        while (!Instant.now().isAfter(stop)) \{
            rc = mgr.getEvent_SummaryState(summaryStateEvent);
            if (rc == SAL_[set subsys].SAL__OK) \{
                return new SummaryStateEvent(summaryStateEvent.priority, SummaryStateEvent.LSE209State.values()\[summaryStateEvent.SummaryStateValue\]);
            \}

            rc = mgr.getEvent_idleBusyDetailedState(idleBusy);
            if (rc == SAL_[set subsys].SAL__OK) \{
                return new IdleBusyDetailedStateEvent(idleBusy.priority, IdleBusyDetailedStateEvent.IdleBusyState.values()\[idleBusy.substate\]);
            \}
"

   if { $subsys == "[set subsys]" } {
     puts $fout "
            rc = mgr.getEvent(anEvent);
            if (rc == SAL_[set subsys].SAL__OK) \{
                //TODO: Temporary Hack
                if (anEvent.message.startsWith(\"AvailableFilters: \")) \{
                    return new AvailableFiltersEvent(1, anEvent.message.substring(\"AvailableFilters: \".length()));
                \} else \{
                    return new GenericEvent(0, anEvent.message);
                \}
            \}
"
   }


   puts $fout "
            try \{
                // FIXME: Would be great if we did not have to poll
                Thread.sleep(10);
            \} catch (InterruptedException ex) \{
                throw new SALException(\"Unexpected interupt while polling for event\", ex);
            \}
        \}
        return null; // Timeout        
    \}

    @Override
    public void sendTelemetry([set subsys]Telemetry telemetry) throws SALException \{
        telemetry.putSample(mgr);
    \}

    @Override
    @SuppressWarnings(\"SleepWhileInLoop\")
    public [set subsys]Telemetry getTelemetry(Duration timeout) throws SALException \{
        Instant stop = Instant.now().plus(timeout);

        // Currently we have to poll for each event
"

   puts $fout "
        mgr.salTelemetrySub(\"[set subsys]_Cold\");
        [set subsys].Cold coldData = new [set subsys].Cold();
"

   puts $fout "
        while (!Instant.now().isAfter(stop)) \{
"
   puts $fout "
            int rc = mgr.getSample(coldData);
            if (rc == SAL_[set subsys].SAL__OK) {
                return new [set subsys]ColdTelemetry(coldData);
            \}
"

   puts $fout "
            try \{
                // FIXME: Would be great if we did not have to poll
                Thread.sleep(10);
            \} catch (InterruptedException ex) \{
                throw new SALException(\"Unexpected interupt while polling for event\", ex);
            \}
        \}
        return null; // Timeout 
    \}

    @Override
    public void close() \{
        mgr.salShutdown();
    \}
\}
"
   close $fout
}


proc gensimplesalcommand { subsys command } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/command/[set command]Command.java w]
   puts $fout "
package org.lsst.sal.[set subsys].command;

import java.time.Duration;
import org.lsst.sal.SAL_[set subsys];
import org.lsst.sal.[set subsys].[set subsys]Command;

/**
 *
 * @author Farrukh Azfar
 */
public class [set command]Command extends [set subsys]Command \{
"

   puts $fout "
private int nClears;
    
    public ClearCommand(int nClears) \{
        this.nClears = nClears;
     
    \}

    public int getNClears() \{
        return nClears;
    \}
"

   puts $fout "
    @Override
    protected int issueCommand(SAL_[set subsys] mgr) \{
        [set subsys].command_clear cmd = new [set subsys].command_clear();
        cmd.nClears = nClears;
        int cmdId = mgr.issueCommand_clear(cmd);
        return cmdId;
    \}
"

   puts $fout "

    @Override
    protected void waitForResponse(SAL_[set subsys] mgr, int cmdId, Duration timeout) \{
        mgr.waitForCompletion_clear(cmdId, (int) timeout.getSeconds());
    \}

    @Override
    protected void acknowledgeCommand(int response, int timeout, String message) \{
        getManager().ackCommand_clear(getCmdId(), response, timeout, message);
    \}
"

   puts $fout "
    @Override
    public String toString() \{
        return \"[set command]Command{\" + \"nClears=\" + nClears + '}';
    \}
    
\}
"
   close $fout
}

proc gensimplesalevent { subsys event } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/event/[set event]Event.java w]
   puts $fout "
package org.lsst.sal.[set subsys].event;

import org.lsst.sal.SAL_[set subsys];
import [set subsys].logevent_[set event];
import org.lsst.sal.[set subsys].[set subsys]Event;
/**
 *
 * @author Farrukh Azfar
 */
public class [set event]Event extends [set subsys]Event \{
    
    public [set event]Event(int priority) \{
        super(priority);
    \}

    @Override
    protected void logEvent(SAL_[set subsys] mgr) \{
        // Create events 
        logevent_[set event] event = new logevent_[set event]();
        mgr.logEvent_[set event](event, 0);
    \}

    @Override
    public String toString() \{
        return \"[set event]Event{\" + '}';
    \}
    
\}
"
   close $fout
}

proc gensimplesalevent { subsys telemetry } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/main/java/org/lsst/sal/[set subsys]/[set subsys]/[set telemetry]Telemetry.java w]
   puts $fout "
package org.lsst.sal.[set subsys];

import [set subsys].[set telemetry];
import org.lsst.sal.SAL_[set subsys];

/**
 *
 * @author tonyj
 */
public class [set subsys][set telemetry]Telemetry extends [set subsys]Telemetry {
"

   puts $fout "
    private final float[] Compressor_load = new float\[6\];
"

   puts $fout "

    public [set subsys][set telemetry]Telemetry() {
       
    }
"

   puts $fout "
    [set subsys][set telemetry]Telemetry([set telemetry] data) {
        System.arraycopy(Compressor_load,0,data.Compressor_load,0,Compressor_load.length);
    }
"

   puts $fout "
    public float getUtilityRoom_temperature() {
        return UtilityRoom_temperature;
    }

    public void setUtilityRoom_temperature(float UtilityRoom_temperature) {
        this.UtilityRoom_temperature = UtilityRoom_temperature;
    }
"

   puts $fout "
    @Override
    void putSample(SAL_[set subsys] mgr) {
        [set subsys].[set telemetry] data = new [set subsys].[set telemetry]();
"

   puts stdout "
        data.Compressor_load = Compressor_load;
"

   puts $fout "
        mgr.putSample(data);
    }
    
}
"
   close $fout
}

proc gensimplesalcmdtests { subsys } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/test/java/org/lsst/sal/[set subsys]/CommandSendReceiveTest.java w]
   puts $fout "
package org.lsst.sal.[set subsys];

import java.io.IOException;
import java.time.Duration;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import org.junit.AfterClass;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import org.junit.BeforeClass;
import org.junit.Test;
"
  
   puts $fout "
import org.lsst.sal.[set subsys].command.StartCommand;
"

   puts $fout "
/**
 *
 * @author tonyj
 */
public class CommandSendReceiveTest \{

    private static SAL[set subsys] [set subsys];
    private static ExecutorService executor;

    public CommandSendReceiveTest() \{
    \}

    @BeforeClass
    public static void setUpClass() \{
        [set subsys] = SAL[set subsys].create();
        executor = Executors.newFixedThreadPool(1);
    \}

    @AfterClass
    public static void tearDownClass() throws InterruptedException \{
        executor.shutdown();
        executor.awaitTermination(10, TimeUnit.SECONDS);
        [set subsys].close();
    \}
"

   puts $fout "
    @Test
    public void sendReceiveEnableCommand() throws InterruptedException, SALException, ExecutionException, TimeoutException \{
        [set subsys]Command command = testCommandSendReceive(new EnableCommand());
        assertTrue(command instanceof EnableCommand);
    \}

   @Test
    public void sendTakeImagesCommand() throws InterruptedException, SALException, ExecutionException, TimeoutException \{
        [set subsys]Command command = testCommandSendReceive(new TakeImagesCommand(10, 2, true, true, true, true, \"MyImage\"));
        assertTrue(command instanceof TakeImagesCommand);
        TakeImagesCommand tic = (TakeImagesCommand) command;
        assertEquals(2, tic.getNumImages());
        assertEquals(10, tic.getExpTime(), 1e-6);
        assertTrue(tic.isShutter());
        assertTrue(tic.isScience());
        assertTrue(tic.isGuide());
        assertTrue(tic.isWfs());
        assertEquals(\"MyImage\", tic.getImageSequenceName());
    \}
"

   puts $fout "
    private [set subsys]Command testCommandSendReceive([set subsys]Command command) throws SALException, InterruptedException, ExecutionException, TimeoutException \{
        Future<[set subsys]Command> future = executor.submit(() -> [set subsys].getNextCommand(Duration.ofSeconds(10)));
        CommandResponse response = [set subsys].issueCommand(command);
        [set subsys]Command result = future.get(10, TimeUnit.SECONDS);
        result.reportComplete();
        response.waitForResponse(Duration.ofSeconds(1));
        return result;
    \}
\}

"
   close $fout
}


proc gensimplesalevttests { subsys } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/test/java/org/lsst/sal/[set subsys]/EventSendReceiveTest.java w]
   puts $fout "
package org.lsst.sal.[set subsys];
import java.time.Duration;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import org.junit.AfterClass;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;
import org.junit.BeforeClass;
import org.junit.Test;
"

   puts $fout "
import org.lsst.sal.[set subsys].event.AppliedSettingsMatchStartEvent;
import org.lsst.sal.[set subsys].states.SummaryStateEvent;
"

   puts $fout "
/**
 *
 * @author tonyj
 */
public class EventSendRecieveTest \{

    private static SAL[set subsys] [set subsys];
    private static ExecutorService executor;

    public EventSendRecieveTest() \{
    \}

    @BeforeClass
    public static void setUpClass() \{
        [set subsys] = SAL[set subsys].create();
        executor = Executors.newFixedThreadPool(1);
    \}

    @AfterClass
    public static void tearDownClass() throws InterruptedException \{
        executor.shutdown();
        executor.awaitTermination(10, TimeUnit.SECONDS);
        [set subsys].close();
    \}

"

   puts $fout "
    @Test
    public void sendReceiveIdleBusyDetailedStateEvent() throws InterruptedException, SALException, Executi
onException, TimeoutException \{
        [set subsys]Event event = testEventSendReceive(new IdleBusyDetailedStateEvent(1, IdleBusyState.BUSY));
        assertTrue(event instanceof IdleBusyDetailedStateEvent);
        IdleBusyDetailedStateEvent detail = (IdleBusyDetailedStateEvent) event;
        assertEquals(IdleBusyState.BUSY, detail.getState());
        assertEquals(1, detail.getPriority());
    \}

"

   puts $fout "
   private [set subsys]Event testEventSendReceive([set subsys]Event event) throws SALException, InterruptedException,
 ExecutionException, TimeoutException \{
        Future<[set subsys]Event> future = executor.submit(() -> [set subsys].getNextEvent(Duration.ofSeconds(10)));
        [set subsys].logEvent(event);
        [set subsys]Event result = future.get(10, TimeUnit.SECONDS);
        return result;
    \}
\}
"
   close $fout
}


proc gensimplesaltlmtests { subsys } {
global SAL_WORK_DIR SSAL_BASE SALVERSION
   set fout [open $SSAL_BASE/src/test/java/org/lsst/sal/[set subsys]/TelemetrySendReceiveTest.java w]
   puts $fout "
package org.lsst.sal.[set subsys];

import java.time.Duration;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import org.junit.AfterClass;
import static org.junit.Assert.assertTrue;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.assertTrue;
"

  puts $fout "
import org.lsst.sal.[set subsys].states.SummaryStateEvent.LSE209State;
"

  puts $fout "
/**
 * 
 * @author tonyj
 */
public class TelemetrySendReceiveTest \{

    private static SAL[set subsys] [set subsys];
    private static ExecutorService executor;

    public TelemetrySendReceiveTest() \{
    \}

    @BeforeClass
    public static void setUpClass() \{
        [set subsys] = SAL[set subsys].create();
        executor = Executors.newFixedThreadPool(1);
    \}

    @AfterClass
    public static void tearDownClass() throws InterruptedException \{
        executor.shutdown();
        executor.awaitTermination(10, TimeUnit.SECONDS);
        [set subsys].close();
    \}
"

   puts $fout "
    @Test
    public void sendColdTelemetry() throws InterruptedException, SALException, ExecutionException, Timeout
Exception \{
        [set subsys].sendTelemetry(new [set subsys]ColdTelemetry());
    \}
"

   puts $fout "
}
"
   close $fout
}


