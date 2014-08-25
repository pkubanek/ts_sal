package org.lsst.sal;

import org.omg.dds.core.Bootstrap;
import org.omg.dds.core.InstanceHandle;
import org.omg.dds.core.modifiable.ModifiableInstanceHandle;

public class SALInstanceHandle extends ModifiableInstanceHandle {
    /** default serialVersionUID */
    private static final long serialVersionUID = 1L;

    private long handle = 0L;

    public SALInstanceHandle(long thehandle) {
        handle = thehandle;
    }

    public long getHandle() {
        return handle;
    }

    @Override
    public ModifiableInstanceHandle copyFrom(InstanceHandle other) {
        handle = ((SALInstanceHandle) other).getHandle();
        return this;
    }

    @Override
    public InstanceHandle finishModification() {
        return this;
    }

    @Override
    public ModifiableInstanceHandle modify() {
        return this;
    }

    @Override
    public Bootstrap getBootstrap() {
        return null;
    }

    @Override
    public ModifiableInstanceHandle clone() {
        return new SALInstanceHandle(handle);
    }

    @Override
    public boolean isNil() {
        return handle == 0;
    }
}
