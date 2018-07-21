# image2text
A cmdline tool that help you convert image with common format to character graph.
[![Build Status](https://www.travis-ci.org/537PowerTeam/image2text.svg?branch=master)](https://www.travis-ci.org/537PowerTeam/image2text)

~~image2text demo website~~

# Functions:

1. Convert image to character graph.

2. Convert image to html page with/without color.

3. Scale image ratio and resolution.

# Usage:
```
$ > ./image2text --source=[source.jpg] --scalex=[x] --scaley=[y] --type=[0 is stdout, 1 is output txt, 2 is output html with color.] --output=[target.html(txt)]

also

$ > ./image2text --help //to see a detailed usage.
```

# Html Template

You can customize the style of output html page. Modify what you want in 

```
 ./Template.html
```

Besides, you need to take this template with executable file in the same folder. The program will load this template when it needs to generate html page.

# Dependencies:

1. [OpenCV3.0](https://opencv.org/releases.html)

2. CMake


If it's your first time to open this solution in VS2017, you need to set the properties of this project.
		
1.Right click "image2text" in the solution explorer, click "Properties", and expand subtitle "VC++ Directory".

2.Add or modify
```
..\opencv\build\include
..\opencv\build\include\opencv
..\opencv\build\include\opencv2
$(LocalDebuggerWorkingDirectory)\include
```
in "Include Directory".

3.Add or modify
```
..\opencv\build\x64\vc15\lib
```
in "Library Directory".

4.Expand "Linker" -> Input, add opencv_world341d.lib in Additional dependencies.

Then you need to navigate to the project folder in cmd or powershell, run
	
```
git update-index --assume-unchanged image2text.vcxproj
```
		
manually, to pretend the conflicts of the VS configuration for each contributor.(too complex..>_<)
		
if you are coding in Linux, unless you had modified the installation path of OpenCV, our cmake script had been configured all the lib path and include path correctly.
	
