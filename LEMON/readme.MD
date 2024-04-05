
# How is LEMON implemented?
- Template library (generic programming - STL like)

## Pros
- Less verbose than BoostGraphLib
- Uses CMake (easier to integrate with ns3 project)
- It's syntax is easier than BoostGraphLib
- Slightly better performance than BGL
- Quite customizable
- Mostly header only (can be used without building)

## Cons
- Last stable release is old (1.3.1 - 2018) and problematic with gcc 9+ (gives a lot of warnings) when building
- Doesn't support parallel computing (future feature)

# Example
- To run the provided example, the user must have the library properly installed in their system

# Refs
- https://www.sciencedirect.com/science/article/pii/S1571066111000740
- http://lemon.cs.elte.hu/pub/tutorial/index.html
- http://lemon.cs.elte.hu/pub/doc/1.3.1/index.html
- https://blog.sommer-forst.de/2016/10/28/solving-the-shortest-path-problem-5-benchmarks/

