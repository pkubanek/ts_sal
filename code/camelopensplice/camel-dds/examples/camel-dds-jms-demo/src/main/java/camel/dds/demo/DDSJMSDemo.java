package camel.dds.demo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;

import javax.jms.ConnectionFactory;

import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.camel.CamelContext;
import org.apache.camel.Endpoint;
import org.apache.camel.Exchange;
import org.apache.camel.Processor;
import org.apache.camel.ProducerTemplate;
import org.apache.camel.builder.RouteBuilder;
import org.apache.camel.component.jms.JmsComponent;
import org.apache.camel.impl.DefaultCamelContext;

import com.google.gson.Gson;

import Chat.SimpleChatMessage;

public class DDSJMSDemo {
    private int userID;
    private String user;
    private static int idx;    
    private static ProducerTemplate template;
    private static Endpoint endpoint;

	public DDSJMSDemo(int userID, String user) {
        this.userID = userID;
        this.user = user;
        idx = 0;
    }

    public static void main(String args[]) throws Exception {

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
        DDSJMSDemo chatter = new DDSJMSDemo(chatterID, userName);

        // Create the camel context.
        CamelContext context = new DefaultCamelContext();
        template = context.createProducerTemplate();

        // Set up the ActiveMQ JMS Components
        ConnectionFactory connectionFactory = new ActiveMQConnectionFactory("vm://localhost?broker.persistent=false");
        // Note we can explicity name the component
        context.addComponent("test-jms", JmsComponent.jmsComponentAutoAcknowledge(connectionFactory));

        // Add some configuration by hand ...
        String qos = "?ReliabilityKind=RELIABLE";
        // filter out sent messages: userID <> userID
        String filter = "&contentFilter=userID%20%3C%3E%201";
        String partition = "&Partition=ChatRoom";
        final String fromURI = "dds:Chat_SimpleChatMessage:0/Chat.SimpleChatMessage" + qos + filter + partition;
        // We use the endpoint later.
        endpoint = context.getEndpoint(fromURI);

        // Build the route.
        context.addRoutes(new RouteBuilder() {
            public void configure() {
                // From the DDS URI through the converter bean to the JMS queue.
            	from(fromURI).bean(ChatMessagetoJSONConverterBean.class, "onChat").to("test-jms:queue:chat.queue");
            	
            	// We also need a route from the JMS queue to a processor so that we can
            	// see the JMS message that has been sent.
            	from("test-jms:queue:chat.queue").process(new Processor() {
                    public void process(Exchange e) {
                        // The processor parses the JSON string back into a SimpleChatMessage
                        // object before displaying the content. NOTE - There is no
                        // filtering of the messages that the user sends.
                        String jsonString = (String) e.getIn().getBody();
                        int beginIndex = jsonString.indexOf("{\"data\": ") + 9;
                        int endIndex = jsonString.indexOf(", \"info\": ");
                        String chatMessageString = jsonString.substring(beginIndex, endIndex);
                        Gson gson = new Gson();
                        SimpleChatMessage message = gson.fromJson(chatMessageString, SimpleChatMessage.class);
                        String content = message.content;
                        System.out.println(content);
                    }
                });
            }
        });
        
        context.start ();
        
        System.out.println("User " + userName + " logged into chat");

        InputStreamReader isr = new InputStreamReader(System.in);
        BufferedReader br = new BufferedReader(isr);

        try {
            while(true) {
                String s = br.readLine();
                if(s.equalsIgnoreCase("quit")) {
                    try {
                        if(template != null) {
                            template.stop();
                        }
                        context.stop();
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                    break;
                } else {
                    chatter.sendMessage(s);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
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
}