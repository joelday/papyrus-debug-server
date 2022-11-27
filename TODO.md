# TODO

- [x] Test debugging with Skyrim 1.5.97 and 1.6.640. 

- [ ] Get Fallout 4 working:
  - [ ] figure out what to do with CommonLibF4. CommonLibF4 in this repo originally had a huge number of things copied over from CommonLibSSE. The upstream repo has a lot of things missing, most importantly the implementations for the internal BSScript classes like CodeTasklet. We may have to just copy back the old one for now to get this working in the short term.

- [x] Remove usage of skse64/f4se entirely and use only CommonLibSSE/F4.  
  - skse64/f4se introduces a number of compiler headaches to use in combination with the latter because of the usage of c++20; we have to avoid certain headers, like `skse64/GameTypes.h`.
  - f4se also has namespace conflicts with CommonLibSSE
  - There's also licensing issues with skse64 because of its "No Skyrim Online" clause. 
  - CommonLibSSE/F4 reproduce almost all the functionality we need in their XSE headers, we just need to figure out how to get XSE/Logger.h to open up a new file.

- [ ]Replace Champollion submodule with a vcpkg. This will require modifying Champollion's build system to install a vcpkg-friendly cmake package to consume.
  - [ ]Also figure out what is up with the ostream l-value/r-value thing that I couldn't fix and had to hack around

- [ ]Upstream necessary changes to the portfiles to the vcpkg-colorglass repo. The less we need to maintain, the better.

- [ ]Replace build system with CMake. This will make the builds far more flexible and less prone to weird MSBuild crap. It will also make this easy to package and turn into a vcpkg for consumption downstream.