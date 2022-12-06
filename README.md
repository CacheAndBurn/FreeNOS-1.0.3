# CS 4310.03 Project 4: Inspect FreeNOS Memory

## Group: CacheAndBurn

### Page Size

FreeNOS uses 4k pages as defined by the constant PAGESIZE which can be found in the path FreeNOS-1.0.3/lib/libarch/arm/ARMConstant.h on line 97, where it states that ARM uses 4k pages. FreeNOS also uses first-level and second-level page tables. On lines 102 and 103, respectively, it states that TTBR0 is the first-level page table for the application and TTBR1 is the first-level page table of the kernel/OS, which is always 16KB. Line 111 states that second-level page tables are 1KB in size with 1MB in virtual memory.

### Memory Space Management

Within the MemoryBlock class found within the /home/cphanes/FreeNOS-1.0.3/lib/libstd/MemoryBlock.h / MemoryBlock.cpp file structure, we can see this is where the memory is compared and copied. In the copy function a destination and source pointer are passed along with a count that represents the number of bytes being compared. Within the set function, this where the system actually writes the bytes to memory. Within the copy function, it does the algorithm to see where to place the address into memory. I believe this algorithm is First Fit, meaning it traverses the destination, finding the first spot in memory that can accomadate the size of the block being fitted. This code segment can be found on lines 47-70 of MemoryBlock.cpp.

In FreeNOS/lib/libarch/MemoryContext.h, the findFree(...) function on line 213 also follows the First Fit algorithm. In order to find unused memory, the function must find the first continuous block of unused virtual memory before returning the virtual address of the first page of the block. This code segment can be found on lines 117 to 144 in FreeNOS-1.0.3/lib/libarch/MemoryContext.cpp.

Pages are given a virtual address in memory via the setVirtual(...) function inside FreeNOS-1.0.3/lib/libipc/MemoryChannel.h. This setVirtual(...) function assumes that the virtual address has already been mapped into the designated address space. Likewise, pages are given a physical address in memory via the setPhysical(...) function inside FreeNOS-1.0.3/lib/libipc/MemoryChannel.h. This setPhysical(...) function takes the physical address and maps it into the current address space using IO:map. These functions can be found on lines 86-88 and 104-106, respectively.

### Contributions

Gabrielle David:

- 
    
Urjaa Ghimirey:

- 
    
Cody Hanes:

- 
    