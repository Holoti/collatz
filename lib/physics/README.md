# Physics Engine

**Achtung! poorly-worded "documentation" ahead!**

Important points so far:
- Physics engine doesn't know anything about Collatz, graphics, graph representation, or user application whatsoever
- The only thing it somewhat cares about, besides the physics simulation itself, if interpolating the state it gives as a part of public interface
- UPS is decoupled from FPS and fixed to 60 updates per second
- Actual physics simulation is still WIP
