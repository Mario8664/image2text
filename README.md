# image2text
A cmdline tool that help you convert image with common format to character graph.
[![Build Status](https://www.travis-ci.org/537PowerTeam/image2text.svg?branch=master)](https://www.travis-ci.org/537PowerTeam/image2text)
# Functions:

1. Convert image to character graph.

2. Convert image to html page with/without color.

3. Scale image ratio and resolution.

# Usage:
```
$ > ./image2text --source [source.jpg] --scale x:y --type [html/txt] --with-color(only type is html) --output [target.html(txt)]

also

$ > ./image2text --help //to see a detailed usage.
```
# Dependencies:

1. [OpenCV3.0](https://opencv.org/releases.html)

2. CMake


If it's your first time to open this solution in VS2017, you need to set the properties of this project.
		
VC++ Directory -> Include Directory and Library Directory -> Set the OpenCV path in your computer.
		
Then you need to navigate to the project folder in cmd or powershell, run
	
```
git update-index --assume-unchanged image2text.vcxproj
```
		
manually, to pretend the conflicts of the VS configuration for each contributor.(too complex..>_<)
		
if you are coding in Linux, unless you had modified the installation path of OpenCV, our cmake script had been configured all the lib path and include path correctly. Just tap your kb!
			
	
