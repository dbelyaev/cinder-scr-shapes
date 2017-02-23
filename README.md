# cinder-scr-shapes
Simple screensaver using Cinder framework with main purpose to re-create and old screensaver I saw many years ago on some Windows 98\XP machine. Was it called bouncing line or something?
<image here>
# Build instuctions
* download latest Cinder SDK (this project was tested with v0.9.0)
* add environment variable named `CINDERDIR` that points to where your Cinder installation folder is (for example: `c:\sdk\cinder`) 
* open solutions file at `.\shapes\vs2015\shapes.sln` and build it
* in `DEBUG` configuration project will be compilead as App (normal Window), while in `RELEASE` it will generate Windows screensaver (exits on mouse events, fullscreen etc)