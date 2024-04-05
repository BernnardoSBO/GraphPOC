# How is MELON  implemented?
- Template library (generic programming - STL like)
- 
## Pros
- Easier syntax (although it's not properly documented)

## Cons
- Needs conan package manager (https://conan.io/)
- GCC must be at least version 12 (compiler needs to comply with C++20)
- Poorly documented
- Not released yet (beta or even alpha version)
  - as seen in https://github.com/fhamonic/melon/issues/5
- Hard to build
- Only supports digraphs (although undirected graphs can be represented with digraphs)

# How to setup MELON
This will explain how to link melon with a CMake project. To do so, is expected that there's a CMakeLists.txt configuring the build of the project in question.

1. Install dependencies:
   1.  `gcc 12+`
   2.  `conan 2.0+`
2. Clone melon repo locally
```
git clone https:://github.com/fhamonic/melon
```
3. Within this recently added MELON repo, build the conan package locally with the following command
```
cd melon
make package
```
4. Then, execute the following command from the root of the project
```
conan install . --output-folder=<buildpath> --build=missing -sbuild_type=Debug
```
where `<buildpath>` represents what is the path where you want to build the project

5. Now, build the makefile and the executable with the following command
```
cd <buildpath>
cmake -DCMAKE_BUILD_TYPE=Debug ../..
cmake --build .
```
6. The generated executable is currently in the `<buildpath>` folder`.



# Refs
- https://www.boost.org/doc/libs/1_84_0/libs/graph/doc/index.html
- https://www.boost.org/doc/libs/1_84_0/libs/graph/doc/table_of_contents.html
- https://www.youtube.com/watch?v=GSp2531Wti4&t=302s