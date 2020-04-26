# Sea Canal
  Windows Forms desktop application using C++/CLI.
  There are 2 Visio files which describe the application algorithm.

  Main requirement: only one ship can move through the canal at a time.
  To fulfill this requirement the critical section (System.Threading.Monitor Class) 
  was used, because by design every ship is moving in its own thread.
