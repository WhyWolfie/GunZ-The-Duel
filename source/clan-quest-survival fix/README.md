1. Open Gunz solution, CTRL + H (Make sure it says Entire Solution) type into top box "MSM_QUEST" and in bottom box "MSM_TEST"  <br>
2. Replace All,after replacing again CTRL + H (Make sure it says Entire Solution) type into top box "MSM_TEST" and in bottom box "MSM_CLAN"  <br>
3. Move the Matchserver folder back from your Desktop into your source folder  <br>
4. Build the solution, once completed you should then recieve 2 errors, double click the error and it should take you to the line of where to 
the line that the error is produced.  <br>
5. On that line you will see MSM_CLAN, change back to MSM_TEST, and do this for the other error you recieved,you might get MSM_QUEST change it to MSM_TEST. <br>
6. Rebuild and it should build succussful  <br>
7. Open up the Matchserver solution and it should build successfully  <br>
8. Replace your Matchserver.exe and Gunz.exe that you have originally  <br>

[short] <br>
CTRL + Shift + F <br>
Replace -> MSM_QUEST -> MSM_TEST <br>
Replace -> MSM_TEST -> MSM_CLAN <br>
Error -> Change too -> MSM_TEST -> Rebuild <br>

MatchServer/server.ini <br>
change -> mode=clan <br>
