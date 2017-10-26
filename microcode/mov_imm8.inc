[mov_imm8_eoi]
pcp, eoi

[0x10] # MOV A, imm8
!fetch
pco, mari, mo, ai
!mov_imm8_eoi

[0x11] # MOV B, imm8
!fetch
pco, mari, mo, bi
!mov_imm8_eoi

[0x12] # MOV X, imm8
!fetch
pco, mari, mo, xi
!mov_imm8_eoi

[0x13] # MOV Y, imm8
!fetch
pco, mari, mo, yi
!mov_imm8_eoi

[0x14] # MOV SP, imm8
!fetch
pco, mari, mo, spi
!mov_imm8_eoi

[0x15] # MOV SR, imm8
!fetch
pco, mari, mo, sri
!mov_imm8_eoi

[0x15] # MOV [SP], imm8
!fetch
pco, mari, mo
# Todo? Needs some kind of temp register?
!mov_imm8_eoi
