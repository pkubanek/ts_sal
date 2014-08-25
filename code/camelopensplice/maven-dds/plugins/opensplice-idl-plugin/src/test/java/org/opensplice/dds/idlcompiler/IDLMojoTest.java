package org.opensplice.dds.idlcompiler;

import java.io.File;

import org.apache.maven.plugin.testing.AbstractMojoTestCase;

public class IDLMojoTest extends AbstractMojoTestCase {

	private IDLMojo mojo;
	public void setUp() throws Exception
	{
		super.setUp();
		
        File pom = new File( getBasedir(), "src/test/java/projects/project1/pom.xml" );
        mojo = (IDLMojo) lookupMojo("idl-compile", pom);		
	}
    /**
     * Test whether IDL file gets compiled
     */ 
    public void testIDLCompilation()
        throws Exception
    {
        mojo.execute();
        File file = new File(getBasedir(),"target/test-classes/durable/Message.java");
        assertTrue(file.exists());
 
    }
    
    /**
     * Test injection of fields values from POM into MOJO
     */
    public void testFields()
        throws Exception
    {
         String[] macros = (String[])getVariableValueFromObject(mojo, "macros");
         assertTrue(macros.length == 2);
         assertTrue(macros[0].equals("Hello"));
         assertTrue(macros[1].equals("World"));
         
         File[] includeDirs = (File[])getVariableValueFromObject(mojo, "includeDirs");
         assertTrue(includeDirs.length == 2);
         assertTrue(includeDirs[0].getName().equals("myDir1"));
         assertTrue(includeDirs[1].getName().equals("myDir2"));   
         
         File preprocessor = (File)getVariableValueFromObject(mojo, "preprocessor");
         assertTrue(preprocessor.getName().equals("pre"));
         
         String idlc = (String)getVariableValueFromObject(mojo, "idlc");
         assertTrue(idlc.equals("idlpp"));    
         
         String language = (String)getVariableValueFromObject(mojo, "language");
         assertTrue(language.equals("java"));  
         
         String mode = (String)getVariableValueFromObject(mojo, "mode");
         assertTrue(mode.equals("-S"));        
         
         File idlDir = (File)getVariableValueFromObject(mojo, "idlDir");
         assertTrue(idlDir.getName().equals("resources"));  
         
         File outDir = (File)getVariableValueFromObject(mojo, "outDir");
         assertTrue(outDir.getName().equals("test-classes"));         
          
    }    
 
}
