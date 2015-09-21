case 0x00: /* 00 hlt */
    if (cpuPhase == 1) { HaltFlag = 1;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

case 0x01: /* 01 hlt */
    if (cpuPhase == 1) { HaltFlag = 1;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

case 0x02: /* 02 rlc */
    if (cpuPhase == 1) { Carry = (A >> 7);A = ((A << 1) | Carry) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x03: /* 03 ret */
    if (cpuPhase == 1) { PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x04: /* 04 adi @1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { Carry = 0;PSZValue = A = _CPUAdd(MB);STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x05: /* 05 rst 00 */
    if (cpuPhase == 1) { PUSH();PCTR = 0x00;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x06: /* 06 mvi a,@1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { a = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x07: /* 07 rnc */
    if (cpuPhase == 1) { if (Carry == 0) PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

case 0x08: /* 08 inr b */
    if (cpuPhase == 1) { PSZValue = b = (b+1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x09: /* 09 dcr b */
    if (cpuPhase == 1) { PSZValue = b = (b-1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x0a: /* 0a rrc */
    if (cpuPhase == 1) { Carry = A & 1;A = (A >> 1) | (Carry << 7);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x0b: /* 0b ret */
    if (cpuPhase == 1) { PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x0c: /* 0c aci @1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { PSZValue = A = _CPUAdd(MB);STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x0d: /* 0d rst 08 */
    if (cpuPhase == 1) { PUSH();PCTR = 0x08;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x0e: /* 0e mvi b,@1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { b = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x0f: /* 0f rnz */
    if (cpuPhase == 1) { if (PSZValue != 0) PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

case 0x10: /* 10 inr c */
    if (cpuPhase == 1) { PSZValue = c = (c+1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x11: /* 11 dcr c */
    if (cpuPhase == 1) { PSZValue = c = (c-1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x12: /* 12 ral */
    if (cpuPhase == 1) { temp16 = (A << 1) | Carry;A = temp16 & 0xFF;Carry = temp16 >> 8;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x13: /* 13 ret */
    if (cpuPhase == 1) { PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x14: /* 14 sui @1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { Carry = 0;PSZValue = A = _CPUSubtract(MB);STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x15: /* 15 rst 10 */
    if (cpuPhase == 1) { PUSH();PCTR = 0x10;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x16: /* 16 mvi c,@1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { c = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x17: /* 17 rp */
    if (cpuPhase == 1) { if ((PSZValue & 0x80) == 0) PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

case 0x18: /* 18 inr d */
    if (cpuPhase == 1) { PSZValue = d = (d+1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x19: /* 19 dcr d */
    if (cpuPhase == 1) { PSZValue = d = (d-1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x1a: /* 1a rar */
    if (cpuPhase == 1) { temp16 = A | (Carry << 8);A = temp16 >> 1;Carry = temp16 & 1;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x1b: /* 1b ret */
    if (cpuPhase == 1) { PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x1c: /* 1c sbi @1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { PSZValue = A = _CPUSubtract(MB);STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x1d: /* 1d rst 18 */
    if (cpuPhase == 1) { PUSH();PCTR = 0x18;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x1e: /* 1e mvi d,@1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { d = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x1f: /* 1f rpo */
    if (cpuPhase == 1) { if (_CPUParity(PSZValue) == 0) PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

case 0x20: /* 20 inr e */
    if (cpuPhase == 1) { PSZValue = e = (e+1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x21: /* 21 dcr e */
    if (cpuPhase == 1) { PSZValue = e = (e-1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x23: /* 23 ret */
    if (cpuPhase == 1) { PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x24: /* 24 ani @1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { Carry = 0;PSZValue = A = A & MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x25: /* 25 rst 20 */
    if (cpuPhase == 1) { PUSH();PCTR = 0x20;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x26: /* 26 mvi e,@1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { e = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x27: /* 27 rc */
    if (cpuPhase == 1) { if (Carry != 0) PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

case 0x28: /* 28 inr h */
    if (cpuPhase == 1) { PSZValue = h = (h+1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x29: /* 29 dcr h */
    if (cpuPhase == 1) { PSZValue = h = (h-1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x2b: /* 2b ret */
    if (cpuPhase == 1) { PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x2c: /* 2c xri @1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { Carry = 0;PSZValue = A = A ^ MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x2d: /* 2d rst 28 */
    if (cpuPhase == 1) { PUSH();PCTR = 0x28;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x2e: /* 2e mvi h,@1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { h = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x2f: /* 2f rz */
    if (cpuPhase == 1) { if (PSZValue == 0) PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

case 0x30: /* 30 inr l */
    if (cpuPhase == 1) { PSZValue = l = (l+1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x31: /* 31 dcr l */
    if (cpuPhase == 1) { PSZValue = l = (l-1) & 0xFF;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x33: /* 33 ret */
    if (cpuPhase == 1) { PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x34: /* 34 ori @1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { Carry = 0;PSZValue = A = A | MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x35: /* 35 rst 30 */
    if (cpuPhase == 1) { PUSH();PCTR = 0x30;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x36: /* 36 mvi l,@1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { l = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x37: /* 37 rm */
    if (cpuPhase == 1) { if ((PSZValue & 0x80) != 0) PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

case 0x3b: /* 3b ret */
    if (cpuPhase == 1) { PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x3c: /* 3c cpi @1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { Carry = 0;PSZValue = _CPUSubtract(MB);STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x3d: /* 3d rst 38 */
    if (cpuPhase == 1) { PUSH();PCTR = 0x38;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x3e: /* 3e mvi m,@1 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MA = HL();STATUS(3);DISPLAY(MA,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { WRITE();STATUS(0);DISPLAY(PCTR,MB);CYCLES(9);cpuPhase = (0); }
    break;

case 0x3f: /* 3f rpe */
    if (cpuPhase == 1) { if (_CPUParity(PSZValue) != 0) PULL();;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

case 0x40: /* 40 jmp @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x41: /* 41 in 00 */
    if (cpuPhase == 1) { MA = 0x00;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READPORT();A = MB;STATUS(0);DISPLAY(PCTR,A);CYCLES(8);cpuPhase = (0); }
    break;

case 0x42: /* 42 jnc @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (Carry == 0) { PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x43: /* 43 in 01 */
    if (cpuPhase == 1) { MA = 0x01;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READPORT();A = MB;STATUS(0);DISPLAY(PCTR,A);CYCLES(8);cpuPhase = (0); }
    break;

case 0x44: /* 44 call @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PUSH();PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x45: /* 45 in 02 */
    if (cpuPhase == 1) { MA = 0x02;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READPORT();A = MB;STATUS(0);DISPLAY(PCTR,A);CYCLES(8);cpuPhase = (0); }
    break;

case 0x46: /* 46 cnc @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (Carry == 0) { PUSH();PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x47: /* 47 in 03 */
    if (cpuPhase == 1) { MA = 0x03;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READPORT();A = MB;STATUS(0);DISPLAY(PCTR,A);CYCLES(8);cpuPhase = (0); }
    break;

case 0x48: /* 48 jmp @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x49: /* 49 in 04 */
    if (cpuPhase == 1) { MA = 0x04;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READPORT();A = MB;STATUS(0);DISPLAY(PCTR,A);CYCLES(8);cpuPhase = (0); }
    break;

case 0x4a: /* 4a jnz @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (PSZValue != 0) { PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x4b: /* 4b in 05 */
    if (cpuPhase == 1) { MA = 0x05;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READPORT();A = MB;STATUS(0);DISPLAY(PCTR,A);CYCLES(8);cpuPhase = (0); }
    break;

case 0x4c: /* 4c call @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PUSH();PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x4d: /* 4d in 06 */
    if (cpuPhase == 1) { MA = 0x06;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READPORT();A = MB;STATUS(0);DISPLAY(PCTR,A);CYCLES(8);cpuPhase = (0); }
    break;

case 0x4e: /* 4e cnz @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (PSZValue != 0) { PUSH();PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x4f: /* 4f in 07 */
    if (cpuPhase == 1) { MA = 0x07;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READPORT();A = MB;STATUS(0);DISPLAY(PCTR,A);CYCLES(8);cpuPhase = (0); }
    break;

case 0x50: /* 50 jmp @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x51: /* 51 out 08 */
    if (cpuPhase == 1) { MA = 0x08;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x52: /* 52 jp @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if ((PSZValue & 0x80) == 0) { PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x53: /* 53 out 09 */
    if (cpuPhase == 1) { MA = 0x09;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x54: /* 54 call @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PUSH();PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x55: /* 55 out 0a */
    if (cpuPhase == 1) { MA = 0x0a;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x56: /* 56 cp @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if ((PSZValue & 0x80) == 0) { PUSH();PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x57: /* 57 out 0b */
    if (cpuPhase == 1) { MA = 0x0b;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x58: /* 58 jmp @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x59: /* 59 out 0c */
    if (cpuPhase == 1) { MA = 0x0c;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x5a: /* 5a jpo @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (_CPUParity(PSZValue) == 0) { PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x5b: /* 5b out 0d */
    if (cpuPhase == 1) { MA = 0x0d;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x5c: /* 5c call @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PUSH();PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x5d: /* 5d out 0e */
    if (cpuPhase == 1) { MA = 0x0e;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x5e: /* 5e cpo @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (_CPUParity(PSZValue) == 0) { PUSH();PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x5f: /* 5f out 0f */
    if (cpuPhase == 1) { MA = 0x0f;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x60: /* 60 jmp @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x61: /* 61 out 10 */
    if (cpuPhase == 1) { MA = 0x10;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x62: /* 62 jc @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (Carry != 0) { PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x63: /* 63 out 11 */
    if (cpuPhase == 1) { MA = 0x11;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x64: /* 64 call @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PUSH();PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x65: /* 65 out 12 */
    if (cpuPhase == 1) { MA = 0x12;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x66: /* 66 cc @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (Carry != 0) { PUSH();PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x67: /* 67 out 13 */
    if (cpuPhase == 1) { MA = 0x13;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x68: /* 68 jmp @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x69: /* 69 out 14 */
    if (cpuPhase == 1) { MA = 0x14;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x6a: /* 6a jz @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (PSZValue == 0) { PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x6b: /* 6b out 15 */
    if (cpuPhase == 1) { MA = 0x15;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x6c: /* 6c call @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PUSH();PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x6d: /* 6d out 16 */
    if (cpuPhase == 1) { MA = 0x16;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x6e: /* 6e cz @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (PSZValue == 0) { PUSH();PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x6f: /* 6f out 17 */
    if (cpuPhase == 1) { MA = 0x17;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x70: /* 70 jmp @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x71: /* 71 out 18 */
    if (cpuPhase == 1) { MA = 0x18;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x72: /* 72 jm @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if ((PSZValue & 0x80) != 0) { PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x73: /* 73 out 19 */
    if (cpuPhase == 1) { MA = 0x19;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x74: /* 74 call @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PUSH();PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x75: /* 75 out 1a */
    if (cpuPhase == 1) { MA = 0x1a;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x76: /* 76 cm @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if ((PSZValue & 0x80) != 0) { PUSH();PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x77: /* 77 out 1b */
    if (cpuPhase == 1) { MA = 0x1b;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x78: /* 78 jmp @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x79: /* 79 out 1c */
    if (cpuPhase == 1) { MA = 0x1c;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x7a: /* 7a jpe @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (_CPUParity(PSZValue) != 0) { PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x7b: /* 7b out 1d */
    if (cpuPhase == 1) { MA = 0x1d;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x7c: /* 7c call @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { PUSH();PCTR = word16;STATUS(0);DISPLAY(word16,MB);CYCLES(11);cpuPhase = (0); }
    break;

case 0x7d: /* 7d out 1e */
    if (cpuPhase == 1) { MA = 0x1e;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x7e: /* 7e cpe @2 */
    if (cpuPhase == 1) { FETCH();STATUS(2);DISPLAY(PCTR,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { word16 = MB;FETCH();word16 = ((((WORD16)MB) << 8)|word16) & 0x3FFF;;STATUS(2);DISPLAY(PCTR,MB);cpuPhase = 3; }
    if (cpuPhase == 3) { if (_CPUParity(PSZValue) != 0) { PUSH();PCTR = word16; };STATUS(0);DISPLAY(PCTR,MB);CYCLES(10);cpuPhase = (0); }
    break;

case 0x7f: /* 7f out 1f */
    if (cpuPhase == 1) { MA = 0x1f;STATUS(1);DISPLAY((MA << 8)|A,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = A;WRITEPORT();STATUS(0);DISPLAY(PCTR,A);CYCLES(6);cpuPhase = (0); }
    break;

case 0x80: /* 80 add a */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUAdd(a);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x81: /* 81 add b */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUAdd(b);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x82: /* 82 add c */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUAdd(c);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x83: /* 83 add d */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUAdd(d);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x84: /* 84 add e */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUAdd(e);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x85: /* 85 add h */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUAdd(h);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x86: /* 86 add l */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUAdd(l);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x87: /* 87 add m */
    if (cpuPhase == 1) { MA = HL();;STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();Carry = 0;PSZValue = A = _CPUAdd(MB);STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x88: /* 88 adc a */
    if (cpuPhase == 1) { PSZValue = A = _CPUAdd(a);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x89: /* 89 adc b */
    if (cpuPhase == 1) { PSZValue = A = _CPUAdd(b);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x8a: /* 8a adc c */
    if (cpuPhase == 1) { PSZValue = A = _CPUAdd(c);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x8b: /* 8b adc d */
    if (cpuPhase == 1) { PSZValue = A = _CPUAdd(d);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x8c: /* 8c adc e */
    if (cpuPhase == 1) { PSZValue = A = _CPUAdd(e);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x8d: /* 8d adc h */
    if (cpuPhase == 1) { PSZValue = A = _CPUAdd(h);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x8e: /* 8e adc l */
    if (cpuPhase == 1) { PSZValue = A = _CPUAdd(l);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x8f: /* 8f adc m */
    if (cpuPhase == 1) { MA = HL();;STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();PSZValue = A = _CPUAdd(MB);STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x90: /* 90 sub a */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUSubtract(a);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x91: /* 91 sub b */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUSubtract(b);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x92: /* 92 sub c */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUSubtract(c);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x93: /* 93 sub d */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUSubtract(d);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x94: /* 94 sub e */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUSubtract(e);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x95: /* 95 sub h */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUSubtract(h);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x96: /* 96 sub l */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = _CPUSubtract(l);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x97: /* 97 sub m */
    if (cpuPhase == 1) { MA = HL();;STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();Carry = 0;PSZValue = A = _CPUSubtract(MB);STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0x98: /* 98 sbb a */
    if (cpuPhase == 1) { PSZValue = A = _CPUSubtract(a);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x99: /* 99 sbb b */
    if (cpuPhase == 1) { PSZValue = A = _CPUSubtract(b);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x9a: /* 9a sbb c */
    if (cpuPhase == 1) { PSZValue = A = _CPUSubtract(c);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x9b: /* 9b sbb d */
    if (cpuPhase == 1) { PSZValue = A = _CPUSubtract(d);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x9c: /* 9c sbb e */
    if (cpuPhase == 1) { PSZValue = A = _CPUSubtract(e);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x9d: /* 9d sbb h */
    if (cpuPhase == 1) { PSZValue = A = _CPUSubtract(h);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x9e: /* 9e sbb l */
    if (cpuPhase == 1) { PSZValue = A = _CPUSubtract(l);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0x9f: /* 9f sbb m */
    if (cpuPhase == 1) { MA = HL();;STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();PSZValue = A = _CPUSubtract(MB);STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xa0: /* a0 and a */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A & a;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xa1: /* a1 and b */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A & b;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xa2: /* a2 and c */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A & c;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xa3: /* a3 and d */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A & d;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xa4: /* a4 and e */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A & e;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xa5: /* a5 and h */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A & h;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xa6: /* a6 and l */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A & l;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xa7: /* a7 and m */
    if (cpuPhase == 1) { MA = HL();;STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();Carry = 0;PSZValue = A = A & MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xa8: /* a8 xor a */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A ^ a;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xa9: /* a9 xor b */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A ^ b;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xaa: /* aa xor c */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A ^ c;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xab: /* ab xor d */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A ^ d;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xac: /* ac xor e */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A ^ e;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xad: /* ad xor h */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A ^ h;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xae: /* ae xor l */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A ^ l;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xaf: /* af xor m */
    if (cpuPhase == 1) { MA = HL();;STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();Carry = 0;PSZValue = A = A ^ MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xb0: /* b0 ora a */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A | a;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xb1: /* b1 ora b */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A | b;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xb2: /* b2 ora c */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A | c;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xb3: /* b3 ora d */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A | d;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xb4: /* b4 ora e */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A | e;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xb5: /* b5 ora h */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A | h;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xb6: /* b6 ora l */
    if (cpuPhase == 1) { Carry = 0;PSZValue = A = A | l;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xb7: /* b7 ora m */
    if (cpuPhase == 1) { MA = HL();;STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();Carry = 0;PSZValue = A = A | MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xb8: /* b8 cmp a */
    if (cpuPhase == 1) { Carry = 0;PSZValue = _CPUSubtract(a);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xb9: /* b9 cmp b */
    if (cpuPhase == 1) { Carry = 0;PSZValue = _CPUSubtract(b);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xba: /* ba cmp c */
    if (cpuPhase == 1) { Carry = 0;PSZValue = _CPUSubtract(c);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xbb: /* bb cmp d */
    if (cpuPhase == 1) { Carry = 0;PSZValue = _CPUSubtract(d);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xbc: /* bc cmp e */
    if (cpuPhase == 1) { Carry = 0;PSZValue = _CPUSubtract(e);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xbd: /* bd cmp h */
    if (cpuPhase == 1) { Carry = 0;PSZValue = _CPUSubtract(h);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xbe: /* be cmp l */
    if (cpuPhase == 1) { Carry = 0;PSZValue = _CPUSubtract(l);STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xbf: /* bf cmp m */
    if (cpuPhase == 1) { MA = HL();;STATUS(2);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();Carry = 0;PSZValue = _CPUSubtract(MB);STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xc0: /* c0 mov a,a */
    if (cpuPhase == 1) { A = a;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xc1: /* c1 mov a,b */
    if (cpuPhase == 1) { A = b;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xc2: /* c2 mov a,c */
    if (cpuPhase == 1) { A = c;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xc3: /* c3 mov a,d */
    if (cpuPhase == 1) { A = d;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xc4: /* c4 mov a,e */
    if (cpuPhase == 1) { A = e;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xc5: /* c5 mov a,h */
    if (cpuPhase == 1) { A = h;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xc6: /* c6 mov a,l */
    if (cpuPhase == 1) { A = l;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xc7: /* c7 mov a,m */
    if (cpuPhase == 1) { MA = HL();STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();a = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xc8: /* c8 mov b,a */
    if (cpuPhase == 1) { B = a;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xc9: /* c9 mov b,b */
    if (cpuPhase == 1) { B = b;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xca: /* ca mov b,c */
    if (cpuPhase == 1) { B = c;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xcb: /* cb mov b,d */
    if (cpuPhase == 1) { B = d;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xcc: /* cc mov b,e */
    if (cpuPhase == 1) { B = e;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xcd: /* cd mov b,h */
    if (cpuPhase == 1) { B = h;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xce: /* ce mov b,l */
    if (cpuPhase == 1) { B = l;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xcf: /* cf mov b,m */
    if (cpuPhase == 1) { MA = HL();STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();b = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xd0: /* d0 mov c,a */
    if (cpuPhase == 1) { C = a;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xd1: /* d1 mov c,b */
    if (cpuPhase == 1) { C = b;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xd2: /* d2 mov c,c */
    if (cpuPhase == 1) { C = c;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xd3: /* d3 mov c,d */
    if (cpuPhase == 1) { C = d;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xd4: /* d4 mov c,e */
    if (cpuPhase == 1) { C = e;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xd5: /* d5 mov c,h */
    if (cpuPhase == 1) { C = h;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xd6: /* d6 mov c,l */
    if (cpuPhase == 1) { C = l;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xd7: /* d7 mov c,m */
    if (cpuPhase == 1) { MA = HL();STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();c = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xd8: /* d8 mov d,a */
    if (cpuPhase == 1) { D = a;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xd9: /* d9 mov d,b */
    if (cpuPhase == 1) { D = b;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xda: /* da mov d,c */
    if (cpuPhase == 1) { D = c;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xdb: /* db mov d,d */
    if (cpuPhase == 1) { D = d;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xdc: /* dc mov d,e */
    if (cpuPhase == 1) { D = e;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xdd: /* dd mov d,h */
    if (cpuPhase == 1) { D = h;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xde: /* de mov d,l */
    if (cpuPhase == 1) { D = l;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xdf: /* df mov d,m */
    if (cpuPhase == 1) { MA = HL();STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();d = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xe0: /* e0 mov e,a */
    if (cpuPhase == 1) { E = a;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xe1: /* e1 mov e,b */
    if (cpuPhase == 1) { E = b;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xe2: /* e2 mov e,c */
    if (cpuPhase == 1) { E = c;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xe3: /* e3 mov e,d */
    if (cpuPhase == 1) { E = d;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xe4: /* e4 mov e,e */
    if (cpuPhase == 1) { E = e;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xe5: /* e5 mov e,h */
    if (cpuPhase == 1) { E = h;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xe6: /* e6 mov e,l */
    if (cpuPhase == 1) { E = l;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xe7: /* e7 mov e,m */
    if (cpuPhase == 1) { MA = HL();STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();e = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xe8: /* e8 mov h,a */
    if (cpuPhase == 1) { H = a;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xe9: /* e9 mov h,b */
    if (cpuPhase == 1) { H = b;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xea: /* ea mov h,c */
    if (cpuPhase == 1) { H = c;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xeb: /* eb mov h,d */
    if (cpuPhase == 1) { H = d;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xec: /* ec mov h,e */
    if (cpuPhase == 1) { H = e;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xed: /* ed mov h,h */
    if (cpuPhase == 1) { H = h;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xee: /* ee mov h,l */
    if (cpuPhase == 1) { H = l;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xef: /* ef mov h,m */
    if (cpuPhase == 1) { MA = HL();STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();h = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xf0: /* f0 mov l,a */
    if (cpuPhase == 1) { L = a;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xf1: /* f1 mov l,b */
    if (cpuPhase == 1) { L = b;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xf2: /* f2 mov l,c */
    if (cpuPhase == 1) { L = c;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xf3: /* f3 mov l,d */
    if (cpuPhase == 1) { L = d;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xf4: /* f4 mov l,e */
    if (cpuPhase == 1) { L = e;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xf5: /* f5 mov l,h */
    if (cpuPhase == 1) { L = h;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xf6: /* f6 mov l,l */
    if (cpuPhase == 1) { L = l;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(5);cpuPhase = (0); }
    break;

case 0xf7: /* f7 mov l,m */
    if (cpuPhase == 1) { MA = HL();STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { READ();l = MB;STATUS(0);DISPLAY(PCTR,MB);CYCLES(8);cpuPhase = (0); }
    break;

case 0xf8: /* f8 mov m,a */
    if (cpuPhase == 1) { MA = HL();;STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = a;WRITE();;STATUS(0);DISPLAY(PCTR,MB);CYCLES(7);cpuPhase = (0); }
    break;

case 0xf9: /* f9 mov m,b */
    if (cpuPhase == 1) { MA = HL();;STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = b;WRITE();;STATUS(0);DISPLAY(PCTR,MB);CYCLES(7);cpuPhase = (0); }
    break;

case 0xfa: /* fa mov m,c */
    if (cpuPhase == 1) { MA = HL();;STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = c;WRITE();;STATUS(0);DISPLAY(PCTR,MB);CYCLES(7);cpuPhase = (0); }
    break;

case 0xfb: /* fb mov m,d */
    if (cpuPhase == 1) { MA = HL();;STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = d;WRITE();;STATUS(0);DISPLAY(PCTR,MB);CYCLES(7);cpuPhase = (0); }
    break;

case 0xfc: /* fc mov m,e */
    if (cpuPhase == 1) { MA = HL();;STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = e;WRITE();;STATUS(0);DISPLAY(PCTR,MB);CYCLES(7);cpuPhase = (0); }
    break;

case 0xfd: /* fd mov m,h */
    if (cpuPhase == 1) { MA = HL();;STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = h;WRITE();;STATUS(0);DISPLAY(PCTR,MB);CYCLES(7);cpuPhase = (0); }
    break;

case 0xfe: /* fe mov m,l */
    if (cpuPhase == 1) { MA = HL();;STATUS(3);DISPLAY(MA,opcode);cpuPhase = 2; }
    if (cpuPhase == 2) { MB = l;WRITE();;STATUS(0);DISPLAY(PCTR,MB);CYCLES(7);cpuPhase = (0); }
    break;

case 0xff: /* ff hlt */
    if (cpuPhase == 1) { HaltFlag = 1;STATUS(0);DISPLAY(PCTR,opcode);CYCLES(4);cpuPhase = (0); }
    break;

