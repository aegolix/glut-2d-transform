# glut-2d-transform
This should be a follow-up to the glut-painter. However, transform requires more complex storage. So there are major changes in the codes that benefit transformation. These codes are what depression looks like D:

#### Usage instruction:
* First time opening, the default shape is Rectangle
*	To draw shapes:
    * Rectangle, Circle, Ellipse: click a start point and drag mouse to an end point, then release mouse.
    * Polygon: click a start point and keep clicking next point as polygon’s next vertices, to close the shape or finish a polygon, press Esc.
    * Right click mouse to open a menu to choose other shapes.
*	To transform shape:
    *	After drawing a shape, user can transform it immediately
    *	To choose other shape for transforming, hold Ctrl key and Left mouse click on other shape’s boundary.
    *	Transform controls are:
        * Translate: Left / Right / Up / Down arrows.
        * Rotate: L/l/R/r.
        * Scale: + / -.
