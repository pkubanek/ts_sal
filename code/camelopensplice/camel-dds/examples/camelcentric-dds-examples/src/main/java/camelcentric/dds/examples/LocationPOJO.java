package camelcentric.dds.examples;

import java.io.Serializable;

public class LocationPOJO implements Serializable {


    private String city;
    private int zip;

    public LocationPOJO(String c, int z) {
        city = c;
        zip = z;
    }

    public String getCity() {
        return city;
    }

    public int getZip() {
        return zip;
    }


}
