// this file autogenerated by CharClasses_mk.cpp

#include <wchar.h>

bool IsCharFullWidth(wchar_t c)
{
	switch (c) {
		case 0x1100 ... 0x115f:
		case 0x231a: case 0x231b:
		case 0x2329: case 0x232a:
		case 0x23e9 ... 0x23ec:
		case 0x23f0:
		case 0x23f3:
		case 0x25fd: case 0x25fe:
		case 0x2614: case 0x2615:
		case 0x2648 ... 0x2653:
		case 0x267f:
		case 0x2693:
		case 0x26a1:
		case 0x26aa: case 0x26ab:
		case 0x26bd: case 0x26be:
		case 0x26c4: case 0x26c5:
		case 0x26ce:
		case 0x26d4:
		case 0x26ea:
		case 0x26f2: case 0x26f3:
		case 0x26f5:
		case 0x26fa:
		case 0x26fd:
		case 0x2705:
		case 0x270a: case 0x270b:
		case 0x2728:
		case 0x274c:
		case 0x274e:
		case 0x2753 ... 0x2755:
		case 0x2757:
		case 0x2795 ... 0x2797:
		case 0x27b0:
		case 0x27bf:
		case 0x2b1b: case 0x2b1c:
		case 0x2b50:
		case 0x2b55:
		case 0x2e80 ... 0x2e99:
		case 0x2e9b ... 0x2ef3:
		case 0x2f00 ... 0x2fd5:
		case 0x2ff0 ... 0x2ffb:
		case 0x3000 ... 0x303e:
		case 0x3041 ... 0x3096:
		case 0x3099 ... 0x30ff:
		case 0x3105 ... 0x312f:
		case 0x3131 ... 0x318e:
		case 0x3190 ... 0x31e3:
		case 0x31f0 ... 0x321e:
		case 0x3220 ... 0x3247:
		case 0x3250 ... 0x4dbf:
		case 0x4e00 ... 0xa48c:
		case 0xa490 ... 0xa4c6:
		case 0xa960 ... 0xa97c:
		case 0xac00 ... 0xd7a3:
		case 0xf900 ... 0xfaff:
		case 0xfe10 ... 0xfe19:
		case 0xfe30 ... 0xfe52:
		case 0xfe54 ... 0xfe66:
		case 0xfe68 ... 0xfe6b:
		case 0xff01 ... 0xff60:
		case 0xffe0 ... 0xffe6:
		case 0x16fe0 ... 0x16fe4:
		case 0x16ff0: case 0x16ff1:
		case 0x17000 ... 0x187f7:
		case 0x18800 ... 0x18cd5:
		case 0x18d00 ... 0x18d08:
		case 0x1b000 ... 0x1b11e:
		case 0x1b150 ... 0x1b152:
		case 0x1b164 ... 0x1b167:
		case 0x1b170 ... 0x1b2fb:
		case 0x1f004:
		case 0x1f0cf:
		case 0x1f18e:
		case 0x1f191 ... 0x1f19a:
		case 0x1f200 ... 0x1f202:
		case 0x1f210 ... 0x1f23b:
		case 0x1f240 ... 0x1f248:
		case 0x1f250: case 0x1f251:
		case 0x1f260 ... 0x1f265:
		case 0x1f300 ... 0x1f320:
		case 0x1f32d ... 0x1f335:
		case 0x1f337 ... 0x1f37c:
		case 0x1f37e ... 0x1f393:
		case 0x1f3a0 ... 0x1f3ca:
		case 0x1f3cf ... 0x1f3d3:
		case 0x1f3e0 ... 0x1f3f0:
		case 0x1f3f4:
		case 0x1f3f8 ... 0x1f43e:
		case 0x1f440:
		case 0x1f442 ... 0x1f4fc:
		case 0x1f4ff ... 0x1f53d:
		case 0x1f54b ... 0x1f54e:
		case 0x1f550 ... 0x1f567:
		case 0x1f57a:
		case 0x1f595: case 0x1f596:
		case 0x1f5a4:
		case 0x1f5fb ... 0x1f64f:
		case 0x1f680 ... 0x1f6c5:
		case 0x1f6cc:
		case 0x1f6d0 ... 0x1f6d2:
		case 0x1f6d5 ... 0x1f6d7:
		case 0x1f6eb: case 0x1f6ec:
		case 0x1f6f4 ... 0x1f6fc:
		case 0x1f7e0 ... 0x1f7eb:
		case 0x1f90c ... 0x1f93a:
		case 0x1f93c ... 0x1f945:
		case 0x1f947 ... 0x1f978:
		case 0x1f97a ... 0x1f9cb:
		case 0x1f9cd ... 0x1f9ff:
		case 0x1fa70 ... 0x1fa74:
		case 0x1fa78 ... 0x1fa7a:
		case 0x1fa80 ... 0x1fa86:
		case 0x1fa90 ... 0x1faa8:
		case 0x1fab0 ... 0x1fab6:
		case 0x1fac0 ... 0x1fac2:
		case 0x1fad0 ... 0x1fad6:
		case 0x20000 ... 0x2fffd:
		case 0x30000 ... 0x3fffd:
			return true;
		default: return false;
	}
}

