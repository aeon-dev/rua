[0x00] # MOV A, B
!fetch
ao, bi, eoi

[0x01] # MOV A, X
!fetch
ao, xi, eoi

[0x02] # MOV A, Y
!fetch
ao, yi, eoi

[0x03] # MOV A, SP
!fetch
ao, spi, eoi

[0x04] # MOV A, SR
!fetch
ao, sri, eoi

[0x05] # MOV B, A
!fetch
bo, ai, eoi

[0x06] # MOV B, X
!fetch
bo, xi, eoi

[0x07] # MOV B, Y
!fetch
bo, yi, eoi

[0x08] # MOV B, SP
!fetch
bo, spi, eoi

[0x09] # MOV B, SR
!fetch
bo, sri, eoi

[0x0A] # MOV X, A
!fetch
xo, ai, eoi

[0x0B] # MOV X, B
!fetch
xo, bi, eoi

[0x0C] # MOV Y, A
!fetch
yo, ai, eoi

[0x0D] # MOV Y, B
!fetch
yo, bi, eoi

[0x0E] # MOV SP, A
!fetch
spo, ai, eoi

[0x0F] # MOV SR, A
!fetch
sro, ai, eoi
