=What=
A collection of *Classic* and *Modern* Computer Science *Algorithms* and *Data Structures* in the form of a C++ template library.

=Why=
Most libraries provide very few or no choice at all regarding the concrete implementation of their abstract data structures. For instance, an associative container could be implemented as a red-black tree instead of a hash table. Both have different characteristics like speed and space complexities but these are not always documented by the library, thus all the user knows about the implementation is the general contract - the outcome of the operations.

Even though the libraries may provide good implementations for its algorithms and data structures, what works in one situation doesn't necessarily works well on another. Let's assume you need an associative array. A hash table would be just fine if all you need is random access, but if you also need sorted iteration or range scan, a binary search tree would be way better.

There are several daily situations where these details don't really matter, but when they do the developer often ends up having to provide his own implementation of the data structures or algorithms instead of just reusing code which should be generic and widely available by now.

=Goal=
The aim of this project is to provide portable object oriented reference implementations for a comprehensive collection of classic and modern algorithms and data structures, with proper documentation of their speed and space complexities. Different implementations of the same data structure may be provided if this difference is meaningful for a given context.

Even though this project started with learning purposes in mind, code quality and simplicity are top priorities.

=How=
C++ is the programming language of choice. The heavy use of templates not only facilitates generic implementations but also avoids the need for binary distributions. The library is provided in the form of header files, thus no compilation is needed before use.

No third-party libraries are used, which helps to avoid certain portability and deployment issues.
