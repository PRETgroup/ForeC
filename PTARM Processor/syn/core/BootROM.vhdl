library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity BootROM is 
  generic (
    DATAWIDTH : integer := 32;
    ADDRWIDTH : integer := 5);
  port (
    CLK : in std_logic;
    EN_A : in std_logic;
    EN_B : in std_logic;
    WEN_A : in std_logic;
    ADDR_A : in std_logic_vector(ADDRWIDTH-1 downto 0);
    DI_A : in std_logic_vector(DATAWIDTH-1 downto 0);
    DO_A : out std_logic_vector(DATAWIDTH-1 downto 0);
    ADDR_B : in std_logic_vector(ADDRWIDTH-1 downto 0);
    DO_B : out std_logic_vector(DATAWIDTH-1 downto 0));
  
    -- NOTE! Make sure to hook addr signal to bits (4 downto 2),
    -- not starting from 0!! We assume its word aligned access only!!
end entity BootROM;
architecture behavioral of BootROM is
  type mem is array (((2**ADDRWIDTH) - 1) downto 0) of std_logic_vector(DATAWIDTH-1 downto 0);

  signal my_Rom : mem := (
0 => X"ea000013",
1 => X"ea00001e",
2 => X"ea00001d",
3 => X"ea00001c",
4 => X"ea00001b",
5 => X"e1a00000",
6 => X"ea000019",
7 => X"ea000018",
8 => X"e1a00000",
9 => X"e52de004",
10 => X"e52d1004",
11 => X"e52d2004",
12 => X"ee001d00",
13 => X"e3a02004",
14 => X"e0010192",
15 => X"e59f200c",
16 => X"e081e002",
17 => X"e49d2004",
18 => X"e49d1004",
19 => X"e59ef000",
20 => X"0001ffe0",
21 => X"e59f224c",
22 => X"e3a03000",
23 => X"e5c23000",
24 => X"ee005d00",
25 => X"e3550000",
26 => X"0a000010",
27 => X"e5d24000",
28 => X"e3540000",
29 => X"0afffffc",
30 => X"e1a0e00f",
31 => X"e3a0f000",
32 => X"eafffff3",
33 => X"eafffffe",
34 => X"52415450",
35 => X"3035204d",
36 => X"207a684d",
37 => X"65677545",
38 => X"3220656e",
39 => X"754a2034",
40 => X"3220656e",
41 => X"0d363130",
42 => X"07ff000a",
43 => X"000073a1",
44 => X"eb00004f",
45 => X"e3a02021",
46 => X"e59f31ec",
47 => X"eb000038",
48 => X"eb00005e",
49 => X"e3e020f6",
50 => X"e3a03001",
51 => X"e5823000",
52 => X"e1a03083",
53 => X"e3130010",
54 => X"13a03001",
55 => X"e59f11cc",
56 => X"eb00004f",
57 => X"e3510000",
58 => X"0afffff7",
59 => X"e35000ff",
60 => X"0a000002",
61 => X"e59f11b4",
62 => X"eb000042",
63 => X"eafffff0",
64 => X"e3a000fe",
65 => X"e59f11a4",
66 => X"eb00003e",
67 => X"e3510000",
68 => X"0affffeb",
69 => X"e3a02000",
70 => X"e3a03018",
71 => X"e59f118c",
72 => X"eb00003f",
73 => X"e3510000",
74 => X"0affffe5",
75 => X"e1822310",
76 => X"e2533008",
77 => X"5afffff8",
78 => X"e3a03000",
79 => X"e59f116c",
80 => X"eb000037",
81 => X"e3510000",
82 => X"0affffdd",
83 => X"e4c30001",
84 => X"e2522001",
85 => X"1afffff8",
86 => X"eb000038",
87 => X"e59f5144",
88 => X"e3a06001",
89 => X"e5c56000",
90 => X"eef00d00",
91 => X"e1a0e00f",
92 => X"e3a0f000",
93 => X"eef40d25",
94 => X"e2444002",
95 => X"e2455002",
96 => X"eb00001b",
97 => X"e3a02004",
98 => X"e59f3124",
99 => X"eb000004",
100 => X"e1a02004",
101 => X"eb00000b",
102 => X"e1a02005",
103 => X"eb000009",
104 => X"eaffffc7",
105 => X"e1a0600e",
106 => X"e4d30001",
107 => X"e59f10fc",
108 => X"eb000014",
109 => X"e3510000",
110 => X"0affffc1",
111 => X"e2522001",
112 => X"1afffff8",
113 => X"e1a0f006",
114 => X"e1a0600e",
115 => X"e3a03018",
116 => X"e1a00332",
117 => X"e20000ff",
118 => X"e59f10d0",
119 => X"eb000009",
120 => X"e3510000",
121 => X"0affffb6",
122 => X"e2533008",
123 => X"5afffff7",
124 => X"e1a0f006",
125 => X"e59f80bc",
126 => X"e59f90bc",
127 => X"e59fa0bc",
128 => X"e59fb0bc",
129 => X"e1a0f00e",
130 => X"e5da7000",
131 => X"e3570000",
132 => X"05cb0000",
133 => X"01a0f00e",
134 => X"e2511001",
135 => X"1afffff9",
136 => X"e1a0f00e",
137 => X"e5d87000",
138 => X"e3570001",
139 => X"05d90000",
140 => X"01a0f00e",
141 => X"e2511001",
142 => X"1afffff9",
143 => X"e1a0f00e",
144 => X"e3a00000",
145 => X"e3e010f6",
146 => X"e5c10000",
147 => X"e3e010ff",
148 => X"e5c10000",
149 => X"e3e00000",
150 => X"e3e010df",
151 => X"e5c10000",
152 => X"e3e010d7",
153 => X"e5c10000",
154 => X"e3e010cf",
155 => X"e5c10000",
156 => X"e3e010c7",
157 => X"e5c10000",
158 => X"e3e010bf",
159 => X"e5c10000",
160 => X"e3e010b7",
161 => X"e5c10000",
162 => X"e3e010af",
163 => X"e5c10000",
164 => X"e3e010a7",
165 => X"e5c10000",
166 => X"e3a00000",
167 => X"e3e0109f",
168 => X"e5c10000",
169 => X"e1a0f00e",
170 => X"0001ffe0",
171 => X"fffe0088",
172 => X"000d9fb9",
173 => X"fffe00aa",
174 => X"ffff0000",
175 => X"ffff0004",
176 => X"ffff0008",
177 => X"ffff000c",
others => X"00000000"
    );

  
begin
  port_a: process (CLK)
  begin 
    if (CLK'event and CLK = '1') then 
      if EN_A = '1' then
        DO_A <= my_Rom(conv_integer(ADDR_A));
        if WEN_A = '1' then
          my_Rom(conv_integer(ADDR_A)) <= DI_A;
        end if;
      end if;
    end if;
  end process;


  port_b: process (CLK)
  begin 
    if (CLK'event and CLK = '1') then 
      if EN_B = '1' then
        DO_B <= my_Rom(conv_integer(ADDR_B));
      end if;
    end if;
  end process;


end architecture behavioral;