bool IsCharPrefix(wchar_t c)
{
	switch (c) {
		case 0xd800 ... 0xdfff:
			return true;
		default: return false;
	}
}

bool IsCharSuffix(wchar_t c)
{
	switch (c) {
		case 0x300 ... 0x36f:
		case 0x483 ... 0x487:
		case 0x591 ... 0x5bd:
		case 0x5bf:
		case 0x5c1: case 0x5c2:
		case 0x5c4: case 0x5c5:
		case 0x5c7:
		case 0x610 ... 0x61a:
		case 0x620:
		case 0x622 ... 0x65f:
		case 0x66e ... 0x673:
		case 0x675 ... 0x6d3:
		case 0x6d5 ... 0x6dc:
		case 0x6df ... 0x6e4:
		case 0x6e7: case 0x6e8:
		case 0x6ea ... 0x6ef:
		case 0x6fa ... 0x6fc:
		case 0x6ff:
		case 0x710 ... 0x74a:
		case 0x74d ... 0x77f:
		case 0x7a6 ... 0x7b0:
		case 0x7ca ... 0x7f3:
		case 0x7fa:
		case 0x7fd:
		case 0x816 ... 0x819:
		case 0x81b ... 0x823:
		case 0x825 ... 0x827:
		case 0x829 ... 0x82d:
		case 0x840 ... 0x85b:
		case 0x860:
		case 0x862 ... 0x865:
		case 0x867 ... 0x86a:
		case 0x8a0 ... 0x8ac:
		case 0x8ae ... 0x8b4:
		case 0x8b6 ... 0x8c7:
		case 0x8d3 ... 0x8e1:
		case 0x8e3 ... 0x903:
		case 0x93a ... 0x93c:
		case 0x93e ... 0x94f:
		case 0x951 ... 0x957:
		case 0x962: case 0x963:
		case 0x981 ... 0x983:
		case 0x9bc:
		case 0x9be ... 0x9c4:
		case 0x9c7: case 0x9c8:
		case 0x9cb ... 0x9cd:
		case 0x9d7:
		case 0x9e2: case 0x9e3:
		case 0x9fe:
		case 0xa01 ... 0xa03:
		case 0xa3c:
		case 0xa3e ... 0xa42:
		case 0xa47: case 0xa48:
		case 0xa4b ... 0xa4d:
		case 0xa51:
		case 0xa70: case 0xa71:
		case 0xa75:
		case 0xa81 ... 0xa83:
		case 0xabc:
		case 0xabe ... 0xac5:
		case 0xac7 ... 0xac9:
		case 0xacb ... 0xacd:
		case 0xae2: case 0xae3:
		case 0xafa ... 0xaff:
		case 0xb01 ... 0xb03:
		case 0xb3c:
		case 0xb3e ... 0xb44:
		case 0xb47: case 0xb48:
		case 0xb4b ... 0xb4d:
		case 0xb55 ... 0xb57:
		case 0xb62: case 0xb63:
		case 0xb82:
		case 0xbbe ... 0xbc2:
		case 0xbc6 ... 0xbc8:
		case 0xbca ... 0xbcd:
		case 0xbd7:
		case 0xc00 ... 0xc04:
		case 0xc3e ... 0xc44:
		case 0xc46 ... 0xc48:
		case 0xc4a ... 0xc4d:
		case 0xc55: case 0xc56:
		case 0xc62: case 0xc63:
		case 0xc81 ... 0xc83:
		case 0xcbc:
		case 0xcbe ... 0xcc4:
		case 0xcc6 ... 0xcc8:
		case 0xcca ... 0xccd:
		case 0xcd5: case 0xcd6:
		case 0xce2: case 0xce3:
		case 0xd00 ... 0xd03:
		case 0xd3b: case 0xd3c:
		case 0xd3e ... 0xd44:
		case 0xd46 ... 0xd48:
		case 0xd4a ... 0xd4d:
		case 0xd57:
		case 0xd62: case 0xd63:
		case 0xd81 ... 0xd83:
		case 0xdca:
		case 0xdcf ... 0xdd4:
		case 0xdd6:
		case 0xdd8 ... 0xddf:
		case 0xdf2: case 0xdf3:
		case 0xe31:
		case 0xe34 ... 0xe3a:
		case 0xe47 ... 0xe4e:
		case 0xeb1:
		case 0xeb4 ... 0xebc:
		case 0xec8 ... 0xecd:
		case 0xf18: case 0xf19:
		case 0xf35:
		case 0xf37:
		case 0xf39:
		case 0xf3e: case 0xf3f:
		case 0xf71 ... 0xf84:
		case 0xf86: case 0xf87:
		case 0xf8d ... 0xf97:
		case 0xf99 ... 0xfbc:
		case 0xfc6:
		case 0x102b ... 0x103e:
		case 0x1056 ... 0x1059:
		case 0x105e ... 0x1060:
		case 0x1062 ... 0x1064:
		case 0x1067 ... 0x106d:
		case 0x1071 ... 0x1074:
		case 0x1082 ... 0x108d:
		case 0x108f:
		case 0x109a ... 0x109d:
		case 0x135d ... 0x135f:
		case 0x1712 ... 0x1714:
		case 0x1732 ... 0x1734:
		case 0x1752: case 0x1753:
		case 0x1772: case 0x1773:
		case 0x17b4 ... 0x17d3:
		case 0x17dd:
		case 0x1807:
		case 0x180a ... 0x180d:
		case 0x1820 ... 0x1878:
		case 0x1885 ... 0x18aa:
		case 0x1920 ... 0x192b:
		case 0x1930 ... 0x193b:
		case 0x1a17 ... 0x1a1b:
		case 0x1a55 ... 0x1a5e:
		case 0x1a60 ... 0x1a7c:
		case 0x1a7f:
		case 0x1ab0 ... 0x1b04:
		case 0x1b34 ... 0x1b44:
		case 0x1b6b ... 0x1b73:
		case 0x1b80 ... 0x1b82:
		case 0x1ba1 ... 0x1bad:
		case 0x1be6 ... 0x1bf3:
		case 0x1c24 ... 0x1c37:
		case 0x1cd0 ... 0x1cd2:
		case 0x1cd4 ... 0x1ce8:
		case 0x1ced:
		case 0x1cf4:
		case 0x1cf7 ... 0x1cf9:
		case 0x1dc0 ... 0x1dff:
		case 0x200d:
		case 0x20d0 ... 0x20ff:
		case 0x2cef ... 0x2cf1:
		case 0x2d7f:
		case 0x2de0 ... 0x2dff:
		case 0x302a ... 0x302f:
		case 0x3099: case 0x309a:
		case 0xa66f:
		case 0xa674 ... 0xa67d:
		case 0xa69e: case 0xa69f:
		case 0xa6f0: case 0xa6f1:
		case 0xa802:
		case 0xa806:
		case 0xa80b:
		case 0xa823 ... 0xa827:
		case 0xa82c:
		case 0xa840 ... 0xa872:
		case 0xa880: case 0xa881:
		case 0xa8b4 ... 0xa8c5:
		case 0xa8e0 ... 0xa8f1:
		case 0xa8ff:
		case 0xa926 ... 0xa92d:
		case 0xa947 ... 0xa953:
		case 0xa980 ... 0xa983:
		case 0xa9b3 ... 0xa9c0:
		case 0xa9e5:
		case 0xaa29 ... 0xaa36:
		case 0xaa43:
		case 0xaa4c: case 0xaa4d:
		case 0xaa7b ... 0xaa7d:
		case 0xaab0:
		case 0xaab2 ... 0xaab4:
		case 0xaab7: case 0xaab8:
		case 0xaabe: case 0xaabf:
		case 0xaac1:
		case 0xaaeb ... 0xaaef:
		case 0xaaf5: case 0xaaf6:
		case 0xabe3 ... 0xabea:
		case 0xabec: case 0xabed:
		case 0xfb1e:
		case 0xfe00 ... 0xfe0f:
		case 0xfe20 ... 0xfe2f:
		case 0x101fd:
		case 0x102e0:
		case 0x10376 ... 0x1037a:
		case 0x10a01 ... 0x10a03:
		case 0x10a05: case 0x10a06:
		case 0x10a0c ... 0x10a0f:
		case 0x10a38 ... 0x10a3a:
		case 0x10a3f:
		case 0x10ac0 ... 0x10ac5:
		case 0x10ac7:
		case 0x10ac9: case 0x10aca:
		case 0x10acd ... 0x10ae1:
		case 0x10ae4 ... 0x10ae6:
		case 0x10aeb ... 0x10aef:
		case 0x10b80 ... 0x10b91:
		case 0x10ba9 ... 0x10bae:
		case 0x10d00 ... 0x10d27:
		case 0x10eab: case 0x10eac:
		case 0x10f30 ... 0x10f44:
		case 0x10f46 ... 0x10f54:
		case 0x10fb0:
		case 0x10fb2 ... 0x10fb6:
		case 0x10fb8 ... 0x10fbf:
		case 0x10fc1 ... 0x10fc4:
		case 0x10fc9 ... 0x10fcb:
		case 0x11000 ... 0x11002:
		case 0x11038 ... 0x11046:
		case 0x1107f ... 0x11082:
		case 0x110b0 ... 0x110ba:
		case 0x11100 ... 0x11102:
		case 0x11127 ... 0x11134:
		case 0x11145: case 0x11146:
		case 0x11173:
		case 0x11180 ... 0x11182:
		case 0x111b3 ... 0x111c0:
		case 0x111c9 ... 0x111cc:
		case 0x111ce: case 0x111cf:
		case 0x1122c ... 0x11237:
		case 0x1123e:
		case 0x112df ... 0x112ea:
		case 0x11300 ... 0x11303:
		case 0x1133b: case 0x1133c:
		case 0x1133e ... 0x11344:
		case 0x11347: case 0x11348:
		case 0x1134b ... 0x1134d:
		case 0x11357:
		case 0x11362: case 0x11363:
		case 0x11366 ... 0x1136c:
		case 0x11370 ... 0x11374:
		case 0x11435 ... 0x11446:
		case 0x1145e:
		case 0x114b0 ... 0x114c3:
		case 0x115af ... 0x115b5:
		case 0x115b8 ... 0x115c0:
		case 0x115dc: case 0x115dd:
		case 0x11630 ... 0x11640:
		case 0x116ab ... 0x116b7:
		case 0x1171d ... 0x1172b:
		case 0x1182c ... 0x1183a:
		case 0x11930 ... 0x11935:
		case 0x11937: case 0x11938:
		case 0x1193b ... 0x1193e:
		case 0x11940:
		case 0x11942: case 0x11943:
		case 0x119d1 ... 0x119d7:
		case 0x119da ... 0x119e0:
		case 0x119e4:
		case 0x11a01 ... 0x11a0a:
		case 0x11a33 ... 0x11a39:
		case 0x11a3b ... 0x11a3e:
		case 0x11a47:
		case 0x11a51 ... 0x11a5b:
		case 0x11a8a ... 0x11a99:
		case 0x11c2f ... 0x11c36:
		case 0x11c38 ... 0x11c3f:
		case 0x11c92 ... 0x11ca7:
		case 0x11ca9 ... 0x11cb6:
		case 0x11d31 ... 0x11d36:
		case 0x11d3a:
		case 0x11d3c: case 0x11d3d:
		case 0x11d3f ... 0x11d45:
		case 0x11d47:
		case 0x11d8a ... 0x11d8e:
		case 0x11d90: case 0x11d91:
		case 0x11d93 ... 0x11d97:
		case 0x11ef3 ... 0x11ef6:
		case 0x16af0 ... 0x16af4:
		case 0x16b30 ... 0x16b36:
		case 0x16f4f:
		case 0x16f51 ... 0x16f87:
		case 0x16f8f ... 0x16f92:
		case 0x16fe4:
		case 0x16ff0: case 0x16ff1:
		case 0x1bc9d: case 0x1bc9e:
		case 0x1d165 ... 0x1d169:
		case 0x1d16d ... 0x1d172:
		case 0x1d17b ... 0x1d182:
		case 0x1d185 ... 0x1d18b:
		case 0x1d1aa ... 0x1d1ad:
		case 0x1d242 ... 0x1d244:
		case 0x1da00 ... 0x1da36:
		case 0x1da3b ... 0x1da6c:
		case 0x1da75:
		case 0x1da84:
		case 0x1da9b ... 0x1da9f:
		case 0x1daa1 ... 0x1daaf:
		case 0x1e000 ... 0x1e006:
		case 0x1e008 ... 0x1e018:
		case 0x1e01b ... 0x1e021:
		case 0x1e023: case 0x1e024:
		case 0x1e026 ... 0x1e02a:
		case 0x1e130 ... 0x1e136:
		case 0x1e2ec ... 0x1e2ef:
		case 0x1e8d0 ... 0x1e8d6:
		case 0x1e900 ... 0x1e94a:
		case 0xe0100 ... 0xe01ef:
			return true;
		default: return false;
	}
}

bool IsCharXxxfix(wchar_t c)
{
	return IsCharPrefix(c) || IsCharSuffix(c);
}
