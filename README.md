# EAE6610_Che_Chang
## Assignment 1
- Files
  + `/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg1/src/Boid.cpp` -> Boid Class cpp file, contains Seek(Arrive), Wander, Kinematic motion demo code
  + `/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg1/src/Flocking.cpp` -> contains flocking behavior source code
  + `/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg1/src/Separation.cpp` -> contains separation behavior source code
  + `/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg1/src/VelocityMatch.cpp` -> contains velocity match behavior source code

- How to run
  1. navigate to `EAE6610_Che_Chang/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg1/bin/`
  2. under that folder there's an executable called `GameAI_CheChang_Asg1.app`
  3. when you run the app, there's different button to press that changes the scene for different behaviors


## Assignment 2
- Files
  + `/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg2/src/Graph.cpp` -> Graph Class, contains Edge, Graph, PathFindingList implementation
  + `/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg2/src/GraphTestCaseParser.cpp` -> Graph Test Case Parser Class, contains the logic that parses DIMACS shortest path challenge input file format
  + `/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg2/src/Heuristics.cpp` -> Heuristics Class, contains the heuristic function definitions
  + `/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg2/src/Node.cpp` -> Node Class, contains the node definition within a graph
  + `/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg2/src/Tile.cpp` -> Tile Class, contains the tile definition, including tile size, walkable or notm etc.
  + `/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg2/src/TileGraph.cpp` -> Tile Graph Class, inherits from Graph, contains a list of tiles, and is in charge of managing the graph nodes and edges

- How to run
  1. navigate to `EAE6610_Che_Chang/of_v0.11.2_osx_release/apps/myApps/GameAI_CheChang_Asg2/bin/`
  2. find the executable file `GameAI_CheChang_Asg1.app` (it's somehow stilled named after the first assignment)
  3. run the app, and there's 3 buttons to switch between modes (Draw Obstacles, Path Find, and Reset)
