package camelcentric.dds.examples;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.apache.camel.CamelContext;
import org.apache.camel.Endpoint;
import org.apache.camel.Exchange;
import org.apache.camel.Processor;
import org.apache.camel.ProducerTemplate;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.impl.DefaultCamelContext;



public class POJOMessage {

    private Exchange receivedExchange;
    private ProducerTemplate template;
    private Endpoint endpoint;
    private CamelContext ctx;

    public void initialize() throws Exception{
        ctx = new DefaultCamelContext();
        template = ctx.createProducerTemplate();
        final String fromURI = "dds:ExampleLocationTopic:0/?target=locationTarget";
        endpoint = ctx.getEndpoint(fromURI);
        ctx.addRoutes(new RouteBuilder() {
            public void configure() {
                from(fromURI).process(new Processor() {
                    public void process(Exchange e) {
                        receivedExchange = e;
                        displayExchange();
                    }
                });
            }
        });
        ctx.start();
        System.out.println("Type quit to terminate \n");
        System.out.println("\nEnter Address (City,Zip):");
    }

    private void displayExchange() {
        LocationPOJO recd = (LocationPOJO)receivedExchange.getIn().getBody();
        System.out.println("Received Location:" + recd.getCity() + "," + recd.getZip());
        System.out.println("\nEnter Address (City,Zip):");
    }

    public void sendMessage(String message) {
        String[] loc = message.split(",");
        String c = null;
        int zip = 0;
        try {
            c = loc[0];
            zip = Integer.parseInt(loc[1]);
        } catch(Exception exp) {
            System.out.println("Invalid Entry");
            return;
        }

        final LocationPOJO msg = new LocationPOJO(c, zip);

        template.send(endpoint, new Processor() {
                public void process(Exchange exchange) {
                    exchange.getIn().setBody(msg);
                }
            });
    }

    public void stop() {
        try {
            if(template != null) {
                template.stop();
            }
            ctx.stop();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main (String[] args) {

        POJOMessage msg = new POJOMessage();
        try {
            msg.initialize();
        } catch(Exception exp) {
            exp.printStackTrace();
        }

        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);

        try {
            while(true) {
                String s = br.readLine();
                if(s.equalsIgnoreCase("quit")) {
                    msg.stop();
                    break;
                } else {
                    msg.sendMessage(s);
                }
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }


    }

}
