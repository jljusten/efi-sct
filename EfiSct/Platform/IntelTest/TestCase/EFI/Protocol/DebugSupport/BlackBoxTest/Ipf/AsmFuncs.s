// Copyright (c) 2005, Intel Corporation
// All rights reserved. This program and the accompanying materials
// are licensed and made available under the terms and conditions of the Eclipse Public License
// which accompanies this distribution.  The full text of the license may be found at
// http://www.opensource.org/licenses/eclipse-1.0.php
//
// THE PROGRAM IS DISTRIBUTED UNDER THE ECLIPSE PUBLIC LICENSE (EPL) ON AN "AS IS" BASIS,
// WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//


/////////////////////////////////////////////
//
//  Name:
//      SoftwareBreak
//
//  Description:
//      C callable function to generate a software break
//

        .global         SoftwareBreak
        .proc           SoftwareBreak
SoftwareBreak::
        break        0;;
        {
            .mib
            nop.m   0
            nop.i   0
            nop.b   0
        }
        br.ret.sptk.many    b0

        .endp           SoftwareBreak

