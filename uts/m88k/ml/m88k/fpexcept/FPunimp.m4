;function _FPunimp --      
;See the documentation of this release for the overall description of this code

		include(sub.m4)		
		global _FPunimp
		text
_FPunimp:
		sub	r3,r0,1
		jmp.n	r1
		or	r4,r0,0x40
