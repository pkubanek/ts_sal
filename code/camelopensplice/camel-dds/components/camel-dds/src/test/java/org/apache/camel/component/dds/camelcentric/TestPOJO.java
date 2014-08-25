package org.apache.camel.component.dds.camelcentric;

import java.io.Serializable;

public class TestPOJO implements Serializable {

    private long ssn;
    private String name;
    private String address;

    public TestPOJO(long s, String n, String a) {
        ssn = s;
        name = n;
        address = a;
    }

    public long getSSN() {
        return ssn;
    }

    public String getName() {
        return name;
    }

    public String getAdress() {
        return address;
    }

}
