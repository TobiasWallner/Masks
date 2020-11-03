Mask
====
This is a C++17 header only library that provides templated masks and bit
patterns for integral data types.

Usage
-----

Just #include <mask.h>

You can use the masks as shown in the following example:

    //from struct
    long mask = mask::msb<long>::value;

    //from constant
    long cmask = mask::but_msb_v<long>;

Overview
--------
* Mask everything                       all_v           1 ... 1
* Mask none                             none_v          0 ... 0
* Mask the msb                          msb_v           1 0 ... 0
* Mask everything but the msb           but_msb_v       0 1 ... 1
* Mask the lsb                          lsb_v           0 ... 0 1
* Mask everything but the lsb           but_lsb_v       1 ... 1 0
* Mask bit                              bit             0 ... 0 1 0 ... 0  
                                                     bit n ~~~~~^
                                                     
* Mask everything but bit               bit             1 ... 1 0 1 ... 1  
                                                     bit n ~~~~~^
                                                     
* Mask everything from lsb up to n      up_to_v         0 ... 0 1 ... 1  
                                                     bit n ~~~~~^
                                                     
* Mask everything from msb down to n    down_to_v       1 ... 1 0 ... 0  
                                                   bit n ~~~~~^ 
                                                   
* Mask everything from n1 to n2         from_to_v       0 ... 0 1 ... 1 0 ... 0  
                                                    bit n2 ~~~~~^     ^~~~~~ bit n1
                                                    
* Mask everything but from_to           but_from_to_v   1 ... 1 0 ... 0 1 ... 1  
                                                    bit n2 ~~~~~^     ^~~~~~ bit n1
                                                    
