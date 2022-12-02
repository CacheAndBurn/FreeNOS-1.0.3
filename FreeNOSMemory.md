# Inspection report of FreeNOS memory management

## Page size

FreeNOS uses 4k pages as defined by the constant PAGESIZE which can be found in the path FreeNOS-1.0.3/lib/libarch/arm/ARMConstant.h on line 97, where it states that ARM uses 4k pages

## Memory Space Management

Within the MemoryBlock class found within the /home/cphanes/FreeNOS-1.0.3/lib/libstd/MemoryBlock.h / MemoryBlock.cpp file structure, we can see this is where the memory is compared and copied. In the copy function a destination and source pointer are passed along with a count that represents the number of bytes being compared. Within the set function, this where the system actually writes the bytes to memory. Within the copy function, it does the algorithm to see where to place the address into memory. I believe this algorithm is First Fit, meaning it traverses the destination, finding the first spot in memory that can accomadate the size of the block being fitted. This code segment can be found on lines 47-70 of MemoryBlock.cpp.
