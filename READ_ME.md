# Memory Hacking
In a nutshell, changes the memory addresses of the game after it gets into it.
Most of the games can be hacked in a similar way(some being way easier).
This is a console based application.

## Programs Used
[Visual Studio 2017](https://www.visualstudio.com/vs/community/)
[Cheat Engine](https://cheatengine.org/)
[Assault Cube - 1.2.0.2](https://assault.cubers.net/download.html)

## How to Use
Run the game
Run the exe [file](Assault%20Cube%20Hack.exe)
> Press F1 to turn on/off unlimited ammo
> Press F2 to turn on/off unlimited health
> Press INSERT to exit

## About
The reason for using Assault Cube is that the game is about 40 MB and is a FPS game.  
Memory Hacking Modern Warfare,Call Of Duty, Black Ops,... is a lot more easier since, this game has more protection(Dynamic Memory Allocation).  

## How To Make
We need to find the addresses to which we need to write into.  
Cheat Engine is a pretty good tool for this purpose.  
> Attach Cheat Engine to the game.  
> Find address of variable containing the current ammo value(shoot to change values and refine scan results).  
> Since the address we need is a static one, we need to find the pointer containing this address and the offset(Use "find what access this address").  
> Using the above option, we can refine(one can check if the obtained address is correct by manually adding the address and changing value, doing so would change the value in the game) and find the hex value of address.  
> we can search this hex value in Cheat engine (again need to refine) to get the corresponding address.  
> Repeat the process until the possible values of addresses in hex scan are green in colour(they are static addresses).  
> Keep note of all the pointers and their corresponding offsets(Also [uploaded](address.txt) in this project).  
> Repeat the process for health.  

> Using this values we now Program the hack(done in c++ using visual studio as a win32 console application).  
> The [code](Assault%20Cube%20Hack/Assault%20Cube%20Hack/Assault%20Cube%20Hack.cpp) used has already been commented briefly.  
> The file is in multibyte character set.  