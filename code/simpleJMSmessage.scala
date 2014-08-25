import java.util.{Hashtable => JHashtable}
import javax.naming._
import javax.jms._
 
  object SimpleJMSClient {

    val DEFAULT_QCF_NAME = "jms/MarksConnectionFactory"
    val DEFAULT_QUEUE_NAME = "jms/MarksQueue"
    val DEFAULT_URL = "t3://localhost:7101"
    val DEFAULT_USER = "weblogic"
    val DEFAULT_PASSWORD =  "weblogic"
 
    def sendMessage(theMessage: String) {
      sendMessage(
        url = DEFAULT_URL,
        user = DEFAULT_USER,
        password = DEFAULT_PASSWORD,
        cf = DEFAULT_QCF_NAME,
        queue = DEFAULT_QUEUE_NAME,
        messageText = theMessage)
    }
 
    def sendMessage(url : String, user : String, password : String,
                    cf : String, queue : String, messageText : String) {
      // create InitialContext
      val properties = new JHashtable[String, String]
      properties.put(Context.INITIAL_CONTEXT_FACTORY,
                    "weblogic.jndi.WLInitialContextFactory")
      properties.put(Context.PROVIDER_URL, url)
      properties.put(Context.SECURITY_PRINCIPAL, user)
      properties.put(Context.SECURITY_CREDENTIALS, password)
 
      try {
        val ctx = new InitialContext(properties)
        println("Got InitialContext " + ctx.toString())
 
        // create QueueConnectionFactory
        val qcf = (ctx.lookup(cf)).asInstanceOf[QueueConnectionFactory]
        println("Got QueueConnectionFactory " + qcf.toString())
 
        // create QueueConnection
        val qc = qcf.createQueueConnection()
        println("Got QueueConnection " + qc.toString())
 
        // create QueueSession
        val qsess = qc.createQueueSession(false, 0)
        println("Got QueueSession " + qsess.toString())

        // lookup Queue
        val q = (ctx.lookup(queue)).asInstanceOf[Queue]
        println("Got Queue " + q.toString())
 
        // create QueueSender
        val qsndr = qsess.createSender(q)
        println("Got QueueSender " + qsndr.toString())
 
        // create TextMessage
        val message = qsess.createTextMessage()
        println("Got TextMessage " + message.toString())
 
        // set message text in TextMessage
        message.setText(messageText)
        println("Set text in TextMessage " + message.toString())
 
        // send message
        qsndr.send(message)
        println("Sent message ")
 
      } catch {
        case ne : NamingException =>
          ne.printStackTrace(System.err)
          System.exit(0)
        case jmse : JMSException =>
          jmse.printStackTrace(System.err)
          System.exit(0)
        case _ =>
          println("Got other/unexpected exception")
          System.exit(0)
      }
    }
 
    def main(args: Array[String]) = {
      sendMessage(
        theMessage = "hello from Scala sendMessage() with 1 arg"
      )
      sendMessage(
        url =        "t3://localhost:7101",
        user =       "weblogic",
        password =   "weblogic",
        cf =         "jms/MarksConnectionFactory",
        queue =      "jms/MarksQueue",
        messageText = "hello from Scala sendMessage() with 6 args"
      )
    }
 
 }


//To compile and run this code, you will need to put the 
// wlthint3client.jar on your classpath, as shown below:
//
// scala -classpath ~/Oracle/Middleware/wlserver_10.3/server/lib/wlthint3client.jar:.

