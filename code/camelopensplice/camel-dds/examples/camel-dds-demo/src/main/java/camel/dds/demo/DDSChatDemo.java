package camel.dds.demo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;

import org.apache.camel.CamelContext;
import org.apache.camel.Endpoint;
import org.apache.camel.Exchange;
import org.apache.camel.Processor;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.component.dds.DdsMessage;
import org.apache.camel.impl.DefaultCamelContext;
import org.apache.camel.ProducerTemplate;

import Chat.SimpleChatMessage;

public class DDSChatDemo {

    private int userID;
    private String user;
    private Exchange receivedExchange;
    private ProducerTemplate template;
    private Endpoint endpoint;
    private CamelContext ctx;
    private static int idx;

    public DDSChatDemo(int userID, String user) {
        this.userID = userID;
        this.user = user;
        idx = 0;
    }


    public void initialize() throws Exception {
        ctx = new DefaultCamelContext();
        template = ctx.createProducerTemplate();
        String qos = "?ReliabilityKind=RELIABLE";
        // filter out sent messages: userID <> userID
        String filter = "&contentFilter=userID%20%3C%3E%20" + userID;
        String partition = "&Partition=ChatRoom";
        final String fromURI = "dds:Chat_SimpleChatMessage:0/Chat.SimpleChatMessage" + qos + filter + partition;
        endpoint = ctx.getEndpoint(fromURI);
        ctx.addRoutes(new RouteBuilder() {
            public void configure() {
                from(fromURI).process(new Processor() {
                    public void process(Exchange e) {
                        receivedExchange = e;
                    	System.out.println("Received exchange: " + e); 
                    	DdsMessage message = (DdsMessage) e.getIn();
                    	System.out.println("Message: " + message);
                        displayExchange();
                    }
                });
            }
        });
        ctx.start();

        System.out.println("User " + user + " logged into chat");
    }

    private void displayExchange() {
        SimpleChatMessage msg = (SimpleChatMessage)receivedExchange.getIn().getBody();
        String content = msg.content;
        System.out.println(content);
    }

    public void sendMessage(String message) {
        final SimpleChatMessage cm = new SimpleChatMessage();
        cm.userID = userID;
        cm.index = idx++;
        cm.content = user + ">" + message;
        template.send(endpoint, new Processor() {
                public void process(Exchange exchange) {
                    exchange.getIn().setBody(cm);
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
        int chatterID = -1;
        String userName = null;

        if(args.length > 0) {
            userName = args[0];
        }

        if(userName == null) {
            userName = "Anonymous";
        }

        // Generate a Unique ID
        chatterID = (new Random()).nextInt();
        DDSChatDemo chatter = new DDSChatDemo(chatterID, userName);


        try {
            chatter.initialize();
        } catch(Exception exp) {
            exp.printStackTrace();
        }

        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);

        try {
            while(true) {
                String s = br.readLine();
                if(s.equalsIgnoreCase("quit")) {
                    chatter.stop();
                    break;
                } else {
                    chatter.sendMessage(s);
                }
            }
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }


    }
}
