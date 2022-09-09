1. Move Matchserver folder from your source onto your Desktop <br>
2. Open Gunz solution, CTRL + H (Make sure it says Entire Solution) type into top box "MSM_QUEST" and in bottom box "MSM_TEST"  <br>
3. Replace All,after replacing again CTRL + H (Make sure it says Entire Solution) type into top box "MSM_TEST" and in bottom box "MSM_CLAN"  <br>
4. Move the Matchserver folder back from your Desktop into your source folder  <br>
5. Build the solution, once completed you should then recieve 2 errors, double click the error and it should take you to the line of where to 
the line that the error is produced.  <br>
6. On that line you will see MSM_CLAN, change back to MSM_TEST, and do this for the other error you recieved,you might get MSM_QUEST change it to MSM_TEST. <br>
7. Rebuild and it should build succussful  <br>
8. Open up the Matchserver solution and it should build successfully  <br>
9. Replace your Matchserver.exe and Gunz.exe that you have originally  <br>

MatchServer/server.ini <br>
change -> mode=clan <br>
