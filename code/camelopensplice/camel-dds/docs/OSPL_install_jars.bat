@ECHO OFF

if "%OSPL_HOME%"=="" goto OSPLNOTSET

if "M2_HOME"=="" goto M2NOTSET

if "M2"=="" goto M2NOTSET

if exist "%M2_HOME%\bin\mvn.bat" goto installospljars
echo.
echo ERROR: M2_HOME is set to an invalid directory.
echo M2_HOME = %M2_HOME%
echo Please set the M2_HOME variable in your environment to match the
echo location of the Maven installation
echo.
goto end


:installospljars
ECHO "Installing Opensplice Jar Files"
mvn install:install-file -Dfile=%OSPL_HOME%\jar\dcpssaj.jar -DgroupId=org.opensplice.dds -DartifactId=dcpssaj -Dversion=4.1 -Dpackaging=jar

IF NOT ERRORLEVEL==0 (
  ECHO:
  ECHO Jar Installation Failed
  ECHO:
  GOTO error
)

GOTO end


:OSPLNOTSET
echo OSPL_HOME variable not set
goto end

:M2NOTSET
echo M2_HOME and M2 variable must be set.
goto end

:end