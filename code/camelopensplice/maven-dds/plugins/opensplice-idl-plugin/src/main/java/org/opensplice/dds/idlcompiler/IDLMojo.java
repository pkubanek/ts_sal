package org.opensplice.dds.idlcompiler;


import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import org.apache.maven.plugin.AbstractMojo;
import org.apache.maven.plugin.MojoExecutionException;

/**
 * Opensplice IDL Compiler.
 *
 * @goal idl-compile
 * @phase generate-sources
 */
public class IDLMojo
    extends AbstractMojo
{
    /**
     * Location of the outputDirectory.
     * @parameter expression="${opensplice.idlc.outDir}" default-value="${project.build.directory}/generated-sources/idl"
     */
    private File outDir;
    
    /**
     * include directories
     * @parameter 
     */
    private File[] includeDirs ;   
    
    /**
     * IDL Directory
     * @parameter expression="${opensplice.idlc.idlDir}" default-value="${basedir}/src/main/idl"
     */
    private File idlDir;    
    
    /**
     * macro definitions
     * @parameter
     */
    private String[] macros;
    
    /**
     * preprocessor path
     * @parameter expression="${opensplice.idlc.preprocessor}" 
     */
    private File preprocessor ;    
    
    /**
     * Compiler Executable
     * @parameter expression="${opensplice.idlc}" default-value="idlpp"
     */
    private String idlc;
   
    /**
     * language can be java, c++ or c
     * @parameter expression="${opensplice.idlc.lang}" default-value="java"
     */
    private String language;

    /**
     * mode can be stand-alone or corba (-S | -C)
     * @parameter expression="${opensplice.idlc.mode}" default-value="-S"
     */
    private String mode;
    
     
    /**
     * Process arguments
     */
    private List<String> arguments;

    /**
     * Creates the IDL compiler command and processes every IDL 
     * @throws MojoExecutionException
     */
    public void execute()
        throws MojoExecutionException
    {
    	if(!idlDir.exists())
    	{
       		getLog().info("IDL Directory:" + idlDir.getName() + " does not exist");
    		return;    		
    	}
       	
    	File[] idlFiles = idlDir.listFiles();
    	if(idlFiles == null || idlFiles.length == 0)
    	{
    		getLog().info("No IDL Files found");
    		return;
    	}

    	if(!outDir.exists())
    	{
    		outDir.mkdirs();
    	}
        
    	arguments = new ArrayList<String>();

    	arguments.add(getCompiler());
    	
    	arguments.add("-d");
    	arguments.add(outDir.getAbsolutePath());
    	
    	arguments.add(mode);
    	
    	arguments.add("-l");
    	arguments.add(language);
    	
    	if(preprocessor != null)
    	{
    		arguments.add("-c");
    		arguments.add(preprocessor.getAbsolutePath());
    	}
    	
    	if(macros != null && macros.length > 0)
    	{
    		for(int x = 0; x < macros.length; x++)
    		{
    	    	arguments.add("-D");
    	    	arguments.add(macros[x]);    			
    		}
    	}
    	
       	if(includeDirs != null && includeDirs.length > 0)
    	{
    		for(int x = 0; x < includeDirs.length; x++)
    		{
    	    	arguments.add("-I");
    	    	arguments.add(includeDirs[x].getAbsolutePath());    			
    		}
    	}    	
 

    	boolean idlExists = false;
    	IDLProcessor proc = new IDLProcessor(getLog());
    	String idlFile = null;
    	for(File idlf: idlFiles)
    	{
    		if(!idlf.getName().endsWith(".idl"))
    			continue;
    		idlFile = idlf.getAbsolutePath();
    		arguments.add(idlFile);
    		idlExists = true;
    		try
    		{
    			proc.process(arguments);
    		}
    		catch(MojoExecutionException e)
    		{
    			throw e;
    		}
    		finally
    		{
    			arguments.remove(idlFile);
    		}
    	}

    	if(!idlExists)
    	{
    		getLog().info("No IDL Files found");
    	}

    }
    
    
	/**
	 * 
	 * @return Absolute Path to the IDL Compiler
	 * @param executable the idl executable
	 * @throws MojoExecutionException
	 */
	protected String getCompiler() throws MojoExecutionException 
	{
		Map<String, String> env = System.getenv();
		String OSPL_HOME_VAR = env.get("OSPL_HOME");
		if(OSPL_HOME_VAR == null)
			throw new MojoExecutionException("OSPL_HOME not set"); 
		return OSPL_HOME_VAR + File.separatorChar + "bin" + File.separatorChar + idlc; 
	}
    
}
