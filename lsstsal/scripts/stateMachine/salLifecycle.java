//
// The contents of this file are subject to the Mozilla Public
// License Version 1.1 (the "License"); you may not use this file
// except in compliance with the License. You may obtain a copy of
// the License at http://www.mozilla.org/MPL/
// 
// Software distributed under the License is distributed on an "AS
// IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
// implied. See the License for the specific language governing
// rights and limitations under the License.
// 
// 
// Contributor(s): 
//
// Name
//  salLifecycle
//
// Description
//   When a state machine executes an action, it is really calling a
//   member function in the context class.
//

import mount.*;
import org.lsst.sal.SAL_mount;
//import salLifecycleContext;

public class salLifecycle
{
    private salLifecycleContext	_fsm;
    private boolean 		_is_online;
    private boolean		_is_ready;
    private boolean             _external_abort;
    private int 		status;
    private String		setParameter;
    private String		setValue;
    private SAL_mount 		salObject;
    private String		subSystem = "mount";
    public void salLifecycle()
    {
        _fsm = new salLifecycleContext(this);
        _is_online = false;

        // Uncomment to see debug output.
        _fsm.setDebugFlag(true);
    }

    public void initialize()
    {
        String nextCmd;
        salObject = new SAL_mount();
        mount.command nextCommand = new mount.command();

        int cmdId = 0;
        int timeout = 0;
        boolean iquit = false;

        status = SAL_mount.SAL__OK;
        salObject.salProcessor();
        _fsm.enterStartState();
        while (!iquit) {
          cmdId = salObject.acceptCommand(nextCommand);
          _external_abort = false;
          if (cmdId > 0)  {
            if (nextCommand.action.compareTo("quit") == 0) {
                _fsm.ocsQuit();
                salObject.ackCommand(cmdId,SAL_mount.SAL__CMD_COMPLETE, 0, "Done : OK");
                iquit = true	;
            }
            else if (nextCommand.action.compareTo("reset") == 0)
            {
                _fsm.ocsReset();
            }
            else if (nextCommand.action.compareTo("abandon") == 0)
            {
                _fsm.ocsAbandon();
            }
            else if (nextCommand.action.compareTo("enable") == 0)
            {
                _fsm.ocsEnable();
            }
            else if (nextCommand.action.compareTo("disable") == 0)
            {
                _fsm.ocsDisable();
            }
            else if (nextCommand.action.compareTo("abort") == 0)
            {
                _external_abort = true;
                _fsm.ocsAbort();
            }
            else if (nextCommand.action.compareTo("stop") == 0)
            {
                _fsm.ocsStop();
            }
            else if (nextCommand.action.compareTo("configure") == 0)
            {
                _fsm.ocsConfigure();
            }
            else if (nextCommand.action.compareTo("set") == 0)
            {
                setParameter = nextCommand.property;
                setValue = nextCommand.value;
                _fsm.ocsSetValue();
            }
            else if (nextCommand.action.compareTo("unconfigure") == 0)
            {
                _fsm.ocsConfigure();
            }
            else 
            {
                if (!_is_ready) {
                  System.out.println("System is not ready for functional commands");
                  salObject.ackCommand(cmdId,SAL_mount.SAL__CMD_COMPLETE, SAL_mount.SAL__CMD_NOPERM, "Done : ERROR");
                } else {
                  System.out.println("Received functional command " + 
                                      nextCommand.device + " " + 
                                      nextCommand.property + " " + 
                                      nextCommand.action + " " + 
                                      nextCommand.value + " " + 
                                      nextCommand.modifiers); 
                  salObject.ackCommand(cmdId,SAL_mount.SAL__CMD_COMPLETE, 0, "Done : OK");
                }
            }
          }
        }
    }

    public void boot()
    {
        _is_online = true;
	_is_ready = false;
	status = salObject.logEvent(subSystem  + " state : STANDBY",1);
     }

    public void quit()
    {
        _is_online = false;
	_is_ready = false;
	status = salObject.logEvent(subSystem  + " state : OFF",1);
    }

    public void reset()
    {
        _is_online = true;
	_is_ready = false;
	status = salObject.logEvent(subSystem  + " state : STANDBY",1);
    }

    public void configureAck()
    {
	status = salObject.logEvent(subSystem  + " state : CONFIGURING",1);
	_is_ready = false;
        configureDone();
    }

    public void enableAck()
    {
	status = salObject.logEvent(subSystem  + " state : ENABLING",1);
	_is_ready = false;
        enableDone();
    }

    public void unConfigureAck()
    {
	status = salObject.logEvent(subSystem  + " state : UNCONFIGURING",1);
	_is_ready = false;
        unconfigureDone();
    }

    public void abandon()
    {
	status = salObject.logEvent(subSystem  + " state : ABANDON",1);
    }

    public void configureDone()
    {
	status = salObject.logEvent(subSystem  + " state : DISABLED",1);
	_is_ready = false;
    }

    public void enableDone()
    {
	status = salObject.logEvent(subSystem  + " state : ENABLED",1);
	_is_ready = true;
    }

    public void disableDone()
    {
	status = salObject.logEvent(subSystem  + " state : DISABLED",1);
	_is_ready = false;
    }

    public void unconfigureDone()
    {
	status = salObject.logEvent(subSystem  + " state : STANDBY",1);
	_is_ready = false;
    }

    public void stopDone()
    {
	status = salObject.logEvent(subSystem  + " state : ENABLED",1);
	_is_ready = true;
    }

    public void enableFailed()
    {
        if (_external_abort) {
           System.out.println("Enable was externally aborted");
        }
	status = salObject.logEvent(subSystem  + " state : ERROR",1);
	_is_ready = false;
    }

    public void configureFailed()
    {
        if (_external_abort) {
           System.out.println("Enable was externally aborted");
        }
	status = salObject.logEvent(subSystem  + " state : ERROR",1);
	_is_ready = false;
    }

    public void disableFailed()
    {
        if (_external_abort) {
           System.out.println("Disable was externally aborted");
        }
	status = salObject.logEvent(subSystem  + " state : ERROR",1);
	_is_ready = false;
    }

    public void setValue()
    {
	status = salObject.logEvent(subSystem  + " state : SET VALUE " + setParameter + " = " + setValue,1);
	_is_ready = true;
    }
}



