package org.opensplice.dds.idlcompiler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;

import org.apache.maven.plugin.MojoExecutionException;
import org.apache.maven.plugin.logging.Log;

public class IDLProcessor {

	/**
	 * log reference for logging
	 */
	Log log;
	

	protected IDLProcessor(Log lg)
	{
		log = lg;
	}
	
	/**
	 * Invoke the idl compiler for the given IDL File
	 * @param arguments command line to be passed to the process builder
	 * @throws MojoExecutionException
	 */
	protected void process(List<String> arguments) throws MojoExecutionException
	{
		BufferedReader results = null, errors = null;
		try
		{
			ProcessBuilder pb = new ProcessBuilder(arguments);
			Process p = null;
			try
			{
				log.info("Executing idl command" + arguments.toString());	
				p = pb.start();

				results = new BufferedReader(new InputStreamReader(p.getInputStream()));
				String s;
				boolean error = false;
				while((s = results.readLine()) != null)
				{
					error = true;
					log.info(s);
				}

				errors = new BufferedReader(new InputStreamReader(p.getErrorStream()));
				while((s = errors.readLine()) != null)
				{
					error = true;
					log.error(s);
				}
				try
				{
				   p.waitFor();
				}
				catch(InterruptedException exp)
				{
					//do nothing
				}
				if(error)
					throw new MojoExecutionException("");
			}
			catch(IOException exp)
			{
				log.error(exp);
				throw new MojoExecutionException("");
			}			
		}
		finally
		{
			try
			{
			  if(results != null)	
			     results.close();
			  if(errors != null)
			     errors.close();
			}
			catch(IOException exp)
			{
				log.error(exp);
				throw new MojoExecutionException("");
			}
			
		}
	}
	
}
