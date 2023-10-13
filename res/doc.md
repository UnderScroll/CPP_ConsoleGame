https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
https://www.w3.org/TR/xml-entity-names/025.html
https://learn.microsoft.com/fr-fr/windows/console/char-info-str

**Convention**
variable => camelCase
class member => type _name;
ref => type r_name;
function => PascaleCase
class => PascaleCase
const => ALL_CAPS

Include order :
\#include <sharedlib>

\#include "main.h"

\#include "other.h"

Excluding empty or one line constructor/destructor/otherSpecialFunctions if there is a cpp and h file : definition in h file, implementation in cpp file
No diacritics or special symbols
Namespaces do not increase indentation
Everything is in core namespace (there was several conflict with windows.h)