  /*
   * $Id: SystemCallExample.java 106 2008-08-30 00:58:59Z jyeary $
   * 
   * Software License Agreement (BSD License)
   * 
   * Copyright (c) 2008, Blue Lotus Software, LLC
   * All rights reserved.
   * 
   * Redistribution and use of this software in source and binary forms, with or
   * without modification, are permitted provided that the following conditions 
   * are met:
   * 
   *   Redistributions of source code must retain the above
   *   copyright notice, this list of conditions and the
   *   following disclaimer.
   * 
   *   Redistributions in binary form must reproduce the above
   *   copyright notice, this list of conditions and the
   *   following disclaimer in the documentation and/or other
   *   materials provided with the distribution.
   * 
   *   Neither the name of Blue Lotus Software, LLC nor the names of its
   *   contributors may be used to endorse or promote products
   *   derived from this software without specific prior
   *   written permission of Blue Lotus Software, LLC
   * 
   * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
   * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
   * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
   * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
   * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
   * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
   */

//package org.lsst.sal.utilities;
  
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
  
  /**
   * This is a demo application on how to use Java to make system calls. 
   * The use of system calls is platform specific. This code may not be 
   * transportable accross platforms,i.e. UNIX, Mac OS X, and Windows.
   * @author John Yeary
   * @version 1.0
   */
public class sal_SystemCall {
  
      /**
       * Creates a new instance of SystemCallExample
       */
      public String sal_SystemCall(String execute) {
          Runtime r = Runtime.getRuntime();
          String last = "";
          try {
              /*
               * Here we are executing the UNIX command ls for directory listing. 
               * The format returned is the long format which includes file 
               * information and permissions.
               */

              Process p = r.exec(execute);
              InputStream in = p.getInputStream();
              BufferedInputStream buf = new BufferedInputStream(in);
              InputStreamReader inread = new InputStreamReader(buf);
              BufferedReader bufferedreader = new BufferedReader(inread);
  
              // Read the ls output
              String line;
              while ((line = bufferedreader.readLine()) != null) {
                  last = line;
              }
              // Check for ls failure
              try {
                  if (p.waitFor() != 0) {
                      System.err.println("exit value = " + p.exitValue());
                  }
              } catch (InterruptedException e) {
                  System.err.println(e);
              } finally {
                  // Close the InputStream
                  bufferedreader.close();
                  inread.close();
                  buf.close();
                  in.close();
              }
          } catch (IOException e) {
              System.err.println(e.getMessage());
          }
          return last;
      }
  
      /**
       * Main program method
       * @param args the command line arguments
       */
      public static void main(String[] args) {
          Runtime r = Runtime.getRuntime();
  
          try {
              /*
               * Here we are executing the UNIX command ls for directory listing. 
               * The format returned is the long format which includes file 
               * information and permissions.
               */
              String test = args[0];
              Process p = r.exec(test);
              InputStream in = p.getInputStream();
              BufferedInputStream buf = new BufferedInputStream(in);
              InputStreamReader inread = new InputStreamReader(buf);
              BufferedReader bufferedreader = new BufferedReader(inread);
  
              // Read the ls output
              String line;
              while ((line = bufferedreader.readLine()) != null) {
                  System.out.println(line);
              }
              // Check for ls failure
              try {
                  if (p.waitFor() != 0) {
                      System.err.println("exit value = " + p.exitValue());
                  }
              } catch (InterruptedException e) {
                  System.err.println(e);
              } finally {
                  // Close the InputStream
                  bufferedreader.close();
                  inread.close();
                  buf.close();
                  in.close();
              }
          } catch (IOException e) {
              System.err.println(e.getMessage());
          }
     }
}

