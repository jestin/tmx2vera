# tmx2vera

This is a command line application that converts a TMX file into a binary
readable by the VERA chip.

![tmx2vera compile](tmx2vera_compile.gif)

The [VERA graphics chip](https://github.com/fvdhoef/vera-module) that is being
used by the Commander X16 modern retro computer can render graphics based on
the contents of its onboard video RAM, but those contents need to be in a
specific format.  This command line application is able to extract a tile layer
from a `*.tmx` file produced by the Tiled map editor, and convert it into a
VERA-compatible tile map binary that can be loaded into the VERA's video RAM.
Additionally, this application can convert tile layers from a `*tmx` file into
a similar binary format that can be used as a collision map loaded into the
Commander X16's main memory.  This is useful for doing map collisions as well
as creating tiles that can trigger events in a game or application.  This can
then be used in conjunction with
[gimp-vera-tileset-plugin](https://github.com/jestin/gimp-vera-tileset-plugin),
a GIMP plugin for exporting VERA-compatible tile sets, which allows for game
engine style development for Commander X16 games and applications.

## Compilation and Installation

To compile `tmx2vera` you will need the `libxml++-2.6` library and include
files, as well as the `pkg-config` command line application.  Once the
dependencies are available, you can run:

```
$ make
```

This will produce the `tmx2vera` binary.  Copy this binary to somewhere in your
execution path, and you should now be able to run this application from your
Commander X16 project directory.

## Usage

```
Usage: tmx2vera [OPTION...] TMX_FILE OUTPUT_FILE
A tool to convert Tiled maps into files usable by the VERA chip of the
Commander X16 computer

  -c, --collision            Output a 1 byte per tile collision map instead of
                             2 byte per tile VERA tile map
  -d, --disable-paloffset    Do not write a palette offset to the tile data
  -l, --layer=LAYER_NAME     The name of the layer to convert
  -u, --use-header           Write a 2-byte header to output files
  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.

Report bugs to https://github.com/jestin/tmx2vera/issues.
```

`tmx2vera` has two ways it can be run: tile map mode (default) and collision
map mode (`-c`).  In both modes, a tile layer will need to be specified with
the `-l` argument.  This lets `tmx2vera` know which layer it is that you wish
to extract.

### Tile Map Mode (default)

In this mode, you specify one of your tile layers in Tiled that will be
converted into a VERA-compatible tilemap binary file.  This file can be loaded
directly into the VERA's VRAM using the `SETLFS`, `SETNAM`, and `LOAD` routines
of the Commander X16 Kernal.

For example, the following line from a `Makefile` will take the layer named
"terrain" and convert it into a binary file named `LOMAP.BIN`:

```
L0MAP.BIN: MyMap.tmx
	tmx2vera MyMap.tmx L0MAP.BIN -l terrain
```

This map file can now be loaded into the VERA's VRAM.

### Collision Map Mode (`-c`)

The VERA chip does not handle regular tile collisions (only hardware sprite
collisions), so collision detection with tile maps needs to be written manually
by a game's programmer.  However, Tiled and `tmx2vera` both have features that
make this task simpler and allows for a better workflow.  Tiled has an
[automapping](https://doc.mapeditor.org/en/stable/manual/automapping/) feature
that (aside from other uses) can be used to generate collision maps.  Simple
create a tile set of collision tiles, and configure Tiled's automapping to
create a tile layer of collision tiles that correspond to your actual tile
maps.  These tiles can be created with
[gimp-vera-tileset-plugin](https://github.com/jestin/gimp-vera-tileset-plugin)
using the 1 bit per pixel output mode, and imported into Tiled in the form of a
tileset file (`*tmx`) that the gimp-vera-tileset-plugin can also output for
you.

VERA-compatible tile maps require 2 bytes per tile, but this is wasteful for
collision maps which are not interpretted by the VERA chip.  This is why
`tmx2vera` as a special "collision" mode that simply outputs a binary map of 1
byte per tile, containing the tile index alone.  It can now be added to a
`Makefile` as a resource compiler for your Commander X16 project.

For example, to export a collision map from a tile layer named "collision":

```
CLSNMAP.BIN: MyMap.tmx
	tmx2vera -c MyMap.tmx CLSNMAP.BIN -l collision
```

The code to perform the collision detection is still up to the programmer to
write, but `tmx2vera` and Tiled can make for a powerful toolchain for quickly
creating the data.  This combined with Tiled's
[terrain](https://doc.mapeditor.org/en/stable/manual/terrain/) and
[automapping](https://doc.mapeditor.org/en/stable/manual/automapping/) features
make for a very game-engine-like development process for Command X16 game
development.

### Two Byte File Header (`-u`)

Files loaded into memory on Commodore computers (and Commodore-like computers
such as the Commander X16) have historically used a two byte header to indicate
the address in memory where the file is expected to be loaded.  Many BASIC
commands on these computers expect this header when dealing with files.  While
the Commander X16's BASIC commands (such as `LOAD` and `VLOAD`) also expect
this header, altenative commands have been added that do not require it.  For
this reason, the `--use-header` option has been added to `tmx2vera` in order to
generate files that can work with both standards.  By default, headers will not
be added, but `tmx2vera` can be told to place two bytes of 0s at the beginning
of an output file by specifying `--use-header` or `-u` at the command line.

## Video Demonstrations

_These videos use the older convention of adding a two byte header to the
output by default.  The current version of `tmx2vera` will not add the header
by default, and therefore would be incompatible with some of the code examples
in these old videos._

Tools Overview:

[![Tools Demo](https://img.youtube.com/vi/ATiwyTGiSc4/0.jpg)](https://www.youtube.com/watch?v=ATiwyTGiSc4)

Collision Detection:

[![Collision Detection](https://img.youtube.com/vi/HCEfZ3UPACM/0.jpg)](https://www.youtube.com/watch?v=HCEfZ3UPACM)
