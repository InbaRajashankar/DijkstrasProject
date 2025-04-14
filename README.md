# DijkstrasProject
A simple C++ program that uses Dijkstra's algorithm to find shortest paths in a graph specified in a .txt file.

## Usage
```
./findPath [FILENAME]
```
FILENAME specifies a adjacency list in .txt format. Use `cities.txt` as an example file.

Example:
```
$ make
$ ./findPath cities.txt
$
$ CITIES:
$ - Washington_DC
$ - Boston
$ - Miami
$ - Chicago
$ - Mumbai
$ - Bangkok

...

$ Enter your start city: Singapore
$
$ Where to go to (q to quit)? Istanbul
$ Path from Singapore to Istanbul found!
$  - Cost: 720.
$  - Path: Singapore -(440)-> Dubai -(280)-> Istanbul.
```
