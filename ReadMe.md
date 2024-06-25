![Build status](https://github.com/LegalizeAdulthood/tierazon/actions/workflows/msbuild.yml/badge.svg)

# Tiera-Zon

Tiera-zon is a freeware fractal generator which runs under Windows.
It was written by Stephen C. Ferguson in the late 1990s (version 2.7
is dated 09-17-98).
A graphics monitor of a least 256 colors is required, high color or
true color is prefered since it generates fractals in true-color.

The Tiera-zon program is about twice as fast as the Iterations/Flarium
programs.  The main program is written in Visual C++ and the formulae
and filters are written and included in a DLL file that is compiled
with the freeware DJGPP compiler using a Windows port software
package called RSX.

Tiera-zon currently has the following capabilities:

- About 100 formulae, mostly consisting of Newton MSet formula, Newton variations, and trig functions.
- Several enhancement filters such as stalks, bubbles, and atan methods.
- Saves images in 24-bit bmp format.
- Image processing such as blur, emboss, contour, and sharpen
- Anti-aliasing by blurring the image (low pass filtering), then reducing the image to half size.
- Fractal dimension and standard deviation coloring method.
- A unique formulae editor and parser which supports the following complex math functions:
  `*`, `/`, `+`, `-`, `^`, `sin`, `sinh`, `asin`, `cos`, `acos`, `tan`, `atan`, and `log`.
- The formula editor/ parser can be used to write your own unique formulae.
- Capability for creating AVI file video clips of zooming and/ or panning into fractals.
- Capability for creating AVI file video clips of Julia set animations. (New in version 1.5).

## Credits:
 
- [Jan Hubicka](http://limax.paru.cas.cz/~hubicka/XaoS/index.html) for telling me about the DJGPP compiler
- [Paul Carlson](http://sprott.physics.wisc.edu/carlson.htm) for the Newton Mset formula explanations, the Ushiki Phoenix formulae, the atan, bubbles, the stalks method, etc, etc......
- Björn Isho for creating the [Kaos Rhei](http://www.b-ischo.horizont-is.net/) program.
- [Paul Derbyshire](http://surf.to/pgd.net) for discovering the Nova formula.
- [Gerry Myers `<myersge@hiwaay.net>`](mailto:myersge@hiwaay.net) for writing the unique formula editor/ parser.
- Holger Jaenisch and James Handley for help with the initial release of `Iterations.exe`.
- [Sharon Webb](http://www.fractalus.com/sharon/) for providing lots of testing and feedback during the development of Flarium24.
- [Ramon Vives Valls `<ramon_vives@ctv.es>`](mailto:Ramon%20Vives%20Valls%20<ramon_vives@ctv.es>) for contributing the magnet1 and magnet2 formulae.
- [Jette Randlov `<randlov@alf.nbi.dk>`](mailto:Jette%20Randlov%20<randlov@alf.nbi.dk>) for the (x/y) orbit trap method.
- [Earl Hinrich](http://computerart.org/fractal.html) for the (1-z/radius) orbit counting method.
- Thanks to [Seth Bollinger `<sethb@visi.com>`](mailto:sethb@visi.com), filter # 50 has been corrected.

This ReadMe created from [Stephen C. Ferguson's web page](https://vchira.com/1998/Tierazon/Tierazon.html) by Richard Thomson.
