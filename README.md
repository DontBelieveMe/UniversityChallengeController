# University Challenge Software Controller

### About
The source code for a school university challenge competition.  
Aka it controls the buzzers (you can press a buzzer, it lights up, and plays a nice sound)  
Runs on a heavily customised raspberry pi configuration, with a cool hardware setup for the buzzers themselves/audio.

### Building
In order to build run `sh build.sh` in the root directory. This will invoke CMake in order to generate project files (in the `build` directory and then will build the code which will output in the `build` directory.  
To run the code execute `sh run.sh` in the root directory. This requires root privileges. 
